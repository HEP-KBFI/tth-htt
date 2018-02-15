#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_WZctrl import analyzeConfig_WZctrl
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

# E.g.: ./tthAnalyzeRun_WZctrl.py -v 2017Dec13 -e 2017

#TODO: needs actual Ntuples

era_choices                = ['2017']
default_resubmission_limit = 4

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
)
parser.add_argument('-v', '--version',
  type = str, dest = 'version', metavar = 'version', default = None, required = True,
  help = 'R|Analysis version (e.g. %s)' % datetime.date.today().strftime('%Y%b%d'),
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', choices = era_choices, default = None, required = True,
  help = 'R|Era of data/MC (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, era_choices)),
)
parser.add_argument('-d', '--dry-run',
  dest = 'dry_run', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs, just generate the necessary shell scripts'
)
parser.add_argument('-r', '--resubmission-limit',
  type = int, dest = 'resubmission_limit', metavar = 'number', default = default_resubmission_limit,
  required = False,
  help = 'R|Maximum number of resubmissions (default: %i)' % default_resubmission_limit
)
parser.add_argument('-R', '--disable-resubmission',
  dest = 'disable_resubmission', action = 'store_false', default = True,
  help = 'R|Disable resubmission (overwrites option -r/--resubmission-limit)'
)
parser.add_argument('-V', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Increase verbosity level in sbatchManager'
)
args = parser.parse_args()

era                  = args.era
version              = args.version
resubmit             = args.disable_resubmission
max_job_resubmission = args.resubmission_limit if resubmit else 1

if era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  max_files_per_job = 100
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s !!" % era)

for sample_name, sample_info in samples.items():
  if sample_info["process_name_specific"] == "WZTo3LNu":
    sample_info["sample_category"] = "WZ"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_WZctrl(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze = "analyze_WZctrl",
      cfgFile_analyze    = "analyze_WZctrl_cfg.py",
      samples            = samples,
      hadTau_selection   = "dR03mvaLoose",
      central_or_shifts  = [
        "central",
##        "CMS_ttHl_JESUp",
##        "CMS_ttHl_JESDown",
##        "CMS_ttHl_thu_shape_ttH_x1Up",
##        "CMS_ttHl_thu_shape_ttH_x1Down",
##        "CMS_ttHl_thu_shape_ttH_y1Up",
##        "CMS_ttHl_thu_shape_ttH_y1Down",
##        "CMS_ttHl_thu_shape_ttW_x1Up",
##        "CMS_ttHl_thu_shape_ttW_x1Down",
##        "CMS_ttHl_thu_shape_ttW_y1Up",
##        "CMS_ttHl_thu_shape_ttW_y1Down",
##        "CMS_ttHl_thu_shape_ttZ_x1Up",
##        "CMS_ttHl_thu_shape_ttZ_x1Down",
##        "CMS_ttHl_thu_shape_ttZ_y1Up",
##        "CMS_ttHl_thu_shape_ttZ_y1Down",
      ],
      max_files_per_job = max_files_per_job,
      era               = era,
      use_lumi          = True,
      lumi              = lumi,
      debug             = False,
      running_method    = "sbatch",
      num_parallel_jobs = 8,
      histograms_to_fit = [
        "EventCounter",
        "numJets",
        "mLL",
        "mT",
      ],
      select_rle_output = True,
      verbose           = idx_job_resubmission > 0,
      dry_run           = args.dry_run,
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
