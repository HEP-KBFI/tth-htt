#!/usr/bin/env python
import codecs, os, re, stat, argparse, sys

ZOMBIE_FILES = "broken_files.txt"
ZEROFS_FILES = "zerofs_files.txt"
RESUBMIT_FILE = "resubmit.sh"

if __name__ == '__main__':

  parser = argparse.ArgumentParser(description = "Create resubmission file for xrdcp copy jobs")
  parser.add_argument('--broken-path', '-b', metavar = '/path/to/broken/dir', default = '.',
                      help = "Path to the directory where files '%s' and '%s' are stored" %
                             (ZOMBIE_FILES, ZEROFS_FILES))
  parser.add_argument('--remote-path', '-r', metavar = '/path/to/remote/dir', default = '.',
                      help = "Path to the directory where the files (w/o extensions) containing "
                             "the list of remote paths of the root files")
  parser.add_argument('--output-path', '-o', metavar = '/path/to/output/dir', default = '.',
                      help = "Path to which the resubmission script '%s' is written" % RESUBMIT_FILE)
  parse_results = parser.parse_args()

  # parse arguments
  broken_path = parse_results.broken_path
  remote_path = parse_results.remote_path
  output_path = parse_results.output_path

  for path in [broken_path, remote_path, output_path]:
    if not os.path.exists(path) or not os.path.isdir(path):
      raise ValueError("No such directory: '%s'" % path)
  resubmit_path = os.path.join(output_path, RESUBMIT_FILE)

  # define lambdas
  fill_array = lambda f: [l.rstrip('\n') for l in codecs.open(f, 'r', 'utf-8').readlines()]
  grep = lambda fparr, s: [str(l.rstrip('\n')) for f in fparr
                           for l in codecs.open(f, 'r', 'utf-8').readlines()
                           if re.match('^.*%s.*?$' % s, l)]
  is_binary = lambda x: os.system("file -b %s | grep text > /dev/null" % x) != 0
  chmodx = lambda x: os.chmod(x, os.stat(x).st_mode | stat.S_IEXEC)

  # read the list of files which are broken or have zero file size
  broken_file_txts = [os.path.join(broken_path, f) for f in [ZOMBIE_FILES, ZEROFS_FILES]
                      if os.path.isfile(os.path.join(broken_path, f))]
  if len(broken_file_txts) == 0:
    print("There are no files called '%s' or '%s' in directory '%s'" %
          (ZOMBIE_FILES, ZEROFS_FILES, broken_path))
    sys.exit(1)
  broken_files = [str(f) for bft in broken_file_txts for f in fill_array(bft)]
  if len(broken_files) == 0:
    print("There are no broken files left")
    sys.exit(255)

  # gather the files which have no extension
  valid_remotes = map(lambda x: os.path.join(remote_path, x),
                      filter(lambda y: os.path.isfile(os.path.join(remote_path, y)) and
                                       not is_binary(os.path.join(remote_path, y)) and
                                       re.match("(?!(.*\..*|Makefile))", y),
                             os.listdir(remote_path)
                             )
                      )
  if len(valid_remotes) == 0:
    print("There were no files w/o extension in directory '%s'" % remote_path)
    sys.exit(2)

  # start grepping the files containing lines starting with root://..
  # until we hit the jackpot
  copy_pairs = []
  for broken_file in broken_files:
    broken_file_split = broken_file.split('/')
    test_paths = ['/'.join(broken_file_split[i:]) for i in range(len(broken_file_split))]
    test_result = []
    for test_path in test_paths:
      test_result = grep(valid_remotes, test_path)
      if len(test_result) == 1: break
      else:                     test_result = []
    if len(test_result) != 1:
      raise RuntimeError("Something went horribly wrong")
    copy_pairs.append((test_result[0], os.path.dirname(broken_file)))

  # create a new command list for the files which we need to copy again
  # -f means 'force overwriting'
  if len(copy_pairs) > 0:
    with codecs.open(resubmit_path, 'w', 'utf-8') as f:
      f.write("#!/bin/bash\n")
      f.write('%s\n' % '\n'.join(['xrdcp -f %s %s' % pair for pair in copy_pairs]))
    chmodx(resubmit_path)
