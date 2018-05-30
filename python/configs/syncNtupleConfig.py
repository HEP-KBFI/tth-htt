from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import DKEY_SCRIPTS, DKEY_LOGS, DKEY_SYNC
from tthAnalysis.HiggsToTauTau.jobTools import get_log_version, run_cmd, create_if_not_exists, record_software_state
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd

import os
import jinja2
import uuid
import logging
import sys

DEPENDENCIES = [
    "",  # CMSSW_BASE/src
    "tthAnalysis/HiggsToTauTau",
    "tthAnalysis/TauTriggerSFs2017",
    "TauAnalysis/ClassicSVfit",
    "TauAnalysis/SVfitTF",
    "ttH_Htautau_MEM_Analysis",
    "tthAnalysis/tthMEM",
]

makeFileTemplate = '''
.DEFAULT_GOAL := all
SHELL := /bin/bash

all: {{ output_file }}

{{ output_file }}:{% for channel_output in channel_info %} {{channel_output}}{% endfor %}
\trm -f {{ output_file }}
\t{{ hadd_script }} &> {{ hadd_wrapper_log }}
\t{{ additional_cmds }}

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

  def __init__(self,
        config_dir,
        output_dir,
        output_filename,
        version,
        era,
        channels,
        dry_run,
        resubmission_limit,
        check_input_files,
        running_method,
        isDebug,
        rle_select,
        with_mem,
        use_nonnominal,
        hlt_filter,
        tau_id_wp,
        use_home
      ):

    self.running_method    = running_method
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

    common_args = "-m %s -v %s -e %s -r %d -J 5" % \
      ('sync_wMEM' if with_mem else 'sync',  version, era, resubmission_limit)
    additional_args = " -A"
    if self.dry_run:
      additional_args += " -d"
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
    if self.running_method:
      additional_args += " -R %s" % self.running_method

    inclusive_args = '-v %s -e %s' % (version, era)
    if with_mem:
      inclusive_args += ' -M'

    inclusive_args += additional_args
    common_args    += additional_args

    create_if_not_exists(config_dir)
    create_if_not_exists(output_dir)

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
    self.sw_ver_file_cfg  = os.path.join(config_dir, "VERSION_sync.log")
    self.sw_ver_file_out  = os.path.join(output_dir, "VERSION_sync.log")
    self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out = get_log_version((
      self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out
    ))
    self.makefile_path = os.path.join(config_dir, 'Makefile_sync')

  def create(self):
    create_if_not_exists(self.hadd_log_dir_path)

    if self.running_method == 'sbatch':
      create_if_not_exists(self.hadd_script_dir_path)

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
      self.hadd_script_path = 'python %s' % self.hadd_script_path
      additional_cmds = ''

    else:
      self.hadd_script_path = 'hadd -f {} {}'.format(
        os.path.basename(self.final_output_file), ' '.join(list(self.channel_info.keys()))
      )
      additional_cmds = 'mv {} {}'.format(
        os.path.basename(self.final_output_file), self.final_output_file
      )

    with open(self.makefile_path, 'w') as makefile:
      makeFileContents = jinja2.Template(makeFileTemplate).render(
        output_file      = self.final_output_file,
        channel_info     = self.channel_info,
        hadd_script      = self.hadd_script_path,
        hadd_wrapper_log = self.hadd_log_wrapper_path,
        additional_cmds  = additional_cmds,
      )
      makefile.write(makeFileContents)
    logging.info("Created the makefile: %s" % self.makefile_path)

  def run(self, clean):
    record_software_state(self.sw_ver_file_cfg, self.sw_ver_file_out, DEPENDENCIES)
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
