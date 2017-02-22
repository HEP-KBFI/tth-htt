#!/usr/bin/env python

from contextlib import contextmanager
import copy
import json
import os
import re
import signal
import sys
import subprocess
import shlex
import time

#--------------------------------------------------------------------------------
# Check status of crab jobs and resubmit jobs that have failed.
# In case jobs that are "stuck" in the same state for more than one day,
# a new crab task with the "stuck" jobs is created
#
# Author: Christian Veelken (Tallinn)
#
# NOTE: The following variables need to be updated before running the script
#        o crabFilePath
#        o heppyFilePath
#        o jobName_regex
#        o samples
#        o force_resubmit
#
# Examples:
# 
# ./crabSitter.py 
#
#--------------------------------------------------------------------------------

print("<crabSitter>:")

crabFilePath = '/scratch/veelken/crab_sub/crab_projects_VHBB_V25tthtautau/'

statusFileName = 'crabSitter.json'

heppyFilePath = '/home/veelken/CMSSW_8_0_21/src/VHbbAnalysis/Heppy/test/crab'
if not os.path.isdir(heppyFilePath):
    raise ValueError("Invalid heppyFilePath = '%s' !!" % heppyFilePath)
currentDir = os.getcwd()
os.chdir(heppyFilePath)

jobName_regex = r'crab_VHBB_V25tthtautau_(?P<sample>[a-zA-Z0-9_-]+)'
jobName_matcher = re.compile(jobName_regex)

samples = [
    # leave empty to check all samples
    "DoubleEG__Run2016C-23Sep2016-v1",
    "DoubleMuon__Run2016C-23Sep2016-v1",
    "DoubleMuon__Run2016G-23Sep2016-v1",
    "MuonEG__Run2016C-23Sep2016-v1",
    "MuonEG__Run2016G-23Sep2016-v1",
    "SingleElectron__Run2016C-23Sep2016-v1",
    "SingleElectron__Run2016G-23Sep2016-v1",
    "SingleMuon__Run2016C-23Sep2016-v1",
    "SingleMuon__Run2016G-23Sep2016-v1",
    "Tau__Run2016C-23Sep2016-v1",
    "Tau__Run2016G-23Sep2016-v1",
]

outputFilePath_base = '/hdfs/cms/'

executable_ls = 'ls'
executable_rm = 'rm'
executable_crab = 'crab'
executable_tar = 'tar'

force_resubmit = False
##force_resubmit = True

whitelist_when_force_resubmit = None # do not use whitelist
##whitelist_when_force_resubmit = [ 'T2_EE_Estonia' ] # run job on Tallinn T2

def runCommand(commandLine):
    print(commandLine)
    args = shlex.split(commandLine)
    retVal = subprocess.Popen(args, stdout = subprocess.PIPE)
    #retVal.wait()
    return retVal.stdout.readlines()

whoami = runCommand('whoami')
if len(whoami) != 1:
    raise ValueError("Failed to identify userName !!")
userName = whoami[0].strip()
print("userName = %s" % userName)

# CV: check that crab environment is set
which_crab = runCommand('which crab')
if len(which_crab) != 1:
    raise ValueError("crab environment not set !!")

# delete crabSitter.json file to reset all time-stamps
#runCommand('%s %s' % (executable_rm, statusFileName))

def runCommand_via_shell(commandLine, tmpShellScriptFileName = 'crabSitter_tmp.sh', tmpOutputFileName = 'crabSitter_tmp.out'):
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

def runCommand_via_shell_with_timeout(commandLine, tmpShellScriptFileName = 'crabSitter_tmp.sh', tmpOutputFileName = 'crabSitter_tmp.out', timeout = 30):

    print "<runCommand_via_shell_with_timeout (timeout = %1.0fs)>:" % timeout 
    
    class TimeoutException(Exception): pass

    @contextmanager
    def time_limit(seconds):
        def signal_handler(signum, frame):
            raise TimeoutException, "Timed out!"
        signal.signal(signal.SIGALRM, signal_handler)
        signal.alarm(seconds)
        try:
            yield
        finally:
            signal.alarm(0)

    try:
        with time_limit(timeout):
            return runCommand_via_shell(commandLine, tmpShellScriptFileName = tmpShellScriptFileName, tmpOutputFileName = tmpOutputFileName)
    except TimeoutException, msg:
        print "Timed out!"

def removeLeadingSlash(filePath):
    retVal = filePath
    if retVal.find("/") == 0:
        retVal = retVal[1:]
    return retVal

def getOutputFilePaths(outputFilePath):
    #print "<getOutputFilePaths>:"
    #print "outputFilePath = '%s'" % outputFilePath
    outputFilePaths = []
    file_or_directoryNames = runCommand('%s %s' % (executable_ls, outputFilePath))
    for file_or_directoryName in file_or_directoryNames:
        file_or_directoryName = file_or_directoryName.replace("\n", "")
        file_or_directoryName = os.path.join(outputFilePath, file_or_directoryName)
        #print "file_or_directoryName = '%s'" % file_or_directoryName
        if os.path.isdir(file_or_directoryName):
            outputFilePaths.append(file_or_directoryName)
            outputFilePaths.extend(getOutputFilePaths(file_or_directoryName))
    return outputFilePaths

def checkOutputFiles(outputFileInfos, jobId, jobIds_force_resubmit):

    #print "<checkOutputFiles>:"
    #print "jobId = %i" % jobId

    outputFileName_regex = 'tree_(?P<jobId>\d+).root'
    outputFileName_matcher = re.compile(outputFileName_regex)

    resubmit_job = False

    outputFileInfos_matched = []
    for outputFileInfo in outputFileInfos:
        outputFileName_match = outputFileName_matcher.match(outputFileInfo['file'])
        if outputFileName_match:
            outputFile_jobId = int(outputFileName_match.group('jobId'))
            if outputFile_jobId == jobId:
                outputFileInfos_matched.append(outputFileInfo)
    #print " found %i copies." % len(outputFileInfos_matched)
    if len(outputFileInfos_matched) == 0:
        resubmit_job = True
    elif len(outputFileInfos_matched) > 1:
        print("Warning: jobId = %i produced multiple output files = %s !!" (jobId, [ outputFileInfo['file'] for outputFileInfo in outputFileInfos_matched ]))
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
                print "--> deleting copy = %s" % outputFileInfo['path'] 
                outputFiles_to_delete.append(outputFileInfo['path'])
        ##for outputFileName in outputFiles_to_delete:
        ##    commandLine = 'rm %s' % outputFileName
        ##    shellScriptCommands.append(commandLine)         

    if resubmit_job:
        print("Info: jobId = %i produced no output file(s) --> resubmitting it" % jobId)
        jobIds_force_resubmit.append(jobId)
    
jobStatus_dict = {}
if os.path.exists(statusFileName):
    if os.path.isfile(statusFileName):
        print("Loading previous status of crab jobs from file '%s'" % statusFileName)
        statusFile = open(statusFileName, "r")
        jobStatus_dict = json.load(statusFile)
        #print(jobStatus_dict)
        statusFile.close()
    else:
        raise ValueError("File '%s' exists, but is a directory !!" % statusFileName)
else:
    print("File '%s' does not yet exist...creating it." % statusFileName)
jobStatus_dict_updated = copy.deepcopy(jobStatus_dict)

key_value_pair_regex   = r'(?P<key>[a-zA-Z0-9_.]+)\s*=\s*(?P<value>.+)\s*'
key_value_pair_matcher = re.compile(key_value_pair_regex)

attribute_requestName = 'config.General.requestName'
attribute_inputFileName = 'config.Data.inputDataset'
attribute_lumiMask = 'config.Data.lumiMask'
attribute_outputFileName = 'config.Data.outputDatasetTag'
attribute_outputFilePath = 'config.Data.outLFNDirBase'
attribute_whitelist = 'config.Site.whitelist'

crabJobSummary_regex = r'\s*Jobs status:\s*[a-zA-Z_]+\s*[0-9.%]+\s*\([0-9]+\s*/\s*(?P<numJobs>[0-9]+)\)\s*'
crabJobSummary_matcher = re.compile(crabJobSummary_regex)
crabJobStatus_header = ' Job State        Most Recent Site        Runtime   Mem (MB)      CPU %    Retries   Restarts      Waste       Exit Code'
crabJobStatus_regex = r'\s*(?P<jobId>[0-9]+)\s+(?P<State>[a-zA-Z_]+)\s+[a-zA-Z0-9_]+\s+[0-9:]+\s+[0-9]+\s+[0-9]+\s+(?P<Retries>[0-9]+)\s+[0-9]+\s+[0-9:]+\s+[a-zA-Z0-9_ ]+\s*'
crabJobStatus_matcher = re.compile(crabJobStatus_regex)

current_time = time.time()
print("current time = %s" % time.asctime(time.gmtime(current_time)))

# CV: define maximum time (default is one day = 24*60*60 seconds) for which crab jobs are allowed to stay in same 'State' and with same number of 'Retries'
#     before they they get automatically resubmitted as a new crab task
time_limit = 60*60*24

checkJobOutputFiles = True
#checkJobOutputFiles = False

shellScriptCommands = []

crabJobs = runCommand('%s %s' % (executable_ls, crabFilePath))
for crabJob in crabJobs:
    crabJob = crabJob.replace('\n', '')
    print("processing Task = '%s'" % crabJob)
    crabJob_match = jobName_matcher.match(crabJob)
    if crabJob_match:
        print("checking directory/file = '%s'" % crabJob)
        crabDir = os.path.join(crabFilePath, crabJob)
        if not os.path.isdir(crabDir):
            print(" not a crab directory --> skipping")
            continue
        
        crabJob = crabJob.replace('\n', '')
        print(" matched.")
        if not jobStatus_dict.has_key(crabJob):
            jobStatus_dict[crabJob] = {}
            
        sample = crabJob_match.group('sample')
        if len(samples) > 0 and not sample in samples:
            print("sample = '%s' not in list of samples = %s --> skipping" % (sample, samples))
            continue
        #print("sample = %s" % sample)

        # unpack tar-ball that contains crab config file
        if not os.path.isdir(os.path.join(crabFilePath, crabJob, "debug")):
            crabConfigFileName_tarball = os.path.join(crabFilePath, crabJob, "inputs/debugFiles.tgz")
            print "unpacking crab config file from tar-ball '%s'" % crabConfigFileName_tarball            
            runCommand("%s -xzvf %s --directory %s" % (executable_tar, crabConfigFileName_tarball, crabDir))

        # run 'crab status' command (abort after 5 minutes = 300 seconds)
        crabStatus_lines = runCommand_via_shell_with_timeout('%s status -d %s --long' % (executable_crab, crabDir), timeout = 300)
        ##crabStatus_lines = []
        ##crabStatus_lines.append("Jobs status:			failed         56.4% (3692/6542)")
        ##crabStatus_lines.append(" Job State        Most Recent Site        Runtime   Mem (MB)      CPU %    Retries   Restarts      Waste       Exit Code")
        ##crabStatus_lines.append("   1 failed       Unknown                 0:00:00          0          0          1          0    0:05:25  Postprocessing failed")
        ##crabStatus_lines.append("   6 finished     T2_PL_Swierk            5:17:50       1832         97          0          0    0:00:00               0")
        ##crabStatus_lines.append("6405 failed       T2_PL_Swierk            4:16:13       1690         99          0          0    0:00:00  Postprocessing failed")
        ##crabStatus_lines.append("6406 failed       T1_UK_RAL               2:40:29       1837         91          0          0    0:00:00  Postprocessing failed")
        if not crabStatus_lines:
            print "Failed to run 'crab -status' command for sample = '%s' --> skipping" % sample
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
            #print "parsing line = '%s'" % crabConfig_line
            key_value_pair_match = key_value_pair_matcher.match(crabConfig_line)
            if key_value_pair_match:
                key = key_value_pair_match.group('key')
                #print("key = %s" % key)
                value = key_value_pair_match.group('value')
                value = value.replace("'", "") # CV: remove apostrophes that enclose strings
                #print("value = %s" % value)
                if key == attribute_requestName:
                    requestName = value
                elif key == attribute_inputFileName:
                    inputFileName = value
                elif key == attribute_lumiMask:
                    lumiMask = value    
                elif key == attribute_outputFileName:
                    outputFileName = value
                elif key == attribute_outputFilePath:
                    outputFilePath = value
                elif key == attribute_whitelist:
                    whitelist = value
        crabConfigFile.close()
        if not (requestName and inputFileName and outputFileName and outputFilePath):
            raise ValueError("Failed to parse crab config file = '%s' !!" % crabConfigFileName)        
        outputFilePath_part1 = outputFilePath_base
        #print "outputFilePath_part1 = '%s'" % outputFilePath_part1
        outputFilePath_part2 = removeLeadingSlash(outputFilePath)
        #print "outputFilePath_part2 = '%s'" % outputFilePath_part2
        pos = inputFileName.find("/")
        if pos == 0:
            pos = inputFileName.find("/", 1)
        if pos == -1:
            raise ValueError("Failed to parse attribute '%s' = '%s' !!" % (attribute_inputFileName, inputFileName))
        outputFilePath_part3 = removeLeadingSlash(inputFileName[:pos])
        #print "outputFilePath_part3 = '%s'" % outputFilePath_part3
        outputFilePath_part4 = removeLeadingSlash(outputFileName)
        #print "outputFilePath_part4 = '%s'" % outputFilePath_part4
        outputFilePath_sample = os.path.join(outputFilePath_part1, outputFilePath_part2, outputFilePath_part3, outputFilePath_part4)
        #print "outputFilePath_sample = '%s'" % outputFilePath_sample
        outputFilePaths_sample = getOutputFilePaths(outputFilePath_sample)
        #print "outputFilePaths_sample = %s" % outputFilePaths_sample

        # read list of files existing in output file path
        if checkJobOutputFiles:
            outputFileInfos = []
            for outputFilePath_sample in outputFilePaths_sample:
                file_or_directoryNames = runCommand('%s %s' % (executable_ls, outputFilePath_sample))
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
        print "outputFileInfos:"
        print [ outputFileInfo['file'] for outputFileInfo in outputFileInfos ]
            
        # parse job status information returned by executing 'crab status' command
        numJobs = None
        foundStart = False
        foundEnd = False
        isCrabFailure = False
        jobStatus_summary = {}
        jobIds_resubmit = []
        jobIds_force_resubmit = []
        for crabStatus_line in crabStatus_lines:
            crabStatus_line = crabStatus_line.replace("\n", "")
            #print "crabStatus_line = '%s'" % crabStatus_line 
            # CV: check if job status cannot be determined,
            #     due to crab internal error
            if isCrabFailure:
                continue    
            if crabStatus_line.find("Traceback (most recent call last):") != -1:
                print("Failed to execute 'crab status' command --> checking output files:")
                for jobId in range(1, numJobs):
                    checkOutputFiles(outputFileInfos, jobId, jobIds_force_resubmit)                            
                    isCrabFailure = True
                crabJobStatus_regex
            crabJobSummary_match = crabJobSummary_matcher.match(crabStatus_line)
            if crabJobSummary_match:
                numJobs = crabJobSummary_match.group('numJobs')
                print "Task = '%s' has %s jobs." % (crabJob, numJobs)
                continue
            if crabStatus_line == crabJobStatus_header:
                foundStart = True
                continue
            if not foundStart or foundEnd:
                continue
            jobId = None
            State = None
            Retries = None            
            crabJobStatus_match = crabJobStatus_matcher.match(crabStatus_line)
            if crabJobStatus_match:
                jobStatus_entry = None
                if not crabJob in jobStatus_dict_updated.keys():
                    jobStatus_dict_updated[crabJob] = {}
                jobId = int(crabJobStatus_match.group('jobId'))
                if not jobId in jobStatus_dict_updated[crabJob]:
                    jobStatus_dict_updated[crabJob][jobId] = {}
                jobStatus_entry = jobStatus_dict_updated[crabJob][jobId] 
                State = crabJobStatus_match.group('State')
                jobStatus_entry['State'] = State
                if not State in jobStatus_summary.keys():
                    jobStatus_summary[State] = 0
                jobStatus_summary[State] = jobStatus_summary[State] + 1
                Retries = int(crabJobStatus_match.group('Retries'))
                jobStatus_entry['Retries'] = Retries
            else:
                foundEnd = True
            if jobId and State and Retries is not None:
                print "jobId = %i: State = '%s', Retries = %i" % (jobId, State, Retries)
                if State in [ "finished" ] or force_resubmit:
                    checkOutputFiles(outputFileInfos, jobId, jobIds_force_resubmit)    
                elif State in [ "failed", "transferring" ]:
                    # CV: check if job remained in this state for more than one day;
                    #     if so, assume that crab job got "stuck" and create a new crab task with this job
                    if crabJob in jobStatus_dict.keys() and jobId in jobStatus_dict[crabJob].keys():
                        if Retries == jobStatus_dict[crabJob][jobId]['Retries'] and (current_time - jobStatus_dict[crabJob]['lastUpdate']) > time_limit:
                            print("Info: jobId = %i got stuck in state '%s' --> creating a new crab task with this job !!" % (jobId, State))
                            jobIds_force_resubmit.append(jobId)
                    elif State in [ "failed" ]:
                        print("Info: jobId = %i failed --> resubmitting it" % jobId)
                        jobIds_resubmit.append(jobId)

        print "Job summary:"
        for jobStatus, numJobs_status in jobStatus_summary.items():
            print " %i Jobs in status = '%s'" % (numJobs_status, jobStatus)

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
                print "firstJob = %i" % firstJob
                lastJob = (jobIndex + 1)*numJobsPerResubmit - 1
                print "lastJob = %i" % lastJob
                jobIds_resubmit_string = ",".join([ "%i" % jobId for jobId in jobIds_resubmit_unique[firstJob:lastJob] ])
                print "jobIds_resubmit_string = '%s'" % jobIds_resubmit_string
                commandLine = '%s resubmit -d %s --jobids %s' % (executable_crab, crabDir, jobIds_resubmit_string)
                print "commandLine = '%s'" % commandLine
                runCommand_via_shell(commandLine)

        # create new crab task with jobs that remained in 'failed' or 'transferring' state for more than one day
        print("jobIds_force_resubmit = %s" % jobIds_force_resubmit_unique)
        print("(%i jobs)" % len(jobIds_force_resubmit_unique))
        if len(jobIds_force_resubmit_unique) > 0:
            crabReportFileName = os.path.join(crabDir, "results/notFinishedLumis.json")
            if not os.path.isfile(crabReportFileName):
                commandLine = '%s report -d %s' % (executable_crab, crabDir)
                runCommand_via_shell(commandLine)
            if not 'forceResubmissions' in jobStatus_dict_updated[crabJob].keys():
                jobStatus_dict_updated[crabJob]['forceResubmissions'] = 1
            jobStatus_dict_updated[crabJob]['forceResubmissions'] = jobStatus_dict_updated[crabJob]['forceResubmissions'] + 1
            # write new crab config file
            crabConfigFileName_new = os.path.join(crabFilePath, 'crabConfig_%s_forceResubmit%i.py' % (crabJob, jobStatus_dict_updated[crabJob]['forceResubmissions']))
            crabConfigFile_new = open(crabConfigFileName_new, "w")
            value_lumiMask = "'%s'" % crabReportFileName
            print "value_lumiMask = %s" % value_lumiMask
            isSet_lumiMask = False
            value_whitelist = "%s" % whitelist_when_force_resubmit
            print "value_whitelist = %s" % value_whitelist
            isSet_whitelist = False
            for crabConfig_line in crabConfig_lines:
                key_value_pair_match = key_value_pair_matcher.match(crabConfig_line)                                
                crabConfig_line_new = crabConfig_line
                if key_value_pair_match:
                    key = key_value_pair_match.group('key')
                    value = key_value_pair_match.group('value')
                    if key == attribute_requestName:
                        value = "'%s_forceResubmit%i'" % (value.replace("'", ""), jobStatus_dict_updated[crabJob]['forceResubmissions'])                        
                    elif key == attribute_lumiMask:
                        value = value_lumiMask
                        isSet_lumiMask = True
                    elif key == attribute_outputFileName:
                        value = "'%s_forceResubmit%i'" % (value.replace("'", ""), jobStatus_dict_updated[crabJob]['forceResubmissions'])
                    elif key == attribute_whitelist:
                        if whitelist_when_force_resubmit:
                            value = value_whitelist
                        isSet_whitelist = True                    
                    crabConfig_line_new = "%s = %s\n" % (key, value)
                crabConfigFile_new.write(crabConfig_line_new)
            if not isSet_lumiMask:
                crabConfig_line_new = "%s = %s\n" % (attribute_lumiMask, value_lumiMask)
                crabConfigFile_new.write(crabConfig_line_new)
            if not isSet_whitelist and whitelist_when_force_resubmit:
                crabConfig_line_new = "%s = %s\n" % (attribute_whitelist, value_whitelist)
                crabConfigFile_new.write(crabConfig_line_new)
            crabConfigFile_new.close()
            commandLine = '%s submit -c %s' % (executable_crab, crabConfigFileName_new)
            print "commandLine = '%s'" % commandLine
            runCommand_via_shell(commandLine)

        print("")

#print(jobStatus_dict_updated)

statusFile = open(statusFileName, "w")
json.dump(jobStatus_dict_updated, statusFile)
statusFile.close()

os.chdir(currentDir)

print("Finished running 'crabSitter.py'.")
