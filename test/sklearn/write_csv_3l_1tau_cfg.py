import FWCore.ParameterSet.Config as cms

process = cms.PSet()

#sampleName = 'signal'
#sampleName = 'TT'
#sampleName = 'TTW'
sampleName = 'TTZ'
#sampleName = 'EWK'

outfile = '3l_1tau_%s_07Apr2017.csv' %sampleName
inputTree = '3l_1tau_OS_lepLoose_tauTight/sel/evtntuple/%s/evtTree' %sampleName

process.fwliteInput = cms.PSet(
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Feb03v1/3l1tau/histograms_3l_1tau_all.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Feb07/histograms/3l_1tau/forBDTtraining_OS/histograms_3l_1tau_all.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Mar23v2_fastsim_dR03mvaLoose/histograms/3l_1tau/forBDTtraining_OS/ntuple_3l_1tau_os_all.root"),
    #fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Mar29_fastsim_dR03mvaVVLoose/histograms/ntuple_3l_1tau_os.root"),
    fileNames = cms.vstring("/home/arun/ttHAnalysis/2016/2017Apr06_fastsim_dR03mvaVVLoose/histograms/ntuple_3l_1tau_os.root"),
    
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
    branches_to_write = cms.PSet(
        # list of branches in input Ntuple that will be written to CSV output file
        ptmiss=cms.string('TMath::Min(ptmiss, 500)/Formula->F'),
        htmiss=cms.string('TMath::Min(htmiss, 500)/Formula->F'),
        nJet=cms.string('nJet/I'),
        mindr_lep1_jet=cms.string('mindr_lep1_jet/F'),
        mindr_lep2_jet=cms.string('mindr_lep2_jet/F'),
        mindr_lep3_jet=cms.string('mindr_lep3_jet/F'),
        avg_dr_jet=cms.string('avg_dr_jet/F'),
        lep1_pt=cms.string('lep1_pt/F'),
        lep1_abs_eta=cms.string('TMath::Abs(lep1_eta)/Formula->F'),
        lep2_pt=cms.string('lep2_pt/F'),
        lep2_abs_eta=cms.string('TMath::Abs(lep2_eta)/Formula->F'),
        lep3_pt=cms.string('lep3_pt/F'),
        lep3_abs_eta=cms.string('TMath::Abs(lep3_eta)/Formula->F'),
        lep1_conePt=cms.string('lep1_conePt/F'), 
        lep2_conePt=cms.string('lep2_conePt/F'),
        lep3_conePt=cms.string('lep3_conePt/F'),
        mindr_tau_jet=cms.string('mindr_tau_jet/F'),
        mT_lep1=cms.string('mT_lep1/F'),
        mT_lep2=cms.string('mT_lep2/F'),
        mT_lep3=cms.string('mT_lep3/F'),
        dr_leps=cms.string('dr_leps/F'),
        tau_pt=cms.string('tau_pt/F'),
        tau_abs_eta=cms.string('TMath::Abs(tau_eta)/Formula->F'),
        dr_lep1_tau=cms.string('dr_lep1_tau/F'),
        dr_lep2_tau=cms.string('dr_lep2_tau/F'),
        dr_lep3_tau=cms.string('dr_lep3_tau/F'),
        mTauTauVis1=cms.string('mTauTauVis1/F'),
        mTauTauVis2=cms.string('mTauTauVis2/F'),
        lep1_tth_mva=cms.string('lep1_tth_mva/F'),
        lep2_tth_mva=cms.string('lep2_tth_mva/F'),
        lep3_tth_mva=cms.string('lep3_tth_mva/F'),
        nBJetLoose=cms.string('nBJetLoose/I'),
        nBJetMedium=cms.string('nBJetMedium/I'),
        tau_mva=cms.string('tau_mva/F'),
        #memOutput_isValid=cms.string('memOutput_isValid/F'),
        #memOutput_errorFlag=cms.string('memOutput_errorFlag/F'),
        #memOutput_ttH=cms.string('memOutput_ttH/F'),
        #memOutput_ttZ=cms.string('memOutput_ttZ/F'),
        #memOutput_ttZ_Zll=cms.string('memOutput_ttZ_Zll/F'),
        #memOutput_LR=cms.string('memOutput_LR/F'),
        #log_memOutput_ttH=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttH))/Formula->F'),
        #log_memOutput_ttZ=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttZ))/Formula->F'),
        #log_memOutput_ttH_Hww=cms.string('TMath::Log(TMath::Max(1.e-30, memOutput_ttH_Hww))/Formula->F'),
        mvaOutput_3l_ttV=cms.string('mvaOutput_3l_ttV/F'),
        mvaOutput_3l_ttbar=cms.string('mvaOutput_3l_ttbar/F'),
        mvaDiscr_3l=cms.string('mvaDiscr_3l/F'),
        lep1_frWeight=cms.string('(lep1_genLepPt > 0 ? 1.0 : lep1_fake_prob)/Formula->F'),
        lep2_frWeight=cms.string('(lep2_genLepPt > 0 ? 1.0 : lep2_fake_prob)/Formula->F'),
        lep3_frWeight=cms.string('(lep3_genLepPt > 0 ? 1.0 : lep3_fake_prob)/Formula->F'),
        tau_frWeight=cms.string('(tau_genTauPt > 0 ? 1.0 : tau_fake_prob)/Formula->F'),
        lumiScale=cms.string('lumiScale/F'), 
        genWeight=cms.string('genWeight/F'), 
        evtWeight=cms.string('evtWeight/F')       
        )
)
