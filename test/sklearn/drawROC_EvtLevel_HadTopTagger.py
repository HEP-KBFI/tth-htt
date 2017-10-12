import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend, TTree, TList
from ROOT import TMVA, TMath
import sys

print sys.argv
process =  sys.argv[1] 

reader = TMVA.Reader("!V")
CSV_Wj1 = array.array('f',[0])
CSV_b = array.array('f',[0])
dR_Wj1Wj2 = array.array('f',[0])
dR_bW = array.array('f',[0])
m_Wj1Wj2 = array.array('f',[0])
nllKinFit = array.array('f',[0])
pT_Wj2 = array.array('f',[0])
pT_bWj1Wj2 = array.array('f',[0])
qg_Wj2 = array.array('f',[0])
bWj1Wj2_isGenMatched = array.array('f',[0])
run = array.array('f',[0])
lumi = array.array('f',[0])
evt = array.array('f',[0])

reader.AddVariable("CSV_Wj1", CSV_Wj1)
reader.AddVariable("CSV_b", CSV_b)
reader.AddVariable("dR_Wj1Wj2", dR_Wj1Wj2)
reader.AddVariable("dR_bW", dR_bW)
reader.AddVariable("m_Wj1Wj2", m_Wj1Wj2)
reader.AddVariable("nllKinFit", nllKinFit)
reader.AddVariable("pT_Wj2", pT_Wj2)
reader.AddVariable("pT_bWj1Wj2", pT_bWj1Wj2)
reader.AddVariable("qg_Wj2", qg_Wj2)

#reader.BookMVA("testmva", "Results/TMVABDT_hadTopTagger_maxDepth3_9Var_ttH.xml")
reader.BookMVA("testmva", "Results_10Oct2017/TMVABDT_hadTopTagger_maxDepth3_9Var_ps75.xml")

if process=="signal":
    file = TFile("/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim.root")
    tree = file.Get("analyze_hadTopTagger/evtntuple/signal/evtTree")
elif process=="TT":
    file = TFile("/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim.root")
    tree = file.Get("analyze_hadTopTagger/evtntuple/TT/evtTree")
elif process=="TTV":
    file1 = TFile("/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTWJetsToLNu_fastsim.root")
    tree_ttw = file1.Get("analyze_hadTopTagger/evtntuple/TTW/evtTree")
    file2 = TFile("/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTZToLLNuNu_fastsim.root")
    tree_ttz = file2.Get("analyze_hadTopTagger/evtntuple/TTZ/evtTree")
    list = TList()
    list.Add(tree_ttw)
    list.Add(tree_ttz)
    tree = TTree.MergeTrees(list)
    tree.SetName("bkgTree")
elif process=="All":
    file1 = TFile("/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim.root")
    tree_tth = file1.Get("analyze_hadTopTagger/evtntuple/signal/evtTree")
    file2 = TFile("/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim.root")
    tree_tt = file2.Get("analyze_hadTopTagger/evtntuple/TT/evtTree")
    file3 = TFile("/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTWJetsToLNu_fastsim.root")
    tree_ttw = file3.Get("analyze_hadTopTagger/evtntuple/TTW/evtTree")
    file4 = TFile("/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTZToLLNuNu_fastsim.root")
    tree_ttz = file4.Get("analyze_hadTopTagger/evtntuple/TTZ/evtTree")
    list = TList()
    list.Add(tree_tth)
    list.Add(tree_tt)
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

histogram_base = TH1F("histogram_base", "", 1000, -1., 1.)
histogram_base.SetTitle("")
histogram_base.SetStats(False)
histogram_base.SetMinimum(0.001)
histogram_base.SetMaximum(10.0)
histogram_base.GetXaxis().SetTitle("BDT Score")
histogram_base.GetYaxis().SetTitle("Events")
#histogram_base.Draw("hist")

hist_signal = TH1F("hist_signal", "", 1000, -1., 1.)
hist_bkg = TH1F("hist_bkg", "", 1000, -1.,1.)

entries = tree.GetEntriesFast()

last_run = -1
last_lumi = -1
last_evt = -1
last_bdtvalue = -100.0
last_genMatch = -1

#if entries > 10000000: entries = 10000000

for jentry in xrange( entries ):
    # get the next tree in the chain and verify
    ientry = tree.LoadTree( jentry )
    if ientry < 0:
        break
    
    if jentry%1000000 == 0: print "proceesing entries: ", jentry
    # copy next entry into memory and verify
    nb = tree.GetEntry( jentry )
    if nb <= 0:
        continue
    if tree.CSV_b < 0.244:
           continue
    run[0] = tree.run
    evt[0] = tree.evt
    lumi[0] = tree.lumi
    CSV_Wj1[0] = tree.CSV_Wj1
    CSV_b[0] = tree.CSV_b
    dR_Wj1Wj2[0] = tree.dR_Wj1Wj2
    dR_bW[0] = tree.dR_bW
    m_Wj1Wj2[0] = tree.m_Wj1Wj2
    nllKinFit[0] = tree.nllKinFit
    pT_Wj2[0] = tree.pT_Wj2
    pT_bWj1Wj2[0] = tree.pT_bWj1Wj2
    qg_Wj2[0] = tree.qg_Wj2
    bWj1Wj2_isGenMatched[0] = tree.bWj1Wj2_isGenMatched
    mvaValue = reader.EvaluateMVA("testmva")
    if tree.run == last_run and tree.lumi == last_lumi and tree.evt == last_evt:
        if mvaValue > last_bdtvalue:
            last_bdtvalue = mvaValue
            last_genMatch = tree.bWj1Wj2_isGenMatched
    else:
        #First, Fill the mva value for the last event
        if last_bdtvalue != -100.0:
            if last_genMatch > 0.5:
                hist_signal.Fill(last_bdtvalue)
            else:
                hist_bkg.Fill(last_bdtvalue)
        #Then, reset the run, lumi, evt for the next block    
        last_run = tree.run
        last_lumi = tree.lumi
        last_evt = tree.evt
        last_bdtvalue = mvaValue
        last_genMatch = tree.bWj1Wj2_isGenMatched
        
print "No. of signal ", hist_signal.Integral(), " No. of bkg ", hist_bkg.Integral()
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

leg.AddEntry(hist_signal, "signal", "l")
leg.AddEntry(hist_bkg, "background", "l")

histogram_base.Draw("hist")
hist_signal.DrawNormalized("histsame")
hist_bkg.DrawNormalized("histsame")
leg.Draw()

c1.SaveAs("plots/bdt_score_evtLevel_hadTopTagger_"+process+"_opt1.png")
c1.SaveAs("plots/bdt_score_evtLevel_hadTopTagger_"+process+"_opt1.C")

hist_eff_signal = TH1F("hist_eff_signal", "", 1000, -1., 1.)
hist_eff_bkg = TH1F("hist_eff_bkg", "", 1000, -1., 1.)
eff_signal = array.array( 'd' )
eff_bkg = array.array( 'd' )

for x in range(1, 1001):
    n_sig = 0
    n_bkg = 0
    for y in range(x, 1001):
        n_sig += hist_signal.GetBinContent(y)
        n_bkg += hist_bkg.GetBinContent(y)
    n_sig = n_sig/hist_signal.Integral()
    n_bkg = n_bkg/hist_bkg.Integral()
    hist_eff_signal.SetBinContent(x, n_sig)
    hist_eff_bkg.SetBinContent(x, n_bkg)
    eff_signal.append(n_sig)
    eff_bkg.append(n_bkg)

hist_eff_signal.SetLineColor(2)
hist_eff_bkg.SetLineColor(4)
#hist_eff_signal.SetFillColor(2)
#hist_eff_bkg.SetFillColor(4)

histogram_base.GetXaxis().SetTitle("Cut on BDT Score")
histogram_base.GetYaxis().SetTitle("Efficiency")
histogram_base.Draw("hist")
hist_eff_signal.Draw("same")
hist_eff_bkg.Draw("same")
leg.Draw()

c1.SaveAs("plots/eff_evtLevel_hadTopTagger_"+process+"_opt1.png")
c1.SaveAs("plots/eff_evtLevel_hadTopTagger_"+process+"_opt1.C")

hist_roc = TGraph(1000, eff_signal, eff_bkg)
hist_roc.SetTitle("")
hist_roc.SetMinimum(0.001)
hist_roc.SetMaximum(10.0)
hist_roc.GetXaxis().SetTitle("Signal Efficiency")
hist_roc.GetYaxis().SetTitle("Background Efficiency")

hist_roc.Draw("AL")

c1.SaveAs("plots/roc_evtLevel_hadTopTagger_"+process+"_opt1.png")
c1.SaveAs("plots/roc_evtLevel_hadTopTagger_"+process+"_opt1.C")
