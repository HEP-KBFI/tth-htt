import subprocess, os, codecs, stat

HADOOP_SH       = "hadoop_cmds.sh"
XRDCP_SH        = "xrdcp_cmds_%d.sh"
XRDCP_SUBMIT_SH = "xrdcp_submit.sh"
NOHUP_OUT       = "nohup_%d.out"
MAKEFILE        = "Makefile"
LOGFILE         = "job_%s.log"

'''
Script that generates scripts for copying Ntuples (or any root files) from remote site
using xrootd protocol.

Note that you need to have a valid proxy before you run any of these commands; try:
voms-proxy-init -voms cms -valid <h:m>
'''

def split(l, n):
  '''Splits the list into n equal parts
  @param l: list, To be splitted
  @param n: int, Number of chunks
  @return: A list of n lists

  The all the sublists have the same length except for the last one
  Cheers to: http://stackoverflow.com/a/2135920
  '''
  k, m = len(l) / n, len(l) % n
  return list(l[i * k + min(i, m):(i + 1) * k + min(i + 1, m)] for i in range(n))

def call_xrdfs(domain, loc):
  '''Call `ls -l -u' through xrootd protocol
  @param domain: string, The domain name
  @param loc: string, A given directory (argument to `ls -l -u')
  @return: string, A list of files and folders in the immediate subdirectory of `loc'

  The `ls' arguments have the following meaning:
    -l stat every entry and pring long listing
    -u print paths as URLs
  Source: http://xrootd.org/doc/man/xrdfs.1.html
  Note that the path `loc' must be a directory, not a file.

  A line of the example output:
  xrdfs t3se01.psi.ch ls -l -u /store/user/perrozzi/VHBBHeppyV23
  dr-x 2016-07-17 00:21:28         512 root://192.33.123.24:1094//store/user/perrozzi/VHBBHeppyV23/WWTo4Q_13TeV-powheg
  '''
  process = subprocess.Popen(
    ['xrdfs', domain, 'ls', '-l', '-u', loc],
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE
  )
  out, err = process.communicate()
  if len(err) > 0: print("ERROR?!: %s" % err)
  return out

def get_root_files(domain, loc):
  '''Retrieves all root files under directory `loc' or its subdirectories
  @param domain: string, The domain name
  @param loc: string, A given directory
  @return: string array, All root files under directory `loc' or its subdirectories

  The function recursively (or technically, iteratively) loops over all
  the subdirectories under `loc' until it hits root files (breadth-first search).
  Then a file list is formed which includes all retrieved root files.
  '''
  file_list = []
  dir_list = [loc]

  while len(dir_list) > 0:
    dir_name = dir_list.pop()
    print(">> %s" % dir_name)
    out = call_xrdfs(domain, dir_name)
    
    for entry in out.split('\n'):
      split_entry = entry.split()
      if len(split_entry) == 0: continue # Might be an empty line

      filename = split_entry[-1].rstrip()
      if filename.endswith(".root"):
        # If it's a root file, add to the file list
        file_list.append(filename)
      elif entry.startswith('d'):
        # The first character are in one line of the `ls' output is either:
        #   - 'd' if the file is a directory, or
        #   - '-' if the file is a ... file
        #
        # If it's a directory, loop over it later
        dir_list.append("/" + filename.split("//")[-1])

  return file_list

def get_filelist(source, output_dir):
  '''Retrieves all root files, given domain name, uppermost parent directory
     and a list of subdirectories, the root files under which we want to copy over
  @param source: dict, Holds information about the domain name ["domain"],
                       root directory ["parent"] and its immediate valid subdirectories
                       ["subdirs"]
  @param output_dir: string, Output directory where the file list is dumped

  Note that one list of files is created for each sample (denoted by "subdirs"),
  bearing the same name as one of the  "subdirs" value. For example, if we want root files
  for the sample "SingleMuon", we look into subdirectory "SingleMuon", fetch all the root
  files under this subdirectory by traversing the directory tree recursively, and finally
  dump all the retrieved full paths to text file called "SingleMuon" under directory
  `output_dir'.
  However, this might pose a problem when the user wants to copy the sample (ot at least
  the same subdirectory) from different domains or parent dirs: the file will be written over.
  '''

  # Perform initial scan first: look into immediate subdirectories of "parent"
  subdir_list = call_xrdfs(source["domain"], source["parent"])

  for line in subdir_list.split('\n'):
    split_line = line.split()
    if len(split_line) == 0: continue # Might be an empty line

    full_path = split_line[-1]
    dirname = full_path.split('/')[-1]
    if dirname in source["subdirs"]:
      # If the immediate subdirectory is in our list, look for the root files therein
      print("Processing subdirectory %s" % dirname)
      file_list = get_root_files(source["domain"], "/" + full_path.split("//")[-1])
      print("Retrieved all files")
      if len(file_list) > 0:
        # Dump the file list to a text file (one file per line)
        with codecs.open(os.path.join(output_dir, dirname), 'w', 'utf-8') as f:
          for root_file in file_list:
            f.write("%s\n" % root_file)
  print("Done with the retrieval")

def generate_cmds(source, output_dir, hdfs_path, nof_splits):
  '''Generate `xrdcp' and and `hadoop fs -mkdir` commands
  @param source: dict, Holds information about the domain name ["domain"],
                       root directory ["parent"] and its immediate valid subdirectories
                       ["subdirs"]
  @param output_dir: string, Directory containing full files, which hold full paths to
                             the root files on remote domain
  @param hdfs_path: string, Root of the local path to copy the root files

  All `xrdcp' commands are saved to xrdcp_cmds.sh;
  all `hadoop' commands are copied to hadoop_cmds under the directory `output_dir'.
  We need the latter because `xrdcp' doesn't copy the files if the destination directory
  doesn't exist. Therefore we need to create the directories beforehand. AFAIK, there's
  no recursive option for `hadoop fs -mkdir', thus we have to mimic the recursive creation
  ourselves.
  '''
  cmds = []
  hadoop_paths = [hdfs_path]
  print("Generate copy and hadoop commands")

  for subdir in source["subdirs"]:
    txtfile = os.path.join(output_dir, subdir)
    if os.path.exists(txtfile):
      with codecs.open(txtfile, 'r', 'utf-8') as f:
        for line in f:
          line = line.rstrip('\n')
          dir_candidate = os.path.dirname(line.split(source["parent"])[1])
          hdfs_dir = os.path.join(hdfs_path, dir_candidate)
          hdfs_parents = []
          hdfs_parent = hdfs_dir
          while hdfs_parent not in hadoop_paths:
            print(">> %s" % hdfs_parent)
            hdfs_parents.append(str(hdfs_parent))
            hdfs_parent = os.path.dirname(hdfs_parent)
          hadoop_paths.extend(list(reversed(hdfs_parents)))

          cmds.append(" ".join(["xrdcp", line, hdfs_dir]))

  cmd_files = os.path.join(output_dir, XRDCP_SH)
  cmd_file = os.path.join(output_dir, XRDCP_SUBMIT_SH)
  nohup_files = os.path.join(output_dir, NOHUP_OUT)
  hadoop_file = os.path.join(output_dir, HADOOP_SH)
  make_file = os.path.join(output_dir, MAKEFILE)
  log_files = os.path.join(output_dir, LOGFILE)

  # Split the copy commands into `nof_splits' pieces and write them
  cmds_split = split(cmds, nof_splits)
  for i in range(nof_splits):
    cmd_files_i = cmd_files % i
    with codecs.open(cmd_files_i, 'w', 'utf-8') as f:
      f.write("#!/bin/bash\n")
      for cmd_split in cmds_split[i]:
        f.write("%s\n" % cmd_split)
    st = os.stat(cmd_files_i)
    os.chmod(cmd_files_i, st.st_mode | stat.S_IEXEC)

  # Write the individual commands into a bash file
  with codecs.open(cmd_file, 'w', 'utf-8') as f:
    f.write("#!/bin/bash\n")
    f.write("%s\n" % hadoop_file)
    for i in range(nof_splits):
      f.write("nohup %s &> %s &\n" % (cmd_files % i, nohup_files % i))

  # Write the `hadoop' commands
  with codecs.open(hadoop_file, 'w', 'utf-8') as f:
    f.write("#!/bin/bash\n")
    for hadoop_path in hadoop_paths:
      f.write("hadoop fs -mkdir %s\n" % hadoop_path)

  # Apply chmod +x to the bash files
  for bash_file in (cmd_file, hadoop_file):
    st = os.stat(bash_file)
    os.chmod(bash_file, st.st_mode | stat.S_IEXEC)

  # Create the Makefile as well
  with codecs.open(make_file, 'w', 'utf-8') as f:
    hadoop_log = log_files % "hadoop"
    hadoop_job = "jobh"
    copy_job = "job%d"
    job_list = " ".join(map(lambda x: copy_job % x, range(nof_splits)) + [hadoop_job])
    f.write("SHELL :=/bin/bash\n\n")
    f.write(".PHONY: %s\n\n" % job_list)
    f.write("all: %s\n\n" % job_list)
    f.write("%s:\n\t%s > %s 2>&1\n\n" % (hadoop_job, hadoop_file, hadoop_log))
    for i in range(nof_splits):
      f.write("%s: %s\n" % ((copy_job % i), hadoop_job))
      f.write("\tsource %s > %s 2>&1\n\n" % (cmd_files % i, log_files % str(i)))

  print("There are %d copies per nohup job; %d in total" %
        (len(cmds_split[0]), len(cmds)))

if __name__ == '__main__':
  sources = [
    {"domain"  : "t3se01.psi.ch",
     "parent"  : "/store/user/perrozzi/VHBBHeppyV23",
     "subdirs" : []
    },
    {"domain"  : "stormgf1.pi.infn.it",
     "parent"  : "/store/user/cvernier/VHBBHeppyV23/",
     "subdirs" : [
       "ttH_M125_13TeV_powheg_pythia8", "ttHToNonbb_M125_13TeV_powheg_pythia8",
       "SingleMuon", "DoubleMuon"
       ]
     }
  ]
  output_dir = "/home/karl/sandbox/filelist"
  if not os.path.exists(output_dir) or not os.path.isdir(output_dir):
    os.makedirs(output_dir)

  # NB! no slash at the end of hdfs_path!!!
  hdfs_path = '/hdfs/local/karl/VHBBHeppyV23'
  nof_splits = 30

  for i in range(len(sources)):
    # Dump the full paths
    get_filelist(sources[i], output_dir)
    # Generate the bash scripts
    generate_cmds(sources[i], output_dir, hdfs_path, nof_splits)

  print("All done!")
  print("Please run:\t%s\n" % os.path.join(output_dir, XRDCP_SUBMIT_SH))
  print("Or:        \tmake -f %s -j %d\n" %
        (os.path.join(output_dir, MAKEFILE), nof_splits))
  print("If you run the first command, please do not exit your shell session!!!")
