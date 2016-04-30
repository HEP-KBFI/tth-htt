import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_1/tree.root'),
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_2/tree.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/karl/sandbox/ttHJetToTT_M125_13TeV_ntuples_sync_v2.root')
#    fileName = cms.string('/home/karl/sandbox/ttJet_13TeV_ntuples_sync_v2.root')
)

process.syncNtuple = cms.PSet(
    treeName = cms.string('tree'),
    outputTreeName = cms.string('tree'),
    
    process = cms.string('ttH'),
#    process = cms.string('ttJet'),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
