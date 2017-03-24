#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.sbatchManager_v2 import sbatchManager, \
  sbatchManagerTimeoutError, sbatchManagerMemoryError, sbatchManagerSyntaxError
import os, unittest, shutil, uuid

# use a directory which is universally available by cluster nodes, i.e. either /home or /hdfs
testDir = os.path.expanduser('~/test_status_sbatch')
if os.path.isdir(testDir):
  raise ValueError("Directory '%s' already exists; pick another" % testDir)

class SbatchStatusTestCase(unittest.TestCase):

  def __init__(self, *args, **kwargs):
    super(SbatchStatusTestCase, self).__init__(*args, **kwargs)
    self.manager        = None
    self.queue          = 'prio'
    self.pool_id        = uuid.uuid4()
    self.verbose        = True
    self.log_completion = True
    self.workingDir     = os.getcwd()

  def setUp(self):
    self.manager = sbatchManager(pool_id = self.pool_id, verbose = self.verbose)
    self.manager.setWorkingDir(self.workingDir)
    self.manager.queue = self.queue

    self.manager.log_completion = self.log_completion

  def tearDown(self):
    del self.manager

  def testMemory(self):
    cmd = 'python -c "`echo -e "a = []\\nwhile True:\\n\\ta.append(' ' * 1024 * 1024)"`"'
    self.manager.sbatchArgs = '--mem=2M'
    self.manager.poll_interval = 1
    self.manager.submit_job_version2('dummy_memory', cmd, testDir)
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerMemoryError, self.manager.waitForJobs)

  def testTimeout(self):
    cmd = 'python -c "import time; time.sleep(900)"'
    self.manager.sbatchArgs = '--time=1'
    self.manager.poll_interval = 5
    self.manager.submit_job_version2('dummy_timeout', cmd, testDir)
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerTimeoutError, self.manager.waitForJobs)

  def testSyntax(self):
    cmd = 'echo "missing quote'
    self.manager.poll_interval = 1
    self.manager.submit_job_version2('dummy_syntax', cmd, testDir)
    # if passes, true negative; otherwise true positive
    self.assertRaises(sbatchManagerSyntaxError, self.manager.waitForJobs)

def suite():
  testSuite = unittest.TestSuite()
  testSuite.addTest(unittest.makeSuite(SbatchStatusTestCase))
  return testSuite

suite_instance = suite()
runner = unittest.TextTestRunner()
runner.run(suite_instance)

if os.path.isdir(testDir):
  shutil.rmtree(testDir)
