import os, logging, sys, getpass

#from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_hadTopTagger_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_hadTopTagger_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.analyzeConfig_hadTopTagger import analyzeConfig_hadTopTagger
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI =  2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2017Jul07"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_hadTopTagger(
    configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze = "analyze_hadTopTagger", cfgFile_analyze = "analyze_hadTopTagger_cfg.py",
    samples = samples,
    hadTau_selection = "Tight|dR03mvaMedium",
    max_files_per_job = 100,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 8)

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  ##run_analysis = True
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

