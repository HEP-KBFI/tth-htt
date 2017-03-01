import FWCore.ParameterSet.Config as cms
import os, sys
sys.path.append("..")

from sync_ntuples_cfg import *

process.syncNtuple.selEventsFileName_input = cms.string('output/selEvents_ttHJetToNonbb_2lss_1tau_M125_Tight_OS.txt')
process.syncNtuple.outputTreeName = cms.string('syncTree_2lSS1tau_Flip')
process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/ntuple/sync_ntuple_2lss_1tau_OS.root')
)
