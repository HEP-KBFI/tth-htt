import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
  fileNames = cms.vstring(''),
  maxEvents = cms.int32(-1),
  outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
  fileName = cms.string('analyze_1l_2tau.root')
)

process.analyze_1l_2tau = cms.PSet(
  treeName = cms.string('Events'),

  process = cms.string('ttH'),

  histogramDir = cms.string('1l_2tau_OS_Tight'),

  era = cms.string('2017'),

  triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
  use_triggers_1e = cms.bool(True),
  triggers_1e1tau = cms.vstring(),
  use_triggers_1e1tau = cms.bool(False),
  triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
  use_triggers_1mu = cms.bool(True),
  triggers_1mu1tau = cms.vstring(),
  use_triggers_1mu1tau = cms.bool(False),

  apply_offline_e_trigger_cuts_1e = cms.bool(True),
  apply_offline_e_trigger_cuts_1e1tau = cms.bool(True),
  apply_offline_e_trigger_cuts_1mu = cms.bool(True),
  apply_offline_e_trigger_cuts_1mu1tau = cms.bool(True),

  leptonSelection = cms.string('Tight'),
  apply_leptonGenMatching = cms.bool(False),
  apply_leptonGenMatching_ttZ_workaround = cms.bool(False),

  hadTauSelection = cms.string('Tight|dR03mvaTight'),
  hadTauChargeSelection = cms.string('OS'),
  apply_hadTauGenMatching = cms.bool(False),

  applyFakeRateWeights = cms.string("disabled"), # either "disabled", "3L" or "2tau"
  leptonFakeRateWeight = cms.PSet(
  inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_lep_ttH_mva_2016_data.root"),
  histogramName_e = cms.string("FR_mva075_el_data_comb"),
  histogramName_mu = cms.string("FR_mva075_mu_data_comb")
  ),
  hadTauFakeRateWeight = cms.PSet(
  inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
  lead = cms.PSet(
  absEtaBins = cms.vdouble(-1., 1.479, 9.9),
  graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
  applyGraph = cms.bool(True),
  fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
  applyFitFunction = cms.bool(True)
  ),
  sublead = cms.PSet(
  absEtaBins = cms.vdouble(-1., 1.479, 9.9),
  graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
  applyGraph = cms.bool(True),
  fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
  applyFitFunction = cms.bool(True)
  )
  ),

  use_HIP_mitigation_mediumMuonId = cms.bool(False),

  isMC = cms.bool(False),
  central_or_shift = cms.string('central'),
  lumiScale = cms.double(1.),
  apply_genWeight = cms.bool(True),
  apply_trigger_bits = cms.bool(True),
  apply_hadTauFakeRateSF = cms.bool(False),
  isBDTtraining = cms.bool(False),

  fillGenEvtHistograms = cms.bool(False),

  branchName_electrons = cms.string('Electron'),
  branchName_muons = cms.string('Muon'),
  branchName_hadTaus = cms.string('Tau'),
  branchName_jets = cms.string('Jet'),
  branchName_met = cms.string('MET'),

  branchName_genLeptons1 = cms.string('GenLep'),
  branchName_genLeptons2 = cms.string(''),
  branchName_genHadTaus = cms.string('GenVisTau'),
  branchName_genJets = cms.string('GenJet'),
  redoGenMatching = cms.bool(True),

  branchName_genTopQuarks = cms.string('GenTop'),
  branchName_genBJets = cms.string('GenBQuarkFromTop'),
  branchName_genWBosons = cms.string('GenVbosons'),
  branchName_genWJets = cms.string('GenWZQuark'),

  selEventsFileName_input = cms.string(''),
  selEventsFileName_output = cms.string(''),
  selectBDT = cms.bool(False),
)
