import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(''),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_hadTopTagger.root')
)

process.analyze_hadTopTagger = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string('ttH'),

    histogramDir = cms.string('hadTopTagger_gen'),

    era = cms.string('2017'),

    # Xanda: dumb entries for the triggers: we will not use it anyway
    triggers_2e = cms.vstring(),
    use_triggers_2e = cms.bool(False),
    triggers_2mu = cms.vstring(),
    use_triggers_2mu = cms.bool(False),
    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1e1tau = cms.vstring(),
    use_triggers_1e1tau = cms.bool(False),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    triggers_1mu1tau = cms.vstring(),
    use_triggers_1mu1tau = cms.bool(False),
    triggers_1e1mu = cms.vstring(),
    use_triggers_1e1mu = cms.bool(False),

    apply_offline_e_trigger_cuts_1e = cms.bool(False),
    apply_offline_e_trigger_cuts_2e = cms.bool(False),
    apply_offline_e_trigger_cuts_1mu = cms.bool(False),
    apply_offline_e_trigger_cuts_2mu = cms.bool(False),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(False),

    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(True),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    apply_hadTauGenMatching = cms.bool(True),

    chargeSumSelection = cms.string('OS'),

    apply_lepton_and_hadTauCharge_cut = cms.bool(True),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_trigger_bits = cms.bool(False),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_jetsHTTv2 = cms.string('HTTV2'),
    branchName_subjetsHTTv2 = cms.string('HTTV2Subjets'),
    branchName_jetsAK12 = cms.string('FatJetAK12'),
    branchName_subjetsAK12 = cms.string('SubJetAK12'),
    branchName_jetsAK8 = cms.string('FatJet'),
    branchName_subjetsAK8 = cms.string('SubJet'),
    branchName_met = cms.string('MET'),

    #branchName_genLeptons1 = cms.string('GenLep'),
    #branchName_genLeptons2 = cms.string(''),
    #branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    branchName_genTopQuarks = cms.string('GenTop'),
    branchName_genBJets = cms.string('GenBQuarkFromTop'),
    branchName_genWBosons = cms.string('GenVbosons'),
    branchName_genWJets = cms.string('GenWZQuark'),
    branchName_genQuarkFromTop = cms.string('GenQuarkFromTop'),

    selEventsFileName_input = cms.string(''),
    ##selEventsFileName_input = cms.string('/home/veelken/CMSSW_9_4_4/src/tthAnalysis/HiggsToTauTau/test/selEvents_hadTopTagger_gen.txt'),
    ##selEventsFileName_output = cms.string('')
    selEventsFileName_output = cms.string('/home/acaan/CMSSW_9_4_4/src/tthAnalysis/HiggsToTauTau/test/selEvents_hadTopTagger.txt'),

    selectBDT = cms.bool(True),
    isDEBUG = cms.bool(False),
    hasLHE = cms.bool(True),

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    ),
)
