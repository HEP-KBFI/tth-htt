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
import stat

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)
from tthAnalysis.HiggsToTauTau.hdfs import hdfs, hdfsException, NoSuchPathException

class HDFSTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(HDFSTestCase, self).__init__(*args, **kwargs)

  @classmethod
  def setUpClass(cls):
    cls.groupName = "HEPUsers"
    cls.userName = getpass.getuser()
    cls.userHDFSdir = os.path.join('/hdfs/local', cls.userName)
    cls.userHomeDir = os.path.join('/home',       cls.userName)

    mainDirName = 'hdfstest'
    cls.userHDFSmainDir = os.path.join(cls.userHDFSdir, mainDirName)
    cls.userHomeMainDir = os.path.join(cls.userHomeDir, mainDirName)

    subdirName = 'subdir'
    cls.userHDFSsubDir = os.path.join(cls.userHDFSmainDir, subdirName)
    cls.userHomeSubDir = os.path.join(cls.userHomeMainDir, subdirName)

    cls.nonExistingGroupName = "thisGroupDoesNotExist"
    cls.nonExistingUserName = "thisUserDoesNotExist"
    cls.nonExistingHDFSdir = os.path.join('/hdfs/local', cls.nonExistingUserName)
    cls.nonExistingHomeDir = os.path.join('/home',       cls.nonExistingUserName)

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

    cls.userHDFSfileCopy = cls.userHDFSfile + '.copy'
    cls.userHomeFileCopy = cls.userHomeFile + '.copy'
    cls.userHDFSfileCopy2 = cls.userHDFSfileCopy + '2'
    cls.userHomeFileCopy2 = cls.userHomeFileCopy + '2'
    cls.userHDFSsubDirFile = os.path.join(cls.userHDFSsubDir, fileBaseName)
    cls.userHomeSubDirFile = os.path.join(cls.userHomeSubDir, fileBaseName)
    cls.userHDFSsubDir2 = cls.userHDFSsubDir + '2'
    cls.userHomeSubDir2 = cls.userHomeSubDir + '2'
    cls.userHDFSsubDir3 = cls.userHDFSsubDir + '3'
    cls.userHomeSubDir3 = cls.userHomeSubDir + '3'
    cls.userHDFSsubDir4 = cls.userHDFSsubDir + '4'
    cls.userHomeSubDir4 = cls.userHomeSubDir + '4'

  @classmethod
  def tearDownClass(cls):
    pass

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

  def testListDir(self):
    dirListHDFS = set(hdfs.listdir(self.userHDFSdir, return_objs = False))
    dirListHome = set(hdfs.listdir(self.userHomeDir, return_objs = False))
    dirListHDFSposix = set(map(lambda path: os.path.join(self.userHDFSdir, path), os.listdir(self.userHDFSdir)))
    dirListHomePosix = set(map(lambda path: os.path.join(self.userHomeDir, path), os.listdir(self.userHomeDir)))
    self.assertEqual(dirListHDFS, dirListHDFSposix)
    self.assertEqual(dirListHome, dirListHomePosix)

  def testListDirFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.listdir(self.nonExistingHDFSdir, return_objs = False))
    self.assertRaises(OSError,             lambda: hdfs.listdir(self.nonExistingHomeDir, return_objs = False))

  def testListDirObjects(self):
    dirListHDFSobjs  = set(map(lambda obj: obj.name, hdfs.listdir(self.userHDFSdir, return_objs = True)))
    dirListHDFSposix = set(map(lambda path: os.path.join(self.userHDFSdir, path), os.listdir(self.userHDFSdir)))
    self.assertEqual(dirListHDFSobjs, dirListHDFSposix)
    self.assertRaises(hdfsException, lambda: hdfs.listdir(self.userHomeDir, return_objs = True))

  def testMkdirsFail(self):
    self.assertEqual(hdfs.mkdirs(self.nonExistingHDFSdir), -1)
    self.assertEqual(hdfs.mkdirs(self.nonExistingHomeDir), -1)
    self.assertRaises(hdfsException, lambda: hdfs.mkdirs(self.userHDFSfile))
    self.assertRaises(hdfsException, lambda: hdfs.mkdirs(self.userHomeFile))

  def testMkdirs(self):
    self.assertEqual(hdfs.mkdirs(self.userHDFSsubDir), 0)
    self.assertEqual(hdfs.mkdirs(self.userHomeSubDir), 0)

  def testChownFail(self):
    self.assertRaises(hdfsException, lambda: hdfs.chown(self.userHomeFile, "", ""))
    self.assertRaises(hdfsException, lambda: hdfs.chown(self.userHDFSfile, "", ""))
    self.assertRaises(NoSuchPathException, lambda: hdfs.chown(self.nonExistingHomeFile, self.userName, self.groupName))
    self.assertRaises(NoSuchPathException, lambda: hdfs.chown(self.nonExistingHDFSfile, self.userName, self.groupName))
    self.assertEqual(hdfs.chown(self.userHomeFile, self.nonExistingUserName, ""), -1)
    self.assertEqual(hdfs.chown(self.userHDFSfile, self.nonExistingUserName, ""), -1)
    self.assertEqual(hdfs.chown(self.userHomeFile, "", self.nonExistingGroupName), -1)
    self.assertEqual(hdfs.chown(self.userHDFSfile, "", self.nonExistingGroupName), -1)

  def testChown(self):
    self.assertEqual(hdfs.chown(self.userHomeFile, self.userName, self.groupName), 0)
    self.assertEqual(hdfs.chown(self.userHDFSfile, self.userName, self.groupName), 0)

  def testChmodFail(self):
    chmod_invalid = 1234
    chmod_new     = 777
    self.assertRaises(hdfsException, lambda: hdfs.chmod(self.userHomeFile, chmod_invalid))
    self.assertRaises(hdfsException, lambda: hdfs.chmod(self.userHDFSfile, chmod_invalid))
    self.assertRaises(NoSuchPathException, lambda: hdfs.chmod(self.nonExistingHomeFile, chmod_new))
    self.assertRaises(NoSuchPathException, lambda: hdfs.chmod(self.nonExistingHDFSfile, chmod_new))

  def testChmod(self):
    chmod_new = 777
    self.assertEqual(hdfs.chmod(self.userHomeFile, chmod_new), 0)
    self.assertEqual(hdfs.chmod(self.userHDFSfile, chmod_new), 0)
    userHomeFilePermissions = int(oct(os.stat(self.userHomeFile)[stat.ST_MODE])[-3:])
    userHDFSfilePermissions = int(oct(os.stat(self.userHDFSfile)[stat.ST_MODE])[-3:])
    self.assertEqual(userHDFSfilePermissions, int(oct(int(str(chmod_new), 8) ^ 0111)[-3:]))
    self.assertEqual(userHomeFilePermissions, chmod_new)

  def testCopy(self):
    self.assertEqual(hdfs.copy(self.userHDFSfile, self.userHDFSfileCopy), 0)
    self.assertEqual(hdfs.copy(self.userHomeFile, self.userHomeFileCopy), 0)
    self.assertEqual(hdfs.copy(self.userHomeFile, self.userHDFSfileCopy2), 0)
    self.assertEqual(hdfs.copy(self.userHDFSfile, self.userHomeFileCopy2), 0)
    self.assertEqual(hdfs.copy(self.userHDFSsubDir, self.userHDFSsubDir2, overwrite = True), 0)
    self.assertEqual(hdfs.copy(self.userHomeSubDir, self.userHomeSubDir2, overwrite = True), 0)
    self.assertEqual(hdfs.copy(self.userHDFSsubDir, self.userHomeSubDir3, overwrite = True), 0)
    self.assertEqual(hdfs.copy(self.userHomeSubDir, self.userHDFSsubDir3, overwrite = True), 0)

  def testCopyFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.copy(self.nonExistingHDFSfile, self.userHDFSfileCopy))
    self.assertRaises(NoSuchPathException, lambda: hdfs.copy(self.nonExistingHomeFile, self.userHDFSfileCopy))
    self.assertRaises(NoSuchPathException, lambda: hdfs.copy(self.nonExistingHDFSfile, self.userHomeFileCopy))
    self.assertRaises(NoSuchPathException, lambda: hdfs.copy(self.nonExistingHomeFile, self.userHomeFileCopy))
    self.assertRaises(hdfsException, lambda: hdfs.copy(self.userHDFSsubDir, self.userHDFSsubDir2, overwrite = False))
    self.assertRaises(hdfsException, lambda: hdfs.copy(self.userHomeSubDir, self.userHomeSubDir2, overwrite = False))
    self.assertRaises(hdfsException, lambda: hdfs.copy(self.userHDFSsubDir, self.userHomeSubDir3, overwrite = False))
    self.assertRaises(hdfsException, lambda: hdfs.copy(self.userHomeSubDir, self.userHDFSsubDir3, overwrite = False))

  def testMoveFail(self):
    self.assertEqual(hdfs.move(self.userHDFSfile, self.nonExistingHDFSfile), -1)
    self.assertEqual(hdfs.move(self.userHomeFile, self.nonExistingHDFSfile), -1)
    self.assertEqual(hdfs.move(self.userHDFSfile, self.nonExistingHomeFile), -1)
    self.assertEqual(hdfs.move(self.userHomeFile, self.nonExistingHomeFile), -1)
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHDFSfile, self.nonExistingHDFSfile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHDFSfile, self.userHDFSfile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHDFSfile, self.userHomeFile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHomeFile, self.nonExistingHDFSfile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHomeFile, self.userHDFSfile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.move(self.nonExistingHomeFile, self.userHomeFile))

  def testMove(self):
    self.assertEqual(hdfs.move(self.userHDFSfileCopy, self.userHDFSsubDirFile), 0)
    self.assertEqual(hdfs.move(self.userHomeFileCopy, self.userHomeSubDirFile), 0)
    self.assertEqual(hdfs.move(self.userHDFSfileCopy2, self.userHomeSubDirFile), 0)
    self.assertEqual(hdfs.move(self.userHomeFileCopy2, self.userHDFSsubDirFile), 0)
    self.assertEqual(hdfs.move(self.userHDFSsubDir2, self.userHDFSsubDir), 0)
    self.assertEqual(hdfs.move(self.userHomeSubDir2, self.userHomeSubDir), 0)
    self.assertEqual(hdfs.move(self.userHDFSsubDir3, self.userHomeSubDir), 0)
    self.assertEqual(hdfs.move(self.userHomeSubDir3, self.userHDFSsubDir), 0)

  def testRemoveFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.remove(self.nonExistingHDFSfile))
    self.assertRaises(NoSuchPathException, lambda: hdfs.remove(self.nonExistingHomeFile))
    self.assertEqual(hdfs.remove(self.userHDFSsubDir, recursive = False), -1)
    self.assertEqual(hdfs.remove(self.userHomeSubDir, recursive = False), -1)

  def testRemove(self):
    self.assertEqual(hdfs.remove(self.userHDFSsubDir, recursive = True), 0)
    self.assertEqual(hdfs.remove(self.userHomeSubDir, recursive = True), 0)
    self.assertEqual(hdfs.remove(self.userHDFSmainDir), 0)
    self.assertEqual(hdfs.remove(self.userHomeMainDir), 0)
    self.assertEqual(hdfs.remove(self.userHDFSfile), 0)
    self.assertEqual(hdfs.remove(self.userHomeFile), 0)

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
    "testListDir",
    "testListDirFail",
    "testListDirObjects",
    "testMkdirsFail",
    "testMkdirs",
    "testChown",
    "testChownFail",
    "testChmod",
    "testChmodFail",
    "testCopy",
    "testCopyFail",
    "testMoveFail",
    "testMove",
    "testRemoveFail",
    "testRemove",
  ]
  for test in tests:
    testSuite.addTest(HDFSTestCase(test))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner(verbosity = 2)
runner.run(suite_instance)
