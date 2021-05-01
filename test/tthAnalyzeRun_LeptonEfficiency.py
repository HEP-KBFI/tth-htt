#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonEfficiency import analyzeConfig_LeptonEfficiency
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples_aux as load_samples, load_samples_stitched

import os
import sys
import getpass
import re

# E.g: ./tthAnalyzeRun_LeptonEfficiency.py -v $VERSION -e $ERA -L hh_multilepton -LeptonType mu -L_useTightChargeCut True

cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_10_2_13') # immediate parent dir to src folder (w/o Siddesh's charge flip code)
cmssw_base_dir_combine = os.path.expanduser('~/VHbbNtuples_10_x/CMSSW_10_2_13') if 'ssawant' in cmssw_base_dir_combine else cmssw_base_dir_combine

parser = tthAnalyzeParser()


parser.add_lep_mva_wp() # TAKEN FROM  LFR CODE
parser.add_lep_useTightChargeCut(default_option = 'False')
parser.add_preselect() 
parser.add_files_per_job()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
parser.add_stitched([ 'dy_lo', 'wjets' ])

parser.add_argument('-LeptonType', '--lepton_type',
  type = str, dest = 'lepton_type_string', metavar = 'handle to change lepton flavor in the Lepton ID Efficiency code',
  choices = ['e', 'mu'], default = 'e',
  help = 'R|Flag to change lepton flavor in the Lepton ID Efficiency code',
)

args_tmp = parser.parse_args()

if (args_tmp.lepton_type_string == 'e'):
    lepID_systs = systematics.an_chargeFlip_e_opts
    systematics.full = systematics.an_chargeFlip_e
elif (args_tmp.lepton_type_string == 'mu'):
    lepID_systs = systematics.an_chargeFlip_mu_opts
    systematics.full = systematics.an_chargeFlip_mu
else:
    raise ValueError('Invalid Lepton Type provided: %s' % lepton_type_string)       

sys_choices      = [ 'full' ] + lepID_systs

parser.add_sys(sys_choices, default_choice = 'full')

args = parser.parse_args()


# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
systematics_label = args.systematics
lep_mva_wp        = args.lep_mva_wp
lep_useTightChargeCut   = args.lep_useTightChargeCut
files_per_job     = args.files_per_job
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching
use_stitched      = args.use_stitched
lepton_type_string = args.lepton_type_string


# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

preselection_suffix = ""
samples = load_samples(era, suffix = preselection_suffix)
samples = load_samples_stitched(samples, era, use_stitched)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events':
    continue
  if sample_info["use_it"] == False:
    continue
  if sample_info["type"] == "mc":
      if lepton_type_string == 'e':
          sample_info["triggers"] = [ "1e"]
      elif lepton_type_string == 'mu':
          sample_info["triggers"] = [ "1mu"]
      else:    
          raise ValueError('Invalid Lepton Type provided: %s' % lepton_type_string)       
  if re.match("/DY(\d)?Jets", sample_name) or sample_info["process_name_specific"].startswith("DYToLL"):
    sample_info["sample_category"] = "DY"
  elif sample_info["process_name_specific"].startswith(("TTTo", "TTJets")):
    sample_info["sample_category"] = "TTbar"
  elif re.match("/W(\d)?Jets", sample_name):
    sample_info["sample_category"] = "WJets"
  elif sample_info["process_name_specific"].startswith("ST_"):
    sample_info["sample_category"] = "Singletop"
  elif sample_info["process_name_specific"].startswith(("WWTo", "WZTo", "ZZTo")):
    sample_info["sample_category"] = "Diboson"
  elif sample_info["sample_category"] == "data_obs":
      ## Restricting ourselves to /SingleElectron (2016,2017), /EGamma (2018), /SingleMuon (2016,2017,2018)     
      if lepton_type_string == 'e':
          sample_info["use_it"] = ("SingleElectron" in sample_name or "EGamma" in sample_name)
      elif lepton_type_string == 'mu':
          sample_info["use_it"] = ("SingleMuon" in sample_name)
      else:    
          raise ValueError('Invalid Lepton Type provided: %s' % lepton_type_string)       
  else:
      sample_info["use_it"] = False

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)




  if (lepton_type_string == 'e'):
        numerator_histogram_labels    = ("m_ll", "m_{ee}")
        denominator_histogram_labels  = ("m_ll", "m_{ee}")
  elif(lepton_type_string == 'mu'): 
      numerator_histogram_labels    = ("m_ll", "m_{#mu#mu}")
      denominator_histogram_labels  = ("m_ll", "m_{#mu#mu}")
  else:
      raise ValueError('Invalid Lepton Type provided: %s' % lepton_type_string)       


  analysis = analyzeConfig_LeptonEfficiency(  
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    cmssw_base_dir_combine      = cmssw_base_dir_combine,
    executable_analyze          = "analyze_LeptonEfficiency",
    samples                     = samples,
    absEtaBins_e = [ 0., 0.9, 1.2, 2.1, 2.5 ], 
    absEtaBins_mu = [ 0., 0.9, 1.2, 2.1, 2.5 ], 
    ptBins_e = [ 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120. ], 
    ptBins_mu = [ 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120. ],
    lepton_type_string          = lepton_type_string, ## Options are e/mu  
    lep_mva_wp                  = lep_mva_wp,
    lep_useTightChargeCut       = lep_useTightChargeCut,
    lepton_selection_string     = "Tight", 
    fillGenEvtHistograms        = False, 
    jet_cleaning_by_index       = jet_cleaning_by_index,
    gen_matching_by_index       = gen_matching_by_index,
    central_or_shifts           = central_or_shifts,  
    max_files_per_job           = files_per_job,
    era                         = era,
    use_lumi                    = True,
    lumi                        = lumi,
    check_output_files          = check_output_files,
    running_method              = running_method,  
    num_parallel_jobs           = num_parallel_jobs,
    numerator_histogram         = numerator_histogram_labels,
    denominator_histogram       = denominator_histogram_labels,
    prep_dcard                  = True,  
    executable_prep_dcard       = "prepareDatacards",
    executable_comp_LeptonEfficiency = "comp_LeptonEfficiency",  
    select_rle_output           = True,
    dry_run                     = dry_run,
    isDebug                     = debug,
    use_home                    = use_home,
    submission_cmd              = sys.argv,  
  )

  job_statistics = analysis.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

  if auto_exec:
    run_analysis = True
  elif no_exec:
    run_analysis = False
  else:
    run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
