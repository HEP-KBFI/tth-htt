from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version, check_submission_cmd, record_software_state
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.common import logging, DEPENDENCIES
from tthAnalysis.HiggsToTauTau.analysisSettings import VH_keys

import re
import os
import uuid

DKEY_CFGS       = "cfgs"
DKEY_NTUPLES    = "ntuples"
DKEY_LOGS       = "logs"
MAKEFILE_TARGET = "sbatch_vhSplit"

class vhSplitConfig:
    """Configuration metadata needed to run VH splitting
    """
    def __init__(self,
             configDir,
             localDir,
             outputDir,
             samples,
             era,
             check_output_files,
             running_method,
             version,
             num_parallel_jobs,
             dry_run,
             isDebug,
             use_home,
             keep_logs,
             verbose = False,
             pool_id        = '',
             submission_cmd = None,
          ):

        self.configDir             = configDir
        self.localDir              = localDir
        self.outputDir             = outputDir
        self.max_num_jobs          = 200000
        self.samples               = samples
        self.max_files_per_job     = 1
        self.era                   = era
        self.check_output_files    = check_output_files
        self.verbose               = verbose
        self.dry_run               = dry_run
        self.isDebug               = isDebug
        self.use_home              = use_home
        self.keep_logs             = keep_logs
        if running_method.lower() not in ["sbatch", "makefile"]:
          raise ValueError("Invalid running method: %s" % running_method)

        self.running_method    = running_method
        self.is_sbatch         = self.running_method.lower() == "sbatch"
        self.is_makefile       = not self.is_sbatch
        self.makefile          = os.path.join(self.localDir, "Makefile_vhSplitter")
        self.num_parallel_jobs = num_parallel_jobs
        self.pool_id           = pool_id if pool_id else uuid.uuid4()

        self.workingDir = os.getcwd()
        logging.info("Working directory is: %s" % self.workingDir)
        self.template_dir = os.path.join(
            os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'test', 'templates'
        )
        logging.info("Templates directory is: %s" % self.template_dir)

        self.version = version
        self.samples = samples

        create_if_not_exists(self.configDir)
        create_if_not_exists(self.localDir)
        create_if_not_exists(self.outputDir)
        self.stdout_file_path = os.path.join(self.localDir, "stdout.log")
        self.stderr_file_path = os.path.join(self.localDir, "stderr.log")
        self.sw_ver_file_cfg  = os.path.join(self.localDir, "VERSION.log")
        self.sw_ver_file_out  = os.path.join(self.outputDir, "VERSION.log")
        self.submission_out   = os.path.join(self.localDir, "SUBMISSION.log")
        self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out, self.submission_out = get_log_version((
            self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out, self.submission_out
        ))
        check_submission_cmd(self.submission_out, submission_cmd)

        self.sbatchFile = os.path.join(self.localDir, "sbatch.py")
        self.jobParams = {}
        self.logFiles = {}
        self.scriptFiles = {}

        self.inputFiles   = {}
        self.outputFiles  = {}
        self.filesToClean = [ self.configDir ]
        self.dirs         = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue
            process_name = sample_info["process_name_specific"]
            assert(process_name.startswith("VH"))
            for vh_key in VH_keys:
                key_dir = re.sub("^VH", vh_key, process_name)
                assert(key_dir != process_name)
                for dir_type in [ DKEY_CFGS, DKEY_NTUPLES, DKEY_LOGS ]:
                    initDict(self.dirs, [ key_dir, dir_type ])
                    if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                        dir_choice = self.configDir if dir_type == DKEY_CFGS else self.localDir
                        self.dirs[key_dir][dir_type] = os.path.join(dir_choice, dir_type, key_dir)
                    else:
                        self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, key_dir)
        for dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
            initDict(self.dirs, [ dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                dir_choice = self.configDir if dir_type == DKEY_CFGS else self.localDir
                self.dirs[dir_type] = os.path.join(dir_choice, dir_type)
                if dir_choice != self.configDir:
                    self.filesToClean.append(self.dirs[dir_type])
            else:
                self.dirs[dir_type] = os.path.join(self.outputDir, dir_type)

        self.cvmfs_error_log = {}
        self.executable = "split_vh.py"

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the VH splitting jobs to the batch system
        """
        num_jobs = tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile,
            executable              = self.executable,
            command_line_parameters = self.jobParams,
            input_file_names        = self.inputFiles,
            output_file_names       = self.outputFiles,
            script_file_names       = self.scriptFiles,
            log_file_names          = self.logFiles,
            keep_logs               = self.keep_logs,
            working_dir             = self.workingDir,
            max_num_jobs            = self.max_num_jobs,
            cvmfs_error_log         = self.cvmfs_error_log,
            pool_id                 = self.pool_id,
            verbose                 = self.verbose,
            job_template_file       = 'sbatch-node.produce.sh.template',
            dry_run                 = self.dry_run,
            use_home                = self.use_home,
            validate_outputs        = self.check_output_files,
            max_num_submittedJobs   = 3000,
        )
        return num_jobs

    def addToMakefile(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the VH splitting jobs
        """
        if self.is_sbatch:
            lines_makefile.extend([
                "%s:" % MAKEFILE_TARGET,
                "\t%s %s" % ("python", self.sbatchFile),
                "",
            ])
        for key_file, output_file in self.outputFiles.items():
            jobParams = self.jobParams[key_file]
            if self.is_makefile:
                log_file = self.logFiles[key_file]
                lines_makefile.extend([
                    "%s:" % output_file,
                    "\t%s %s &> %s" % (self.executable, jobParams, log_file),
                    "",
                ])
            elif self.is_sbatch:
                lines_makefile.extend([
                    "%s: %s" % (output_file, MAKEFILE_TARGET),
                    "\t%s" % ":",
                    "",
                ])

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the VH splitting
        """
        targets = None
        if self.is_sbatch:
            targets = [ MAKEFILE_TARGET ]
        else:
            targets = self.outputFiles.values()
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean)
        logging.info("Run it with:\tmake -f %s -j %i " % (self.makefile, self.num_parallel_jobs))

    def create(self):
        """Creates all necessary config files and runs the VH splitting -- either locally or on the batch system
        """

        for key in self.dirs.keys():
            if type(self.dirs[key]) == dict:
                for dir_type in self.dirs[key].keys():
                    create_if_not_exists(self.dirs[key][dir_type])
            else:
                create_if_not_exists(self.dirs[key])

        self.inputFileIds = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue

            process_name = sample_info["process_name_specific"]
            assert(process_name.startswith("VH"))

            for vh_key in VH_keys:

                logging.info("Creating configuration files to extract %s events for sample %s" % (vh_key, process_name))
                key_dir = re.sub("^VH", vh_key, process_name)
                assert(process_name != key_dir)

                inputFileList = generateInputFileList(sample_info, self.max_files_per_job)
                subDirs = list(map(
                    lambda y: os.path.join(self.dirs[key_dir][DKEY_NTUPLES], '%04d' % y),
                    set(map(lambda x: x // 1000, inputFileList.keys()))
                ))
                for subDir in subDirs:
                    create_if_not_exists(subDir)
                for jobId in inputFileList.keys():

                    key_file = getKey(key_dir, jobId)

                    self.inputFiles[key_file] = inputFileList[jobId]
                    assert(len(self.inputFiles[key_file]) == 1)
                    if len(self.inputFiles[key_file]) == 0:
                        logging.warning(
                            "ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, self.inputFiles[key_file])
                        )
                        continue

                    self.jobParams[key_file] = "-i {} -{}".format(self.inputFiles[key_file][0], vh_key.lower()[0])
                    self.scriptFiles[key_file] = os.path.join(
                        self.dirs[key_dir][DKEY_CFGS], "vhSplitter_%s_%i.sh" % (key_dir, jobId)
                    )
                    self.outputFiles[key_file] = os.path.join(
                        self.dirs[key_dir][DKEY_NTUPLES], "%04d" % (jobId // 1000), "tree_%i.root" % jobId
                    )
                    self.logFiles[key_file] = os.path.join(
                        self.dirs[key_dir][DKEY_LOGS], "vhSplitter_%s_%i.log" % (key_dir, jobId)
                    )

        num_jobs = 0
        if self.is_sbatch:
            logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable)
            num_jobs = self.createScript_sbatch()
            logging.info("Generated %i job(s)" % num_jobs)

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile(lines_makefile)
        self.createMakefile(lines_makefile)

        logging.info("Done")
        return num_jobs

    def run(self):
        """Runs all VH splitting jobs -- either locally or on the batch system.
        """
        record_software_state(self.sw_ver_file_cfg, self.sw_ver_file_out, DEPENDENCIES)
        run_cmd(
            "make -f %s -j %i 2>%s 1>%s" % \
            (self.makefile, self.num_parallel_jobs, self.stderr_file_path, self.stdout_file_path),
            False
        )
