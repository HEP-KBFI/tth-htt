#!/usr/bin/env python
import subprocess, argparse, os, sys, logging, imp, re

'''Copies in-house produced Ntuples to /hdfs in a consistent manner.

Example usage:

./scripts/copy_prod_ntuples.py \
  -p /home/veelken/ttHNtupleProduction/2016/2016Dec13/ntuples/2lss_1tau/ \
  -d /hdfs/local/karl/ttHNtupleProduction/2016/2016Dec13/ntuples/2lss_1tau/ \
  -n samples_2016 \
  -D python/tthAnalyzeSamples_2016.py \
  -v
'''

def copy_from_local(local_file, remote_file, verbose = True):
  '''Copies a file from local file system to remote hadoop file system

  local_file:  string, local file name (full path)
  remote_path: string, target file name (full path)
  verbose:     bool,   prints out the stdout and stderr of the mkdir and cp commands

  return: None

  NB! The target path must be a directory!!
  NB! The script creates the remote path if it doesn't exist.
  '''
  remote_dirname = os.path.dirname(remote_file)
  if not os.path.isdir(remote_dirname):
    mkdir_arr = ['mkdir', '-p', remote_dirname]
    if verbose:
      print ' '.join(mkdir_arr)
    process_mkdir = subprocess.Popen(
      mkdir_arr,
      stdout = subprocess.PIPE,
      stderr = subprocess.PIPE
    )
    out_mkdir, err_mkdir = process_mkdir.communicate()

    if verbose:
      print(out_mkdir)
      print(err_mkdir)

  cp_arr = ['cp', local_file, remote_file]
  if verbose:
    print ' '.join(cp_arr)
  process_cp = subprocess.Popen(
    cp_arr,
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE
  )
  out_cp, err_cp = process_cp.communicate()
  if verbose:
    print(out_cp)
    print(err_cp)

  return

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )
  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-p', '--path', dest = 'path', metavar = 'path', required = True, type = str,
                      help = 'R|Top level path containing Ntuples to be copied from')
  parser.add_argument('-d', '--destination', dest = 'destination', metavar = 'path', required = True, type = str,
                      help = 'R|Path to which the Ntuples will be copied')
  parser.add_argument('-D', '--dictionary', dest = 'dictionary', metavar = 'file', required = True, type = str,
                      help = 'R|Path to the reference dictionary supporting the source Ntuples')
  parser.add_argument('-n', '--dict_name', dest = 'dict_name', metavar = 'NAME', required = True, type = str,
                      help = 'R|Name of the dictionary (specified by -D), e.g. samples_2016')
  parser.add_argument('-t', '--test', dest = 'test', action = 'store_true', default = False,
                      help = 'R|Test copying (doesn\'t actually copy) by printing out cp commands')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Force copying, regardless of missing file errors')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  source_path = args.path
  dest_path   = args.destination
  dict_path   = args.dictionary
  dict_name   = args.dict_name
  test_cp     = args.test
  force       = args.force
  verbose     = args.verbose

  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  # load the dictionary
  if not os.path.isfile(dict_path):
    logging.error("No such dictionary file: {dict_path}".format(dict_path = dict_path))
    sys.exit(1)
  imp_dict = imp.load_source('', dict_path)
  if not hasattr(imp_dict, dict_name):
    logging.error("No such dictionary in the file '{dict_path}': {dict_name}".format(
      dict_path = dict_path, dict_name = dict_name,
    ))
  samples = getattr(imp_dict, dict_name)

  copy_dict = []

  p = re.compile('_(\d+?).root')
  for sample_name, sample_info in samples.iteritems():
    process_name = sample_info['process_name_specific']
    expected_path = os.path.join(source_path, process_name)
    if not os.path.isdir(expected_path):
      logging.warning("Process '{process_name}' has no Ntuples".format(process_name = process_name))
      continue
    logging.debug("Checking the files stored in {process_path}".format(process_path = expected_path))

    file_nrs = []
    file_list = []
    for f in os.listdir(expected_path):
      # we're interested in the last number which corresponds to exactly one VHbb Ntuple
      m = p.search(f)
      if m:
        file_nrs.append(int(m.group(1)))
        file_list.append(f)
    file_nrs_set = set(file_nrs)

    #NB!!! we expect only one local_path entry with selection '*'
    nof_files = sample_info['nof_files']
    expected_files = set(range(1, nof_files + 1)) - set(sample_info['local_paths'][0]['blacklist'])
    missing_files  = list(sorted(list(expected_files - file_nrs_set)))
    excess         = list(sorted(list(file_nrs_set - expected_files)))

    has_errors = False
    if missing_files:
      logging.error("There are {nof_missing} missing files in sample '{sample_name}'".format(
        nof_missing = len(missing_files), sample_name = process_name,
      ))
      has_errors = True
    if excess:
      logging.error("There are {nof_excess} more files than expected in sample '{sample_name}'".format(
        nof_excess = len(excess), sample_name = process_name,
      ))
      has_errors = True
    if has_errors and not (test_cp or force):
      continue

    # we assume that the first part of the sample key is always contained in the original Ntuple base path
    # if this is true, we can split the original base path by the sample key and construct a new path
    # to which the Ntuple will be copied
    sample_key = sample_name.split('/')[1] # (the sample name starts with a '/')
    sample_orig_path = sample_info['local_paths'][0]['path']
    sample_orig_path_split = sample_orig_path.split('/')
    if 'TTW_FastSim' not in sample_orig_path_split:
      assert(sample_key in sample_orig_path_split), "Sample: %s" % sample_orig_path
    else:
      logging.error("You have to copy TTW_FastSim manually!")

    # now we can build a new path from these pieces
    sample_orig_path_split_by_key = sample_orig_path[len(sample_orig_path.split(sample_key)[0]):]
    new_base_path = os.path.join(dest_path, sample_orig_path_split_by_key)
    logging.debug("Created a new base path for sample {sample_name}: {base_path}".format(
      sample_name = process_name, base_path = new_base_path,
    ))

    # let's create the source <-> target arguments needed by copy_from_local
    for i in range(len(file_list)):
      f = file_list[i]
      nr = file_nrs[i]
      immediate_parent = "000" + str(nr / 1000)
      new_filename = "tree_%d.root" % nr
      new_fullpath = os.path.join(new_base_path, immediate_parent, new_filename)
      copy_dict.append({
        'source_path' : os.path.join(expected_path, f),
        'target_path' : new_fullpath,
      })

  for entry in copy_dict:
    if not test_cp:
      copy_from_local(entry['source_path'], entry['target_path'], verbose)
    else:
      print('cp {source_file} {dest_file}'.format(
        source_file = entry['source_path'],
        dest_file   = entry['target_path'],
      ))
