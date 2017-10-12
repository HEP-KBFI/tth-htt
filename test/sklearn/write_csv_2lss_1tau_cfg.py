import FWCore.ParameterSet.Config as cms

process = cms.PSet()

sampleName = 'signal'
#sampleName = 'TT'
#sampleName = 'TTW'
#sampleName = 'TTZ'
#sampleName = 'EWK'

outfile = '2lss_1tau_%s_fastsim_28Mar2017.csv' %sampleName
#inputTree = '2lss_1tau_SS_Loose/sel/evtntuple/%s/evtTree' %sampleName
inputTree = '2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/%s/evtTree' %sampleName

process.fwliteInput = cms.PSet(
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Jan06_dR03mvaVVLoose/histograms/histograms_harvested_stage1_2lss_1tau.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Jan30v1/histograms/2lss_1tau/forBDTtraining_SS/ntuple_2lss_1tau_all.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Feb14/histograms/2lss_1tau/forBDTtraining_SS/ntuple_2lss_1tau_all.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Feb21_fastsim_dR03mvaLoose/histograms/2lss_1tau/forBDTtraining_SS_OS/ntuple_2lss_1tau_SS_OS_all.root"),
    fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Mar27_dr03mvaLoose/histograms/ntuple_2lss_1tau_ss_os_all.root"),

    ##maxEvents = cms.int32(100000),
    maxEvents = cms.int32(-1),
      
    outputEvery = cms.uint32(10000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string(outfile)
)

process.write_csv = cms.PSet(    

    treeName = cms.string(inputTree),
    #preselection = cms.string("memOutput_errorFlag==0"),
    preselection = cms.string("memOutput_errorFlag==0 && (mindr_lep1_jet>0.4) && (mindr_lep2_jet>0.4) && (dr_leps>0.3)"),
    branches_to_write = cms.PSet(
        # list of branches in input Ntuple that will be written to CSV output file
        max_lep_eta=cms.string('TMath::Max(TMath::Abs(lep1_eta), TMath::Abs(lep2_eta))/Formula->F'),
        ptmiss=cms.string('TMath::Min(ptmiss, 500)/Formula->F'),
        htmiss=cms.string('TMath::Min(htmiss, 500)/Formula->F'),
        nJet=cms.string('nJet/I'),
        mindr_lep1_jet=cms.string('mindr_lep1_jet/F'),
        mindr_lep2_jet=cms.string('mindr_lep2_jet/F'),
        avg_dr_jet=cms.string('avg_dr_jet/F'),
        lep1_pt=cms.string('lep1_pt/F'),
        lep1_abs_eta=cms.string('TMath::Abs(lep1_eta)/Formula->F'),
        lep2_pt=cms.string('lep2_pt/F'),
        lep2_abs_eta=cms.string('TMath::Abs(lep2_eta)/Formula->F'),
        lep1_conePt=cms.string('lep1_conePt/F'), 
        lep2_conePt=cms.string('lep2_conePt/F'),
        mindr_tau_jet=cms.string('mindr_tau_jet/F'),
        #ptmiss=cms.string('ptmiss/F'),
        mT_lep1=cms.string('mT_lep1/F'),
        mT_lep2=cms.string('mT_lep2/F'),
        #htmiss=cms.string('htmiss/F'),
        dr_leps=cms.string('dr_leps/F'),
        tau_pt=cms.string('tau_pt/F'),
        tau_abs_eta=cms.string('TMath::Abs(tau_eta)/Formula->F'),
        dr_lep1_tau=cms.string('dr_lep1_tau/F'),
        dr_lep2_tau=cms.string('dr_lep2_tau/F'),
        mTauTauVis1=cms.string('mTauTauVis1/F'),
        mTauTauVis2=cms.string('mTauTauVis2/F'),
        lep1_tth_mva=cms.string('lep1_tth_mva/F'),
        lep2_tth_mva=cms.string('lep2_tth_mva/F'),
        nBJetLoose=cms.string('nBJetLoose/I'),
        nBJetMedium=cms.string('nBJetMedium/I'),
        tau_mva=cms.string('tau_mva/F'),
        memOutput_isValid=cms.string('memOutput_isValid/F'),
        #memOutput_errorFlag=cms.string('memOutput_errorFlag/F'),
        memOutput_type=cms.string('memOutput_type/F'),
        #memOutput_ttH=cms.string('memOutput_ttH/F'),
        #memOutput_ttZ=cms.string('memOutput_ttZ/F'),
        #memOutput_ttZ_Zll=cms.string('memOutput_ttZ_Zll/F'),
        #memOutput_tt=cms.string('memOutput_tt/F'),
        memOutput_LR=cms.string('memOutput_LR/F'),
        log_memOutput_ttH=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttH))/Formula->F'),
        log_memOutput_ttZ=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttZ))/Formula->F'),
        log_memOutput_ttZ_Zll=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttZ_Zll))/Formula->F'),
        log_memOutput_tt=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_tt))/Formula->F'),
        memOutput_tt_LR=cms.string('(memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 1.e-15*memOutput_tt)) : (memOutput_ttH/(memOutput_ttH + 1.e-12*memOutput_tt)))/Formula->F'),
        memOutput_ttZ_LR=cms.string('(memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 0.5*memOutput_ttZ)) : (memOutput_ttH/(memOutput_ttH + 0.05*memOutput_ttZ)))/Formula->F'),
        memOutput_ttZ_Zll_LR=cms.string('(memOutput_type == 0 ? (memOutput_ttH/(memOutput_ttH + 1.0*memOutput_ttZ_Zll)) : (memOutput_ttH/(memOutput_ttH + 0.1*memOutput_ttZ_Zll)))/Formula->F'),
        lep1_frWeight=cms.string('(lep1_genLepPt > 0 ? 1.0 : lep1_fake_prob)/Formula->F'),
        lep2_frWeight=cms.string('(lep2_genLepPt > 0 ? 1.0 : lep2_fake_prob)/Formula->F'),
        tau_frWeight=cms.string('(tau_genTauPt > 0 ? 1.0 : tau_fake_prob)/Formula->F'),
        lumiScale=cms.string('lumiScale/F'), 
        genWeight=cms.string('genWeight/F'), 
        evtWeight=cms.string('evtWeight/F'),
        lep1_isTight=cms.string('lep1_isTight/I'),
        lep2_isTight=cms.string('lep2_isTight/I'),
        tau_isTight=cms.string('tau_isTight/I')
        )
)
