import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/local/karl/ttHNtupleProduction/2017/2018Apr08_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo/0000/tree_1.root'),
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
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaVLoose'),
    apply_hadTauGenMatching = cms.bool(True),

    chargeSumSelection = cms.string('OS'),

    apply_lepton_and_hadTauCharge_cut = cms.bool(True),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_trigger_bits = cms.bool(False),

    cfgMEtFilter = cms.PSet(),
    cfgEvtYieldHistManager = cms.PSet(),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_jetsHTTv2 = cms.string('HTTV2'),
    branchName_subjetsHTTv2 = cms.string('HTTV2Subjets'),
    branchName_jetsAK12 = cms.string('FatJetAK12'),
    branchName_subjetsAK12 = cms.string('SubJetAK12'),
    branchName_met = cms.string('MET'),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genPhotons = cms.string('GenPhoton'),
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
    selEventsFileName_output = cms.string('selEvents_hadTopTagger_gen.txt'),
    selEventsFileName_output_boosted = cms.string('selEvents_hadTopTagger_gen_boosted.txt'),
    selEventsFileName_output_semiboosted = cms.string('selEvents_hadTopTagger_gen_semiboosted.txt'),
    selEventsFileName_output_resolved = cms.string('selEvents_hadTopTagger_gen_resolved.txt'),
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

## inputFilePath = "/hdfs/local/karl/ttHNtupleProduction/2017/2018Feb28_wNanoPrep_woPresel_all/ntuples/ttHJetToNonbb_M125_amcatnlo/0000/"
## maxInputFiles = 50
## zombie_files = []
## import os
## def getInputFiles(inputFilePath):
##     inputFiles = []
##     files_and_subdirectories = os.listdir(inputFilePath)
##     for file_or_subdirectory in files_and_subdirectories:
##         if file_or_subdirectory in zombie_files:
##             continue
##         file_or_subdirectory = os.path.join(inputFilePath, file_or_subdirectory)
##         if os.path.isfile(file_or_subdirectory):
##             if file_or_subdirectory.endswith(".root"):
##                 inputFiles.append(file_or_subdirectory)
##         if os.path.isdir(file_or_subdirectory):
##             inputFiles.extend(getInputFiles(file_or_subdirectory))
##     return inputFiles
## inputFiles = getInputFiles(inputFilePath)
## process.fwliteInput.fileNames = cms.vstring(inputFiles[0:maxInputFiles])
## print "inputFiles = ", process.fwliteInput.fileNames

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
process.analyze_hadTopTagger_gen.leptonChargeSelection = cms.string('SS')
process.analyze_hadTopTagger_gen.hadTauSelection = cms.string('Tight|dR03mvaMedium')
process.analyze_hadTopTagger_gen.apply_hadTauGenMatching = cms.bool(True)
process.analyze_hadTopTagger_gen.chargeSumSelection = cms.string('OS')
process.analyze_hadTopTagger_gen.isMC = cms.bool(True)
process.analyze_hadTopTagger_gen.central_or_shift = cms.string('central')
process.analyze_hadTopTagger_gen.lumiScale = cms.double(0.002600)
process.analyze_hadTopTagger_gen.apply_genWeight = cms.bool(True)
process.analyze_hadTopTagger_gen.apply_trigger_bits = cms.bool(True)



#added by Siddhesh
inputFilePath = "/hdfs/local/karl/ttHNtupleProduction/2017/2018May09_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo/0000/"
maxInputFiles = 50
#zombie_files = [ "tree_110.root", ]
#zombie_files = [ "tree_110.root", "tree_168.root"]
zombie_files = [ ]
import os
def getInputFiles(inputFilePath):
    inputFiles = []
    files_and_subdirectories = os.listdir(inputFilePath)
    for file_or_subdirectory in files_and_subdirectories:
        if file_or_subdirectory in zombie_files:
            continue
        file_or_subdirectory = os.path.join(inputFilePath, file_or_subdirectory)
        if os.path.isfile(file_or_subdirectory):
            if file_or_subdirectory.endswith(".root"):
                inputFiles.append(file_or_subdirectory)
        if os.path.isdir(file_or_subdirectory):
            inputFiles.extend(getInputFiles(file_or_subdirectory))
    return inputFiles
inputFiles = getInputFiles(inputFilePath)
process.fwliteInput.fileNames = cms.vstring(inputFiles[0:maxInputFiles])
print "inputFiles = ", process.fwliteInput.fileNames

