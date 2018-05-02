#!/usr/bin/env python

from contextlib import contextmanager
import copy
import json
import os
import re
import signal
import subprocess
import shlex
import time
import argparse

#--------------------------------------------------------------------------------
# Check status of crab jobs and resubmit jobs that have failed.
# In case jobs that are "stuck" in the same state for more than one day,
# a new crab task with the "stuck" jobs is created
#
# Author: Christian Veelken (Tallinn)
#
# NOTE: The following variables need to be reviewed before running the script
#        o SAMPLES
#
# Examples:
#
# $ crabSitter.py -h
#
# usage: crabSitter.py [-h] [-c path] [-p pattern] [-w name] [-f]
#
# optional arguments:
#  -h, --help                      show this help message and exit
#  -c path, --crab-file path       Path to the parent directory of crab log directories (and crabSitter.json) (default: ~/crab_projects)
#  -p pattern, --prefix pattern    Prefix of the CRAB log directories (default: crab_NanoAOD_2017_v1)
#  -w name, --whitelist-tier name  Whitelist a tier (e.g. 'T2_EE_Estonia') (default: None)
#  -f, --force-resubmit            Use production Ntuples (default: False)
#
#--------------------------------------------------------------------------------

SAMPLES = [
    # leave empty to check all samples; otherwise loops over all CRAB log directories; e.g.:
    #'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8__RunIISummer17MiniAOD-92X_upgrade2010_ext1-v1',
    #'ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8__RunIISummer17MiniAOD-NZtic_v10-v1',
]
STATUSFILENAME      = 'crabSitter.json'
OUTPUTFILEPATH_BASE = '/hdfs/cms/'

EXECUTABLE_LS   = 'ls'
EXECUTABLE_RM   = 'rm'
EXECUTABLE_CRAB = 'crab'
EXECUTABLE_TAR  = 'tar'

KEY_VALUE_PAIR_REGEX   = r'(?P<key>[a-zA-Z0-9_.]+)\s*=\s*(?P<value>.+)\s*'
KEY_VALUE_PAIR_MATCHER = re.compile(KEY_VALUE_PAIR_REGEX)

ATTRIBUTE_REQUESTNAME    = 'config.General.requestName'
ATTRIBUTE_INPUTFILENAME  = 'config.Data.inputDataset'
ATTRIBUTE_LUMIMASK       = 'config.Data.lumiMask'
ATTRIBUTE_OUTPUTFILENAME = 'config.Data.outputDatasetTag'
ATTRIBUTE_OUTPUTFILEPATH = 'config.Data.outLFNDirBase'
ATTRIBUTE_WHITELIST      = 'config.Site.whitelist'
ATTRIBUTE_BLACKLIST      = 'config.Site.blacklist'

CRABJOBSUMMARY_REGEX   = r'(?P<numJobs>\d+)'
CRABJOBSUMMARY_MATCHER = re.compile(CRABJOBSUMMARY_REGEX)

TIME_LIMIT = 60 * 60 * 24

def runCommand(commandLine):
    print(commandLine)
    args = shlex.split(commandLine)
    retVal = subprocess.Popen(args, stdout = subprocess.PIPE)
    return retVal.stdout.readlines()

def runCommand_via_shell(commandLine, tmpShellScriptFileName = 'crabSitter_tmp.sh',
                         tmpOutputFileName = 'crabSitter_tmp.out'):
    # CV: crab is implemented in python and seems to cause problem when called directly from python;
    #     wrap 'crab -status' command into simple shell script
    print(commandLine)
    tmpShellScriptFile = open(tmpShellScriptFileName, "w")
    tmpShellScriptFile.write("#!/bin/bash -f\n")
    tmpShellScriptFile.write("%s > %s\n" % (commandLine, tmpOutputFileName))
    tmpShellScriptFile.close()
    subprocess.call('chmod +x %s' % tmpShellScriptFileName, shell = True)
    subprocess.call('./%s' % tmpShellScriptFileName, shell = True)
    subprocess.call('rm %s' % tmpShellScriptFileName, shell = True)
    tmpOutputFile = open(tmpOutputFileName, "r")
    retVal = tmpOutputFile.readlines()
    tmpOutputFile.close()
    subprocess.call('rm %s' % tmpOutputFileName, shell = True)
    return retVal

def runCommand_via_shell_with_timeout(commandLine, tmpShellScriptFileName = 'crabSitter_tmp.sh',
                                      tmpOutputFileName = 'crabSitter_tmp.out', timeout = 30):

    print("<runCommand_via_shell_with_timeout (timeout = %1.0fs)>:" % timeout)

    class TimeoutException(Exception): pass

    @contextmanager
    def time_limit_func(seconds):
        def signal_handler(signum, frame):
            raise TimeoutException("Timed out!")
        signal.signal(signal.SIGALRM, signal_handler)
        signal.alarm(seconds)
        try:
            yield
        finally:
            signal.alarm(0)

    try:
        with time_limit_func(timeout):
            return runCommand_via_shell(
                commandLine, tmpShellScriptFileName = tmpShellScriptFileName,
                tmpOutputFileName = tmpOutputFileName
            )
    except TimeoutException as msg:
        print("Timed out!")

def removeLeadingSlash(filePath):
    retVal = filePath
    if retVal.find("/") == 0:
        retVal = retVal[1:]
    return retVal

def getOutputFilePaths(outputFilePath):
    outputFilePaths = []
    file_or_directoryNames = runCommand('%s %s' % (EXECUTABLE_LS, outputFilePath))
    for file_or_directoryName in file_or_directoryNames:
        file_or_directoryName = file_or_directoryName.replace("\n", "")
        file_or_directoryName = os.path.join(outputFilePath, file_or_directoryName)
        if os.path.isdir(file_or_directoryName):
            outputFilePaths.append(file_or_directoryName)
            outputFilePaths.extend(getOutputFilePaths(file_or_directoryName))
    return outputFilePaths

def checkOutputFiles(outputFileInfos, jobId, jobIds_force_resubmit):
    outputFileName_regex   = 'tree_(?P<jobId>\d+).root'
    outputFileName_matcher = re.compile(outputFileName_regex)

    resubmit_job = False

    outputFileInfos_matched = []
    for outputFileInfo in outputFileInfos:
        outputFileName_match = outputFileName_matcher.match(outputFileInfo['file'])
        if outputFileName_match:
            outputFile_jobId = int(outputFileName_match.group('jobId'))
            if outputFile_jobId == jobId:
                outputFileInfos_matched.append(outputFileInfo)
    if len(outputFileInfos_matched) == 0:
        resubmit_job = True
    elif len(outputFileInfos_matched) > 1:
        print("Warning: jobId = %i produced multiple output files = %s !!" % \
              (jobId, [ outputFileInfo['file'] for outputFileInfo in outputFileInfos_matched ])
        )
        # keep file with maximum size;
        # in case multiple files have the same size, keep the newest one
        outputFileName_keep = None
        fileSize_keep = None
        date_and_time_keep = None
        outputFiles_to_delete = []
        for outputFileInfo in outputFileInfos_matched:
            outputFileName = outputFileInfo['file']
            fileSize = outputFileInfo['size']
            date_and_time = outputFileInfo['time']
            if not outputFileName_keep or fileSize > fileSize_keep or \
              (fileSize == fileSize_keep and date_and_time > date_and_time_keep):
                outputFileName_keep = outputFileName
                fileSize_keep = fileSize
                date_and_time_keep = date_and_time
        for outputFileInfo in outputFileInfos_matched:
            if outputFileInfo['file'] != outputFileName_keep:
                print("--> deleting copy = %s" % outputFileInfo['path'])
                outputFiles_to_delete.append(outputFileInfo['path'])

    if resubmit_job:
        print("Info: jobId = %i produced no output file(s) --> resubmitting it" % jobId)
        jobIds_force_resubmit.append(jobId)

if __name__ == '__main__':

    class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
        def _split_lines(self, text, width):
            if text.startswith('R|'):
                return text[2:].splitlines()
            return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

    parser = argparse.ArgumentParser(
        formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
    )
    parser.add_argument('-c', '--crab-file',
        type = str, dest = 'crab_file', metavar = 'path',
        default = os.path.join(os.path.expanduser('~'), 'crab_projects'), required = False,
        help = 'R|Path to the parent directory of crab log directories (and %s)' % STATUSFILENAME,
    )
    parser.add_argument('-p', '--prefix',
        type = str, dest = 'prefix', metavar = 'pattern',
        default = 'crab_NanoAOD_2017_v1', required = False,
        help = 'R|Prefix of the CRAB log directories',
    )
    parser.add_argument('-s', '--samples',
        type = str, dest = 'samples', metavar = 'pattern',
        default = '.*', required = False,
        help = 'R|Regex pattern for individual sample names'
    )
    parser.add_argument('-w', '--whitelist-tier',
        type = str, dest = 'whitelist_tier', metavar = 'name', default = '', required = False,
        help = "R|Whitelist tier(s) (e.g. 'T2_EE_Estonia'); separate multiple tiers by a comma",
    )
    parser.add_argument('-b', '--blacklist-tier',
        type = str, dest = 'blacklist_tier', metavar = 'name', default = '', required = False,
        help = "R|Blacklist tier(s); separate multpiple tiers by a comma",
    )
    parser.add_argument('-r', '--maxjobruntime',
        type = int, dest = 'maxjobruntime', metavar = 'minutes', default = 1315, required = False,
        help = 'R|Maximum job runtime in minutes',
    )
    parser.add_argument('-f', '--force-resubmit',
        dest = 'force_resubmit', action = 'store_true', default = False, required = False,
        help = 'R|Force resubmission',
    )
    args = parser.parse_args()

    crabFilePath     = args.crab_file
    prefix           = args.prefix
    sampleName_regex = args.samples
    force_resubmit   = args.force_resubmit
    blacklist_tier   = args.blacklist_tier
    whitelist_tier   = args.whitelist_tier
    maxjobruntime    = args.maxjobruntime
    assert(maxjobruntime > 0)

    crabJobPath = crabFilePath
    if not os.path.isdir(crabJobPath):
        raise ValueError("Invalid crabJobPath = '%s' !!" % crabJobPath)
    currentDir = os.getcwd()
    os.chdir(crabJobPath)

    # CV: check that crab environment is set
    which_crab = runCommand('which %s' % EXECUTABLE_CRAB)
    if len(which_crab) != 1:
        raise ValueError("crab environment not set !!")

    print("<crabSitter>:")

    jobName_regex = r'%s_(?P<sample>[a-zA-Z0-9_-]+)' % prefix
    jobName_matcher = re.compile(jobName_regex)
    sampleName_matcher = re.compile(sampleName_regex)

    jobStatus_dict = {}
    if os.path.exists(STATUSFILENAME):
        if os.path.isfile(STATUSFILENAME):
            print("Loading previous status of crab jobs from file '%s'" % STATUSFILENAME)
            statusFile = open(STATUSFILENAME, "r")
            jobStatus_dict = json.load(statusFile)
            statusFile.close()
        else:
            raise ValueError("File '%s' exists, but is a directory !!" % STATUSFILENAME)
    else:
        print("File '%s' does not yet exist...creating it." % STATUSFILENAME)
    jobStatus_dict_updated = copy.deepcopy(jobStatus_dict)

    current_time = time.time()
    print("current time = %s" % time.asctime(time.gmtime(current_time)))

    # CV: define maximum time (default is one day = 24*60*60 seconds) for which crab jobs are allowed to
    #     stay in same 'State' and with same number of 'Retries' before they they get automatically
    #     resubmitted as a new crab task
    checkJobOutputFiles = True
    shellScriptCommands = []

    crabJobs = os.listdir(os.path.expanduser(crabFilePath))
    for crabJob in crabJobs:
        print("processing Task = '%s'" % crabJob)
        crabJob_match = jobName_matcher.match(crabJob)
        if not crabJob_match:
            continue

        print("checking directory/file = '%s'" % crabJob)
        crabDir = os.path.join(crabFilePath, crabJob)
        if not os.path.isdir(crabDir):
            print(" not a crab directory --> skipping")
            continue

        sample = crabJob_match.group('sample')
        sample_match = sampleName_matcher.match(sample)
        if not sample_match:
            continue

        print(" matched.")
        if not jobStatus_dict.has_key(crabJob):
            jobStatus_dict[crabJob] = {}

        if len(SAMPLES) > 0 and not sample in SAMPLES:
            print("sample = '%s' not in list of samples = %s --> skipping" % (sample, SAMPLES))
            continue

        # unpack tar-ball that contains crab config file
        if not os.path.isdir(os.path.join(crabFilePath, crabJob, "debug")):
            crabConfigFileName_tarball = os.path.join(crabFilePath, crabJob, "inputs/debugFiles.tgz")
            print("unpacking crab config file from tar-ball '%s'" % crabConfigFileName_tarball)
            runCommand("%s -xzvf %s --directory %s" % (EXECUTABLE_TAR, crabConfigFileName_tarball, crabDir))

        # run 'crab status' command (abort after 5 minutes = 300 seconds)
        crabStatus_lines = runCommand_via_shell_with_timeout(
            '%s status -d %s --json' % (EXECUTABLE_CRAB, crabDir), timeout = 300
        )
        if not crabStatus_lines:
            print("Failed to run 'crab -status' command for sample = '%s' --> skipping" % sample)
            continue

        # open crab config file and read path and name of output file
        crabConfigFileName = os.path.join(crabDir, 'debug/crabConfig.py')
        crabConfigFile = open(crabConfigFileName, "r")
        crabConfig_lines = crabConfigFile.readlines()
        requestName = None
        inputFileName = None
        lumiMask = None
        outputFileName = None
        outputFilePath = None
        whitelist = None
        for crabConfig_line in crabConfig_lines:
            crabConfig_line = crabConfig_line.replace("\n", "")
            key_value_pair_match = KEY_VALUE_PAIR_MATCHER.match(crabConfig_line)
            if key_value_pair_match:
                key = key_value_pair_match.group('key')
                value = key_value_pair_match.group('value')
                value = value.replace("'", "") # CV: remove apostrophes that enclose strings
                if key == ATTRIBUTE_REQUESTNAME:
                    requestName = value
                elif key == ATTRIBUTE_INPUTFILENAME:
                    inputFileName = value
                elif key == ATTRIBUTE_LUMIMASK:
                    lumiMask = value
                elif key == ATTRIBUTE_OUTPUTFILENAME:
                    outputFileName = value
                elif key == ATTRIBUTE_OUTPUTFILEPATH:
                    outputFilePath = value
                elif key == ATTRIBUTE_WHITELIST:
                    whitelist = value
        crabConfigFile.close()
        if not (requestName and inputFileName and outputFileName and outputFilePath):
            raise ValueError("Failed to parse crab config file = '%s' !!" % crabConfigFileName)
        outputFilePath_part1 = OUTPUTFILEPATH_BASE
        outputFilePath_part2 = removeLeadingSlash(outputFilePath)
        pos = inputFileName.find("/")
        if pos == 0:
            pos = inputFileName.find("/", 1)
        if pos == -1:
            raise ValueError("Failed to parse attribute '%s' = '%s' !!" % (ATTRIBUTE_INPUTFILENAME, inputFileName))
        outputFilePath_part3 = removeLeadingSlash(inputFileName[:pos])
        outputFilePath_part4 = removeLeadingSlash(outputFileName)
        outputFilePath_sample = os.path.join(
            outputFilePath_part1, outputFilePath_part2, outputFilePath_part3, outputFilePath_part4
        )
        outputFilePaths_sample = getOutputFilePaths(outputFilePath_sample)

        # read list of files existing in output file path
        if checkJobOutputFiles:
            outputFileInfos = []
            for outputFilePath_sample in outputFilePaths_sample:
                file_or_directoryNames = runCommand('%s %s' % (EXECUTABLE_LS, outputFilePath_sample))
                for file_or_directoryName in file_or_directoryNames:
                    file_or_directoryName = file_or_directoryName.replace("\n", "")
                    file_or_directoryName = os.path.join(outputFilePath_sample, file_or_directoryName)
                    if os.path.isfile(file_or_directoryName) and file_or_directoryName.find(".root") != -1:
                        outputFileInfo = {
                            'file' : os.path.basename(file_or_directoryName),
                            'path' : file_or_directoryName,
                            'size' : os.path.basename(file_or_directoryName),
                            'time' : os.path.basename(file_or_directoryName)
                        }
                        outputFileInfos.append(outputFileInfo)
        print("outputFileInfos:")
        print([ outputFileInfo['file'] for outputFileInfo in outputFileInfos ])

        # parse job status information returned by executing 'crab status' command
        numJobs = None
        jobStatus_summary = {}
        jobIds_resubmit = []
        jobIds_force_resubmit = []
        for crabStatus_line in crabStatus_lines:
            crabStatus_line = crabStatus_line.rstrip('\n')
            if 'Jobs status:' in crabStatus_line:
                crabStatus_line_whitespaceSplit = crabStatus_line.split()[-1]
                crabStatus_line_slashSplit = crabStatus_line_whitespaceSplit.split('/')
                assert(len(crabStatus_line_slashSplit) == 2)
                crabJobSummary_match = CRABJOBSUMMARY_MATCHER.match(crabStatus_line_slashSplit[1])
                assert(crabJobSummary_match)
                numJobs = crabJobSummary_match.group('numJobs')
                print("Task = '%s' has %s jobs." % (crabJob, numJobs))
                continue

            if crabStatus_line.startswith('{'):
                crab_json = json.loads(crabStatus_line)
                for jobId_str, jobStatus_entry in crab_json.items():
                    jobId = int(jobId_str)
                    if crabJob not in jobStatus_dict_updated.keys():
                        jobStatus_dict_updated[crabJob] = {}
                    if jobId not in jobStatus_dict_updated[crabJob]:
                        jobStatus_dict_updated[crabJob][jobId] = {}
                    State = jobStatus_entry['State']
                    Retries = jobStatus_entry['Retries']
                    jobStatus_dict_updated[crabJob][jobId]['State'] = State
                    jobStatus_dict_updated[crabJob][jobId]['Retries'] = Retries

                    if State not in jobStatus_summary.keys():
                        jobStatus_summary[State] = 0
                    jobStatus_summary[State] += 1

                    print("jobId = %i: State = '%s', Retries = %i" % (jobId, State, Retries))
                    if State in [ "finished" ] or force_resubmit:
                        checkOutputFiles(outputFileInfos, jobId, jobIds_force_resubmit)
                    elif State in [ "failed", "transferring" ]:
                        # CV: check if job remained in this state for more than one day;
                        #     if so, assume that crab job got "stuck" and create a new crab task with this job
                        if crabJob in jobStatus_dict.keys() and jobId in jobStatus_dict[crabJob].keys():
                            if Retries == jobStatus_dict[crabJob][jobId]['Retries'] and \
                                  (current_time - jobStatus_dict[crabJob]['lastUpdate']) > TIME_LIMIT:
                                print(
                                    "Info: jobId = %i got stuck in state '%s' --> " \
                                    "creating a new crab task with this job !!" % (jobId, State)
                                )
                                jobIds_force_resubmit.append(jobId)
                        elif State in [ "failed" ]:
                            print("Info: jobId = %i failed --> resubmitting it" % jobId)
                            jobIds_resubmit.append(jobId)
                break

        print("Job summary:")
        for jobStatus, numJobs_status in jobStatus_summary.items():
            print(" %i Jobs in status = '%s'" % (numJobs_status, jobStatus))

        # sort jobIds in ascending order
        jobIds_resubmit.sort()
        jobIds_force_resubmit.sort()

        # make sure each jobId is contained in list at most once
        jobIds_resubmit_unique = []
        for jobId in jobIds_resubmit:
            if not jobId in jobIds_resubmit_unique:
                jobIds_resubmit_unique.append(jobId)
        jobIds_force_resubmit_unique = []
        for jobId in jobIds_force_resubmit:
            if not jobId in jobIds_force_resubmit_unique:
                jobIds_force_resubmit_unique.append(jobId)

        # resubmit jobs that that failed
        print("jobIds_resubmit = %s" % jobIds_resubmit_unique)
        print("(%i jobs)" % len(jobIds_resubmit_unique))
        if len(jobIds_resubmit_unique) > 0:
            # resubmit crab jobs in groups of 500 jobs
            numJobsPerResubmit = 500
            for jobIndex in range(len(jobIds_resubmit_unique)/numJobsPerResubmit + 1):
                firstJob = jobIndex*numJobsPerResubmit
                print("firstJob = %i" % firstJob)
                lastJob = (jobIndex + 1)*numJobsPerResubmit - 1
                print("lastJob = %i" % lastJob)
                jobIds_resubmit_string = ",".join([
                    "%i" % jobId for jobId in jobIds_resubmit_unique[firstJob:lastJob]
                ])
                print("jobIds_resubmit_string = '%s'" % jobIds_resubmit_string)
                commandLine = '%s resubmit -d %s --jobids %s' % (EXECUTABLE_CRAB, crabDir, jobIds_resubmit_string)
                if whitelist_tier:
                    commandLine += " --sitewhitelist=%s" % whitelist_tier
                if blacklist_tier:
                    commandLine += " --siteblacklist=%s" % blacklist_tier
                commandLine += " --maxjobruntime=%d" % maxjobruntime
                print("commandLine = '%s'" % commandLine)
                runCommand_via_shell(commandLine)

        # create new crab task with jobs that remained in 'failed' or 'transferring' state for more than one day
        print("jobIds_force_resubmit = %s" % jobIds_force_resubmit_unique)
        print("(%i jobs)" % len(jobIds_force_resubmit_unique))
        if len(jobIds_force_resubmit_unique) > 0:
            crabReportFileName = os.path.join(crabDir, "results/notFinishedLumis.json")
            if not os.path.isfile(crabReportFileName):
                commandLine = '%s report -d %s' % (EXECUTABLE_CRAB, crabDir)
                runCommand_via_shell(commandLine)
            if not 'forceResubmissions' in jobStatus_dict_updated[crabJob].keys():
                jobStatus_dict_updated[crabJob]['forceResubmissions'] = 1
            jobStatus_dict_updated[crabJob]['forceResubmissions'] = jobStatus_dict_updated[crabJob]['forceResubmissions'] + 1
            # write new crab config file
            crabConfigFileName_new = os.path.join(
                crabFilePath, 'crabConfig_%s_forceResubmit%i.py' % \
                (crabJob, jobStatus_dict_updated[crabJob]['forceResubmissions'])
            )
            crabConfigFile_new = open(crabConfigFileName_new, "w")
            value_lumiMask = "'%s'" % crabReportFileName
            print("value_lumiMask = %s" % value_lumiMask)
            isSet_lumiMask = False
            value_whitelist = "%s" % whitelist_tier.split(',')
            print("value_whitelist = %s" % value_whitelist)
            isSet_whitelist = False
            value_blacklist = "%s" % blacklist_tier.split(',')
            print("value_blacklist = %s" % value_blacklist)
            isSet_blacklist = False
            for crabConfig_line in crabConfig_lines:
                key_value_pair_match = KEY_VALUE_PAIR_MATCHER.match(crabConfig_line)
                crabConfig_line_new = crabConfig_line
                if key_value_pair_match:
                    key = key_value_pair_match.group('key')
                    value = key_value_pair_match.group('value')
                    if key == ATTRIBUTE_REQUESTNAME:
                        value = "'%s_forceResubmit%i'" % \
                                (value.replace("'", ""), jobStatus_dict_updated[crabJob]['forceResubmissions'])
                    elif key == ATTRIBUTE_LUMIMASK:
                        value = value_lumiMask
                        isSet_lumiMask = True
                    elif key == ATTRIBUTE_OUTPUTFILENAME:
                        value = "'%s_forceResubmit%i'" % \
                                (value.replace("'", ""), jobStatus_dict_updated[crabJob]['forceResubmissions'])
                    elif key == ATTRIBUTE_WHITELIST:
                        if whitelist_tier:
                            value = value_whitelist
                        isSet_whitelist = True
                    elif key == ATTRIBUTE_BLACKLIST:
                        if blacklist_tier:
                            value = value_blacklist
                        isSet_blacklist = True
                    crabConfig_line_new = "%s = %s\n" % (key, value)
                crabConfigFile_new.write(crabConfig_line_new)
            if not isSet_lumiMask:
                crabConfig_line_new = "%s = %s\n" % (ATTRIBUTE_LUMIMASK, value_lumiMask)
                crabConfigFile_new.write(crabConfig_line_new)
            if not isSet_whitelist and whitelist_tier:
                crabConfig_line_new = "%s = %s\n" % (ATTRIBUTE_WHITELIST, value_whitelist)
                crabConfigFile_new.write(crabConfig_line_new)
            if not isSet_blacklist and blacklist_tier:
                crabConfig_line_new = "%s = %s\n" % (ATTRIBUTE_BLACKLIST, value_blacklist)
                crabConfigFile_new.write(crabConfig_line_new)
            crabConfigFile_new.close()
            commandLine = '%s submit -c %s' % (EXECUTABLE_CRAB, crabConfigFileName_new)
            print("commandLine = '%s'" % commandLine)
            runCommand_via_shell(commandLine)

        print("")

    statusFile = open(STATUSFILENAME, "w")
    json.dump(jobStatus_dict_updated, statusFile, indent = 2)
    statusFile.close()

    os.chdir(currentDir)

    print("Finished running 'crabSitter.py'.")
