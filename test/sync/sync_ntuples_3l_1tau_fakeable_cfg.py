import FWCore.ParameterSet.Config as cms
import os, sys
sys.path.append("..")

from sync_ntuples_cfg import *

process.syncNtuple.selEventsFileName_input = cms.string('output/selEvents_ttHJetToNonbb_3l_1tau_M125_Fakeable_wFakeRateWeights_OS.txt')
process.syncNtuple.outputTreeName = cms.string('syncTree_3l1tau_Fake')
process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/ntuple/sync_ntuple_3l_1tau_fakeable.root')
)