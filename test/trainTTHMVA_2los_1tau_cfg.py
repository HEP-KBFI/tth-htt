import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteInput.fileNames = cms.vstring(
    '/home/arun/ttHAnalysis/2016Aug09_dR03mvaVVLoose/histograms/histograms_harvested_stage1_2los_1tau.root'
)

process.trainTTHMVA_1l_2tau = cms.PSet(

    treeName = cms.string('evtTree'),

    signalDirPath = cms.string('2los_1tau_Tight/sel/evtntuple/signal'),
    backgroundDirPath = cms.string('2los_1tau_Tight/sel/evtntuple/TT'),

    branchNameEvtWeight = cms.string(''),

    mvaName = cms.string("mvaTTHvsTTbar2los1tau"),
    mvaMethodType = cms.string("BDT"),
    mvaMethodName = cms.string("BDTG"),
    mvaTrainingOptions = cms.string(
        "!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.30:UseBaggedBoost:GradBaggingFraction=0.5:SeparationType=GiniIndex:nCuts=500:PruneMethod=NoPruning:MaxDepth=3"
    ),
    inputVariables = cms.vstring(
        'lep1_pt/F',
        'lep1_eta/F',
        'lep2_pt/F',
        'lep2_eta/F',
        'lep1_tth_mva/F',
        'lep2_tth_mva/F',
        'mindr_lep1_jet/F',
        'mindr_lep2_jet/F',
        'mindr_tau_jet/F',
        'avg_dr_jet/F',
        'ptmiss/F',
        'mT_lep1/F',
        'mT_lep2/F',
        'htmiss/F',
        'dr_leps/F',
        #'nJet/I',
        #'nBJetLoose/I',
        #'nBJetMedium/I',
        'tau_pt/F',
        'tau_eta/F',
        'dr_lep_tau_os/F',
        'dr_lep_tau_ss/F',
        'mTauTauVis/F'
    ),
    spectatorVariables = cms.vstring(
        'nJet/I',
        'nBJetLoose/I',
        'nBJetMedium/I',
        'tau_mva/F'
    ),

    outputFileName = cms.string('/scratch/arun/mvaTraining/2016Aug10_dR03mvaVVLoose/trainTTHMVA_2los_1tau_woTauID_woNJet.root')
)
