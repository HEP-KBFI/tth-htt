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
    histogramDir = cms.string('2lss_1tau_lepSS_sumOS_Tight'),
    era = cms.string('2016'),

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
    
    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(True),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    apply_hadTauGenMatching = cms.bool(True),

    apply_genWeight = cms.bool(True),
    chargeSumSelection = cms.string('OS'),
    
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
        )
    ),


    use_HIP_mitigation_bTag = cms.bool(False),
    use_HIP_mitigation_mediumMuonId = cms.bool(False),

    apply_lepton_and_hadTauCharge_cut = cms.bool(True),
        
    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(False),
    apply_hadTauFakeRateSF = cms.bool(False),

    fillGenEvtHistograms = cms.bool(False),
    
    branchName_electrons = cms.string('selLeptons'),
    branchName_muons = cms.string('selLeptons'),
    branchName_hadTaus = cms.string('TauGood'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),
    branchName_memOutput = cms.string(''),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('output/selEvents_ttHJetToNonbb_2lss_1tau_M125_Tight_SS.txt'),

    selectBDT = cms.bool(False),
)

process.fwliteInput.fileNames = cms.vstring(['/home/andres/tth/sync/ttHJetToNonbb_M125_13TeV_sync_summer_v3.root'])
process.fwliteOutput.fileName = cms.string('output/ttHJetToNonbb_2lss_1tau_M125_Tight_SS.root')
process.analyze_2lss_1tau.process = cms.string('signal')
process.analyze_2lss_1tau.histogramDir = cms.string('2lss_1tau_SS_Tight')
#process.analyze_2lss_1tau.histogramDir = cms.string('2lss_1tau_lepSS_sumOS_Tight')
process.analyze_2lss_1tau.era = cms.string('2016')
process.analyze_2lss_1tau.triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPTight_Gsf_v'])
process.analyze_2lss_1tau.use_triggers_1e = cms.bool(True)
process.analyze_2lss_1tau.triggers_2e = cms.vstring(['HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2e = cms.bool(True)
process.analyze_2lss_1tau.triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v', 'HLT_BIT_HLT_IsoMu22_eta2p1_v', 'HLT_BIT_HLT_IsoTkMu22_eta2p1_v'])
process.analyze_2lss_1tau.use_triggers_1mu = cms.bool(True)
process.analyze_2lss_1tau.triggers_2mu = cms.vstring(['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2mu = cms.bool(True)
process.analyze_2lss_1tau.triggers_1e1mu = cms.vstring(['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'])
process.analyze_2lss_1tau.use_triggers_1e1mu = cms.bool(True)
process.analyze_2lss_1tau.leptonSelection = cms.string('Tight')
process.analyze_2lss_1tau.apply_leptonGenMatching = cms.bool(True)
process.analyze_2lss_1tau.leptonChargeSelection = cms.string('SS')
process.analyze_2lss_1tau.hadTauSelection = cms.string('Tight|dR03mvaMedium')
process.analyze_2lss_1tau.apply_hadTauGenMatching = cms.bool(True)
process.analyze_2lss_1tau.applyFakeRateWeights = cms.string('disabled')
process.analyze_2lss_1tau.hadTauFakeRateWeight.inputFileName = cms.string('tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root')
process.analyze_2lss_1tau.hadTauFakeRateWeight.lead.fitFunctionName = cms.string('jetToTauFakeRate/dR03mvaMedium/$etaBin/fitFunction_data_div_mc_hadTaus_pt')
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyGraph_lead = cms.bool(False)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyFitFunction_lead = cms.bool(True)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyGraph_sublead = cms.bool(False)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyFitFunction_sublead = cms.bool(True)
process.analyze_2lss_1tau.apply_hadTauFakeRateSF = cms.bool(True)
process.analyze_2lss_1tau.chargeSumSelection = cms.string('OS')
process.analyze_2lss_1tau.use_HIP_mitigation_bTag = cms.bool(True)
process.analyze_2lss_1tau.use_HIP_mitigation_mediumMuonId = cms.bool(True)
process.analyze_2lss_1tau.isMC = cms.bool(True)
process.analyze_2lss_1tau.central_or_shift = cms.string('central')
process.analyze_2lss_1tau.lumiScale = cms.double(0.002600)
process.analyze_2lss_1tau.apply_genWeight = cms.bool(True)
process.analyze_2lss_1tau.apply_trigger_bits = cms.bool(True)
#process.analyze_2lss_1tau.selEventsFileName_output = cms.string('/home/veelken/ttHAnalysis/2016/2016Nov03/output_rle/2lss_1tau/Tight_SS/ttHJetToNonbb_M125/rle_2lss_1tau_ttHJetToNonbb_M125_Tight_SS_central_0.txt')
#process.analyze_2lss_1tau.selEventsFileName_output = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/str_2lss_1tau_SR.txt')
#process.analyze_2lss_1tau.selEventsFileName_output = cms.string('/home/veelken/ttHAnalysis/2016/2017Feb22/output_rle/2lss_1tau/Tight_SS_OS/ttHJetToNonbb_M125_amcatnlo/rle_2lss_1tau_ttHJetToNonbb_M125_amcatnlo_Tight_lepSS_sumOS_central_1.txt')
process.analyze_2lss_1tau.selectBDT = cms.bool(False)
process.analyze_2lss_1tau.apply_leptonGenMatching_ttZ_workaround = cms.bool(False)
process.analyze_2lss_1tau.branchName_genLeptons1 = cms.string('GenLep')
process.analyze_2lss_1tau.branchName_genLeptons2 = cms.string('GenLepFromTau')
process.analyze_2lss_1tau.branchName_genHadTaus = cms.string('GenHadTaus')
process.analyze_2lss_1tau.branchName_genJets = cms.string('GenJet')
