#!/usr/bin/env python

import subprocess, re, datetime, collections, jinja2, argparse

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

meta_dictionary = OD()

### event sums

sum_events = {
  #("", ""),
}

'''

METADICT_TEMPLATE_DATA = '''meta_dictionary["{{ dataset_name }}"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "{{ process_name_specific }}"),
  ("nof_db_events",         {{ nof_db_events }}),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

'''

DATA_SAMPLES = [
  'SingleElectron',
  'SingleMuon',
  'DoubleEG',
  'DoubleMuon',
  'MuonEG',
  'Tau',
]
DATA_TIER     = 'MINIAOD'
AQC_KEY       = 'cat'
PDS_KEY       = 'data'
DATA_GREP_STR = '\\|'.join(map(lambda sample: '^/%s/' % sample, DATA_SAMPLES))
DATA_PIPED    = '|'.join(DATA_SAMPLES)
DASGOCLIENT_QUERY_COMMON  = "dasgoclient -query='dataset=%s | grep dataset.%s' -unique | grep -v '^\\['"
DASGOCLIENT_QUERY_RELEASE = "dasgoclient -query='release dataset=%s' -unique"
MAX_DATA_SAMPLE_LEN       = max(map(len, DATA_SAMPLES))

def convert_date(date):
  return datetime.datetime.fromtimestamp(int(date)).strftime('%Y-%m-%d %H:%M:%S')

def convert_cmssw_versions(cmssw_str):
  return ','.join(set([re.match(r'.*\"(?P<ver>.*)\".*', s).group('ver')[len('CMSSW')+1:] for s in cmssw_str.split(',')]))

def id_(x): # identity function
  return x

def run_cmd(cmd_str, return_stderr = True):
  cmd = subprocess.Popen(cmd_str, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True)
  stdout, stderr = cmd.communicate()
  if return_stderr:
    return stdout, stderr
  return stdout

if __name__ == '__main__':

  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
  )
  parser.add_argument('-m', '--metadict',
    type = str, dest = 'metadict', metavar = 'path', default = 'metaDict.py', required = False,
    help = 'R|Output path of the Python meta-dictionary',
  )
  parser.add_argument('-d', '--datasets',
    type = str, dest = 'dataset', metavar = 'path', default = 'datasets.txt', required = False,
    help = 'R|Output path of the dataset list',
  )
  parser.add_argument('-r', '--run',
    type = str, dest = 'run', metavar = 'run', default = '2017', required = False,
    help = 'R|Data collection period',
  )
  parser.add_argument('-v', '--cmssw-version',
    type = str, dest = 'version', metavar = 'version', default = '9_4_0', required = False,
    help = 'R|Minimum required CMSSW version',
  )
  args = parser.parse_args()

  has_dasgoclient = run_cmd('which dasgoclient 2>/dev/null | wc -l', False)
  if has_dasgoclient.rstrip('\n') != "1":
    raise ValueError("dasgoclient not available! Set up your 94x environment")
  has_voms_proxy = run_cmd('which voms-proxy-info 2>/dev/null | wc -l', False)
  if has_voms_proxy.rstrip('\n') != "1":
    raise ValueError("voms-proxy-* not available! Set up your 94x environment")

  min_voms_proxy_timeleft_minutes = 30
  voms_proxy_timeleft = int(run_cmd('voms-proxy-info --timeleft', False).rstrip('\n'))
  if voms_proxy_timeleft < 60 * min_voms_proxy_timeleft_minutes:
    raise ValueError(
      "proxy not open at least %i minutes to run this script; "         \
      "update your proxy with: voms-proxy-init -voms cms -valid 1:00" % \
      min_voms_proxy_timeleft_minutes
    )

  required_cmssw_version_str = args.version
  required_cmssw_version = Version(required_cmssw_version_str)
  era = 'Run{year}'.format(year = args.run)

  data_query_str = "dasgoclient -query='dataset dataset=/*/*%s*/%s' | grep '%s' | sort" % \
                   (era, DATA_TIER, DATA_GREP_STR)
  data_query_out, data_query_err = run_cmd(data_query_str)

  data_samples_list = data_query_out.rstrip('\n').split('\n')
  data_samples_aggr = {data_sample : {} for data_sample in DATA_SAMPLES}

  collection_regex = re.compile(r'/(?P<%s>\b(%s)\b)/%s(?P<%s>[A-Z]{1}).+/%s' % \
                                (PDS_KEY, DATA_PIPED, era, AQC_KEY, DATA_TIER))
  for data_sample in data_samples_list:
    collection_match = collection_regex.match(data_sample)
    if not collection_match:
      raise ValueError("Could not parse sample: %s" % data_sample)
    primary_dataset    = collection_match.group(PDS_KEY)
    aqcuisition_period = collection_match.group(AQC_KEY)

    if primary_dataset not in data_samples_aggr:
      raise ValueError(
        "Data sample '%s' not in any of those: " % (primary_dataset, ', '.join(DATA_SAMPLES))
      )
    if aqcuisition_period not in data_samples_aggr[primary_dataset]:
      data_samples_aggr[primary_dataset][aqcuisition_period] = []
    data_samples_aggr[primary_dataset][aqcuisition_period].append(data_sample)

  das_keys = collections.OrderedDict([
    ('name',                   {'colname' : 'Name',            'func' : id_}),
    ('status',                 {'colname' : 'Status',          'func' : id_}),
    ('acquisition_era_name',   {'colname' : 'Acq. era name',   'func' : id_}),
    ('primary_ds_name',        {'colname' : 'Primary DS name', 'func' : id_}),
    ('primary_ds_type',        {'colname' : 'Primary DS type', 'func' : id_}),
    ('creation_time',          {'colname' : 'Creation time',   'func' : convert_date}),
    ('last_modification_date', {'colname' : 'Last modified',   'func' : convert_date}),
    ('nevents',                {'colname' : 'Nof events',      'func' : id_}),
    ('processing_version',     {'colname' : 'Processing ver.', 'func' : id_}),
    ('release',                {'colname' : 'CMSSW release',   'func' : convert_cmssw_versions}),
  ])

  print(
    "Primary datasets within acquisition era sorted by creation date; "     \
    "V -- produced with CMSSW version %s or later; "                        \
    "L -- latest sample by modification date." % required_cmssw_version_str
  )

  data_sample_selection = {}
  for data_sample in DATA_SAMPLES:
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
          dasgoclient_query_out, dasgoclient_query_err = run_cmd(dasgoclient_query)
          das_parser = das_keys[das_key]['func']
          das_query_results[dataset][das_key] = das_parser(dasgoclient_query_out.rstrip('\n')).strip()

        if das_query_results[dataset]['status'] != 'VALID':
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
  meta_dictionary_entries, dataset_list = [], []
  for dataset in DATA_SAMPLES:
    if dataset not in data_sample_selection:
      continue

    for acquisition_era in sorted(data_sample_selection[dataset]):
      selection = data_sample_selection[dataset][acquisition_era]
      if selection:
        print('  %s, %s%s -> %s' % (dataset.rjust(MAX_DATA_SAMPLE_LEN), era, acquisition_era, selection['name']))
        meta_dictionary_entries.append(jinja2.Template(METADICT_TEMPLATE_DATA).render(
          dataset_name          = selection['name'],
          process_name_specific = '_'.join(selection['name'].split('/')[1:-1]).replace('-', '_'),
          nof_db_events         = selection['nevents'],
        ))
        dataset_list.append(selection['name'])
      else:
        print('  %s, %s%s -> missing' % (dataset.rjust(MAX_DATA_SAMPLE_LEN), era, acquisition_era))

  with open(args.metadict, 'w+') as f:
    f.write(METADICT_HEADER)
    f.write('\n'.join(meta_dictionary_entries))
    f.write('\n')

  with open(args.dataset, 'w+') as f:
    f.write('\n'.join(dataset_list))
    f.write('\n')
