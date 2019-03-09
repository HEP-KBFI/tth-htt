#!/usr/bin/env python

import os.path
import getpass
import logging
import sys

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

from tthAnalysis.HiggsToTauTau.hdfs import hdfs

dir_str = os.path.join('/hdfs/local/%s' % getpass.getuser())
dir_obj = hdfs.get_path_info(dir_str)
print(dir_obj.__dict__)

dirs = hdfs.list_directory(dir_str)
for d in dirs:
  print(d.name)

print(hdfs.exists(dir_str))

