import ctypes
import logging
import re
import os.path

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

class hdfsException(Exception):
  pass

def fuse_path(path):
  if not path.startswith("hdfs://"):
    raise hdfsException("Invalid path: %s" % path)
  return re.sub('^hdfs://', '/hdfs', path)

def normalize_path(path):
  if not path.startswith('/hdfs') and not path.startswith("hdfs://"):
    raise hdfsException("Invalid path: %s" % path)
  path_t = re.sub('^/hdfs', 'hdfs://', path) if path.startswith('/hdfs') else path
  path_url = urlparse(path_t)
  path_f = path_url.scheme + '://' + path_url.path
  return path_f

class _hdfs:
  _instance = None

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
      self.kind          = chr(hdfsFileInfoObject.contents.mKind)
      self.name          = normalize_path(hdfsFileInfoObject.contents.mName)
      self.size          = hdfsFileInfoObject.contents.mSize
      self.name_fuse     = fuse_path(self.name)
      self.basename      = os.path.basename(self.name_fuse)
      self.depth         = len(self.name_fuse.split(os.path.sep)) - 1
      self.sparent_depth = -1

    def __str__(self):
      return self.name_fuse

    def __repr__(self):
      return self.name

    def is_file(self):
      return self.kind == 'F'

    def is_dir(self):
      return self.kind == 'D'

  def __init__(self):
    self.lib_path = "/usr/lib64/libhdfs.so"
    if not os.path.isfile(self.lib_path):
      raise hdfsException("No such file: %s" % self.lib_path)

    logging.debug("Loading {lib}".format(lib = self.lib_path))
    self.lib = ctypes.cdll.LoadLibrary(self.lib_path)
    self.lib.hdfsListDirectory.restype = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.lib.hdfsGetPathInfo.restype   = ctypes.POINTER(_hdfs.hdfsFileInfo)
    self.hdfsFileInfo_size             = ctypes.sizeof(_hdfs.hdfsFileInfo)

    logging.debug("Building HDFS interface")
    self.bld = self.lib.hdfsNewBuilder()
    if not self.bld:
      raise hdfsException("Could not create new HDFS interface")
    self.lib.hdfsBuilderSetNameNode(self.bld, "hdfs-nn")
    self.lib.hdfsBuilderSetNameNodePort(self.bld, 9000)

    logging.debug("Connecting to the HDFS interface")
    self.fs = self.lib.hdfsBuilderConnect(self.bld)
    if not self.fs:
      raise hdfsException("Could not connect to the HDFS interface")

  def get_path_info(self, path):
    normalized_path = normalize_path(path)
    path_info = self.lib.hdfsGetPathInfo(self.fs, normalized_path)
    if not path_info:
      raise hdfsException("No such path: %s" % normalized_path)
    path_obj = _hdfs.info(path_info)
    self.lib.hdfsFreeFileInfo(path_info, 1)
    return path_obj

  def get_dir_entries(self, path_obj):
    nof_entries = ctypes.c_int()
    dir_ptr = self.lib.hdfsListDirectory(self.fs, path_obj.name, ctypes.byref(nof_entries))
    if not dir_ptr:
      raise hdfsException("No such path: %s" % path_obj.name)
    dir_ptr_copy = dir_ptr
    entries = []
    for j in range(nof_entries.value):
      entries.append(_hdfs.info(dir_ptr))
      void_p  = ctypes.cast(dir_ptr, ctypes.c_voidp).value + self.hdfsFileInfo_size
      dir_ptr = ctypes.cast(void_p, ctypes.POINTER(_hdfs.hdfsFileInfo))
    self.lib.hdfsFreeFileInfo(dir_ptr_copy, nof_entries)
    return entries

def hdfsWrapper():
  if _hdfs._instance is None:
    _hdfs._instance = _hdfs()
  return _hdfs._instance

hdfs = hdfsWrapper()
