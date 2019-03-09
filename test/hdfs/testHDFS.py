#!/usr/bin/env python

import os.path
import getpass
import logging
import sys
import unittest

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

class HDFSTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(HDFSTestCase, self).__init__(*args, **kwargs)

  def setUp(self):
    self.userHDFSdir = os.path.join('/hdfs/local', getpass.getuser())
    self.userHomeDir = os.path.join('/home', getpass.getuser())

    self.nonExistingHDFSdir = os.path.join('/hdfs/local/thisUserDoesNotExist')
    self.nonExistingHomeDir = os.path.join('/home/thisUserDoesNotExist')

  def tearDown(self):
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

  def testIsDirException(self):
    self.assertFalse(hdfs.isdir(self.nonExistingHDFSdir))
    self.assertFalse(hdfs.isdir(self.nonExistingHomeDir))

def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(HDFSTestCase))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner(verbosity = 2)
runner.run(suite_instance)
