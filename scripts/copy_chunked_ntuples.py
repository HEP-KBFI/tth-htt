#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter

import collections
import argparse
import os
import re
import shutil

TREE_RE = re.compile('tree_(?P<idx>\d+).root')

def get_file_idx(path):
  return int(TREE_RE.match(os.path.basename(path)).group('idx'))

def get_file_list(chunk):
  files_to_copy_chunk = []
  taskdirs = [ os.path.join(chunk, p) for p in os.listdir(chunk) ]
  if len(taskdirs) != 1:
    raise RuntimeError("Found multiple tasks in %s" % chunk)

  taskdir = taskdirs[0]
  subdirs = [ os.path.join(taskdir, p) for p in os.listdir(taskdir) ]
  if not subdirs:
    raise RuntimeError("Unable to find any subdirs in %s" % taskdir)

  for subdir in subdirs:
    files_to_copy_chunk.extend(filter(lambda path: path.endswith('.root'), [ os.path.join(subdir, p) for p in os.listdir(subdir) ]))

  files_to_copy_chunk = list(sorted(files_to_copy_chunk, key = get_file_idx))
  return files_to_copy_chunk

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True,
    help = 'R|Input file containing Ntuple locations produced by CRAB',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'path', required = True,
    help = 'R|Output directory where the Ntuples will be copied',
  )
  parser.add_argument('-c', '--copy',
    dest = 'copy', action = 'store_true', default = False,
    help = 'R|Actually execute the copy operation',
  )
  parser.add_argument('-m', '--modify',
    dest = 'modify', action = 'store_true', default = False,
    help = 'R|Modify input file with the new paths',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Enable verbose output',
  )
  args = parser.parse_args()

  logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)

  if not os.path.isfile(args.input):
    raise ValueError("No such file: %s" % args.input)

  # read the input text file to obtain the location of Ntuples that've been processed in chunks
  chunks = {}
  file_input = []
  with open(args.input, 'r') as input_list_file:
    for line in input_list_file:
      line_stripped = line.rstrip('\n')
      line_split = line_stripped.split()
      path = line_split[0]
      comment = float(line_split[1].replace('%', '')) if len(line_split) > 0 else 100.
      if not path:
        continue
      if 'CHUNK' in path:
        chunks[path] = comment
      else:
        file_input.append(line_stripped)

  # collect the paths into chunks
  chunk_pairs = []
  for chunk in chunks:
    if 'CHUNK1' in chunk:
      chunk_other = chunk.replace('CHUNK1', 'CHUNK2')
      if chunk_other in chunks:
        chunk_pairs.append((chunk, chunk_other))
        logging.info("Found pairs: {} and {}".format(chunk, chunk_other))
      else:
        logging.info("Found no complementary location for {}".format(chunk))

  # determine the list of ROOT files that we're going to copy over
  new_lines = {}
  for chunk_pair in chunk_pairs:
    chunk_1 = chunk_pair[0]
    chunk_2 = chunk_pair[1]

    assert ('CHUNK1' in chunk_1)
    chunk_0 = chunk_1.replace('CHUNK1', 'CHUNK0')
    destination = os.path.join(os.path.join(args.output, *chunk_0.split(os.path.sep)[-3:]), '000000_000000')

    file_list_1 = get_file_list(chunk_1)
    file_list_2 = get_file_list(chunk_2)

    missing_subdirs = []

    # copy files from the first chunk verbatim
    copy_relations = collections.OrderedDict()
    for root_file in file_list_1:
      root_file_basename = os.path.basename(root_file)
      root_file_idx = get_file_idx(root_file) // 1000
      dst_subdir = os.path.join(destination, '%04d' % root_file_idx)
      if dst_subdir not in missing_subdirs:
        missing_subdirs.append(dst_subdir)
      copy_relations[root_file] = os.path.join(dst_subdir, root_file_basename)

    # files from the second chunk are added sequentially
    offset = get_file_idx(file_list_1[-1])
    new_idx = offset
    for root_file in file_list_2:
      new_idx += 1
      root_file_basename = 'tree_%d.root' % new_idx
      root_file_idx = new_idx // 1000
      dst_subdir = os.path.join(destination, '%04d' % root_file_idx)
      if dst_subdir not in missing_subdirs:
        missing_subdirs.append(dst_subdir)
      copy_relations[root_file] = os.path.join(dst_subdir, root_file_basename)

    if args.copy:
      for missing_subdir in missing_subdirs:
        if not os.path.isdir(missing_subdir):
          logging.info('Created subdirectory {}'.format(missing_subdir))
          try:
            os.makedirs(missing_subdir)
          except:
            raise RuntimeError("Unable to create directory: %s" % missing_subdir)

    for src_file, dst_file in copy_relations.items():
      logging.debug('Copying file {} to {}'.format(src_file, dst_file))
      if args.copy and not os.path.isfile(dst_file):
        try:
          shutil.copy2(src_file, dst_file)
        except:
          raise RuntimeError("Unable to copy file from %s to %s" % (src_file, dst_file))

    logging.info('Copying done')
    new_lines[os.path.dirname(destination)] = (
        chunks[chunk_1] * len(file_list_1) / 100. + chunks[chunk_2] * len(file_list_2) / 100.
      ) / (len(file_list_1) + len(file_list_2)) * 100.

  if args.modify:
    with open(args.input, 'w') as input_list_file:
      input_list_file.write('\n'.join(file_input) + '\n')
      input_list_file.write('\n'.join(map(lambda kv: '{} {:.2f}%'.format(*kv), new_lines.items())) + '\n')
    logging.info('Rewrote file {}'.format(args.input))

  logging.info('All done')
