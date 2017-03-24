#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.sbatchManager_v2 import sbatchManager, sbatchManagerRuntimeError
import os, unittest, shutil, uuid

# use a directory which is universally available by cluster nodes, i.e. either /home or /hdfs
testDir = os.path.expanduser('~/test_bulk_sbatch')
if os.path.isdir(testDir):
  raise ValueError("Directory '%s' already exists; pick another" % testDir)

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
        'cmd': 'python -c raise "ValueError(\"123\")"',
      },
    }

  def setUp(self):
    self.manager = sbatchManager(pool_id = self.pool_id, verbose = self.verbose)
    self.manager.setWorkingDir(self.workingDir)
    self.manager.queue          = self.queue
    self.manager.poll_interval  = self.poll_interval
    self.manager.log_completion = self.log_completion
    self.manager.max_nof_greps  = self.max_nof_greps

  def tearDown(self):
    del self.manager

  def testPositive(self):
    testArgs = self.testArguments['positive']
    for i in range(1, self.nof_jobs + 1):
      self.manager.submit_job_version2(testArgs['name'] % i, testArgs['cmd'], testDir)
    try:
      # true positive
      self.manager.waitForJobs()
    except:
      # false negative
      self.fail("self.manager.waitForJobs() raise unexpectedly")

  def testNegative(self):
    testArgs = self.testArguments['positive']
    for i in range(1, self.nof_jobs):
      self.manager.submit_job_version2(testArgs['name'] % i, testArgs['cmd'], testDir)
    # fail the last job
    testArgs = self.testArguments['negative']
    self.manager.submit_job_version2(testArgs['name'] % self.nof_jobs, testArgs['cmd'], testDir)
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerRuntimeError, self.manager.waitForJobs)


def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(SbatchBulkTestCase))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner()
runner.run(suite_instance)

if os.path.isdir(testDir):
  shutil.rmtree(testDir)
