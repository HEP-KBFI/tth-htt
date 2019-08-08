#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.hdfs import hdfs, logging
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import argparse
import datetime
import os
import re

DATASET_REGEX = re.compile("^/(.*)/(.*)/[0-9A-Za-z]+$")
COMPLETED_REGEX = re.compile('.*finished.*100\.0%.*')
TREE_REGEX = re.compile('tree_(?P<idx>\d+)\.root')

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
    type = str, dest = 'contains', metavar = 'string', required = False, nargs = '+', default = [],
    help = 'R|String a CRAB subdirectory must contain',
  )
  parser.add_argument('-t', '--threshold',
    type = int, dest = 'threshold', metavar = 'percentage', required = False, default = 100,
    help = 'R|Threshold of completed jobs',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  crab_dirs = args.input
  output_fn = args.output
  req_strs = args.contains

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  for crab_dir in crab_dirs:
    if not os.path.isdir(crab_dir):
      raise ValueError("No such directory: %s" % crab_dir)

  output_fn_dir = os.path.dirname(output_fn)
  if not os.path.isdir(output_fn_dir):
    raise ValueError("No such directory: %s" % output_fn_dir)

  crab_paths = {}
  for crab_dir in crab_dirs:
    for crab_subdir in os.listdir(crab_dir):
      if req_strs:
        is_match = False
        for req_str in req_strs:
          if req_str in crab_subdir:
            is_match = True
            break
        if not is_match:
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
      nof_jobs = -1
      with open(crab_logfile, 'r') as crab_logfile_ptr:
        for line in crab_logfile_ptr:
          line_stripped = line.rstrip('\n')
          if line_stripped.startswith('Jobs status:'):
            nof_jobs = int(line_stripped.replace('/', ' ').replace(')', '').strip().split()[-1])
          if line_stripped.startswith('config.Data.inputDataset'):
            dataset_name = line_stripped.replace("'", '').split()[-1]
          if line_stripped.startswith('config.Data.outLFNDirBase'):
            output_dir = line_stripped.replace("'", '').split()[-1]
          if COMPLETED_REGEX.match(line_stripped):
            is_completed = True
            break
      chunk_str = crab_subdir[crab_subdir.find('CHUNK'):crab_subdir.find('CHUNK') + len('CHUNK') + 1] if 'CHUNK' in crab_subdir else ''
      dataset_match = DATASET_REGEX.match(dataset_name)
      logging.debug("Found dataset: {}".format(dataset_name))
      if not dataset_name or not dataset_match:
        raise RuntimeError("Unable to parse dataset name from file: %s" % crab_logfile)
      if not output_dir:
        raise RuntimeError("Unable to parse output directory from file: %s" % crab_logfile)
      if nof_jobs < 0:
        raise RuntimeError("Unable to parse total number of jobs from file: %s" % crab_logfile)
      version = os.path.basename(output_dir)
      version_date = version.split('_')[1]
      prefix = '{}_{}'.format(version, chunk_str) if chunk_str else version
      userName = os.path.basename(os.path.dirname(output_dir))
      dataset_requestName = '%s__%s' % (dataset_match.group(1), dataset_match.group(2))
      requestName = '%s_%s' % (prefix, dataset_requestName)
      max_requestname_len = 160 - len(userName)
      if len(requestName) > max_requestname_len:
        requestName = requestName[:max_requestname_len]
      crab_path = os.path.join('/hdfs', 'cms', output_dir[1:], dataset_match.group(1), requestName)
      if hdfs.isdir(crab_path):
        logging.debug("Found directory: {}".format(crab_path))
        subdirs = hdfs.listdir(crab_path)
        if len(subdirs) != 1:
          raise RuntimeError("Expected exactly one subdir in %s" % crab_path)
        subdir = subdirs[0]
        root_files = [
          root_file for subsubdir in hdfs.listdir(subdir) for root_file in hdfs.listdir(subsubdir) if root_file.endswith('.root')
        ]
        root_idxs = set(map(lambda fn: int(TREE_REGEX.match(os.path.basename(fn)).group('idx')), root_files))
        nof_completed = len(root_idxs) * 100. / nof_jobs
        expected_idxs = set(range(1, nof_jobs + 1))
        assert(not (root_idxs - expected_idxs))
        missing_idxs = expected_idxs - root_idxs
        if not missing_idxs:
          logging.debug("'crab status' claimed failed jobs, but all files are actually present")
          is_completed = True
        else:
          logging.debug("The following {} ROOT file(s) are missing in {}: {}".format(
            len(missing_idxs), crab_path, ', '.join(map(str, list(sorted(missing_idxs)))))
          )
          logging.debug("Job completion is at {}% out of {} jobs".format(round(nof_completed, 2), nof_jobs))
        if dataset_requestName not in crab_paths:
          crab_paths[dataset_requestName] = { 'date' : version_date, 'crab_path' : crab_path, 'nof_completed' : nof_completed }
        else:
          if is_completed:
            logging.debug("Found duplicates: {} vs {}".format(crab_path, crab_paths[dataset_requestName]['crab_path']))
            current_date = datetime.datetime.strptime(version_date, '%Y%b%d')
            previous_date = datetime.datetime.strptime(crab_paths[dataset_requestName]['date'], '%Y%b%d')
            previous_completed = crab_paths[dataset_requestName]['nof_completed']
            if current_date > previous_date and nof_completed >= previous_completed:
              logging.debug("Favoured {} as it is more recent (and more complete)".format(crab_path))
              crab_paths[dataset_requestName] = { 'date' : version_date, 'crab_path' : crab_path, 'nof_completed' : nof_completed }
            else:
              logging.debug("Favoured {} as it is more recent (and more complete)".format(crab_paths[dataset_requestName]['crab_path']))
          elif nof_completed >= args.threshold:
            logging.debug("Found duplicates: {} vs {}".format(crab_path, crab_paths[dataset_requestName]['crab_path']))
            previous_completed = crab_paths[dataset_requestName]['nof_completed']
            if nof_completed > previous_completed:
              logging.debug("Favoured {} as it is more complete".format(crab_path))
              crab_paths[dataset_requestName] = { 'date' : version_date, 'crab_path' : crab_path, 'nof_completed' : nof_completed }
            else:
              logging.debug("Favoured {} as it is more complete".format(crab_paths[dataset_requestName]['crab_path']))
      else:
        logging.warning("No such directory found: {}".format(crab_path))

  with open(output_fn, 'w') as output_fptr:
    output_fptr.write('\n'.join(list(sorted(
      map(lambda kv: '{} {}%'.format(kv[1]['crab_path'], round(kv[1]['nof_completed'], 2)), crab_paths.items())
    ))) + '\n')
  logging.info("Wrote file {}".format(output_fn))
