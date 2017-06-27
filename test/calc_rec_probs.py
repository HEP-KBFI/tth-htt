from ROOT import TFile
import ROOT

categories = ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH"]

def calc_rec_probs(infile, processes):
  f = TFile(infile)
  
  for p in processes:
    print p
    for cat in categories:
        histo_OS = f.Get("OS/%s/%s"  % (cat, "mass_ll"))
        histo_SS = f.Get("SS/%s/%s" % (cat, "mass_ll"))
        print "SS/%s/%s" % (cat, "mass_ll")
        #print cat, "Entries: %d SS, %d OS" % (histo_SS.GetEntries(), histo_OS.GetEntries())
        #for bin_pt in range(1, histo_OS.GetNbinsX()+1):
        #for bin_eta in range(1, histo_OS.GetNbinsY()+1):
        os_count = histo_OS.Integral()
        ss_count = histo_SS.Integral()
        if ss_count + os_count > 0:
            ratio = 100. * ss_count / (ss_count + os_count)
            print "Category: %s:\t Ratio = %f" % (cat, ratio)
        else: print "Category: %s:\t Ratio = NA" % cat
        #print "Integral OS:", histo_OS.Integral(), histo_OS.Integral(1,histo_OS.GetNbinsX()-1)
        #print "Integral SS:", histo_SS.Integral(), histo_SS.Integral(1,histo_SS.GetNbinsX()-1)


def calc_probs_21(infile):
  f = TFile(infile) 
  cats = ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH"]
  for cat in cats:
    histo_OS = f.Get("gen/OS/%s/mass_ll" % cat)
    histo_SS = f.Get("gen/SS/%s/mass_ll" % cat)
    os_count = histo_OS.Integral()
    ss_count = histo_SS.Integral()
    if os_count > 0:ratio = 100. * ss_count / (ss_count + os_count)
    else: ratio = 100.
    print "Category %s:\t ratio = %f" % (cat, ratio)

def print_probs_21(infile):
  f = TFile(infile) 
  cats = ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH"]
  i = 0
  os_err = ROOT.Double()
  ss_err = ROOT.Double()
  for cat in cats:
    histo_OS = f.Get("gen/OS/%s/mass_ll" % cat)
    histo_SS = f.Get("gen/SS/%s/mass_ll" % cat)
    os_count = histo_OS.IntegralAndError(0, histo_OS.GetNbinsX()+2, os_err)
    ss_count = histo_SS.IntegralAndError(0, histo_SS.GetNbinsX()+2, ss_err)
    if os_count > 0:
      ratio = ss_count / (ss_count + os_count)
      err = (ss_count + ss_err) / (ss_count + ss_err + os_count - os_err) - ratio
    else: ratio = 1.
    print "%d, %f, %f, %f" % (i, ratio, err, err)
    #print "ERR: ", ss_count, ss_err, os_count, os_err
    i+=1
        

if __name__ == "__main__":
  procs = ["DY"]
  infile = "/hdfs/local/ttH_2tau/andres/ttHAnalysis/2016/histosCF_summer2/histograms/charge_flip/histograms_harvested_stage2_charge_flip_Tight.root"
  #calc_rec_probs(infile, procs)
  print "_" * 80
  calc_probs_21(infile)
  print_probs_21(infile)
