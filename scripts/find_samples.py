#!/usr/bin/env python

# In order to compute the integrated luminosity, follow these links:
#
# https://cms-service-lumi.web.cern.ch/cms-service-lumi/brilwsdoc.html
# https://github.com/CMS-LUMI-POG/Normtags
#
# To summarize, in order to find integrated luminosity of datasets, triggers, and whatnot, direct
# access to CERN servers is needed. These numbers can be gathered from off-site servers as well,
# but this requires the off-site user to set up a python environment called brilconda (a derivative
# of anaconda framework that supports BRIL tools) and maintain a live ssh session while calling any
# of the BRIL tools. The second component is the normtag file, which is enables to use calibration
# information / apply correction functions on the measured instantaneous luminosity, which of course
# depends on the choice of the luminometer. The recommended normtag for 2017 data is
# normtag_PHYSICS.json: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
#
# At the time of writing this comment, both ReReco and PromptReco golden JSONs w/ normtag_PHYSICS.json
# reproduce the same results as reported in https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/761.html:
#
# > with golden JSON:   43.925/fb delivered, 41.298/fb recorded
# > ...
# > The associated uncertainty on the luminosity is *2.4%*. [..]
#
# The recorded integrated luminosity coincides with the advertised figure of preliminary validated
# *offline* integrated luminosity of 41.30/fb (https://twiki.cern.ch/twiki/bin/view/CMS/DataQuality);
# dropping the normtag reproduces the advertised figure of preliminary validated *online* integrated
# luminosity of 41.86/fb which coincides with the recorded integrated luminosity for both ReReco and
# PromptReco golden JSONs. Both figures (taken from plots) quoted on this page are referred to as
# ,,certified as good for physics analysis during stable beams'' and ,,the operational losses [..]
# are accounted separately''.

#TODO: add support for eos and XRD protocols
#TODO: disentangle the computation of era-based integrated luminosity and DAS queries on data samples

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd, human_size, create_if_not_exists

import re
import datetime
import collections
import jinja2
import argparse
import os
import sys
import json
import itertools
import ast
import getpass
import multiprocessing
import signal
import ROOT

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

class Version:
  def __init__(self, version):
    version_split = version.split('_')
    self.major    = int(version_split[0])
    self.minor    = int(version_split[1])
    self.subminor = int(version_split[2])
    self.is_pre_or_patch = 0
    self.pre_or_patch_version = 0

    version_key = 'ver'
    pre_regex = re.compile(r'pre(?P<%s>[0-9]+)' % version_key)
    patch_regex = re.compile(r'patch(?P<%s>[0-9]+)' % version_key)
    cand_regex = re.compile(r'cand(?P<%s>[0-9]+)' % version_key)

    if len(version_split) > 3:
      pre_or_patch_str = version_split[3]
      if 'pre' in pre_or_patch_str:
        self.is_pre_or_patch = -1
        pre_match = pre_regex.match(pre_or_patch_str)
        if not pre_match:
          raise ValueError("Unparsable version: '%s'" % version)
        self.pre_or_patch_version = pre_match.group(version_key)
      elif 'patch' in pre_or_patch_str:
        self.is_pre_or_patch = 1
        patch_match = patch_regex.match(pre_or_patch_str)
        if not patch_match:
          raise ValueError("Unparsable version: '%s'" % version)
        self.pre_or_patch_version = patch_match.group('ver')
      elif 'cand' in pre_or_patch_str:
        self.is_pre_or_patch = -1 # Let's assume it's a ,,pre''
        cand_match = cand_regex.match(pre_or_patch_str)
        if not cand_match:
          raise ValueError("Unparsable version: '%s'" % version)
        self.pre_or_patch_version = cand_match.group('ver')
      else:
        raise ValueError("Unparsable version: '%s'" % version)

  def passes(self, other):
    if self.major >= other.major and self.minor >= other.minor and self.subminor >= other.subminor \
      and self.is_pre_or_patch >= other.is_pre_or_patch:
      if self.is_pre_or_patch == other.is_pre_or_patch:
        return self.pre_or_patch_version >= other.pre_or_patch_version
      return True
    return False

METADICT_HEADER = '''from collections import OrderedDict as OD

# file generated at {{ date }} with the following command:
# {{ command }}

meta_dictionary = OD()

{% if is_mc %}
### event sums

sum_events = { {% for sum_event_arr in sum_events %}
  ("{{ sum_event_arr|join('", "') }}"),
{%- endfor %}
}


{% endif %}
'''

METADICT_FOOTER = '''

# event statistics by sample category:
{%- for sample_category, event_count in event_statistics.items() %}
# {{ sample_category }} {{ event_count }}
{%- endfor %}

'''

METADICT_TEMPLATE_DATA = '''meta_dictionary["{{ dataset_name }}"] =  OD([
  ("crab_string",           "{{ crab_string }}"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "{{ process_name_specific }}"),
  ("nof_db_events",         {{ nof_db_events }}),
  ("nof_db_files",          {{ nof_db_files }}),
  ("fsize_db",              {{ fsize_db }}),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             {{ run_range }}),
  ("golden_run_range",      {{ golden_run_range }}),
  ("comment",               "{{ comment }}"),
])

'''

METADICT_TEMPLATE_MC = '''meta_dictionary["{{ dataset_name }}"] =  OD([
  ("crab_string",           "{{ crab_string }}"),
  ("sample_category",       "{{ sample_category }}"),
  ("process_name_specific", "{{ specific_name }}"),
  ("nof_db_events",         {{ nof_db_events }}),
  ("nof_db_files",          {{ nof_db_files }}),
  ("fsize_db",              {{ fsize_db }}),
  ("xsection",              {{ xs }}),
  ("use_it",                {{ use_it }}),
  ("genWeight",             True),
  ("comment",               "{{ comment }}"),
])

'''

DATA_SAMPLES_ALL = [
  'SingleElectron',
  'SingleMuon',
  'DoubleEG',
  'DoubleMuon',
  'MuonEG',
  'Tau',
]
DATA_SAMPLES_DEFAULT = [ data_sample for data_sample in DATA_SAMPLES_ALL if data_sample != 'Tau' ]

LUMI_UNITS = [ '/fb', '/pb', '/nb', '/ub' ]

DATA_TIER     = 'MINIAOD'
MC_TIER       = '%sSIM' % DATA_TIER
PRIVATE_TIER  = 'USER'
AQC_KEY       = 'cat'
PDS_KEY       = 'data'

DASGOCLIENT_QUERY_COMMON     = "dasgoclient -query='        dataset=%s          | grep dataset.%s' -unique | grep -v '^\\['"
DASGOCLIENT_QUERY_ANY_STATUS = "dasgoclient -query='dataset dataset=%s status=* | grep dataset.%s' -unique | grep -v '^\\['"
DASGOCLIENT_QUERY_RELEASE    = "dasgoclient -query='release dataset=%s' -unique"
DASGOCLIENT_QUERY_RUNLUMI    = "dasgoclient -query='run,lumi dataset=%s' -unique"

PRIVATE_REGEX = re.compile(r'/[\w\d_-]+/[\w\d_-]+/%s' % PRIVATE_TIER)
MC_REGEX      = re.compile(r'/[\w\d_-]+/[\w\d_-]+/%s' % MC_TIER)
DATASET_REGEX = re.compile("^/(.*)/(.*)/[0-9A-Za-z]+$")

def get_crab_string(dataset_name, paths):
  paths_ = []
  for path in paths:
    if os.path.isfile(path):
      with open(path, 'r') as f:
        for line in f:
          path_candidate = line.rstrip('\n')
          if not os.path.isdir(path_candidate):
            raise RuntimeError('Not a directory: %s' % path_candidate)
          paths_.append(path_candidate)
    else:
      paths_.append(path)
  for path in paths_:
    version = os.path.basename(path)
    dataset_match = DATASET_REGEX.match(dataset_name)
    requestName = '%s_%s__%s' % (version, dataset_match.group(1), dataset_match.group(2))
    primary_name = dataset_name.split('/')[1]
    full_path = os.path.join(path, primary_name, requestName)
    if os.path.isdir(full_path):
      return requestName
    # is a hack... I cannot explain where this magic number '152' comes from but it works
    if len(requestName) > 152:
      requestName = requestName[:152]
    full_path = os.path.join(path, primary_name, requestName)
    if os.path.isdir(full_path):
      return requestName
  return ''

def convert_date(date):
  return datetime.datetime.fromtimestamp(int(date)).strftime('%Y-%m-%d %H:%M:%S')

def convert_cmssw_versions(cmssw_list):
  return ','.join(set([
    re.match(r'.*\"(?P<ver>.*)\".*', cmssw_ver).group('ver')[len('CMSSW')+1:]
    for cmssw_ver in cmssw_list.split(',')
  ]))

def id_(x): # identity function
  return x

def get_golden_runlumi(lumimask_location):
  with open(lumimask_location, 'r') as lumimask_file:
    try:
      golden_runlumi_json = json.load(lumimask_file)
    except json.decoder.JSONDecodeError:
      raise ValueError("File %s is not a JSON file" % lumimask_file)
  if not golden_runlumi_json:
    raise ValueError("No JSON-formatted infromation was loaded from %s" % lumimask_file)

  golden_runlumi = collections.OrderedDict(
    (
      int(run),
      list(itertools.chain(*[
        # Expand the luminosity ranges
        # For instance, if the luminosity ranges are
        # [[1, 7], [40, 45]]
        # then this is expanded and flattened into
        # [1, 2, 3, 4, 5, 6, 7, 40, 41, 42, 43, 44, 45]
        # We assume that both endpoints of the luminosity range are included
        list(range(lumi_range[0], lumi_range[1] + 1)) for lumi_range in lumi_ranges
      ]))
    ) for run, lumi_ranges in golden_runlumi_json.items()
  )
  return golden_runlumi

def get_runlumi_data(runlumi_query_out):
  lines = runlumi_query_out.rstrip('\n').split('\n')
  lines_split = [ line.split() for line in lines ]
  runlumi_data = collections.OrderedDict()
  for line in lines_split:
    run = int(line[0])
    lumis = list(sorted(ast.literal_eval(line[1])))
    runlumi_data[run] = lumis
  return runlumi_data

def split_into_ranges(flat_list):
  # The input is a list of numbers, e.g. [4, 5, 6, 10, 11, 13, 14, 15]
  # which is split into lists that represent sub-ranges, which in our example should be
  # [[4, 6], [10, 11], [13, 14, 15]]
  # Notice that we assume that the endpoints of both ranges are included (which I hope is the case
  # in the gloden JSON files)

  # First, let's find at which points in the list the sequentiality is broken
  # In our example, the program below should return [2, 4], b/c the 3rd and 4th (5th and 6th)
  # element in the list differ by more than one
  split_indices = [ i for i in range(len(flat_list) - 1) if flat_list[i + 1] != flat_list[i] + 1 ]

  # No let's construct the sub-range format by going through the break points one-by-one:
  # prev_idx = 0, curr_idx = 2,
  # prev_idx = 3, curr_idx = 4
  prev_idx = 0
  split_ranges = []
  for curr_idx in split_indices:
    split_ranges.append([flat_list[prev_idx],flat_list[curr_idx]])
    prev_idx = curr_idx + 1
  # Here we have to consider the final ,,tail'', which spans the index range 5..7 (included)
  # Notice that if the input list is fully sequential, the split_ranges variable remains empty,
  # and prev_idx remains 0, which means that the full range is concentrated into a single range here
  split_ranges.append([flat_list[prev_idx],flat_list[len(flat_list) - 1]])

  # Make sure that we can recover the full flat input list from split_ranges
  # (cf. get_golden_runlumi for more)
  flat_list_to_test = list(itertools.chain(
    *[list(range(split_range[0], split_range[1] + 1)) for split_range in split_ranges]
  ))
  if flat_list_to_test != flat_list:
    assert(0)

  return split_ranges

def get_data_golden(runlumi_data, golden_runlumi):
  data_runs   = set(runlumi_data.keys())
  golden_runs = set(golden_runlumi.keys())
  common_runs = list(sorted(list(data_runs & golden_runs)))

  # We want to check the intersection of each individual common run, because it might be the case
  # that the first or last run do not have any common luminosity blocks and is therefore not
  # part of the golden run. For instance, if a common run, say 304199 has golden range of [10, 18]
  # and the PD also contains run 304199 but only the luminosity blocks [2, 5], then this run should
  # be excluded from the golden runs since there's no overlap in their luminosity range.
  # If such runs happen to be first and/or last in the common runs, then the golden run range will
  # be different from the case where we only find the common run ranges.
  golden_data_runs = collections.OrderedDict()
  for run in common_runs:
    lumi_range_intersection = list(sorted(list(set(runlumi_data[run]) & set(golden_runlumi[run]))))
    if lumi_range_intersection:
      golden_data_runs[run] = split_into_ranges(lumi_range_intersection)
  return golden_data_runs

def get_integrated_lumi(dataset_name, data_golden, brilcalc_path, normtag, units, tmp_filename):
  if data_golden:
    with open(tmp_filename, 'w') as f:
      f.write(json.dumps(data_golden))

  brilcalc_cmd = '{brilcalc_path} lumi -c offsite -i {golden_json} {normtag} -u {units} --output-style=csv'.format(
    brilcalc_path = brilcalc_path,
    golden_json   = tmp_filename,
    normtag       = '--normtag %s' % normtag if normtag else '',
    units         = units,
  )
  brilcalc_out, brilcalc_err = run_cmd(brilcalc_cmd, do_not_log = True, return_stderr = True)
  if brilcalc_err:
    raise ValueError("brilcalc return an error: %s" % brilcalc_err)

  brilcalc_out_split = brilcalc_out.rstrip('\n').split('\n')
  summary_idx = brilcalc_out_split.index('#Summary:')
  if summary_idx < 0:
    raise ValueError("brilcalc didn't return any summary: %s" % brilcalc_out)

  # We only need two lines in this summary: the header and the actual values in the table
  lines = [line.lstrip('#').split(',') for line in brilcalc_out_split[summary_idx + 1:summary_idx + 3]]

  # Make sure that both lines contain the same amount of columns (split by a comma)
  nof_cols_first  = len(lines[0])
  nof_cols_second = len(lines[1])
  if nof_cols_first != nof_cols_second:
    raise ValueError("brilcalc returned uneven amount of columns in the summary: %s" % brilcalc_out)

  results = { lines[0][i] : lines[1][i] for i in range(nof_cols_first) }

  # Cleanup
  if data_golden:
    if os.path.isfile(tmp_filename):
      os.remove(tmp_filename)

  return dataset_name, results

def get_nof_events(dataset_private_file):
  if not dataset_private_file.lower().endswith('.root'):
    return -1 # Not a ROOT file
  dataset_private_file_ptr = ROOT.TFile.Open(dataset_private_file, 'read')
  if not dataset_private_file_ptr:
    return -2 # Not a valid ROOT file
  dataset_private_tree_ptr = dataset_private_file_ptr.Get('Events')
  if not dataset_private_tree_ptr:
    return -3 # No TKey named Events
  if not hasattr(dataset_private_tree_ptr, 'GetEntries'):
    return -4 # Not a valid TTree object
  nof_entries = dataset_private_tree_ptr.GetEntries()
  dataset_private_file_ptr.Close()
  del dataset_private_file_ptr
  del dataset_private_tree_ptr
  return nof_entries

def scan_private(dataset_private_path):
  fs_results = {
    'size'                   : 0,
    'nfiles'                 : 0,
    'nevents'                : 0,
    'last_modification_date' : 0,
  }
  for filename in os.listdir(dataset_private_path):
    dataset_private_file = os.path.join(dataset_private_path, filename)
    nof_events = get_nof_events(dataset_private_file)
    if nof_events < 0:
      # Not a valid ROOT file
      continue
    fs_results['size'] += os.path.getsize(dataset_private_file)
    fs_results['nevents'] += nof_events
    fs_results['nfiles'] += 1
    current_mtime = int(os.stat(dataset_private_file).st_mtime)
    if current_mtime > fs_results['last_modification_date']:
      fs_results['last_modification_date'] = current_mtime
  # Convert the results to strings
  for fs_key in fs_results:
    fs_results[fs_key] = str(fs_results[fs_key])
  fs_results['last_modification_date'] = convert_date(fs_results['last_modification_date'])
  return fs_results

lumi_results = {}

def update_lumi_results(results):
  lumi_results[results[0]] = results[1]

if __name__ == '__main__':

  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'path', required = False,
    help = 'R|Input file containing MC DBS names (one per line)',
  )
  parser.add_argument('-m', '--metadict',
    type = str, dest = 'metadict', metavar = 'path', default = 'metaDict.py', required = False,
    help = 'R|Output path of the Python meta-dictionary',
  )
  parser.add_argument('-d', '--datasets',
    type = str, dest = 'dataset', metavar = 'path', default = 'datasets.txt', required = False,
    help = 'R|Output path of the dataset list (valid if -i/--input not provided)',
  )
  parser.add_argument('-s', '--sum-events',
    type = str, dest = 'sum_events', metavar = 'file', default = '', required = False,
    help = 'R|File containing list of samples that cover the same phase space (one such list per line)',
  )
  parser.add_argument('-c', '--crab-string',
    type = str, nargs = '+', dest = 'crab_string', metavar = 'path', default = [], required = False,
    help = 'R|Fill CRAB string',
  )
  parser.add_argument('-r', '--run',
    type = str, dest = 'run', metavar = 'run', default = '2017', required = False,
    help = 'R|Data collection period',
  )
  parser.add_argument('-p', '--primary-datasets',
    type = str, nargs = '+', dest = 'primary_datasets', metavar = 'PD', choices = DATA_SAMPLES_ALL,
    default = DATA_SAMPLES_DEFAULT, required = False,
    help = 'R|List of PDs to be considered (choices: %s)' % \
           (', '.join(map(lambda choice: "'%s'" % choice, DATA_SAMPLES_ALL))),
  )
  parser.add_argument('-g', '--golden-json',
    type = str, dest = 'golden_json', metavar = 'file', required = False,
    default = os.path.join(
      os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'NanoAOD', 'data',
      'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt'
    ),
    help = 'R|Path to the golden lumimask file in JSON format',
  )
  parser.add_argument('-n', '--normtag',
    type = str, dest = 'normtag', metavar = 'file', required = False,
    default = 'normtag_PHYSICS.json',
    help = 'R|Normtag to be used (use empty string if no normtag needed)',
  )
  parser.add_argument('-N', '--normtag-dir',
    type = str, dest = 'normtag_dir', metavar = 'path', required = False,
    default = os.path.join(os.path.expanduser('~'), 'Normtags'),
    help = 'R|Path to the normtag repository',
  )
  parser.add_argument('-B', '--brilconda-dir',
    type = str, dest = 'brilconda_dir', metavar = 'path', required = False,
    default = os.path.join(os.path.expanduser('~'), 'brilconda'),
    help = 'R|Root directory of the brilconda setup',
  )
  parser.add_argument('-u', '--units',
    type = str, dest = 'units', metavar = 'unit', choices = LUMI_UNITS, required = False,
    default = '/fb',
    help = 'R|Units of the integrated luminosity (choices: %s)' % \
           (', '.join(map(lambda choice: "'%s'" % choice, LUMI_UNITS))),
  )
  parser.add_argument('-v', '--cmssw-version',
    type = str, dest = 'version', metavar = 'version', default = '9_4_0', required = False,
    help = 'R|Minimum required CMSSW version',
  )
  parser.add_argument('-C', '--custom-strings',
    type = str, nargs = '+', dest = 'custom_strings', metavar = 'str', default = [], required = False,
    help = 'R|Custom string(s) a dataset name must contain',
  )
  parser.add_argument('-t', '--tmp-dir',
    type = str, dest = 'tmp_dir', metavar = 'path', required = False,
    default = os.path.join('/tmp', getpass.getuser()),
    help = 'R|Directory where the golden era run & lumisections are temporarily stored',
  )
  parser.add_argument('-l', '--luminosity',
    dest = 'luminosity', action = 'store_true', default = False, required = False,
    help = 'R|Compute integrated luminosity for each selected PD',
  )
  parser.add_argument('-V', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  has_dasgoclient = run_cmd(
    'which dasgoclient 2>/dev/null | wc -l', do_not_log = True, return_stderr = False
  )
  if has_dasgoclient.rstrip('\n') != "1":
    raise ValueError("dasgoclient not available! Set up your 94x environment")
  has_voms_proxy = run_cmd(
    'which voms-proxy-info 2>/dev/null | wc -l', do_not_log = True, return_stderr = False
  )
  if has_voms_proxy.rstrip('\n') != "1":
    raise ValueError("voms-proxy-* not available! Set up your 94x environment")

  min_voms_proxy_timeleft_minutes = 30
  voms_proxy_timeleft = int(run_cmd(
    'voms-proxy-info --timeleft', do_not_log = True, return_stderr = False
  ).rstrip('\n'))
  if voms_proxy_timeleft < 60 * min_voms_proxy_timeleft_minutes:
    raise ValueError(
      "proxy not open at least %i minutes to run this script; "         \
      "update your proxy with: voms-proxy-init -voms cms -valid 1:00" % \
      min_voms_proxy_timeleft_minutes
    )

  mc_input = args.input
  required_cmssw_version_str = args.version
  required_cmssw_version = Version(required_cmssw_version_str)
  verbose = args.verbose
  crab_string = args.crab_string

  primary_datasets = args.primary_datasets
  DATA_GREP_STR = '\\|'.join(map(lambda sample: '^/%s/' % sample, primary_datasets))
  DATA_PIPED = '|'.join(primary_datasets)
  MAX_DATA_SAMPLE_LEN = max(map(len, primary_datasets))
  DATA_QUERY = "dasgoclient -query='dataset dataset=/*/*%s*/{data_tier}' | grep '{data_str}' | sort".format(
    data_tier = DATA_TIER,
    data_str  = DATA_GREP_STR,
  )

  lumimask_location = args.golden_json
  if not os.path.isfile(lumimask_location):
    raise ValueError("No such file: %s" % lumimask_location)
  golden_runlumi = get_golden_runlumi(lumimask_location)

  compute_lumi = args.luminosity
  normtag = args.normtag
  normtag_path = os.path.join(args.normtag_dir, normtag) if normtag else ''
  brilcalc_path = os.path.join(args.brilconda_dir, 'bin', 'brilcalc')
  units = args.units
  tmp_dir = args.tmp_dir
  sum_events_file = args.sum_events
  custom_strings = args.custom_strings
  lumi_pool = None

  if sum_events_file and not os.path.isfile(sum_events_file):
    raise ValueError('No such file: %s' % sum_events_file)

  if compute_lumi:
    # Check if the brilconda package has been installed
    if not os.path.isfile(brilcalc_path):
      raise ValueError("brilcalc not available in %s" % brilcalc_path)

    # Check if the user requested to run with normtag or not; if the user has requested to
    # use a normtag, then we have to make sure that the normtag is available
    if normtag_path:
      if not os.path.isfile(normtag_path):
        raise ValueError("normtag not found in %s" % normtag_path)

    # Create the temporary directory only when it's needed
    # In principle we could create the directory in individual processes, but experience shows that
    # this might cause some unwanted behavior, so we'll do it once here instead of concurrently
    create_if_not_exists(tmp_dir)

    # Print a message to remind the user what needs to be done before brilcalc can be run remotely
    print("NB! Make sure that you've created an SSH tunnel in order to access BRIL tools!")

  execution_datetime = '{date:%Y-%m-%d %H:%M:%S}'.format(date = datetime.datetime.now())
  execution_command  = ' '.join([os.path.basename(__file__)] + sys.argv[1:])

  if mc_input:
    if not os.path.isfile(mc_input):
      raise ValueError("No such file: %s" % mc_input)

    das_keys = collections.OrderedDict([
      ('name',                   {'colname' : 'Name',            'func' : id_}),
      ('dataset_access_type',    {'colname' : 'Status',          'func' : id_}),
      ('acquisition_era_name',   {'colname' : 'Acq. era name',   'func' : id_}),
      ('primary_ds_type',        {'colname' : 'Primary DS type', 'func' : id_}),
      ('last_modification_date', {'colname' : 'Last modified',   'func' : convert_date}),
      ('size',                   {'colname' : 'Size',            'func' : id_}),
      ('nfiles',                 {'colname' : 'Nof files',       'func' : id_}),
      ('nevents',                {'colname' : 'Nof events',      'func' : id_}),
      ('release',                {'colname' : 'CMSSW release',   'func' : convert_cmssw_versions}),
    ])

    das_query_results = collections.OrderedDict()
    with open(mc_input) as mc_file:
      for line in mc_file:
        line_stripped = line.rstrip('\n')
        field_str = line_stripped.split('#')[0].strip()
        if not field_str:
          # probably a comment or an empty line
          continue
        fields = field_str.split()
        if len(fields) < 5:
          raise ValueError("Unparseable line in file %s: %s" % (line_stripped, mc_input))

        das_name        = fields[0]
        use_it          = bool(int(fields[1]))
        sample_category = fields[2]
        specific_name   = fields[3]
        xs              = float(fields[4]) # let it fail
        private_path    = fields[5] if len(fields) == 6 else ''

        if not MC_REGEX.match(das_name) and not PRIVATE_REGEX.match(das_name):
          raise ValueError("Error: line '%s' does not correspond to proper DBS name" % das_name)
        if custom_strings and not any(map(lambda custom_string: custom_string in das_name, custom_strings)):
          continue
        das_query_results[das_name] = {
          'sample_category' : sample_category,
          'specific_name'   : specific_name,
          'xs'              : xs,
          'use_it'          : use_it,
          'private_path'    : private_path,
        }

    for dataset_idx, dataset in enumerate(das_query_results):
      if verbose:
        sys.stdout.write(
          "Querying sample (%d/%d): %s;" % (dataset_idx + 1, len(das_query_results), dataset)
        )
      dataset_split = dataset.split('/')
      if dataset_split[3] == PRIVATE_TIER:
        # The sample is privately produced and we would have to get the stats from the FS directly
        # Fill the meta-dictionary with some basic values
        sys.stdout.write("\n(It's a privately produced sample)\n")
        dataset_private_path = das_query_results[dataset]['private_path']
        if not dataset_private_path:
          raise ValueError('No path provided for sample %s' % dataset)
        fs_results = scan_private(dataset_private_path)

        das_query_results[dataset]['name'] = dataset
        das_query_results[dataset]['dataset_access_type'] = 'VALID'
        das_query_results[dataset]['acquisition_era_name'] = dataset_split[2]
        das_query_results[dataset]['primary_ds_type'] = 'mc' # We only produce MC samples privately
        das_query_results[dataset]['last_modification_date'] = fs_results['last_modification_date']
        das_query_results[dataset]['size'] = fs_results['size']
        das_query_results[dataset]['nfiles'] = fs_results['nfiles']
        das_query_results[dataset]['nevents'] = fs_results['nevents']
        das_query_results[dataset]['release'] = required_cmssw_version_str # [*]
        # [*] Assume that the MINIAODSIM was produced with a CMSSW version that is at least as new
        #     as the required CMSSW version
      else:
        for das_key_idx, das_key in enumerate(das_keys):
          if verbose:
            sys.stdout.write(" %s%s" % (das_key, (',' if das_key_idx != len(das_keys) - 1 else '\n')))
            sys.stdout.flush()
          mc_query_str = DASGOCLIENT_QUERY_COMMON % (dataset, das_key) if das_key != 'release' \
                         else DASGOCLIENT_QUERY_RELEASE % dataset
          mc_query_out, mc_query_err = run_cmd(mc_query_str, do_not_log = True, return_stderr = True)
          if not mc_query_out or mc_query_err:
            # this may happen if a sample is in PRODUCTION stage and the dasgoclient script
            # returns nonsense; let's try again with status=*
            query_fail = False
            if das_key != 'release':
              mc_query_str = DASGOCLIENT_QUERY_ANY_STATUS % (dataset, das_key)
              mc_query_out, mc_query_err = run_cmd(mc_query_str, do_not_log = True, return_stderr = True)
              if not mc_query_out or mc_query_err:
                query_fail = True
            else:
              query_fail = True
            if query_fail:
              raise ValueError("Query to DAS resulted in an empty output or an error:"
                               "\nstdout = '%s'\nstderr = '%s'" % (mc_query_out, mc_query_err))

          das_parser = das_keys[das_key]['func']
          das_query_results[dataset][das_key] = das_parser(mc_query_out.rstrip('\n')).strip()

    col_widths = {
      das_key:
        max(
          max(
            map(
              lambda col_value: len(col_value), [
                das_query_results[dataset][das_key] for dataset in das_query_results
              ]
            )
          ), len(das_keys[das_key]['colname'])
        ) for das_key in das_keys
    }
    for dataset in das_query_results:
      das_query_results[dataset]['release_pass'] = any(list(map(
        lambda ver: Version(ver).passes(required_cmssw_version),
        das_query_results[dataset]['release'].split(',')
      )))

    print("OK = the sample is produced with CMSSW version %s or greater" % required_cmssw_version_str)
    print(
      ' OK %s' % \
      '  '.join([das_keys[das_key]['colname'].ljust(col_widths[das_key]) for das_key in das_keys])
    )
    for dataset in das_query_results:
      passes_version_req = das_query_results[dataset]['release_pass']
      passes_version_req_tick = 'x' if passes_version_req else ' '
      print('  %s %s' % (
        passes_version_req_tick,
        '  '.join([
          das_query_results[dataset][das_key].ljust(col_widths[das_key]) for das_key in das_keys
        ])
      ))

    meta_dictionary_entries = []
    for dataset in das_query_results:
      entry = das_query_results[dataset]
      entry['use_it'] = entry['dataset_access_type'] != 'INVALID' and entry['release_pass'] and \
                        entry['use_it']
      meta_dictionary_entries.append(jinja2.Template(METADICT_TEMPLATE_MC).render(
        dataset_name    = entry['name'],
        nof_db_events   = entry['nevents'],
        nof_db_files    = entry['nfiles'],
        fsize_db        = entry['size'],
        sample_category = entry['sample_category'],
        xs              = entry['xs'],
        specific_name   = entry['specific_name'],
        use_it          = entry['use_it'],
        crab_string     = get_crab_string(entry['name'], crab_string),
        comment         = "status: %s; size: %s; nevents: %s; release: %s; last modified: %s" % (
          entry['dataset_access_type'],
          human_size(entry['size']),
          human_size(entry['nevents'], use_si = True, byte_suffix = ''),
          entry['release'],
          entry['last_modification_date'],
        ),
      ))

    sum_suffixes = ['_PSweights$', '_ext[1-9]{1}$']
    specific_names = [
      dataset_entry['specific_name'] for dataset_entry in das_query_results.values() \
      if dataset_entry['use_it']
    ]
    sum_events_flattened = []
    if sum_events_file:
      with open(sum_events_file, 'r') as sum_events_file_ptr:
        for line in sum_events_file_ptr:
          line_split = line.rstrip('\n').split()
          if line_split:
            sum_events_flattened.append(line_split)

    # Let's get the total event counts in each sample category; we want to maintain the original
    # order of sample categories they were declared
    sample_categories = list(collections.OrderedDict.fromkeys(
      [ dataset_entry['sample_category'] for dataset_entry in das_query_results.values() ]
    ))
    # Give the sample categories the same column width by left-padding their names
    max_sample_category_len = max(map(len, sample_categories)) + 1
    event_statistics = collections.OrderedDict(
      (
        ('%s:' % sample_category).ljust(max_sample_category_len),
        human_size(sum(
          int(dataset_entry['nevents']) for dataset_entry in das_query_results.values() \
          if dataset_entry['sample_category'] == sample_category
        ), byte_suffix = '')
      ) for sample_category in sample_categories
    )

    with open(args.metadict, 'w+') as f:
      f.write(jinja2.Template(METADICT_HEADER).render(
        command    = execution_command,
        date       = execution_datetime,
        sum_events = sum_events_flattened,
        is_mc      = True,
      ))
      f.write('\n'.join(meta_dictionary_entries))
      f.write(jinja2.Template(METADICT_FOOTER).render(event_statistics = event_statistics))
      f.write('\n')

  else:
    era = 'Run{year}'.format(year = args.run)
    data_query_str = DATA_QUERY % era
    data_query_out, data_query_err = run_cmd(data_query_str, do_not_log = True, return_stderr = True)

    data_samples_list = data_query_out.rstrip('\n').split('\n')
    data_samples_aggr = {data_sample : {} for data_sample in primary_datasets}

    collection_regex = re.compile(r'/(?P<%s>\b(%s)\b)/%s(?P<%s>[A-Z]{1}).+/%s' % \
                                  (PDS_KEY, DATA_PIPED, era, AQC_KEY, DATA_TIER))
    for data_sample in data_samples_list:
      collection_match = collection_regex.match(data_sample)
      if not collection_match:
        continue
      if custom_strings and not any(map(lambda custom_string: custom_string in data_sample, custom_strings)):
        continue
      primary_dataset    = collection_match.group(PDS_KEY)
      aqcuisition_period = collection_match.group(AQC_KEY)

      if primary_dataset not in data_samples_aggr:
        raise ValueError(
          "Data sample '%s' not in any of those: %s" % (primary_dataset, ', '.join(primary_datasets))
        )
      if aqcuisition_period not in data_samples_aggr[primary_dataset]:
        data_samples_aggr[primary_dataset][aqcuisition_period] = []
      data_samples_aggr[primary_dataset][aqcuisition_period].append(data_sample)

    print(
      "Primary datasets within acquisition era sorted by creation date; "     \
      "V -- produced with CMSSW version %s or later; "                        \
      "L -- latest sample by modification date." % required_cmssw_version_str
    )

    das_keys = collections.OrderedDict([
      ('name',                   {'colname' : 'Name',            'func' : id_}),
      ('dataset_access_type',    {'colname' : 'Status',          'func' : id_}),
      ('acquisition_era_name',   {'colname' : 'Acq. era name',   'func' : id_}),
      ('primary_ds_name',        {'colname' : 'Primary DS name', 'func' : id_}),
      ('primary_ds_type',        {'colname' : 'Primary DS type', 'func' : id_}),
      ('creation_time',          {'colname' : 'Creation time',   'func' : convert_date}),
      ('last_modification_date', {'colname' : 'Last modified',   'func' : convert_date}),
      ('nevents',                {'colname' : 'Nof events',      'func' : id_}),
      ('processing_version',     {'colname' : 'Processing ver.', 'func' : id_}),
      ('size',                   {'colname' : 'Size',            'func' : id_}),
      ('nfiles',                 {'colname' : 'Nof files',       'func' : id_}),
      ('release',                {'colname' : 'CMSSW release',   'func' : convert_cmssw_versions}),
    ])

    data_sample_selection = {}
    for data_sample in primary_datasets:
      if data_sample not in data_samples_aggr:
        continue
      if data_sample not in data_sample_selection:
        data_sample_selection[data_sample] = {}

      for acq_era in sorted(data_samples_aggr[data_sample].keys()):
        if acq_era not in data_sample_selection[data_sample]:
          data_sample_selection[data_sample][acq_era] = None

        datasets = data_samples_aggr[data_sample][acq_era]
        das_query_results = {}
        for dataset in datasets:
          das_query_results[dataset] = {}
          for das_key in das_keys:
            dasgoclient_query = DASGOCLIENT_QUERY_COMMON %                 \
                                (dataset, das_key) if das_key != 'release' \
                                else DASGOCLIENT_QUERY_RELEASE % dataset
            dasgoclient_query_out, dasgoclient_query_err = run_cmd(
              dasgoclient_query, do_not_log = True, return_stderr = True
            )
            das_parser = das_keys[das_key]['func']
            das_query_results[dataset][das_key] = das_parser(dasgoclient_query_out.rstrip('\n')).strip()

          if das_query_results[dataset]['dataset_access_type'] != 'VALID':
            del das_query_results[dataset]

        col_widths = {
          das_key :
            max(
              max(
                map(
                  lambda col_value: len(col_value), [
                      das_query_results[dataset][das_key] for dataset in das_query_results
                  ]
                )
              ), len(das_keys[das_key]['colname'])
            ) for das_key in das_keys
        }
        for dataset in das_query_results:
          das_query_results[dataset]['release_pass'] = any(list(map(
            lambda ver: Version(ver).passes(required_cmssw_version),
                        das_query_results[dataset]['release'].split(',')
          )))

        sorted_by_creation_time = [
          pair[0] for pair in sorted(
            das_query_results.items(), key = lambda value: value[1]['creation_time']
          )
        ]
        sorted_by_modification_time = [
          pair[0] for pair in sorted(
            das_query_results.items(), key = lambda value: value[1]['last_modification_date']
          )
        ]
        latest_modified_dataset = sorted_by_modification_time[-1]
        nof_passes_cmssw_version = sum([
          int(das_query_results[dataset]['release_pass']) for dataset in das_query_results
        ])

        print(
          'Primary DS name %s, acquisition era %s, found %i datasets, '  \
          '%i of which are produced with CMSSW version %s or greater:' % \
          (data_sample, acq_era, len(das_query_results), nof_passes_cmssw_version, required_cmssw_version_str)
        )
        print(
          ' V L %s' % \
          '  '.join([das_keys[das_key]['colname'].ljust(col_widths[das_key]) for das_key in das_keys])
        )

        selection_list = {}
        for dataset in sorted_by_creation_time:
          is_last_modified   = latest_modified_dataset == dataset
          passes_version_req = das_query_results[dataset]['release_pass']
          is_last_modified_tick   = 'x' if is_last_modified   else ' '
          passes_version_req_tick = 'x' if passes_version_req else ' '
          print(' %s %s %s' % (
            passes_version_req_tick, is_last_modified_tick,
            '  '.join([
              das_query_results[dataset][das_key].ljust(col_widths[das_key]) for das_key in das_keys
            ])
          ))
          if passes_version_req:
            selection_list[dataset] = das_query_results[dataset]

        selection_sorted_by_mod_time = [
          pair[0] for pair in sorted(
            selection_list.items(), key = lambda value: value[1]['last_modification_date']
          )
        ]
        if selection_sorted_by_mod_time:
          selected_dataset = selection_sorted_by_mod_time[-1]
          data_sample_selection[data_sample][acq_era] = selection_list[selected_dataset]

    print("%s\nSummary:" % ('-' * 120))
    meta_dictionary_entries = []
    dataset_list = collections.OrderedDict()

    if compute_lumi:
      # Initialize the thread pool in which the processes find the integrated luminosity for
      # each dataset
      original_sigint_handler = signal.signal(signal.SIGINT, signal.SIG_IGN)
      lumi_pool = multiprocessing.Pool(8)
      signal.signal(signal.SIGINT, original_sigint_handler)

      # Compute the total luminosity as well
      lumi_pool.apply_async(
        get_integrated_lumi,
        args     = ('total', None, brilcalc_path, normtag_path, units, lumimask_location),
        callback = update_lumi_results,
      )

    for dataset in primary_datasets:
      if dataset not in data_sample_selection:
        continue

      for acquisition_era in sorted(data_sample_selection[dataset]):
        selection = data_sample_selection[dataset][acquisition_era]

        if selection:
          # Query the run and luminosity ranges, figure out the golden range (for documentation purposes).
          # Exclude the whole sample if the data sample is not in the golden range.
          # We don't want to query the run and luminosity ranges earlier in the code because we only
          # pick a single sample out of multiple from the same PD & acquisition era combination.
          # Otherwise, we would spend a lot of time on querying and matching the run and luminosity ranges.

          runlumi_query = DASGOCLIENT_QUERY_RUNLUMI % selection['name']
          runlumi_query_out, runlumi_query_err = run_cmd(
            runlumi_query, do_not_log = True, return_stderr = True
          )
          if not runlumi_query_out or runlumi_query_err:
            raise ValueError(
              "Was not able to fetch run and lumi ranges for the sample: %s" % selection['name']
            )

          runlumi_data        = get_runlumi_data(runlumi_query_out)
          runlumi_data_golden = get_data_golden(runlumi_data, golden_runlumi)

          if runlumi_data_golden:
            # Let's find the min/max (golden) run ranges
            minmax_runlumi_data        = [ min(runlumi_data.keys()),        max(runlumi_data.keys())        ]
            minmax_runlumi_data_golden = [ min(runlumi_data_golden.keys()), max(runlumi_data_golden.keys()) ]

            print('  %s, %s%s -> %s' % (dataset.rjust(MAX_DATA_SAMPLE_LEN), era, acquisition_era, selection['name']))
            selection['specific_name'] = '_'.join(selection['name'].split('/')[1:-1]).replace('-', '_')
            meta_dictionary_entries.append(jinja2.Template(METADICT_TEMPLATE_DATA).render(
              dataset_name          = selection['name'],
              process_name_specific = selection['specific_name'],
              nof_db_events         = selection['nevents'],
              nof_db_files          = selection['nfiles'],
              fsize_db              = selection['size'],
              crab_string           = get_crab_string(selection['name'], crab_string),
              run_range             = minmax_runlumi_data,
              golden_run_range      = minmax_runlumi_data_golden,
              comment               = "status: %s; size: %s; nevents: %s; release: %s; last modified: %s" % (
                selection['dataset_access_type'],
                human_size(selection['size']),
                human_size(selection['nevents'], use_si = True, byte_suffix = ''),
                selection['release'],
                selection['last_modification_date'],
              ),
            ))
            dataset_list[selection['name']] = {
              'run_range'        : '%d-%d' % tuple(minmax_runlumi_data),
              'golden_run_range' : '%d-%d' % tuple(minmax_runlumi_data_golden),
            }

            # Retrieve the integrated luminosity for this sample
            if compute_lumi:
              try:
                tmp_file = os.path.join(tmp_dir, '%s.json' % selection['specific_name'])
                lumi_pool.apply_async(
                  get_integrated_lumi,
                  args     = (selection['name'], runlumi_data_golden, brilcalc_path, normtag_path, units, tmp_file),
                  callback = update_lumi_results,
                )
              except KeyboardInterrupt:
                lumi_pool.terminate()
                sys.exit(1)

          else:
            print(
              '  %s, %s%s -> excluded only because no golden run range' % \
              (dataset.rjust(MAX_DATA_SAMPLE_LEN), era, acquisition_era)
            )
        else:
          print('  %s, %s%s -> missing' % (dataset.rjust(MAX_DATA_SAMPLE_LEN), era, acquisition_era))

    if compute_lumi:
      # Wait until we've all integrated luminosities before we start writing any files
      lumi_pool.close()
      lumi_pool.join()

    with open(args.metadict, 'w+') as f:
      f.write(jinja2.Template(METADICT_HEADER).render(
        command = execution_command,
        date    = execution_datetime,
        is_mc   = False,
      ))
      f.write('\n'.join(meta_dictionary_entries))
      f.write('\n')

    if compute_lumi:
      totdelivered_colname = 'totdelivered(%s)' % units
      totrecorded_colname  = 'totrecorded(%s)' % units

    if args.dataset:
      with open(args.dataset, 'w+') as f:
        nof_cols = 5 if compute_lumi else 3
        dataset_format = '  '.join(['%s'] * nof_cols) + '\n'

        header = [
          "# DAS name",
          "run range",
          "golden run range",
        ]
        if compute_lumi:
          header += [
            totdelivered_colname,
            totrecorded_colname,
          ]

        col_widths = [
          max(max(map(len,                                  dataset_list.keys())),   len(header[0])),
          max(max(map(lambda d: len(d['run_range']),        dataset_list.values())), len(header[1])),
          max(max(map(lambda d: len(d['golden_run_range']), dataset_list.values())), len(header[2]))
        ]
        if compute_lumi:
          col_widths += [
            max(max(map(lambda d: len(d[header[3]]), lumi_results.values())), len(header[3])),
            max(max(map(lambda d: len(d[header[4]]), lumi_results.values())), len(header[4])),
          ]

        f.write(dataset_format % tuple([header[i].ljust(col_widths[i]) for i in range(nof_cols)]))
        for dataset_name, run_dict in dataset_list.items():
          values = [
            dataset_name,
            run_dict['run_range'],
            run_dict['golden_run_range'],
          ]
          if compute_lumi:
            values += [
              lumi_results[dataset_name][header[3]],
              lumi_results[dataset_name][header[4]],
            ]
          f.write(dataset_format % tuple([values[i].ljust(col_widths[i]) for i in range(nof_cols)]))
        f.write(
          "\n# file generated at %s with the following command:\n# %s\n" % \
          (execution_datetime, execution_command)
        )
        f.write("# golden JSON: %s\n" % os.path.basename(lumimask_location))
        if compute_lumi:
          f.write("# normtag: %s\n" % normtag if normtag else 'none')
          f.write("# %s: %s\n" % (totdelivered_colname, lumi_results['total'][totdelivered_colname]))
          f.write("# %s: %s\n" % (totrecorded_colname,  lumi_results['total'][totrecorded_colname]))
