#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.hdfs import hdfs, logging
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import argparse
import os
import re

DATASET_REGEX = re.compile("^/(.*)/(.*)/[0-9A-Za-z]+$")
COMPLETED_REGEX = re.compile('.*finished.*100\.0%.*')

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'directory', required = True, nargs = '+',
    help = 'R|CRAB directory',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = True,
    help = 'R|Output file name',
  )
  parser.add_argument('-c', '--contains',
    type = str, dest = 'contains', metavar = 'string', required = False, default = '',
    help = 'R|String a CRAB subdirectory must contain',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  crab_dirs = args.input
  output_fn = args.output
  req_str = args.contains

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  for crab_dir in crab_dirs:
    if not os.path.isdir(crab_dir):
      raise ValueError("No such directory: %s" % crab_dir)

  output_fn_dir = os.path.dirname(output_fn)
  if not os.path.isdir(output_fn_dir):
    raise ValueError("No such directory: %s" % output_fn_dir)

  crab_paths = []
  for crab_dir in crab_dirs:
    for crab_subdir in os.listdir(crab_dir):
      if req_str and req_str not in crab_subdir:
        continue
      crab_subdir_fp = os.path.join(crab_dir, crab_subdir)
      if not os.path.isdir(crab_subdir_fp):
        continue
      crab_logfile = os.path.join(crab_subdir_fp, 'crab.log')
      if not os.path.isfile(crab_logfile):
        continue

      is_completed = False
      dataset_name = ''
      output_dir = ''
      with open(crab_logfile, 'r') as crab_logfile_ptr:
        for line in crab_logfile_ptr:
          line_stripped = line.rstrip('\n')
          if line_stripped.startswith('config.Data.inputDataset'):
            dataset_name = line_stripped.replace("'", '').split()[-1]
          if line_stripped.startswith('config.Data.outLFNDirBase'):
            output_dir = line_stripped.replace("'", '').split()[-1]
          if COMPLETED_REGEX.match(line_stripped):
            is_completed = True
            break
      if not is_completed:
        continue
      dataset_match = DATASET_REGEX.match(dataset_name)
      if not dataset_name or not dataset_match:
        raise RuntimeError("Unable to parse dataset name from file: %s" % crab_logfile)
      if not output_dir:
        raise RuntimeError("Unable to parse output directory from file: %s" % crab_logfile)
      version = os.path.basename(output_dir)
      userName = os.path.basename(os.path.dirname(output_dir))
      requestName = '%s_%s__%s' % (version, dataset_match.group(1), dataset_match.group(2))
      max_requestname_len = 160 - len(userName)
      if len(requestName) > max_requestname_len:
        requestName = requestName[:max_requestname_len]
      crab_path = os.path.join('/hdfs', 'cms', output_dir[1:], dataset_match.group(1), requestName)
      if hdfs.isdir(crab_path):
        crab_paths.append(crab_path)
        logging.debug("Found directory: {}".format(crab_path))
      else:
        logging.warning("No such directory found: {}".format(crab_path))

  with open(output_fn, 'w') as output_fptr:
    output_fptr.write('\n'.join(list(sorted(crab_paths))))
