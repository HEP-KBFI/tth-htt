#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_2lss_1tau import analyzeConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass

# E.g. to run: ./test/tthAnalyzeRun_2lss_1tau.py -v 2017Dec13 -m default -e 2017

mode_choices         = [
  'default', 'addMEM', 'forBDTtraining_beforeAddMEM', 'forBDTtraining_afterAddMEM', 'sync', 'sync_wMEM'
]
sys_choices      = [ 'full' ] + systematics.an_extended_opts
systematics.full = systematics.an_extended

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_preselect()
parser.add_rle_select()
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_hlt_filter()
parser.add_files_per_job()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
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
mode              = args.mode
systematics_label = args.systematics
use_preselected   = args.use_preselected
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
hlt_filter        = args.hlt_filter
files_per_job     = args.files_per_job
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
do_sync = mode.startswith('sync')
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

MEMbranch                = ''
lepton_charge_selections = [ "SS" ] if mode.find("forBDTtraining") != -1 else [ "OS", "SS" ]
chargeSumSelections      = [ "OS" ] if mode.find("forBDTtraining") != -1 else [ "OS", "SS" ]
hadTau_selection         = "dR03mvaLoose"

if mode == "default":
  samples = load_samples(era, suffix = "preselected" if use_preselected else "")
elif mode == "addMEM":
  samples = load_samples(era, suffix = "addMEM_preselected_2lss1tau" if use_preselected else "addMEM_2lss1tau")
  MEMbranch = 'memObjects_2lss_1tau_lepFakeable_tauTight_{}'.format(hadTau_selection)

elif mode == "forBDTtraining_beforeAddMEM":
  if use_preselected:
    raise ValueError("Makes no sense to use preselected samples w/ BDT training mode")

  samples = load_samples(era, suffix = "BDT")
  hadTau_selection         = "dR03mvaLoose"
  hadTau_selection_relaxed = "dR03mvaLoose"

elif mode == "forBDTtraining_afterAddMEM":
  if use_preselected:
    raise ValueError("Makes no sense to use preselected samples w/ BDT training mode")
  samples = load_samples(era, suffix = "BDT_addMEM_2lss1tau")
  hadTau_selection         = "dR03mvaLoose"
  hadTau_selection_relaxed = "dR03mvaLoose"
  MEMbranch                = 'memObjects_2lss_1tau_lepLoose_tauTight_{}'.format(hadTau_selection)

elif mode.startswith("sync"):
  if mode == "sync_wMEM":
    if use_preselected:
      raise ValueError("Makes no sense to use preselected samples in sync")
    samples = load_samples(era, suffix = "addMEM_sync" if use_nonnominal else "addMEM_sync_nom")
  elif mode == "sync":
    if use_preselected:
      raise ValueError("Makes no sense to use preselected samples in sync")
    samples = load_samples(era, suffix = "sync" if use_nonnominal else "sync_nom")
  else:
    raise ValueError("Invalid mode: %s" % mode)
else:
  raise ValueError("Invalid mode: %s" % mode)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events': continue
  if sample_name.startswith('/Tau/Run'):
    sample_info["use_it"] = False

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )
  if not use_preselected:
    logging.warning('Running the analysis on fully inclusive samples!')

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  if args.tau_id_wp:
    logging.info("Changing tau ID working point: %s -> %s" % (hadTau_selection, args.tau_id_wp))
    hadTau_selection = args.tau_id_wp

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version)

  analysis = analyzeConfig_2lss_1tau(
    configDir                 = configDir,
    outputDir                 = outputDir,
    executable_analyze        = "analyze_2lss_1tau",
    cfgFile_analyze           = "analyze_2lss_1tau_cfg.py",
    samples                   = samples,
    MEMbranch                 = MEMbranch,
    lepton_charge_selections  = lepton_charge_selections,
    hadTau_selection          = hadTau_selection,
    hadTau_selection_veto     = "dR03mvaMedium", # To avoid overlap w/ 2l+2tau SR
    # CV: apply "fake" background estimation to leptons only and not to hadronic taus, as discussed on slide 10 of
    #     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
    applyFakeRateWeights      = "2lepton",
    chargeSumSelections       = chargeSumSelections,
    jet_cleaning_by_index     = jet_cleaning_by_index,
    gen_matching_by_index     = gen_matching_by_index,
    central_or_shifts         = central_or_shifts,
    max_files_per_job         = files_per_job,
    era                       = era,
    use_lumi                  = True,
    lumi                      = lumi,
    check_output_files        = check_output_files,
    running_method            = running_method,
    num_parallel_jobs         = num_parallel_jobs,
    executable_addBackgrounds = "addBackgrounds",
    # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    executable_addFakes       = "addBackgroundLeptonFakes",
    executable_addFlips       = "addBackgroundLeptonFlips",
    histograms_to_fit         = {
      "EventCounter"                               : {},
      "numJets"                                    : {},
      "mvaOutput_2lss_ttV"                         : {},
      "mvaOutput_2lss_tt"                          : {},
      "mvaOutput_2lss_1tau_plainKin_tt"            : { 'quantile_rebin' : 15, 'quantile_in_fakes' : True }, # BDT2; quantile in fakes
      "mvaOutput_2lss_1tau_plainKin_ttV"           : { 'quantile_rebin' : 15, 'quantile_in_fakes' : True }, # BDT1; quantile in fakes
      "mvaOutput_2lss_1tau_plainKin_1B_M"          : {},
      "mvaOutput_2lss_1tau_plainKin_SUM_M"         : { 'quantile_rebin' : 11, 'quantile_in_fakes' : True }, # BDT3; quantile in fakes
      "mvaOutput_2lss_1tau_plainKin_SUM_M_noRebin" : {},
      "mvaOutput_2lss_1tau_HTT_SUM_M"              : { 'quantile_rebin' : 11, 'quantile_in_fakes' : True }, # BDT4; quantile in fakes
      "mvaOutput_2lss_1tau_HTT_SUM_M_noRebin"      : {},
      "mvaOutput_2lss_1tau_HTTMEM_SUM_M"           : { 'quantile_rebin' : 15, 'quantile_in_fakes' : True }, # BDT5; quantile in fakes
      "mvaOutput_2lss_1tau_HTTMEM_SUM_M_noRebin"   : {},
      "mTauTauVis1"                                : {},
      "mTauTauVis2"                                : {},
      "mTauTauVis"                                 : {},
      "memOutput_LR"                               : {},
      "mvaOutput_final"                            : {},
    },
    select_rle_output         = True,
    dry_run                   = dry_run,
    do_sync                   = do_sync,
    isDebug                   = debug,
    rle_select                = rle_select,
    use_nonnominal            = use_nonnominal,
    hlt_filter                = hlt_filter,
    use_home                  = use_home,
  )

  if mode.find("forBDTtraining") != -1:
    analysis.set_BDT_training(hadTau_selection_relaxed)

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
