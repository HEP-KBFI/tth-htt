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
mindr_lep3_jet = array.array('f',[0])
avg_dr_jet = array.array('f',[0])
lep1_abs_eta = array.array('f',[0])
lep2_abs_eta = array.array('f',[0])
lep3_abs_eta = array.array('f',[0])
max_lep_eta = array.array('f',[0])
lep1_conePt = array.array('f',[0])
lep2_conePt = array.array('f',[0])
lep3_conePt = array.array('f',[0])
mindr_tau_jet = array.array('f',[0])
ptmiss = array.array('f',[0])
mT_lep1 = array.array('f',[0])
mT_lep2 = array.array('f',[0])
mT_lep3 = array.array('f',[0])
htmiss = array.array('f',[0])
dr_leps = array.array('f',[0])
tau_pt = array.array('f',[0])
tau_abs_eta = array.array('f',[0])
dr_lep1_tau = array.array('f',[0])
dr_lep2_tau = array.array('f',[0])
dr_lep3_tau = array.array('f',[0])
mTauTauVis1 = array.array('f',[0])
mTauTauVis2 = array.array('f',[0])

reader.AddVariable("nJet", nJet)
reader.AddVariable("mindr_lep1_jet", mindr_lep1_jet)
#reader.AddVariable("mindr_lep2_jet", mindr_lep2_jet)
reader.AddVariable("avg_dr_jet", avg_dr_jet)
#reader.AddVariable("lep1_abs_eta", lep1_abs_eta)
#reader.AddVariable("lep2_abs_eta", lep2_abs_eta)
#reader.AddVariable("max_lep_eta", max_lep_eta)
#reader.AddVariable("lep1_conePt", lep1_conePt)
#reader.AddVariable("lep2_conePt", lep2_conePt)
#reader.AddVariable("mindr_tau_jet", mindr_tau_jet)
#reader.AddVariable("ptmiss", ptmiss)
#reader.AddVariable("mT_lep1", mT_lep1)
#reader.AddVariable("mT_lep2", mT_lep2)
#reader.AddVariable("htmiss", htmiss)
#reader.AddVariable("dr_leps", dr_leps)
reader.AddVariable("tau_pt", tau_pt)
reader.AddVariable("tau_abs_eta", tau_abs_eta)
reader.AddVariable("dr_lep1_tau", dr_lep1_tau)
reader.AddVariable("dr_lep2_tau", dr_lep2_tau)
reader.AddVariable("dr_lep3_tau", dr_lep3_tau)
#reader.AddVariable("mTauTauVis1", mTauTauVis1)
#reader.AddVariable("mTauTauVis2", mTauTauVis2)
#reader.AddVariable("memOutput_LR", memOutput_LR)

reader.BookMVA("testmva", "training_3l1t_fastsim_30Mar2017_frWt/TMVABDT_3l_1tau_maxDepth3_8Var_frWt.xml")

file_l = TFile("/home/arun/ttHAnalysis/2016/2017Mar29_fastsim_dR03mvaVVLoose/histograms/ntuple_3l_1tau_os.root")
tree_l = file_l.Get("3l_1tau_OS_lepLoose_tauTight/sel/evtntuple/"+process+"/evtTree")
file_t = TFile("/home/arun/ttHAnalysis/2016/2017Mar29_fastsim_dR03mvaVVLoose/histograms/ntuple_3l_1tau_os.root")
tree_t = file_t.Get("3l_1tau_OS_lepLoose_tauTight/sel/evtntuple/"+process+"/evtTree")

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
    avg_dr_jet[0] = tree_l.avg_dr_jet
    tau_pt[0] = tree_l.tau_pt
    tau_abs_eta[0] = TMath.Abs(tree_l.tau_eta)
    dr_lep1_tau[0] = tree_l.dr_lep1_tau
    dr_lep2_tau[0] = tree_l.dr_lep2_tau
    dr_lep2_tau[0] = tree_l.dr_lep2_tau
    evtWeight = tree_l.evtWeight    
    if tree_l.lep1_genLepPt > 0:
        lep1_frWeight = 1.0
    else:
        lep1_frWeight = tree_l.lep1_fake_prob
    if tree_l.lep2_genLepPt > 0:
            lep2_frWeight =1.0
    else:
        lep2_frWeight =tree_l.lep2_fake_prob
    if tree_l.lep3_genLepPt > 0:
            lep3_frWeight =1.0
    else:
        lep3_frWeight =tree_l.lep3_fake_prob                          
    if tree_l.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree_l.tau_fake_prob
    evtWeight = evtWeight*lep1_frWeight*lep2_frWeight*lep3_frWeight*tau_frWeight
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
    
    if tree_t.tau_isTight == 0 or tree_t.lep1_isTight == 0 or tree_t.lep2_isTight == 0 or tree_t.lep3_isTight == 0:
        continue

    nJet[0] = tree_t.nJet
    mindr_lep1_jet[0] = tree_t.mindr_lep1_jet
    avg_dr_jet[0] = tree_t.avg_dr_jet
    tau_pt[0] = tree_t.tau_pt
    tau_abs_eta[0] = TMath.Abs(tree_t.tau_eta)
    dr_lep1_tau[0] = tree_t.dr_lep1_tau
    dr_lep2_tau[0] = tree_t.dr_lep2_tau
    dr_lep3_tau[0] = tree_t.dr_lep3_tau                          
    evtWeight = tree_t.evtWeight    
    if tree_t.lep1_genLepPt > 0:
        lep1_frWeight =1.0
    else:
        lep1_frWeight = tree_t.lep1_fake_prob
    if tree_t.lep2_genLepPt > 0:
        lep2_frWeight =1.0
    else:
        lep2_frWeight =tree_t.lep2_fake_prob
    if tree_t.lep3_genLepPt > 0:
        lep3_frWeight =1.0
    else:
        lep3_frWeight =tree_t.lep3_fake_prob
    if tree_t.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree_t.tau_fake_prob
    evtWeight = evtWeight*lep1_frWeight*lep2_frWeight*lep3_frWeight*tau_frWeight
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

c1.SaveAs("plots/bdt_score_sklearn_3l1t_8Var_wfrWt_loose_vs_tight_"+process+".png")
