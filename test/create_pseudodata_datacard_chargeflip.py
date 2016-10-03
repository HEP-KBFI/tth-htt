from ROOT import TFile, TDirectory
import ROOT
import numpy as np
import math

samples = ["data_obs",
	    "DY",
        "DY_fake", 
	    "WJets", 
	    "Singletop", 
	    "Diboson", 
	    "TTbar"]
categories = ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH"]
prefix = "ttH_charge_flip"
charges = ["OS", "SS"]
systematics = ["CMS_ttHl_electronERUp",
       "CMS_ttHl_electronERDown",
       "CMS_ttHl_electronESEndcapUp",
       "CMS_ttHl_electronESEndcapDown",
       "CMS_ttHl_electronESBarrelUp",
       "CMS_ttHl_electronESBarrelDown"]


def create_pseudodata(infile, outfile_data, outfile_pseudodata):
    f = TFile(infile)
    fout = TFile(outfile_data, "RECREATE")
    fout_pseudo = TFile(outfile_pseudodata, "RECREATE")
    
    for charge in charges:
        for cat in categories:
            first = True
            dirname = "%s_%s_%s" % (prefix, charge, cat)
            cd = fout.mkdir(dirname)
            cd_pseudo = fout_pseudo.mkdir(dirname)
            for sample in samples:
                cd.cd() 
                histo_nominal = f.Get("%s/x_%s"  % (dirname, sample))
                print "%s/x_%s"  % (dirname, sample)
                histo_nominal.Write()
                
                if sample == "data_obs": continue
                cd_pseudo.cd()
                #histo_nominal2 = histo_nominal.Clone()
                histo_nominal.Write()
                
                if first == True:
                    data_histo = histo_nominal.Clone()
                    first = False
                else:
                    data_histo.Add(histo_nominal)
                
                
                for syst in systematics:
                  if syst.startswith("CMS_ttHl_electronER") and not sample == "DY": continue
                  histo = f.Get("%s/x_%s_%s"  % (dirname, sample, syst))
                  #if histo.Integral() > 0 or not sample == "DY":
                  cd.cd() 
                  histo.Write()
                  cd_pseudo.cd() 
                  histo.Write()
            data_histo.SetNameTitle("x_data_obs", "x_data_obs")
            for b in range(1, data_histo.GetNbinsX()+1):
                data_histo.SetBinContent(b, np.random.poisson(data_histo.GetBinContent(b)))
                data_histo.Sumw2(ROOT.kFALSE)
                print data_histo.GetBinContent(b), data_histo.GetBinError(b)
                #data_histo.SetBinError(b, max(1, math.sqrt(data_histo.GetBinContent(b))))
            data_histo.Write()            
    f.Close()
    fout.Close()
    fout_pseudo.Close()
            

if __name__ == "__main__":
  indir = "/home/andres/tth/histograms/histosCF_data_eleESER_mva_0_6_notrig/datacards/"
  infile = "prepareDatacards_charge_flip_mass_ll.root"
  datafile = "prepareDatacards_data_charge_flip_mass_ll.root"
  pseudodatafile = "prepareDatacards_pseudodata_charge_flip_mass_ll.root"
  create_pseudodata(indir + infile, 
    indir + datafile, 
    indir + pseudodatafile)

