from ROOT import TFile, TChain, TTree, TString, TH1, TH2, TH1F, TGraph, TAxis, TCanvas, TLegend, TMath, TROOT, TStyle, TPad, TLatex, TGaxis, TLine
import ROOT
import math
import os 
import errno

#categories = ["1l2tau_SR", "1l2tau_Fake", "2lSS1tau_Flip", "2lSS1tau_SR", "2lSS1tau_Fake", "3l1tau_SR", "3l1tau_Fake"]
categories = ["1l2tau_SR"]#, "2lSS1tau_SR", "3l1tau_SR"]

samples = {}
samples["ttH"] = "ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8"
samples["ttbar"] = "TT_TuneCUETP8M1_13TeV-powheg-pythia8"

groupnames = ["Tallinn", "LLR", "Cornell", "Notre Dame"]
groupnames = ["Tallinn", "Notre Dame"]
groups = {}
for name in groupnames:
  groups[name] = {}
  groups[name]["inputPath"] = "/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples"
  groups[name]["inputFiles"] = {}
  groups[name]["treePrefix"] = "syncTree"

groups["Tallinn"]["inputFiles"]["ttH"] = "sync_ntuples_split.root"
#groups["LLR"]["inputFiles"]["ttH"] = "syncNtuple_event_ttH_80X_Summer16.root"
#groups["Cornell"]["inputFiles"]["ttH"] = "syncNtuple_event.root"
groups["Notre Dame"]["inputFiles"]["ttH"] = "sync_ntuple_m17_1l_2tau.root"

#groups["Tallinn"]["inputPath"]["ttH"] = "sync_ntuples_split.root"
#groups["LLR"]["inputPath"]["ttH"] = "syncNtuple_event_ttH_80X.root"
#groups["Cornell"]["inputPath"]["ttH"] = "syncNtuple_event.root"
#groups["Notre Dame"]["inputPath"]["ttH"] = "sync_ntuple.root"
#std::string inputFilePath_test = "/afs/cern.ch/work/t/tstreble/public/syncNtuple_ttH_Htautau/";
#std::string inputFilePath_test = "/afs/cern.ch/work/t/tstreble/public/syncNtuple_ttH_Htautau/";
#std::string inputFilePath_test3 = "/afs/cern.ch/user/m/matze/public/ttH/";

variables = [("n_presel_mu", "I", "", 9, -0.5, 8.5),
  ("n_presel_ele", "I", "", 9, -0.5, 8.5),
  ("n_presel_tau", "I", "", 13, -0.5, 12.5),
  ("n_presel_jet", "I", "", 20, -0.5, 19.5),
  ("mu0_charge", "I", "n_presel_mu >= 1", 3, -1.5, +1.5),
  ("mu0_jetNDauChargedMVASel", "F", "n_presel_mu >= 1", 20, -0.5, 19.5),
  ("mu0_jetPtRel", "F", "n_presel_mu >= 1", 100, -0.01, 10.),
  ("mu0_miniIsoNeutral", "F", "n_presel_mu >= 1", 20, -0.01, 2.),
  ("mu0_miniIsoCharged", "F", "n_presel_mu >= 1", 20, -0.01, 2.),
  ("mu0_E", "F", "n_presel_mu >= 1", 100, 0., 250.),
  ("mu0_jetPtRatio", "F", "n_presel_mu >= 1", 100, -0.01, 2.),
  ("mu0_leptonMVA", "F", "n_presel_mu >= 1", 100, -1.1, +1.1),
  ("mu0_jetCSV", "F", "n_presel_mu >= 1", 100, -0.01, +1.01),
  ("mu0_segmentCompatibility", "F", "n_presel_mu >= 1", 50, -0.01, +1.01),
  ("mu0_phi", "F", "n_presel_mu >= 1", 36, -math.pi, +math.pi),
  ("mu0_sip3D", "F", "n_presel_mu >= 1", 100, 0., +10.),
  ("mu0_pt", "F", "n_presel_mu >= 1", 100, 0., 250.),
  ("mu0_miniRelIso", "F", "n_presel_mu >= 1", 100, -0.01, 0.5),
  ("mu0_dxy", "F", "n_presel_mu >= 1", 100, -0.02, +0.02),
  ("mu0_eta", "F", "n_presel_mu >= 1", 100, -3., +3.),
  ("mu0_dz", "F", "n_presel_mu >= 1", 100, -0.5, +0.5),
  ("mu1_charge", "I", "n_presel_mu >= 2", 3, -1.5, +1.5),
  ("mu1_jetNDauChargedMVASel", "F", "n_presel_mu >= 2", 20, -0.5, 19.5),
  ("mu1_jetPtRel", "F", "n_presel_mu >= 2", 100, -0.01, 10.),
  ("mu1_miniIsoNeutral", "F", "n_presel_mu >= 2", 100, -0.01, 2.),
  ("mu1_miniIsoCharged", "F", "n_presel_mu >= 2", 100, -0.01, 2.),
  ("mu1_E", "F", "n_presel_mu >= 2", 100, 0., 250.),
  ("mu1_jetPtRatio", "F", "n_presel_mu >= 2", 100, -0.01, 2.),
  ("mu1_leptonMVA", "F", "n_presel_mu >= 2", 100, -1.1, +1.1),
  ("mu1_jetCSV", "F", "n_presel_mu >= 2", 100, -0.01, +1.01),
  ("mu1_segmentCompatibility", "F", "n_presel_mu >= 2", 100, -0.01, +1.01),
  ("mu1_phi", "F", "n_presel_mu >= 2", 36, -math.pi, +math.pi),
  ("mu1_sip3D", "F", "n_presel_mu >= 2", 100, 0., +10.),
  ("mu1_pt", "F", "n_presel_mu >= 2", 100, 0., 250.),
  ("mu1_miniRelIso", "F", "n_presel_mu >= 2", 100, -0.01, 0.5),
  ("mu1_dxy", "F", "n_presel_mu >= 2", 100, -0.02, +0.02),
  ("mu1_eta", "F", "n_presel_mu >= 2", 100, -3., +3.),
  ("mu1_dz", "F", "n_presel_mu >= 2", 100, -0.5, +0.5),
  ("ele0_ntMVAeleID", "F", "n_presel_ele >= 1", 100, -1.5, +1.5),
  ("ele0_charge", "F", "n_presel_ele >= 1", 3, -1.5, +1.5),
  ("ele0_jetNDauChargedMVASel", "F", "n_presel_ele >= 1", 20, -0.5, +19.5),
  ("ele0_jetPtRel", "F", "n_presel_ele >= 1", 100, -0.01, 10.),
  ("ele0_miniIsoNeutral", "F", "n_presel_ele >= 1", 100, -0.01, 2.),
  ("ele0_miniIsoCharged", "F", "n_presel_ele >= 1", 100, -0.01, 2.),
  ("ele0_E", "F", "n_presel_ele >= 1", 100, 0., 250.),
  ("ele0_jetPtRatio", "F", "n_presel_ele >= 1", 100, -0.01, 2.),
  ("ele0_leptonMVA", "F", "n_presel_ele >= 1", 100, -1.1, +1.1),
  ("ele0_jetCSV", "F", "n_presel_ele >= 1", 100, -0.01, +1.01),
  ("ele0_phi", "F", "n_presel_ele >= 1", 36, -math.pi, +math.pi),
  ("ele0_sip3D", "F", "n_presel_ele >= 1", 100, 0., +10.),
  ("ele0_pt", "F", "n_presel_ele >= 1", 100, 0., 250.),
  ("ele0_miniRelIso", "F", "n_presel_ele >= 1", 100, -0.01, 0.5),
  ("ele0_dxy", "F", "n_presel_ele >= 1", 100, -0.02, +0.02),
  ("ele0_eta", "F", "n_presel_ele >= 1", 100, -3.0, +3.0),
  ("ele0_dz", "F", "n_presel_ele >= 1", 100, -0.5, +0.5),
  ("ele1_ntMVAeleID", "F", "n_presel_ele >= 2", 100, -1.5, +1.5),
  ("ele1_charge", "F", "n_presel_ele >= 2", 3, -1.5, +1.5),
  ("ele1_jetNDauChargedMVASel", "F", "n_presel_ele >= 2", 20, -0.5, +19.5),
  ("ele1_jetPtRel", "F", "n_presel_ele >= 2", 100, -0.01, 10.),
  ("ele1_miniIsoNeutral", "F", "n_presel_ele >= 2", 100, -0.01, 2.),
  ("ele1_miniIsoCharged", "F", "n_presel_ele >= 2", 100, -0.01, 2.),
  ("ele1_E", "F", "n_presel_ele >= 2", 100, 0., 250.),
  ("ele1_jetPtRatio", "F", "n_presel_ele >= 2", 100, -0.01, 2.),
  ("ele1_leptonMVA", "F", "n_presel_ele >= 2", 100, -1.1, +1.1),
  ("ele1_jetCSV", "F", "n_presel_ele >= 2", 100, -0.01, +1.01),
  ("ele1_phi", "F", "n_presel_ele >= 2", 36, -math.pi, +math.pi),
  ("ele1_sip3D", "F", "n_presel_ele >= 2", 100, 0., +10.),
  ("ele1_pt", "F", "n_presel_ele >= 2", 100, 0., 250.),
  ("ele1_miniRelIso", "F", "n_presel_ele >= 2", 100, -0.01, 0.5),
  ("ele1_dxy", "F", "n_presel_ele >= 2", 100, -0.02, +0.02),
  ("ele1_eta", "F", "n_presel_ele >= 2", 100, -3.0, +3.0),
  ("ele1_dz", "F", "n_presel_ele >= 2", 100, -0.5, +0.5),
  ("tau0_againstElectronMediumMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_againstElectronLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_againstElectronVLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_againstMuonLoose3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_againstElectronTightMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_decayModeFindingOldDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_againstMuonTight3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_decayModeFindingNewDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_charge", "I", "n_presel_tau >= 1", 3, -1.5, +1.5),
  ("tau0_byTightCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 1", 2, -0.5, +1.5),
  ("tau0_byCombinedIsolationDeltaBetaCorr3Hits", "F", "n_presel_tau >= 1", 100, -0.01, 10.),
  ("tau0_dz", "F", "n_presel_tau >= 1", 100, -0.2, +0.2),
  ("tau0_dxy", "F", "n_presel_tau >= 1", 100, -0.05, +0.05),
  ("tau0_pt", "F", "n_presel_tau >= 1", 100, 0., 250.),
  ("tau0_eta", "F", "n_presel_tau >= 1", 100, -3., +3.),
  ("tau0_phi", "F", "n_presel_tau >= 1", 36, -math.pi, +math.pi),
  ("tau0_E", "F", "n_presel_tau >= 1", 100, 0., 250.),
  ("tau1_againstElectronMediumMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_againstElectronLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_againstElectronVLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_againstMuonLoose3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_againstElectronTightMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_decayModeFindingOldDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_againstMuonTight3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_decayModeFindingNewDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_charge", "I", "n_presel_tau >= 2", 3, -1.5, +1.5),
  ("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 2", 2, -0.5, +1.5),
  ("tau1_byCombinedIsolationDeltaBetaCorr3Hits", "F", "n_presel_tau >= 2", 100, -0.01, 10.),
  ("tau1_dz", "F", "n_presel_tau >= 2", 100, -0.2, +0.2),
  ("tau1_dxy", "F", "n_presel_tau >= 2", 100, -0.05, +0.05),
  ("tau1_pt", "F", "n_presel_tau >= 2", 100, 0., 250.),
  ("tau1_eta", "F", "n_presel_tau >= 2", 100, -3., +3.),
  ("tau1_phi", "F", "n_presel_tau >= 2", 36, -math.pi, +math.pi),
  ("tau1_E", "F", "n_presel_tau >= 2", 100, 0., 250.)			      ,
  ("jet0_CSV", "F", "n_presel_jet >= 1", 100, -0.01, +1.01),
  ("jet0_pt", "F", "n_presel_jet >= 1", 100, 0., 250.),
  ("jet0_eta", "F", "n_presel_jet >= 1", 100, -5.5, +5.5),
  ("jet0_phi", "F", "n_presel_jet >= 1", 36, -math.pi, +math.pi),
  ("jet0_E", "F", "n_presel_jet >= 1", 100, 0., 250.),
  ("jet1_CSV", "F", "n_presel_jet >= 2", 100, -0.01, +1.01),
  ("jet1_pt", "F", "n_presel_jet >= 2", 100, 0., 250.),
  ("jet1_eta", "F", "n_presel_jet >= 2", 100, -5.5, +5.5),
  ("jet1_phi", "F", "n_presel_jet >= 2", 36, -math.pi, +math.pi),
  ("jet1_E", "F", "n_presel_jet >= 2", 100, 0., 250.),
  ("jet2_CSV", "F", "n_presel_jet >= 3", 100, -0.01, +1.01),
  ("jet2_pt", "F", "n_presel_jet >= 3", 100, 0., 250.),
  ("jet2_eta", "F", "n_presel_jet >= 3", 100, -5.5, +5.5),
  ("jet2_phi", "F", "n_presel_jet >= 3", 36, -math.pi, +math.pi),
  ("jet2_E", "F", "n_presel_jet >= 3", 100, 0., 250.),
  ("jet3_CSV", "F", "n_presel_jet >= 4", 100, -0.01, +1.01),
  ("jet3_pt", "F", "n_presel_jet >= 4", 100, 0., 250.),
  ("jet3_eta", "F", "n_presel_jet >= 4", 100, -5.5, +5.5),
  ("jet3_phi", "F", "n_presel_jet >= 4", 36, -math.pi, +math.pi),
  ("jet3_E", "F", "n_presel_jet >= 4", 100, 0., 250.),
  ("PFMET", "F", "", 100, 0., 250.),
  ("PFMETphi", "F", "", 36, -math.pi, +math.pi),
  ("MHT", "F", "", 100, 0., 250.),
  ("metLD", "F", "", 100, 0., 2.),
  ("lep0_conept", "F", "", 100, 0., 250.),
  ("lep1_conept", "F", "", 100, 0., 250.),
  ("mindr_lep0_jet", "F", "", 100, 0., math.pi),
  ("mindr_lep1_jet", "F", "", 100, 0., math.pi),
  ("MT_met_lep0", "F", "", 100, 0., 250.),
  ("avg_dr_jet", "F", "", 100, 0., math.pi),
  ("n_jet25_recl", "I", "", 12, -0.5, 11.5),
  ("MVA_2lss_ttV", "F", "", 100, -1., 1.),
  ("MVA_2lss_ttbar", "F", "", 100, -1., 1.),
  ("MC_weight", "F", "", 100, -10, 10.),
  ("FR_weight", "F", "", 100, -1., 3.),
  ("triggerSF_weight", "F", "", 100, 0., 2.),
  ("leptonSF_weight", "F", "", 100, 0., 2.),
  ("bTagSF_weight", "F", "", 100, 0., 2.),
  ("PU_weight", "F", "", 100, 0., 4.),
  ("tauSF_weight", "F", "", 100, 0., 4.),
  #("gen_weight", "F", "", 100, 0., 250.),
]



def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise

def get_header(category):
  (selection, region) = category.split("_")
  header = selection + ", "
  if region == "SR":
    header += "signal region"
  elif region == "Flip":
    header += "charge flip extrapolation region"
  elif region == "Fake":
    header += "fake extrapolation region"
  return header

def make_comparison_plot(outdir, var, groupname1, groupname2, category, weight = "PU_weight*MC_weight*bTagSF_weight*leptonSF_weight*triggerSF_weight*FR_weight", dataset = "ttH"):
  var_name = var[0]
  n_bins = var[3]
  range_low = var[4]
  range_high = var[5]
  
  histos = []
  plot_name = "p"   #segfault when using different names for each
  #"%s_%s_%s_%s_%s_vs_%s" % (outdir, var_name, dataset, category, groupname1, groupname2)
  name1 = "plot_%s_%s" % (groupname1, plot_name)
  plot1 = single_plot("%s/%s" % (groups[groupname1]["inputPath"], groups[groupname1]["inputFiles"][dataset]),
    name1,
    "%s_%s" % (groups[groupname1]["treePrefix"], category),
    var_name,
    weight,
    n_bins, range_low, range_high)
    
  name2 = "plot_%s_%s" % (groupname2, plot_name)
  plot2 = single_plot("%s/%s" % (groups[groupname2]["inputPath"], groups[groupname2]["inputFiles"][dataset]),
    name2,
    "%s_%s" % (groups[groupname2]["treePrefix"], category),
    var_name,
    weight,
    n_bins, range_low, range_high)
  histos.append(plot1)
  histos.append(plot2)

  leg_entry = []
  leg_entry.append("%s:\t N=%d, mean=%.2f, RMS=%.2f" % (groupname1, plot1.GetEntries(), plot1.GetMean(), plot1.GetRMS()))
  leg_entry.append("%s:\t N=%d, mean=%.2f, RMS=%.2f" % (groupname2, plot2.GetEntries(), plot2.GetMean(), plot2.GetRMS()))
  leg=TLegend(0.45,0.74,0.85,0.89)
  
  leg.SetHeader(get_header(category));
  leg.SetBorderSize(0)
  leg.SetTextSize(0.04)
  leg.SetFillColor(0)

  for i in range(len(histos)):
    normalize_histogram(histos[i])
    leg.AddEntry(histos[i], leg_entry[i])

  histos[0].SetLineColor(ROOT.kOrange-2)
  histos[0].SetFillColor(ROOT.kOrange-2)
  histos[0].SetStats(0)
  histos[0].SetTitle("")

  histos[1].SetLineColor(1)
  histos[1].SetLineWidth(2)

  c=TCanvas("c_%s" % plot_name,"c_%s" % plot_name, 800, 600)

  pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
  pad1.SetLeftMargin(0.15)
  pad1.SetBottomMargin(0) # Upper and lower plot are joined
  pad1.Draw()             # Draw the upper pad: pad1
  pad1.cd()               # pad1 becomes the current pad
  
  max_val = 0.1
  min_val = 0
  for i in range(len(histos)):
    max_val = max(histos[i].GetMaximum(), max_val)
    min_val = min(histos[i].GetMinimum(), min_val)
  
  for i in range(len(histos)):
    histos[i].SetMaximum(1.4*max_val)
    histos[i].SetMinimum(1.4*min_val)
    histos[i].GetXaxis().SetTitle(var_name)
    histos[i].GetYaxis().SetTitle("a.u.")
    histos[i].GetYaxis().SetTitleOffset(1.7)
    #histos[i].GetYaxis().SetTickLength(0)
    #histos[i].GetYaxis().SetLabelOffset(999)

  texl = TLatex(histos[0].GetBinLowEdge(1), 1.01*1.4*max_val, "CMS Preliminary, Simulation ttH #sqrt{s}=13 TeV")
  texl.SetTextSize(0.04)
  texl.Draw("same")

  histos[0].Draw("hist")
  histos[1].Draw("same")
  leg.Draw("same")
  texl.Draw("same")
  
  histos[0].GetYaxis().SetLabelSize(0.)
  axis = TGaxis(range_low, min_val, range_low, max_val, min_val, max_val, 510, "")
  axis.SetLabelFont(43) #Absolute font size in pixel (precision 3)
  axis.SetLabelSize(15)
  axis.Draw()
  
  # lower plot will be in pad
  c.cd()    # Go back to the main canvas before defining pad2
  pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
  pad2.SetLeftMargin(0.15)
  pad2.SetTopMargin(0)
  pad2.SetBottomMargin(0.35)
  pad2.Draw()
  pad2.cd()
  
  h_ratio = make_ratio_histogram("h_ratio", histos[1], histos[0])
  
  """
  h_ratio = h[1].Clone("h_ratio")
  """
  
  h_ratio.SetTitle("")
  h_ratio.Draw()       #Draw the ratio plot
  
  # Y axis histo_emul plot settings
  histos[0].GetYaxis().SetTitleSize(20)
  histos[0].GetYaxis().SetTitleFont(43)
  histos[0].GetYaxis().SetTitleOffset(1.5)
  
  # Ratio plot (h_ratio) settings
  #h_ratio.SetTitle("") # Remove the ratio title
  
  h_ratio.GetYaxis().SetLabelSize(0.)
  axis2 = TGaxis( range_low, 0.01, range_low, 1.99, 0.01, 1.99, 505,"")
  axis2.SetLabelFont(43) # Absolute font size in pixel (precision 3)
  axis2.SetLabelSize(15)
  axis2.Draw()
  
  # Y axis ratio plot settings
  h_ratio.GetYaxis().SetTitle("%s/%s" % (groupname2, groupname1))
  h_ratio.GetYaxis().SetNdivisions(505)
  h_ratio.GetYaxis().SetTitleSize(20)
  h_ratio.GetYaxis().SetTitleFont(43)
  h_ratio.GetYaxis().SetTitleOffset(1.5)
  #h_ratio.GetYaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
  #h_ratio.GetYaxis().SetLabelSize(15)

  
  # X axis ratio plot settings
  h_ratio.GetXaxis().SetTitleSize(20)
  h_ratio.GetXaxis().SetTitleFont(43)
  h_ratio.GetXaxis().SetTitleOffset(4.)
  h_ratio.GetXaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
  h_ratio.GetXaxis().SetLabelSize(15)

  
  line = TLine(range_low, 1., range_high,1.)
  line.Draw("same")

  plot_file_name="%s" % (var_name)
  dirname = ("%s_vs_%s/%s/%s" % (groupname1, groupname2, category, outdir)).replace(" ", "_")
  for file_format in ["png", "pdf"]:
      mkdir_p("plots_test/%s/%s" % (dirname, file_format))
      c.SaveAs("plots_test/%s/%s/%s.%s" % (dirname, file_format, plot_file_name, file_format))


def single_plot(file, name, tree_name, var, cut, n_bins, range_low, range_high):
  tree = TChain(tree_name)
  tree.Add(file)
  g = TH1F(name, name, n_bins, range_low, range_high)
  g.Sumw2()
  tree.Draw(var+">>%s" % name,cut,"goff");
  return g

def normalize_histogram(histogram):
  if histogram.Integral() > 0.:
    histogram.Scale(1./histogram.Integral())

"""//-------------------------------------------------------------------------------
std::string getLegendEntry(const std::string& legendEntry, const TH1* histogram)
{
  std::string legendEntry_full = Form("%s: Entries = %1.0f, Mean = %1.2f, RMS = %1.2f", legendEntry.data(), histogram.GetEntries(), histogram.GetMean(), histogram.GetRMS());
  return legendEntry_full;
}"""

def make_ratio_histogram(ratioHistogramName, numerator, denominator):
  #TH1 histogramRatio
  
  if ( numerator.GetDimension() == denominator.GetDimension() and
       numerator.GetNbinsX() == denominator.GetNbinsX() ):
    histogramRatio = numerator.Clone(ratioHistogramName)
    histogramRatio.Divide(denominator)
    
    #histogramRatio.SetLineColor(numerator.GetLineColor())
    histogramRatio.SetLineWidth(numerator.GetLineWidth())
    histogramRatio.SetMarkerColor(numerator.GetMarkerColor())
    #histogramRatio.SetMarkerStyle(numerator.GetMarkerStyle())
    histogramRatio.SetMarkerSize(numerator.GetMarkerSize())
    
    histogramRatio.SetLineColor(ROOT.kBlack)
    histogramRatio.SetMinimum(0.)#  // Define Y ..
    histogramRatio.SetMaximum(2.)# // .. range
    #histogramRatio.Sumw2()
    histogramRatio.SetStats(0)      # No statistics on lower plot
    histogramRatio.SetMarkerStyle(20)
    return histogramRatio
  else: raise("Histogram dimensions don't match")


if __name__ == "__main__":
  ROOT.gROOT.SetBatch(True)
  for i in range(len(groupnames)-1):
    groupname1 = groupnames[i]
    for j in range(i+1, len(groupnames)):
      groupname2 = groupnames[j]
      for category in categories:
        for var in variables:
          make_comparison_plot("Unweighted", var, groupname1, groupname2, category, "1", dataset = "ttH")
          
          #weight = "PU_weight*MC_weight*bTagSF_weight*leptonSF_weight*triggerSF_weight*FR_weight"
          weight = "PU_weight*MC_weight*bTagSF_weight*leptonSF_weight*triggerSF_weight"#*tauSF_weight"
          if "Fake" in category:
            print category
            weight += "*FR_weight"
          
          if "weight" in var[1]:
            print var
            weight = "1"
          
          make_comparison_plot("Weighted", var, groupname1, groupname2, category, weight, dataset = "ttH")
        #make_comparison_plot("Unweighted", ("total weight", "F", "", 100, -2., 4.), groupname1, groupname2, category, "1", dataset = "ttH")
