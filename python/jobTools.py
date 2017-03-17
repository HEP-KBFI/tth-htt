import getpass, logging, os, subprocess, sys, time, stat, errno

def query_yes_no(question, default = "yes"):
  """Prompts user yes/no

  Args:
    question: question to ask from the user
    default: default option to use; acceptable values: "yes", "no" or None
  """
  default = default.lower()
  valid = { "yes": True, "y": True, "ye": True, "no": False, "n": False }
  if default is None:    prompt = " [y/n] "
  elif default == "yes": prompt = " [Y/n] "
  elif default == "no":  prompt = " [y/N] "
  else:
    raise ValueError("Invalid default answer: '%s'" % default)

  while True:
    sys.stdout.write(question + prompt)
    choice = raw_input().lower()
    if default is not None and choice == "": return valid[default]
    elif choice in valid:                    return valid[choice]
    else:
      sys.stdout.write("Please respond with 'yes' or 'no' (or 'y' or 'n').\n")

def add_chmodX(fullpath):
  """Adds execution rights to a given file.

  Args:
    fullpath: full path of the file to give execution rights (effectively chmod +x'es the thing)
  """
  st = os.stat(fullpath)
  os.chmod(fullpath, st.st_mode | stat.S_IEXEC)

def create_if_not_exists(dir_fullpath):
  """Creates a given directory if it doesn't exist yet

  Args:
    dir_fullpath: full path to the directory
  
  Inspired by: http://stackoverflow.com/a/600612
  """
  try:
    os.makedirs(dir_fullpath)
  except OSError as exc:
    if exc.errno == errno.EEXIST and os.path.isdir(dir_fullpath):
      pass
    else:
      raise

def generate_file_ids(nof_files, max_files_per_job, blacklist = []):
  """Subsets file ids

    Given N total number of input files, the function splits them into sublists, each
    containing up to M files (maximum number of input files). The function only works with
    indexes, not full paths, though.

  Args:
    nof_files: Total number of input files
    max_files_per_job: Maximum number of input files a job can take

  Returns:
    File ids split into sublists of length `max_files_per_job`
  """
  #print "<generate_file_ids>:"
  file_limits = range(1, nof_files + 1, 1)
  file_limits = list(sorted(list(set(file_limits) - set(blacklist))))
  if max_files_per_job > 1:
    job_ids = [file_limits[i: i + max_files_per_job] for i in range(0, len(file_limits), max_files_per_job)]
  elif max_files_per_job == 1:
    job_ids = [[x] for x in file_limits]
  else:
    print("Invalid max_files_per_job=%d; must be a positive number" % max_files_per_job)
    assert(0)
  return job_ids

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store, debug = False):
  """Generates input file list for each job

    Since CRAB was unable to resubmit failed jobs, we had to run the jobs 2nd time. Thus, the full sample
    is complete if we include both storage directories.
    The primary directory contains most of the input files, and the secondary the missing ones.

  Args:
    job_ids: list of file ids (one of the sublists generated in `generate_file_ids`)
    secondary_files: list of input file id's missing in the primary storage
    primary_store: full path to the primary subdirectory containing most of the sample
    secondary_store: full path to the second subdirectory
    debug: if True, checks whether each file is present in the file system
  """
  #print "<generate_input_list>:"
  input_list = []
  for job in job_ids:
    actual_storedir = secondary_store if job in secondary_files else primary_store
    input_file = os.path.join(actual_storedir, "000" + str(job / 1000), "tree_" + str(job) + ".root")
    #print "checking existence of input_file = '%s'" % input_file
    if not os.path.exists(input_file):
      input_file = os.path.join(actual_storedir, "tree_" + str(job) + ".root")
    #print "checking existence of input_file = '%s'" % input_file
    if not os.path.exists(input_file):
      if debug:
        logging.error("File %s doesn't exists!" % input_file)
        sys.exit(2)
      continue
    input_list.append(input_file)
  return input_list

def run_cmd(command, do_not_log = False, stdout_file = None, stderr_file = None, return_stderr = False):
  """Runs given commands and logs stdout and stderr to files
  """
  if not do_not_log: logging.info(command)
  p = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
  stdout, stderr = p.communicate()
  # Remove trailing newline
  stdout = stdout.rstrip('\n')
  stderr = stderr.rstrip('\n')

  if stdout_file:
    stdout_file.write(command + "\n")
    stdout_file.write(stdout)
  if stderr_file:
    stderr_file.write(stderr)

  print("jobTools#run_cmd('%s') stdout: '%s'" % (command, stdout))
  print("jobTools#run_cmd('%s') stderr: '%s'" % (command, stderr))

  if return_stderr:
    return stdout, stderr
  return stdout
