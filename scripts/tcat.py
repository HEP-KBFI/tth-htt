#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os, tarfile, sys, logging, argparse, math, time, contextlib

logging.basicConfig(
  stream = sys.stderr,   # so that the errors won't be piped
  level  = logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

try:
  import backports.lzma as xz
  has_lzma = True
except ImportError:
  logging.warning("No backports.lzma module available")
  has_lzma = False

'''Enables to view contents of the directory tree and individual files inside tar-gzipped files

Author: Karl Ehatäht

Usage:
  1. list files in the archive
    a) list files in the top level
         $ ./tcat.py -f foo.tar.gz -l
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:28 bar/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:22 baz/
         > -rw-r--r--     334B     F 2017-03-22 12:34:09 def.txt
         > -rw-r--r--     332B     F 2017-03-22 12:34:04 henk.txt
    b) list files inside a directory in the archive
         $ ./tcat.py -f foo.tar.gz -l -p bar
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:28 bar/
         > -rw-r--r--     332B     F 2017-03-22 12:34:28 bar/plugh.txt
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:58 bar/quux/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:34 bar/qux/
    c) list files recursively inside a directory in the archive
         $ ./tcat.py -f foo.tar.gz -l -p bar/quux -r
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:58 bar/quux/
         > -rw-r--r--     147B     F 2017-03-22 12:34:54 bar/quux/waldo.txt
         > -rw-r--r--      61B     F 2017-03-22 12:34:58 bar/quux/fred.txt
  2. print the contents of a file
    a) simple cat of a file
         $ ./tcat.py -f foo.tar.gz  -c -p bar/quux/waldo.txt
         > Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
         > Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         > 
    b) same as 2.a), but with line numbers in front of each line
         $ ./tcat.py -f foo.tar.gz  -c -p bar/quux/waldo.txt -n
         > 
         > bar/quux/waldo.txt:1:Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
         > bar/quux/waldo.txt:2:Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         > bar/quux/waldo.txt:3:
    c) cat inside of immediate files of a directory (can leave -p unspecified)
         $ ./tcat.py -f foo.tar.gz  -c -p bar/quux -n
         > bar/quux/waldo.txt:1:Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
         > bar/quux/waldo.txt:2:Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         > bar/quux/waldo.txt:3:
         > bar/quux/fred.txt:1:Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
    d) cat recursively (can leave -p unspecified)
         $ ./tcat.py -f foo.tar.gz  -c -p bar/qux -n -r
         >  bar/qux/corge/uier.txt:1:Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
         >  bar/qux/corge/uier.txt:2:Per id nulla essent, ex quo eros efficiendi, duo ea reque delectus.
         >  bar/qux/corge/uier.txt:3:Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         >  bar/qux/corge/uier.txt:4:
         >  bar/qux/corge/grault.txt:1:Novum salutatus pertinacia nam ex, te liber nostrud vis.
         >  bar/qux/corge/grault.txt:2:Mazim aliquid intellegam sit ea, sumo fugit iracundia vel id.
         >  bar/qux/corge/grault.txt:3:Per id nulla essent, ex quo eros efficiendi, duo ea reque delectus.
         >  bar/qux/corge/grault.txt:4:Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         >  bar/qux/corge/grault.txt:5:
         >  bar/qux/garply.txt:1:Lorem ipsum dolor sit amet, nec ei reque deleniti honestatis.
         >  bar/qux/garply.txt:2:Pri no sale partem officiis, ad pri feugiat salutatus mnesarchum.
         >  bar/qux/garply.txt:3:Novum salutatus pertinacia nam ex, te liber nostrud vis.
         >  bar/qux/garply.txt:4:Et qui democritum adipiscing instructior, quo ea meis evertitur, id nisl quodsi duo.
         >  bar/qux/garply.txt:5:
  3. extract a file/files
    a) extract a single file to cwd
         $ bar/qux/corge/uier.txt
         > # file is in ./bar/qux/corge/uier.txt
    b) extract a single directory and all its subdirectories and -files to cwd
         $ ./tcat.py -f foo.tar.gz -e -p bar/qux
         > # all the files are placed to ./bar/qux
    d) extract a single file to another directory (use -F/--force to force-create the missing output directory)
         $ ./tcat.py -f foo.tar.gz -e -p bar/qux/corge/uier.txt -o test -F
         > # file is in ./test/bar/qux/corge/uier.txt
    e) extract a single directory and all its subdirectories and -files to the output directory
         $ ./tcat.py -f foo.tar.gz -e -p bar/qux -o test
         > # all the files are placed to ./test/bar/qux
    f) extract everything to the output directory
         $ ./tcat.py -f foo.tar.gz -e -o test
         > # all the files are placed to ./test
  4. support for multiple tar files and paths (but bear in mind that the paths must be valid in both archives)
         $ ./tcat.py -f foo.tar.gz foo.tar.xz -l -p bar/ baz
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:28 bar/
         > -rw-r--r--     332B     F 2017-03-22 12:34:28 bar/plugh.txt
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:58 bar/quux/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:34 bar/qux/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:22 baz/
         > -rw-r--r--     314B     F 2017-03-22 12:34:17 baz/thud.txt
         > -rw-r--r--     338B     F 2017-03-22 12:34:22 baz/mos.txt
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:28 bar/
         > -rw-r--r--     332B     F 2017-03-22 12:34:28 bar/plugh.txt
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:58 bar/quux/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:34 bar/qux/
         > -rwxr-xr-x       0B     D 2017-03-22 12:34:22 baz/
         > -rw-r--r--     314B     F 2017-03-22 12:34:17 baz/thud.txt
         > -rw-r--r--     338B     F 2017-03-22 12:34:22 baz/mos.txt

Comments: Note that when extracting any existing files will be overwritten.
          The script supports GZIP, BZIP2 and LZMA compression algorithms, although the latter depends on system
          configuration (see Remarks below).
          The program works very effectively with archives that do not contain many files or for smaller archives in
          general. However, the script makes it easier to inspect certain files inside the archive without cleaning
          after yourself all the time.

Tips & Tricks: You can knit certain shell commands together in order to inspect the archive; some examples:
  a) list of files that end with extension .txt
    $ ./tcat.py -f foo.tar.gz -l -r | \
        awk -v m="\x0a" -v N="6" '{$N=m$N ;print substr($0, index($0,m)+1)}' | \
        grep ".*.txt$"
    > bar/plugh.txt
    > bar/quux/waldo.txt
    > bar/quux/fred.txt
    > bar/qux/corge/uier.txt
    > bar/qux/corge/grault.txt
    > bar/qux/garply.txt
    > baz/thud.txt
    > baz/mos.txt
    > def.txt
    > henk.txt
  b) show 5 largest files in a directory (-b shows the file sizes in bytes)
    $ ./tcat.py -f foo.tar.gz -l -r -b -p bar | sort -k2 -n -r | head -n 5
    > -rw-r--r--          332     F 2017-03-22 12:34:28 bar/plugh.txt
    > -rw-r--r--          272     F 2017-03-22 12:34:46 bar/qux/corge/grault.txt
    > -rw-r--r--          270     F 2017-03-22 12:34:34 bar/qux/garply.txt
    > -rw-r--r--          215     F 2017-03-22 12:34:41 bar/qux/corge/uier.txt
    > -rw-r--r--          147     F 2017-03-22 12:34:54 bar/quux/waldo.txt
  c) list of files that contain a certain word
    $ ./tcat.py -f foo.tar.gz -c -r -n | grep -i lorem | cut -d':' -f1
    > bar/plugh.txt
    > bar/quux/waldo.txt
    > bar/quux/fred.txt
    > bar/qux/corge/uier.txt
    > bar/qux/garply.txt
    > baz/thud.txt
    > def.txt
    > henk.txt

Remarks: For whatever reason, current and upcoming CMSSW package doesn't come with Python3, which has better tarfile
         module in the sense that it enables extracting LZMA-compressed files. This is particularly weird since
         the support for Python2 is soon coming to an end. Unfortunately, the pip installer coming with CMSSW package
         supports Python2.6 (although the default version is 2.7), so this means pip is unable to install the lzma
         module which deals with LZMA-compressed files. The remedy, of course, is to do it manually; to do so
         (instructions taken from https://github.com/peterjc/backports.lzma):
           1. build xz so that the developer headers would be available
             a) curl -O http://tukaani.org/xz/xz-5.2.3.tar.gz # or any newer version available at http://tukaani.org/xz
             b) tar -zxvf xz-5.2.3.tar.gz
             c) cd xz-5.2.3
             d) ./configure --prefix=/path/to/your/install/folder/xz
             e) make && make check && make install
           2. build the python module
             a) git clone git://github.com/peterjc/backports.lzma.git
             b) cd backports.lzma
             c) edit setup.py: add '/path/to/your/install/folder/xz/include' to include_dirs
             c) python setup.py install --prefix=/path/to/your/install/folder/python/backports.lzma
             d) append the prefix path to PYTHONPATH and export it so that it would be available at all times
             e) test it with python -c "import backports.lzma as xz"; if you get nothing back, then it's all good
         LZMA has way better compression rate than GZIP or BZIP2; GZIP2 has the best compression speed out of those
         three; BZIP2 is somewhere in-between in terms of compression rate and time, but the decompression speed is
         the worst.
'''

class TarFileException(Exception):
  pass

def xor(*args):
  '''Checks if only one value has been set to True in a list of booleans
  :param args: list, The list to test the check against (must be convertible to booleans)
  :return: True, if the list contains exactly one object mapped to True value; False, otherwise

  Note that it reduces to XOR operation if the size of the given list is two
  '''
  if len(args) < 2:
    raise ValueError("Must provide at least three arguments")
  return sum(map(bool, args) * 1) == 1

def is_binary_file(fd, bf_sz = 1024):
  '''Check if a given file descriptor points to a binary file
  :param fd: file, The file descriptor the contents of which is tested against
  :param bf_sz: int, Number of bytes to read from the beginning of the file
  :return: True, if the file descriptor corresponds to a binary file; False, otherwise

  Solution taken from: http://stackoverflow.com/a/7392391/4056193
  '''
  textchars = bytearray({7, 8, 9, 10, 12, 13, 27} | set(range(0x20, 0x100)) - {0x7f})
  fd.seek(0)
  is_bin = bool(fd.read(bf_sz).translate(None, textchars))
  fd.seek(0)
  return is_bin

def sz_str(sz_b):
  '''Converts byte size into human-readable form
  :param sz_b: int, bytes
  :return: str, human-readable string

  Cheers to: author of http://stackoverflow.com/a/14822210/4056193
  '''
  assert(isinstance(sz_b, int))
  if sz_b == 0:
    return '0B'
  size_name = ("B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB")
  i = int(math.floor(math.log(sz_b, 1024)))
  s = int(round(sz_b / math.pow(1024, i), 2))
  return '%s%s' % (s, size_name[i])

def TarInfo_type(idx):
  '''Converts filetype identifier from tarinfo prescription into more reasonable identifiers
  :param idx: str, tarinfo identifier
  :return: str, new identifier

  The meaning behind each tarfile identifier is explained in the original tarfile module.
  '''
  assert(isinstance(idx, str))
  if idx == tarfile.REGTYPE:
    return "F" # regular file
  if idx == tarfile.AREGTYPE:
    return "AF" # regular file
  if idx == tarfile.LNKTYPE:
    return "L" # link
  if idx == tarfile.SYMTYPE:
    return "SL" # symbolic link
  if idx == tarfile.CHRTYPE:
    return "CD" # character special device
  if idx == tarfile.BLKTYPE:
    return "BD" # block special device
  if idx == tarfile.DIRTYPE:
    return "D" # directory
  if idx == tarfile.FIFOTYPE:
    return "FIFO" # fifo special device
  if idx == tarfile.CONTTYPE:
    return "CF" # contiguous file
  if idx == tarfile.GNUTYPE_SPARSE:
    return "GSF" # GNU tar sparse file
  if idx == tarfile.GNUTYPE_LONGLINK:
    return "GSLL" # GNU tar sparse longlink
  if idx == tarfile.GNUTYPE_LONGNAME:
    return "GSLN" # GNU tar sparse longname
  if idx == tarfile.XHDTYPE:
    return "XHD" # POSIX.1-2001 extended header
  if idx == tarfile.XGLTYPE:
    return "XGL" # POSIX.1-2001 global header
  if idx == tarfile.SOLARIS_XHDTYPE:
    return "SOL" # Solaris extended header
  raise RuntimeError("Unrecognized file type: %s" % idx)

def TarInfo_str(tarinfo, list_in_bytes = False):
  '''Creates a human-readable string from tarfile.TarInfo object
  :param tarinfo: tarfile.TarInfo, the tarfile member to stringify
  :return: str, Human-readable string of the tarfile member object

  Repackaged parts of the original tarfile code (c.f. tarfile.list method).
  '''
  assert(isinstance(tarinfo,  tarfile.TarInfo))
  name_suffix = ''
  if tarinfo.isdir():
    name_suffix += os.path.sep
  if tarinfo.issym():
    name_suffix += ' -> ' + tarinfo.linkname
  if tarinfo.islnk():
    name_suffix += ' link to ' + tarinfo.linkname

  if list_in_bytes:
    tarinfo_size = str(tarinfo.size).rjust(12)
  else:
    tarinfo_size = sz_str(tarinfo.size).rjust(8)

  tarinfo_str = "%s %s %s %s %s" % (
      tarfile.filemode(tarinfo.mode),
      tarinfo_size,
      TarInfo_type(tarinfo.type).rjust(5),
      "%d-%02d-%02d %02d:%02d:%02d" % time.localtime(tarinfo.mtime)[:6],
      tarinfo.name + name_suffix,
    )
  return tarinfo_str

def TarInfoObject_print(tio, show_linenr, raise_err = False):
  '''Prints the contents of a text file inside the archive
  :param tio: tarfile.TarInfo, the tarfile member to print
  :param show_linenr: bool, If true, shows filename and line number in the begging of each line
  :param raise_err: bool, If true, raises error whenever there's a problem with file extraction
  :return: bool, True if the extraction was successful; False, otherwise
           Note that nothing is returned when raise_err is set to True

  Make sure that the tarfile member object indeed refers to a text file (use is_binary_file for that).
  '''
  try:
    with contextlib.closing(tar.extractfile(tio)) as f:
      if is_binary_file(f):
        if raise_err:
          logging.warning("File is a binary in archive {archive}: {filepath}".format(
            archive  = filename,
            filepath = filepath,
          ))
          raise TarFileException
        else:
          return False
      lines = f.read()
      if show_linenr:
        lines = '\n'.join(['%s:%d:%s' % (tio.name, idx + 1, x) for idx, x in enumerate(lines.split('\n'))])
      sys.stdout.write('%s\n' % lines)
  except tarfile.StreamError as err:
    if raise_err:
      logging.error("Caught an error in {archive} while extracting from {filepath}: {reason}".format(
        archive  = filename,
        filepath = filepath,
        reason   = err,
      ))
      raise TarFileException
    else:
      return False
  return True

if __name__ == '__main__':
  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  compression_choices = ['gz', 'bz2']
  if has_lzma:
    compression_choices.append('xz')
  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-f', '--file', dest = 'file', metavar = 'directory', required = True, type = str, default = [],
                      nargs = '+',
                      help = 'R|Path to be archived')
  parser.add_argument('-C', '--compression', dest = 'compression', metavar = 'type', required = False, type = str,
                      default = '', choices = compression_choices,
                      help = 'R|Compression used to archive the input file')
  parser.add_argument('-p', '--path', dest = 'path', metavar = 'path', required = False, type = str, default = [''],
                      nargs = '+',
                      help = 'R|Path inside the archive')
  parser.add_argument('-l', '--list', dest = 'list', action = 'store_true', default = False,
                      help = 'R|List files in the archive, given path')
  parser.add_argument('-e', '--extract', dest = 'extract', action = 'store_true', default = False,
                      help = 'R|Extract a given file')
  parser.add_argument('-r', '--recursive', dest = 'recursive', action = 'store_true', default = False,
                      help = 'R|Recursively list or extract files')
  parser.add_argument('-o', '--output', dest = 'output', metavar = 'path', required = False, type = str, default = '.',
                      help = 'R|Output directory where the extracted files will be saved')
  parser.add_argument('-c', '--cat', dest = 'cat', action = 'store_true', default = False,
                      help = 'R|Print the contents of a file')
  parser.add_argument('-F', '--force', dest = 'force', action = 'store_true', default = False,
                      help = "R|Force output directory creation (if it doesn't exist)")
  parser.add_argument('-n', '--show-line-numbers', dest = 'show_linenr', action = 'store_true', default = False,
                      help = 'R|When -c/--cat, show line numbers')
  parser.add_argument('-b', '--list-in-bytes', dest = 'bytes', action = 'store_true', default = False,
                      help = 'R|List file sizes in bytes (applies only with -l/--list)')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  filenames     = args.file
  compression_  = args.compression
  list_files    = args.list
  extract_files = args.extract
  filepaths     = map(lambda x: x.rstrip(os.path.sep), args.path)
  recursive     = args.recursive
  output        = args.output
  cat           = args.cat
  show_linenr   = args.show_linenr
  force         = args.force
  list_in_bytes = args.bytes

  if not xor(list_files, extract_files, cat):
    raise parser.error('You should specify either -l/--list, -e/--extract or -c/--cat')
  if recursive and extract_files:
    logging.warning('-r/--recursive has no effect without -e/--extract option')
  if show_linenr and not cat:
    logging.warning('-n/--show-linenumbers has no effect without -c/--cat option')
  if list_in_bytes and not list_files:
    logging.warning('-b/--list-in-bytes has no effect without -l/--list option')

  for filename in filenames:
    if not os.path.isfile(filename):
      logging.error('No such file: {filename}'.format(filename = filename))
      sys.exit(1)
    if not tarfile.is_tarfile(filename) and not has_lzma:
      logging.error('File is not a tar file: {filename}'.format(filename = filename))
      sys.exit(1)

  for filename in filenames:
    for filepath in filepaths:
      try:
        compression = compression_ if compression_ else os.path.splitext(filename)[1][1:]
        if compression != 'xz':
          tarargs = {
            'name' : filename,
            'mode' : 'r:%s' % compression,
          }
        else:
          tarargs = {
            'mode' : 'r',
            'fileobj' : xz.LZMAFile(filename, mode = 'r'),
          }
        with contextlib.closing(tarfile.open(**tarargs)) as tar:
          if list_files:
            TarInfo_str_bound = lambda x: TarInfo_str(x, list_in_bytes = list_in_bytes)
            if not filepath:
              selector = (lambda x: os.path.sep not in x) if not recursive else (lambda x: True)
              files = map(TarInfo_str_bound, [m for m in tar.getmembers() if selector(m.name)])
              sys.stdout.write('%s\n' % '\n'.join(files))
            else:
              try:
                filepath_info = tar.getmember(filepath)
              except KeyError:
                logging.error("No such path in archive {archive}: {filepath}".format(
                  archive  = filename,
                  filepath = filepath,
                ))
                raise TarFileException
              sys.stdout.write('%s\n' % TarInfo_str_bound(filepath_info))
              if filepath_info.isdir():
                filepath_wsep = filepath + os.path.sep
                selector = (lambda x: os.path.dirname(x) == filepath) if not recursive else \
                          (lambda x: x.startswith(filepath_wsep))
                children = map(TarInfo_str_bound, [m for m in tar.getmembers() if selector(m.name)])
                sys.stdout.write('%s\n' % '\n'.join(children))
          elif extract_files:
            if not os.path.isdir(output):
              if force:
                logging.debug('Attempting to create the output directory {output_dir}'.format(
                  output_dir = output,
                ))
                try:
                  os.makedirs(output)
                except IOError as err:
                  logging.error('Could not create directory {output_dir}: {reason}'.format(
                    output_dir = output,
                    reason     = err,
                  ))
                  raise TarFileException
              else:
                logging.error('Directory {output_dir} does not exist; use -F/--force to create it'.format(
                  output_dir = output,
                ))
                raise TarFileException
            if filepath:
              to_extract = []
              try:
                member = tar.getmember(filepath)
              except KeyError:
                logging.error('No such path in archive {archive}: {filepath}'.format(
                  archive  = filename,
                  filepath = filepath,
                ))
                raise TarFileException
              to_extract.append(member)
              if member.isdir():
                parent_dir = filepath + os.path.sep
                to_extract.extend([m for m in tar.getmembers() if m.name.startswith(parent_dir)])
              for m in to_extract:
                try:
                  tar.extract(m, path = output)
                except tarfile.ExtractError as err:
                  logging.error('Could not extract {file} from {archive} to {output_dir}: {reason}'.format(
                    file       = filepath,
                    archive    = filename,
                    output_dir = output,
                    reason     = err,
                  ))
                  raise TarFileException
            else:
              try:
                tar.extractall(output)
              except tarfile.ExtractError as err:
                logging.error('Could not extract {archive} to {output_dir}: {reason}'.format(
                  archive    = filename,
                  output_dir = output,
                  reason     = err,
                ))
                raise TarFileException
          elif cat:
            if filepath:
              try:
                m = tar.getmember(filepath)
              except KeyError:
                logging.error("No such path in archive {archive}: {filepath}".format(
                  archive  = filename,
                  filepath = filepath,
                ))
                raise TarFileException
              if m.isdir():
                filepath_wsep = filepath + os.path.sep
                selector = (lambda x: os.path.dirname(x) == filepath) if not recursive else \
                          (lambda x: x.startswith(filepath_wsep))
                children = [m for m in tar.getmembers() if selector(m.name) and (m.isfile() or m.islnk() or m.issym())]
                for child in children:
                  TarInfoObject_print(child, show_linenr, raise_err = False)
              elif m.isfile() or m.islnk() or m.issym():
                TarInfoObject_print(m, show_linenr, raise_err = True)
              else:
                logging.error("Not a file or directory in archive {archive}: {filepath}".format(
                  archive  = filename,
                  filepath = filepath,
                ))
                raise TarFileException
            else:
              selector = (lambda x: os.path.sep not in x) if not recursive else (lambda x: True)
              children = [m for m in tar.getmembers() if selector(m.name) and (m.isfile() or m.islnk() or m.issym())]
              for child in children:
                TarInfoObject_print(child, show_linenr, raise_err = False)
          else:
            raise RuntimeError("Internal error")
      except TarFileException:
        sys.exit(1)
