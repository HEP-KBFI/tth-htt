import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/local/lucia/VHBBHeppyV24bis/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('produceNtuple_3l_1tau.root')
)

process.produceNtuple_3l_1tau = cms.PSet(
    treeName = cms.string('tree'),

    era = cms.string('2016'),

    leptonSelection = cms.string('Loose'),
    minNumLeptons = cms.int32(2),

    hadTauSelection = cms.string('Loose|dR03mvaVVLoose'),
    minNumHadTaus = cms.int32(1),

    minNumJets = cms.int32(1),

    minNumBJets_loose = cms.int32(0),
    minNumBJets_medium = cms.int32(0),

    selEventsFileName_input = cms.string(''),

    selEventsFileName_addMEM = cms.string(''),

    outputCommands = cms.vstring(
        "drop *",
        ##"keep run",
        ##"keep lumi",
        ##"keep evt",
        "keep isData",
        "keep bx",
        "keep *l1*",
        "keep HLT_BIT_HLT_*Ele*",
        "keep HLT_BIT_HLT_*Mu*",
        "keep HLT_BIT_HLT_*Tau*",
        "keep *trgObjects*Ele*",
        "keep *trgObjects*Mu*",
        "keep *trgObjects*Tau*",
        "keep Flag_*",
        ##"keep *selLeptons_*",
        ##"keep *TauGood_*",
        ##"keep *Jet_*",
        ##"keep *Jet_bTagWeight*Up",
        ##"keep *Jet_bTagWeight*Down",
        ##"keep met_*",
        "keep metPuppi_*",
        "keep tkMet_*",
        "keep xsec",
        "keep *LHE*",
        "keep nPU",
        "keep nPVs",
        "keep *primaryVertices*",
        "keep rho*",
        "keep puWeight*",
        "keep genWeight*",
        "keep btagWeight*",
        "keep *GenLep*",
        "keep *GenTaus*",
        "keep *GenTauHad*",
        "keep *GenHadTaus*",
        "keep *GenNu*",
        "keep *GenBQuarkFromTop*",
        "keep *GenHiggsBoson*",
        "keep *GenTop*",
        "keep *GenVbosons*",
        "keep *GenJet*",
        "keep genHiggsDecayMode",
        "keep genTTH*",
        "drop *Recovered*",
    ),

    copy_histograms = cms.vstring(
        "Count",
        "CountFullWeighted",
        "CountWeighted",
        "CountPosWeight",
        "CountNegWeight",
        "CountWeightedLHEWeightScale",
        "CountWeightedLHEWeightPdf",
    )
)
