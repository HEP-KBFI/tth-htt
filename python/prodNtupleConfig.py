import codecs
import os
import logging
import sys
import getpass

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch

DKEY_CFGS = "cfgs"
DKEY_NTUPLES = "ntuples"
DKEY_LOGS = "logs"

executable_rm = 'rm'

class prodNtupleConfig:
    """Configuration metadata needed to run Ntuple production.
    
    Args:
        configDir: The root config dir -- all configuration files are stored in its subdirectories
        outputDir: The root output dir -- all log and output files are stored in its subdirectories
        executable_prodNtuple: Name of the executable that runs the Ntuple production
        debug: if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method: either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs: number of jobs that can be run in parallel on local machine (does not limit number of Ntuple production jobs running in parallel on batch system)
  
    """
    def __init__(self, configDir, outputDir, executable_prodNtuple, channel, samples,
                 era, debug, running_method, rle_directory, version, num_parallel_jobs):

        self.configDir = configDir
        self.outputDir = outputDir
        self.executable_prodNtuple = executable_prodNtuple
        self.channel = channel
        self.max_files_per_job = 1
        self.max_num_jobs = 200000
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
          self.configDir, "Makefile_%s" % self.channel)
        self.num_parallel_jobs = num_parallel_jobs

        self.workingDir = os.getcwd()
        print "Working directory is: " + self.workingDir

        self.rle_directory = rle_directory
        self.version       = version
        if self.rle_directory == 'default':
            self.rle_directory = os.path.join(
                ##os.path.join("/hdfs/local/ttH_2tau", getpass.getuser(), "ttHNtupleProduction", ERA, version),
                '/home', getpass.getuser(), 'ttHAnalysis', self.era, self.version, 'rles', self.channel
            )
        elif self.rle_directory:
            if not os.path.isdir(self.rle_directory):
                logging.error(
                    "No such directory: '{directory_name}'".format(directory_name=self.rle_directory))
                sys.exit(1)

        create_if_not_exists(self.configDir)        
        create_if_not_exists(self.outputDir)
        self.stdout_file = codecs.open(os.path.join(
          self.outputDir, "stdout_%s.log" % self.channel), 'w', 'utf-8')
        self.stderr_file = codecs.open(os.path.join(
          self.outputDir, "stderr_%s.log" % self.channel), 'w', 'utf-8')
        self.dirs = {}
        self.samples = samples
        self.cfgFiles_prodNtuple_modified = {}
        self.logFiles_prodNtuple = {}
        self.sbatchFile_prodNtuple = os.path.join(
          self.configDir, "sbatch_prodNtuple_%s.py" % self.channel)
        self.inputFiles = {}
        self.outputFiles = {}
        self.filesToClean = []
        
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in [ DKEY_CFGS, DKEY_NTUPLES, DKEY_LOGS ]:
                initDict(self.dirs, [ key_dir, dir_type ])
                if dir_type in [ DKEY_CFGS ]:
                    self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name)
                else:
                    self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
        ##print "self.dirs = ", self.dirs

        self.cvmfs_error_log = {}

    def createCfg_prodNtuple(self, *args):
        raise ValueError(
            "Function 'createCfg_prodNtuple' not implemented in derrived class !!")

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the Ntuple production jobs to the batch system
        """
        tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile_prodNtuple,
            executable = self.executable_prodNtuple,
            cfg_file_names = self.cfgFiles_prodNtuple_modified,
            input_file_names = self.inputFiles,
            output_file_names = self.outputFiles,
            log_file_names = self.logFiles_prodNtuple,
            working_dir = self.workingDir,
            max_num_jobs = self.max_num_jobs,
            cvmfs_error_log = self.cvmfs_error_log
        )

    def addToMakefile_prodNtuple(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the Ntuple production code
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch:")
            lines_makefile.append("\t%s %s" % (
                "python", self.sbatchFile_prodNtuple))
            lines_makefile.append("")
        for key_file, output_file in self.outputFiles.items():
            cfg_file_prodNtuple_modified = self.cfgFiles_prodNtuple_modified[key_file]
            if self.is_makefile:
                lines_makefile.append("%s:" % output_file)
                cfg_file = cfg_file_prodNtuple_modified
                log_file = self.logFiles_prodNtuple[key_file]
                lines_makefile.append("\t%s %s &> %s" % (
                    self.executable_prodNtuple, cfg_file, log_file))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (output_file, "sbatch"))
                lines_makefile.append("\t%s" % ":")  # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(output_file)

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the Ntuple production.
        """
        targets = None
        if self.is_sbatch:
            targets = [ "sbatch" ]
        else:
            targets = self.outputFiles.values()
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean)
        logging.info("Run it with:\tmake -f %s -j %i " %
            (self.makefile, self.num_parallel_jobs))    

    def create(self):
        """Creates all necessary config files and runs the Ntuple production -- either locally or on the batch system
        """

        for key in self.dirs.keys():
            if type(self.dirs[key]) == dict:
                for dir_type in self.dirs[key].keys():
                    create_if_not_exists(self.dirs[key][dir_type])
            else:
                create_if_not_exists(self.dirs[key])
  
        self.inputFileIds = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
                continue

            process_name = sample_info["process_name_specific"]
            is_mc = (sample_info["type"] == "mc")
            rle_filename = ''
            if self.rle_directory:
                rle_filename = os.path.join(self.rle_directory, "{base_name}.txt".format(base_name = process_name))
                if not os.path.isfile(rle_filename):
                    logging.error("No such RLE file: {rle_filename}; setting it to ''".format(rle_filename = rle_filename))
                    rle_filename = ''
                else:
                    logging.info("Using RLE file {rle_filename}".format(rle_filename = rle_filename))

            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_prodNtuple, process_name))  
    
            inputFileList = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
            for jobId in inputFileList.keys():
            
                key_dir = getKey(sample_name)
                key_file = getKey(sample_name, jobId)

                self.inputFiles[key_file] = inputFileList[jobId]
                if len(self.inputFiles[key_file]) == 0:
                    print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, self.inputFiles[key_file])
                    continue
                ##print "sample = '%s', jobId = %i: number of input files = %i" % (sample_name, jobId, len(self.inputFiles[key_file]))
                ##print self.inputFiles[key_file]
                assert(len(self.inputFiles[key_file]) == 1), "There is more than one input file!"
                self.cfgFiles_prodNtuple_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "produceNtuple_%s_%s_%i_cfg.py" % \
                  (self.channel, process_name, jobId))
                self.outputFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_NTUPLES], "%s_%i.root" % \
                  (process_name, jobId))
                self.logFiles_prodNtuple[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "produceNtuple_%s_%s_%i.log" % \
                  (self.channel, process_name, jobId))
                self.createCfg_prodNtuple(self.inputFiles[key_file], self.outputFiles[key_file], self.era, is_mc, 
                                          self.cfgFiles_prodNtuple_modified[key_file], rle_filename)
                
        if self.is_sbatch:
            logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_prodNtuple)
            self.createScript_sbatch()

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile_prodNtuple(lines_makefile)
        #self.addToMakefile_clean(lines_makefile)
        self.createMakefile(lines_makefile)
  
        logging.info("Done")

    def run(self):
        """Runs all Ntuple production jobs -- either locally or on the batch system.
        """
        run_cmd("make -f %s -j %i " % (self.makefile, self.num_parallel_jobs),
            False, self.stdout_file, self.stderr_file)
