#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.hdfs import hdfs
from tthAnalysis.HiggsToTauTau.common import load_samples

from dump_rle_parallel import dump_rle_parallel

import argparse
import sys
import os
import subprocess
import re
import shutil
import array
import time
import getpass

'''The script copies a subset of an Ntuple, given RLE numbers, sample name and output file name

NOTE: If the user has RLE numbers of all Ntuples already stored somewhere (likely created w/ dump_rle_parallel.py),
      then the script will be at least two order of magnitudes faster.

EXAMPLE:
      ./skim_root.py -i ~/RLE_list.txt -o ~/selected.root -s ttHToNonbb_M125 -D -v -f -c -d ~/RLE_directory
  or
      ./skim_root.py -i ~/RLE_list.txt -o ~/selected.root -s ttHToNonbb_M125 -D -v -f -c -n 10

  In the former the RLE files are under ~/RLE_directory and the input RLE numbers ~/RLE_list.txt are immediately grepped
  from the files under this directory; in the latter the RLE files are missing and they have to be created for this
  particular sample (ttHToNonbb_M125). Once the `n` jobs are finished the script proceeds as in the first example.
  If the RLE files are created on the fly, then the resulting files will be under $(dirname ~/RLE_list.txt)/RLE
'''

def join_rle(run, lumi, evt):
  '''Joins array objects run, lumi and event to string w/ delimiter ':'
  Args:
    run:  single-element array object, Run number
    lumi: single-element array object, Lumi number
    evt:  single-element array object, Event number

  Returns:
    string, of the form run:lumi:evt
  '''
  return ':'.join(map(lambda x: str(x[0]), [run, lumi, evt]))

def cleanup(dir_name, exit = False):
  '''Removes a directory and might exit hard from the script
  Args:
    dir_name: string, Path to directory which is to be removed
    exit:     bool,   If True, exits the script via sys.exit() (default: False)

  Returns:
    None
  '''
  logging.debug("Removing directory {dir_name}".format(dir_name = dir_name))
  try:
    shutil.rmtree(dir_name)
  except IOError:
    logging.error("Managed to get an error while removing directory {dir_name}".format(dir_name = dir_name))
  if exit:
    sys.exit(1)

def skim(in_filename, out_filename, entry_list, tree_name = "Events"):
  '''
  Args:
    in_filename:  string,    Path to the input ROOT file
    out_filename: string,    Path to the output ROOT file
    entry_list:   int array, List of entries (not RLE numbers!) which are used to select the event
    tree_name:    string,    TTree name (default: tree)

  Returns:
    True,  if none of the entry numbers didn't exceed the actual number of entries in the ROOT file
    False, otherwise
  '''
  logging.debug("Processing file {in_filename}".format(in_filename = in_filename))
  f_in = ROOT.TFile(in_filename, "read")
  t_in = f_in.Get(tree_name)

  nof_entries = t_in.GetEntries()
  if max(entry_list) > nof_entries:
    logging.error("Max entry ID exceeds the number of entries in {root_filename}: {max_entry} > {nof_entries}".format(
      root_filename = in_filename,
      max_entry     = max(entry_list),
      nof_entries   = nof_entries,
    ))
    return False

  f_out = ROOT.TFile(out_filename, "recreate")
  t_out = t_in.CloneTree(0)

  for i in entry_list:
    t_in.GetEntry(i)
    t_out.Fill()

  t_out.AutoSave()
  logging.debug("Saved events to {out_filename}".format(out_filename = out_filename))
  return True

def get_rle(in_filename, tree_name = "tree"):
  '''Fetches all RLE numbers in a given file
  Args:
    in_filename: string, Path to the ROOT file from which the RLE numbers are fetched
    tree_name:   string, TTree name (default: tree)

  Returns:
    string array, List of RLE numbers (in the format returned by join_rle())

  The function expects the input file to exist in the file system.
  '''
  rle_list = []
  f_in = ROOT.TFile(in_filename, "read")
  t_in = f_in.Get(tree_name)

  run  = array.array('I', [0])
  lumi = array.array('I', [0])
  evt  = array.array('L', [0])

  t_in.SetBranchAddress("run", run)
  t_in.SetBranchAddress("luminosityBlock", lumi)
  t_in.SetBranchAddress("event", evt)

  nof_entries = t_in.GetEntries()
  for i in range(nof_entries):
    t_in.GetEntry(i)
    rle_list.append(join_rle(run, lumi, evt))

  return rle_list

def skim_debug(out_filename, rle_list, tree_name = "tree"):
  '''Checks if skimming was successful by comparing RLE number in the output file to the given list of RLE numbers
  Args:
    out_filename: string,       Path to the file the RLE numbers of which is compared against the RLE array
    rle_list:     string array, List of RLE numbers as strings
    tree_name:    string,       TTree name (default: tree)

  Returns:
    True,  if the RLE numbers in the file match exactly to the given input list of RLE numbers
    False, otherwise
  '''
  logging.debug("Checking if {out_filename} contains exactly the same events as provided by the RLE file".format(
    out_filename = out_filename,
  ))
  if not hdfs.isfile(out_filename):
    return False

  out_rle_list = get_rle(out_filename, tree_name)

  missing_from_file = list(set(rle_list) - set(out_rle_list))
  excess_in_file    = list(set(out_rle_list) - set(rle_list))

  ret_val = True
  if missing_from_file:
    logging.error("There are {nof_missing} events missing from {out_filename}: {list_of_missing_events}".format(
      nof_missing            = len(missing_from_file),
      out_filename           = out_filename,
      list_of_missing_events = ', '.join(missing_from_file),
    ))
    ret_val = False
  if excess_in_file:
    logging.error("There are {nof_excess} event in excess in the file {out_filename}: {list_of_excess_events}".format(
      nof_excess            = len(excess_in_file),
      out_filename          = out_filename,
      list_of_excess_events = ', '.join(excess_in_file),
    ))
    ret_val = False

  return ret_val

def positive_int(i):
  '''argparse type
  Args:
    i: string, Argument to be checked against positive integer-ness

  Returns:
    int, If the argument is truly a positive integer

  Otherwise the method raises argparse.ArgumentTypeError
  '''
  try:
    i_int = int(i)
  except ValueError:
    raise argparse.ArgumentTypeError("Not an integer: {0}".format(i))
  if i_int <= 0:
    raise argparse.ArgumentTypeError("Not a positive integer: {0}".format(i_int))
  return i_int

if __name__ == '__main__':
  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45))
  group = parser.add_mutually_exclusive_group()
  parser.add_argument('-i', '--input', metavar = 'file', required = True, type = str, default = '',
                      help = 'R|Path to RLE numbers')
  parser.add_argument('-e', '--era', metavar = 'era', required = True, type = str, choices = [ '2016', '2017', '2018' ],
                      help = 'R|Era')
  parser.add_argument('-s', '--sample-name', metavar = 'name', required = True, type = str, default = '',
                      help = 'R|Sample name')
  parser.add_argument('-o', '--output', metavar = 'file', required = True, type = str, default = '',
                      help = 'R|Path to output ROOT file')
  group.add_argument ('-d', '--directory', metavar = 'directory', type = str, default = '',
                      help = 'R|Directory containing all RLE numbers (dump_rle_parallel.py output)')
  group.add_argument ('-n', '--nof-files', metavar = 'number', type = positive_int, default = 10,
                      help = 'R|Number of files per job (relevant only if -d option is not used)')
  parser.add_argument('-D', '--debug', dest = 'debug', action = 'store_true', default = False,
                      help = 'R|Perform a RLE-based test to see if all events are correctly selected')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Overwrite output file if it already exists')
  parser.add_argument('-c', '--clean', dest = 'clean', action = 'store_true', default = False,
                      help = 'R|Clean up RLE/tmp directory if it was created')
  parser.add_argument('-p', '--post-processed', dest = 'post_processed', action = 'store_true', default = False,
                      help = 'R|Skim post-processed samples')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  rle_filename = args.input
  out_filename = os.path.abspath(args.output)
  grep_dir     = args.directory
  sample_name  = args.sample_name
  force        = args.force
  debug_output = args.debug
  nof_files    = args.nof_files

  # check if input RLE file exists
  if not hdfs.isfile(rle_filename):
    logging.error("File {rle_filename} does not exist or is not a file!".format(rle_filename = rle_filename))
    sys.exit(1)

  # check if the directory into which we have to write the output ROOT file already exists
  out_parent_dir = os.path.dirname(out_filename)
  if not hdfs.isdir(out_parent_dir):
    if not force:
      logging.error("Parent directory of the output file {out_filename} does not exist".format(
        out_filename = out_filename),
      )
      sys.exit(1)
    else:
      logging.debug("Output directory {out_parent_dir} does not exist, attempting to create one".format(
        out_parent_dir = out_parent_dir,
      ))
      try:
        hdfs.mkdirs(out_parent_dir)
      except IOError as err:
        logging.error("Could not create directory {out_parent_dir}".format(out_parent_dir = out_parent_dir))
        sys.exit(1)

  # check if output ROOT file exists (if it does then the user is obliged to use '-f' flag!)
  if hdfs.exists(out_filename) and not force:
    logging.error("File {out_filename} already exists!".format(out_filename = out_filename))
    sys.exit(1)

  if grep_dir and not hdfs.isdir(grep_dir):
    logging.error("Directory {grep_dir} does not exist!".format(grep_dir = grep_dir))
    sys.exit(1)

  # check if the provided sample name is in our 2016 py dictionary
  samples = load_samples(args.era, is_postproc = args.post_processed)
  sample_key = ''
  for s_key, s_value in samples.iteritems():
    if s_key == 'sum_events':
      continue
    if s_value['process_name_specific'] == sample_name:
      sample_key = s_key
      break

  if not sample_key:
    logging.error("Invalid sample name: '{sample_name}'".format(sample_name = sample_name))
    sys.exit(1)

  # obtain the root path that corresponds to the sample
  sample_path = samples[sample_key]['local_paths'][0]['path']

  # read the list of RLE numbers that are used to filter the events from the ROOT files and check its validity
  rle_list = map(lambda x: x.rstrip('\n'), open(rle_filename, 'r').readlines())
  rle_pattern = re.compile('\d+:\d+:\d+')
  if not all(map(lambda x: rle_pattern.match(x), rle_list)):
    logging.error("File {rle_filename} contains invalid RLE number(s)".format(rle_filename = rle_filename))
    sys.exit(1)
  rle_list_len = len(rle_list)

  # if the user didn't specify the RLE directory, i.e. directory which contains all RLE numbers of the sample
  if not grep_dir:
    logging.debug("No grep directory specified => gotta have to create the RLE list")
    grep_dir = os.path.join(out_parent_dir, "RLE")

    # submit the jobs to SLURM
    sbatch_job_ids = set(
      dump_rle_parallel(
        output_dir = grep_dir,
        nof_files  = nof_files,
        force      = True,
        test       = False,
        verbose    = args.verbose,
        sample     = sample_name
      )
    )

    # wait for the jobs to finish
    while True:
      logging.debug("Waiting for jobs to finish ...")
      poll_cmd_str = "squeue -u %s | awk '{print $1}' | tail -n+2" % getpass.getuser()
      poll_cmd = subprocess.Popen(
        poll_cmd_str,
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell  = True,
      )
      poll_stdout, poll_stderr = poll_cmd.communicate()
      sbatch_job_ids_remain = set(map(int, filter(lambda x: x != '', poll_stdout.split('\n'))))
      nof_remaining_jobs = len(sbatch_job_ids & sbatch_job_ids_remain)
      if nof_remaining_jobs > 0:
        logging.debug("{nof_remaining_jobs} unfinished job(s)".format(nof_remaining_jobs = nof_remaining_jobs))
        time.sleep(10)
      else:
        break

    # remove the tmp directory created by dump_rle_parallel()
    grep_tmp_dir = os.path.join(grep_dir, 'tmp')
    if hdfs.isdir(grep_tmp_dir):
      shutil.rmtree(grep_tmp_dir)

  logging.debug("Attempting to grep RLE numbers individually")

  tmp_dir = os.path.join(out_parent_dir, ".tmp_skim")
  if not hdfs.isdir(tmp_dir):
    logging.debug("Creating temporary directory {tmp_dir}".format(tmp_dir = tmp_dir))
    try:
      hdfs.mkdirs(tmp_dir)
    except IOError as err:
      logging.debug("Could not create directory {tmp_dir}: {reason}".format(
        tmp_dir = tmp_dir,
        reason  = err,
      ))
      sys.exit(1)

  grep_sample_dir = os.path.join(grep_dir, sample_name, '*')
  file_idx_pattern = re.compile('\d+')
  file_map = {}
  percent_counter = 1

  # loop over the RLE numbers and grep each such number from the RLE directory
  for i in range(rle_list_len):
    rle_processed = i / float(rle_list_len)
    rle_number = rle_list[i]

    if rle_processed > percent_counter / 10.:
      percent_counter += 1
      logging.debug("Processed %.2f%% of RLE numbers" % (100 * rle_processed))

    # call grep via OS
    grep_cmd_str = "grep -nr '{rle_number}' {grep_sample_dir}".format(
      rle_number      = rle_number,
      grep_sample_dir = grep_sample_dir,
    )
    grep_process = subprocess.Popen(
      grep_cmd_str,
      stdout = subprocess.PIPE,
      stderr = subprocess.PIPE,
      shell  = True,
    )
    grep_stdout, grep_stderr = grep_process.communicate()

    if grep_stderr:
      logging.error(grep_stderr)
      sys.exit(1)

    # grep should return only one line in the following format:
    # path/to/the/file/<number>.txt:<line-nr>:<line-itself>
    grep_stdout_stripped = grep_stdout.rstrip('\n')
    if len(grep_stdout_stripped.split('\n')) != 1:
      logging.error("grep return unexpected output: {grep_stdout}".format(grep_stdout = grep_stdout))
      cleanup(tmp_dir, True)

    split = grep_stdout_stripped.split(':')
    file_idx_match = file_idx_pattern.match(os.path.basename(split[0]))
    if not file_idx_match:
      logging.error("Unexpected file name encountered in directory {grep_sample_dir}: {unexpected_file}".format(
        grep_sample_dir = grep_sample_dir,
        unexpected_file = split[0],
      ))
      logging.error("The following command failed: {failed_command}".format(failed_command = grep_cmd_str))
      sys.exit(1)

    # there can be more than one entry number for each sample ROOT file; and a bunch of ROOT files per sample
    file_idx = int(file_idx_match.group())
    entry_nr = int(split[1]) - 1
    if file_idx not in file_map:
      file_map[file_idx] = {
        'entry_list' : [],
        'out_filename' : os.path.join(
          tmp_dir, "{out_filename}.{idx}".format(out_filename = os.path.basename(out_filename), idx = str(file_idx))
        ),
        'in_filename' : os.path.join(
          sample_path, str(file_idx / 1000).zfill(4), "tree_{idx}.root".format(idx = file_idx)
        ),
      }
    file_map[file_idx]['entry_list'].append(entry_nr)

  # now that we have the entry numbers for all sample ROOT files, we can just copy the over to a different file
  logging.debug("Collected {nof_files} that contain the RLE numbers".format(nof_files = len(file_map)))
  for k in list(sorted(file_map.keys())):
    file_meta = file_map[k]
    if not skim(file_meta['in_filename'], file_meta['out_filename'], file_meta['entry_list']):
      cleanup(tmp_dir, True)
    if not hdfs.isfile(file_meta['out_filename']):
      logging.error("For some reason file {out_filename} does not exist!".format(
        out_filename = file_meta['out_filename']),
      )
      cleanup(tmp_dir, True)

  # concatenate all temporary root files and then remove them
  logging.debug("Performing hadd on temporary output files")
  hadd_cmd_str = "hadd -f {out_filename} {input_filename_list}".format(
    out_filename         = out_filename,
    input_filename_list  = ' '.join(map(lambda x: file_map[x]['out_filename'], file_map)),
  )
  hadd_cmd = subprocess.Popen(
    hadd_cmd_str,
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE,
    shell  = True,
  )
  hadd_stdout, hadd_stderr = hadd_cmd.communicate()
  if hadd_stderr:
    logging.error("Encountered an error while performing hadd: {reason}".format(reason = hadd_stderr))
    if hdfs.isfile(out_filename):
      hdfs.remove(out_filename)
  cleanup(tmp_dir)

  # check if we didn't miss any RLE numbers in the new, skimmed ROOT file
  if debug_output:
    if skim_debug(out_filename, rle_list):
      logging.debug("Success!")
    else:
      logging.error("The script did not finish correctly")

  logging.debug("Done!")
