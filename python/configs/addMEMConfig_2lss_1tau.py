import os

from tthAnalysis.HiggsToTauTau.configs.addMEMConfig import *
from tthAnalysis.HiggsToTauTau.analysisTools import create_cfg

class addMEMConfig_2lss_1tau(addMEMConfig):

  def __init__(self,
        treeName,
        outputDir,
        cfgDir,
        executable_addMEM,
        samples,
        era,
        debug,
        leptonSelection,
        hadTauSelection,
        running_method,
        max_files_per_job,
        mem_integrations_per_job,
        max_mem_integrations,
        num_parallel_jobs,
        lowIntegrationPoints,
        isDebug,
        central_or_shift,
        dry_run,
        use_nonnominal,
        use_home,
        pool_id = '',
      ):
    addMEMConfig.__init__(self,
      treeName                 = treeName,
      outputDir                = outputDir,
      cfgDir                   = cfgDir,
      executable_addMEM        = executable_addMEM,
      samples                  = samples,
      era                      = era,
      debug                    = debug,
      running_method           = running_method,
      max_files_per_job        = max_files_per_job,
      mem_integrations_per_job = mem_integrations_per_job,
      max_mem_integrations     = max_mem_integrations,
      num_parallel_jobs        = num_parallel_jobs,
      leptonSelection          = leptonSelection,
      hadTauSelection          = hadTauSelection,
      lowIntegrationPoints     = lowIntegrationPoints,
      dry_run                  = dry_run,
      use_nonnominal           = use_nonnominal,
      use_home                 = use_home,
      channel                  = "2lss_1tau",
      pool_id                  = pool_id,
    )

    self.cfgFile_addMEM_original = os.path.join(self.template_dir, "addMEM_2lss_1tau_cfg.py")
    self.isDebug = isDebug
    self.central_or_shift = central_or_shift

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
    lines.append("process.addMEM_2lss_1tau.lowIntegrationPoints = cms.bool(%s)" % self.lowIntegrationPoints)
    lines.append("process.addMEM_2lss_1tau.isDEBUG = cms.bool(%s)" % self.isDebug)
    lines.append("process.addMEM_2lss_1tau.central_or_shift = cms.vstring(%s)" % self.central_or_shift)
    lines.append("process.addMEM_2lss_1tau.dryRun = cms.bool(%s)" % self.dry_run)
    lines.append("process.addMEM_2lss_1tau.use_nonnominal = cms.bool(%s)" % self.use_nonnominal)

    create_cfg(self.cfgFile_addMEM_original, cfgFile_modified, lines)
