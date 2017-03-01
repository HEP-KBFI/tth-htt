import FWCore.ParameterSet.Config as cms
import os, sys
sys.path.append("..")

from sync_ntuples_cfg import *

process.syncNtuple.selEventsFileName_input = cms.string('output/selEvents_ttHJetToNonbb_1l_2tau_M125_Tight_OS.txt')
process.syncNtuple.outputTreeName = cms.string('syncTree_1l2tau_SR')
process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/ntuple/sync_ntuple_1l_2tau_OS.root')
)
