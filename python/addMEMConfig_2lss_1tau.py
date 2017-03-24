import os

from tthAnalysis.HiggsToTauTau.addMEMConfig import *
from tthAnalysis.HiggsToTauTau.analysisTools import create_cfg

class addMEMConfig_2lss_1tau(addMEMConfig):

  def __init__(self, treeName, outputDir, cfgDir, executable_addMEM, samples, era, debug, leptonSelection, hadTauSelection,
               running_method, max_files_per_job, mem_integrations_per_job, max_mem_integrations, num_parallel_jobs,
               isForBDTtraining, pool_id):
    addMEMConfig.__init__(self, treeName, outputDir, cfgDir, executable_addMEM, samples, era, debug, running_method,
                          max_files_per_job, mem_integrations_per_job, max_mem_integrations, num_parallel_jobs,
                          leptonSelection, hadTauSelection, isForBDTtraining, pool_id, "2lss_1tau",
                          "maxPermutations_addMEM_2lss_1tau")

    self.cfgFile_addMEM_original = os.path.join(self.workingDir, "addMEM_2lss_1tau_cfg.py")

  def createCfg_addMEM(self, inputFiles, startRange, endRange, outputFile, era, isMC, cfgFile_modified):
    """Create python configuration file for the addMEM_2lss_1tau executable (MEM code)

    Args:
      inputFile: list of input files (Ntuples)
      outputFile: output file of the job
    """

    '''Let's assume that the following configuration options remain constant at all times and need not be modified
    - process.fwliteInput.outputEvery
    - process.addMEM_2lss_1tau.branchName_electrons
    - process.addMEM_2lss_1tau.branchName_muons
    - process.addMEM_2lss_1tau.branchName_hadTaus
    - process.addMEM_2lss_1tau.branchName_jets
    - process.addMEM_2lss_1tau.branchName_met
    - process.addMEM_2lss_1tau.use_HIP_mitigation_bTag
    '''

    lines = []
    skipEvents = startRange
    maxEvents = endRange - startRange
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteInput.skipEvents = cms.uint32(%s)" % skipEvents)
    lines.append("process.fwliteInput.maxEvents = cms.int32(%s)" % maxEvents)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
    lines.append("process.addMEM_2lss_1tau.era = cms.string('%s')" % era)
    if skipEvents > 0:
      lines.append("process.addMEM_2lss_1tau.copy_histograms = cms.vstring()")
    lines.append("process.addMEM_2lss_1tau.leptonSelection = cms.string('%s')" % self.leptonSelection)
    lines.append("process.addMEM_2lss_1tau.hadTauSelection = cms.string('%s')" % self.hadTauSelection)
    lines.append("process.addMEM_2lss_1tau.isMC = cms.bool(%s)" % isMC)
    lines.append("process.addMEM_2lss_1tau.isForBDTtraining = cms.bool(%s)" % self.isForBDTtraining)

    create_cfg(self.cfgFile_addMEM_original, cfgFile_modified, lines)
