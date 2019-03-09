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

#NOTE works only when the following is done:
# /usr/lib/hadoop/libexec/hadoop-config.sh
# export CLASSPATH=`hadoop classpath --glob`
# for j in $(ls /usr/lib/hadoop/client/*.jar); do export CLASSPATH=$CLASSPATH:$j; done
#
#TODO
# - set necessary environment variables at runtime
# - implement unit tests

try:
  from urllib.parse import urlparse
except ImportError:
  from urlparse import urlparse

class _hdfs:
  _instance = None
  _tz = None
  
  class hdfsException(Exception):
    pass

  class NoSuchPathException(Exception):
    pass

  @staticmethod
  def defuse(path):
    return re.sub('^/hdfs', '', path)

  @staticmethod
  def normalize_path(path):
    if not path.startswith("hdfs://"):
      raise _hdfs.hdfsException("Invalid path: %s" % path)

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

    self.lib_path = "/usr/lib64/libhdfs.so"
    if not os.path.isfile(self.lib_path):
      raise _hdfs.hdfsException("No such file: %s" % self.lib_path)

    logging.debug("Loading {lib}".format(lib = self.lib_path))
    self.lib = ctypes.cdll.LoadLibrary(self.lib_path)
    self.lib.hdfsListDirectory.restype = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.lib.hdfsGetPathInfo.restype   = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.lib.hdfsGetDefaultBlockSize   = ctypes.c_int64
    self.lib.hdfsGetCapacity           = ctypes.c_int64
    self.lib.hdfsGetUsed               = ctypes.c_int64
    self.lib.hdfsDelete                = ctypes.c_int32
    self.lib.hdfsCreateDirectory       = ctypes.c_int32
    self.lib.hdfsChown                 = ctypes.c_int32
    self.lib.hdfsChmod                 = ctypes.c_int32
    self.lib.hdfsMove                  = ctypes.c_int32
    self.lib.hdfsCopy                  = ctypes.c_int32
    self.hdfsFileInfo_size             = ctypes.sizeof(_hdfs.hdfsFileInfo)

    logging.debug("Building HDFS interface")
    self.bld = self.lib.hdfsNewBuilder()
    if not self.bld:
      raise _hdfs.hdfsException("Could not create new HDFS interface")
    self.lib.hdfsBuilderSetNameNode(self.bld, self.nn)
    self.lib.hdfsBuilderSetNameNodePort(self.bld, self.port)

    self.lbld = self.lib.hdfsNewBuilder()
    self.lib.hdfsBuilderSetNameNode(self.lbld, None)
    self.lib.hdfsBuilderSetNameNodePort(self.lbld, 0)

    logging.debug("Connecting to the HDFS interface")
    self.fs = self.lib.hdfsBuilderConnect(self.bld)
    if not self.fs:
      raise _hdfs.hdfsException(
        "Could not connect to the HDFS interface (nn = '%s', port = %d)" % (self.nn, self.port)
      )

    logging.debug("Interfacing to the local file system")
    self.lfs = self.lib.hdfsBuilderConnect(self.lbld)
    if not self.lfs:
      raise _hdfs.hdfsException("Could not create interface to local file system")

  def get_path_info(self, path):
    if not path.startswith('/hdfs'):
      raise _hdfs.hdfsException("Invalid path: %s" % path)
    normalized_path = re.sub('^/hdfs', '', path)
    path_info = self.lib.hdfsGetPathInfo(self.fs, normalized_path)
    if not path_info:
      raise _hdfs.NoSuchPathException(path)

    path_obj = _hdfs.info(path_info)
    self.lib.hdfsFreeFileInfo(path_info, 1)
    return path_obj

  def list_dir(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path) if type(path) == str else path
      nof_entries = ctypes.c_int()
      dir_ptr = self.lib.hdfsListDirectory(self.fs, path_obj.url, ctypes.byref(nof_entries))
      if not dir_ptr:
        raise _hdfs.NoSuchPathException(path)

      entries = []
      for idx in range(nof_entries.value):
        void_p  = ctypes.cast(dir_ptr, ctypes.c_voidp).value + idx * self.hdfsFileInfo_size
        cur_ptr = ctypes.cast(void_p, ctypes.POINTER(_hdfs.hdfsFileInfo))
        path_obj = _hdfs.info(cur_ptr)
        entries.append(path_obj.name)
      self.lib.hdfsFreeFileInfo(dir_ptr, nof_entries)

      return entries
    else:
      return os.listdir(path)

  def get_default_block_size(self):
    return self.lib.hdfsGetDefaultBlockSize(self.fs)

  def get_capacity(self):
    return self.lib.hdfsGetCapacity(self.fs)

  def get_used(self):
    return self.lib.hdfsGetUsed(self.fs)

  def exists(self, path):
    is_local = path.startswith('/hdfs')
    if is_local:
      return self.lib.hdfsExists(self.fs, _hdfs.defuse(path)) == 0
    else:
      return os.path.exists(path)

  def isfile(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.isfile()
    else:
      return os.path.isfile(path)

  def isdir(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.isdir()
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
      return grp.getgrgid(os.stat(path)[stat.ST_UID]).gr_name

  def getpermissions(self, path):
    if path.startswith('/hdfs'):
      path_obj = self.get_path_info(path)
      return path_obj.permissions
    else:
      return int(oct(os.stat(path)[stat.ST_MODE])[-3:])

  def copy(self, src, dst):
    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = re.sub('^/hdfs', '', src)
    dst_defused = re.sub('^/hdfs', '', dst)
    if is_local_src and is_local_dst:
      try:
        shutil.copy(src_defused, dst_defused)
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
    is_local_src = not src.startswith('/hdfs')
    is_local_dst = not dst.startswith('/hdfs')
    src_defused = re.sub('^/hdfs', '', src)
    dst_defused = re.sub('^/hdfs', '', dst)
    if is_local_src and is_local_dst:
      try:
        shutil.move(src_defused, dst_defused)
      except OSError:
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

  def remove(self, path):
    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsDelete(self.fs, path_defused)
    else:
      try:
        shutil.rmtree(path)
      except OSError:
        return -1
      return 0

  def mkdirs(self, path):
    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsCreateDirectory(self.fs, path_defused)
    else:
      try:
        os.makedirs(path)
      except OSError:
        return -1
      return 0

  def chown(self, path, owner = "", group = ""):
    if not owner and not group:
      raise _hdfs.hdfsException("Missing owner and group name")
    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsChown(self.fs, path_defused, owner, group)
    else:
      uid = pwd.getpwnam(owner).pw_uid
      gid = grp.getgrnam(group).gr_gid
      try:
        os.chown(path, uid, gid)
      except OSError:
        return -1
      return 0

  def chmod(self, path, permissions):
    if not (0 <= int(permissions) <= 777):
      raise _hdfs.hdfsException("Invalid permission code: %s" % str(permissions))
    permissions_oct = int(str(permissions), 8)
    if path.startswith('/hdfs'):
      path_defused = re.sub('^/hdfs', '', path)
      return self.lib.hdfsChmod(self.fs, path_defused, permissions_oct)
    else:
      try:
        os.chmod(path, permissions_oct)
      except OSError:
        return -1
      return 0

def hdfsWrapper():
  if _hdfs._instance is None:
    _hdfs._instance = _hdfs()
    _hdfs._tz = dateutil.tz.tzlocal()
  return _hdfs._instance

hdfs = hdfsWrapper()
