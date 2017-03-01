import FWCore.ParameterSet.Config as cms
import os, sys
sys.path.append("..")

from sync_ntuples_cfg import *

process.syncNtuple.selEventsFileName_input = cms.string('output/selEvents_ttHJetToNonbb_2lss_1tau_M125_Tight_SS.txt')
process.syncNtuple.outputTreeName = cms.string('syncTree_2lSS1tau_SR')
process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/ntuple/sync_ntuple_2lss_1tau_SS.root')
)

process.syncNtuple.histogramDir = cms.string('2lss_1tau_SS_Tight')
process.syncNtuple.era = cms.string('2016')
process.syncNtuple.triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v'])
process.syncNtuple.use_triggers_1e = cms.bool(True)
process.syncNtuple.triggers_2e = cms.vstring(['HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'])
process.syncNtuple.use_triggers_2e = cms.bool(True)
process.syncNtuple.triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'])
process.syncNtuple.use_triggers_1mu = cms.bool(True)
process.syncNtuple.triggers_2mu = cms.vstring(['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'])
process.syncNtuple.use_triggers_2mu = cms.bool(True)
process.syncNtuple.triggers_1e1mu = cms.vstring(['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'])
process.syncNtuple.use_triggers_1e1mu = cms.bool(True)
process.syncNtuple.leptonSelection = cms.string('Tight')
process.syncNtuple.apply_leptonGenMatching = cms.bool(True)
process.syncNtuple.leptonChargeSelection = cms.string('SS')
process.syncNtuple.hadTauSelection = cms.string('Tight|dR03mvaMedium')
process.syncNtuple.apply_hadTauGenMatching = cms.bool(False)
process.syncNtuple.applyFakeRateWeights = cms.string('disabled')
process.syncNtuple.isMC = cms.bool(True)
process.syncNtuple.central_or_shift = cms.string('central')
process.syncNtuple.lumiScale = cms.double(0.000446)
process.syncNtuple.apply_genWeight = cms.bool(True)
process.syncNtuple.apply_trigger_bits = cms.bool(True)
process.syncNtuple.use_HIP_mitigation_bTag = cms.bool(True)
process.syncNtuple.use_HIP_mitigation_mediumMuonId = cms.bool(False)

