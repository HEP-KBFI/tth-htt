from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version, record_software_state
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd as tools_createScript_sbatch_hadd
from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging

import os
import array
import uuid

DEPENDENCIES = [
    "",  # CMSSW_BASE/src
    "tthAnalysis/HiggsToTauTau",
    "TauAnalysis/ClassicSVfit",
    "TauAnalysis/SVfitTF",
    "ttH_Htautau_MEM_Analysis",
    "tthAnalysis/tthMEM",
]

DKEY_CFGS          = "cfgs"
DKEY_NTUPLES       = "ntuples"
DKEY_FINAL_NTUPLES = "final_ntuples"
DKEY_LOGS          = "logs"
DKEY_HADD          = "hadd_cfg"
DKEY_HADD_RT       = "hadd_cfg_rt"

class addMEMConfig:
    """Configuration metadata needed to run MEM for any channel.

    Args:
        outputDir: The root output dir -- all configuration, log and output files are stored in its subdirectories
        executable_addMEM: Name of the executable that runs the MEM computation; expected value is `executable_addMEM`
        debug: if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method: either `sbatch` (uses SLURM) or `Makefile`
        mem_integrations_per_job: (max) number of MEM integrations performed in one job
        num_parallel_jobs: number of jobs that can be run in parallel on local machine
                           (does not limit number of MEM jobs running in parallel on batch system)

    """
    def __init__(self,
            treeName,
            outputDir,
            cfgDir,
            executable_addMEM,
            samples,
            era,
            check_output_files,
            running_method,
            max_files_per_job,
            mem_integrations_per_job,
            max_mem_integrations,
            num_parallel_jobs,
            leptonSelection,
            hadTauSelection,
            integration_choice,
            jet_cleaning_by_index,
            dry_run,
            use_nonnominal,
            use_home,
            channel,
            rle_filter_file = '',
            pool_id = '',
            max_jobs_per_sample = -1 
          ):

        self.treeName = treeName
        self.outputDir = outputDir
        self.cfgDir = cfgDir
        self.executable_addMEM = executable_addMEM
        self.mem_integrations_per_job = mem_integrations_per_job
        self.max_files_per_job = max_files_per_job
        self.max_mem_integrations = max_mem_integrations
        self.max_jobs_per_sample = max_jobs_per_sample
        self.samples = samples
        self.era = era
        self.check_output_files = check_output_files
        self.channel = channel
        self.rle_filter_file = rle_filter_file
        self.leptonSelection = leptonSelection
        self.hadTauSelection = hadTauSelection
        if self.hadTauSelection:
            self.hadTauDefinition = self.hadTauSelection.split('|')[0]
            self.hadTauWorkingPoint = self.hadTauSelection.split('|')[1]
        else:
            self.hadTauDefinition = None
            self.hadTauWorkingPoint = None
        self.maxPermutations_branchName = None
        self.integration_choice = integration_choice
        self.jet_cleaning_by_index = jet_cleaning_by_index
        logging.info(
            "Number of integration points: %s" % self.integration_choice
        )
        if running_method.lower() not in ["sbatch", "makefile"]:
            raise ValueError("Invalid running method: %s" % running_method)
        self.running_method = running_method
        self.is_sbatch = False
        self.is_makefile = False
        if self.running_method.lower() == "sbatch":
            self.is_sbatch = True
        else:
            self.is_makefile = True
        self.makefile = os.path.join(
          self.cfgDir, "Makefile_%s" % self.channel)
        self.num_parallel_jobs = num_parallel_jobs
        self.dry_run = dry_run
        self.use_nonnominal = use_nonnominal
        self.use_home = use_home
        self.pool_id = pool_id if pool_id else uuid.uuid4()

        self.workingDir = os.getcwd()
        logging.info("Working directory is: {workingDir}".format(workingDir = self.workingDir))

        for dirPath in [self.outputDir, self.cfgDir]:
          create_if_not_exists(dirPath)

        self.stdout_file_path = os.path.join(self.cfgDir, "stdout_%s.log" % self.channel)
        self.stderr_file_path = os.path.join(self.cfgDir, "stderr_%s.log" % self.channel)
        self.sw_ver_file_cfg  = os.path.join(self.cfgDir, "VERSION_%s.log" % self.channel)
        self.sw_ver_file_out  = os.path.join(self.outputDir, "VERSION_%s.log" % self.channel)
        self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out = get_log_version((
            self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out
        ))

        self.dirs = {}
        self.samples = samples
        self.cfgFiles_addMEM_modified = {}
        self.shFiles_addMEM_modified = {}
        self.logFiles_addMEM = {}
        self.sbatchFile_addMEM = os.path.join(self.cfgDir, "sbatch_addMEM_%s.py" % self.channel)
        self.inputFiles = {}
        self.outputFiles = {}
        self.hadd_records = {}
        self.filesToClean = []

        del self.samples['sum_events']
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in [DKEY_NTUPLES, DKEY_FINAL_NTUPLES]:
                initDict(self.dirs, [key_dir, dir_type])
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
            for dir_type in [DKEY_CFGS, DKEY_LOGS, DKEY_HADD, DKEY_HADD_RT]:
                initDict(self.dirs, [key_dir, dir_type])
                self.dirs[key_dir][dir_type] = os.path.join(self.cfgDir, dir_type, self.channel, process_name)

        self.cvmfs_error_log = {}

    def createCfg_addMEM(self, inputFiles, startRange, endRange, outputFile, era, isMC, cfgFile_modified, whitelist = []):
        raise ValueError(
            "Function 'createCfg_addMEM' not implemented in derrived class !!")

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the MEM jobs to the batch system
        """
        tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile_addMEM,
            executable              = self.executable_addMEM,
            command_line_parameters = self.cfgFiles_addMEM_modified,
            input_file_names        = self.inputFiles,
            output_file_names       = self.outputFiles,
            script_file_names       = self.shFiles_addMEM_modified,
            log_file_names          = self.logFiles_addMEM,
            working_dir             = self.workingDir,
            max_num_jobs            = 100000000, # it's really silly to limit the number of jobs; use an enormous number as the ,,fix''
            cvmfs_error_log         = self.cvmfs_error_log,
            pool_id                 = self.pool_id,
            use_home                = self.use_home,
            validate_outputs        = self.check_output_files,
            max_num_submittedJobs   = 2000,
        )

    def addToMakefile_addMEM(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the MEM code
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch_addMEM:")
            lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_addMEM))
            lines_makefile.append("")
        for key_file, output_file in self.outputFiles.items():
            cfg_file_addMEM_modified = self.cfgFiles_addMEM_modified[key_file]
            if self.is_makefile:
                lines_makefile.append("%s:" % output_file)
                cfg_file = cfg_file_addMEM_modified
                log_file = self.logFiles_addMEM[key_file]
                lines_makefile.append("\t%s %s &> %s" % (self.executable_addMEM, cfg_file, log_file))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (output_file, "sbatch_addMEM"))
                lines_makefile.append("\t%s" % ":")  # CV: null command
                lines_makefile.append("")
            #self.filesToClean.append(output_file)

    def addToMakefile_hadd(self, lines_makefile):
        """Add hadd targets to the Makefile
        """
        for hadd_out, hadd_in in self.hadd_records.iteritems():
            hadd_in_files = hadd_in['output_files']
            hadd_fileset_id = hadd_in['fileset_id']
            process_name = hadd_in['process_name']
            sbatch_hadd_file = os.path.join(
                self.cfgDir, DKEY_HADD, self.channel, process_name,
                "sbatch_hadd_cat_%s_%d.py" % (process_name, hadd_fileset_id)
            )
            sbatch_hadd_shFile = os.path.join(
                self.cfgDir, DKEY_HADD, self.channel, process_name,
                "sbatch_hadd_cat_%s_%d.sh" % (process_name, hadd_fileset_id)
            )
            sbatch_hadd_logFile = os.path.join(
                self.cfgDir, DKEY_HADD, self.channel, process_name,
                "sbatch_hadd_cat_%s_%d.log" % (process_name, hadd_fileset_id)
            )
            sbatch_hadd_dir = os.path.join(
                self.cfgDir, DKEY_HADD_RT, self.channel, process_name,
            )
            sbatch_hadd_logFile = get_log_version((sbatch_hadd_logFile,))
            tools_createScript_sbatch_hadd(
                sbatch_script_file_name = sbatch_hadd_file,
                input_file_names        = hadd_in_files,
                output_file_name        = hadd_out,
                script_file_name        = sbatch_hadd_shFile,
                log_file_name           = sbatch_hadd_logFile[0],
                working_dir             = self.workingDir,
                waitForJobs             = False,
                auxDirName              = sbatch_hadd_dir,
                pool_id                 = self.pool_id,
                use_home                = self.use_home,
            )

            lines_makefile.append("%s: %s" % (hadd_out, " ".join(hadd_in_files)))
            lines_makefile.append("\t%s %s" % ("rm -f", hadd_out))
            lines_makefile.append("\t%s %s" % ("python", sbatch_hadd_file))
            lines_makefile.append("")
            #self.filesToClean.append(hadd_out)

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the MEM
        """
        targets = self.hadd_records.keys()
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean, self.is_sbatch)
        logging.info("Run it with:\tmake -f %s -j %i " % (self.makefile, self.num_parallel_jobs))

    def memJobList(self, inputFileList, rle_whitelist):
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
        apply_rle_filter = bool(self.rle_filter_file)
        for filesetId, inputFileSet in inputFileList.iteritems():
            memJobDict_common = { 'fileset_id' : filesetId, 'input_fileset' : inputFileSet }
            print("Processing file %s" % inputFileSet)
            ch = ROOT.TChain(self.treeName)
            for fn in inputFileSet:
                # chaining a file
                logging.debug("Processing file {fileName}".format(fileName = fn))
                ch.AddFile(fn)

            nof_entries = ch.GetEntries()

            memJobDict_common['nof_entries'] = nof_entries
            if nof_entries == 0:
                jobId += 1
                memJobDict[jobId] = dict({
                    'event_range'     : [0, 0],
                    'nof_int'         : 0,
                    'nof_int_pass'    : 0,
                    'nof_events_pass' : 0,
                    'nof_zero'        : 0,
                }, **memJobDict_common)
                continue

            current_pos = 0
            evt_ranges = []

            counter, counter_arr = 0, []
            nof_events_pass_counter, nof_events_pass   = 0, []
            nof_int_pass_counter,    nof_int_pass      = 0, []
            nof_zero_integrations,   nof_events_zero   = 0, []
            whitelist_all,           whitelist_running = [], []

            run                    = array.array('I', [0])
            luminosityBlock        = array.array('I', [0])
            event                  = array.array('L', [0])
            maxPermutations_addMEM = array.array('i', [0])
            ch.SetBranchAddress("run",             run)
            ch.SetBranchAddress("luminosityBlock", luminosityBlock)
            ch.SetBranchAddress("event",           event)
            if self.maxPermutations_branchName is not None and self.maxPermutations_branchName != "":
              ch.SetBranchAddress(self.maxPermutations_branchName, maxPermutations_addMEM)
            else:
              maxPermutations_addMEM[0] = 1

            for i in range(nof_entries):
                ch.GetEntry(i)
                if i > 0 and i % 10000 == 0:
	            print(" Processing event %i/%i" % (i, nof_entries))
                    logging.debug("Processing event %i/%i" % (i, nof_entries))

                rle = ':'.join(map(lambda nr: str(nr[0]), [ run, luminosityBlock, event ]))

                nof_integrations = maxPermutations_addMEM[0]
                if apply_rle_filter:
                    if rle in rle_whitelist:
                        if not (nof_integrations > 0):
                            logging.error("Expected non-zero # integrations in event {}, but got {}".format(rle, nof_integrations))
                        nof_integrations = 1
                    else:
                        nof_integrations = 0

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

                    if apply_rle_filter:
                        whitelist_all.append(whitelist_running)
                        whitelist_running = []

                if rle in rle_whitelist:
                    whitelist_running.append(rle)

                counter += nof_integrations
                current_pos += 1

            if counter <= self.mem_integrations_per_job and counter >= 0:
                if evt_ranges:
                    evt_ranges.append([evt_ranges[-1][1], int(nof_entries)])
                else:
                    evt_ranges.append([0, int(nof_entries)])
                counter_arr.append(counter)
                nof_events_pass.append(nof_events_pass_counter)
                nof_int_pass.append(nof_int_pass_counter)
                nof_events_zero.append(nof_zero_integrations)
                if apply_rle_filter:
                    whitelist_all.append(whitelist_running)

            # ensure that the event ranges won't overlap (i.e. there won't be any double-processing of any event)
            evt_ranges_cat = []
            for v in [range(x[0], x[1]) for x in evt_ranges]:
              evt_ranges_cat += v
            assert(evt_ranges_cat == range(nof_entries))
            assert(bool(evt_ranges))

            for i in range(len(evt_ranges)):
              if self.max_jobs_per_sample == -1 or jobId < self.max_jobs_per_sample:
                jobId += 1
                memJobDict[jobId] = dict({
                    'event_range'     : evt_ranges[i],
                    'nof_int'         : counter_arr[i],
                    'nof_int_pass'    : nof_int_pass[i],
                    'nof_events_pass' : nof_events_pass[i],
                    'nof_zero'        : nof_events_zero[i],
                    'whitelist'       : whitelist_all[i] if apply_rle_filter else [],
                }, **memJobDict_common)
                # we now have all event ranges per one file, let's add them to the dictionary

            del ch
        return memJobDict

    def get_filter(self):
        rle_filter_file = ROOT.TFile.Open(self.rle_filter_file, 'read')
        channel_dir = rle_filter_file.Get(self.channel)
        sample_names = [ key.GetName() for key in channel_dir.GetListOfKeys() ]
        rle_map = {}
        for sample_name in sample_names:
            rle_map[sample_name] = []
            sample_tree = channel_dir.Get(sample_name)
            run             = array.array('I', [0])
            luminosityBlock = array.array('I', [0])
            event           = array.array('L', [0])
            sample_tree.SetBranchAddress("run",             run)
            sample_tree.SetBranchAddress("luminosityBlock", luminosityBlock)
            sample_tree.SetBranchAddress("event",           event)
            nof_entries = sample_tree.GetEntries()
            for entry_idx in range(nof_entries):
                sample_tree.GetEntry(entry_idx)
                rle = ':'.join(map(lambda nr: str(nr[0]), [ run, luminosityBlock, event ]))
                assert(rle not in rle_map[sample_name])
                rle_map[sample_name].append(rle)
        rle_filter_file.Close()
        rle_map_keys = set(rle_map.keys())
        sample_keys = set(
            sample_info["process_name_specific"] for sample_key, sample_info in self.samples.items() if sample_info["use_it"]
        )
        rle_map_keys_missing = list(sorted(sample_keys - rle_map_keys))
        if rle_map_keys_missing:
            raise RuntimeError(
                "Missing samples from file %s: %s" % (self.rle_filter_file, ', '.join(rle_map_keys_missing))
            )
        sample_keys_missing = list(sorted(rle_map_keys - sample_keys))
        if sample_keys_missing:
            raise RuntimeError(
                "Found samples in file %s that are disabled in the workflow: %s" % \
                (self.rle_filter_file, ', '.join(sample_keys_missing))
            )
        return rle_map

    def create(self):
        """Creates all necessary config files and runs the MEM -- either locally or on the batch system
        """

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

        rle_filters = self.get_filter() if self.rle_filter_file else {}
        statistics = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue

            if not os.path.exists(sample_info['local_paths'][0]['path']):
                logging.warning("Skipping sample {sample_name}".format(sample_name = sample_name))
                continue

            process_name = sample_info["process_name_specific"]
            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_addMEM, process_name))
            is_mc = (sample_info["type"] == "mc")
            if self.rle_filter_file:
                assert(process_name in rle_filters)

            inputFileList = generateInputFileList(sample_info, self.max_files_per_job)
            # typically, the analysis ends here and starts looping b/c the smallest unit of work processes
            # at least one file; we need, however, to split the file into event ranges in such a way that
            # each job performs mem_integrations_per_job MEM integrations

            # so what we are going to do is to open each set of files in inputFileList, read the variable
            # requestMEM_*l_*tau and try to gather the event ranges such that each event range
            # performs up to mem_integrations_per_job integrations per job
            memEvtRangeDict = self.memJobList(inputFileList, rle_filters[process_name] if self.rle_filter_file else [])

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
                self.shFiles_addMEM_modified[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_CFGS], "addMEM_%s_%s_%i.sh" % (self.channel, process_name, jobId)
                )
                self.outputFiles[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_NTUPLES], "%s_%i.root" % (process_name, jobId)
                )
                self.logFiles_addMEM[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_LOGS], "addMEM_%s_%s_%i.log" % (self.channel, process_name, jobId)
                )
                self.logFiles_addMEM[key_file] = get_log_version((self.logFiles_addMEM[key_file],))[0]
                self.createCfg_addMEM(
                    self.inputFiles[key_file],
                    memEvtRangeDict[jobId]['event_range'][0],
                    memEvtRangeDict[jobId]['event_range'][1],
                    self.outputFiles[key_file],
                    self.era,
                    is_mc,
                    self.cfgFiles_addMEM_modified[key_file],
                    memEvtRangeDict[jobId]['whitelist'],
                )

                # associate the output file with the fileset_id
                #UDPATE: ONE OUTPUT FILE PER SAMPLE!
                fileset_id = memEvtRangeDict[jobId]['fileset_id']
                hadd_output_dir = os.path.join(
                    self.dirs[key_dir][DKEY_FINAL_NTUPLES],
                    '%04d' % (fileset_id // 1000)
                )
                if not os.path.exists(hadd_output_dir):
                    os.makedirs(hadd_output_dir)
                hadd_output = os.path.join(
                    hadd_output_dir, '%s_%i.root' % ('tree', fileset_id) # UDPATE: ADDED
                    #hadd_output_dir, "tree.root" # UDPATE: REMOVED
                )
                if hadd_output not in self.hadd_records:
                    self.hadd_records[hadd_output] = {}
                    self.hadd_records[hadd_output]['output_files'] = []
                self.hadd_records[hadd_output]['fileset_id'] = fileset_id
                self.hadd_records[hadd_output]['output_files'].append(self.outputFiles[key_file])
                self.hadd_records[hadd_output]['process_name'] = process_name
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
            if v['nof_entries'] == 0:
                int_per_event = 0.
                evt_pass = 0.
            else:
                int_per_event = float(v['nof_int']) / v['nof_entries']
                evt_pass = (100 * float(v['nof_events_pass']) / v['nof_entries'])
            if v['nof_events_pass'] == 0:
                nof_int_pass = 0.
            else:
                nof_int_pass = float(v['nof_int_pass']) / v['nof_events_pass']
            print('%s%s: %d (%d entries; %d jobs; %.2f int/evt; %d (%.2f%%) evt pass; %.2f int/evt pass; %d evt 0int)' %
              (k,
               ' ' * (ws_len - len(k)),
               v['nof_int'],
               v['nof_entries'],
               v['nof_jobs'],
               int_per_event,
               v['nof_events_pass'],
               evt_pass,
               nof_int_pass,
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
        record_software_state(self.sw_ver_file_cfg, self.sw_ver_file_out, DEPENDENCIES)
        run_cmd(
            "make -f %s -j %i 2>%s 1>%s" % \
            (self.makefile, self.num_parallel_jobs, self.stderr_file_path, self.stdout_file_path),
            False
        )
