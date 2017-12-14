#!/usr/bin/env python

import logging, argparse, os, sys, getpass, jinja2, subprocess, stat, re, io, ROOT
from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples

dumPy = """#!/usr/bin/env python

import ROOT, logging, sys, shutil, os, array

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

def get_rle(input_rootfile, output_textfile_remote, output_textfile_local):
  if not os.path.isdir(os.path.dirname(output_textfile_remote)):
    os.makedirs(os.path.dirname(output_textfile_remote))
  with open(output_textfile_remote, 'w') as f:
    ch_root = ROOT.TChain("{{ tree }}")
    ch_root.AddFile(input_rootfile)

    run_a  = array.array('I', [0])
    lumi_a = array.array('I', [0])
    evt_a  = array.array('L', [0])

    ch_root.SetBranchAddress("{{ run }}",  run_a)
    ch_root.SetBranchAddress("{{ lumi }}", lumi_a)
    ch_root.SetBranchAddress("{{ event }}",  evt_a)

    nof_entries = ch_root.GetEntries()
    rle_i_arr = []
    for i in range(nof_entries):
      ch_root.GetEntry(i)
      rle_i_arr.append(':'.join(map(str, [run_a[0], lumi_a[0], evt_a[0]])))

    f.write("{rle_lines}\\n".format(rle_lines = '\\n'.join(rle_i_arr)))

  logging.debug("Wrote {nof_bytes} kB to {filename}".format(
    nof_bytes = os.path.getsize(output_textfile_remote) / 1000,
    filename = output_textfile_remote,
  ))
  if not os.path.isdir(os.path.dirname(output_textfile_local)):
    os.makedirs(os.path.dirname(output_textfile_local))
  shutil.copy2(output_textfile_remote, output_textfile_local)

{% for input_rootfile, output_textfile_remote, output_textfile_local in input_list %}
get_rle('{{ input_rootfile }}', '{{ output_textfile_remote }}', '{{ output_textfile_local }}'){% endfor %}
logging.debug("Done!")

"""

dumpSh = """#!/bin/bash

mkdir -p {{ scratch_dir }}
python {{ py_script }}
rm -rf {{ scratch_dir }}

"""

def create_dir_if_not_exist(d):
  '''Creates the directory if it doesn't exist
  Args:
    d: string, the diretory to be created

  Returns:
    True, if the directory was created
    False, otherwise
  '''
  if not os.path.isdir(d):
    logging.debug("Directory '{dir_name}' doesn't exist, attempting to create it".format(
      dir_name = d,
    ))
    try:
      os.makedirs(d)
    except IOError:
      logging.error("Could not create the directory")
      return False
  return True

def raw_linecount(filename, buf_sz = 2**20):
  '''Counts the number of lines in a file
  Args:
    filename: string, path to the file the number of newlines of which shall be counted
    buf_sz:   int, the buffer size in bytes (i.e. how much data is processed at once);
                   defaults to 1 MiB

  Returns:
    int, number of newline characters in the file

  Credit to the author of this post: http://stackoverflow.com/a/27518377
  '''
  f = io.open(filename, 'rb')
  lines = 0
  read_f = f.raw.read
  buf = read_f(buf_sz)
  while buf:
      lines += buf.count(b'\n')
      buf    = read_f(buf_sz)
  return lines

def bake_job(sh_script_path, rle_branchNames, treeName, py_script_path, sh_args, py_args, logfile,
             submit_job = True):
  '''Bakes a sbatch job for us
  Args:
    sh_script_path:  string,                   Path to the bash script
    rle_branchNames: dict { string : string }, Branch names of run, lumi and event
    treeName:        string,                   Name of the TTree
    py_script_path:  string,                   Path to the python script
    sh_args:         string,                   Path to the scratch directory
    py_args:         zip,                      Arguments to python script
    logfile,         string,                   Path to sbatch log file
    submit_job:      bool,                     If True, submit the jobs (default);
                                               if False, create the scripts only

  Returns:
    None
  '''

  def chmod_x(f):
    st = os.stat(f)
    os.chmod(f, st.st_mode | stat.S_IEXEC)

  with open(sh_script_path, 'w') as sh_script:
    sh_script.write(jinja2.Template(dumpSh).render(
      py_script = py_script_path,
      scratch_dir = sh_args,
    ))
  chmod_x(sh_script_path)
  with open(py_script_path, 'w') as py_script:
    py_script.write(jinja2.Template(dumPy).render(
      input_list = py_args,
      run        = rle_branchNames['run'],
      lumi       = rle_branchNames['lumi'],
      event      = rle_branchNames['event'],
      tree       = treeName,
    ))
  chmod_x(py_script_path)

  if submit_job:
    submit_cmd = "sbatch --partition=short --output={logfile} {bash_script}".format(
      logfile = logfile,
      bash_script = sh_script_path,
    )
    submit = subprocess.Popen(
      submit_cmd,
      stdout = subprocess.PIPE,
      stderr = subprocess.PIPE,
      shell  = True,
    )
    submit_out, submit_err = submit.communicate()
    logging.debug("\n%s\n%s" % (submit_out, submit_err))
    logging.debug("Submitted the job")
    return int(submit_out.split()[-1])

def dump_rle_parallel(output_dir, rle_branchNames, treeName, nof_files = 100, force = False,
                      test = False, verbose = False, sample = '', tmp_dir = ''):
  '''Dumps RLE numbers ,,in parallel''
  Args:
    output_dir:      string, Path to the directory where the RLE files will be stored
    rle_branchNames: dict { string : string }, Specifies the run, lumi and event branch names
    treeName:        string,                   Name of the TTree
    nof_files:       int,                      Number of files to be processed by one sbatch jobs
    force:           bool,                     If True, creates `output_dir` if it's not there
    test:            bool,                     If True, create jobs scripts but do not submit them to SLURM
    verbose:         bool,                     If True, prints lots of information to standard output
    sample:          string,                   (optional) sample name; if the sample name is not specified,
                                               all samples will be processed

  Returns:
    int array, List of sbatch job IDs that were submitted to SLURM
               This list can be used in checking if the jobs that were submitted in this routine are finished or not

  The method does the following things:
    1) loops over sample entries in 2016 dictionary (default) or selects only one sample (specified by `sample`)
    2) loops over all root files under sample directory and arranges them into chunks specified by `nof_files`
    3) creates a Python script and a Bash script which loops over the entries in the file
    4) submits each job to SLURM, unless `test` is True
    5) returns a list of sbatch job IDs that were assigned to each job
  '''
  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  if not os.path.isdir(output_dir):
    if not force:
      logging.error("Directory '{output_dir}' does not exist".format(
        output_dir = output_dir,
      ))
      sys.exit(1)
    else:
      logging.debug("Creating directory '{output_dir}' since it's missing".format(
        output_dir = output_dir,
      ))

  # let's make a temporary directories
  output_dir_tmp = os.path.join(output_dir, "tmp") if not tmp_dir else tmp_dir
  if not create_dir_if_not_exist(output_dir_tmp): sys.exit(1)
  output_dir_tmp_sh = os.path.join(output_dir_tmp, "sh")
  output_dir_tmp_py = os.path.join(output_dir_tmp, "py")
  output_dir_tmp_log = os.path.join(output_dir_tmp, "log")
  if not create_dir_if_not_exist(output_dir_tmp_sh):  sys.exit(1)
  if not create_dir_if_not_exist(output_dir_tmp_py):  sys.exit(1)
  if not create_dir_if_not_exist(output_dir_tmp_log): sys.exit(1)
  scratch_dir = "/scratch/{user_name}/dump_rle".format(user_name = getpass.getuser())

  idx = lambda x: int(x[x.rfind('_') + 1: x.rfind('.')])
  tree_pattern = re.compile("tree_\d+.root")

  jobId = 0
  root_files, remote_output, local_output = [], [], []

  found_sample_name = False
  sbatch_job_ids = []
  for s_key, s_value in samples.iteritems():
    sample_name = s_value['process_name_specific']
    if sample and sample_name != sample:
      continue
    found_sample_name = True

    sample_path = s_value['local_paths'][0]['path']
    logging.debug("Processing sample '{sample_name}'".format(
      sample_name = sample_name,
    ))

    output_dir_parent = os.path.join(output_dir, sample_name)
    if not os.path.isdir(output_dir_parent):
      os.makedirs(output_dir_parent)

    for sample_subdir_basename in os.listdir(sample_path):
      sample_subdir = os.path.join(sample_path, sample_subdir_basename)

      for rootfile_basename in os.listdir(sample_subdir):
        tree_match = tree_pattern.match(rootfile_basename)
        if not tree_match:
          continue

        rootfile_idx = idx(rootfile_basename)
        root_files.append(os.path.join(sample_subdir, rootfile_basename))
        local_output.append(os.path.join(output_dir_parent, "{i}.txt".format(i = rootfile_idx)))
        remote_output.append(os.path.join(scratch_dir, str(jobId), sample_name, os.path.basename(local_output[-1])))

        if len(root_files) == nof_files:
          sh_path = os.path.join(output_dir_tmp_sh, "{i}.sh".format(i = jobId))
          py_path = os.path.join(output_dir_tmp_py, "{i}.py".format(i = jobId))
          log_path = os.path.join(output_dir_tmp_log, "{i}.log".format(i = jobId))
          scratch_job_dir = os.path.join(os.path.join(scratch_dir, str(jobId)))
          sbatch_job_id = bake_job(
            sh_path, rle_branchNames, treeName, py_path, scratch_job_dir,
            zip(root_files, remote_output, local_output), log_path, not test,
          )
          if sbatch_job_id:
            sbatch_job_ids.append(sbatch_job_id)
          logging.debug("Creating job {jobId}".format(jobId = jobId))
          root_files, remote_output, local_output = [], [], []
          jobId += 1

  if sample and not found_sample_name:
    logging.error("Sample name '{sample_name}' does not exist in the sample dictionary".format(sample_name = sample))
    sys.exit(1)

  if root_files:
    sh_path = os.path.join(output_dir_tmp_sh, "{i}.sh".format(i = jobId))
    py_path = os.path.join(output_dir_tmp_py, "{i}.py".format(i = jobId))
    log_path = os.path.join(output_dir_tmp_log, "{i}.log".format(i = jobId))
    scratch_job_dir = os.path.join(os.path.join(scratch_dir, str(jobId)))
    sbatch_job_id = bake_job(
      sh_path, rle_branchNames, treeName, py_path, scratch_job_dir,
      zip(root_files, remote_output, local_output), log_path, not test,
    )
    if sbatch_job_id:
      sbatch_job_ids.append(sbatch_job_id)
    logging.debug("Creating job {jobId}".format(jobId = jobId))

  logging.debug("Done!")
  return map(int, sbatch_job_ids)

def validate(output_dir, verbose = False):
  '''Validates the job execution carried out by dump_rle_parallel()
  Args:
    output_dir: string, The directory where all RLE files are stored
    verbose:    bool,   Enable verbose output

  Returns:
    None

  The validation is quite basic: the program will loop over the subdirectories of output_dir,
  matches them against the dictionary entries specified by sample variable and counts the number
  of lines in each RLE file. If the number of files doesn't match to the number of entries in
  the corresponding ROOT file, the user will be notified about such discrepancies.

  In principle, the script could also print relevant commands to fix the issues (and dump them
  to an easily executable file) but let's leave it for another time.
  '''

  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  root_file_regex = re.compile('^tree_(\d+).root$')
  file_dict = { k : [] for k in ['excess', 'missing', 'corrupted'] }

  try:

    for s_key, s_value in samples.iteritems():
      sample_name = s_value['process_name_specific']
      sample_dir = os.path.join(output_dir, sample_name)
      if os.path.isdir(sample_dir):
        logging.debug("Found sample directory {sample_dir}".format(sample_dir = sample_dir))

        #NB! assume that there are no secondary paths in the dictionary (hence index 0!)
        sample_path_dict = s_value['local_paths'][0]
        sample_path      = sample_path_dict['path']
        blacklist        = sample_path_dict['blacklist']
        for sample_subdir in os.listdir(sample_path):
          sample_subpath_idx = -1
          try:
            sample_subpath_idx = int(sample_subdir)
          except ValueError:
            continue
          if sample_subpath_idx < 0:
            raise ValueError("Internal error")
          sample_subpath = os.path.join(sample_path, sample_subdir)
          logging.debug("Processing sample subdirectory {sample_subpath}".format(sample_subpath = sample_subpath))

          for sample_file in os.listdir(sample_subpath):
            sample_file_fullpath = os.path.join(sample_subpath, sample_file)
            if not sample_file.endswith('.root') or not os.path.isfile(sample_file_fullpath):
              continue

            root_file_regex_match = root_file_regex.search(sample_file)
            if not root_file_regex_match:
              continue

            root_file_idx = int(root_file_regex_match.group(1))
            expected_rle_file_basename = '{root_file_idx}.txt'.format(root_file_idx = root_file_idx)
            expected_rle_file          = os.path.join(sample_dir, expected_rle_file_basename)
            file_dict_entry            = (expected_rle_file, sample_file_fullpath)
            if root_file_idx in blacklist:
              if os.path.isfile(expected_rle_file):
                logging.warning('Found RLE file {rle_file} (corresponding to blacklisted {root_file}) '
                                'which you ought to delete'.format(
                  rle_file  = expected_rle_file,
                  root_file = sample_file_fullpath,
                ))
              file_dict['excess'].append(file_dict_entry)
              continue

            if not os.path.isfile(expected_rle_file):
              logging.warning('Missing RLE file {rle_file} (corresponding to {root_file})'.format(
                rle_file  = expected_rle_file,
                root_file = sample_file_fullpath,
              ))
              file_dict['missing'].append(file_dict_entry)
              continue
            nof_rle_events = raw_linecount(expected_rle_file)
            if nof_rle_events == 1 and os.path.getsize(expected_rle_file) == 1:
              # the RLE file contains only a newline, hence no events
              nof_rle_events = 0

            root_file = ROOT.TFile(sample_file_fullpath, 'read')
            root_tree = root_file.Get('tree')
            nof_entries = root_tree.GetEntries()

            nof_events_diff = nof_rle_events - nof_entries
            if nof_events_diff < 0:
              logging.error('Missing {nof_events} events in {rle_filename} (corresponding to {sample_file}): '
                            'expected {expected}, got {actual}'.format(
                nof_events   = abs(nof_events_diff),
                rle_filename = expected_rle_file,
                sample_file  = sample_file_fullpath,
                expected     = nof_entries,
                actual       = nof_rle_events,
              ))
              file_dict['corrupted'].append(file_dict_entry)
            elif nof_events_diff > 0:
              logging.error('Got {nof_events} more event than expected in {rle_filename} (corresponding '
                            'to {sample_file}): expected {expected}, got {actual}'.format(
                nof_events   = nof_events_diff,
                rle_filename = expected_rle_file,
                sample_file  = sample_file_fullpath,
                expected     = nof_entries,
                actual       = nof_rle_events,
              ))
              file_dict['corrupted'].append(file_dict_entry)
            else:
              logging.debug('File {rle_filename} (corresponding to {sample_file}) looks OK'.format(
                rle_filename = expected_rle_file,
                sample_file  = sample_file_fullpath,
              ))

  except KeyboardInterrupt:
    pass

  if any(map(bool, file_dict.values())):
    logging.info('Validation finished with errors')
    for key in file_dict.keys():
      if file_dict[key]:
        logging.info('Number of {key} RLE files: {nof_key}'.format(key = key, nof_key = len(file_dict[key])))
        for entry in file_dict[key]:
          logging.info('{rle_file} <=> {sample_file}'.format(rle_file = entry[0], sample_file = entry[1]))
  else:
    logging.info('Validation finished successfully')
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

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 40))
  parser.add_argument('-o', '--output-dir', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Directory where the list of RLE numbers will be saved')
  parser.add_argument('-n', '--nof-files', metavar = 'number', required = False, type = int, default = 100,
                      help = 'R|Number of root files to be processed')
  parser.add_argument('-s', '--sample-name', metavar = 'name', required = False, type = str, default = '',
                      help = 'R|Specific sample name (default: all samples)')
  parser.add_argument('-T', '--tmp-dir', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Temporary directory where py and sh cfgs, and logs will be stored')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Force the creation of output directory if missing')
  parser.add_argument('-t', '--test', dest = 'test', action = 'store_true', default = False,
                      help = 'R|Do not submit the jobs')
  parser.add_argument('-r', '--run', metavar = 'name', required = False, type = str, default = 'run',
                      help = 'R|Name of the run branch')
  parser.add_argument('-l', '--lumi', metavar = 'name', required = False, type = str, default = 'luminosityBlock',
                      help = 'R|Name of the lumi branch')
  parser.add_argument('-e', '--event', metavar = 'name', required = False, type = str, default = 'event',
                      help = 'R|Name of the event branch')
  parser.add_argument('-y', '--tree', metavar = 'name', required = False, type = str, default = 'Events',
                      help = 'R|Name of the TTree')
  parser.add_argument('-V', '--validate', dest = 'validate', action = 'store_true', default = False,
                      help = 'R|Check if all the RLE numbers have been fetched')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  rle_branchNames = {
    'run'   : args.run,
    'lumi'  : args.lumi,
    'event' : args.event,
  }

  if args.validate:
    validate(args.output_dir, args.verbose)
  else:
    dump_rle_parallel(
      args.output_dir, rle_branchNames, args.tree, args.nof_files, args.force, args.test,
      args.verbose, args.sample_name, args.tmp_dir,
    )
