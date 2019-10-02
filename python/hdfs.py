# -*- coding: utf-8 -*-

# Author: Karl Ehatäht

from tthAnalysis.HiggsToTauTau.common import logging

import ctypes
import re
import os
import datetime
import dateutil.tz
import stat
import pwd
import grp
import shutil
import errno

class hdfsException(Exception):
  '''Generic exception class designed to be raised in generic issues related to HDFS.
  '''
  pass

class NoSuchPathException(Exception):
  '''Exception class designed to be raised in case a given path does not exist on the file system.
  '''
  pass

try:
  from urllib.parse import urlparse
except ImportError:
  from urlparse import urlparse

class _hdfs:
  '''Main class for hosting the routines for connecting to the HDFS service and  performing direct calls to it.

  Note that paths that don't start with /hdfs are treated as "local" paths:
  - /hdfs/local/$USER -- the path is treated as HDFS path and it's prefix /hdfs is dropped internally before querying HDFS
  - /home/$USER -- the path is treated as local path because it does not start with /hdfs

  Using any other alternative for HDFS paths does *NOT* work because they don't start with /hdfs prefix:
  - /local/$USER -- the path is treated as local path but will raise exception since there is no /local/$USER on the system
  - hdfs:///local/$USER -- non-POSIX path that causes undefined behavior
  - hdfs://<namenode>:<port>/local/$USER -- non-POSIX path that causes undefined behavior

  The sanitazation of inputs is the responsibility of the user!
  '''
  _instance = None
  _tz = None

  @staticmethod
  def defuse(path):
    '''Remove /hdfs prefix from a given path
    :param path: The given path
    :return: Path without /hdfs in front of it

    Note: the function return the same string if it does not start with /hdfs

    Note: the main reason why this function is used so often is because the direct calls to HDFS that bypass FUSE do not
          know a thing about the FUSE mount point (which is /hdfs). Thus, in order to make proper calls we need to strip
          the path from /hdfs prefix -- otherwise the HDFS service does not recognize the path as valid path.
    '''
    return re.sub('^/hdfs', '', path)

  @staticmethod
  def normalize_path(url):
    '''Convert path URL into a POSIX-compatible path
    :param path: The URL of the path stored in mName field of _hdfs.hdfsFileInfo structure
    :return: POSIX path

    The function basically converts an URL of the form:

    hdfs://<namenode-name>:<HDFS-post>/<path>

    into:

    hdfs:///<path>
    '''
    if not url.startswith("hdfs://"):
      raise hdfsException("Invalid path: %s" % url)

    url_obj = urlparse(url)
    path = url_obj.scheme + '://' + url_obj.path
    return path

  @staticmethod
  def get_dt(unix_tm):
    '''Convert UNIX time to datetime object
    :param unix_tm: UNIX time in seconds
    :return: Datetime object in current time zone
    '''
    return datetime.datetime.fromtimestamp(unix_tm, _hdfs._tz)

  class hdfsFileInfo(ctypes.Structure):
    '''See more: https://github.com/ambroff/libhdfs/blob/cfabdbdea727d5ab8c4007d9ac8fd84e29bea911/hdfs.h#L327-L341
    '''
    _fields_ = [
      ('mKind',        ctypes.c_int),
      ('mName',        ctypes.c_char_p),
      ('mLastMod',     ctypes.c_int64),
      ('mSize',        ctypes.c_int64),
      ('mReplication', ctypes.c_short),
      ('mBlockSize',   ctypes.c_int64),
      ('mOwner',       ctypes.c_char_p),
      ('mGroup',       ctypes.c_char_p),
      ('mPermissions', ctypes.c_int32),
      ('mLastAccess',  ctypes.c_int64),
    ]

  class info:
    '''Class for transforming _hdfs.hdfsFileInfo object into a more accessible object
    '''
    def __init__(self, hdfsFileInfoObject):
      '''Constructor
      :param hdfsFileInfoObject: instance of _hdfs.hdfsFileInfo object

      Note: The last access time may not always be available (IIRC this may be true for directories only, though). Since
            we are supposed to convert the UNIX time of the last access time into a datetime object we will set it to
            None type in case the last access time is missing.
      '''
      self.kind          = chr(hdfsFileInfoObject.contents.mKind)
      self.url           = _hdfs.normalize_path(hdfsFileInfoObject.contents.mName)
      self.name          = re.sub('^hdfs://', '/hdfs', self.url)
      self.basename      = os.path.basename(self.name)
      self.depth         = self.name.count('/')
      self.lastMod       = _hdfs.get_dt(hdfsFileInfoObject.contents.mLastMod)
      self.size          = hdfsFileInfoObject.contents.mSize
      self.replication   = hdfsFileInfoObject.contents.mReplication
      self.owner         = hdfsFileInfoObject.contents.mOwner
      self.group         = hdfsFileInfoObject.contents.mGroup
      self.permissions   = hdfsFileInfoObject.contents.mPermissions
      self.lastAccess    = hdfsFileInfoObject.contents.mLastAccess
      self.sparent_depth = -1

      if self.lastAccess:
        self.lastAccess = datetime.datetime.fromtimestamp(self.lastAccess, _hdfs._tz)
      else:
        self.lastAccess = None

    def isfile(self):
      '''Check if a given path object corresponds to a file
      :return: True if the given path object corresponds to a file,
               False otherwise
      '''
      return self.kind == 'F'

    def isdir(self):
      '''Check if a given path object corresponds to a directory
      :return: True if the given path object corresponds to a directory,
               False otherwise
      '''
      return self.kind == 'D'

    def __str__(self):
      return self.name

    def __repr__(self):
      return self.name

  def __init__(self, nn = "hdfs-nn", port = 9000):
    '''Set up runtime parameters for performing direct queries to HDFS
    :param nn:   Name of the name node
    :param port: HDFS service port

    The constructor does the following three things:
    - set up necessary environment variables in order to perform queries to HDFS
    - dynamically load the library calls from libhdfs.so and define the return types for each call
    - build the connection to Hadoop service and local file system
    '''
    self.nn = nn
    self.port = port

    logging.debug("Setting environment variables")

    hadoop_prefix = '/usr/lib/hadoop'
    library_path  = os.path.join(hadoop_prefix, 'lib/native')
    log_dir       = os.path.join(hadoop_prefix, 'logs')
    log_file      = 'hadoop.log'
    home_dir      = hadoop_prefix
    policy_file   = 'hadoop-policy.xml'

    id_str          = ''
    log_level       = 'INFO'
    preferIPv4Stack = True

    heapsize         = 256
    memsize          = 64
    cachesize        = 64
    malloc_arena_max = 2
    gc_threads       = 1

    # source /usr/lib/hadoop/libexec/hadoop-config.sh && unset HADOOP_HDFS_HOME
    # Unfortunately, it not possible to completely suppress JVM stack trace in case the call to a Java library throws
    # an exception. Tried both '-XX:-StackTraceInThrowable' and '-XX:MaxJavaStackTraceDepth=0' in both 'HADOOP_OPTS'
    # and 'JAVA_TOOL_OPTIONS' environment variables but to no avail.
    os.environ['JAVA_HOME']        = ''
    os.environ['LIBHDFS_OPTS']     = '-Xmx{}m'.format(heapsize)
    os.environ['HADOOP_CONF_DIR']  = '/etc/hadoop/conf'
    os.environ['MALLOC_ARENA_MAX'] = str(malloc_arena_max)
    os.environ['HADOOP_HEAPSIZE']  = str(heapsize * 10)
    os.environ['HADOOP_PREFIX']    = '/usr/lib/hadoop'
    os.environ['HADOOP_OPTS']      = '-Xms{}m '.format(memsize)                           + \
                                     '-XX:ReservedCodeCacheSize={}m '.format(cachesize)   + \
                                     '-XX:ParallelGCThreads={} '.format(gc_threads)       + \
                                     '-Dhadoop.log.dir={} '.format(log_dir)               + \
                                     '-Dhadoop.log.file={} '.format(log_file)             + \
                                     '-Dhadoop.home.dir={} '.format(home_dir)             + \
                                     '-Dhadoop.id.str={} '.format(id_str)                 + \
                                     '-Dhadoop.root.logger={},console '.format(log_level) + \
                                     '-Dhadoop.policy.file={} '.format(policy_file)       + \
                                     '-Djava.library.path={} '.format(library_path)       + \
                                     '-Djava.net.preferIPv4Stack={}'.format('true' if preferIPv4Stack else 'false')
    if not os.environ['LD_LIBRARY_PATH'].endswith(':'):
      os.environ['LD_LIBRARY_PATH'] += ':'
    os.environ['LD_LIBRARY_PATH'] += library_path

    # hadoop classpath --glob
    classpath = [
      "/etc/hadoop/conf",
      "/usr/lib/hadoop",
      "/usr/lib/hadoop/lib",
      "/usr/lib/hadoop-hdfs",
      "/usr/lib/hadoop-hdfs/lib",
    ]
    client_library = "/usr/lib/hadoop/client"
    classpath.extend(
      map(
        lambda jarfile: os.path.join(client_library, jarfile),
        filter(
          lambda filename: filename.endswith('.jar'),
          os.listdir(client_library)
        )
      )
    )
    os.environ['CLASSPATH'] = ':'.join(classpath)

    lib_path = "/usr/lib64/libhdfs.so"
    if not os.path.isfile(lib_path):
      raise hdfsException("No such file: %s" % lib_path)

    logging.debug("Loading {lib}".format(lib = lib_path))
    self.lib = ctypes.cdll.LoadLibrary(lib_path)
    self.lib.hdfsListDirectory.restype   = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.lib.hdfsGetPathInfo.restype     = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.lib.hdfsExists.restype          = ctypes.c_int32
    self.lib.hdfsDelete.restype          = ctypes.c_int32
    self.lib.hdfsCreateDirectory.restype = ctypes.c_int32
    self.lib.hdfsChown.restype           = ctypes.c_int32
    self.lib.hdfsChmod.restype           = ctypes.c_int32
    self.lib.hdfsMove.restype            = ctypes.c_int32
    self.lib.hdfsCopy.restype            = ctypes.c_int32
    self.hdfsFileInfo_size               = ctypes.sizeof(_hdfs.hdfsFileInfo)

    logging.debug("Building HDFS interface")
    self.bld = self.lib.hdfsNewBuilder()
    if not self.bld:
      raise hdfsException("Could not create new HDFS interface")
    self.lib.hdfsBuilderSetNameNode(self.bld, self.nn)
    self.lib.hdfsBuilderSetNameNodePort(self.bld, self.port)

    self.lbld = self.lib.hdfsNewBuilder()
    self.lib.hdfsBuilderSetNameNode(self.lbld, None)
    self.lib.hdfsBuilderSetNameNodePort(self.lbld, 0)

    logging.debug("Connecting to the HDFS interface")
    self.fs = self.lib.hdfsBuilderConnect(self.bld)
    if not self.fs:
      raise hdfsException(
        "Could not connect to the HDFS interface (nn = '%s', port = %d)" % (self.nn, self.port)
      )

    logging.debug("Interfacing to the local file system")
    self.lfs = self.lib.hdfsBuilderConnect(self.lbld)
    if not self.lfs:
      raise hdfsException("Could not create interface to local file system")

  def _address(self, path):
    return 'hdfs://{nn}:{port}/{path}'.format(nn = self.nn, port = self.port, path = _hdfs.defuse(path))

  def get_path_info(self, path, fail = True):
    '''Returns a dynamically-allocated _hdfs.info object that contains information about the given path
    :param path: The path of the file or directory
    :param fail: If True (the default), throw NoSuchPathException in case the path does not exist on the file system;
                 if False then instead return None in case the path does not exist on the file system
    :return: Instance of _hdfs.info class (or None if 'fail' is set to False and the path does not exist)

    May raise:
    - NoSuchPathException if the specified path does not exist on the file system
    - hdfsException       if the specified path is not an HDFS path
    '''
    if not path.startswith('/hdfs'):
      raise hdfsException("Invalid path: %s" % path)

    path_info = self.lib.hdfsGetPathInfo(self.fs, self._address(path))
    if not path_info:
      if fail:
        raise NoSuchPathException(path)
      else:
        return None

    path_obj = _hdfs.info(path_info)
    self.lib.hdfsFreeFileInfo(path_info, 1)
    return path_obj

  def exists(self, path):
    '''Check if a given path exists on the file system
    :param path: The given path
    :return: True, if the given path exists on the file system,
             False otherwise

    Note: does not raise any exceptions

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsExists.html
    '''
    is_hdfs = path.startswith('/hdfs')
    if is_hdfs:
      return self.lib.hdfsExists(self.fs, self._address(path)) == 0
    else:
      return os.path.exists(path)

  def isfile(self, path):
    '''Check if a given path corresponds to a file
    :param path: The given path
    :return: True, if the given path corresponds to a file,
             False otherwise

    Note: does not raise any exceptions
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path, fail = False)
      return path_obj.isfile() if path_obj else False
    else:
      return os.path.isfile(path)

  def isdir(self, path):
    '''Check if a given path corresponds to a directory
    :param path: The given path
    :return: True, if the given path corresponds to a directory,
             False otherwise

    Note: does not raise any exceptions
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path, fail = False)
      return path_obj.isdir() if path_obj else False
    else:
      return os.path.isdir(path)

  def getsize(self, path):
    '''Get the file size of the file
    :param path: The path of the file
    :return: File size in bytes

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    - hdfsException       if the specified path refers to a directory and not to a file
    '''
    if self.isdir(path):
      raise hdfsException("getsize cannot be applied to directory: %s" % path)

    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.size
    else:
      return os.path.getsize(path)

  def getatime(self, path):
    '''Get latest access time of the file or directory
    :param path: The path of the file or directory
    :return: Datetime object for the latest access time of the file or directory, or
             None if the latest access time is not available in case the specified file or directory resides on HDFS

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.lastAccess
    else:
      return _hdfs.get_dt(os.path.getatime(path))

  def getmtime(self, path):
    '''Get modification time of the file or directory
    :param path: The path of the file or directory
    :return: Datetime object for the modification time of the file or directory

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.lastMod
    else:
      return _hdfs.get_dt(os.path.getmtime(path))

  def getowner(self, path):
    '''Get owner name of the file or directory
    :param path: The path of the file or directory
    :return: Owner name of the file or directory

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.owner
    else:
      return pwd.getpwuid(os.stat(path)[stat.ST_UID]).pw_name

  def getgroup(self, path):
    '''Get group name that owns the file or directory
    :param path: The path of the file or directory
    :return: Group name that owns the file or directory

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.group
    else:
      return grp.getgrgid(os.stat(path)[stat.ST_GID]).gr_name

  def getpermissions(self, path):
    '''Get file permissions for a given path
    :param path: The path of the file or directory
    :return: Bitmask in decimal notation

    May raise:
    - NoSuchPathException if the specified path is an HDFS path but it does not exist on the file system
    - OSError             if the specified path is a non-HDFS path but it does not exist on the file system
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return int(oct(path_obj.permissions)[-3:])
    else:
      return int(oct(os.stat(path)[stat.ST_MODE])[-3:])
  
  def listdir(self, path, return_objs = False):
    '''Gets list of files and directories for a given path
    :param path:        The path of the directory
    :param return_objs: If False (the default), return the full paths of the files in the directory as string array;
                        if True, return the list of files in the directory as array of _hdfs.info objects
    :return: String array or array of _hdfs.info objects that correspond to files inside given path

    May raise:
    - NoSuchPathException if the path does not exist on the file system
    - hdfsException       if return_objs has been explicitly set to True but the requested path is not an HDFS path
                          (it's not possible to create _hdfs.info object from non-HDFS path)

    Note: if the given path points to a file, then the file itself will be returned as in single-element array

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsListDirectory.html
    '''
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path) if type(path) == str else path
      nof_entries = ctypes.c_int()
      dir_ptr = self.lib.hdfsListDirectory(self.fs, path_obj.url, ctypes.byref(nof_entries))
      if not dir_ptr:
        if self.isdir(path):
          return []
        else:
          raise NoSuchPathException(path)

      entries = []
      for idx in range(nof_entries.value):
        void_p  = ctypes.cast(dir_ptr, ctypes.c_voidp).value + idx * self.hdfsFileInfo_size
        cur_ptr = ctypes.cast(void_p, ctypes.POINTER(_hdfs.hdfsFileInfo))
        path_obj = _hdfs.info(cur_ptr)
        entries.append(path_obj if return_objs else path_obj.name)
      self.lib.hdfsFreeFileInfo(dir_ptr, nof_entries)

      return entries
    else:
      if return_objs:
        raise hdfsException("Cannot return HDFS objects for path: %s" % path)
      return list(map(lambda entry: os.path.join(path, entry), os.listdir(path)))

  def remove(self, path, recursive = True):
    '''Deletes the specified directory or file
    :param path:      The path of the file
    :param recursive: If False, deletes the specified directory, in case the directory is empty;
                      if the directory is not empty, an error is returned.
                      If True (the default), deletes the specified directory and all of its subdirectories.
                      If the specified object is a file, not a directory, this parameter is ignored.
    :return: 0 on success, -1 on error

    May raise:
    - NoSuchPathException if the path does not exist on the file system

    Note: the operation may fail and return -1 if the user has no permissions to remove file(s) from given path

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsDelete.html
    '''
    if not self.exists(path):
      raise NoSuchPathException(path)

    if path.startswith('/hdfs'):
      return self.lib.hdfsDelete(self.fs, self._address(path), int(recursive))
    else:
      try:
        if self.isdir(path):
          if recursive:
            shutil.rmtree(path)
          else:
            os.rmdir(path)
        else:
          os.remove(path)
      except OSError:
        return -1
      else:
        return 0

  def copy(self, src, dst, overwrite = True):
    '''Copy file or directory from one path to another
    :param src:       The path of source file or directory
    :param dst:       The path of destination file or directory
    :param overwrite: If the destination path exists on the file system and this parameter is set to True (the default),
                      then the destination path is completely removed before the copy operation;
                      if the destination path exists on the file system and this parameter is explicitly set to False,
                      then the operation raises an exception accordingly
    :return: 0 on success, -1 on error

    May raise:
    - NoSuchPathException if the path to the source file or directory does not exist on the file system
    - hdfsException       if the destination path exists but it cannot be removed due to insufficient permissions
    - hdfsException       if the destination path exists but the overwriting flag has been explicitly set to False

    Note: the operation may fail and return -1 if the user has no permissions to copy the source file or directory to
          the new location

    Note: the destination path must be explicit in the sense that the source file or directory won't be move *inside*
          the destination path but rather it will *replace* the existing path

    See more: https://github.com/ambroff/libhdfs/blob/cfabdbdea727d5ab8c4007d9ac8fd84e29bea911/hdfs.h#L245-L253
    '''
    if not self.exists(src):
      raise NoSuchPathException(src)

    if self.exists(dst):
      if overwrite:
        if not self.remove(dst):
          raise hdfsException("Unable to remove %s while overwriting it" % dst)
      else:
        raise hdfsException("Cannot copy to %s since the path already exist" % dst)

    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = self._address(src)
    dst_defused = self._address(dst)

    if is_local_src and is_local_dst:
      try:
        if self.isdir(src):
          shutil.copytree(src, dst)
        else:
          shutil.copy2(src, dst)
      except OSError:
        return -1
      return 0
    elif is_local_src and not is_local_dst:
      return self.lib.hdfsCopy(self.lfs, src, self.fs, dst_defused)
    elif not is_local_src and is_local_dst:
      return self.lib.hdfsCopy(self.fs, src_defused, self.lfs, dst)
    elif not is_local_src and not is_local_dst:
      return self.lib.hdfsCopy(self.fs, src_defused, self.fs, dst_defused)
    else:
      raise RuntimeError("Impossible error")

  def move(self, src, dst):
    '''Move file or directory from one path to another
    :param src: The path of source file or directory
    :param dst: The path of destination file or directory
    :return: 0 on success, -1 on error

    May raise:
    - NoSuchPathException if the path to the source file or directory does not exist on the file system

    Note: the operation may fail and return -1 if the user has no permissions to move the source file or directory to
          the destination path

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsRename.html
              https://github.com/ambroff/libhdfs/blob/cfabdbdea727d5ab8c4007d9ac8fd84e29bea911/hdfs.h#L256-L264
    '''
    if not self.exists(src):
      raise NoSuchPathException(src)

    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = self._address(src)
    dst_defused = self._address(dst)

    if is_local_src and is_local_dst:
      try:
        shutil.move(src, dst)
      except IOError:
        return -1
      return 0
    elif is_local_src and not is_local_dst:
      return self.lib.hdfsMove(self.lfs, src, self.fs, dst_defused)
    elif not is_local_src and is_local_dst:
      return self.lib.hdfsMove(self.fs, src_defused, self.lfs, dst)
    elif not is_local_src and not is_local_dst:
      return self.lib.hdfsRename(self.fs, src_defused, dst_defused)
    else:
      raise RuntimeError("Impossible error")

  def mkdirs(self, path):
    '''Recursively creates a directory at the specified path
    :param path: The path of the directory
    :return: 0 on success, -1 on error

    May raise:
    - hdfsException if the path is an existing file on the file system

    Note: if the directory to be created already exists, the function considers it as success and returns 0 as is
          the case with the familiar POSIX command 'mkdir -p'

    Note: the operation may fail and return -1 if the user has no permissions to create a directory at specified path

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsCreateDirectory.html
    '''
    if self.isfile(path):
      raise hdfsException("Cannot create directory since the requested path is a file: %s" % path)

    if path.startswith('/hdfs'):
      # The function returns 0 if the directory was successfully created or if it already exists
      return self.lib.hdfsCreateDirectory(self.fs, self._address(path))
    else:
      try:
        os.makedirs(path)
      except OSError, e:
        if e.errno != errno.EEXIST:
          return -1
        else:
          # Directory already exists -> pretend that is succeeded as is the case for hdfsCreateDirectory()
          return 0
      except:
        return -1
      else:
        return 0

  def chown(self, path, owner = "", group = ""):
    '''Changes ownership of a file or directory in the manner of the chown command
    :param path:  The path to the file or directory
    :param owner: The user to own the file or directory; set to an empty string to keep the owner as is
    :param group: The group to own the file or directory; set to an empty string to keep the owner as is
    :return: 0 on success, -1 on error

    May raise:
    - NoSuchPathException if the path does not exist on the file system
    - hdfsException       if both owner and group names are empty

    Note: the operation may fail and return -1 if the user does not own the file or if either the assigned owner or
          group name do not exist in the system

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsChown.html
    '''
    if not self.exists(path):
      raise NoSuchPathException(path)

    if not owner and not group:
      raise hdfsException("Missing owner and group name")

    if path.startswith('/hdfs'):
      return self.lib.hdfsChown(self.fs, self._address(path), owner, group)
    else:
      try:
        uid = pwd.getpwnam(owner).pw_uid
        gid = grp.getgrnam(group).gr_gid
        os.chown(path, uid, gid)
      except KeyError:
        return -1
      except IOError:
        return -1
      else:
        return 0

  def chmod(self, path, permissions):
    '''Changes permissions on a file or directory in the manner of the chmod command
    :param path:        The path to the file or directory
    :param permissions: The bitmask for the new permissions in decimal representation (i.e. between 0 and 777)
    :return: 0 on success, -1 on error

    May raise:
    - NoSuchPathException if the path does not exist on the file system
    - hdfsException       if the provided bitmask is not between 0 and 777

    Note: an HDFS path cannot be given executable rights. If the provided bitmask implies executable rights,
          the executable rights are subtracted before the chmod operation and a warning is displayed accordingly.

    Note: the operation may fail and return -1 if the user does not own the file

    See more: https://mapr.com/docs/51/DevelopmentGuide/hdfsChmod.html
    '''
    if not self.exists(path):
      raise NoSuchPathException(path)

    if not (0 <= int(permissions) <= 777):
      raise hdfsException("Invalid permission code: %s" % str(permissions))
    permissions_oct = int(str(permissions), 8)

    if path.startswith('/hdfs'):
      if permissions_oct & 0111 != 0:
        logging.warning(
          "Cannot set executable rights to files that reside on /hdfs => setting it from {} to {} for {}".format(
            permissions,
            int(oct(permissions_oct ^ 0111)[-3:]),
            path,
          )
        )
      return self.lib.hdfsChmod(self.fs, self._address(path), permissions_oct)
    else:
      try:
        os.chmod(path, permissions_oct)
      except IOError:
        return -1
      else:
         return 0

def hdfsWrapper():
  '''Simple factory function for building a single instance of _hdfs class
  :return: New _hdfs class instance if it has never been initialized before,
           or the one and only _hdfs class instance if it has already been created.
  '''
  if _hdfs._instance is None:
    _hdfs._instance = _hdfs()
    _hdfs._tz = dateutil.tz.tzlocal()
  return _hdfs._instance

# Singleton of _hdfs class.
# Notice that in order to see the debug messages in the constructor of _hdfs class, you need to lower the logging level
# before the call:
#
# from tthAnalysis.HiggsToTauTau.hdfs import hdfs
#
# Once this line is executed, the instance of _hdfs object has already been created and is ready to use.
hdfs = hdfsWrapper()
