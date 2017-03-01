import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    ##fileNames = cms.vstring('/afs/cern.ch/user/k/kaehatah/public/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_2lss_1tau.root')
)

process.analyze_2lss_1tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    histogramDir = cms.string('2lss_1tau_SS_Tight'),

    era = cms.string('2015'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),
    
    apply_genWeight = cms.bool(True),
    
    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(False),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('dR03mvaTight'),
    apply_hadTauGenMatching = cms.bool(False),

    applyFakeRateWeights = cms.string("disabled"), # either "disabled", "3L" or "2tau"
    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_lep_ttH_mva_2015_data.root"),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb")
    ),
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2015.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        )
    ),

    use_HIP_mitigation_bTag = cms.bool(False),

    apply_lepton_and_hadTauCharge_cut = cms.bool(False),
        
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(True),

    fillGenEvtHistograms = cms.bool(False),
    
    branchName_electrons = cms.string('selLeptons'),
    branchName_muons = cms.string('selLeptons'),
    branchName_hadTaus = cms.string('TauGood'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),
    branchName_memOutput = cms.string(''),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('output/selEvents_ttHJetToNonbb_2lss_1tau_M125_Fakeable_wFakeRateWeights_SS.txt')
)

process.fwliteInput.fileNames = cms.vstring(['/home/andres/tth/sync/ttHJetToNonbb_M125_13TeV_sync_summer_v0.root'])
process.fwliteOutput.fileName = cms.string('output/ttHJetToNonbb_2lss_1tau_M125_Fakeable_wFakeRateWeights_SS.root')
process.analyze_2lss_1tau.process = cms.string('signal')
process.analyze_2lss_1tau.histogramDir = cms.string('2lss_1tau_SS_Fakeable_wFakeRateWeights')
process.analyze_2lss_1tau.era = cms.string('2016')
process.analyze_2lss_1tau.triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v'])
process.analyze_2lss_1tau.use_triggers_1e = cms.bool(True)
process.analyze_2lss_1tau.triggers_2e = cms.vstring(['HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2e = cms.bool(True)
process.analyze_2lss_1tau.triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'])
process.analyze_2lss_1tau.use_triggers_1mu = cms.bool(True)
process.analyze_2lss_1tau.triggers_2mu = cms.vstring(['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2mu = cms.bool(True)
process.analyze_2lss_1tau.triggers_1e1mu = cms.vstring(['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'])
process.analyze_2lss_1tau.use_triggers_1e1mu = cms.bool(True)
process.analyze_2lss_1tau.leptonSelection = cms.string('Fakeable')
process.analyze_2lss_1tau.apply_leptonGenMatching = cms.bool(True)
process.analyze_2lss_1tau.leptonChargeSelection = cms.string('SS')
process.analyze_2lss_1tau.hadTauSelection = cms.string('Fakeable|dR03mvaMedium')
process.analyze_2lss_1tau.apply_hadTauGenMatching = cms.bool(True)
process.analyze_2lss_1tau.applyFakeRateWeights = cms.string('3L')
process.analyze_2lss_1tau.hadTauFakeRateWeight.inputFileName = cms.string('tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root')
process.analyze_2lss_1tau.hadTauFakeRateWeight.lead.fitFunctionName = cms.string('jetToTauFakeRate/dR03mvaMedium/$etaBin/fitFunction_data_div_mc_hadTaus_pt')
process.analyze_2lss_1tau.isMC = cms.bool(True)
process.analyze_2lss_1tau.central_or_shift = cms.string('central')
process.analyze_2lss_1tau.lumiScale = cms.double(0.000446)
process.analyze_2lss_1tau.apply_trigger_bits = cms.bool(False)
#process.analyze_2lss_1tau.selEventsFileName_output = cms.string('/home/veelken/ttHAnalysis/2016/2016Nov03/output_rle/2lss_1tau/Fakeable_wFakeRateWeights_SS/ttHJetToNonbb_M125/rle_2lss_1tau_ttHJetToNonbb_M125_Fakeable_wFakeRateWeights_SS_central_0.txt')
process.analyze_2lss_1tau.use_HIP_mitigation_bTag = cms.bool(True)
process.analyze_2lss_1tau.use_HIP_mitigation_mediumMuonId = cms.bool(False)
