from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import DKEY_SCRIPTS, DKEY_LOGS, DKEY_SYNC
from tthAnalysis.HiggsToTauTau.jobTools import get_log_version, run_cmd, create_if_not_exists, record_software_state
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd
from tthAnalysis.HiggsToTauTau.common import logging

import os
import jinja2
import uuid
import sys
import collections
import re

DEPENDENCIES = [
    "",  # CMSSW_BASE/src
    "tthAnalysis/NanoAOD",
    "tthAnalysis/HiggsToTauTau",
    "TauAnalysisTools/TauTriggerSFs",
    "TauAnalysis/ClassicSVfit",
    "TauAnalysis/SVfitTF",
    "ttH_Htautau_MEM_Analysis",
    "tthAnalysis/tthMEM",
]

makeFileTemplate = '''
.DEFAULT_GOAL := all
SHELL := /bin/bash

all: {{ output_file }} validate

{{ output_file }}:{% for channel_output in channel_info %} {{channel_output}}{% endfor %}
\t{{ hadd_script }} &> {{ hadd_wrapper_log }}
\t{{ additional_cmds }}

run:{% for channel_output, channel_cmd in channel_info.items() %}
\t{{ channel_cmd['create'] }}
{%- endfor %}

{% for channel_output, channel_cmd in channel_info.items() %}
{{ channel_output }}: run
\t{{ channel_cmd['run'] }}
{% endfor %}

validate: {{ output_file }}
\tinspect_rle_numbers.py -i {{ output_dir }} -w {{ validate_channels }}

clean:
{%- for channel_output, channel_cmd in channel_info.items() %}
\t{{ channel_cmd['clean'] }}{% endfor %}
\trm -f {{ output_file }}

.PHONY: clean run validate

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
        check_output_files,
        running_method,
        isDebug,
        rle_select,
        with_mem,
        use_nonnominal,
        hlt_filter,
        tau_id_wp,
        tau_id,
        use_home,
        systematics_label,
        use_preselected,
        jet_cleaning,
        gen_matching,
        project_dir = os.path.join(os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau'),
        file_pattern = 'tthAnalyzeRun_%s.py',
        suffix = '',
      ):

    self.running_method     = running_method
    self.dry_run            = dry_run
    self.check_output_files = check_output_files
    self.use_home           = use_home
    executable_pattern = os.path.join(project_dir, 'test', file_pattern)

    self.config_dir = config_dir
    self.hadd_script_dir_path = os.path.join(self.config_dir, DKEY_SCRIPTS, DKEY_SYNC)
    self.hadd_log_dir_path    = os.path.join(self.config_dir, DKEY_LOGS,    DKEY_SYNC,)
    self.hadd_script_path         = os.path.join(self.hadd_script_dir_path, 'hadd_sync.py')
    self.hadd_log_wrapper_path    = os.path.join(self.hadd_log_dir_path,    'hadd_sync_wrapper.log')
    self.hadd_log_executable_path = os.path.join(self.hadd_log_dir_path,    'hadd_sync_executable.log')

    self.output_dir = output_dir
    final_output_dir = os.path.join(self.output_dir, DKEY_SYNC)
    self.final_output_file = os.path.join(final_output_dir, output_filename)

    common_args = "-v %s -e %s -s %s -y %s " % (version, era, ' '.join(systematics_label), use_home)
    if jet_cleaning:
      common_args += " -q %s " % jet_cleaning
    if gen_matching:
      common_args += " -g %s " % gen_matching
    additional_args = " -E"
    if self.dry_run:
      additional_args += " -d"
    if check_output_files:
      additional_args += " -C"
    if isDebug:
      additional_args += " -D"
    if rle_select:
      additional_args += " -S '%s'" % rle_select
    if use_nonnominal:
      additional_args += " -O"
    if hlt_filter:
      additional_args += " -H"
    if tau_id:
      additional_args += " -t %s" % tau_id
    if tau_id_wp:
      additional_args += " -w %s" % tau_id_wp
    if self.running_method:
      additional_args += " -R %s" % self.running_method

    mem_channels = [ '2lss_1tau', '3l', 'hh_bb2l' ]
    cr_channels = [ '3l', '4l' ]

    inclusive_args = '-v %s -e %s' % (version, era)

    inclusive_args += additional_args
    common_args    += additional_args

    create_if_not_exists(self.config_dir)
    create_if_not_exists(self.output_dir)

    channels_extended = collections.OrderedDict()
    for channel in channels:
      channels_extended[channel] = ''
      if channel in cr_channels:
        channels_extended[channel + 'ctrl'] = ' -c'

    self.channels_to_validate = []
    self.channel_info = {}
    for channel in channels_extended:
      if channel not in [ 'ttWctrl', 'ttZctrl', 'WZctrl', 'ZZctrl' ] and 'inclusive' not in channel:
        self.channels_to_validate.append(channel)

      input_file = os.path.join(final_output_dir, '%s.root' % channel)
      executable_channel = channel
      if channel.replace('ctrl', '') in cr_channels:
        executable_channel = channel.replace('ctrl', '')
      channel_script = executable_pattern % executable_channel

      channel_makefile = os.path.join(self.config_dir, 'Makefile_%s' % channel)
      channel_outlog   = os.path.join(self.config_dir, 'stdout_sync_%s.log' % channel)
      channel_errlog   = os.path.join(self.config_dir, 'stderr_sync_%s.log' % channel)
      channel_outlog_create = os.path.join(self.config_dir, 'stdout_sync_create_%s.log' % channel)
      channel_errlog_create = os.path.join(self.config_dir, 'stderr_sync_create_%s.log' % channel)
      channel_outlog, channel_errlog, channel_outlog_create, channel_errlog_create = get_log_version((
        channel_outlog, channel_errlog, channel_outlog_create, channel_errlog_create
      ))

      cmd_args = common_args if 'inclusive' not in channel else inclusive_args
      if 'inclusive' not in channel:
        cmd_args += " -p %s" % use_preselected
        cmd_args += ' -m %s' % ('sync_wMEM' if with_mem and channel in mem_channels else 'sync')
      cmd_args += channels_extended[channel]

      channel_cmd_create = '%s %s 2>%s 1>%s' % \
                           (channel_script, cmd_args, channel_errlog_create, channel_outlog_create)
      channel_cmd_run   = '$(MAKE) -j 5 -f %s all 2>%s 1>%s' % (channel_makefile, channel_errlog, channel_outlog)
      channel_cmd_clean = '$(MAKE) -f %s clean' % channel_makefile
      if self.running_method.lower() == "makefile":
        channel_cmd_run = "\n\t".join([
          "mkdir -p {}".format(channel),
          channel_cmd_run.replace('$(MAKE)', '$(MAKE) -C {}'.format(channel)),
          "rm -r {}".format(channel),
        ])
      self.channel_info[input_file] = {
        'create' : channel_cmd_create,
        'run'    : channel_cmd_run,
        'clean'  : channel_cmd_clean,
      }

    self.stdout_file_path = os.path.join(self.config_dir,      "stdout_sync.log")
    self.stderr_file_path = os.path.join(self.config_dir,      "stderr_sync.log")
    self.sw_ver_file_cfg  = os.path.join(self.config_dir,      "VERSION_sync.log")
    self.sw_ver_file_out  = os.path.join(self.output_dir, "VERSION_sync.log")
    self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out = get_log_version((
      self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out
    ))
    self.makefile_path = os.path.join(self.config_dir, 'Makefile_sync')
    if suffix:
      self.makefile_path += "_{}".format(suffix)

  def create(self):
    create_if_not_exists(self.hadd_log_dir_path)

    if self.running_method.lower() == 'sbatch':
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
        max_input_files_per_job = len(self.channel_info),
        dry_run                 = self.dry_run,
        use_home                = self.use_home,
        min_file_size           = -1,
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
      hadd_script_cmd = '{}{}'.format(
        'sleep 60\n\t' if self.running_method.lower() == 'makefile' else '',
        self.hadd_script_path
      )
      makeFileContents = jinja2.Template(makeFileTemplate).render(
        output_file       = self.final_output_file,
        channel_info      = self.channel_info,
        hadd_script       = hadd_script_cmd,
        hadd_wrapper_log  = self.hadd_log_wrapper_path,
        additional_cmds   = additional_cmds,
        validate_channels = ' '.join(self.channels_to_validate),
        output_dir        = self.output_dir,
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
    make_cmd = "make -f %s -j %d %s 2>%s 1>%s" % \
      (self.makefile_path, nof_parallel_jobs, target, self.stderr_file_path, self.stdout_file_path)
    if self.running_method.lower() == "makefile":
      run_dir = re.sub('^/home', '/scratch/1', self.config_dir)
      create_if_not_exists(run_dir)
      make_cmd = re.sub('^make', 'make -C {}'.format(run_dir), make_cmd)
    logging.info("Running the make command: %s" % make_cmd)
    run_cmd(make_cmd)
    logging.info("All done")
