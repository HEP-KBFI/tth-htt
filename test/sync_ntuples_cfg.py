import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_1/tree.root'),
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_2/tree.root'),
    fileNames = cms.vstring('/hdfs/local/lucia/VHBBHeppyV24bis/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttHJetToTT_M125_13TeV_ntuples_sync_v0.root')
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttJet_13TeV_ntuples_sync_v0.root')
    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttHJetToNonbb_M125_13TeV_sync_v0.root')
)

process.syncNtuple = cms.PSet(
    treeName = cms.string('tree'),
    outputTreeName = cms.string('tree'),
#    era = cms.string('2015'),
    era = cms.string('2016'),

    # 2015 triggers
    #triggers_1e = cms.vstring('HLT_BIT_HLT_Ele23_WPLoose_Gsf_v'),
    #triggers_2e = cms.vstring('HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    #triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu20_v', 'HLT_BIT_HLT_IsoTkMu20_v'),
    #triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    #triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v'),

    # 2016 triggers
    triggers_1e = cms.vstring('HLT_BIT_HLT_Ele25_WPTight_Gsf_v'),
    triggers_2e = cms.vstring('HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'),
    triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
