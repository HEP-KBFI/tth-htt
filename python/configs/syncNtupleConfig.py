from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import DKEY_SCRIPTS, DKEY_LOGS, DKEY_SYNC
from tthAnalysis.HiggsToTauTau.jobTools import get_log_version, run_cmd, create_if_not_exists
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd
import os, jinja2, uuid, logging, sys

makeFileTemplate = '''
.DEFAULT_GOAL := all
SHELL := /bin/bash

all: {{ output_file }}

{{ output_file }}:{% for channel_output in channel_info %} {{channel_output}}{% endfor %}
\trm -f {{ output_file }}
\tpython {{ hadd_script }} &> {{ hadd_wrapper_log }}

{% for channel_output, channel_cmd in channel_info.items() %}
{{ channel_output }}:
\trm -f {{ channel_output }}
\t{{ channel_cmd['run'] }}
{% endfor %}

clean:
{%- for channel_output, channel_cmd in channel_info.items() %}
\t{{ channel_cmd['clean'] }}{% endfor %}
\trm -f {{ output_file }}

.PHONY: clean

'''

class syncNtupleConfig:

  def __init__(self, config_dir, output_dir, output_filename, version, era, channels, dry_run,
               resubmission_limit, disable_resubmission, check_input_files, isDebug, rle_select,
               no_mem, use_nonnominal, hlt_filter, tau_id_wp, use_home):

    self.dry_run           = dry_run
    self.check_input_files = check_input_files
    self.use_home          = use_home
    project_dir = os.path.join(os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau')
    executable_pattern = os.path.join(project_dir, 'test', 'tthAnalyzeRun_%s.py')

    self.hadd_script_dir_path = os.path.join(config_dir, DKEY_SCRIPTS, DKEY_SYNC)
    self.hadd_log_dir_path    = os.path.join(config_dir, DKEY_LOGS,    DKEY_SYNC,)
    self.hadd_script_path         = os.path.join(self.hadd_script_dir_path, 'hadd_sync.py')
    self.hadd_log_wrapper_path    = os.path.join(self.hadd_log_dir_path,    'hadd_sync_wrapper.log')
    self.hadd_log_executable_path = os.path.join(self.hadd_log_dir_path,    'hadd_sync_executable.log')

    final_output_dir = os.path.join(output_dir, DKEY_SYNC)
    self.final_output_file = os.path.join(final_output_dir, output_filename)

    common_args = "-m %s -v %s -e %s -r %d" % \
      ('sync_noMEM' if no_mem else 'sync',  version, era, resubmission_limit)
    additional_args = " -A"
    if self.dry_run:
      additional_args += " -d"
    if disable_resubmission:
      additional_args += " -R"
    if check_input_files:
      additional_args += " -C"
    if isDebug:
      additional_args += " -D"
    if rle_select:
      additional_args += " -S '%s'" % rle_select
    if use_nonnominal:
      additional_args += " -O"
    if use_home:
      additional_args += " -y"
    if hlt_filter:
      additional_args += " -H"

    inclusive_args = '-v %s -e %s' % (version, era)
    if no_mem:
      inclusive_args += ' -N'

    inclusive_args += additional_args
    common_args    += additional_args

    self.channel_info = {}
    for channel in channels:
      input_file = os.path.join(final_output_dir, '%s.root' % channel)
      channel_script = executable_pattern % channel

      channel_makefile = os.path.join(config_dir, 'Makefile_%s' % channel)
      channel_outlog   = os.path.join(config_dir, 'stdout_sync_%s.log' % channel)
      channel_errlog   = os.path.join(config_dir, 'stderr_sync_%s.log' % channel)
      channel_outlog, channel_errlog = get_log_version((channel_outlog, channel_errlog))

      cmd_args = common_args if channel != 'inclusive' else inclusive_args
      if tau_id_wp and 'tau' in channel:
        additional_args += " -w %s" % tau_id_wp

      channel_cmd_run = '%s %s 2>%s 1>%s' % \
                        (channel_script, cmd_args, channel_errlog, channel_outlog)
      channel_cmd_clean = 'make -f %s clean' % channel_makefile
      self.channel_info[input_file] = {
        'run'   : channel_cmd_run,
        'clean' : channel_cmd_clean,
      }

    self.stdout_file_path = os.path.join(config_dir, "stdout_sync.log")
    self.stderr_file_path = os.path.join(config_dir, "stderr_sync.log")
    self.stdout_file_path, self.stderr_file_path = get_log_version((
      self.stdout_file_path, self.stderr_file_path,
    ))
    self.makefile_path = os.path.join(config_dir, 'Makefile_sync')

  def create(self):
    create_if_not_exists(self.hadd_script_dir_path)
    create_if_not_exists(self.hadd_log_dir_path)

    createScript_sbatch_hadd(
      sbatch_script_file_name = self.hadd_script_path,
      input_file_names        = list(self.channel_info.keys()),
      output_file_name        = self.final_output_file,
      script_file_name        = self.hadd_script_path.replace('.py', '.sh'),
      log_file_name           = self.hadd_log_executable_path, # the basename will be replaced anyways?
      working_dir             = None,
      waitForJobs             = True,
      auxDirName              = '',
      pool_id                 = uuid.uuid4(),
      verbose                 = False,
      dry_run                 = self.dry_run,
      use_home                = self.use_home,
    )
    logging.info("Generated hadd config file: %s" % self.hadd_script_path)

    with open(self.makefile_path, 'w') as makefile:
      makeFileContents = jinja2.Template(makeFileTemplate).render(
        output_file      = self.final_output_file,
        channel_info     = self.channel_info,
        hadd_script      = self.hadd_script_path,
        hadd_wrapper_log = self.hadd_log_wrapper_path,
      )
      makefile.write(makeFileContents)
    logging.info("Created the makefile: %s" % self.makefile_path)

  def run(self, clean):
    target = 'all'
    if clean:
      if not os.path.isfile(self.makefile_path):
        logging.error(
          "The makefile %s is missing and therefore it's not possible to clean anything; "
          "run sync Ntuple production first!" % self.makefile_path
        )
        sys.exit(1)
      target = 'clean'

    nof_parallel_jobs = len(self.channel_info)
    make_cmd          = "make -f %s -j %d %s 2>%s 1>%s" % \
      (self.makefile_path, nof_parallel_jobs, target, self.stderr_file_path, self.stdout_file_path)
    logging.info("Running the make command: %s" % make_cmd)
    run_cmd(make_cmd)
    logging.info("All done")
