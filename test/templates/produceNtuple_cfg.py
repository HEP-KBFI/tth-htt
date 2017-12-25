import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring(''),
    maxEvents   = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('produceNtuple.root')
)

process.produceNtuple = cms.PSet(
    treeName = cms.string('Events'),

    era = cms.string('2017'),

    leptonSelection = cms.string('Fakeable'),
    hadTauSelection = cms.string('Fakeable|dR03mvaMedium'),

    minNumLeptons             = cms.int32(1),
    minNumHadTaus             = cms.int32(1),
    minNumLeptons_and_HadTaus = cms.int32(2),
    minNumJets                = cms.int32(2),
    minNumBJets_loose         = cms.int32(2),
    minNumBJets_medium        = cms.int32(1),

    branchName_electrons   = cms.string('Electron'),
    branchName_muons       = cms.string('Muon'),
    branchName_hadTaus     = cms.string('Tau'),
    branchName_jets        = cms.string('Jet'),
    branchName_met         = cms.string('MET'),
    branchName_genLeptons1 = cms.string('GenLep'),
    branchName_genLeptons2 = cms.string(''),
    branchName_genHadTaus  = cms.string('GenVisTau'),
    branchName_genJets     = cms.string('GenJet'),

    use_HIP_mitigation_mediumMuonId = cms.bool(False),

    isMC = cms.bool(True),

    selEventsFileName_input = cms.string(''),

    #----------------------------------------------------------------------------
    # CV: Copy additional branches from input to output tree
    #     Note that branches that are accessed by
    #      - RecoElectron, RecoMuon, RecoHadTau, RecoJet, RecoMEt
    #      - GenLep, GenVisTau, GenJet (if MC)
    #     reader classes must *not* appear in the outputCommands,
    #     as ROOT cannot handle accesses from multiple places in the code to the same branch
    #TODO: Karl: record the branch names to be read inside the *Reader classes and put "keep *" here
    outputCommands = cms.vstring(
        "drop *",
        "keep *l1*",
        "keep HLT_*Ele*",
        "keep HLT_*Mu*",
        "keep HLT_*Tau*",
        "keep *TrigObj*",
        "keep Flag_*",
        "keep PuppiMET_*",
        "keep TkMET_*",
        "keep *LHE*",
        "keep Pileup_*",
        "keep PV_*",
        "keep *Rho*",
        "keep *Weight*",
        "keep gen*",
        "keep *GenHiggs*",
        "keep *GenNu*",
        "keep *Gen*Quark*",
        "keep *Gen*boson*",
        "keep *GenTau*",
        "keep *Gen*Top*",
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
