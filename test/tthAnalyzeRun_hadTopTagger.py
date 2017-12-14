import os, logging, sys, getpass

#from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_hadTopTagger_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_hadTopTagger_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_hadTopTagger import analyzeConfig_hadTopTagger
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

changeBranchNames = False

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

version = "2017Nov11"

##max_job_resubmission = 3
max_job_resubmission = 1

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  job_statistics_summary = {}

  run_analysis = False
  is_last_resubmission = False
  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    print "Job submission #%i:" % (idx_job_resubmission + 1)

    analysis = analyzeConfig_hadTopTagger(
      configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
      executable_analyze = "analyze_hadTopTagger", cfgFile_analyze = "analyze_hadTopTagger_cfg.py",
      samples = samples,
      changeBranchNames = changeBranchNames,
      hadTau_selection = "Tight|dR03mvaMedium",
      max_files_per_job = 3,
      era = ERA, use_lumi = True, lumi = LUMI,
      debug = False,
      running_method = "sbatch",
      num_parallel_jobs = 8)

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      print " #jobs of type '%s' = %i" % (job_type, num_jobs)
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
      run_analysis = query_yes_no("Start jobs ?")
      #run_analysis = True
    if run_analysis:
      analysis.run()
    else:
      sys.exit(0)

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    print "Job submission #%i:" % (idx_job_resubmission + 1)
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      print " #jobs of type '%s' = %i" % (job_type, num_jobs)

