# -*- coding: utf-8 -*-

# Author: Karl Ehatäht

import ctypes
import logging
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
  pass

class NoSuchPathException(Exception):
  pass

try:
  from urllib.parse import urlparse
except ImportError:
  from urlparse import urlparse

class _hdfs:
  _instance = None
  _tz = None

  @staticmethod
  def defuse(path):
    return re.sub('^/hdfs', '', path)

  @staticmethod
  def normalize_path(path):
    if not path.startswith("hdfs://"):
      raise hdfsException("Invalid path: %s" % path)

    path_url = urlparse(path)
    path_normalized = path_url.scheme + '://' + path_url.path
    return path_normalized

  @staticmethod
  def get_dt(unix_tm):
    return datetime.datetime.fromtimestamp(unix_tm, _hdfs._tz)

  class hdfsFileInfo(ctypes.Structure):
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
    def __init__(self, hdfsFileInfoObject):
      self.kind        = chr(hdfsFileInfoObject.contents.mKind)
      self.url         = _hdfs.normalize_path(hdfsFileInfoObject.contents.mName)
      self.name        = re.sub('^hdfs://', '/hdfs', self.url)
      self.lastMod     = _hdfs.get_dt(hdfsFileInfoObject.contents.mLastMod)
      self.size        = hdfsFileInfoObject.contents.mSize
      self.owner       = hdfsFileInfoObject.contents.mOwner
      self.group       = hdfsFileInfoObject.contents.mGroup
      self.permissions = hdfsFileInfoObject.contents.mPermissions
      self.lastAccess  = hdfsFileInfoObject.contents.mLastAccess

      if self.lastAccess:
        self.lastAccess = datetime.datetime.fromtimestamp(self.lastAccess, _hdfs._tz)
      else:
        self.lastAccess = None

    def isfile(self):
      return self.kind == 'F'

    def isdir(self):
      return self.kind == 'D'

  def __init__(self, nn = "default", port = 0):
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

    heapsize         = 20480
    memsize          = 2048
    cachesize        = 512
    malloc_arena_max = 4

    # source /usr/lib/hadoop/libexec/hadoop-config.sh && unset HADOOP_HDFS_HOME
    os.environ['LIBHDFS_OPTS']     = '-Xmx{}m'.format(heapsize)
    os.environ['HADOOP_CONF_DIR']  = '/etc/hadoop/conf'
    os.environ['MALLOC_ARENA_MAX'] = str(malloc_arena_max)
    os.environ['HADOOP_HEAPSIZE']  = str(heapsize)
    os.environ['HADOOP_PREFIX']    = '/usr/lib/hadoop'
    os.environ['HADOOP_OPTS']      = '-Xms{}m '.format(memsize)                           + \
                                     '-XX:ReservedCodeCacheSize={}m '.format(cachesize)   + \
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

  def get_path_info(self, path, fail = True):
    if not path.startswith('/hdfs'):
      raise hdfsException("Invalid path: %s" % path)

    normalized_path = re.sub('^/hdfs', '', path)
    path_info = self.lib.hdfsGetPathInfo(self.fs, normalized_path)
    if not path_info:
      if fail:
        raise NoSuchPathException(path)
      else:
        return None

    path_obj = _hdfs.info(path_info)
    self.lib.hdfsFreeFileInfo(path_info, 1)
    return path_obj

  def exists(self, path):
    is_local = path.startswith('/hdfs')
    if is_local:
      return self.lib.hdfsExists(self.fs, _hdfs.defuse(path)) == 0
    else:
      return os.path.exists(path)

  def isfile(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path, fail = False)
      return path_obj.isfile() if path_obj else False
    else:
      return os.path.isfile(path)

  def isdir(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path, fail = False)
      return path_obj.isdir() if path_obj else False
    else:
      return os.path.isdir(path)

  def getsize(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.size
    else:
      return os.path.getsize(path)

  def getatime(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.lastAccess
    else:
      return _hdfs.get_dt(os.path.getatime(path))

  def getmtime(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.lastMod
    else:
      return _hdfs.get_dt(os.path.getmtime(path))

  def getowner(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.owner
    else:
      return pwd.getpwuid(os.stat(path)[stat.ST_UID]).pw_name

  def getgroup(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.group
    else:
      return grp.getgrgid(os.stat(path)[stat.ST_GID]).gr_name

  def getpermissions(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return int(oct(path_obj.permissions)[-3:])
    else:
      return int(oct(os.stat(path)[stat.ST_MODE])[-3:])
  
  def listdir(self, path, return_objs = False):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path) if type(path) == str else path
      nof_entries = ctypes.c_int()
      dir_ptr = self.lib.hdfsListDirectory(self.fs, path_obj.url, ctypes.byref(nof_entries))
      if not dir_ptr:
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

  def copy(self, src, dst, overwrite = True):
    if not self.exists(src):
      raise NoSuchPathException(dst)

    if self.isdir(dst):
      if overwrite:
        self.remove(dst)
      else:
        raise hdfsException("Destination '%s' is a directory but overwriting disabled" % dst)

    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = re.sub('^/hdfs', '', src)
    dst_defused = re.sub('^/hdfs', '', dst)

    if is_local_src and is_local_dst:
      try:
        if self.isdir(src_defused):
          shutil.copytree(src_defused, dst_defused)
        else:
          shutil.copy2(src_defused, dst_defused)
      except OSError:
        return -1
      return 0
    elif is_local_src and not is_local_dst:
      return self.lib.hdfsCopy(self.lfs, src_defused, self.fs, dst_defused)
    elif not is_local_src and is_local_dst:
      return self.lib.hdfsCopy(self.fs, src_defused, self.lfs, dst_defused)
    elif not is_local_src and not is_local_dst:
      return self.lib.hdfsCopy(self.fs, src_defused, self.fs, dst_defused)
    else:
      raise RuntimeError("Impossible error")

  def move(self, src, dst):
    if not self.exists(src):
      raise NoSuchPathException(src)

    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = re.sub('^/hdfs', '', src)
    dst_defused = re.sub('^/hdfs', '', dst)

    if is_local_src and is_local_dst:
      try:
        shutil.move(src_defused, dst_defused)
      except IOError:
        return -1
      return 0
    elif is_local_src and not is_local_dst:
      return self.lib.hdfsMove(self.lfs, src_defused, self.fs, dst_defused)
    elif not is_local_src and is_local_dst:
      return self.lib.hdfsMove(self.fs, src_defused, self.lfs, dst_defused)
    elif not is_local_src and not is_local_dst:
      return self.lib.hdfsRename(self.fs, src_defused, dst_defused)
    else:
      raise RuntimeError("Impossible error")

  def remove(self, path, recursive = True):
    if not self.exists(path):
      raise NoSuchPathException(path)

    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsDelete(self.fs, path_defused, int(recursive))
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
      return 0

  def mkdirs(self, path):
    if self.isfile(path):
      raise hdfsException("Cannot create directory since the requested path is a file: %s" % path)

    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      # the function returns 0 if the directory was successfully created or if it already exists
      return self.lib.hdfsCreateDirectory(self.fs, path_defused)
    else:
      try:
        os.makedirs(path)
      except OSError, e:
        # directory already exists -> pretend that is succeeded as is the case for hdfsCreateDirectory()
        if e.errno != errno.EEXIST:
          return -1
      except:
        return -1
      return 0

  def chown(self, path, owner = "", group = ""):
    if not owner and not group:
      raise hdfsException("Missing owner and group name")

    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsChown(self.fs, path_defused, owner, group)
    else:
      uid = pwd.getpwnam(owner).pw_uid
      gid = grp.getgrnam(group).gr_gid
      try:
        os.chown(path, uid, gid)
      except IOError:
        return -1
      return 0

  def chmod(self, path, permissions):
    if not (0 <= int(permissions) <= 777):
      raise hdfsException("Invalid permission code: %s" % str(permissions))
    permissions_oct = int(str(permissions), 8)

    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsChmod(self.fs, path_defused, permissions_oct)
    else:
      try:
        os.chmod(path, permissions_oct)
      except IOError:
        return -1
      return 0

def hdfsWrapper():
  if _hdfs._instance is None:
    _hdfs._instance = _hdfs()
    _hdfs._tz = dateutil.tz.tzlocal()
  return _hdfs._instance

hdfs = hdfsWrapper()
