import FWCore.ParameterSet.Config as cms
import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    fileNames = cms.vstring('/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_1.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_2.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_3.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_4.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_5.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_6.root',
                            '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_7.root'
    ),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_LeptonFakeRate.root')
)

process.analyze_LeptonFakeRate = cms.PSet(
    treeName = cms.string('tree'),
    process = cms.string('ttH'),
    era = cms.string('2016'),

    triggers_mu = cms.VPSet(
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu27_v"),
            cone_minPt = cms.double(45.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(143),
            prescale_rand_mc = cms.double(5.) 
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu17_v"),
            cone_minPt = cms.double(30.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(126),
            prescale_rand_mc = cms.double(5.) 
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu8_v"),
            cone_minPt = cms.double(15.),
            cone_maxPt = cms.double(45.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(9072),
            prescale_rand_mc = cms.double(100.) 
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu3_PFJet40_v"),
            cone_minPt = cms.double(10.),
            cone_maxPt = cms.double(30.),
            jet_minPt = cms.double(40.), 
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(4841),
            prescale_rand_mc = cms.double(100.)
         )
    ),
    use_triggers_1mu = cms.bool(True),

    triggers_e = cms.VPSet(
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v"),
            cone_minPt = cms.double(30.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(569),
            prescale_rand_mc = cms.double(1.)   
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v"),
            cone_minPt = cms.double(20.),
            cone_maxPt = cms.double(30.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(2021),
            prescale_rand_mc = cms.double(1.)
        )
    ),
    use_triggers_1e = cms.bool(True),

#    apply_offline_e_trigger_cuts_1e = cms.bool(True),  ## NOT NEEDED ANYMORE
#    apply_offline_e_trigger_cuts_1mu = cms.bool(True), ## NOT NEEDED ANYMORE

    absEtaBins_e = cms.vdouble(0., 1.479, 9.9),
    absEtaBins_mu = cms.vdouble(0., 1.479, 9.9),
    absPtBins_e = cms.vdouble(15., 20., 30., 45., 65., 100000.),
    absPtBins_mu = cms.vdouble(10., 15., 20., 30., 45., 65., 100000.),

    minPt_e = cms.double(15), ## NEWLY ADDED
    minPt_mu = cms.double(10), ## NEWLY ADDED

    use_HIP_mitigation_mediumMuonId = cms.bool(False),
                                      
    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
#    central_or_shift = cms.string('CMS_ttHl_JERUp'),
    lumiScale = cms.double(1.),
#    apply_trigger_bits = cms.bool(True),  ## True for both Data and MC ## NOT NEEDED ANYMORE
    apply_genWeight = cms.bool(True),
    fillGenEvtHistograms = cms.bool(True),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')

#    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v","HLT_BIT_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v","HLT_BIT_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v"),
#    triggers_1mu = cms.vstring("HLT_BIT_HLT_Mu3_PFJet40_v", "HLT_BIT_HLT_Mu8_v", "HLT_BIT_HLT_Mu17_v", "HLT_BIT_HLT_Mu27_v" ),
#    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
#    use_triggers_1e1mu = cms.bool(False),
#    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),
#    chargeSelection = cms.string('OS'),
#    jet_minPt = cms.double(20.),
#    jet_maxPt = cms.double(1.e+6),
#    jet_minAbsEta = cms.double(-1.),
#    jet_maxAbsEta = cms.double(2.3),
#    hadTauSelections = cms.vstring(
#        'dR05isoLoose',
#        'dR05isoMedium',
#        'dR05isoTight',
#        'dR03mvaVLoose',
#        'dR03mvaLoose',
#        'dR03mvaMedium',
#        'dR03mvaTight',
#        'dR03mvaVTight',
#        'dR03mvaVVTight'
#    ),
#    absEtaBins = cms.vdouble(-1., 1.479, 9.9),
)


### KARL'S LATEST FILES GIVES AN ERROR ABOUT MISSING selleptons BRANCH
# process.fwliteInput.fileNames = cms.vstring('/hdfs/local/karl/ttHNtupleProduction/2016/2017Sep29_wPreselection/ntuples/TTTT/0000/tree_1.root')


#process.fwliteInput.fileNames = cms.vstring(['/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_1.root',                                               '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_2.root',                                               '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_3.root',                                              '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_4.root',                                              '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_5.root',                                             '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_6.root',                                             '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_7.root',                                             '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_8.root',                                             '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_9.root',                                             '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050/0000/tree_10.root']
#)

#process.analyze_LeptonFakeRate.process = cms.string('data_obs')
#process.analyze_LeptonFakeRate.isMC = cms.bool(False)  ## FOR DATA
#process.analyze_LeptonFakeRate.apply_genWeight = cms.bool(False)
#process.analyze_LeptonFakeRate.fillGenEvtHistograms = cms.bool(False)
# process.analyze_LeptonFakeRate.apply_trigger_bits = cms.bool(True) ## True for both Data and MC NOT NEEDED ANYMORE !
#process.analyze_LeptonFakeRate.use_triggers_1e = cms.bool(False)
#process.analyze_LeptonFakeRate.use_triggers_1mu = cms.bool(True)

