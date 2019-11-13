#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager, sbatchManagerRuntimeError
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import os
import unittest
import shutil
import uuid

'''Tests sbatchManager submission and failure detection with single jobs

The aim of this test is to verify that sbatchManager works with minimal working units (read: that it works at all).

The test cases are:
1) 1 jobs which should finish successfully
2) 1 job which should fail, thus propagating the errors up to sbatchManager
Since we expect a job to fail in case 2), the test can only pass if the sbatchManager instance throws an error of type
sbatchManagerRuntimeError.

In order to run the test, navigate to the directory where this file resides and execute it:

$ ./sbatch_test.py

If you see the following message

> Ran 2 tests in ...s
>
> OK

then the tests passed.
'''

# use a directory which is universally available by cluster nodes and able to support writing in append mode, i.e. /home
testDir = os.path.expanduser('~/test_sbatch')

class SbatchTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(SbatchTestCase, self).__init__(*args, **kwargs)
    self.manager        = None
    self.queue          = 'short'
    self.poll_interval  = 1
    self.pool_id        = uuid.uuid4()
    self.verbose        = True
    self.log_completion = True
    self.workingDir     = os.getcwd()
    self.testArguments = {
      'positive' : {
        'name' : 'dummy_positive',
        'cmd'  : 'python -c "print 123"',
      },
      'negative' : {
        'name' : 'dummy_negative',
        'cmd'  : 'python -c raise "ValueError(\'123\')"',
      },
    }

  def setUp(self):
    self.manager = sbatchManager(pool_id = self.pool_id, verbose = self.verbose)
    self.manager.setWorkingDir(self.workingDir)
    self.manager.setLogFileDir(testDir)
    self.manager.queue          = self.queue
    self.manager.poll_interval  = self.poll_interval
    self.manager.log_completion = self.log_completion

  def tearDown(self):
    del self.manager

  def testPositive(self):
    testArgs = self.testArguments['positive']
    self.manager.submitJob(
      inputFiles             = [],
      executable             = testArgs['cmd'],
      command_line_parameter = "",
      outputFilePath         = "",
      outputFiles            = [],
      scriptFile             = os.path.join(testDir, '{}.sh'.format(testArgs['name'])),
    )
    try:
      # true positive
      self.manager.waitForJobs()
    except:
      # false negative
      self.fail("self.manager.waitForJobs() raised unexpectedly")

  def testNegative(self):
    testArgs = self.testArguments['negative']
    self.manager.submitJob(
      inputFiles             = [],
      executable             = testArgs['cmd'],
      command_line_parameter = "",
      outputFilePath         = "",
      outputFiles            = [],
      scriptFile             = os.path.join(testDir, '{}.sh'.format(testArgs['name'])),
    )
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerRuntimeError, self.manager.waitForJobs)

def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(SbatchTestCase))
  return testSuite

if not hdfs.isdir(testDir):
  hdfs.mkdirs(testDir)

suite_instance = suite()
runner = unittest.TextTestRunner()
runner.run(suite_instance)

if hdfs.isdir(testDir):
  shutil.rmtree(testDir)
