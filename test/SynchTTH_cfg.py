import os
import FWCore.ParameterSet.Config as cms
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
  fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
  maxEvents = cms.int32(-1),
  outputEvery = cms.uint32(100000)
)
process.SynchTTH = cms.PSet(
  isMC = cms.bool(True),
  central_or_shift = cms.string('central'),
  outputDir = cms.string('/tmp/veelken/'),
  forceOverwrite = cms.bool(True)
)
