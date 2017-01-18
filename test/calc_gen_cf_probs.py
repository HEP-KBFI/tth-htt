from ROOT import TFile, TCanvas

def calc_probs_hist(infile, processes):
  f = TFile(infile)
  
  for p in processes:
    histo_all = f.Get("gen_ratio/%s/pt_eta_ID" % p)
    histo_SS = f.Get("gen_ratio/%s/pt_eta_MisID" % p)
    histo2 = histo_all.Clone("histo2")
    histo = histo_SS.Clone("histo")
    histo.Divide(histo2)
    print p, ", ", histo.GetEntries(), histo2.GetEntries()
    for bin_eta in range(1, histo.GetNbinsY()+1):
      for bin_pt in range(1, histo.GetNbinsX()+1):
        #os_count = histo_OS.GetBinContent(bin_pt, bin_eta)
        #all_count = histo_SS.GetBinContent(bin_pt, bin_eta)
        ratio = 100. * histo.GetBinContent(bin_pt, bin_eta)
        error = 100. * histo.GetBinError(bin_pt, bin_eta)
        print "Bin (%d, %d): ratio = %f +- %f" % (bin_eta, bin_pt, ratio, error)
    #for bin_eta in range(1, histo_OS.GetNbinsY()+1):
    #  for bin_pt in range(1, histo_OS.GetNbinsX()+1):
    #    os_count = histo_OS.GetBinContent(bin_pt, bin_eta)
    #    ss_count = histo_SS.GetBinContent(bin_pt, bin_eta)
    #    print "Bin (%d, %d): SS entries = %f, content = %f" % (bin_eta, bin_pt, histo_SS.GetEntries(), ss_count)


def calc_probs(infile, processes):
  f = TFile(infile)
  
  for p in processes:
    effs = f.Get("gen_ratio/pt_eta_%s" % p)
    print effs
    totalHisto = effs.GetTotalHistogram()
    print totalHisto
    for bin_eta in range(1, totalHisto.GetNbinsY()+1):
      for bin_pt in range(1, totalHisto.GetNbinsX()+1):
        bin = effs.GetGlobalBin(bin_pt, bin_eta)
        eff = effs.GetEfficiency(bin)
        effErrLo = effs.GetEfficiencyErrorLow(bin)
        effErrHi = effs.GetEfficiencyErrorUp(bin)
        print "Bin (%d, %d): Eff = %f + %f - %f" % (bin_eta, bin_pt, eff * 100, effErrHi * 100, effErrLo*100)
  


if __name__ == "__main__":
  #procs = ["additional_signal_overlap", "WZ", "TTW", "Rares", "TTZ", "signal", "DY"]
  procs = ["DY"]
  for infile in ["/home/andres/tth/histograms/histosCF_genWeight/histograms/histograms_harvested_stage2_charge_flip.root",
      "/home/andres/tth/histograms/histosCF_mu2/histograms/histograms_harvested_stage2_charge_flip.root",
      ]:
    print infile
    calc_probs(infile, procs)
    #calc_probs_hist(infile, procs)
  
  
