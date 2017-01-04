import codecs
import os
import logging
import ROOT
import array
import sys
import getpass

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd as tools_createScript_sbatch_hadd

DKEY_CFGS          = "cfgs"
DKEY_NTUPLES       = "ntuples"
DKEY_FINAL_NTUPLES = "final_ntuples"
DKEY_LOGS          = "logs"
DKEY_HADD          = "hadd_cfg"

executable_rm = 'rm'

class addMEMConfig_2lss_1tau:
    """Configuration metadata needed to run MEM for 2lss_1tau channel.

    Args:
        outputDir: The root output dir -- all configuration, log and output files are stored in its subdirectories
        executable_addMEM: Name of the executable that runs the MEM computation; expected value is `executable_addMEM`
        debug: if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method: either `sbatch` (uses SLURM) or `Makefile`
        mem_integrations_per_job: (max) number of MEM integrations performed in one job
        num_parallel_jobs: number of jobs that can be run in parallel on local machine
                           (does not limit number of MEM jobs running in parallel on batch system)

    """
    def __init__(self, treeName, outputDir, executable_addMEM, samples, era, debug, running_method,
                 max_files_per_job, mem_integrations_per_job, max_mem_integrations, num_parallel_jobs):

        self.treeName = treeName
        self.outputDir = outputDir
        self.executable_addMEM = executable_addMEM
        self.channel = "2lss_1tau"
        self.mem_integrations_per_job = mem_integrations_per_job
        self.max_files_per_job = max_files_per_job
        self.max_mem_integrations = max_mem_integrations
        self.samples = samples
        self.era = era
        self.debug = debug
        assert(running_method.lower() in [
          "sbatch", "makefile"]), "Invalid running method: %s" % running_method
        self.running_method = running_method
        self.is_sbatch = False
        self.is_makefile = False
        if self.running_method.lower() == "sbatch":
            self.is_sbatch = True
        else:
            self.is_makefile = True
        self.makefile = os.path.join(
          self.outputDir, "Makefile_%s" % self.channel)
        self.num_parallel_jobs = num_parallel_jobs

        self.workingDir = os.getcwd()
        print "Working directory is: " + self.workingDir

        create_if_not_exists(self.outputDir)
        self.stdout_file = codecs.open(os.path.join(
          self.outputDir, "stdout_%s.log" % self.channel), 'w', 'utf-8')
        self.stderr_file = codecs.open(os.path.join(
          self.outputDir, "stderr_%s.log" % self.channel), 'w', 'utf-8')
        self.dirs = {}
        self.samples = samples
        self.cfgFile_addMEM_original = os.path.join(self.workingDir, "addMEM_2lss_1tau_cfg.py")
        self.cfgFiles_addMEM_modified = {}
        self.logFiles_addMEM = {}
        self.sbatchFile_addMEM = os.path.join(
          self.outputDir, "sbatch_addMEM_%s.py" % self.channel)
        self.inputFiles = {}
        self.outputFiles = {}
        self.hadd_records = {}
        self.filesToClean = []

        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"] or \
                sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in [ DKEY_CFGS, DKEY_NTUPLES, DKEY_FINAL_NTUPLES, DKEY_LOGS, DKEY_HADD ]:
                initDict(self.dirs, [ key_dir, dir_type ])
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)

        self.cvmfs_error_log = {}

    def createCfg_addMEM(self, inputFiles, startRange, endRange, outputFile, era, cfgFile_modified):
        """Create python configuration file for the addMEM_2lss_1tau executable (MEM code)

        Args:
          inputFile: list of input files (Ntuples)
          outputFile: output file of the job
        """

        '''Let's assume that the following configuration options remain constant at all times and need not be modified
        - process.fwliteInput.outputEvery
        - process.addMEM_2lss_1tau.branchName_electrons
        - process.addMEM_2lss_1tau.branchName_muons
        - process.addMEM_2lss_1tau.branchName_hadTaus
        - process.addMEM_2lss_1tau.branchName_jets
        - process.addMEM_2lss_1tau.branchName_met
        - process.addMEM_2lss_1tau.leptonSelection
        - process.addMEM_2lss_1tau.hadTauSelection
        - process.addMEM_2lss_1tau.use_HIP_mitigation_bTag
        '''

        lines = []
        skipEvents = startRange
        maxEvents = endRange - startRange
        lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
        lines.append("process.fwliteInput.skipEvents = cms.uint32(%s)" % skipEvents)
        lines.append("process.fwliteInput.maxEvents = cms.int32(%s)" % maxEvents)
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
        lines.append("process.addMEM_2lss_1tau.era = cms.string('%s')" % era)
        if skipEvents > 0:
            lines.append("process.addMEM_2lss_1tau.copy_histograms = cms.vstring()")

        create_cfg(self.cfgFile_addMEM_original, cfgFile_modified, lines)

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the MEM jobs to the batch system
        """
        tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile_addMEM,
            executable = self.executable_addMEM,
            cfg_file_names = self.cfgFiles_addMEM_modified,
            input_file_names = self.inputFiles,
            output_file_names = self.outputFiles,
            log_file_names = self.logFiles_addMEM,
            working_dir = self.workingDir,
            max_num_jobs = 100000,
            cvmfs_error_log = self.cvmfs_error_log,
        )

    def addToMakefile_addMEM(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the MEM code
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch:")
            lines_makefile.append("\t%s %s" % (
                "python", self.sbatchFile_addMEM))
            lines_makefile.append("")
        for key_file, output_file in self.outputFiles.items():
            cfg_file_addMEM_modified = self.cfgFiles_addMEM_modified[key_file]
            if self.is_makefile:
                lines_makefile.append("%s:" % output_file)
                cfg_file = cfg_file_addMEM_modified
                log_file = self.logFiles_addMEM[key_file]
                lines_makefile.append("\t%s %s &> %s" % (
                  self.executable_addMEM, cfg_file, log_file))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (output_file, "sbatch"))
                lines_makefile.append("\t%s" % ":")  # CV: null command
                lines_makefile.append("")
            #self.filesToClean.append(output_file)

    def addToMakefile_hadd(self, lines_makefile):
        """Add hadd targets to the Makefile
        """
        for hadd_out, hadd_in in self.hadd_records.iteritems():
            hadd_in_files = hadd_in['output_files']
            hadd_fileset_id = hadd_in['fileset_id']
            sbatch_hadd_file = os.path.join(
                self.outputDir, DKEY_HADD, "sbatch_hadd_%s_%s_%d.py" % (self.channel, 'cat', hadd_fileset_id)
            )
            tools_createScript_sbatch_hadd(sbatch_hadd_file, hadd_in_files, hadd_out, 'cat', self.workingDir, False)

            lines_makefile.append("%s: %s" % (hadd_out, " ".join(hadd_in_files)))
            lines_makefile.append("\t%s %s" % ("rm -f", hadd_out))
            lines_makefile.append("\t%s %s" % ("python", sbatch_hadd_file))
            lines_makefile.append("")
            #self.filesToClean.append(hadd_out)

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the MEM
        """
        targets = self.hadd_records.keys()
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean)
        logging.info("Run it with:\tmake -f %s -j %i " %
            (self.makefile, self.num_parallel_jobs))

    def memJobList(self, inputFileList):
        '''
        Args:
          inputFileList:{ int, array of strings }; i.e. fileset* ID and the list of files

        * if the script were to generate configuration files, this number would correspond to job ID

        Returns:
          { int : { str : int, str : [str, str, ...], str : [int, int] } }
            |        |          |                      |
         job id  "fileset_id" "input_fileset"     "event_range"

        The function reads a given set of files and determines the event range
        '''
        memJobDict = {}
        jobId = 0
        for filesetId, inputFileSet in inputFileList.iteritems():
            memJobDict_common = { 'fileset_id' : filesetId, 'input_fileset' : inputFileSet }
            ch = ROOT.TChain(self.treeName)
            for fn in inputFileSet:
                # chaining a file
                ch.AddFile(fn)

            nof_entries = ch.GetEntries()
            memJobDict_common['nof_entries'] = nof_entries
            current_pos = 0
            evt_ranges = []

            counter, counter_arr = 0, []
            nof_events_pass_counter, nof_events_pass = 0, []
            nof_int_pass_counter,    nof_int_pass    = 0, []
            nof_zero_integrations,   nof_events_zero = 0, []

            maxPermutations_addMEM_2lss_1tau_a = array.array('i', [0])
            ch.SetBranchAddress("maxPermutations_addMEM_2lss_1tau", maxPermutations_addMEM_2lss_1tau_a)

            for i in range(nof_entries):
                ch.GetEntry(i)

                nof_integrations = maxPermutations_addMEM_2lss_1tau_a[0]
                if nof_integrations < 0:
                    nof_integrations = 0

                if nof_integrations >= 1:
                    nof_events_pass_counter += 1
                    nof_int_pass_counter += nof_integrations
                else:
                    nof_zero_integrations += 1

                if nof_integrations > self.mem_integrations_per_job:
                    raise ValueError("Too many nof_integrations = %d in file(s) %s at %d:%d:%d" %
                                     (nof_integrations, ', '.join(inputFileSet), ch.run, ch.lumi, ch.evt))

                if (counter + nof_integrations) > self.mem_integrations_per_job:
                    if evt_ranges:
                        evt_ranges.append([evt_ranges[-1][1], current_pos])
                    else:
                        evt_ranges.append([0, current_pos])
                    counter_arr.append(counter)
                    counter = 0

                    nof_events_pass.append(nof_events_pass_counter)
                    nof_events_pass_counter = 0

                    nof_int_pass.append(nof_int_pass_counter)
                    nof_int_pass_counter = 0

                    nof_events_zero.append(nof_zero_integrations)
                    nof_zero_integrations = 0
                counter += nof_integrations
                current_pos += 1

            if counter <= self.mem_integrations_per_job and counter > 0:
                if evt_ranges:
                    evt_ranges.append([evt_ranges[-1][1], int(nof_entries)])
                else:
                    evt_ranges.append([0, int(nof_entries)])
                counter_arr.append(counter)
                nof_events_pass.append(nof_events_pass_counter)
                nof_int_pass.append(nof_int_pass_counter)
                nof_events_zero.append(nof_zero_integrations)

            for i in range(len(evt_ranges)):
                jobId += 1
                memJobDict[jobId] = dict({
                    'event_range'     : evt_ranges[i],
                    'nof_int'         : counter_arr[i],
                    'nof_int_pass'    : nof_int_pass[i],
                    'nof_events_pass' : nof_events_pass[i],
                    'nof_zero'        : nof_events_zero[i],
                }, **memJobDict_common)
                # we now have all event ranges per one file, let's add them to the dictionary

        return memJobDict

    def create(self):
        """Creates all necessary config files and runs the MEM -- either locally or on the batch system
        """
        statistics = {}

        for key in self.dirs.keys():
            if type(self.dirs[key]) == dict:
                for dir_type in self.dirs[key].keys():
                    create_if_not_exists(self.dirs[key][dir_type])
            else:
                create_if_not_exists(self.dirs[key])

        # read the file in, sample-by-sample
        # build the dictionary recursively
        # add rle file also to generated cfg files
        # print integrations per job as well!
        # consider more than 1 file per jobs -- the jobs are splitted by MEM integration anyways

        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"] or \
              sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
                continue

            if not os.path.exists(sample_info['local_paths'][0]['path']):
                logging.warning("Skipping sample {sample_name}".format(sample_name = sample_name))
                continue

            process_name = sample_info["process_name_specific"]
            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_addMEM, process_name))

            inputFileList = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
            # typically, the analysis ends here and starts looping b/c the smallest unit of work processes
            # at least one file; we need, however, to split the file into event ranges in such a way that
            # each job performs mem_integrations_per_job MEM integrations

            # so what we are going to do is to open each set of files in inputFileList, read the variable
            # requestMEM_2lss_1tau and try to gather the event ranges such that each event range
            # performs up to mem_integrations_per_job integrations per job
            memEvtRangeDict = self.memJobList(inputFileList)

            for jobId in memEvtRangeDict.keys():

                key_dir = getKey(sample_name)
                key_file = getKey(sample_name, jobId)

                self.inputFiles[key_file] = memEvtRangeDict[jobId]['input_fileset']

                # there should always be a job
                assert(self.inputFiles[key_file] > 0), "More than one input file: %s ?? !!" % \
                                                       ', '.join(self.inputFiles[key_file])

                #assert(len(self.inputFiles[key_file]) == 1), "There is more than one input file!"
                self.cfgFiles_addMEM_modified[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_CFGS], "addMEM_%s_%s_%i_cfg.py" % (self.channel, process_name, jobId)
                )
                self.outputFiles[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_NTUPLES], "%s_%i.root" % (process_name, jobId)
                )
                self.logFiles_addMEM[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_LOGS], "addMEM_%s_%s_%i.log" % (self.channel, process_name, jobId)
                )
                self.createCfg_addMEM(
                    self.inputFiles[key_file],
                    memEvtRangeDict[jobId]['event_range'][0],
                    memEvtRangeDict[jobId]['event_range'][1],
                    self.outputFiles[key_file],
                    self.era,
                    self.cfgFiles_addMEM_modified[key_file],
                )

                # associate the output file with the fileset_id
                #UDPATE: ONE OUTPUT FILE PER SAMPLE!
                fileset_id = memEvtRangeDict[jobId]['fileset_id']
                hadd_output = os.path.join(
                    #self.dirs[key_dir][DKEY_FINAL_NTUPLES], '%s_%i.root' % ('tree', fileset_id) # UDPATE: REMOVED
                    self.dirs[key_dir][DKEY_FINAL_NTUPLES], "tree.root" # UDPATE: ADDED
                )
                if hadd_output not in self.hadd_records:
                    self.hadd_records[hadd_output] = {}
                    self.hadd_records[hadd_output]['output_files'] = []
                self.hadd_records[hadd_output]['fileset_id'] = fileset_id
                self.hadd_records[hadd_output]['output_files'].append(self.outputFiles[key_file])
                #self.filesToClean.append(self.outputFiles[key_file])

            # let's sum the number of integration per sample
            nofEntriesMap = {}
            for v in memEvtRangeDict.values():
                if v['fileset_id'] not in nofEntriesMap:
                    nofEntriesMap[v['fileset_id']] = {
                        'nof_entries' : v['nof_entries'],
                    }
            statistics[process_name] = {
                'nof_int'         : sum([entry['nof_int']         for entry in memEvtRangeDict.values()]),
                'nof_entries'     : sum([entry['nof_entries']     for entry in nofEntriesMap.values()]),
                'nof_events_pass' : sum([entry['nof_events_pass'] for entry in memEvtRangeDict.values()]),
                'nof_int_pass'    : sum([entry['nof_int_pass']    for entry in memEvtRangeDict.values()]),
                'nof_zero'        : sum([entry['nof_zero']        for entry in memEvtRangeDict.values()]),
                'nof_jobs'        : len(memEvtRangeDict),
            }

        if self.is_sbatch:
            logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addMEM)
            self.createScript_sbatch()

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile_addMEM(lines_makefile)
        self.addToMakefile_hadd(lines_makefile)
        self.createMakefile(lines_makefile)

        ws_len = max([len(kk) + 1 for kk in statistics.keys()])
        total_nof_integrations_sum = sum(x['nof_int']            for x in statistics.values())
        total_nof_entires          = sum(x['nof_entries']        for x in statistics.values())
        total_nof_zero_int         = sum(x['nof_zero']           for x in statistics.values())
        total_nof_jobs             = sum(x['nof_jobs']           for x in statistics.values())
        total_nof_pass             = sum(x['nof_events_pass']    for x in statistics.values())
        total_nof_int_pass_avg     = float(sum(x['nof_int_pass'] for x in statistics.values())) / total_nof_pass
        total_nof_integrations_avg = float(total_nof_integrations_sum) / total_nof_entires
        total_nof_int_per_job = float(total_nof_integrations_sum) / total_nof_jobs
        for k, v in statistics.iteritems():
            print('%s%s: %d (%d entries; %d jobs; %.2f int/evt; %d (%.2f%%) evt pass; %.2f int/evt pass; %d evt 0int)' %
              (k,
               ' ' * (ws_len - len(k)),
               v['nof_int'],
               v['nof_entries'],
               v['nof_jobs'],
               float(v['nof_int']) / v['nof_entries'],
               v['nof_events_pass'],
               (100 * float(v['nof_events_pass']) / v['nof_entries']),
               float(v['nof_int_pass']) / v['nof_events_pass'],
               v['nof_zero'],
              )
            )
        print('%s%s: %d (%d entries; %d jobs; %.2f int/evt; %d evt pass; %.2f int/evt pass; '
              '%.2f int/job pass; %d evt 0int)' %
          ('total',
           ' ' * (ws_len - len('total')),
           total_nof_integrations_sum,
           total_nof_entires,
           total_nof_jobs,
           total_nof_integrations_avg,
           total_nof_pass,
           total_nof_int_pass_avg,
           total_nof_int_per_job,
           total_nof_zero_int,
          )
        )

        if self.max_mem_integrations > 0 and total_nof_integrations_sum > self.max_mem_integrations:
            logging.error("Will not start the jobs (max nof integrations exceeded)!")
            return False
        else:
            logging.info("Done")
            return True

    def run(self):
        """Runs all Ntuple addMEM jobs -- either locally or on the batch system.
        """
        run_cmd("make -f %s -j %i " % (self.makefile, self.num_parallel_jobs),
                False, self.stdout_file, self.stderr_file)
