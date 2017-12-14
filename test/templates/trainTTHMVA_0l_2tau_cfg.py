import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteInput.fileNames = cms.vstring(
    '/home/arun/ttHAnalysis/2016Aug09_dR03mvaVVLoose/histograms/histograms_harvested_stage1_0l_2tau.root'
)

process.trainTTHMVA_1l_2tau = cms.PSet(

    treeName = cms.string('evtTree'),

    signalDirPath = cms.string('0l_2tau_OS_Tight/sel/evtntuple/signal'),
    backgroundDirPath = cms.string('0l_2tau_OS_Tight/sel/evtntuple/TT'),

    branchNameEvtWeight = cms.string(''),

    mvaName = cms.string("mvaTTHvsTTbar0l2tau"),
    mvaMethodType = cms.string("BDT"),
    mvaMethodName = cms.string("BDTG"),
    mvaTrainingOptions = cms.string(
        "!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.30:UseBaggedBoost:GradBaggingFraction=0.5:SeparationType=GiniIndex:nCuts=500:PruneMethod=NoPruning:MaxDepth=3"
    ),
    inputVariables = cms.vstring(
        #'nJet/I',
        #'nBJetLoose/I',
        #'nBJetMedium/I',
        'mindr_tau1_jet/F',
        'mindr_tau2_jet/F',
        'avg_dr_jet/F',
        'ptmiss/F',
        'mT_tau1/F',
        'mT_tau2/F',
        'htmiss/F',
        #'tau1_mva/F',
        #'tau2_mva/F',
        'tau1_pt/F',
        'tau2_pt/F',
        'tau1_eta/F',
        'tau2_eta/F',
        'dr_taus/F',
        'mTauTauVis/F',
        'mTauTau/F'
    ),
    spectatorVariables = cms.vstring(
        'nJet/I',
        'nBJetLoose/I',
        'nBJetMedium/I',
        'tau1_mva/F',
        'tau2_mva/F'
    ),

    outputFileName = cms.string('/scratch/arun/mvaTraining/2016Aug10_dR03mvaVVLoose/trainTTHMVA_0l_2tau_woTauID.root')
)
