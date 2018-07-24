import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteInput.fileNames = cms.vstring(
    #'/hdfs/local/arun/ttHAnalysis/2016/2017June13_dR03mvaLoose/histograms/2los_1tau/forBDTtraining/histograms_2los_1tau_all.root'
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p1.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p2.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p3.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p1.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p2.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p3.root',
    '/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTZToLLNuNu_fastsim.root'
)

process.trainTTHMVA_hadTopTagger = cms.PSet(

    treeName = cms.string('evtTree'),

    treeDirPath = cms.string('analyze_hadTopTagger/evtntuple/signal'),
    #treeDirPath2 = cms.untracked.string('analyze_hadTopTagger/evtntuple/TT'),
    #treeDirPath3 = cms.untracked.string('analyze_hadTopTagger/evtntuple/TTZ'),
    #preselection = cms.untracked.string("lep1_isTight>0.5 && lep2_isTight>0.5 && tau_isTight>0.5"),
    signalPreselection = cms.untracked.string("bWj1Wj2_isGenMatched>0.5"),
    bkgPreselection = cms.untracked.string("bWj1Wj2_isGenMatched<0.5"),
    branchNameEvtWeight = cms.string(''),
    mvaName = cms.string("mvaHadTopTagger"),
    mvaMethodType = cms.string("BDT"),
    mvaMethodName = cms.string("BDTG"),
    mvaTrainingOptions = cms.string(
        "!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.30:UseBaggedBoost:GradBaggingFraction=0.5:SeparationType=GiniIndex:nCuts=500:PruneMethod=NoPruning:MaxDepth=3"
    ),
    inputVariables = cms.vstring(
        'CSV_Wj1/F',
        'CSV_Wj2/F',
        'CSV_b/F',
        'alphaKinFit/F',
        'dR_Wj1Wj2/F',
        'dR_bW/F',
        'dR_bWj1/F',
        'dR_bWj2/F',
        'logPErrKinFit/F',
        'logPKinFit/F',
        'm_Wj1Wj2/F',
        'm_Wj1Wj2_div_m_bWj1Wj2/F',
        'm_bWj1/F',
        'm_bWj1Wj2/F',
        'm_bWj2/F',
        'max_dR_div_expRjet/F',
        'nllKinFit/F',
        'pT_Wj1/F',
        'pT_Wj1Wj2/F',
        'pT_Wj2/F',
        'pT_b/F',
        'pT_bWj1Wj2/F',
        'qg_Wj1/F',
        'qg_Wj2/F',
        'qg_b/F',
        'statusKinFit/F'
        ),
    spectatorVariables = cms.vstring(
        ),
    outputFileName = cms.string('trainTTHMVA_hadTopTagger_26Var_15Sep2017_ttH.root')
)
