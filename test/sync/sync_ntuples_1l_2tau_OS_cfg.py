import FWCore.ParameterSet.Config as cms
import os, sys
sys.path.append("..")

from sync_ntuples_cfg import *

process.syncNtuple.selEventsFileName_input = cms.string('output/selEvents_ttHJetToNonbb_1l_2tau_M125_Tight_OS.txt')
process.syncNtuple.outputTreeName = cms.string('syncTree_1l2tau_SR')
process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/ntuple/sync_ntuple_1l_2tau_OS.root')
)

process.syncNtuple.process = cms.string('signal')
process.syncNtuple.histogramDir = cms.string('1l_2tau_OS_Tight')
process.syncNtuple.era = cms.string('2016')
process.syncNtuple.triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded_v'])
process.syncNtuple.use_triggers_1e = cms.bool(True)
process.syncNtuple.triggers_1e1tau = cms.vstring(['HLT_BIT_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v', 'HLT_BIT_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v', 'HLT_BIT_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v'])
#process.syncNtuple.triggers_1e1tau = cms.vstring(['HLT_BIT_HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v'])
process.syncNtuple.use_triggers_1e1tau = cms.bool(True)
process.syncNtuple.triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v', 'HLT_BIT_HLT_IsoMu22_eta2p1_v', 'HLT_BIT_HLT_IsoTkMu22_eta2p1_v'])
process.syncNtuple.use_triggers_1mu = cms.bool(True)
process.syncNtuple.triggers_1mu1tau = cms.vstring(['HLT_BIT_HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v'])
process.syncNtuple.use_triggers_1mu1tau = cms.bool(False)
process.syncNtuple.leptonSelection = cms.string('Tight')
process.syncNtuple.apply_leptonGenMatching = cms.bool(True)
process.syncNtuple.hadTauSelection = cms.string('Tight|dR03mvaTight')
process.syncNtuple.hadTauChargeSelection = cms.string('OS')
process.syncNtuple.apply_hadTauGenMatching = cms.bool(True)
process.syncNtuple.applyFakeRateWeights = cms.string('disabled')
process.syncNtuple.use_HIP_mitigation_bTag = cms.bool(True)
process.syncNtuple.use_HIP_mitigation_mediumMuonId = cms.bool(True)
process.syncNtuple.isMC = cms.bool(True)
process.syncNtuple.central_or_shift = cms.string('central')
process.syncNtuple.lumiScale = cms.double(0.002600)
process.syncNtuple.apply_genWeight = cms.bool(True)
process.syncNtuple.apply_trigger_bits = cms.bool(True)
