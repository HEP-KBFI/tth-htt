import os

from tthAnalysis.HiggsToTauTau.prodNtupleConfig import *
from tthAnalysis.HiggsToTauTau.analysisTools import create_cfg

class prodNtupleConfig_2lss_1tau(prodNtupleConfig):
    """Configuration metadata needed to run Ntuple production for 2lss_1tau channel.

    Args:
        outputDir: The root output dir -- all configuration, log and output files are stored in its subdirectories
        executable_prodNtuple: Name of the executable that runs the Ntuple production; expected value is `prodNtuple_2lss_1tau`
        debug: if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method: either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs: number of jobs that can be run in parallel on local machine (does not limit number of Ntuple production jobs running in parallel on batch system)
  
    """
    def __init__(self, outputDir, executable_prodNtuple, samples,
                 era, debug, running_method, num_parallel_jobs):
        prodNtupleConfig.__init__(self, outputDir, executable_prodNtuple, "2lss_1tau", samples,
          era, debug, running_method, num_parallel_jobs)

        self.cfgFile_prodNtuple_original = os.path.join(self.workingDir, "produceNtuple_2lss_1tau_cfg.py")
               
    def createCfg_prodNtuple(self, inputFiles, outputFile, era, cfgFile_modified):
        """Create python configuration file for the produceNtuple_2lss_1tau executable (Ntuple production code)

        Args:
          inputFiles: list of input files (Ntuples)
          outputFile: output file of the job -- a ROOT file containing histogram
        """  
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
        lines.append("process.produceNtuple_2lss_1tau.era = cms.string('%s')" % era)
        create_cfg(self.cfgFile_prodNtuple_original, cfgFile_modified, lines)

