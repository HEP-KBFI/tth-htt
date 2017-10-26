import ROOT, array
import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend, TTree, TList
from ROOT import TMVA, TMath
import sys

print sys.argv
process =  sys.argv[1] 
 
reader = TMVA.Reader("!V")
mindr_lep1_jet = array.array('f',[0])
mindr_lep2_jet = array.array('f',[0])
avg_dr_jet = array.array('f',[0])
max_lep_eta = array.array('f',[0])
lep1_conePt = array.array('f',[0])
lep2_conePt = array.array('f',[0])
mT_lep1 = array.array('f',[0])
dr_leps = array.array('f',[0])
mTauTauVis1 = array.array('f',[0])
mTauTauVis2 = array.array('f',[0]) 
#memOutput_ttZ_LR = array.array('f',[0])
#memOutput_ttZ_Zll_LR = array.array('f',[0])
#memOutput_LR = array.array('f',[0])

reader.AddVariable("mindr_lep1_jet", mindr_lep1_jet)
reader.AddVariable("mindr_lep2_jet", mindr_lep2_jet)
reader.AddVariable("avg_dr_jet", avg_dr_jet)
reader.AddVariable("TMath::Max(TMath::Abs(lep1_eta), TMath::Abs(lep2_eta))", max_lep_eta)
reader.AddVariable("lep1_conePt", lep1_conePt)
reader.AddVariable("lep2_conePt", lep2_conePt)
reader.AddVariable("mT_lep1", mT_lep1)
reader.AddVariable("dr_leps", dr_leps)
reader.AddVariable("mTauTauVis1", mTauTauVis1)
reader.AddVariable("mTauTauVis2", mTauTauVis2)
#reader.AddVariable("memOutput_ttZ_LR", memOutput_ttZ_LR)
#reader.AddVariable("memOutput_ttZ_Zll_LR", memOutput_ttZ_Zll_LR)
#reader.AddVariable("memOutput_LR", memOutput_LR)

reader.BookMVA("testmva", "/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_15Mar2017/mvaTTHvsTTV2lss1tau_BDTG.weights.xml")

file = TFile("/home/arun/ttHAnalysis/2016/2017Feb21_fastsim_dR03mvaLoose/histograms/2lss_1tau/forBDTtraining_SS_OS/ntuple_2lss_1tau_SS_OS_all.root")
if process=="signal":
    tree = file.Get("2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/signal/evtTree")
elif process=="TTV":
    tree_ttw = file.Get("2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/TTW/evtTree")
    tree_ttz = file.Get("2lss_1tau_lepSS_sumOS_Loose/sel/evtntuple/TTZ/evtTree")
    list = TList()
    list.Add(tree_ttw)
    list.Add(tree_ttz)
    tree = TTree.MergeTrees(list)
    tree.SetName("bkgTree")

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

entries = tree.GetEntriesFast()

for jentry in xrange( entries ):
    # get the next tree in the chain and verify
    ientry = tree.LoadTree( jentry )
    if ientry < 0:
        break
    
    # copy next entry into memory and verify
    nb = tree.GetEntry( jentry )
    if nb <= 0:
        continue
    
    mindr_lep1_jet[0] = tree.mindr_lep1_jet
    mindr_lep2_jet[0] = tree.mindr_lep2_jet
    avg_dr_jet[0] = tree.avg_dr_jet
    max_lep_eta[0] = TMath.Max(TMath.Abs(tree.lep1_eta), TMath.Abs(tree.lep2_eta))
    mT_lep1[0] = tree.mT_lep1
    dr_leps[0] = tree.dr_leps
    lep1_conePt[0] = tree.lep1_conePt
    lep2_conePt[0] = tree.lep2_conePt
    mTauTauVis1[0] = tree.mTauTauVis1
    mTauTauVis2[0] = tree.mTauTauVis2
    evtWeight = tree.evtWeight
    if tree.lep1_genLepPt > 0:
        lep1_frWeight = 1.0
    else:
        lep1_frWeight = tree.lep1_fake_prob
    if tree.lep2_genLepPt > 0:
            lep2_frWeight =1.0
    else:
        lep2_frWeight =tree.lep2_fake_prob
    if tree.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree.tau_fake_prob
    evtWeight = evtWeight*lep1_frWeight*lep2_frWeight*tau_frWeight
    mvaValue = reader.EvaluateMVA("testmva")
    hist_signal.Fill(mvaValue, evtWeight)

for jentry in xrange( entries ):
    # get the next tree in the chain and verify 
    ientry = tree.LoadTree( jentry )
    if ientry < 0:
        break

    # copy next entry into memory and verify
    nb = tree.GetEntry( jentry )
    if nb <= 0:
        continue
    
    if tree.tau_isTight == 0 or tree.lep1_isTight == 0 or tree.lep2_isTight == 0:
        continue
    
    mindr_lep1_jet[0] = tree.mindr_lep1_jet
    mindr_lep2_jet[0] = tree.mindr_lep2_jet
    avg_dr_jet[0] = tree.avg_dr_jet
    max_lep_eta[0] = TMath.Max(TMath.Abs(tree.lep1_eta), TMath.Abs(tree.lep2_eta))
    mT_lep1[0] = tree.mT_lep1
    dr_leps[0] = tree.dr_leps
    lep1_conePt[0] = tree.lep1_conePt
    lep2_conePt[0] = tree.lep2_conePt
    mTauTauVis1[0] = tree.mTauTauVis1
    mTauTauVis2[0] = tree.mTauTauVis2
    evtWeight =tree.evtWeight
    if tree.lep1_genLepPt > 0:
        lep1_frWeight =1.0
    else:
        lep1_frWeight = tree.lep1_fake_prob
    if tree.lep2_genLepPt > 0:
        lep2_frWeight =1.0
    else:
        lep2_frWeight =tree.lep2_fake_prob
    if tree.tau_genTauPt > 0:
        tau_frWeight =1.0
    else:
        tau_frWeight =tree.tau_fake_prob
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

c1.SaveAs("plots/bdt_score_tmva_2lss1t_againstTTV_10Var_wCut_wfrWt_loose_vs_tight_"+process+".png")


