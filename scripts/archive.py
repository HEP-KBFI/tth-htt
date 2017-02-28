#!/usr/bin/env python

import os, subprocess, shutil, argparse, logging, sys

def run_cmd(cmd_str, verbose = False):
  if verbose:
    print(cmd_str)

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

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-u', '--unarchive', dest = 'unarchive', action = 'store_true', default = False,
                      help = 'R|Archive')
  parser.add_argument('-p', '--path', dest = 'path', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Path to be archived')
  parser.add_argument('-k', '--keep', dest = 'keep', action = 'store_true', default = False,
                      help = 'R|Keep archived files (do not delete them)')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.path:
    path = os.path.abspath(args.path)
    use_default_path = False
  else:
    path = os.path.dirname(os.path.abspath(__file__))
    use_default_path = True
  verbose    = args.verbose
  unarchive  = args.unarchive
  keep_files = args.keep

  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  if not os.path.isdir(path):
    raise ValueError("No such directory: {missing_dir}".format(missing_dir = path))
  logging.debug("Attempting to archive {dir}".format(dir = path))

  home_path = os.path.expanduser('~')
  if not path.startswith(home_path):
    raise ValueError("You should apply this script on a directory somewhere in {home}!".format(home = home_path))

  path_relative_to_home = path[len(home_path) + 1:]
  tar_basename = '{tar_filename}.tar.gz'.format(tar_filename = path_relative_to_home.replace(os.path.sep, '_'))
  tar_fullpath = os.path.join(path, tar_basename)

  if not unarchive:

    if os.path.isfile(tar_fullpath):
      logging.warning('File {tar} already exists and it will be overwritten'.format(tar = tar_fullpath))

    skipped_files, to_archive = [tar_basename, os.path.basename(__file__)], []
    for any_file in os.listdir(path):
      if not any_file in skipped_files:
        to_archive.append(any_file)

    if not to_archive:
      raise ValueError("There's nothing to archive here")

    logging.debug('Will archive the following files in {dir}: {file_list}'.format(
      dir       = path,
      file_list = ', '.join(to_archive),
    ))

    tar = 'GZIP=-9 cd {tar_location}; tar -czf {tar_file} {to_archive}'.format(
      tar_location = path,
      tar_file     = tar_basename,
      to_archive   = ' '.join(to_archive),
    )

    tar_out, tar_err = run_cmd(tar, verbose = verbose)

    if not (tar_err or keep_files):
      for any_file in to_archive:
        to_remove = os.path.join(path, any_file)
        if os.path.isdir(to_remove):
          logging.warning('Removing directory {dir}'.format(dir = to_remove))
          shutil.rmtree(to_remove)
        else:
          logging.warning('Removing file {file}'.format(file = to_remove))
          os.remove(to_remove)

  else:
    if not os.path.isfile(tar_fullpath):
      raise ValueError("Expected a file {tar} but got nothing".format(tar = tar_fullpath))

    tar = 'cd {tar_location}; tar -zxf {tar_file}'.format(
      tar_location = path,
      tar_file     = tar_basename,
    )

    tar_out, tar_err = run_cmd(tar, verbose = verbose)

    if not (tar_err or keep_files):
      to_remove = tar_fullpath
      logging.warning('Removing file {file}'.format(file = to_remove))
      os.remove(to_remove)
