import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_2lss_1tau.root')
)

process.analyze_2lss_1tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    triggers_1e = cms.vstring(""),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring(""),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring(""),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring(""),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring(""),
    use_triggers_1e1mu = cms.bool(True),
    
    chargeSelection = cms.string('SS'),
    leptonSelection = cms.string('Tight'),
    
    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
