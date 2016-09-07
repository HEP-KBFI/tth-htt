import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    fileNames = cms.vstring('/afs/cern.ch/user/k/kaehatah/public/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_1l_2tau.root')
)

process.analyze_1l_2tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
        
    hadTauChargeSelection = cms.string('OS'),
    hadTauSelection = cms.string('Tight'),
    hadTauGenMatch = cms.string('all'),
    apply_hadTauGenMatching = cms.bool(False),

    hadTauEtaBins_lead = cms.vdouble(-1., 1.2, 1.7, 9.9),
    hadTauEtaBins_sublead = cms.vdouble(-1., 1.2, 1.7, 9.9),

    applyJetToTauFakeRateWeight = cms.bool(False),
    jetToTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau.root"),
        absEtaBins = cms.vdouble(-1., 1.479, 9.9),
        graphName_lead = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
        applyGraph_lead = cms.bool(True),
        fitFunctionName_lead = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
        applyFitFunction_lead = cms.bool(True),
        graphName_sublead = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
        applyGraph_sublead = cms.bool(True),
        fitFunctionName_sublead = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
        applyFitFunction_sublead = cms.bool(True),
    ),
    
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
