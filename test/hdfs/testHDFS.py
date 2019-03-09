#!/usr/bin/env python

import os.path
import getpass
import logging
import sys
import unittest
import time

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
    userName = getpass.getuser()
    cls.userHDFSdir = os.path.join('/hdfs/local', userName)
    cls.userHomeDir = os.path.join('/home',       userName)

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
    with open(cls.userHomeFile, 'w') as f:
      f.write(text)

    cls.delay = 10

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
    # wait for 5 seconds so that the file would finally enter the hadoop file system
    time.sleep(self.delay)

    fileSizeHDFS = hdfs.getsize(self.userHDFSfile)
    fileSizeHome = hdfs.getsize(self.userHomeFile)
    self.assertEqual(fileSizeHDFS, self.fileSize)
    self.assertEqual(fileSizeHome, self.fileSize)

  def testFileSizeFail(self):
    self.assertRaises(NoSuchPathException, lambda: hdfs.getsize(self.nonExistingHDFSfile))
    self.assertRaises(OSError,             lambda: hdfs.getsize(self.nonExistingHomeFile))

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
  ]
  for test in tests:
    testSuite.addTest(HDFSTestCase(test))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner(verbosity = 2)
runner.run(suite_instance)
