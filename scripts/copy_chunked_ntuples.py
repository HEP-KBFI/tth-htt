#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.hdfs import hdfs
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import argparse
import os
import math
import re
import copy

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'directory', required = True,
    help = 'R|Directory containing the results of chunked CRAB jobs',
  )
  parser.add_argument('-d', '--datasets',
    type = str, dest = 'datasets', metavar = 'file', required = True,
    help = 'R|File containing list of datasets',
  )
  parser.add_argument('-f', '--fileblock-datasets',
    type = str, dest = 'fileblock_datasets', metavar = 'file', required = False,
    default = os.path.join(
      os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'NanoAOD', 'test', 'datasets_fileblock_err.txt'
    ),
    help = 'R|File containing list of datasets that have file block errors',
  )
  parser.add_argument('-n', '--nevents',
    type = int, dest = 'nevents', metavar = 'int', required = False, default = 50000,
    help = 'R|Number of events processed in a CRAB job',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'directory', required = True,
    help = 'R|Output directory where the new Ntuples will be copied to',
  )
  parser.add_argument('-c', '--copy',
    dest = 'copy', action = 'store_true', default = False,
    help = 'R|Copy the Ntuples to the destination',
  )
  args = parser.parse_args()

  input_dir = args.input
  datasets_filename = args.datasets
  datasets_fileblock_filename = args.fileblock_datasets
  crab_nevents = args.nevents
  output_dir = args.output
  do_copy = args.copy

  # Validate inputs
  if not hdfs.isdir(args.input):
    raise ValueError("No such directory: %s" % input_dir)
  if not os.path.isfile(datasets_filename):
    raise ValueError("No such file: %s" % datasets_filename)
  if not os.path.isfile(datasets_fileblock_filename):
    raise ValueError("No such file: %s" % datasets_fileblock_filename)
  assert(crab_nevents > 0)

  # Find common datasets that have fileblock errors and have been processed
  datasets_fileblock = {}
  with open(datasets_fileblock_filename, 'r') as datasets_fileblock_file:
    for line in datasets_fileblock_file:
      line_stripped = line.rstrip()
      if not line_stripped:
        continue
      line_split = line_stripped.split()
      datasets_fileblock[line_split[0]] = int(math.ceil(float(line_split[1]) / crab_nevents))

  dataset_dirs = hdfs.listdir(input_dir)
  version = os.path.basename(input_dir)

  datasets_common = {}
  with open(datasets_filename, 'r') as datasets_file:
    for line in datasets_file:
      line_stripped = line.rstrip()
      if not line_stripped:
        continue
      line_split = line_stripped.split()

      dataset_name = line_split[0]
      if dataset_name not in datasets_fileblock:
        continue

      dataset_name_split = dataset_name.split('/')
      dataset_part_head = dataset_name_split[1]
      dataset_part_tail = dataset_name_split[2]

      expected_dir = os.path.join(input_dir, dataset_part_head)
      if expected_dir not in dataset_dirs:
        print("Unable to find directory {} for dataset {}".format(expected_dir, dataset_name))
        continue

      nchunks_expected = datasets_fileblock[dataset_name]
      requestName = '%s_CHUNK(?P<chunk_idx>\d+)_%s__%s' % (version, dataset_part_head, dataset_part_tail)
      if len(requestName) > 152:
        requestName = requestName[:152]
      chunkdir_regex = re.compile(requestName)

      chunk_arr = []
      has_multiple_tasks = False
      for subdir in hdfs.listdir(expected_dir):
        task_dirs = hdfs.listdir(subdir)
        if len(task_dirs) > 1:
          print("Detected multiple task directories: {}".format(', '.join(task_dirs)))
          has_multiple_tasks = True
          break
        elif not task_dirs:
          print("No task dir found in {}".format(subdir))
          continue

        subdir_name = os.path.basename(subdir)
        subdir_match = re.match(subdir_name)
        if not subdir_match:
          print("Unable to find match for: {}".format(subdir_name))
        else:
          chunk_idx = int(subdir_match.group('chunk_idx'))
          chunk_arr.append({ 'idx' : chunk_idx, 'path' : task_dirs[0] })
      if has_multiple_tasks:
        continue

      chunk_arr = list(sorted(chunk_arr, key = lambda chunk: chunk['idx']))
      chunk_idxs = list(map(lambda chunk: chunk['idx'], chunk_arr))
      missing_chunks = list(set(range(1, max(chunk_idxs) + 1)) - set(chunk_idxs))
      if missing_chunks:
        print("Found missing chunks: {}".format(', '.join(map(str, missing_chunks))))
        continue

      if len(chunk_arr) != nchunks_expected:
        print("Expected {} chunks, but got {} chunks".format(nchunks_expected, len(chunk_idxs)))
        continue

      process_name = line_split[3]
      datasets_common[dataset_name] = {
        'process_name' : process_name,
        'chunks'       : copy.deepcopy(chunk_arr),
      }
  print("Found {} chunked datasets in directory {}".format(len(datasets_common), input_dir))

  # Map input directory to the output directory
  tree_re = re.compile('^tree_(?P<idx>\d+)\.root$')
  tree_re_func = lambda path: int(tree_re.match(os.path.basename(path)).group('idx'))

  for dataset_name in datasets_common:
    print("Handling files in dataset {}".format(dataset_name))
    process_name = datasets_common[dataset_name]['process_name']
    chunks = datasets_common[dataset_name]['chunks']
    output_basedir = os.path.join(output_dir, process_name)

    # The copying is done such that first subdir of the first chunk is copied, followed by second subdir of
    # the first chunk etc until all subdirs in the first chunk have been exhausted; then the loop goes over to
    # the second chunk and repeats the sequence etc until all chunks have been exhausted.
    # Example: the 1st chunk has 2200 root files, the 2nd chunk has 1100 files and the 3rd chunk has 700 files:
    #
    # chunk1/0000/tree_1.root -> out/0000/tree_1.root
    # ..
    # chunk1/0000/tree_999.root -> out/0000/tree_999.root
    # chunk1/0001/tree_1000.root -> out/0001/tree_1.root
    # ..
    # chunk1/0001/tree_1999.root -> out/0001/tree_1999.root
    # chunk1/0002/tree_2000.root -> out/0002/tree_2000.root
    # ..
    # chunk1/0002/tree_2200.root -> out/0002/tree_2200.root
    # chunk2/0000/tree_1.root -> out/0002/tree_2201.root
    # ..
    # chunk2/0000/tree_799.root -> out/0002/tree_2999.root
    # chunk2/0000/tree_800.root -> out/0003/tree_3000.root
    # ..
    # chunk2/0000/tree_999.root -> out/0003/tree_3199.root
    # chunk2/0001/tree_1000.root -> out/0003/tree_3200.root
    # ..
    # chunk2/0001/tree_1100.root -> out/0003/tree_3300.root
    # chunk3/0000/tree_1.root -> out/0003/tree_3301.root
    # ..
    # chunk3/0000/tree_699.root -> out/0003/tree_3999.root
    # chunk3/0000/tree_700.root -> out/0004/tree_4000.root
    #
    # NOTE: if a ROOT file is missing, then the index of target ROOT file is still incremented. This ensures 1-to-1
    # correspondence b/w the original files and the copied files in case the CRAB jobs are still running or the jobs
    # have died beyond revival. For instance, if tree_699.root and tree_701.root are present in the first chunk but
    # tree_700.root is missing, file tree_701.root will be copied as tree_701.root (and not be renamed to tree_700.root).
    # The 1-to-1 correspondence will be violated if the last ROOT file in the last subdir of a chunk is missing.

    latest_idx = 0
    latest_task = -1
    for chunk in chunks:
      print("Copying chunk {} to {}".format(chunk['path'], output_basedir))

      present_paths = []
      for task_subdir in hdfs.listdir(chunk['path']):
        present_paths.extend(filter(lambda path: path.endswith('.root'), hdfs.listdir(task_subdir)))
      present_paths = list(sorted(present_paths, key = tree_re_func))

      max_idx = tree_re_func(present_paths[-1])
      expected_paths = [
        os.path.join(chunk['path'], '%04d' % (idx // 1000), 'tree_%d.root' % idx) for idx in range(1, max_idx + 1)
      ]
      for expected_path in expected_paths:
        latest_idx += 1
        current_task = latest_idx // 1000
        output_taskdir = os.path.join(output_basedir, '%04d' % current_task)
        if current_task != latest_task:
          hdfs.mkdir(output_taskdir)

        output_file = os.path.join(output_taskdir, 'tree_%d.root' % latest_idx)
        if expected_path in present_paths:
          print("Copying {} to {}".format(expected_path, output_file))
          if do_copy:
            hdfs.copy(expected_path, output_file)
        else:
          print("File {} does not exist -> skipping {}".format(expected_path, output_file))
