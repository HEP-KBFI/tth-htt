#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager, sbatchManagerRuntimeError
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists

import os
import unittest
import shutil
import uuid

'''Tests sbatchManager submission and failure detection with a set of jobs

The aim of this test is to verify that sbatchManager can handle a set of jobs submitted from its instance.

The test cases are:
1) 100 jobs which should finish successfully
2) 99 jobs which should finish successfully + 1 job which should fail, thus propagating the errors up to sbatchManager
Since we expect a job to fail in case 2), the test can only pass if the sbatchManager instance throws an error of type
sbatchManagerRuntimeError.

In order to run the test, navigate to the directory where this file resides and execute it:

$ ./sbatch_bulk_test.py

If you see the following message

> Ran 2 tests in ...s
>
> OK

then the tests passed.
'''

# use a directory which is universally available by cluster nodes and able to support writing in append mode, i.e. /home
testDir = os.path.expanduser('~/test_bulk_sbatch')

class SbatchBulkTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(SbatchBulkTestCase, self).__init__(*args, **kwargs)
    self.manager        = None
    self.queue          = 'short'
    self.poll_interval  = 1
    self.pool_id        = uuid.uuid4()
    self.verbose        = True
    self.log_completion = True
    self.workingDir     = os.getcwd()
    self.nof_jobs       = 100
    self.max_nof_greps  = 2
    self.testArguments = {
      'positive': {
        'name': 'dummy_positive_%d',
        'cmd': 'python -c "print 123"',
      },
      'negative': {
        'name': 'dummy_negative_%d',
        'cmd': 'python -c raise "ValueError(\'123\')"',
      },
    }

  def setUp(self):
    self.manager = sbatchManager(pool_id = self.pool_id, verbose = self.verbose, max_num_submittedJobs = 50)
    self.manager.setWorkingDir(self.workingDir)
    self.manager.setLogFileDir(testDir)
    self.manager.queue          = self.queue
    self.manager.poll_interval  = self.poll_interval
    self.manager.log_completion = self.log_completion
    self.manager.max_nof_greps  = self.max_nof_greps

  def tearDown(self):
    del self.manager

  def testPositive(self):
    testArgs = self.testArguments['positive']
    for i in range(1, self.nof_jobs + 1):
      self.manager.submitJob(
        inputFiles             = [],
        executable             = testArgs['cmd'],
        command_line_parameter = "",
        outputFilePath         = "",
        outputFiles            = [],
        scriptFile             = os.path.join(testDir, testArgs['name'] % i + ".sh"),
      )
    try:
      # true positive
      self.manager.waitForJobs()
    except:
      # false negative
      self.fail("self.manager.waitForJobs() raise unexpectedly")

  def testNegative(self):
    testArgs = self.testArguments['positive']
    for i in range(1, self.nof_jobs):
      self.manager.submitJob(
        inputFiles             = [],
        executable             = testArgs['cmd'],
        command_line_parameter = "",
        outputFilePath         = "",
        outputFiles            = [],
        scriptFile             = os.path.join(testDir, testArgs['name'] % i + ".sh"),
      )
      #self.manager.submit_job_version2(testArgs['name'] % i, testArgs['cmd'], testDir)
    # fail the last job
    testArgs = self.testArguments['negative']
    self.manager.submitJob(
      inputFiles             = [],
      executable             = testArgs['cmd'],
      command_line_parameter = "",
      outputFilePath         = "",
      outputFiles            = [],
      scriptFile             = os.path.join(testDir, testArgs['name'] % self.nof_jobs + ".sh"),
    )
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerRuntimeError, self.manager.waitForJobs)

def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(SbatchBulkTestCase))
  return testSuite

create_if_not_exists(testDir)

suite_instance = suite()
runner = unittest.TextTestRunner()
runner.run(suite_instance)

if os.path.isdir(testDir):
  shutil.rmtree(testDir)
