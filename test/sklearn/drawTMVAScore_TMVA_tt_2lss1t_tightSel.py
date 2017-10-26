import ROOT, array
import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend, TTree
from ROOT import TMVA, TMath
import sys

print sys.argv
process =  sys.argv[1] 

reader = TMVA.Reader("!V")
nJet = array.array('f',[0])
mindr_lep1_jet = array.array('f',[0])
mindr_lep2_jet = array.array('f',[0])
avg_dr_jet = array.array('f',[0])
lep1_abs_eta = array.array('f',[0])
lep2_abs_eta = array.array('f',[0])
max_lep_eta = array.array('f',[0])
lep1_conePt = array.array('f',[0])
lep2_conePt = array.array('f',[0])
mindr_tau_jet = array.array('f',[0])
ptmiss = array.array('f',[0])
mT_lep1 = array.array('f',[0])
mT_lep2 = array.array('f',[0])
htmiss = array.array('f',[0])
dr_leps = array.array('f',[0])
tau_pt = array.array('f',[0])
tau_abs_eta = array.array('f',[0])
dr_lep1_tau = array.array('f',[0])
dr_lep2_tau = array.array('f',[0])
mTauTauVis1 = array.array('f',[0])
mTauTauVis2 = array.array('f',[0])
#memOutput_tt_LR = array.array('f',[0])
#memOutput_LR = array.array('f',[0])

reader.AddVariable("nJet", nJet)
reader.AddVariable("mindr_lep1_jet", mindr_lep1_jet)
#reader.AddVariable("mindr_lep2_jet", mindr_lep2_jet)
reader.AddVariable("avg_dr_jet", avg_dr_jet)
#reader.AddVariable("TMath::Abs(lep1_eta)", lep1_abs_eta)
#reader.AddVariable("TMath::Abs(lep2_eta)", lep2_abs_eta)
reader.AddVariable("TMath::Max(TMath::Abs(lep1_eta), TMath::Abs(lep2_eta))", max_lep_eta)
#reader.AddVariable("lep1_conePt", lep1_conePt)
reader.AddVariable("lep2_conePt", lep2_conePt)
#reader.AddVariable("mindr_tau_jet", mindr_tau_jet)
#reader.AddVariable("TMath::Min(ptmiss, 500)", ptmiss)
#reader.AddVariable("mT_lep1", mT_lep1)
#reader.AddVariable("mT_lep2", mT_lep2)
#reader.AddVariable("TMath::Min(htmiss, 500)", htmiss)
reader.AddVariable("dr_leps", dr_leps)
reader.AddVariable("tau_pt", tau_pt)
#reader.AddVariable("TMath::Abs(tau_eta)", tau_abs_eta)
reader.AddVariable("dr_lep1_tau", dr_lep1_tau)
#reader.AddVariable("dr_lep2_tau", dr_lep2_tau)
#reader.AddVariable("mTauTauVis1", mTauTauVis1)
#reader.AddVariable("mTauTauVis2", mTauTauVis2)
#reader.AddVariable("memOutput_LR", memOutput_LR)

#reader.BookMVA("testmva", "training_fastsim_v2_03Mar2017_wCuts_frWt/TMVABDT_2lss_1tau_maxDepth3_allVar_frWt.xml")
#reader.BookMVA("testmva", "/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/weights_2lss_1tau_wCuts_allVar_07Mar2017/mvaTTHvsTTbar2lss1tau_BDTG.weights.xml");
reader.BookMVA("testmva", "/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/weights_2lss_1tau_wCuts_8Var_07Mar2017/mvaTTHvsTTbar2lss1tau_BDTG.weights.xml");

file_l = TFile("/home/arun/ttHAnalysis/2016/2017Feb21_fastsim_dR03mvaLoose/histograms/2lss_1tau/forBDTtraining_SS_OS/ntuple_2lss_1tau_SS_OS_all.root")
tree_l = file_l.Get("2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/"+process+"/evtTree")
file_t = TFile("/home/arun/ttHAnalysis/2016/2017Feb21_fastsim_dR03mvaLoose/histograms/2lss_1tau/forBDTtraining_SS_OS/ntuple_2lss_1tau_SS_OS_all.root")
tree_t = file_t.Get("2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/"+process+"/evtTree")

c1 = TCanvas()
c1.SetFillColor(10)
c1.SetBorderSize(2)
c1.SetLeftMargin(0.12)
c1.SetBottomMargin(0.12)
c1.SetRightMargin(0.05)
c1.SetLogy()

histogram_base = TH1F("histogram_base", "", 100, -1., 1.)
histogram_base.SetTitle("")
histogram_base.SetStats(False)
histogram_base.SetMinimum(0.001)
histogram_base.SetMaximum(10.0)
histogram_base.GetXaxis().SetTitle("BDT Score")
histogram_base.GetYaxis().SetTitle("Events")
histogram_base.Draw("hist")

hist_signal = TH1F("hist_signal", "", 100, -1., 1.)
hist_bkg = TH1F("hist_bkg", "", 100, -1.,1.)

entries = tree_l.GetEntriesFast()

for jentry in xrange( entries ):
    # get the next tree in the chain and verify
    ientry = tree_l.LoadTree( jentry )
    if ientry < 0:
        break
    
    # copy next entry into memory and verify
    nb = tree_l.GetEntry( jentry )
    if nb <= 0:
        continue
    
    nJet[0] = tree_l.nJet
    mindr_lep1_jet[0] = tree_l.mindr_lep1_jet
    mindr_lep2_jet[0] = tree_l.mindr_lep2_jet
    avg_dr_jet[0] = tree_l.avg_dr_jet
    lep1_abs_eta[0] = TMath.Abs(tree_l.lep1_eta)
    lep2_abs_eta[0] = TMath.Abs(tree_l.lep2_eta)
    max_lep_eta[0] = TMath.Max(TMath.Abs(tree_l.lep1_eta), TMath.Abs(tree_l.lep2_eta))
    lep1_conePt[0] = tree_l.lep1_conePt
    lep2_conePt[0] = tree_l.lep2_conePt
    mindr_tau_jet[0] = tree_l.mindr_tau_jet
    ptmiss[0] = TMath.Min(tree_l.ptmiss, 500)
    mT_lep1[0] = tree_l.mT_lep1
    mT_lep2[0] = tree_l.mT_lep2
    htmiss[0] = tree_l.htmiss
    dr_leps[0] = tree_l.dr_leps
    tau_pt[0] = tree_l.tau_pt
    tau_abs_eta[0] = TMath.Abs(tree_l.tau_eta)
    dr_lep1_tau[0] = tree_l.dr_lep1_tau
    dr_lep2_tau[0] = tree_l.dr_lep2_tau
    mTauTauVis1[0] = tree_l.mTauTauVis1
    mTauTauVis2[0] = tree_l.mTauTauVis2
    '''
    memOutput_LR[0] = tree_l.memOutput_LR
    if tree_l.memOutput_type == 0:
        memOutput_tt_LR[0] = (tree_l.memOutput_ttH/TMath.Max(tree_l.memOutput_ttH + 1.e-15*tree_l.memOutput_tt, 1.e-30)) 
    else: 
        memOutput_tt_LR[0] = (tree_l.memOutput_ttH/TMath.Max(tree_l.memOutput_ttH + 1.e-12*tree_l.memOutput_tt, 1.e-30))
    '''
    evtWeight = tree_l.evtWeight    
    if tree_l.lep1_genLepPt > 0:
        lep1_frWeight = 1.0
    else:
        lep1_frWeight = tree_l.lep1_fake_prob
    if tree_l.lep2_genLepPt > 0:
            lep2_frWeight =1.0
    else:
        lep2_frWeight =tree_l.lep2_fake_prob
    if tree_l.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree_l.tau_fake_prob
    evtWeight = evtWeight*lep1_frWeight*lep2_frWeight*tau_frWeight
    mvaValue = reader.EvaluateMVA("testmva")
    hist_signal.Fill(mvaValue, evtWeight)

entries = tree_t.GetEntriesFast()
for jentry in xrange( entries ):
    # get the next tree in the chain and verify                                                                                                                                            
    ientry = tree_t.LoadTree( jentry )
    if ientry < 0:
        break

    # copy next entry into memory and verify                                                                                                                                               
    nb = tree_t.GetEntry( jentry )
    if nb <= 0:
        continue
    
    if tree_t.tau_isTight == 0 or tree_t.lep1_isTight == 0 or tree_t.lep2_isTight == 0:
        continue

    nJet[0] = tree_t.nJet
    mindr_lep1_jet[0] = tree_t.mindr_lep1_jet
    mindr_lep2_jet[0] = tree_t.mindr_lep2_jet
    avg_dr_jet[0] = tree_t.avg_dr_jet
    lep1_abs_eta[0] = TMath.Abs(tree_t.lep1_eta)
    lep2_abs_eta[0] = TMath.Abs(tree_t.lep2_eta)
    max_lep_eta[0] = TMath.Max(TMath.Abs(tree_t.lep1_eta), TMath.Abs(tree_t.lep2_eta))
    lep1_conePt[0] = tree_t.lep1_conePt
    lep2_conePt[0] = tree_t.lep2_conePt
    mindr_tau_jet[0] = tree_t.mindr_tau_jet
    ptmiss[0] = TMath.Min(tree_t.ptmiss, 500)
    mT_lep1[0] = tree_t.mT_lep1
    mT_lep2[0] = tree_t.mT_lep2
    htmiss[0] = tree_t.htmiss
    dr_leps[0] = tree_t.dr_leps
    tau_pt[0] = tree_t.tau_pt
    tau_abs_eta[0] = TMath.Abs(tree_t.tau_eta)
    dr_lep1_tau[0] = tree_t.dr_lep1_tau
    dr_lep2_tau[0] = tree_t.dr_lep2_tau
    mTauTauVis1[0] = tree_t.mTauTauVis1
    mTauTauVis2[0] = tree_t.mTauTauVis2
    '''
    memOutput_LR[0] = tree_t.memOutput_LR
    if tree_t.memOutput_type == 0:
        memOutput_tt_LR[0] = (tree_t.memOutput_ttH/TMath.Max(tree_t.memOutput_ttH + 1.e-15*tree_t.memOutput_tt, 1.e-30))
    else:
        memOutput_tt_LR[0] = (tree_t.memOutput_ttH/TMath.Max(tree_t.memOutput_ttH + 1.e-12*tree_t.memOutput_tt, 1.e-30))
    '''
    evtWeight = tree_t.evtWeight    
    if tree_t.lep1_genLepPt > 0:
        lep1_frWeight =1.0
    else:
        lep1_frWeight = tree_t.lep1_fake_prob
    if tree_t.lep2_genLepPt > 0:
        lep2_frWeight =1.0
    else:
        lep2_frWeight =tree_t.lep2_fake_prob
    if tree_t.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree_t.tau_fake_prob
    evtWeight = evtWeight*lep1_frWeight*lep2_frWeight*tau_frWeight
    mvaValue = reader.EvaluateMVA("testmva")
    hist_bkg.Fill(mvaValue, evtWeight)
    

hist_signal.SetLineColor(2)
hist_bkg.SetLineColor(4)
hist_signal.SetFillColor(2)
hist_bkg.SetFillColor(4)
hist_signal.SetFillStyle(3004)
hist_bkg.SetFillStyle(3005)

leg = TLegend(0.2, 0.65, 0.5, 0.9)
leg.SetBorderSize(0)
leg.SetFillColor(10)
leg.SetLineColor(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.04)
leg.SetTextFont(42)

leg.AddEntry(hist_signal, "loose selection", "l")
leg.AddEntry(hist_bkg, "tight selection", "l")

hist_signal.DrawNormalized("histsame")
hist_bkg.DrawNormalized("histsame")
leg.Draw()

#c1.SaveAs("plots/bdt_score_sklearn_2lss1t_allVar_wCut_wfrWt_loose_vs_tight_"+process+".png")
#c1.SaveAs("plots/bdt_score_tmva_2lss1t_allVar_wCut_wfrWt_loose_vs_tight_"+process+".png")  
c1.SaveAs("plots/bdt_score_tmva_2lss1t_8Var_wCut_wfrWt_loose_vs_tight_"+process+".png")
