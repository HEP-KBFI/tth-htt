#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import os.path
import getpass

dir_str = os.path.join('/local', getpass.getuser())
dir_obj = hdfs.get_path_info(dir_str)
print(dir_obj.__dict__)
