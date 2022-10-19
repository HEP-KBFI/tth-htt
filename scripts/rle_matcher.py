#!/usr/bin/env python

'''Example usage:

  ./rle_matcher.py                         \
  -s DoubleEG_Run2016[A,B,C,D,E,F]_v\\d{1} \
  -f ~/test_RLE.txt                        \
  -o ~/sandbox/test_RLE_result.txt         \
  -d /local/karl/RLE_DS16_v2          \
  -v

Explanation:
  -s Specifies the samples you want to process; it can be a precise name or a regular expression [*]
  -f Input RLE list, for which you want corresponding list of ROOT files containing these events
  -o Output file name, where the list of gathered ROOT files are written
  -d Output directory of dump_rle_parallel.py (contains a full list of RLE files, one per each Ntuple)
  -v Enables verbose output

[*] The regular expression must be compatible with Python's re module. You must escape characters with backslash
    in front of them. For example, if you want to match files that contain a single number somewhere in the sample
    name, you'd use
      \d{1}
    as the regex in Python code. This, however, becomes
      \\d{1}
    on the command line.

Note that gathering the list of ROOT files via grepping (i.e. by specifying the full RLE list with -d/--directory option)
doesn't ensure that all RLE numbers have a match (all RLE numbers are grepped at once). If this is a problem, then you
should use -a/--all flag in order to grep each number individually. However, if the number of samples (especially data
samples) or the number of input RLE numbers is large, it will take ages to find the matches. So, unless the input RLE
directory isn't obsolete (and invalid), you shouldn't worry about such corner cases and take it for granted.

NB! The input file you provide can work only for a single MC sample or multiple data samples collected with the same
    trigger.
'''

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_preselected import samples_2017 as samples
from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter

import argparse
import os
import sys
import re
import array
import subprocess

def is_dict_full(d):
  '''Checks whether all values in a given dictionary are present
  Args:
    d: dictionary, which is checked here

  Returns: True, if none of its values are empty strings,
           False otherwise
  '''
  return len(filter(lambda x: x == '', d.values())) == 0

if __name__ == '__main__':
  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 40))
  parser.add_argument('-s', '--sample-name', metavar = 'name', required = True, type = str,
                      help = 'R|Sample name (may be a regex)')
  parser.add_argument('-f', '--file', metavar = 'file', required = True, type = str,
                      help = 'R|Path to file containing a list of RLE numbers')
  parser.add_argument('-o', '--output', metavar = 'file', required = False, type = str, default = '',
                      help = 'R|File where the list of matched ROOT files is saved')
  parser.add_argument('-d', '--directory', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Directory where all RLE numbers are stored')
  parser.add_argument('-a', '--all', dest = 'all', action = 'store_true', default = False,
                      help = 'R|Grep RLE numbers individually (valid only if -d/--directory has been set')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help='R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  rle_file          = args.file
  sample_name       = args.sample_name
  output_file       = args.output
  grep_directory    = args.directory
  grep_individually = args.all
  try:
    sample_name_re = re.compile(sample_name)
  except:
    logging.error("Argument {arg} not a valid regex".format(arg = sample_name))
    sys.exit(1)

  if grep_individually and not grep_directory:
    logging.warning('Option -a/--all has no effect unless you specify -d/--directory')

  if not os.path.isfile(rle_file):
    logging.error("No such file: '{rle_filename}'".format(
      rle_filename = rle_file,
    ))
    sys.exit(1)

  if output_file and not os.path.isdir(os.path.dirname(output_file)):
    logging.error("Parent directory of '{output_file}' doesn't exist".format(
      output_file = output_file,
    ))
    sys.exit(1)

  if grep_directory and not os.path.isdir(grep_directory):
    logging.error("Grep directory '{grep_directory}' doesn't exist".format(
      grep_directory = grep_directory,
    ))
    sys.exit(1)

  sample_keys = {}
  for s_key, s_value in samples.iteritems():
    if sample_name_re.match(s_value['process_name_specific']):
      sample_keys[s_key] = s_value['process_name_specific']

  if not sample_keys:
    logging.error("Invalid sample name: '{sample_name}'".format(sample_name = sample_name))
    sys.exit(1)
  logging.debug("Got the following matches: {matches}".format(matches = ', '.join(sample_keys.keys())))

  # read the RLE numbers and form a dictionary { RLE number : root file it contains it }
  rle_pattern = re.compile('\d+:\d+:\d+')
  rles = {}
  with open(rle_file, 'r') as f:
    for line in f:
      line = line.rstrip('\n')
      if not line: continue

      rle_match = rle_pattern.match(line)
      if not rle_match:
        logging.error("Line '{unmatched_line}' doesn't look like a RLE number".format(
          unmatched_line = line,
        ))
        sys.exit(1)

      rles[line] = []

  # here we try to grep RLE numbers instead of looping over ROOT files
  rle_matched_files = []

  for sample_key in sample_keys:
    # since 2016 Ntuples have no "secondary paths" we can read off the location to the Ntuples trivially
    sample_path = samples[sample_key]['local_paths'][0]['path']
    logging.debug('Considering sample {sample_name}'.format(sample_name = sample_key))

    if grep_directory:

      grep_subdir = os.path.join(grep_directory, sample_keys[sample_key])
      if not os.path.isdir(grep_subdir):
        logging.error("No such directory: '{grep_subdir}'".format(grep_subdir=grep_subdir))
        sys.exit(1)
      logging.debug('Grepping from {grep_dir}'.format(grep_dir=grep_subdir))

      if not grep_individually:
        logging.debug('Grepping RLE numbers all at once')

        # let's create a grep command first
        grep_rle_list = '\\|'.join(rles.keys())
        grep_cmd_str = "grep -nr '%s' %s | awk -F ':' '{print $1}' | uniq" % \
                       (grep_rle_list, os.path.join(grep_subdir, '*'))
        grep_process = subprocess.Popen(
          grep_cmd_str,
          stdout = subprocess.PIPE,
          stderr = subprocess.PIPE,
          shell  = True
        )
        grep_stdout, grep_stderr = grep_process.communicate()
        if grep_stderr:
          logging.error("There was an error:\n%s" % grep_stderr)
          sys.exit(1)

        grep_result = map(os.path.basename, filter(lambda x: x != '', grep_stdout.split()))
        rle_matched_files.extend(map(
          lambda x: os.path.join(
            sample_path, '000%d' % (int(x[:x.rfind('.')]) / 1000), 'tree_{i}.root'.format(i = x[:x.rfind('.')])
          ), grep_result)
        )
        logging.debug('Got {nof_matches} matches in {grep_dir}'.format(
          nof_matches = len(grep_result),
          grep_dir    = grep_subdir,
        ))

      else:
        logging.debug('Grepping each RLE number individually')
        for rle in rles.keys():
          grep_cmd_str = "grep -nr '%s' %s | awk -F ':' '{print $1}' | uniq" % \
                         (rle, os.path.join(grep_subdir, '*'))
          grep_process = subprocess.Popen(
            grep_cmd_str,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell  = True
          )
          grep_stdout, grep_stderr = grep_process.communicate()
          if grep_stderr:
            logging.error("There was an error:\n%s" % grep_stderr)
            sys.exit(1)

          grep_stdout = grep_stdout.rstrip('\n')
          if not grep_stdout:
            logging.warning('Could not get a match for RLE number {rle} and sample {sample_key}'.format(
              rle        = rle,
              sample_key = sample_key,
            ))
            continue

          file_basename = os.path.basename(grep_stdout)
          file_idx = int(file_basename[:file_basename.rfind('.')])
          grep_result = os.path.join(
            sample_path, '000%d' % (file_idx / 1000), 'tree_{i}.root'.format(i = file_idx)
          )
          rles[rle].append(grep_result)
    else:
      # instead of forming a list of files let's loop over the subfolders and the files therein instead
      logging.debug('Looping over the files in {sample_path}'.format(sample_path = sample_path))
      for subdir_ in os.listdir(sample_path):
        subdir = os.path.join(sample_path, subdir_)
        logging.debug('Found subdirectory {subdir}'.format(subdir = subdir))
        for rootfile_ in os.listdir(subdir):
          rootfile = os.path.join(subdir, rootfile_)
          logging.debug("Processing file '{rootfile}'".format(
            rootfile = rootfile,
          ))

          # open the file
          ch_root = ROOT.TChain("Events")
          ch_root.AddFile(rootfile)

          run_a  = array.array('I', [0])
          lumi_a = array.array('I', [0])
          evt_a  = array.array('L', [0])

          ch_root.SetBranchAddress("run",             run_a)
          ch_root.SetBranchAddress("luminosityBlock", lumi_a)
          ch_root.SetBranchAddress("event",           evt_a)

          nof_entries = ch_root.GetEntries()
          for i in range(nof_entries):
            ch_root.GetEntry(i)
            rle_i = ':'.join(map(str, [run_a[0], lumi_a[0], evt_a[0]]))
            if rle_i in rles:
              rles[rle_i].append(rootfile)
              logging.debug("Got a match '{rle_number}'".format(rle_number = rle_i))

  xor = lambda lhs, rhs: bool(lhs) ^ bool(rhs)
  if not xor(grep_directory, grep_individually):
    if not is_dict_full(rles):
      missing_rles = []
      for rle_i in rles:
        if not rles[rle_i]:
          missing_rles.append(rle_i)
      logging.error("There are still some RLE numbers left for which no ROOT file was found: "
                    "{rle_list}".format(
        rle_list = "\n".join(missing_rles),
      ))
    # let's make the list of matched ROOT files unique
    rle_matched_files = []
    for rle_arr in rles.values():
      for rle_v in rle_arr:
        if rle_v not in rle_matched_files:
          rle_matched_files.append(rle_v)
    logging.debug('Found {nof_matches} matches'.format(nof_matches = len(rle_matched_files)))

  logging.debug("Got matches for the following files:")
  for rle_match in rle_matched_files:
    print("{rle_match}".format(
      rle_match = rle_match,
    ))

  # optionally, let's save the file
  if output_file:
    logging.debug("Writing to file '{output_file}'".format(
      output_file = output_file,
    ))
    with open(output_file, 'w') as f:
      for rle_match in rle_matched_files:
        f.write("%s\n" % rle_match)

  logging.debug("Done!")
