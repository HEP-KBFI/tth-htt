#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.sbatchManager_v2 import sbatchManager, sbatchManagerError
import os, unittest, shutil, uuid

testDir = os.path.expanduser('~/test_sbatch')
if os.path.isdir(testDir):
  raise ValueError("Directory '%s' already exists; pick another" % testDir)

class SbatchTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(SbatchTestCase, self).__init__(*args, **kwargs)
    self.manager        = None
    self.queue          = 'prio'
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
        'cmd'  : 'python -c raise "ValueError(\"123\")"',
      },
    }

  def setUp(self):
    self.manager = sbatchManager(pool_id = self.pool_id, verbose = self.verbose)
    self.manager.setWorkingDir(self.workingDir)
    self.manager.queue          = self.queue
    self.manager.poll_interval  = self.poll_interval
    self.manager.log_completion = self.log_completion

  def tearDown(self):
    del self.manager

  def testPositive(self):
    testArgs = self.testArguments['positive']
    self.manager.submit_job_version2(testArgs['name'], testArgs['cmd'], testDir)
    try:
      # true positive
      self.manager.waitForJobs()
    except:
      # false negative
      self.fail("self.manager.waitForJobs() raise unexpectedly")

  def testNegative(self):
    testArgs = self.testArguments['negative']
    self.manager.submit_job_version2(testArgs['name'], testArgs['cmd'], testDir)
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerError, self.manager.waitForJobs)

def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(SbatchTestCase))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner()
runner.run(suite_instance)

if os.path.isdir(testDir):
  shutil.rmtree(testDir)
