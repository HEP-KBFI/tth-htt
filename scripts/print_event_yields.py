#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import os
import collections
import prettytable
import math
import csv
import argparse
import re

OUTPUT_NN = 'output_NN'
OUTPUT_NN_RE     = re.compile('{}_(?P<node>\w+)'.format(OUTPUT_NN))
OUTPUT_NN_RE_CAT = re.compile('{}_(?P<node>\w+)_(?P<category>\w+)'.format(OUTPUT_NN))
EVENTCOUNTER = 'EventCounter'
SYS_HISTOGRAM_PREFIX = 'CMS_ttHl_'
GEN_MATCHES = [ 'prompt', 'fake', 'flip', 'Convs', 'gentau', 'faketau' ]
DECAY_MODES = {
  'ttH' : [ 'htt', 'hww', 'hzz', 'hmm', 'hzg' ],
  'HH'  : [ 'tttt',  'zzzz',  'wwww',  'ttzz',  'ttww',  'zzww', 'bbtt', 'bbww', 'bbzz' ],
}
DECAY_MODE_PROCESSES = {
  'ttH' : [ 'ttH', 'tHq', 'tHW', 'VH', 'ZH', 'WH', 'ggH', 'qqH', 'TTWH', 'TTZH' ],
  'HH'  : [ 'HH' ]
}
ANALYSIS_REGIONS = collections.OrderedDict([
  ( 'sr',        'Tight'                     ),
  ( 'flip',      'Tight'                     ),
  ( 'fake',      'Fakeable_wFakeRateWeights' ),
  ( 'mcclosure', 'Fakeable_mcClosure'        ),
])
CHANNEL_LIST = [
  '0l_2tau', '1l_1tau', '1l_2tau', '2l_2tau', '2lss', '2los_1tau', '2lss_1tau', '3l', '3lctrl', '3l_1tau', '4l', '4lctrl',
]
TITLE_KEYS = [ 'era', 'channel', 'region_name', 'sample' ]

def get_dir(fptr, path):
  dir_ptr = fptr.Get(path)
  if type(dir_ptr) != ROOT.TDirectoryFile:
    raise RuntimeError(
      "Object at '%s' in file %s is not an instance of ROOT.TDirectoryFile" % (path, fptr.GetName())
    )
  return dir_ptr

def get_keys(dir_ptr, include = None, exclude = None):
  keys = [ key.GetName() for key in dir_ptr.GetListOfKeys() ]
  if include:
    keys = [ key for key in keys if include(key) ]
  if exclude:
    keys = [ key for key in keys if not exclude(key) ]
  return keys

def get_systematics(histogram_name):
  assert(
      histogram_name.endswith(EVENTCOUNTER) or
      OUTPUT_NN_RE.match(histogram_name)    or
      OUTPUT_NN_RE_CAT.match(histogram_name)
  )
  if histogram_name.startswith(SYS_HISTOGRAM_PREFIX):
    if EVENTCOUNTER in histogram_name:
      histogram_name_prefix = histogram_name.replace('_{}'.format(EVENTCOUNTER), '').replace(SYS_HISTOGRAM_PREFIX, '')
    else:
      histogram_name_prefix = histogram_name.split('_{}'.format(OUTPUT_NN))[0].replace(SYS_HISTOGRAM_PREFIX, '')
    assert(histogram_name_prefix.endswith(('Up', 'Down')))
    return histogram_name_prefix
  else:
    return 'central'

def get_node_subcategory(histogram_name):
  output_nn_match = OUTPUT_NN_RE.match(histogram_name)
  output_nn_match_cat = OUTPUT_NN_RE_CAT.match(histogram_name)
  if output_nn_match_cat:
    node = output_nn_match.group('node')
    category = output_nn_match.group('category')
    return node, category
  elif output_nn_match:
    node = output_nn_match.group('node')
    return node, ''
  else:
    return '', ''

def parse_process(process):
  process_name = process
  decay_mode = ''
  gen_match = 'prompt'
  if process_name.endswith(tuple('_{}'.format(gm) for gm in GEN_MATCHES)):
    process_name_split = process_name.split('_')
    process_name = '_'.join(process_name_split[:-1])
    gen_match = process_name_split[-1]
    assert(gen_match in GEN_MATCHES)
  for decay_mode_process in DECAY_MODE_PROCESSES:
    if process_name.endswith(tuple('_{}'.format(dm) for dm in DECAY_MODES[decay_mode_process])):
      process_name_split = process_name.split('_')
      process_name = '_'.join(process_name_split[:-1])
      decay_mode = process_name_split[-1]
      assert(decay_mode in DECAY_MODES[decay_mode_process])
      assert(process_name in DECAY_MODE_PROCESSES[decay_mode_process])
      break
  return process_name, decay_mode, gen_match

def fmt_float(val, significant_digits = 4, max_pow = 3):
  assert(type(val) == float)
  if val == 0.:
    return "0"
  abs_val = abs(val)
  val_lg10 = int(math.log10(abs_val))
  if val_lg10 < 0:
    val_lg10 -= 1
  if abs(val_lg10) > max_pow:
    val_pow = val / 10**val_lg10
    return '{:.{prec}}e{pow}'.format(val_pow, prec = significant_digits, pow = val_lg10)
  alt_precision = significant_digits
  if val_lg10 > 0:
    alt_precision = max(significant_digits, val_lg10) + 1
  return '{:.{prec}}'.format(val, prec = alt_precision)

def get_evt_yields(input_file_name, results = None):
  if not results:
    results = collections.OrderedDict()
  metadata = extract_metadata(input_file_name)
  if not input_file_name:
    return results, metadata
  assert('sample' in metadata)
  sample = metadata['sample']

  assert(hdfs.isfile(input_file_name))
  input_file = ROOT.TFile.Open(input_file_name, 'read')

  subdirectories = get_keys(
    input_file,
    exclude = lambda key: key in [ 'analyzedEntries', 'selectedEntries' ] or \
                          key.endswith(('_fake', '_nonfake'))
  )
  for whitelist in [ '1l_1tau_Fakeable_wFakeRateWeights', '1l_1tau_Tight' ]:
    if whitelist in subdirectories:
      subdirectories = [ whitelist ]
  is_single_subcategory = len(subdirectories) == 1

  for subdirectory in subdirectories:
    evt_directory_path = os.path.join(subdirectory, 'sel', 'evt')
    evt_directory_ptr = get_dir(input_file, evt_directory_path)
    subcategory_name = '' if is_single_subcategory else subdirectory
    processes = get_keys(evt_directory_ptr, exclude = lambda key: key.startswith(('tHq', 'tHW', 'HH')) and 'kt_' in key)
    for process in processes:
      process_path = os.path.join(evt_directory_path, process)
      process_dir_ptr = get_dir(input_file, process_path)
      process_name, decay_mode, gen_match = parse_process(process)
      histogram_names = get_keys(
        process_dir_ptr,
        include = lambda key: EVENTCOUNTER in key or \
                              OUTPUT_NN_RE_CAT.match(key) or \
                              OUTPUT_NN_RE.match(key)
        )
      for histogram_name in histogram_names:
        histogram_path = os.path.join(process_path, histogram_name)
        histogram = input_file.Get(histogram_path)
        if type(histogram) != ROOT.TH1D:
          raise RuntimeError(
            "Object at '%s' in file %s is not an instance of ROOT.TH1D" % (histogram_path, input_file_name)
          )
        systematics = get_systematics(histogram_name)
        node, category = get_node_subcategory(histogram_name)
        event_count = int(histogram.GetEntries())
        event_yield = histogram.Integral()
        if systematics.startswith('FR'):
          continue
        if subcategory_name not in results:
          results[subcategory_name] = collections.OrderedDict()
        if process_name not in results[subcategory_name]:
          results[subcategory_name][process_name] = collections.OrderedDict()
        if sample not in results[subcategory_name][process_name]:
          results[subcategory_name][process_name][sample] = collections.OrderedDict()
        if decay_mode not in results[subcategory_name][process_name][sample]:
          results[subcategory_name][process_name][sample][decay_mode] = collections.OrderedDict()
        if gen_match not in results[subcategory_name][process_name][sample][decay_mode]:
          results[subcategory_name][process_name][sample][decay_mode][gen_match] = collections.OrderedDict()
        if systematics not in results[subcategory_name][process_name][sample][decay_mode][gen_match]:
          results[subcategory_name][process_name][sample][decay_mode][gen_match][systematics] = collections.OrderedDict()
        if node not in results[subcategory_name][process_name][sample][decay_mode][gen_match][systematics]:
          results[subcategory_name][process_name][sample][decay_mode][gen_match][systematics][node] = collections.OrderedDict()
        if category in results[subcategory_name][process_name][sample][decay_mode][gen_match][systematics][node]:
          raise RuntimeError(
            "Possible double-counting the event counts and yields by reading histogram '%s' in file %s: "
            "subcategory name = %s, process name = %s, sample = %s, decay mode = %s, gen matching = %s, "
            "systematics = %s, node = %s, category = %s" % (
              histogram_path, input_file_name, subcategory_name, process_name, sample, decay_mode, gen_match,
              systematics, node, category,
            )
          )
        results[subcategory_name][process_name][sample][decay_mode][gen_match][systematics][node][category] = {
          'count' : event_count,
          'yield' : event_yield,
        }
        del histogram
      del process_dir_ptr
    del evt_directory_ptr
  input_file.Close()
  return results, metadata

def get_table(input_file_names, allowed_decay_modes = None, show_gen_matching = True, allowed_systematics = 'central',
              show_by_nodes = False, show_by_sample = False):
  channel = ''
  results, metadata_stage2 = get_evt_yields(input_file_names['stage2'])
  if 'channel' in metadata_stage2:
    channel = metadata_stage2['channel']
  for input_file_name in input_file_names['stage1']:
    results, metadata_stage1 = get_evt_yields(input_file_name, results)
    if not channel and 'channel' in metadata_stage1:
      channel = metadata_stage1['channel']
  if not results:
    return
  assert(channel)

  header = []
  allowed_decay_mode_processes = []
  has_decay_modes = not (len(allowed_decay_modes) == 1 and '' in allowed_decay_modes)
  if len(results) > 1:
    header.append('Event subcategory')
  header.append('Process')
  if show_by_sample:
    header.append('Sample')
  if has_decay_modes:
    header.append('Decay mode')
    for allowed_decay_mode in allowed_decay_modes:
      allowed_decay_mode_processes.extend(DECAY_MODE_PROCESSES[allowed_decay_mode])
  if show_gen_matching:
    header.append('Gen matching')
  if allowed_systematics == 'all':
    header.append('Systematics')
  if show_by_nodes:
    header.append('Node')
    header.append('Category')
  header.append('Event yields (counts)')

  exclude_from_SM_exp = [ 'data_obs', 'fakes_mc' ]
  if channel == '1l_1tau':
    exclude_from_SM_exp.append('flips_mc')

  lines = [ header ]
  for subcategory in results:
    SM_exp = collections.OrderedDict()
    for process in results[subcategory]:
      for sample in results[subcategory][process]:
        if not show_by_sample and sample:
          continue
        for decay_mode in results[subcategory][process][sample]:
          if (not has_decay_modes and decay_mode                                                ) or \
             (    has_decay_modes and decay_mode and process not in allowed_decay_mode_processes):
            continue
          for gen_matching in results[subcategory][process][sample][decay_mode]:
            if not show_gen_matching and gen_matching != 'prompt':
              continue
            for systematics in results[subcategory][process][sample][decay_mode][gen_matching]:
              if allowed_systematics == 'central' and systematics != 'central':
                continue
              if systematics.startswith('thu'):
                systematics_split = systematics.split('_')
                assert(len(systematics_split) == 4)
                if systematics_split[2].lower() not in process.lower():
                  continue
              for node in results[subcategory][process][sample][decay_mode][gen_matching][systematics]:
                if not show_by_nodes and node:
                  continue
                if node not in SM_exp:
                  SM_exp[node] = collections.OrderedDict()
                for category, stats in results[subcategory][process][sample][decay_mode][gen_matching][systematics][node].items():
                  if not show_by_nodes and category:
                    continue
                  if category not in SM_exp[node]:
                    SM_exp[node][category] = collections.OrderedDict()
                  yields = str(stats['count'])
                  if process != 'data_obs':
                    yields = '{} ({})'.format(fmt_float(stats['yield']), yields)
                  line = []
                  if subcategory:
                    line.append(subcategory)
                  line.append(process)
                  if show_by_sample:
                    line.append(sample)
                  if has_decay_modes:
                    line.append(decay_mode)
                  if show_gen_matching:
                    line.append(gen_matching)
                  if allowed_systematics == 'all':
                    line.append(systematics)
                  if show_by_nodes:
                    line.append(node)
                    line.append(category)
                  line.append(yields)
                  assert(len(line) == len(header))
                  lines.append(line)

                  if not sample and \
                     not decay_mode and \
                     gen_matching == 'prompt' and \
                     process not in exclude_from_SM_exp and \
                     not systematics.startswith('thu'):
                    if systematics not in SM_exp[node][category]:
                      SM_exp[node][category][systematics] = {
                        'yield' : 0.,
                        'count' : 0,
                      }
                    SM_exp[node][category][systematics]['yield'] += stats['yield']
                    SM_exp[node][category][systematics]['count'] += stats['count']
    for node in SM_exp:
      if not show_by_nodes and node:
        continue
      for category in SM_exp[node]:
        if not show_by_nodes and category:
          continue
        for systematics in SM_exp[node][category]:
          if allowed_systematics == 'central' and systematics != 'central':
            continue
          line = []
          if subcategory:
            line.append(subcategory)
          line.append('SM expectation')
          if show_by_sample:
            line.append('')
          if has_decay_modes:
            line.append('')
          if show_gen_matching:
            line.append('prompt')
          if allowed_systematics == 'all':
            line.append(systematics)
          if show_by_nodes:
            line.append(node)
            line.append(category)
          SM_exp_results = SM_exp[node][category][systematics]
          line.append('{} ({})'.format(fmt_float(SM_exp_results['yield'], max_pow = 4), SM_exp_results['count']))
          assert(len(line) == len(header))
          lines.append(line)
  return lines

def print_table(lines, metadata):
  assert('path' in metadata)
  fmt_str = ''
  if all(key in metadata for key in TITLE_KEYS):
    fmt_str = 'ERA = {era}, CHANNEL = {channel}, REGION = {region_name}, '
    if metadata['sample']:
      fmt_str += "SAMPLE = {sample}, "
  fmt_str += 'PATH = {path}'
  print(fmt_str.format(**metadata))

  table = prettytable.PrettyTable(lines[0])
  for line in lines[1:]:
    table.add_row(line)
  print(table)

def reformat_table(lines, title):
  result = [ title ]
  header = lines[0]
  header_modified = header[:-1] + [ 'Event yields', 'Event counts' ]
  result.append(header_modified)
  for row in lines[1:]:
    row_modified = row[:-1]
    row_last_split = row[-1].replace('(', '').replace(')', '').split()
    assert(0 < len(row_last_split) < 3)
    yields = float(row_last_split[0])
    counts = int(row_last_split[1]) if len(row_last_split) == 2 else int(yields)
    row_modified += [ yields, counts ]
    result.append(row_modified)
  return result

def save_table(lines, output_filename):
  with open(output_filename, 'w') as output_file:
    table_writer = csv.writer(output_file, quoting = csv.QUOTE_NONNUMERIC)
    for row in lines:
      table_writer.writerow(row)

def extract_metadata(hadd_stage_path):
  path_split = [ subpath for subpath in hadd_stage_path.split(os.path.sep) if subpath != '' ]
  if len(path_split) < 9:
    return { 'path' : hadd_stage_path }
  era = path_split[4]
  channel = path_split[7]
  if channel not in CHANNEL_LIST:
    raise RuntimeError("Unrecognizable channel found in path %s: %s" % (hadd_stage_path, channel))
  region = path_split[8]
  region_name = ''
  region_key = ''
  if region.startswith('Tight'):
    region_name = 'SR'
    region_key = 'sr'
    if channel in [ '2lss', '2lss_1tau' ] and region.startswith('Tight_OS'):
      region_name = 'flip AR'
      region_key = 'flip'
  elif region.startswith('Fakeable_wFakeRateWeights'):
    region_name = 'fake AR'
    region_key = 'fake'
    if channel in [ '2lss', '2lss_1tau' ] and region.startswith('Fakeable_wFakeRateWeights_OS'):
      region_name = ''
      region_key = ''
  elif region.startswith('Fakeable_mcClosure'):
    region_split = region.split('_')
    typ = region_split[2]
    assert(typ in [ 'e', 'm', 't' ])
    region_name = 'MC closure ({})'.format(typ)
    region_key = 'mcclosure'
  sample_name = path_split[9] if (len(path_split) > 9 and path_split[9] != 'hadd') else ''
  metadata = {
    'path'        : hadd_stage_path,
    'era'         : era,
    'channel'     : channel,
    'region'      : region,
    'region_name' : region_name,
    'region_key'  : region_key,
    'sample'      : sample_name,
  }
  return metadata

def is_hadd_stage_file(input_path, is_hadd_stage1, metadata = None):
  if not metadata:
    metadata = extract_metadata(input_path)
  candidate_file_basename = os.path.basename(input_path)
  return candidate_file_basename.startswith('hadd_stage{}_'.format(1 if is_hadd_stage1 else 2)) and (
     candidate_file_basename.endswith('_{}.root'.format(metadata['region'])) or
     candidate_file_basename.replace('lep', '').replace('sum', '').endswith('_{}.root'.format(metadata['region']))
    )

def find_hadd_stage_files(input_path, regions, find_hadd_stage1):
  path_split = [ subpath for subpath in input_path.split(os.path.sep) if subpath != '' ]
  nof_levels = len(path_split)
  if not ( 5 < nof_levels < 11 ):
    raise ValueError("Invalid path: %s" % input_path)

  current_paths = [ input_path ]
  if nof_levels == 6:
    assert (len(current_paths) == 1)
    current_path = os.path.join(current_paths.pop(), 'histograms')
    if not hdfs.isdir(current_path):
      return []
    current_paths = [ current_path ]
    nof_levels += 1
  if nof_levels == 7:
    assert(len(current_paths) == 1)
    current_path = current_paths.pop()
    current_paths = hdfs.listdir(current_path)
    nof_levels += 1
  if nof_levels == 8:
    next_paths = []
    for current_path in current_paths:
      region_paths = hdfs.listdir(current_path)
      for region_path in region_paths:
        if os.path.basename(region_path).startswith(tuple(ANALYSIS_REGIONS[region] for region in regions)):
          next_paths.append(region_path)
    current_paths = next_paths
    nof_levels += 1
  if nof_levels == 9:
    next_paths = []
    for current_path in current_paths:
      for next_path in hdfs.listdir(current_path):
        next_path_basename = os.path.basename(next_path)
        if not (find_hadd_stage1 != (next_path_basename != 'hadd')):
          next_paths.append(next_path)
    current_paths = next_paths
    nof_levels += 1
  if nof_levels == 10:
    next_paths = []
    for current_path in current_paths:
      candidate_files = []
      metadata = extract_metadata(current_path)
      if metadata['region_key'] not in regions:
        continue
      for candidate_file in hdfs.listdir(current_path):
        if not hdfs.isfile(candidate_file):
          continue
        if is_hadd_stage_file(candidate_file, find_hadd_stage1, metadata):
          candidate_files.append(candidate_file)
      if candidate_files:
        assert(len(candidate_files) == 1)
        next_paths.append(candidate_files[0])
    current_paths = next_paths
  return current_paths

def path_sorter(path):
  metadata = extract_metadata(path)
  if all(key in metadata for key in [ 'era', 'channel', 'region_key' ]):
    return (
      CHANNEL_LIST.index(metadata['channel']),
      ANALYSIS_REGIONS.keys().index(metadata['region_key']),
      int(metadata['era'])
    )
  else:
    return (-1, -1, -1)

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True, nargs = '+',
    help = 'R|Output of any hadd stage',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = False, default = '',
    help = 'R|Name of the output CSV file',
  )
  parser.add_argument('-d', '--decay-modes',
    type = str, dest = 'decay_modes', metavar = 'processes', required = False, default = [ 'ttH' ], nargs = '+',
    choices = list(DECAY_MODE_PROCESSES.keys()) + [ '' ],
    help = 'R|Processes for which the event yields and counts are split by decay modes',
  )
  parser.add_argument('-g', '--gen-matching',
    dest = 'gen_matching', action = 'store_true', default = False,
    help = 'R|Show event yields and counts split by gen matching',
  )
  parser.add_argument('-s', '--systematics',
    type = str, dest = 'systematics', metavar = 'choice', required = False, default = 'central',
    choices = [ 'central', 'all' ],
    help = 'R|Show event yields and counts for central or all systematics',
  )
  parser.add_argument('-r', '--region',
    type = str, dest = 'regions', metavar = 'region', required = False, default = [ 'sr' ], nargs = '+',
    choices = ANALYSIS_REGIONS.keys(),
    help = 'R|Which hadd stage2 files to search for',
  )
  parser.add_argument('-n', '--node',
    dest = 'node', action = 'store_true', default = False,
    help = 'R|Show event yields and counts split by NN node (effective only in 2lss, 3l)',
  )
  parser.add_argument('-S', '--sample',
    dest = 'sample', action = 'store_true', default = False,
    help = 'R|Show results by sample from hadd stage1 files',
  )
  args = parser.parse_args()

  input_file_paths = args.input
  output_file_name = args.output
  allowed_decay_modes = args.decay_modes
  show_gen_matching = args.gen_matching
  allowed_systematics = args.systematics
  searchable_regions = args.regions
  show_by_nodes = args.node
  show_by_sample = args.sample

  if len(allowed_decay_modes) > 1 and '' in allowed_decay_modes:
    raise ValueError("Conflicting values to 'decay_modes' parameter")

  input_file_names_hadd_stage1 = []
  input_file_names_hadd_stage2 = []
  for input_file_path in input_file_paths:
    if not input_file_path.startswith('/hdfs/local'):
      raise ValueError("Invalid path: %s" % input_file_path)

    if hdfs.isfile(input_file_path):
      input_file_abs_path = os.path.abspath(input_file_path)
      if is_hadd_stage_file(input_file_abs_path, True):
        input_file_names_hadd_stage1.append(input_file_abs_path)
      elif is_hadd_stage_file(input_file_abs_path, False):
        input_file_names_hadd_stage2.append(input_file_abs_path)
      else:
        raise ValueError("Not a valid hadd stage 1 or stage 2 file: %s" % input_file_path)
    else:
      input_file_names_hadd_stage1.extend(find_hadd_stage_files(input_file_path, searchable_regions, True))
      input_file_names_hadd_stage2.extend(find_hadd_stage_files(input_file_path, searchable_regions, False))

  input_file_names_regrouped = collections.OrderedDict()
  for input_file_name in input_file_names_hadd_stage2:
    prefix = os.path.dirname(os.path.dirname(input_file_name))
    if prefix not in input_file_names_regrouped:
      input_file_names_regrouped[prefix] = {
        'stage2' : '',
        'stage1' : [],
      }
    assert(not input_file_names_regrouped[prefix]['stage2'])
    input_file_names_regrouped[prefix]['stage2'] = input_file_name
  for input_file_name in input_file_names_hadd_stage1:
    prefix = os.path.dirname(os.path.dirname(input_file_name))
    if prefix not in input_file_names_regrouped:
      input_file_names_regrouped[prefix] = {
        'stage2': '',
        'stage1': [],
      }
    input_file_names_regrouped[prefix]['stage1'].append(input_file_name)

  prefixes = list(sorted(set(input_file_names_regrouped.keys()), key = path_sorter))
  if not prefixes:
    raise ValueError("No valid input files found from: %s" % ', '.join(input_file_paths))

  tables = []
  for prefix, input_file_names in input_file_names_regrouped.items():
    table = get_table(
      input_file_names,
      allowed_decay_modes = allowed_decay_modes,
      show_gen_matching   = show_gen_matching,
      allowed_systematics = allowed_systematics,
      show_by_nodes       = show_by_nodes,
      show_by_sample      = show_by_sample or (not show_by_sample and not input_file_names['stage2']),
    )
    metadata = extract_metadata(prefix)
    print_table(table, metadata)
    if output_file_name:
      assert('path' in metadata)
      title = []
      if all(key in metadata for key in TITLE_KEYS):
        title = [ metadata[key] for key in TITLE_KEYS if metadata[key] ]
      title.append(metadata['path'])
      tables.extend(reformat_table(table, title))

  if output_file_name:
    output_file_dir = os.path.dirname(os.path.abspath(output_file_name))
    if not os.path.isdir(output_file_dir):
      os.makedirs(output_file_dir)
    save_table(tables, output_file_name)
