#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Author: Karl Ehatäht

import os.path
import getpass
import logging
import sys
import unittest
import time
import datetime

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)
from tthAnalysis.HiggsToTauTau.hdfs import hdfs, NoSuchPathException

class HDFSTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(HDFSTestCase, self).__init__(*args, **kwargs)

  @classmethod
  def setUpClass(cls):
    cls.groupName = "HEPUsers"
    cls.userName = getpass.getuser()
    cls.userHDFSdir = os.path.join('/hdfs/local', cls.userName)
    cls.userHomeDir = os.path.join('/home',       cls.userName)

    nonExistingUserName = "thisUserDoesNotExist"
    cls.nonExistingHDFSdir = os.path.join('/hdfs/local', nonExistingUserName)
    cls.nonExistingHomeDir = os.path.join('/home',       nonExistingUserName)

    fileBaseName = 'hdfstest.txt'
    cls.userHDFSfile = os.path.join(cls.userHDFSdir, fileBaseName)
    cls.userHomeFile = os.path.join(cls.userHomeDir, fileBaseName)

    cls.nonExistingHDFSfile = os.path.join(cls.nonExistingHDFSdir, fileBaseName)
    cls.nonExistingHomeFile = os.path.join(cls.nonExistingHomeDir, fileBaseName)

    text = 'testing'
    cls.fileSize = len(text)
    with open(cls.userHDFSfile, 'w') as f:
      f.write(text)
    # wait for 10 seconds so that the file would finally enter the hadoop file system
    time.sleep(10)

    with open(cls.userHomeFile, 'w') as f:
      f.write(text)

    # set file access and modification times explicitly
    atime_ut  = int(time.mktime(datetime.datetime.now().timetuple()))
    mtime_ut  = atime_ut - 10
    cls.atime = datetime.datetime.fromtimestamp(atime_ut, hdfs._tz)
    cls.mtime = datetime.datetime.fromtimestamp(mtime_ut, hdfs._tz)
    os.utime(cls.userHDFSfile, (atime_ut, mtime_ut))
    os.utime(cls.userHomeFile, (atime_ut, mtime_ut))

    cls.permissions = 666
    permissions_oct = int(str(cls.permissions), 8)
    os.chmod(cls.userHDFSfile, permissions_oct)
    os.chmod(cls.userHomeFile, permissions_oct)

  @classmethod
  def tearDownClass(cls):
    os.remove(cls.userHDFSfile)
    os.remove(cls.userHomeFile)

  def testFileExists(self):
    self.assertTrue(hdfs.exists(self.userHDFSdir))
    self.assertTrue(hdfs.exists(self.userHomeDir))

  def testFileNotExists(self):
    self.assertFalse(hdfs.exists(self.nonExistingHDFSdir))
    self.assertFalse(hdfs.exists(self.nonExistingHomeDir))

  def testIsDir(self):
    self.assertTrue(hdfs.isdir(self.userHDFSdir))
    self.assertTrue(hdfs.isdir(self.userHomeDir))

  def testIsNotDir(self):
    self.assertFalse(hdfs.isdir(self.nonExistingHDFSdir))
    self.assertFalse(hdfs.isdir(self.nonExistingHomeDir))

  def testIsFile(self):
    self.assertTrue(hdfs.isfile(self.userHDFSfile))
    self.assertTrue(hdfs.isfile(self.userHomeFile))

  def testIsNotFile(self):
    self.assertFalse(hdfs.isfile(self.nonExistingHDFSfile))
    self.assertFalse(hdfs.isfile(self.nonExistingHomeFile))

  def testFileSize(self):
    fileSizeHDFS = hdfs.getsize(self.userHDFSfile)
    fileSizeHome = hdfs.getsize(self.userHomeFile)
    self.assertEqual(fileSizeHDFS, self.fileSize)
    self.assertEqual(fileSizeHome, self.fileSize)

  def testFileSizeFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getsize(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getsize(self.nonExistingHomeFile))

  def testAccessTime(self):
    fileAccessTimeHDFS = hdfs.getatime(self.userHDFSfile)
    fileAccessTimeHome = hdfs.getatime(self.userHomeFile)
    self.assertNotEqual(fileAccessTimeHDFS, None)
    self.assertNotEqual(fileAccessTimeHome, None)
    self.assertEqual(fileAccessTimeHDFS - self.atime, datetime.timedelta(0))
    self.assertEqual(fileAccessTimeHome - self.atime, datetime.timedelta(0))

  def testAccessTimeFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getatime(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getatime(self.nonExistingHomeFile))

  def testModificationTime(self):
    fileModificationTimeHDFS = hdfs.getmtime(self.userHDFSfile)
    fileModificationTimeHome = hdfs.getmtime(self.userHomeFile)
    self.assertNotEqual(fileModificationTimeHDFS, None)
    self.assertNotEqual(fileModificationTimeHome, None)
    self.assertEqual(fileModificationTimeHDFS - self.mtime, datetime.timedelta(0))
    self.assertEqual(fileModificationTimeHome - self.mtime, datetime.timedelta(0))

  def testModificationTimeFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getmtime(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getmtime(self.nonExistingHomeFile))

  def testOwner(self):
    self.assertEqual(hdfs.getowner(self.userHDFSfile), self.userName)
    self.assertEqual(hdfs.getowner(self.userHomeFile), self.userName)

  def testOwnerFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getowner(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getowner(self.nonExistingHomeFile))

  def testGroup(self):
    self.assertEqual(hdfs.getgroup(self.userHDFSfile), self.groupName)
    self.assertEqual(hdfs.getgroup(self.userHomeFile), self.groupName)

  def testGroupFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getgroup(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getgroup(self.nonExistingHomeFile))

  def testPermissions(self):
    self.assertEqual(hdfs.getpermissions(self.userHDFSfile), self.permissions)
    self.assertEqual(hdfs.getpermissions(self.userHomeFile), self.permissions)

  def testPermissionsFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getpermissions(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getpermissions(self.nonExistingHomeFile))

def suite():
  testSuite = unittest.TestSuite()
  tests = [
    "testFileExists",
    "testFileNotExists",
    "testIsDir",
    "testIsNotDir",
    "testIsFile",
    "testIsNotFile",
    "testFileSize",
    "testFileSizeFail",
    "testAccessTime",
    "testAccessTimeFail",
    "testModificationTime",
    "testModificationTimeFail",
    "testOwner",
    "testOwnerFail",
    "testGroup",
    "testGroupFail",
    "testPermissions",
    "testPermissionsFail",
  ]
  for test in tests:
    testSuite.addTest(HDFSTestCase(test))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner(verbosity = 2)
runner.run(suite_instance)
