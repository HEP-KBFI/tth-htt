#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017 as samples

import argparse
import getpass
import os
import shutil

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
parser.add_argument(
  '-i', '--input', dest = 'input', metavar = 'file', required = True, type = str,
  help = 'R|Input file containing a list of samples to be copied over',
)
parser.add_argument(
  '-d', '--destination', dest = 'destination', metavar = 'path', required = False, type = str,
  default = '/hdfs/local/%s/nanoProduction/' % getpass.getuser(),
  help = 'R|Destination',
)
parser.add_argument(
  '-p', '--part1-fraction', dest = 'part1_fraction', metavar = 'number', required = False, type = float, default = 0.25,
  help = 'R|Fraction of samples to be copied for part1 (between 0. and 1.)',
)
args = parser.parse_args()

input_file     = args.input
dest           = args.destination
part1_fraction = args.part1_fraction

if not (0. < part1_fraction < 1.):
  raise ValueError('part1_fraction must be between 0 and 1')

if not os.path.isfile(input_file):
  raise ValueError('No such file: %s' % input_file)

samples_to_copy = []

with open(input_file, 'r') as f:
  for line in f:
    line_split = line.split()
    if len(line_split) == 0:
      continue
    sample_raw = line_split[0]
    sample_split = sample_raw.split('/')
    assert(len(sample_split) == 5)
    sample = '/'.join(sample_split[:-1])
    part = sample_split[-1]
    assert (part in ['part1', 'part2'])
    if sample not in samples_to_copy:
      if sample not in samples:
        raise RuntimeError('No such sample in dictionary: %s' % sample)
      samples_to_copy.append(sample)

def copy_files(start, end, src, dst):
  file_idxs = list(range(start, end + 1))
  for idx, file_idx in enumerate(file_idxs):
    src_file = os.path.join(src, '%04d' % (file_idx  // 1000), 'tree_%d.root' % file_idx)
    dst_file = os.path.join(dst, '%04d' % ((idx + 1) // 1000), 'tree_%d.root' % (idx + 1))
    if not os.path.isfile(src_file):
      raise RuntimeError('No such file: %s' % src_file)
    dst_file_dir = os.path.dirname(dst_file)
    if not os.path.isdir(dst_file_dir):
      os.makedirs(dst_file_dir)
    print('Copying %s to %s' % (src_file, dst_file))
    shutil.copyfile(src_file, dst_file)

for sample in samples_to_copy:
  nof_files = samples[sample]['nof_files']
  nof_files_part1 = int(part1_fraction * nof_files)
  nof_files_part2 = nof_files - nof_files_part1
  assert(len(samples[sample]['local_paths']) == 1)
  sample_path = samples[sample]['local_paths'][0]['path']
  sample_dest_part = os.path.join(dest, '{}_part%d'.format(samples[sample]['process_name_specific']))
  sample_dest_part1 = sample_dest_part % 1
  sample_dest_part2 = sample_dest_part % 2
  copy_files(1,                   nof_files_part1, sample_path, sample_dest_part1)
  copy_files(nof_files_part1 + 1, nof_files,       sample_path, sample_dest_part2)

