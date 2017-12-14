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
    fileName = cms.string('tthMVATrainingNtuple_1l_1tau.root')
)

process.produceTTHMVATrainingNtuple_1l_1tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(False),

    chargeSelection = cms.string('OS'),
    
    hadTauSelection = cms.string('Tight'),
    hadTauGenMatch = cms.string('all'),

    hadTauEtaBins = cms.vdouble(-1., 1.2, 1.7, 9.9),

    applyJetToTauFakeRateWeight = cms.bool(False),
    jetToTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/tauFR_data_dR03MVATight.root"),
        fitFunctionNormName = cms.string("jetToTauFakeRate/$etaBin/fitFunctionNorm_SS_Tight_div_SS_Fakeable"),
        graphShapeName = cms.string(""),
        fitFunctionShapeName_central = cms.string("jetToTauFakeRate/$etaBin/fitFunctionShape_hadTauPt_lead_SS_Tight_div_SS_Fakeable"),
        fitFunctionShapeName_shift = cms.string(""),
        fitFunctionShapePower = cms.double(1.),
        applyFitFunction_or_graph = cms.string("fitFunction")
    ),
        
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
