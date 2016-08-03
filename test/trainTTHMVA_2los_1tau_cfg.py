import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteInput.fileNames = cms.vstring(
    '/home/arun/ttHAnalysis/2016Jul31_dR03mvaVLoose/histograms/histograms_harvested_stage1_2los_1tau.root'
)

process.trainTTHMVA_1l_2tau = cms.PSet(

    treeName = cms.string('evtTree'),

    signalDirPath = cms.string('2los_1tau_Tight/sel/evtntuple/signal'),
    backgroundDirPath = cms.string('2los_1tau_Tight/sel/evtntuple/TT'),

    branchNameEvtWeight = cms.string(''),

    mvaName = cms.string("mvaTTHvsTTbar0l2tau"),
    mvaMethodType = cms.string("BDT"),
    mvaMethodName = cms.string("BDTG"),
    mvaTrainingOptions = cms.string(
        "!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.30:UseBaggedBoost:GradBaggingFraction=0.5:SeparationType=GiniIndex:nCuts=500:PruneMethod=NoPruning:MaxDepth=3"
    ),
    inputVariables = cms.vstring(
        'lep_pt_max/F',
        'lep_eta_max/F',
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
        'nJet/I',
        'nBJetLoose/I',
        'nBJetMedium/I',
        'mTauTauVis/F'
    ),
    spectatorVariables = cms.vstring(
        'tau_mva/F',
        'tau_pt/F' 
    ),

    outputFileName = cms.string('/scratch/arun/mvaTraining/2016Jul31_dR03mvaVLoose/trainTTHMVA_2los_1tau_noTauID.root')
)
