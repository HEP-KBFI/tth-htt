from ROOT import TFile, TCanvas

def calc_probs_hist(infile, processes):
  f = TFile(infile)
  
  for p in processes:
    histo_OS = f.Get("gen_ratio/%s/pt_eta_ID" % p)
    histo_SS = f.Get("gen_ratio/%s/pt_eta_MisID" % p)
    histo2 = histo_OS.Clone("histo2")
    histo2.Add(histo_SS)
    histo = histo_SS.Clone("histo")
    histo.Divide(histo_OS)
    print p, ", ", histo_OS.GetEntries(), histo_SS.GetEntries()
    for bin_eta in range(1, histo_OS.GetNbinsY()+1):
      for bin_pt in range(1, histo_OS.GetNbinsX()+1):
        #os_count = histo_OS.GetBinContent(bin_pt, bin_eta)
        #ss_count = histo_SS.GetBinContent(bin_pt, bin_eta)
        ratio = 100. * histo.GetBinContent(bin_pt, bin_eta)
        error = 100. * histo.GetBinError(bin_pt, bin_eta)
        print "Bin (%d, %d): ratio = %f +- %f" % (bin_eta, bin_pt, ratio, error)
    for bin_eta in range(1, histo_OS.GetNbinsY()+1):
      for bin_pt in range(1, histo_OS.GetNbinsX()+1):
        os_count = histo_OS.GetBinContent(bin_pt, bin_eta)
        ss_count = histo_SS.GetBinContent(bin_pt, bin_eta)
        print "Bin (%d, %d): SS entries = %f, content = %f" % (bin_eta, bin_pt, histo_SS.GetEntries(), ss_count)


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
  infile = "/home/andres/tth/histosCF_data_effs/histograms/charge_flip_Tight/allHistogramsCF.root"
  calc_probs(infile, procs)
  
  
