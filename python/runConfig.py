from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter, STITCHING_OPTIONS
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import LEP_MVA_WPS

import argparse
import datetime
import re
import os.path

FILE_SUFFIX = 'file'
ALLOWED_CONDITION_KEYS = [ 'name', 'cat', 'path', 'dbs' ]
ALLOWED_CONDITION_KEYS.extend(['{}_{}'.format(key, FILE_SUFFIX) for key in ALLOWED_CONDITION_KEYS])

def positive_int_type(value):
  try:
    value_int = int(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not an integer: %s' % value)
  if value_int <= 0:
    raise argparse.ArgumentTypeError('Must be a positive integer: %d' % value_int)
  return value_int

def condition_type(value):
  value_split = value.split(':')
  if len(value_split) != 2:
    raise argparse.ArgumentTypeError("You must provide the condition in the form of '<key>:<regex>'")

  negate = False
  key = value_split[0]
  if key.endswith('_{}'.format(FILE_SUFFIX)):
    key = key[:-(len('_{}'.format(FILE_SUFFIX)))]
    input_path = value_split[1]
    if input_path.startswith('~'):
      input_path = input_path[1:]
      negate = True
    input_filename = os.path.abspath(input_path)
    if not os.path.isfile(input_filename):
      raise RuntimeError("No such file: %s" % input_filename)
    values = []
    with open(input_filename, 'r') as input_file:
      for line in input_file:
        line_stripped = line.rstrip()
        if not line_stripped:
          continue
        line_stripped_rfmt = '^{}$'.format(line_stripped)
        if line_stripped_rfmt not in values:
          values.append(line_stripped_rfmt)
    logging.info("Found {} entries from file {}".format(len(values), input_filename))
    regex_str = '({})'.format('|'.join(values))
  else:
    regex_str = value_split[1]
    if regex_str.startswith('~'):
      regex_str = regex_str[1:]
      negate = True
  regex = re.compile(regex_str)

  if key not in ALLOWED_CONDITION_KEYS:
    raise argparse.ArgumentTypeError("Allowed keys are: %s" % (', '.join(ALLOWED_CONDITION_KEYS)))
  return (key, regex, negate)

def filter_samples(sample, condition, force = False):
  key = condition[0]
  regex = condition[1]
  negate = condition[2]

  for sample_name, sample_entry in sample.items():
    if sample_name == 'sum_events': continue
    if key == 'path':
      use_it = bool(regex.match(sample_entry['local_paths'][0]['path']))
    elif key == 'dbs':
      use_it = bool(regex.match(sample_name))
    elif key == 'name':
      use_it = bool(regex.match(sample_entry['process_name_specific']))
    elif key == 'cat':
      use_it = bool(regex.match(sample_entry['sample_category']))
    else:
      raise RuntimeError("Invalid key: %s" % key)
    if negate:
      use_it = not use_it
    if force:
      sample_entry['use_it'] = use_it
    else:
      sample_entry['use_it'] &= use_it
    logging_str = 'Enabling' if sample_entry['use_it'] else 'Disabling'
    process_name = sample_entry["process_name_specific"]
    logging.info('%s sample %s' % (logging_str, process_name))

  return sample

class tthAnalyzeParser(argparse.ArgumentParser):
  def __init__(
    self,
    era_choices               = ('2016', '2017', '2018'),
    default_num_parallel_jobs = 16,
    max_help_position         = 45,
    isAddMEM                  = False,
  ):
    super(tthAnalyzeParser, self).__init__(
      formatter_class = lambda prog: SmartFormatter(prog, max_help_position = max_help_position)
    )
    self.add_argument('-e', '--era',
      type = str, dest = 'era', metavar = 'era', choices = era_choices, default = None,
      required = True,
      help = 'R|Era of data/MC (choices: %s)' % tthAnalyzeParser.cat(era_choices),
    )
    self.add_argument('-v', '--version',
      type = str, dest = 'version', metavar = 'version', default = None, required = True,
      help = 'R|Analysis version (e.g. %s)' % datetime.date.today().strftime('%Y%b%d'),
    )
    self.add_argument('-f', '--filter',
      type = condition_type, dest = 'filter', metavar = 'condition', default = None, required = False,
      help = 'R|Filter samples based on condition <key>:<regex> (allowed keys: %s)' % \
             (', '.join(ALLOWED_CONDITION_KEYS))
    )
    run_parser = self.add_mutually_exclusive_group()
    self.add_argument('-d', '--dry-run',
      dest = 'dry_run', action = 'store_true', default = False,
      help = 'R|Do not submit the jobs, just generate the necessary shell scripts' if isAddMEM else \
             'R|Run addMEM without actually computing the MEM score',
    )
    running_method_choices = [ 'sbatch', 'makefile' ]
    self.add_argument('-R', '--running-method',
      type = str, dest = 'running_method', metavar = 'method', default = 'sbatch', required = False,
      choices = running_method_choices,
      help = 'R|Running method (choices: %s)' % tthAnalyzeParser.cat(running_method_choices),
    )
    self.add_argument('-J', '--num-parallel-jobs',
      type = positive_int_type, dest = 'num_parallel_jobs', metavar = 'number', required = False,
      default = default_num_parallel_jobs,
      help = 'R|Number of parallel makefile targets',
    )
    run_parser.add_argument('-E', '--no-exec',
      dest = 'no_exec', action = 'store_true', default = False,
      help = 'R|Do not submit the jobs (ignore prompt)',
    )
    run_parser.add_argument('-A', '--auto-exec',
      dest = 'auto_exec', action = 'store_true', default = False,
      help = 'R|Automatically submit the jobs (ignore prompt)',
    )
    self.add_argument('-C', '--not-check-output-files',
      dest = 'not_check_input_files', action = 'store_true', default = False,
      help = 'R|Do not check each output file while generating the config files',
    )
    self.add_argument('-D', '--debug',
      dest = 'debug', action = 'store_true', default = False,
      help = 'R|Enable debugging flag in the analysis',
    )
    self.add_argument('-K', '--keep-logs',
      dest = 'keep_logs', action ='store_true', default = False,
      help = 'R|Keep all logs',
    )


  def add_files_per_job(self, files_per_job = 20):
    self.add_argument('-j', '--files-per-job',
      type = str, dest = 'files_per_job', metavar = 'number', default = str(files_per_job),
      help = 'R|Number of input files per job',
    )

  def add_modes(self, modes, default = None):
    if type(default) == str:
      assert(default in modes)
      required = False
    else:
      required = True
    self.add_argument('-m', '--mode',
      type = str, dest = 'mode', metavar = 'mode', default = default, required = required, choices = modes,
      help = 'R|Analysis type (choices: %s)' % tthAnalyzeParser.cat(modes),
    )

  def add_sideband(self, default_choice = 'disabled'):
    sideband_choices = [ 'disabled', 'enabled', 'only' ]
    self.add_argument('-B', '--sideband',
      type = str, dest = 'sideband', metavar = 'choice', default = default_choice, required = False,
      choices = sideband_choices,
      help = 'R|Sideband (choices: %s)' % tthAnalyzeParser.cat(sideband_choices),
    )

  def add_sys(self, sys_choices, default_choice = 'central'):
    self.add_argument('-s', '--systematics',
      type = str, nargs = '+', dest = 'systematics', metavar = 'mode', choices = sys_choices, default = [ default_choice ],
      required = False,
      help = 'R|Systematic uncertainties (choices: %s)' % tthAnalyzeParser.cat(sys_choices),
    )

  def add_preselect(self, use_preselected = True):
    type_lambda = lambda s: s.lower() in [ 'true', 't', 'yes', '1' ]
    self.add_argument('-p', '--use-preselected',
      type = type_lambda, dest = 'use_preselected', metavar = 'option',
      default = use_preselected, required = False,
      help = 'R|Use Ntuples which contains preselected events',
    )

  def add_rle_select(self):
    self.add_argument('-S', '--rle-select',
      type = str, dest = 'rle_select', metavar = 'pattern', default = '', required = False,
      help = 'R|Regular expression to the path of RLE text files',
    )

  def add_nonnominal(self):
    self.add_argument('-O', '--original-central',
      dest = 'original_central', action = 'store_true', default = False,
      help = 'R|Use original central (i.e. non-nominal) values for jet/MET pt & mass/phi',
    )

  def add_tau_id_wp(self, default_wp = '', required = False, choices = []):
    argparse_args = {
      'type'     : str,
      'dest'     : 'tau_id_wp',
      'metavar'  : 'tau ID WP',
      'default'  : default_wp,
      'required' : required,
      'help'     : 'R|Overwrite tau ID working point (choices: %s)' % tthAnalyzeParser.cat(choices),
    }
    if choices:
      argparse_args['choices'] = choices
    self.add_argument('-w', '--tau-id-wp', **argparse_args)
 
  def add_tau_id(self, default_id = 'deepVSj'):
    choices = [ 'dR03mva', 'deepVSj' ]
    self.add_argument('-t', '--tau-id',
      type = str, dest = 'tau_id', metavar = 'tau ID', default = default_id, required = False, choices = choices, 
      help = 'R|Tau ID discriminant (choices: %s)' % tthAnalyzeParser.cat(choices),
    )

  def add_hlt_filter(self):
    self.add_argument('-H', '--hlt-filter',
      dest = 'hlt_filter', action = 'store_true', default = False,
      help = 'R|Apply HLT filter',
    )

  def add_use_home(self, use_home = False):
    self.add_argument('-y', '--use-home',
      type = lambda s: s.lower() in ['true', 't', 'yes', '1'], dest = 'use_home', metavar = 'option',
      default = use_home, required = False,
      help = 'R|Use /home instead of /scratch for SLURM jobs', 
    )

  def add_lep_mva_wp(self, default_wp = ''):
    if default_wp:
      assert(default_wp in LEP_MVA_WPS)
    self.add_argument('-L', '--lepton-mva-wp',
      type = str, dest = 'lep_mva_wp', metavar = 'lepton MVA WP', choices = list(LEP_MVA_WPS.keys()),
      required = not bool(default_wp), default = default_wp,
      help = 'R|Lepton MVA WP (choices: %s)' % tthAnalyzeParser.cat(list(LEP_MVA_WPS.keys())),
    )

  def add_disableFRwgts(self):
    self.add_argument('-disableFRwgts', '--disable-FRwgts',
      dest = 'disableFRwgts', action = 'store_true', default = False,
      help = 'R|Disable FR weights for Fakes Application region',
    )

  def add_lep_useTightChargeCut(self, default_option = ''):
    self.add_argument('-L_useTightChargeCut', '--lepton-useTightChargeCut',
      type = str, dest = 'lep_useTightChargeCut', metavar = 'lepton Tight Charge cut option', choices = ['True', 'False'],
      required = not bool(default_option), default = default_option,
      help = 'R|Flag to use Lepton tight charge cut',
    )

  def add_lep_useSFCor(self, default_option = ''):
    self.add_argument('-L_useSFCor', '--lepton-useSFCor',
      type = str, dest = 'lep_useSFCor', metavar = 'lepton SF correction', choices = ['True', 'False'],
      required = not bool(default_option), default = default_option,
      help = 'R|Flag to use Lepton SF correction derived in hh_multilepton analysis',
    )

  def add_lep_useDifferentMVACutForLepton3(self, default_option = ''):
    self.add_argument('-L_useDifferentMVACutForLepton3', '--lepton-useDifferentMVACutForLepton3',
      type = str, dest = 'lep_useDifferentMVACutForLepton3', metavar = 'Use different MVA cut for W->lepton in WZ', choices = ['True', 'False'],
      required = not bool(default_option), default = default_option, 
      help = 'R|Use different lepton MVA cut (that are provided using the other arguments) for lepton3',
    )

  def add_lep_mva_cut_mu_forLepton3(self, default_wp = ''):
    self.add_argument('-L_mva_cut_mu_forLepton3', '--lepton-mva-cut-mu-forLepton3',
      type = str, dest = 'lep_mva_cut_mu_forLepton3', metavar = 'lepton mva cut mu for lepton3', #choices = list(LEP_MVA_WPS.keys()),
      required = not bool(default_wp), default = '0.5',
      help = 'R|Lepton mva cut mu for lepton3 (choices: 0.5)'
    )

  def add_lep_mva_cut_e_forLepton3(self, default_wp = ''):
    self.add_argument('-L_mva_cut_e_forLepton3', '--lepton-mva-cut-e-forLepton3',
      type = str, dest = 'lep_mva_cut_e_forLepton3', metavar = 'lepton mva cut e for lepton3', #choices = list(LEP_MVA_WPS.keys()),
      required = not bool(default_wp), default = '0.3',
      help = 'R|Lepton mva cut e for lepton3 (choices: 0.3)'
    )

  def add_ele_ConvsCR(self, default_option = ''):
    option_choices = ['disable_nLostHits_convsVeto', 'invert_nLostHits', 'invert_convsVeto', 'invert_eitherOf_convsVeto_nLostHits', 'invert_both_convsVeto_nLostHits']    
    self.add_argument('-ele_ConvsCR', '--ele-ConvsCR-CutOption',
      type = str, dest = 'ele_ConvsCR', metavar = 'Conversion cuts for electrons in conversion_CR', choices = option_choices,
      required = not bool(default_option), default = default_option,
      help = 'R|Conversion cuts for electrons in conversion_CR (choices: %s)' % tthAnalyzeParser.cat(option_choices),
    )
        
  def add_jet_cleaning(self, default_jet_cleaning = 'by_index'):
    choices = [ 'by_index', 'by_dr' ]
    self.add_argument('-q', '--jet-cleaning',
      type = str, dest = 'jet_cleaning', metavar = 'method', default = default_jet_cleaning, required = False, choices = choices,
      help = 'R|Jet cleaning method (choices: %s)' % tthAnalyzeParser.cat(choices),
    )

  def add_gen_matching(self, default_gen_matching = 'by_index'):
    choices = [ 'by_index', 'by_dr' ]
    self.add_argument('-g', '--gen-matching',
      type = str, dest = 'gen_matching', metavar = 'method', default = default_gen_matching, required = False, choices = choices,
      help = 'R|Method of gen matching (choices: %s)' % tthAnalyzeParser.cat(choices),
    )

  def add_control_region(self):
    self.add_argument('-c', '--control-region',
      dest = 'control_region', action = 'store_true', default = False,
      help = 'R|Run control region instead',
    )

  def do_MC_only(self):
    self.add_argument('-M', '--MC-only',
        dest = 'MC_only', action = 'store_true', default = False,
        help = 'M|do not run data',
    )

  def enable_regrouped_jerc(self, default = 'both', include_ak8 = False):
    choices = [ 'both', 'jes', 'jer' ]
    if include_ak8:
      choices.extend([ 'jes_ak8', 'jes_all', 'all' ])
    assert(default in choices)
    self.add_argument('-G', '--enable-regrouped-jerc',
      type = str, dest = 'enable_regrouped_jerc', metavar = 'choice', default = '', const = default, choices = choices, nargs = '?', action = 'store',
      help = 'R|Enable regrouped JES/JER/both',
    )

  def add_split_trigger_sys(self, default = 'both'):
    choices = [ 'yes', 'no', 'both' ]
    assert(default in choices)
    self.add_argument('-T', '--split-trigger-sys',
      type = str, dest = 'split_trigger_sys', metavar = 'choice', default = default, required = False, choices = choices,
      help = 'R|Split trigger systematic uncertainties (choices: %s)' % tthAnalyzeParser.cat(choices),
    )

  def add_stitched(self, choices = None):
    if choices:
      assert(all(choice in STITCHING_OPTIONS for choice in choices))
    self.add_argument('-u', '--use-stitched',
      type = str, dest = 'use_stitched', metavar = 'process', default = choices, required = False, nargs = '+',
      choices = STITCHING_OPTIONS,
      help = 'R|Load stitched samples (choices: %s)' % tthAnalyzeParser.cat(STITCHING_OPTIONS),
    )

  def add_blacklist(self, default = True):
    type_lambda = lambda s: s.lower() in [ 'true', 't', 'yes', '1' ]
    self.add_argument('-k', '--use-blacklist',
      type = type_lambda, dest = 'use_blacklist', metavar = 'option', default = default, required = False,
      help = 'R|Apply blacklist', # see https://github.com/HEP-KBFI/tth-htt/issues/175
    )

  @staticmethod
  def cat(choices):
    return ', '.join(map(lambda choice: "'%s'" % str(choice), choices))
