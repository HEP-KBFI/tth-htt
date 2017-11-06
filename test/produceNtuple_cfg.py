import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849/0000/tree_1.root'),

    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('produceNtuple.root')
)

process.produceNtuple = cms.PSet(
    treeName = cms.string('tree'),

    era = cms.string('2016'),

    leptonSelection = cms.string('Fakeable'),
    hadTauSelection = cms.string('Fakeable|dR03mvaMedium'),

    minNumLeptons = cms.int32(1),
    minNumHadTaus = cms.int32(1),
    minNumLeptons_and_HadTaus = cms.int32(2),
    minNumJets = cms.int32(2),
    minNumBJets_loose = cms.int32(2),
    minNumBJets_medium = cms.int32(1),

    branchName_electrons = cms.string('selLeptons'), # 'Electron' for 2017
    branchName_muons = cms.string('selLeptons'), # 'Muon' for 2017
    branchName_hadTaus = cms.string('TauGood'), # 'Tau' for 2017
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),
    branchName_genLeptons1 = cms.string('GenLep'), # 'GenPart' for 2017
    branchName_genLeptons2 = cms.string('GenLepFromTau'), # '' for 2017
    branchName_genHadTaus = cms.string('GenHadTaus'), # 'GenVisTau' for 2017
    branchName_genJets = cms.string('GenJet'),

    use_HIP_mitigation_mediumMuonId = cms.bool(False),

    isMC = cms.bool(True),

    selEventsFileName_input = cms.string(''),

    #----------------------------------------------------------------------------
    # CV: Copy additional branches from input to output tree
    #     Note that branches that are accessed by
    #      - RecoElectron, RecoMuon, RecoHadTau, RecoJet, RecoMEt
    #      - GenLepton, GenHadTau, GenJet (if MC)
    #     reader classes must *not* appear in the outputCommands,
    #     as ROOT cannot handle accesses from multiple places in the code to the same branch
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
        ##"keep *GenLep*",
        ##"keep *GenLepFromTau*",
        "keep *GenTaus*",
        ##"keep *GenHadTaus*",
        "keep *GenNu*",
        "keep *GenBQuarkFromTop*",
        "keep *GenHiggsBoson*",
        "keep *GenTop*",
        "keep *GenVbosons*",
        ##"keep *GenJet*",
        "keep genHiggsDecayMode",
        "keep genTTH*",
        "drop *Recovered*",
    ),
    #----------------------------------------------------------------------------

    copy_histograms = cms.vstring(
        "Count",
        "CountFullWeighted",
        "CountWeighted",
        "CountPosWeight",
        "CountNegWeight",
        "CountWeightedLHEWeightScale",
        "CountWeightedLHEWeightPdf",
    ),

    random_seed = cms.uint32(4357)
)

