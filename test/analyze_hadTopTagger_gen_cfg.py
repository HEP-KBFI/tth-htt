import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_hadTopTagger_gen.root')
)

process.analyze_hadTopTagger_gen = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string('ttH'),

    histogramDir = cms.string('hadTopTagger_gen'),

    era = cms.string('2017'),

    triggers_1e = cms.vstring('HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v'),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring('HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'),
    use_triggers_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),

    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(True),
    apply_leptonGenMatching_ttZ_workaround = cms.bool(False),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    apply_hadTauGenMatching = cms.bool(True),

    chargeSumSelection = cms.string('OS'),

    use_HIP_mitigation_mediumMuonId = cms.bool(False),

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
    branchName_met = cms.string('MET'),

    branchName_genLeptons1 = cms.string('GenDressedLepton'),
    branchName_genLeptons2 = cms.string(''),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    branchName_genTopQuarks = cms.string('GenTop'),
    branchName_genBJets = cms.string('GenBQuarkFromTop'),
    branchName_genWBosons = cms.string('GenVbosons'),
    branchName_genWJets = cms.string('GenWZQuark'),
)

process.fwliteInput.fileNames = cms.vstring(['/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_13.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_14.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_15.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_16.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_17.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_18.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_19.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_2.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_21.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_22.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_3.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_4.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_5.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_6.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_7.root', '/hdfs/cms/store/user/kaehatah/NanoAOD_2017/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoAOD_jetSubstrcutre_v8_ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180208_134952/0000/tree_8.root'])
process.fwliteOutput.fileName = cms.string('analyze_hadTopTagger_gen.root')
process.analyze_hadTopTagger_gen.process = cms.string('signal')
process.analyze_hadTopTagger_gen.era = cms.string('2017')
process.analyze_hadTopTagger_gen.triggers_1e = cms.vstring(['HLT_Ele27_WPTight_Gsf'])
process.analyze_hadTopTagger_gen.use_triggers_1e = cms.bool(True)
process.analyze_hadTopTagger_gen.triggers_2e = cms.vstring(['HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ'])
process.analyze_hadTopTagger_gen.use_triggers_2e = cms.bool(True)
process.analyze_hadTopTagger_gen.triggers_1mu = cms.vstring(['HLT_IsoMu24'])
process.analyze_hadTopTagger_gen.use_triggers_1mu = cms.bool(True)
process.analyze_hadTopTagger_gen.triggers_2mu = cms.vstring(['HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ'])
process.analyze_hadTopTagger_gen.use_triggers_2mu = cms.bool(True)
process.analyze_hadTopTagger_gen.triggers_1e1mu = cms.vstring(['HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL', 'HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL'])
process.analyze_hadTopTagger_gen.use_triggers_1e1mu = cms.bool(True)
process.analyze_hadTopTagger_gen.leptonSelection = cms.string('Tight')
process.analyze_hadTopTagger_gen.apply_leptonGenMatching = cms.bool(True)
process.analyze_hadTopTagger_gen.apply_leptonGenMatching_ttZ_workaround = cms.bool(True)
process.analyze_hadTopTagger_gen.leptonChargeSelection = cms.string('SS')
process.analyze_hadTopTagger_gen.hadTauSelection = cms.string('Tight|dR03mvaMedium')
process.analyze_hadTopTagger_gen.apply_hadTauGenMatching = cms.bool(True)
process.analyze_hadTopTagger_gen.chargeSumSelection = cms.string('OS')
process.analyze_hadTopTagger_gen.use_HIP_mitigation_mediumMuonId = cms.bool(True)
process.analyze_hadTopTagger_gen.isMC = cms.bool(True)
process.analyze_hadTopTagger_gen.central_or_shift = cms.string('central')
process.analyze_hadTopTagger_gen.lumiScale = cms.double(0.002600)
process.analyze_hadTopTagger_gen.apply_genWeight = cms.bool(True)
process.analyze_hadTopTagger_gen.apply_trigger_bits = cms.bool(True)
process.analyze_hadTopTagger_gen.isDEBUG = cms.bool(False)

