import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteInput.fileNames = cms.vstring(
    '/home/arun/ttHAnalysis/2016Aug09_dR03mvaVLoose/histograms/histograms_harvested_stage1_1l_1tau.root'
)

process.trainTTHMVA_1l_2tau = cms.PSet(

    treeName = cms.string('evtTree'),

    signalDirPath = cms.string('1l_1tau_OS_Tight/sel/evtntuple/signal'),
    backgroundDirPath = cms.string('1l_1tau_OS_Tight/sel/evtntuple/TT'),

    branchNameEvtWeight = cms.string(''),

    mvaName = cms.string("mvaTTHvsTTbar1l1tau"),
    mvaMethodType = cms.string("BDT"),
    mvaMethodName = cms.string("BDTG"),
    mvaTrainingOptions = cms.string(
        "!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.30:UseBaggedBoost:GradBaggingFraction=0.5:SeparationType=GiniIndex:nCuts=500:PruneMethod=NoPruning:MaxDepth=3"
    ),
    inputVariables = cms.vstring(
        'lep_pt/F',
        'lep_eta/F',
        'lep_tth_mva/F',
        #'nJet/I',
        #'nBJetLoose/I',
        #'nBJetMedium/I',
        'mindr_lep_jet/F',
        'mindr_tau_jet/F',
        'avg_dr_jet/F',
        'ptmiss/F',
        'mT_lep/F',
        'htmiss/F',
        #'tau_mva/F',
        'tau_pt/F',
        'tau_eta/F',
        'dr_tau_lep/F',
        'mTauTauVis/F',
        'mTauTau/F'
    ),
    spectatorVariables = cms.vstring(
        'nJet/I',
        'nBJetLoose/I',
        'nBJetMedium/I',
        'tau_mva/F'
    ),

    outputFileName = cms.string('/scratch/arun/mvaTraining/2016Aug10_dR03mvaVLoose/trainTTHMVA_1l_1tau_woTauID_woNJet.root')
)
