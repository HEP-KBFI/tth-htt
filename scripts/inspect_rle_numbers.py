#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import collections
import re
import argparse
import array
import os.path

OUTPUT_RLE = 'output_rle'
REGEX_RLE = re.compile('^(\d+):(\d+):(\d+)$')
SAMPLES_EXCLUDE = [ 'hadd' ]
SYSTEMATICS_EXCLUDE = [ 'addBackgrounds', 'hadd' ]
SYSTEMATICS_CENTRAL = 'central'

def get_paths(input_paths, whitelist, blacklist):
  valid_paths = {}
  for input_path in input_paths:
    input_path_split = [ subpath for subpath in input_path.split(os.path.sep) if subpath != '' ]
    nof_levels = len(input_path_split)
    if nof_levels == 6:
      input_path_subdir = os.path.join(input_path, OUTPUT_RLE)
      if not hdfs.isdir(input_path_subdir):
        raise ValueError("No such directory: %s" % input_path_subdir)
      for channel_dir in sorted(hdfs.listdir(input_path_subdir)):
        channel_name = os.path.basename(channel_dir)
        if whitelist and channel_name not in whitelist:
          logging.info("Excluding channel: {}".format(channel_name))
          continue
        if channel_name in blacklist:
          logging.info("Excluding channel: {}".format(channel_name))
          continue
        if channel_name in valid_paths:
          raise ValueError(
            "Found duplicate paths for the same channel: %s and %s" % (valid_paths[channel_name], input_path)
          )
        logging.debug('Found channel {} at path {}'.format(channel_name, channel_dir))
        valid_paths[channel_name] = channel_dir
    elif nof_levels == 8:
      if input_path_split[-2] != OUTPUT_RLE:
        raise ValueError("Invalid path: %s" % input_path)
      channel_name = input_path_split[-1]
      if whitelist and channel_name not in whitelist:
        raise ValueError("Path %s conflicting with whitelist: %s" % (input_path, ', '.join(whitelist)))
      if channel_name in blacklist:
        raise ValueError("Path %s conflicting with blacklist: %s" % (input_path, ', '.join(blacklist)))
      if channel_name in valid_paths:
        raise ValueError(
          "Found duplicate paths for the same channel: %s and %s" % (valid_paths[channel_name], input_path)
        )
      logging.debug('Found channel {} at path {}'.format(channel_name, input_path))
      valid_paths[channel_name] = input_path
    else:
      raise ValueError("Invalid path: %s" % input_path)
  assert(len(set(valid_paths.values())) == len(valid_paths))
  return valid_paths

def get_rles(input_paths, whitelist, blacklist, read_all_systematics):
  has_errors = False
  rles = collections.OrderedDict()
  valid_paths = get_paths(input_paths, whitelist, blacklist)
  for channel_name, channel_dir in valid_paths.items():
    rles[channel_name] = collections.OrderedDict()
    for region_dir in sorted(hdfs.listdir(channel_dir)):
      region_name = os.path.basename(region_dir)
      logging.debug('Found region {} in channel {}'.format(channel_name, region_name))
      rles[channel_name][region_name] = collections.OrderedDict()
      for sample_dir in sorted(hdfs.listdir(region_dir)):
        sample_name = os.path.basename(sample_dir)
        if sample_name in SAMPLES_EXCLUDE:
          continue
        logging.debug('Found sample {} in region {} and channel {}'.format(sample_name, region_name, channel_name))
        rles[channel_name][region_name][sample_name] = collections.OrderedDict()
        for rle_dir in sorted(hdfs.listdir(sample_dir)):
          central_or_shift = os.path.basename(rle_dir)
          if central_or_shift in SYSTEMATICS_EXCLUDE:
            continue
          if not read_all_systematics and central_or_shift != SYSTEMATICS_CENTRAL:
            continue
          logging.debug(
            'Found systematics {} for sample {} in region {} and channel {}'.format(
              central_or_shift, sample_name, region_name, channel_name
            )
          )
          rles[channel_name][region_name][sample_name][central_or_shift] = []
          rle_filenames = sorted(hdfs.listdir(rle_dir))
          if not rle_filenames:
            logging.warning('Directory {} is empty'.format(rle_dir))
            continue
          rle_arr = []
          for rle_filename in rle_filenames:
            if not rle_filename.endswith('.txt'):
              raise RuntimeError("Unexpected extension in file: %s" % rle_filename)
            with open(rle_filename, 'r') as rle_file:
              for line in rle_file:
                line_stripped = line.rstrip('\n')
                if not REGEX_RLE.match(line_stripped):
                  raise RuntimeError("Unexpected line found in %s: %s" % (rle_filename, line_stripped))
                rle = line_stripped
                if rle in rle_arr:
                  logging.error(
                    "Duplicate event %s found in channel %s, region %s, sample %s, systematics %s" % \
                    (rle, channel_name, region_name, sample_name, central_or_shift)
                  )
                  has_errors = True
                  continue
                rle_arr.append(rle)
          logging.debug(
            'Found {} events in sample {}, region {}, systematics {}, channel {}'.format(
              len(rle_arr), sample_name, region_name, central_or_shift, channel_name
            )
          )
          rles[channel_name][region_name][sample_name][central_or_shift].extend(rle_arr)
  return rles, has_errors

def build_rle_file(rles, output):
  rles_aggregated = collections.OrderedDict()
  region_plus_sys_arr = collections.OrderedDict()
  for channel in rles:
    rles_aggregated[channel] = collections.OrderedDict()
    region_plus_sys_arr[channel] = []
    for region in rles[channel]:
      for sample_name in rles[channel][region]:
        if sample_name not in rles_aggregated[channel]:
          rles_aggregated[channel][sample_name] = collections.OrderedDict()
        for central_or_shift in rles[channel][region][sample_name]:
          region_plus_sys = region + '_' + central_or_shift
          if region_plus_sys not in region_plus_sys_arr:
            region_plus_sys_arr[channel].append(region_plus_sys)
          for rle in rles[channel][region][sample_name][central_or_shift]:
            assert(REGEX_RLE.match(rle))
            if rle not in rles_aggregated[channel][sample_name]:
              rles_aggregated[channel][sample_name][rle] = []
            rles_aggregated[channel][sample_name][rle].append(region_plus_sys)
  output_file = ROOT.TFile(output, 'recreate')
  for channel in rles_aggregated:
    channel_dir = output_file.mkdir(channel)
    channel_dir.cd()
    event_count = 0
    for sample_name in rles_aggregated[channel]:
      tree = ROOT.TTree(sample_name, sample_name)
      run = array.array('I', [0])
      luminosityBlock = array.array('I', [0])
      event = array.array('L', [0])
      region_plus_sys_brs = collections.OrderedDict()
      for region_plus_sys in region_plus_sys_arr[channel]:
        region_plus_sys_brs[region_plus_sys] = array.array('I', [0])
      tree.Branch('run', run, 'run/i')
      tree.Branch('luminosityBlock', luminosityBlock, 'luminosityBlock/i')
      tree.Branch('event', event, 'event/l')
      for region_plus_sys in region_plus_sys_brs:
        tree.Branch(region_plus_sys, region_plus_sys_brs[region_plus_sys], '%s/i' % region_plus_sys)
      event_count_sample = len(rles_aggregated[channel][sample_name])
      logging.info(
        'Found a total of {} events in sample {} and channel {}'.format(
          event_count_sample, sample_name, channel
        )
      )
      event_count += event_count_sample
      for rle in rles_aggregated[channel][sample_name]:
        rle_split = rle.split(':')
        run[0] = int(rle_split[0])
        luminosityBlock[0] = int(rle_split[1])
        event[0] = int(rle_split[2])
        for region_plus_sys in region_plus_sys_brs:
          region_plus_sys_brs[region_plus_sys][0] = int(region_plus_sys in rles_aggregated[channel][sample_name][rle])
        tree.Fill()
      output_file.Write()
    logging.info('Found a total of {} events in channel {}'.format(event_count, channel))
    logging.info('Wrote file {}'.format(output))

def validate_data(rles):
  has_errors = False
  for channel in rles:
    validation_set = collections.OrderedDict()
    has_errors_channel = False
    for region in rles[channel]:
      validation_set[region] = collections.OrderedDict()
      for sample_name in rles[channel][region]:
        if 'Run201' not in sample_name:
          continue
        for central_or_shift in rles[channel][region][sample_name]:
          for rle in rles[channel][region][sample_name][central_or_shift]:
            if rle not in validation_set[region]:
              validation_set[region][rle] = collections.OrderedDict()
            if sample_name in validation_set[region][rle]:
              validation_set[region][rle][sample_name].append(central_or_shift)
            else:
              if validation_set[region][rle]:
                logging.error(
                  "Found duplicates in channel {} and region {} for event {}: samples {} and {}".format(
                    channel, region, rle, sample_name, ', '.join(validation_set[region][rle].keys())
                  )
                )
                has_errors_channel = True
              validation_set[region][rle][sample_name] = [ central_or_shift ]
      if not has_errors_channel:
        logging.info('No overlapping data events found in channel {} and region {}'.format(channel, region))
      has_errors = has_errors or has_errors_channel
  return has_errors

def validate_regions(rles):
  has_errors = False
  for channel in rles:
    validation_set = collections.OrderedDict()
    for region in rles[channel]:
      if 'Fakeable_mcClosure' in region:
        continue
      for sample_name in rles[channel][region]:
        if sample_name not in validation_set:
          validation_set[sample_name] = collections.OrderedDict()
        for central_or_shift in rles[channel][region][sample_name]:
          if central_or_shift not in validation_set[sample_name]:
            validation_set[sample_name][central_or_shift] = collections.OrderedDict()
          for rle in rles[channel][region][sample_name][central_or_shift]:
            if rle not in validation_set[sample_name][central_or_shift]:
              validation_set[sample_name][central_or_shift][rle] = []
            if region not in validation_set[sample_name][central_or_shift][rle]:
              validation_set[sample_name][central_or_shift][rle].append(region)
    for sample_name in validation_set:
      has_errors_sample = False
      for central_or_shift in validation_set[sample_name]:
        for rle in validation_set[sample_name][central_or_shift]:
          if len(validation_set[sample_name][central_or_shift][rle]) > 1:
            logging.error(
              "Found duplicates in channel {} and sample {} for event {}: regions {}".format(
                channel, sample_name, rle, ', '.join(validation_set[sample_name][central_or_shift][rle])
              )
            )
            has_errors_sample = True
      if not has_errors_sample:
        logging.info('No overlapping events found between regions for sample {} in channel {}'.format(sample_name, channel))
      has_errors = has_errors or has_errors_sample
  return has_errors

def validate_channels(rles):
  validation_set = collections.OrderedDict()
  for channel in rles:
    for region in rles[channel]:
      if 'Tight' not in region:
        continue
      for sample_name in rles[channel][region]:
        if sample_name not in validation_set:
          validation_set[sample_name] = collections.OrderedDict()
        for central_or_shift in rles[channel][region][sample_name]:
          if central_or_shift not in validation_set[sample_name]:
            validation_set[sample_name][central_or_shift] = collections.OrderedDict()
          for rle in rles[channel][region][sample_name][central_or_shift]:
            if rle not in validation_set[sample_name][central_or_shift]:
              validation_set[sample_name][central_or_shift][rle] = collections.OrderedDict()
            validation_set[sample_name][central_or_shift][rle][channel] = region
  has_errors = False
  for sample_name in validation_set:
    for central_or_shift in validation_set[sample_name]:
      for rle in validation_set[sample_name][central_or_shift]:
        if len(validation_set[sample_name][central_or_shift][rle]) > 1:
          if '2los_1tau' in validation_set[sample_name][central_or_shift][rle]           and \
              validation_set[sample_name][central_or_shift][rle]['2los_1tau'] == 'Tight' and \
             '2lss_1tau' in validation_set[sample_name][central_or_shift][rle]           and \
              validation_set[sample_name][central_or_shift][rle]['2lss_1tau'] == 'Tight_OS_OS':
            continue
          logging.error(
            "Found the same event {} from sample {} in multiple channels: {}".format(
              rle,
              sample_name,
              ', '.join([
                '%s (region %s, systematics %s)' % (
                  channel,
                  validation_set[sample_name][central_or_shift][rle][channel],
                  central_or_shift
                ) for channel in validation_set[sample_name][central_or_shift][rle]
              ])
            )
          )
          has_errors = True
  if not has_errors:
    logging.info("No overlaps found between the signal regions of channels: {}".format(', '.join(rles.keys())))
  return has_errors

if __name__ == '__main__':

  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'directory', required = True, nargs = '+',
    help = 'R|Path(s) containing run-lumi-event text files',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = False, default = '',
    help = 'R|Output ROOT file for MEM jobs',
  )
  parser.add_argument('-w', '--whitelist',
    type = str, dest = 'whitelist', metavar = 'channel', required = False, nargs = '+', default = [],
    help = 'R|Channels to exclude from the validation',
  )
  parser.add_argument('-b', '--blacklist',
    type = str, dest = 'blacklist', metavar = 'channel', required = False, nargs = '+', default = [],
    help = 'R|Channels to validate',
  )
  parser.add_argument('-s', '--all-systematics',
    dest = 'all_systematics', action = 'store_true', default = False,
    help = 'R|Consider all systematics',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Enable verbose output',
  )
  args = parser.parse_args()

  logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)
  rles, input_errors = get_rles(args.input, args.whitelist, args.blacklist, args.all_systematics)

  data_errors = validate_data(rles)
  region_errors = validate_regions(rles)
  channel_errors = validate_channels(rles)

  if input_errors or data_errors or region_errors or channel_errors:
    raise RuntimeError('Did not pass validation')

  if args.output:
    build_rle_file(rles, args.output)
