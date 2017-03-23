#!/usr/bin/env python

import os, subprocess, shutil, argparse, logging, sys

'''Archives a directory

The script can archive the whole directory or only the files inside a directory. The latter option can be enabled
with -r/--no-recursive flag which tries to archive all files by recursively traversing a given directory and archiving
all files in each directory (but not the subdirectories), therefore preserving the directory structure. This is
the default behavior as it's easier to access and perhaps parse individual tarballs instead of a giant one which
holds all the files in it. This of course comes at a cost -- the compression rate isn't as good as by archiving
everything, but the problem can be relieved by using compression algorithms (like LZMA), which achieve better
compression rate. This can be done with -c/--compression option, which takes 'gzip', 'bzip2' or 'lzma' as arguments.
The compression level can also be regulated via -l/--level option, which by default uses maximum level (best is 9,
fastest is 1). The unarchiving switch -u/--unarchive restores the original files. By default, all files which
are archived will be deleted. This can be turned of with -k/--keep switch. Finally, there's -p option which takes
the path to be archived as an argument. If the option (and therefore the path itself) is not specified, the script
attempts to archive the path where the script resides (bar the script itself, so that it could be possible to
unarchive it). The script only works under $HOME. If you want to see the shell commands the script invokes, you can
do that with -v/--verbose option. The -t/--test option performs a dry run, i.e. doesn't actually un/archive anything
(coupled with -v option you can still see which command would be executed).

Some examples:
  1. Archive everything in the directory where this script is resides (assuming the script is somewhere in $HOME)
     ./archive.py
  2. Archive everything recursively in $HOME/some/path
     ./archive.py -p $HOME/some/path # the shell expands the (environment) variable implicitly
  3. Same as 2., but archive everything into one giant tarball
     ./archive.py -p $HOME/some/path -r

  If you want to
    a) keep the archived files (i.e. not delete them), add -k/--keep flag
    b) create one tarball, add -r/--no-recursive flag
    c) unarchive all tarballs, add -u/--unarchive flag
    d) unarchive, but keep the original tarballs, combine a) and c)
    e) unarchive the one giant tarball, combine b) and c)
    f) unarchive the one giant tarball, but keep it as well, combine a) and e)
  to 1., 2., 3.

  Falgs like -v/--verbose and -t/--test, and option -c/--compression can be added to any of the above examples;
  option -l/--level makes sense only when archiving (i.e. w/o -u/--unarchive option), but the script only prints
  a warning about it otherwise.
'''

def run_cmd(cmd_str, verbose = False, dryrun = False):
  if verbose:
    print(cmd_str)

  if dryrun:
    return '', ''

  cmd = subprocess.Popen(
    cmd_str,
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE,
    shell  = True,
  )
  cmd_out, cmd_err = cmd.communicate()

  if verbose:
    if cmd_out:
      print(cmd_out)
    if cmd_err:
      print(cmd_err)

  return cmd_out, cmd_err

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

  compression_options = ['gzip', 'bzip2', 'lzma']
  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-u', '--unarchive', dest = 'unarchive', action = 'store_true', default = False,
                      help = 'R|Archive')
  parser.add_argument('-p', '--path', dest = 'path', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Path to be archived')
  parser.add_argument('-c', '--compression', dest = 'compression', metavar = 'compression', required = False,
                      type = str.lower, choices = compression_options, default = compression_options[0],
                      help = 'R|Compression algorithm to use in un/archiving')
  parser.add_argument('-l', '--level', dest = 'level', metavar = 'number', required = False, type = int,
                      choices = range(1, 10), default = 9,
                      help = 'R|Compression level used (irrelevant with option -u/--unarchive)')
  parser.add_argument('-k', '--keep', dest = 'keep', action = 'store_true', default = False,
                      help = 'R|Keep archived files (do not delete them)')
  parser.add_argument('-r', '--no-recursive', dest = 'no_recursive', action = 'store_true', default = False,
                      help = 'R|Archive everything (not recursively)')
  parser.add_argument('-t', '--test', dest = 'test', action = 'store_true', default = False,
                      help = "R|Perform a dry-run (doesn't un/archive anything)")
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.path:
    path = os.path.abspath(args.path)
    use_default_path = False
  else:
    path = os.path.dirname(os.path.abspath(__file__))
    use_default_path = True
  verbose        = args.verbose
  unarchive      = args.unarchive
  keep_files     = args.keep
  level          = args.level
  compression    = args.compression
  no_recursive   = args.no_recursive
  test           = args.test
  this_file = os.path.basename(__file__)

  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  if unarchive and bool({'-l', '--level'} & set(sys.argv)):
    logging.warning('Option -l/--level has no effect when unarchiving')

  if not os.path.isdir(path):
    raise ValueError("No such directory: {missing_dir}".format(missing_dir = path))

  if compression == 'gzip':
    compression_extension = 'gz'
    compression_env = 'GZIP'
  elif compression == 'bzip2':
    compression_extension = 'bz2'
    compression_env = 'BZIP2'
  elif compression == 'lzma':
    compression_extension = 'xz'
    compression_env = 'XZ_OPT'
  else:
    raise RuntimeError("Internal error")

  home_path = os.path.expanduser('~')
  if not path.startswith(home_path):
    raise ValueError("You should apply this script on a directory somewhere in {home}!".format(home = home_path))
  path_relative_to_home = path[len(home_path) + 1:]
  tar_basename = '{tar_filename}.tar.{ext}'.format(
    tar_filename = path_relative_to_home.replace(os.path.sep, '_'),
    ext          = compression_extension,
  )

  if not no_recursive:
    if not unarchive:
      logging.debug("Attempting to recursively archive {dir}".format(dir = path))
      dirs = [path]
      paths = [path]
      while paths:
        p = paths.pop(0)
        for f in os.listdir(p):
          fp = os.path.join(p, f)
          if os.path.isdir(fp):
            dirs.append(fp)
            paths.append(fp)
      tar_template = "cd %s; find . -maxdepth 1 -mindepth 1 -type f ! -name {this_file} | " \
                    "{env}=-{level} xargs tar --create --{compression} --file {tarfile} " \
                    "--transform 's/\.\///g' ".format(
        this_file   = this_file,
        env         = compression_env,
        level       = level,
        compression = compression,
        tarfile     = tar_basename,
      )
      if not keep_files:
        tar_template += "--remove-files"
      for d in dirs:
        tar = tar_template % d
        tar_out, tar_err = run_cmd(tar, verbose = verbose, dryrun = test)
        if tar_err:
          logging.error('Caught tar error: {err}'.format(err = tar_err))
    else:
      logging.debug("Attempting to recursively unarchive {dir}".format(dir = path))
      tars = []
      paths = [path]
      while paths:
        p = paths.pop(0)
        for f in os.listdir(p):
          fp = os.path.join(p, f)
          if f == tar_basename and os.path.isfile(fp):
            tars.append(fp)
          elif os.path.isdir(fp):
            paths.append(fp)
      tar_template = "cd $(dirname {tarfile}); tar --%s --extract --file {tarfile}; " % compression
      if not keep_files:
        tar_template += "rm {tarfile}"
      for t in tars:
        tar = tar_template.format(tarfile = t)
        tar_out, tar_err = run_cmd(tar, verbose = verbose, dryrun = test)
        if tar_err:
          logging.error('Caught tar error: {err}'.format(err = tar_err))
  else:
    tar_fullpath = os.path.join(path, tar_basename)

    if not unarchive:
      logging.debug("Attempting to archive {dir}".format(dir = path))

      if os.path.isfile(tar_fullpath):
        logging.warning('File {tar} already exists and it will be overwritten'.format(tar = tar_fullpath))

      skipped_files, to_archive = [tar_basename, this_file], []
      for any_file in os.listdir(path):
        if not any_file in skipped_files:
          to_archive.append(any_file)

      if not to_archive:
        raise ValueError("There's nothing to archive here")

      logging.debug('Will archive the following files in {dir}: {file_list}'.format(
        dir       = path,
        file_list = ', '.join(to_archive),
      ))

      archiving_command = '{env}=-{level} tar --create --{compression} --file {tar_file} {to_archive} '.format(
        env          = compression_env,
        level        = level,
        compression  = compression,
        tar_file     = tar_basename,
        to_archive   = ' '.join(to_archive),
      )
      if not keep_files:
        archiving_command += '--remove-files'

      tar = 'cd {tar_location};{tar_command}'.format(
        tar_location = path,
        tar_command  = archiving_command,
      )

      tar_out, tar_err = run_cmd(tar, verbose = verbose, dryrun = test)
      if tar_err:
        logging.error('Caught tar error: {err}'.format(err = tar_err))

    else:
      logging.debug("Attempting to unarchive {dir}".format(dir = path))

      if not os.path.isfile(tar_fullpath):
        raise ValueError("Expected a file {tar} but got nothing".format(tar = tar_fullpath))

      unarchiving_command = 'tar --{compression} --extract --file {tar_file}'.format(
        compression = compression,
        tar_file    = tar_basename,
      )
      tar = 'cd {tar_location}; {tar_command}'.format(
        tar_location = path,
        tar_command  = unarchiving_command,
      )

      tar_out, tar_err = run_cmd(tar, verbose = verbose, dryrun = test)

      if not (tar_err or keep_files):
        to_remove = tar_fullpath
        logging.warning('Removing file {file}'.format(file = to_remove))
        if not test:
          os.remove(to_remove)
