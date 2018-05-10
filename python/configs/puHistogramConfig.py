import os, logging, uuid

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, createFile, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd as tools_createScript_sbatch_hadd

DKEY_SCRIPTS    = "scripts"
DKEY_CFGS       = "cfgs"
DKEY_HISTO_TMP  = "tmp_histograms"
DKEY_HISTO      = "histograms"
DKEY_PLOTS      = "plots"
DKEY_LOGS       = "logs"
DKEY_HADD_RT    = "hadd_cfg_rt"
MAKEFILE_TARGET = "sbatch_puProfile"

class puHistogramConfig:
    """Configuration metadata needed to run PU profile production.

    Args:
        configDir:             The root config dir -- all configuration files are stored in its subdirectories
        outputDir:             The root output dir -- all log and output files are stored in its subdirectories
        executable:            Name of the executable that runs the PU profile production
        check_input_files:     if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method:        either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs:     number of jobs that can be run in parallel on local machine
                               (does not limit number of PU profile production jobs running in parallel on batch system)

    """
    def __init__(self, configDir, outputDir, executable,
                 samples, max_files_per_job, era, check_input_files, running_method,
                 version, num_parallel_jobs, pool_id = '', verbose = False, dry_run = False):

        self.configDir             = configDir
        self.outputDir             = outputDir
        self.executable            = executable
        self.max_num_jobs          = 200000
        self.samples               = samples
        self.max_files_per_job     = max_files_per_job
        self.era                   = era
        self.check_input_files     = check_input_files
        self.verbose               = verbose
        self.dry_run               = dry_run
        if running_method.lower() not in ["sbatch", "makefile"]:
          raise ValueError("Invalid running method: %s" % running_method)

        self.running_method    = running_method
        self.is_sbatch         = self.running_method.lower() == "sbatch"
        self.is_makefile       = not self.is_sbatch
        self.makefile          = os.path.join(self.configDir, "Makefile_puProfile")
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
        create_if_not_exists(self.outputDir)
        self.stdout_file_path = os.path.join(self.configDir, "stdout_puProfile.log")
        self.stderr_file_path = os.path.join(self.configDir, "stderr_puProfile.log")
        self.stdout_file_path, self.stderr_file_path = get_log_version((
            self.stdout_file_path, self.stderr_file_path,
        ))

        self.sbatchFile_puProfile = os.path.join(self.configDir, "sbatch_puProfile.py")
        self.cfgFiles_puProfile = {}
        self.logFiles_puProfile = {}
        self.jobOptions_sbatch = {}

        self.inputFiles      = {}
        self.outputFiles_tmp = {}
        self.outputFiles     = {}

        self.phoniesToAdd = []
        self.filesToClean = []

        self.dirs = {}
        all_dirs = [ DKEY_CFGS, DKEY_HISTO_TMP, DKEY_HISTO, DKEY_PLOTS, DKEY_LOGS, DKEY_SCRIPTS, DKEY_HADD_RT ]
        cfg_dirs = [ DKEY_CFGS, DKEY_LOGS, DKEY_PLOTS, DKEY_SCRIPTS, DKEY_HADD_RT ]

        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in all_dirs:
                initDict(self.dirs, [ key_dir, dir_type ])
                if dir_type in cfg_dirs and dir_type != DKEY_PLOTS:
                    self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, process_name)
                else:
                    self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, process_name)
        for dir_type in cfg_dirs:
            initDict(self.dirs, [ dir_type ])
            self.dirs[dir_type] = os.path.join(self.configDir, dir_type)

        self.cvmfs_error_log = {}
        self.num_jobs = {
            'hadd'      : 0,
            'puProfile' : 0,
            'plot'      : 0,
        }


    def createCfg_puProfile(self, jobOptions):
        """Create python configuration file for the puProfile.sh script

        Args:
          inputFiles: list of input files (Ntuples)
          outputFile: output file of the job -- a ROOT file containing histogram
        """
        lines = jobOptions['inputFiles'] + [ '', jobOptions['outputFile'] ]
        assert(len(lines) >= 3)
        createFile(jobOptions['cfgFile_path'], lines, nofNewLines = 1)

    def createCfg_hadd(self, jobOptions):
        # plot_from_histogram.py -i input.root -j autoPU -o output.png -x '# PU interactions' -y '# events' -t 'ttHJetToNonbb' -g
        pass

    def createScript_sbatch(self, executable, sbatchFile, jobOptions,
                            key_cfg_file = 'cfgFile_path', key_input_file = 'inputFiles',
                            key_output_file = 'outputFile', key_log_file = 'logFile',
                            skipFileSizeCheck = True):
        num_jobs = tools_createScript_sbatch(
            sbatch_script_file_name = sbatchFile,
            executable              = executable,
            command_line_parameters = { key: value[key_cfg_file]    for key, value in jobOptions.items() },
            input_file_names        = { key: value[key_input_file]  for key, value in jobOptions.items() },
            output_file_names       = { key: value[key_output_file] for key, value in jobOptions.items() },
            script_file_names       = { key: value[key_cfg_file]    for key, value in jobOptions.items() },
            log_file_names          = { key: value[key_log_file]    for key, value in jobOptions.items() },
            working_dir             = self.workingDir,
            max_num_jobs            = self.max_num_jobs,
            cvmfs_error_log         = self.cvmfs_error_log,
            pool_id                 = uuid.uuid4(),
            verbose                 = self.verbose,
            dry_run                 = self.dry_run,
            job_template_file       = 'sbatch-node.produce.sh.template',
            skipFileSizeCheck       = skipFileSizeCheck,
        )
        return num_jobs

    def create_hadd_python_file(self, inputFiles, outputFile, hadd_stage_name):
        sbatch_hadd_file = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_hadd_%s.py" % hadd_stage_name)
        sbatch_hadd_file = sbatch_hadd_file.replace(".root", "")

        scriptFile = os.path.join(self.dirs[DKEY_SCRIPTS], os.path.basename(sbatch_hadd_file).replace(".py", ".sh"))
        logFile    = os.path.join(self.dirs[DKEY_LOGS],    os.path.basename(sbatch_hadd_file).replace(".py", ".log"))

        sbatch_hadd_dir = os.path.join(self.dirs[DKEY_HADD_RT], hadd_stage_name) if self.dirs[DKEY_HADD_RT] else ''
        self.num_jobs['hadd'] += tools_createScript_sbatch_hadd(
            sbatch_script_file_name = sbatch_hadd_file,
            input_file_names        = inputFiles,
            output_file_name        = outputFile,
            script_file_name        = scriptFile,
            log_file_name           = logFile,
            working_dir             = self.workingDir,
            auxDirName              = sbatch_hadd_dir,
            pool_id                 = uuid.uuid4(),
            verbose                 = self.verbose,
            dry_run                 = self.dry_run,
        )
        return sbatch_hadd_file

    def addToMakefile_puProfile(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the PU profile production code
        """
        if self.is_sbatch:
            lines_makefile.extend([
                "%s:" % MAKEFILE_TARGET,
                "\t%s %s" % ("python", self.sbatchFile_puProfile),
                "",
            ])
        for key_file, output_file in self.outputFiles_tmp.items():
            cfg_file = self.cfgFiles_puProfile[key_file]
            if self.is_makefile:
                log_file = self.logFiles_puProfile[key_file]
                lines_makefile.extend([
                    "%s:" % output_file,
                    "\t%s %s &> %s" % (self.executable, cfg_file, log_file),
                    "",
                ])
            elif self.is_sbatch:
                lines_makefile.extend([
                    "%s: %s" % (output_file, MAKEFILE_TARGET),
                    "\t%s" % ":",
                    "",
                ])
            self.filesToClean.append(output_file)
        self.phoniesToAdd.append(MAKEFILE_TARGET)

    def addToMakefile_hadd(self, lines_makefile):
        scriptFiles = {}
        jobOptions = {}
        for key, cfg in self.outputFiles.items():
            scriptFiles[key] = self.create_hadd_python_file(
                inputFiles      = cfg['inputFiles'],
                outputFile      = cfg['outputFile'],
                hadd_stage_name = "_".join([ key, "ClusterHistogramAggregator" ]),
            )
            jobOptions[key] = {
                'inputFiles'   : cfg['inputFiles'],
                'cfgFile_path' : scriptFiles[key],
                'outputFile'   : cfg['outputFile'],
                'logFile'      : os.path.join(
                    self.dirs[DKEY_LOGS],
                    'hadd_%s' % os.path.basename(cfg['outputFile']).replace(".root", ".log"),
                ),
            }

        sbatchTarget = None
        if self.is_sbatch:
            sbatchTarget = "sbatch_hadd"
            self.phoniesToAdd.append(sbatchTarget)

            sbatchFile = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_hadd.py")
            self.createScript_sbatch('python', sbatchFile, jobOptions)

            lines_makefile.extend([
                "%s: %s" % \
                (
                    sbatchTarget,
                    " ".join([
                        " ".join(self.outputFiles[key]['inputFiles']) for key in self.outputFiles
                    ])
                ),
                "",
            ])
            for cfg in self.outputFiles.values():
                lines_makefile.append("\trm -f %s" % cfg['outputFile'])
                lines_makefile.extend([
                "\tpython %s" % sbatchFile,
                "",
            ])

        for key, cfg in self.outputFiles.items():
            if self.is_sbatch:
                lines_makefile.extend([
                    "%s: %s" % (cfg['outputFile'], sbatchTarget),
                    "\t:",
                    ""
                ])
            else:
                lines_makefile.extend([
                    "%s: %s" % (cfg['outputFile'], ' '.join(cfg['inputFiles'])),
                    "\trm -f %s" % cfg['outputFile'],
                    "\tpython %s" % scriptFiles[key],
                    "",
                ])
            self.filesToClean.append(cfg['outputFile'])

    def addToMakefile_plot(self, lines_makefile):
        phonie_target = "sbatch_plot"

        cmd_string = "plot_from_histogram.py -i %s -j autoPU -o %s -x '# PU interactions' " \
                     "-y '# events' -t '%s' -g"
        cmd_log_string = cmd_string + " -l"

        jobOptions = {}
        for key, cfg in self.outputFiles.items():
            plot_linear = os.path.join(self.dirs[DKEY_PLOTS], '%s.png'     % key)
            plot_log    = os.path.join(self.dirs[DKEY_PLOTS], '%s_log.png' % key)
            logFile_linear = os.path.join(self.dirs[DKEY_LOGS], 'plot_linear_%s.log' % key)
            logFile_log    = os.path.join(self.dirs[DKEY_LOGS], 'plot_log_%s.log' % key)
            logFile_linear, logFile_log = get_log_version((
                logFile_linear, logFile_log
            ))
            jobOptions[key] = {
                'inputFile' : cfg['outputFile'],
                'jobs' : {
                    'linear' : {
                        'outputFile' : plot_linear,
                        'cmd'        : cmd_string % (cfg['outputFile'], plot_linear, key),
                        'logFile'    : logFile_linear,
                    },
                    'log' : {
                        'outputFile' : plot_log,
                        'cmd'        : cmd_log_string % (cfg['outputFile'], plot_log, key),
                        'logFile'    : logFile_log,
                    }
                }
            }
            self.filesToClean.extend([
                jobOptions[key]['jobs'][plot_type]['outputFile'] for plot_type in jobOptions[key]['jobs']
            ])

        if self.is_sbatch:
            lines_makefile.append(
                "%s: %s" % (
                    " ".join(jobOptions[key]['inputFile'] for key in jobOptions),
                    phonie_target,
                ),
            )
            for cfg in jobOptions.values():
                for plot_cfg in cfg['jobs'].values():
                  lines_makefile.append(
                      "\t%s &> %s" % (plot_cfg['cmd'], plot_cfg['logFile'])
                  )
            for cfg in jobOptions.values():
                for plot_cfg in cfg['jobs'].values():
                    lines_makefile.extend([
                        "",
                        "%s: %s" % (phonie_target, plot_cfg['outputFile']),
                        "\t:",
                        "",
                    ])
                    self.num_jobs['plot'] += 1
            self.phoniesToAdd.append(phonie_target)
        else:
            for cfg in jobOptions:
                for plot_cfg in cfg['jobs'].values():
                    lines_makefile.extend([
                        "%s: %s" % (plot_cfg['outputFile'], cfg['inputFile']),
                        "\t%s &> %s" % (plot_cfg['cmd'], plot_cfg['logFile']),
                        "",
                    ])

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the PU profile production.
        """
        targets = None
        if self.is_sbatch:
            targets = [ MAKEFILE_TARGET ]
        else:
            targets = [ cfg['outputFile'] for cfg in self.outputFiles.values() ]
        tools_createMakefile(
            makefileName   = self.makefile,
            targets        = targets,
            lines_makefile = lines_makefile,
            filesToClean   = self.filesToClean,
            isSbatch       = self.is_sbatch,
            phoniesToAdd   = self.phoniesToAdd
        )
        logging.info("Run it with:\tmake -f %s -j %i " % (self.makefile, self.num_parallel_jobs))

    def create(self):
        """Creates all necessary config files and runs the PU profile production -- either locally or on the batch system
        """

        for key in self.dirs.keys():
            if type(self.dirs[key]) == dict:
                for dir_type in self.dirs[key].keys():
                    create_if_not_exists(self.dirs[key][dir_type])
            else:
                create_if_not_exists(self.dirs[key])

        self.inputFileIds = {}
        for sample_name, sample_info in self.samples.items():
            process_name = sample_info["process_name_specific"]
            is_mc = (sample_info["type"] == "mc")

            if not is_mc:
              continue

            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable, process_name))

            inputFileList = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)
            key_dir = getKey(sample_name)

            outputFile = os.path.join(
                self.dirs[key_dir][DKEY_HISTO], "%s.root" % process_name
            )
            self.outputFiles[process_name] = {
                'inputFiles' : [],
                'outputFile' : outputFile
            }

            for jobId in inputFileList.keys():

                key_file = getKey(sample_name, jobId)

                self.inputFiles[key_file] = inputFileList[jobId]
                if len(self.inputFiles[key_file]) == 0:
                    logging.warning(
                        "ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, self.inputFiles[key_file])
                    )
                    continue

                self.cfgFiles_puProfile[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_CFGS], "puProfile_%s_%i_cfg.txt" % (process_name, jobId)
                )
                self.outputFiles_tmp[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_HISTO_TMP], "histogram_%i.root" % jobId
                )
                self.logFiles_puProfile[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_LOGS], "puProfile_%s_%i.log" % (process_name, jobId)
                )
                self.jobOptions_sbatch[key_file] = {
                    'inputFiles'   : self.inputFiles[key_file],
                    'cfgFile_path' : self.cfgFiles_puProfile[key_file],
                    'outputFile'   : self.outputFiles_tmp[key_file],
                    'logFile'      : self.logFiles_puProfile[key_file],
                }
                self.createCfg_puProfile(self.jobOptions_sbatch[key_file])
                self.outputFiles[process_name]['inputFiles'].append(self.outputFiles_tmp[key_file])

        if self.is_sbatch:
          logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable)
          self.num_jobs['puProfile'] += self.createScript_sbatch(
              self.executable, self.sbatchFile_puProfile, self.jobOptions_sbatch
          )

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile_puProfile(lines_makefile)
        self.addToMakefile_hadd(lines_makefile)
        self.addToMakefile_plot(lines_makefile)
        self.createMakefile(lines_makefile)
        logging.info("Done")

        return self.num_jobs

    def run(self):
        """Runs all PU profile production jobs -- either locally or on the batch system.
        """
        run_cmd(
            "make -f %s -j %i 2>%s 1>%s" % \
            (self.makefile, self.num_parallel_jobs, self.stderr_file_path, self.stdout_file_path),
            False
        )
