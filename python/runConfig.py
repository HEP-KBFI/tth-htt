import argparse, datetime, re, logging

ALLOWED_CONDITION_KEYS = {
  'name' : 'process_name_specific',
  'cat'  : 'sample_category',
}

def condition_type(value):
  value_split = value.split(':')
  if len(value_split) != 2:
    raise argparse.ArgumentTypeError("You must provide the condition in the form of '<key>:<regex>'")

  key = value_split[0]
  regex = re.compile(value_split[1])

  if key not in ALLOWED_CONDITION_KEYS:
    raise argparse.ArgumentTypeError(
      "Allowed keys are: %s (corresponding to %s sample keys)" % (
        ', '.join(ALLOWED_CONDITION_KEYS),
        ', '.join(map(lambda k: ALLOWED_CONDITION_KEYS[k], ALLOWED_CONDITION_KEYS))
      )
    )
  return (key, regex)

def filter_samples(sample, condition):
  key = condition[0]
  regex = condition[1]

  sample_key = ALLOWED_CONDITION_KEYS[key]
  for sample_entry in sample.values():
    use_it = bool(regex.match(sample_entry[sample_key]))
    sample_entry['use_it'] = use_it
    logging_str = 'Enabling' if use_it else 'Disabling'
    logging.info('%s sample %s' % (logging_str, sample_entry[ALLOWED_CONDITION_KEYS['name']]))

  return sample

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

class tthAnalyzeParser(argparse.ArgumentParser):
  def __init__(
    self,
    era_choices = ('2017',),
    default_resubmission_limit = 4,
    max_help_position = 45,
    isAddMEM = False,
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
    self.add_argument('-r', '--resubmission-limit',
      type = int, dest = 'resubmission_limit', metavar = 'number',
      default = default_resubmission_limit, required = False,
      help = 'R|Maximum number of resubmissions',
    )
    self.add_argument('-R', '--disable-resubmission',
      dest = 'disable_resubmission', action = 'store_true', default = False,
      help = 'R|Disable resubmission (overwrites option -r/--resubmission-limit)',
    )
    run_parser.add_argument('-E', '--no-exec',
      dest = 'no_exec', action = 'store_true', default = False,
      help = 'R|Do not submit the jobs (ignore prompt)',
    )
    run_parser.add_argument('-A', '--auto-exec',
      dest = 'auto_exec', action = 'store_true', default = False,
      help = 'R|Automatically submit the jobs (ignore prompt)',
    )
    self.add_argument('-C', '--check-input-files',
      dest = 'check_input_files', action = 'store_true', default = False,
      help = 'R|Check each input file before generating the config files',
    )
    self.add_argument('-D', '--debug',
      dest = 'debug', action = 'store_true', default = False,
      help = 'R|Enable debugging flag in the analysis',
    )

  def add_modes(self, modes):
    self.add_argument('-m', '--mode',
      type = str, dest = 'mode', metavar = 'mode', default = None, required = True, choices = modes,
      help = 'R|Analysis type (choices: %s)' % tthAnalyzeParser.cat(modes),
    )

  def add_sys(self, sys_choices):
    self.add_argument('-s', '--systematics',
      type = str, dest = 'systematics', metavar = 'mode', choices = sys_choices, default = 'central',
      required = False,
      help = 'R|Systematic uncertainties (choices: %s)' % tthAnalyzeParser.cat(sys_choices),
    )

  def add_preselect(self):
    self.add_argument('-p', '--use-preselected',
      dest = 'use_preselected', action = 'store_true', default = False,
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

  def add_tau_id_wp(self, default_wp = ''):
    self.add_argument('-w', '--tau-id-wp',
      type = str, dest = 'tau_id_wp', metavar = 'WP', default = default_wp, required = False,
      help = 'R|Overwrite tau ID working point',
    )

  @staticmethod
  def cat(choices):
    return ', '.join(map(lambda choice: "'%s'" % str(choice), choices))