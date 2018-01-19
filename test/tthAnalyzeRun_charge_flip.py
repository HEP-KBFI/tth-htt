import os, logging, sys, getpass

#from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.analyzeConfig_charge_flip import analyzeConfig_charge_flip
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

from optparse import OptionParser
parser = OptionParser()
parser.add_option("--version ", type="string", dest="version", help="Name of output repository with results\n Trees will be stored in /hdfs/local/USER/ttHAnalysis/2016/VERSION/", default='dumb')
parser.add_option("--ERA", type="string", dest="ERA", help="Era of data", default='2016')
(options, args) = parser.parse_args()

ERA                  = options.ERA #"2016"
version              = options.version #"2017Oct24"
max_job_resubmission = 3
max_files_per_job    = 100

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI    = 2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI    = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", ERA, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_charge_flip(
      configDir = configDir,
      outputDir = outputDir,
      executable_analyze = "analyze_charge_flip",
      samples = samples,
      lepton_selections = [ "Tight"],
      central_or_shifts = [ 
        "central",
        "CMS_ttHl_electronESUp",
        "CMS_ttHl_electronESDown",
        "CMS_ttHl_electronERUp", 
        "CMS_ttHl_electronERDown",
        "CMS_ttHl_electronESEndcapUp",
        "CMS_ttHl_electronESEndcapDown",
        "CMS_ttHl_electronESBarrelUp",
        "CMS_ttHl_electronESBarrelDown"
      ],
      max_files_per_job = max_files_per_job,
      era = ERA, use_lumi = True, lumi = LUMI,
      debug = False,
      running_method = "sbatch",
      num_parallel_jobs = 4,
      #sel_events_file = '',#os.path.join(os.environ["CMSSW_BASE"] , "src/tthAnalysis/HiggsToTauTau/data/eventlist_diff.txt"),
      histograms_to_fit = [ "mass_ll" ],
      select_rle_output = False
    )

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
      run_analysis = query_yes_no("Start jobs ?")
    if run_analysis:
      analysis.run()
    else:
      sys.exit(0)

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
