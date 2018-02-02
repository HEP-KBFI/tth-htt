import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.recommendedMEtFilters_cfi import recommendedMEtFilters
  
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

    use_triggers_1e = cms.bool(True),
    use_triggers_2e = cms.bool(True),
    use_triggers_1mu = cms.bool(True),
    use_triggers_2mu = cms.bool(True),

    triggers_mu = cms.VPSet(
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu27_v"),
            cone_minPt = cms.double(45.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(143),
            prescale_rand_mc = cms.double(5.),
            is_trigger_1mu = cms.bool(True),             
            is_trigger_2mu = cms.bool(False),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(False)             
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu17_v"),
            cone_minPt = cms.double(30.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(126),
            prescale_rand_mc = cms.double(5.),
            is_trigger_1mu = cms.bool(False),             
            is_trigger_2mu = cms.bool(True),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(False)             
         ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu8_v"),
            cone_minPt = cms.double(15.),
            cone_maxPt = cms.double(45.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(9072),
            prescale_rand_mc = cms.double(100.),
            is_trigger_1mu = cms.bool(False),             
            is_trigger_2mu = cms.bool(True),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(False)              
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Mu3_PFJet40_v"),
            cone_minPt = cms.double(10.),
            cone_maxPt = cms.double(30.),
            jet_minPt = cms.double(40.), 
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(4841),
            prescale_rand_mc = cms.double(50.),
            is_trigger_1mu = cms.bool(False),             
            is_trigger_2mu = cms.bool(True),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(False)             
         )
    ),
    
    triggers_e = cms.VPSet(
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v"),
            cone_minPt = cms.double(30.),
            cone_maxPt = cms.double(100000.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(569),
            prescale_rand_mc = cms.double(10.),
            is_trigger_1mu = cms.bool(False),             
            is_trigger_2mu = cms.bool(False),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(True)                
        ),
        cms.PSet(
            path = cms.vstring("HLT_BIT_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v"),
            cone_minPt = cms.double(20.),
            cone_maxPt = cms.double(30.),
            jet_minPt = cms.double(30.),
#            pufile    = cms.FileInPath(""), ## PU file to be implemented later
            average_prescale = cms.double(2021),
            prescale_rand_mc = cms.double(25.),
            is_trigger_1mu = cms.bool(False),             
            is_trigger_2mu = cms.bool(False),             
            is_trigger_1e = cms.bool(False),             
            is_trigger_2e = cms.bool(True)             
        )
    ),
   
#    apply_offline_e_trigger_cuts_1e = cms.bool(True),  ## NOT NEEDED ANYMORE
#    apply_offline_e_trigger_cuts_1mu = cms.bool(True), ## NOT NEEDED ANYMORE

    absEtaBins_e = cms.vdouble(0., 1.479, 9.9),
    ptBins_e = cms.vdouble(15., 20., 30., 45., 65., 100000.),
    absEtaBins_mu = cms.vdouble(0., 1.479, 9.9),
    ptBins_mu = cms.vdouble(10., 15., 20., 30., 45., 65., 100000.),

    minPt_e = cms.double(15), ## NEWLY ADDED
    minPt_mu = cms.double(10), ## NEWLY ADDED

    use_HIP_mitigation_mediumMuonId = cms.bool(False),
                                      
    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    fillGenEvtHistograms = cms.bool(True),

    branchName_electrons = cms.string('selLeptons'),
    branchName_muons = cms.string('selLeptons'),
    branchName_hadTaus = cms.string('TauGood'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),

    branchName_genLeptons1 = cms.string('GenLep'),
    branchName_genLeptons2 = cms.string('GenLepFromTau'),
    branchName_genHadTaus = cms.string('GenHadTaus'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    ### NEWLY ADDED
    cfgMEtFilter = recommendedMEtFilters
)

