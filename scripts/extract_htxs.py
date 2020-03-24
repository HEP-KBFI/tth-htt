#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.hdfs import hdfs
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging

import os.path
import argparse
import re

HADD_STAGE2_RE = re.compile('.+\d+-\d+$')

def get_evt_subdir_names(fn):
  assert(hdfs.isfile(fn))
  fptr = ROOT.TFile.Open(fn, 'read')
  assert(fptr)
  logging.info('Opened file {}'.format(fptr.GetName()))

  results = {}
  root_keys = [ k.GetName() for k in fptr.GetListOfKeys() ]
  for root_key in root_keys:
    dir_cand = fptr.Get(root_key)
    if type(dir_cand) != ROOT.TDirectoryFile:
      continue
    evt_dir_name = os.path.join(root_key, 'sel', 'evt')
    evt_dir = fptr.Get(evt_dir_name)
    if not evt_dir:
      continue
    evt_dir_keys = sorted(
      os.path.join(evt_dir_name, k.GetName()) for k in evt_dir.GetListOfKeys() if k.GetName().startswith('htxs_')
    )
    results[root_key] = evt_dir_keys

  logging.info('Closing file: {}'.format(fptr.GetName()))
  fptr.Close()
  return results

def copy_dirs(fn, fo):
  root_keys = get_evt_subdir_names(fn)

  for root_key in root_keys:
    fptr = ROOT.TFile.Open(fn, 'read')
    logging.info('Opened file {} to copy {}'.format(fptr.GetName(), root_key))
    for evt_subdir_name in root_keys[root_key]:
      evt_dir_key = os.path.basename(evt_subdir_name)
      evt_subdir = fptr.Get(evt_subdir_name)
      evt_subdir.ReadAll()
      out_key = os.path.join(root_key, evt_dir_key)
      fo.mkdir(out_key)
      fo.cd(out_key)
      evt_subdir.GetList().Write()
    logging.info('Closing file {} after copying {}'.format(fptr.GetName(), root_key))
    fptr.Close()

def get_hadd_stage2(input_paths):
  results = {}
  for input_path in input_paths:
    path_split = [ subpath for subpath in input_path.split(os.path.sep) if subpath != '' ]
    nof_levels = len(path_split)
    if not ( 5 < nof_levels < 11 ):
      raise ValueError("Invalid path: %s" % input_path)

    current_paths = [ input_path ]
    if nof_levels == 6:
      assert(len(current_paths) == 1)
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
          next_paths.append(region_path)
      current_paths = next_paths
      nof_levels += 1
    if nof_levels == 9:
      next_paths = []
      for current_path in current_paths:
        for next_path in hdfs.listdir(current_path):
          next_path_basename = os.path.basename(next_path)
          if next_path_basename == 'hadd':
            next_paths.append(next_path)
      current_paths = next_paths
      nof_levels += 1
    if nof_levels == 10:
      next_paths = []
      for current_path in current_paths:
        candidate_files = []
        for candidate_file in hdfs.listdir(current_path):
          if not hdfs.isfile(candidate_file):
            continue
          candidate_file_basename = os.path.basename(candidate_file)
          if candidate_file_basename.startswith('hadd_stage2') and \
             not HADD_STAGE2_RE.match(candidate_file_basename.split('.')[0]):
            candidate_files.append(candidate_file)
        if candidate_files:
          assert(len(candidate_files) == 1)
          next_paths.append(candidate_files[0])
      current_paths = next_paths
    for current_path in current_paths:
      current_path_split = [ subpath for subpath in current_path.split(os.path.sep) if subpath != '' ]
      channel = current_path_split[7]
      region = current_path_split[8]
      channel_region = '{}_{}'.format(channel, region)
      if channel_region in results:
        raise RuntimeError(
          "Found two paths corresponding to the same channel (%s) and region (%s): %s and %s" % \
          (channel, region, current_path, results[channel_region])
        )
      results[channel_region] = current_path
      logging.debug(
        'Found hadd stage2 file corresponding to channel {} and region {}: {}'.format(channel, region, current_path)
      )

  return [ results[k] for k in sorted(results.keys()) ]

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'path', required = True, nargs = '+',
    help = 'R|Search paths for hadd stage2 files',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = True,
    help = 'R|Output file',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Enable verbose output',
  )
  args = parser.parse_args()
  logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)

  output_dir = os.path.dirname(os.path.abspath(args.output))
  if not hdfs.isdir(output_dir):
    raise RuntimeError("No such directory: %s" % output_dir)

  fns = get_hadd_stage2(args.input)
  foptr = ROOT.TFile.Open(args.output, 'recreate')
  logging.info('Creating file: {}'.format(foptr.GetName()))
  for fn in fns:
    copy_dirs(fn, foptr)
  logging.info('Writing file: {}'.format(foptr.GetName()))
  foptr.Write()
  foptr.Close()
