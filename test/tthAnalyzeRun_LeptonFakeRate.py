#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

# E.g.: ./tthAnalyzeRun_LeptonFakeRate.py -v 2017Dec13 -e 2017

#TODO: needs actual Ntuples
#TODO: needs an updated value of integrated luminosity for 2017 data

cmssw_base_dir_combine     = os.path.expanduser('~/CMSSW_7_4_7') # immediate parent dir to src folder
era_choices                = ['2017']
default_resubmission_limit = 4
max_files_per_job          = 100

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
parser.add_argument('-n', '--max-files-per-job',
  type = int, dest = 'max_files_per_job', metavar = 'integer', default = max_files_per_job, required = False,
  help = 'R|Maximum number of input files per one job (default: %i)' % max_files_per_job
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
max_files_per_job    = args.max_files_per_job

if era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_jetToTauFRorLeptonFR import samples_2017 as samples
  lumi = 35.9e+3 # 1/pb
  # TODO: update lumi
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s !!" % era)

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

    analysis = analyzeConfig_LeptonFakeRate(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      cmssw_base_dir_combine = cmssw_base_dir_combine,
      executable_analyze     = "analyze_LeptonFakeRate",
      samples                = samples,
      absEtaBins_e           = [ 0., 1.479, 9.9 ],
      absEtaBins_mu          = [ 0., 1.479, 9.9 ],
      absPtBins_e            = [ 15., 20., 30., 45., 65., 100000. ],
      absPtBins_mu           = [ 10., 15., 20., 30., 45., 65., 100000. ],
      fillGenEvtHistograms   = False,
      central_or_shifts      = [
        "central",
        "CMS_ttHl_JESUp",
        "CMS_ttHl_JESDown",
        "CMS_ttHl_JERUp",
        "CMS_ttHl_JERDown",
        "CMS_ttHl_UnclusteredEnUp",
        "CMS_ttHl_UnclusteredEnDown",
  ##       "CMS_ttHl_btag_HFUp",
  ##       "CMS_ttHl_btag_HFDown",
  ##       "CMS_ttHl_btag_HFStats1Up",
  ##       "CMS_ttHl_btag_HFStats1Down",
  ##       "CMS_ttHl_btag_HFStats2Up",
  ##       "CMS_ttHl_btag_HFStats2Down",
  ##       "CMS_ttHl_btag_LFUp",
  ##       "CMS_ttHl_btag_LFDown",
  ##       "CMS_ttHl_btag_LFStats1Up",
  ##       "CMS_ttHl_btag_LFStats1Down",
  ##       "CMS_ttHl_btag_LFStats2Up",
  ##       "CMS_ttHl_btag_LFStats2Down",
  ##       "CMS_ttHl_btag_cErr1Up",
  ##       "CMS_ttHl_btag_cErr1Down",
  ##       "CMS_ttHl_btag_cErr2Up",
  ##       "CMS_ttHl_btag_cErr2Down",
  ##       "CMS_ttHl_JESUp",
  ##       "CMS_ttHl_JESDown",
  ##       "CMS_ttHl_tauESUp",
  ##       "CMS_ttHl_tauESDown",
  ##       "CMS_ttHl_FRet_shiftUp",
  ##       "CMS_ttHl_FRet_shiftDown",
  ##       "CMS_ttHl_FRmt_shiftUp",
  ##       "CMS_ttHl_FRmt_shiftDown",
  ##       "CMS_ttHl_thu_shape_ttH_x1Up",
  ##       "CMS_ttHl_thu_shape_ttH_x1Down",
  ##       "CMS_ttHl_thu_shape_ttH_y1Up",
  ##       "CMS_ttHl_thu_shape_ttH_y1Down",
  ##       "CMS_ttHl_thu_shape_ttW_x1Up",
  ##       "CMS_ttHl_thu_shape_ttW_x1Down",
  ##       "CMS_ttHl_thu_shape_ttW_y1Up",
  ##       "CMS_ttHl_thu_shape_ttW_y1Down",
  ##       "CMS_ttHl_thu_shape_ttZ_x1Up",
  ##       "CMS_ttHl_thu_shape_ttZ_x1Down",
  ##       "CMS_ttHl_thu_shape_ttZ_y1Up",
  ##       "CMS_ttHl_thu_shape_ttZ_y1Down",
      ],
      numerator_histogram                      = ("mT_fix_L",     "m_{T}^{fix}"), # or ("pt", "p_{T}"),
      denominator_histogram                    = ("EventCounter", "Number of events"),
      prep_dcard                               = True,
      max_files_per_job                        = 100,
      era                                      = era,
      use_lumi                                 = True,
      lumi                                     = lumi,
      debug                                    = False,
      running_method                           = "sbatch",
      executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
      executable_prep_dcard                    = "prepareDatacards",
      executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
      num_parallel_jobs                        = 8,
      verbose                                  = idx_job_resubmission > 0,
      dry_run                                  = args.dry_run,
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
