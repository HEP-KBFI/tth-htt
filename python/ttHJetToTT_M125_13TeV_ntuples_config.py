import os
import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
  fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x2/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_4/tree.root'),
  maxEvents = cms.int32(-1),
  outputEvery = cms.uint32(100000)
)

process.ioFormat = cms.PSet(
  outputFilename = cms.string('/home/karl/synch_tth/ttHJetToTT_M125_13TeV_ntuples_sync.root'),
  inputTreename = cms.string('tree'),
  outputTreename = cms.string('tree')
)