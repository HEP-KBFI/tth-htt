from ROOT import *
import ROOT

backgrounds = ["DY_fake", "Singletop", "TTbar", "WJets", "Diboson"]

def make_plot(filename, var, leptons):
  histo_sig = filename.Get("%s/total/%s/%s" % (leptons, "DY", var) )
  histo_sig.SetTitle(var)
  histo_bg = filename.Get("%s/total/%s/%s" % (leptons, backgrounds[0], var) )
  for bg in range(1, len(backgrounds)):
    histo_add = filename.Get("%s/total/%s/%s" % (leptons, backgrounds[bg], var) )
    #print backgrounds[bg], histo_add
    histo_bg.Add(histo_add)
  name = "%s_%s" % (var, leptons)
  plot(histo_sig, histo_bg, name)
    
    
def plot(histo_sig, histo_bg, name):
  ROOT.gStyle.SetOptStat(0)  
  c = TCanvas("canvas", "canvas", 800, 600)
  histo_sig.Scale(1/histo_sig.Integral())
  histo_sig.SetLineColor(kBlue)
  histo_sig.SetMarkerSize(2)
  #histo_sig.SetMarkerStyle(2)
  histo_bg.Scale(1/histo_bg.Integral())
  histo_bg.SetLineColor(kRed)
  histo_bg.SetMarkerSize(3)
  #histo_bg.SetMarkerStyle(3)
  histo_sig.Draw()
  histo_bg.Draw("SAME")
  c.SaveAs("%s.png" % name)
  
  
def make_projection_plot(filename, var, leptons, which_bin):
  histo_sig_2D = filename.Get("%s/total/%s/%s" % (leptons, "DY", var) )
  histo_sig = histo_sig_2D.ProjectionX("DY", which_bin, which_bin)
  histo_sig.SetTitle(var)
  #print "DY", histo_sig.Integral()
  histo_bg_2D = filename.Get("%s/total/%s/%s" % (leptons, backgrounds[0], var) )
  histo_bg = histo_bg_2D.ProjectionX(backgrounds[0], which_bin, which_bin) 
  #print "DY_fake", histo_bg.Integral()
  for bg in range(1, len(backgrounds)):
    histo_add_2D = filename.Get("%s/total/%s/%s" % (leptons, backgrounds[bg], var) )
    histo_add = histo_add_2D.ProjectionX(backgrounds[bg], which_bin, which_bin) 
    #print backgrounds[bg], histo_add
    #print backgrounds[bg], histo_add, histo_add.Integral()
    histo_bg.Add(histo_add)
  name = "%s_%s" % (var, leptons)
  plot(histo_sig, histo_bg, name)

if __name__ == "__main__":
  dirname = "/home/andres/tth/histograms/histosCF_mu_uus"
  fn = "histograms_harvested_stage2_charge_flip.root"
  filename = "%s/%s/%s" % (dirname, "histograms", fn)
  f = TFile(filename, 'read')

  for leptons in ["SS", "OS"]:
    for var in ["nJets", "delta_phi", "nBJetsLoose", "mass_2"]:
      make_plot(f, var, leptons)
    
    for var in ["deltaphi_vs_njets", "deltaphi_vs_bjets_loose"]:
      make_projection_plot(f, var, leptons, 1)     #1-> n(B)Jets == 0

