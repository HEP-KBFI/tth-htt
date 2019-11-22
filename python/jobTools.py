from tthAnalysis.HiggsToTauTau.common import logging

import os
import subprocess
import sys
import math
import stat

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
  """
  from tthAnalysis.HiggsToTauTau.hdfs import hdfs

  if hdfs.mkdirs(dir_fullpath) != 0:
    raise RuntimeError("Unable to create directory %s" % dir_fullpath)

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

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store):
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
  from tthAnalysis.HiggsToTauTau.hdfs import hdfs

  input_list = []
  for job in job_ids:
    actual_storedir = secondary_store if job in secondary_files else primary_store
    input_file = os.path.join(actual_storedir, "000" + str(job / 1000), "tree_" + str(job) + ".root")
    if not hdfs.exists(input_file):
      raise RuntimeError("File %s doesn't exists!" % input_file)
    input_list.append(input_file)
  return input_list

def run_cmd(command, do_not_log = False, stdout_file = None, stderr_file = None,
            return_stderr = False):
  """Runs given commands and logs stdout and stderr to files
  """
  p = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
  stdout, stderr = p.communicate()
  # Remove trailing newline
  stdout = stdout.rstrip('\n')
  stderr = stderr.rstrip('\n')

  if stdout_file:
    stdout_file.write(command + "\n")
    stdout_file.write('%s\n' % stdout)
  if stderr_file:
    stderr_file.write('%s\n' % stderr)

  if not do_not_log:
    logging.debug("Executed command: '%s'" % command)
    logging.debug("stdout: '%s'" % stdout)
    logging.debug("stderr: '%s'" % stderr)

  if return_stderr:
    return stdout, stderr
  return stdout

def get_log_version(list_of_log_files):
  """
  :param list_of_log_files: tuple of strings, List of log files that need to have the same version number
  :return: tuple of strings, List of log files with the same version number

  Instead of passing log files one-by-one, the more consistent way of dealing with these things is
  to loop over a set of log files that represents a single joint iteration of the jobs.
  """
  if all(map(lambda path: not os.path.exists(path), list_of_log_files)):
    # if none of the files exist, then retain the path names
    return list_of_log_files
  # loop over version numbers until none of the paths exist
  version_idx = 1
  while True:
    list_of_log_files_versioned = tuple(map(lambda path: "%s.%i" % (path, version_idx), list_of_log_files))
    if all(map(lambda path: not os.path.exists(path), list_of_log_files_versioned)):
      return list_of_log_files_versioned
    else:
      # some log files already exist -> increase the version number
      version_idx += 1

def human_size(fsize, use_si = True, byte_suffix = 'B'):
  if use_si:
    multiplier = 1000.
    units = ['', 'k', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y']
  else:
    multiplier = 1024.
    units = ['', 'Ki', 'Mi', 'Gi', 'Ti', 'Pi', 'Ei', 'Zi', 'Yi']
  units = list(map(lambda unit: '%s%s' % (unit, byte_suffix), units))
  fsize_int = int(fsize)
  unit_idx = min(int(math.log(fsize_int, multiplier)), len(units) - 1) if fsize_int else 0
  if unit_idx > 0:
    return '%.2f%s' % ((fsize_int / multiplier ** unit_idx), units[unit_idx])
  else:
    return '%d%s' % (fsize_int, units[unit_idx])

def record_software_state(txtfile_cfg, txtfile_out, dependencies):
  from tthAnalysis.HiggsToTauTau.hdfs import hdfs

  git_cmds = [
    'log -n1 --format="%D"',
    'log -n3 --format="%H | %cd | %cn | %s"',
    'status --porcelain=v1 --branch',
    'diff HEAD --no-ext-diff --unified=0 --exit-code -a --no-prefix --word-diff=plain --color=never',
  ]
  BOLD_LINE = "=" * 160
  LIGHT_LINE = "." * 160
  results = []
  for dependency in dependencies:
    dependency_fullpath = os.path.join(
      os.environ['CMSSW_BASE'], 'src', dependency
    )
    results.extend([
      BOLD_LINE,
      "Inspecting dependency: %s" % dependency_fullpath
    ])
    for git_cmd in git_cmds:
      git_cmd_full = 'git -C %s %s' % (dependency_fullpath, git_cmd)
      results.extend([
        LIGHT_LINE,
        "Executing: %s" % git_cmd_full,
        run_cmd(
          git_cmd_full, do_not_log = True, stdout_file = None, stderr_file = None,
          return_stderr = False
        ),
      ])
  with open(txtfile_cfg, 'w') as txtfileptr:
    txtfileptr.write('\n'.join(results))
    txtfileptr.write('\n')
  if txtfile_cfg != txtfile_out:
    hdfs.copy(txtfile_cfg, txtfile_out)
