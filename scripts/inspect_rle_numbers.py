#!/usr/bin/env python

import os
import collections
import logging
import sys
import re
import argparse
import ROOT
import array

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

OUTPUT_RLE = 'output_rle'
REGEX_RLE = re.compile('^(\d+):(\d+):(\d+)$')
SAMPLES_EXCLUDE = [ 'hadd' ]
SYSTEMATICS_EXCLUDE = [ 'addBackgrounds', 'hadd' ]

def get_input_paths(input_path_candidates):
  input_paths = []
  channels = {}
  for input_path_candidate in input_path_candidates:
    input_path = input_path_candidate
    if input_path_candidate.rstrip(os.path.sep).split(os.path.sep)[-1] != OUTPUT_RLE:
      input_path = os.path.join(input_path_candidate, OUTPUT_RLE)
    if not os.path.isdir(input_path):
      raise ValueError("No such directory: %s" % input_path)
    input_paths.append(input_path)
    input_path_channels = os.listdir(input_path)
    for channel in input_path_channels:
      if channel in channels:
        raise RuntimeError("Channel %s found in two areas: %s and %s" % (channel, input_path, channels[channel]))
      channels[channel] = input_path
  return input_paths

def get_rles(input_paths):
  rles = collections.OrderedDict()
  for input_path in input_paths:
    for channel_name in sorted(os.listdir(input_path)):
      logging.debug('Found channel: {}'.format(channel_name))
      channel_dir = os.path.join(input_path, channel_name)
      rles[channel_name] = collections.OrderedDict()
      for region_name in sorted(os.listdir(channel_dir)):
        logging.debug('Found region {} in channel {}'.format(channel_name, region_name))
        rles[channel_name][region_name] = collections.OrderedDict()
        region_dir = os.path.join(channel_dir, region_name)
        for sample_name in sorted(os.listdir(region_dir)):
          if sample_name in SAMPLES_EXCLUDE:
            continue
          logging.debug('Found sample {} in region {} and channel {}'.format(sample_name, region_name, channel_name))
          rles[channel_name][region_name][sample_name] = collections.OrderedDict()
          sample_dir = os.path.join(region_dir, sample_name)
          for central_or_shift in sorted(os.listdir(sample_dir)):
            if central_or_shift in SYSTEMATICS_EXCLUDE:
              continue
            logging.debug(
              'Found systematics {} for sample {} in region {} and channel {}'.format(
                central_or_shift, sample_name, region_name, channel_name
              )
            )
            rles[channel_name][region_name][sample_name][central_or_shift] = []
            rle_dir = os.path.join(sample_dir, central_or_shift)
            rle_basenames = sorted(os.listdir(rle_dir))
            if not rle_basenames:
              logging.warning('Directory {} is empty'.format(rle_dir))
              continue
            for rle_basename in rle_basenames:
              rle_filename = os.path.join(rle_dir, rle_basename)
              if not rle_filename.endswith('.txt'):
                raise RuntimeError("Unexpected extension in file: %s" % rle_filename)
              rle_arr = []
              with open(rle_filename, 'r') as rle_file:
                for line in rle_file:
                  line_stripped = line.rstrip('\n')
                  if not REGEX_RLE.match(line_stripped):
                    raise RuntimeError("Unexpected line found in %s: %s" % (rle_filename, line_stripped))
                  rle_arr.append(line_stripped)
              logging.debug('Found {} events in file {}'.format(len(rle_arr), rle_filename))
              rles[channel_name][region_name][sample_name][central_or_shift].extend(rle_arr)
  return rles

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

def validate_data(rles):
  for channel in rles:
    validation_set = collections.OrderedDict()
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
                raise RuntimeError(
                  "Found duplicates in channel %s and region %s for event %s: %s and %s" % \
                  (channel, region, rle, sample_name, ', '.join(validation_set[region][rle].keys()))
                )
              validation_set[region][rle][sample_name] = [ central_or_shift ]
      logging.debug('No overlapping data events found in channel {}'.format(channel))

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
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Enable verbose output',
  )
  args = parser.parse_args()

  logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)
  input_paths = get_input_paths(args.input)
  rles = get_rles(input_paths)

  if args.output:
    build_rle_file(rles, args.output)

  # find inconsistencies between data datasets
  validate_data(rles)

  #TODO find inconsistencies between different regions in the same channel
  #TODO find inconsistencies between different channels
