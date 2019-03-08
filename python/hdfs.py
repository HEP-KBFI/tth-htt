import ctypes
import logging
import re
import os.path
import datetime
import dateutil.tz

#NOTE works only when the following is done:
# /usr/lib/hadoop/libexec/hadoop-config.sh
# export CLASSPATH=`hadoop classpath --glob`
# for j in $(ls /usr/lib/hadoop/client/*.jar); do export CLASSPATH=$CLASSPATH:$j; done
#
#TODO
# - add methods for creating and removing directories and files
# - clean up the class
# - set necessary environment variables at runtime
# - implement unit tests
#
#EXAMPLES
# 1)
# from tthAnalysis.HiggsToTauTau.hdfs import hdfs
# hdfs.get_path_info(os.path.join('/hdfs', 'local', getpass.getuser()))

try:
  from urllib.parse import urlparse
except ImportError:
  from urlparse import urlparse

class _hdfs:
  _instance = None
  _tz = None
  
  class hdfsException(Exception):
    pass

  @staticmethod
  def fuse_path(path):
    if not path.startswith("hdfs://"):
      raise _hdfs.hdfsException("Invalid path: %s" % path)
    return re.sub('^hdfs://', '/hdfs', path)

  @staticmethod
  def normalize_path(path):
    if not path.startswith('/hdfs') and not path.startswith("hdfs://"):
      raise _hdfs.hdfsException("Invalid path: %s" % path)

    path_sub = re.sub('^/hdfs', 'hdfs://', path) if path.startswith('/hdfs') else path
    path_url = urlparse(path_sub)
    path_final = path_url.scheme + '://' + path_url.path
    return path_final

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
      self.name        = _hdfs.normalize_path(hdfsFileInfoObject.contents.mName)
      self.lastMod     = datetime.datetime.fromtimestamp(hdfsFileInfoObject.contents.mLastMod, _hdfs._tz)
      self.size        = hdfsFileInfoObject.contents.mSize
      self.replication = hdfsFileInfoObject.contents.mReplication
      self.owner       = hdfsFileInfoObject.contents.mOwner
      self.group       = hdfsFileInfoObject.contents.mGroup
      self.permissions = hdfsFileInfoObject.contents.mPermissions
      self.lastAccess  = hdfsFileInfoObject.contents.mLastAccess

      if self.lastAccess:
        self.lastAccess = datetime.datetime.fromtimestamp(self.lastAccess, _hdfs._tz)
      else:
        self.lastAccess = None
      self.nameFuse = _hdfs.fuse_path(self.name)
      self.depth    = len(self.nameFuse.split(os.path.sep)) - 1

    def is_file(self):
      return self.kind == 'F'

    def is_dir(self):
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
    self.lfs = self.lib.hdfsBuilderConnect(self.lbld)
    if not self.lfs:
      raise _hdfs.hdfsException("Could not create interface to local file system")

  def __del__(self):
    self.lib.hdfsDisconnect(self.fs)
    self.lib.hdfsDisconnect(self.lfs)

  '''Get path object from a path that
  '''
  def get_path_info(self, path):
    normalized_path = path#_hdfs.normalize_path(path)
    path_info = self.lib.hdfsGetPathInfo(self.fs, normalized_path)
    if not path_info:
      raise _hdfs.hdfsException("No such path: %s" % normalized_path)

    path_obj = _hdfs.info(path_info)
    self.lib.hdfsFreeFileInfo(path_info, 1)
    return path_obj

  def list_directory(self, path_obj):
    nof_entries = ctypes.c_int()
    dir_ptr = self.lib.hdfsListDirectory(self.fs, path_obj.name, ctypes.byref(nof_entries))
    if not dir_ptr:
      raise _hdfs.hdfsException("No such path: %s" % path_obj.name)

    entries = []
    for idx in range(nof_entries.value):
      void_p  = ctypes.cast(dir_ptr, ctypes.c_voidp).value + idx * self.hdfsFileInfo_size
      cur_ptr = ctypes.cast(void_p, ctypes.POINTER(_hdfs.hdfsFileInfo))
      entries.append(_hdfs.info(cur_ptr))
    self.lib.hdfsFreeFileInfo(dir_ptr, nof_entries)

    return entries

  def exists(self, path):
    return self.lib.hdfsExists(self.fs, path) == 0

  def exists_local(self, path):
    return self.lib.hdfsExists(self.lfs, path) == 0

  def is_file(self, path):
    pass

  def is_dir(self, path):
    pass

  def copy(self, src, dst):
    pass

  def move(self, src, dst):
    pass

  def remove(self, path):
    pass

  def create_directory(self, path):
    pass

  def chown(self, path):
    pass

  def chmod(self, path):
    pass

def hdfsWrapper():
  if _hdfs._instance is None:
    _hdfs._instance = _hdfs()
    _hdfs._tz = dateutil.tz.tzlocal()
  return _hdfs._instance

hdfs = hdfsWrapper()
