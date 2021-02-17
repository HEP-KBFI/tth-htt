#!/usr/bin/env python                                                                                                                                                                                         
'''
Example usage:
python apply_FR_relErrors_LATEST.py -i ../data/FR_lep_mva_hh_multilepton_wFullSyst_woMETSyst_2018_KBFI_2020Nov27.root \
                                    -o FR_lep_mva_hh_multilepton_wFullSyst_woMETSyst_2018_KBFI_2020Nov27_wGiovanniUncs.root
                                    -a hh
                                    -n True                      
'''

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import argparse
import os
import prettytable
import shutil
import array


##----- GIOVANNI'S IMPORTS ----##
from math import *
from os.path import basename
import re

import sys
sys.argv.append('-b-')
#import ROOT
ROOT.gROOT.SetBatch(True)
sys.argv.remove('-b-')
from array import *
from ROOT import TH2D


def makeVariants_CERN(h,altsrc=None,norm=None):
    print("h.GetName()", h.GetName())
    lptmin = log(h.GetXaxis().GetBinCenter(1))
    lptmax = log(h.GetXaxis().GetBinCenter(h.GetNbinsX()))
    lptc     = 0.5*(lptmax+lptmin)
    lptslope = 1.0/(lptmax-lptc)
    shifters = [
        ("up"  ,  lambda pt,eta,fr,err : min(fr+err, 1.0) ),
        ("down",  lambda pt,eta,fr,err : max(fr-err, 0.05*fr) ),
        ("pt1" ,  lambda pt,eta,fr,err : min(max( fr + err * lptslope*(log(pt)-lptc),  0.05*fr),1.0) ),
        ("pt2" ,  lambda pt,eta,fr,err : min(max( fr - err * lptslope*(log(pt)-lptc),  0.05*fr),1.0) ),
        ("be1" ,  lambda pt,eta,fr,err : min(max( fr + err*0.707 if eta < 1.3 else fr-err*0.707, 0.05*fr),1.0) ),
        ("be2" ,  lambda pt,eta,fr,err : min(max( fr - err*0.707 if eta < 1.3 else fr+err*0.707, 0.05*fr),1.0) ),
    ]
    ret = []
    for s,func in shifters:
        hsyst = h.Clone(h.GetName()+"_"+s)
        for bx in xrange(1,h.GetNbinsX()+1):
            x = h.GetXaxis().GetBinCenter(bx)
            print("x: ", x)
            for by in xrange(1,h.GetNbinsY()+1):
                y = h.GetYaxis().GetBinCenter(by)
                print("y: ", y)
                fr0 = h.GetBinContent(bx,by)
                print("fr0: ", fr0)
                if altsrc == None:
                    err = h.GetBinError(bx,by)
                    print("err: ", err)
                else:
                    if altsrc.GetBinContent(bx,by) <= 0:
                        print "Warning: in %s, pt %4.1f, eta %3.1f: nominal %.4f +- %.4f , alternate %.4f +- %.4f  "  % (hsyst.GetName(), x, y, fr0, err, altsrc.GetBinContent(bx,by), altsrc.GetBinError(bx,by))
                    else:
                        err = fr0 * altsrc.GetBinError(bx,by)/altsrc.GetBinContent(bx,by)
                fr = func(x,y,fr0,err)
                print("Variation %-15s: pt %4.1f, eta %3.1f: nominal %.3f +- %.3f --> shifted %.3f "  % (hsyst.GetName(), x, y, fr0, err, fr))
                hsyst.SetBinContent(bx, by, fr)
                hsyst.SetBinError(bx, by, 0)
        if norm and s not in ("up","down"):
            sum0, sums = 0, 0
            for bx in xrange(1,h.GetNbinsX()+1):
                x = h.GetXaxis().GetBinCenter(bx)
                binw = h.GetXaxis().GetBinWidth(bx)
                #if x <= 15: continue
                for by in xrange(1,h.GetNbinsY()+1):
                    f0, f = h.GetBinContent(bx,by), hsyst.GetBinContent(bx,by)
                    sum0 += norm.GetBinContent(bx,by) * binw * f0/(1-f0)
                    sums += norm.GetBinContent(bx,by) * binw * f /(1-f)
                    #print "     at bx %2d by %2d pt %5.1f abseta %5.2f    N = %9.2f  fr0 = %.3f   fr = %.3f" % (bx,by,x,h.GetYaxis().GetBinCenter(by), norm.GetBinContent(bx,by), f0, f)           
            print "   pre-normalization for %s: sum0 %9.2f   sum %9.2f    ratio %.3f " % (hsyst.GetName(), sums, sum0, sums/sum0)
            hsyst.Scale(sum0/sums)
        ret.append(hsyst)
    return ret 



parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'file', required = True,
  help = 'R|Measured fake rates w/o the uncertainties',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', required = True,
  help = 'R|Output file name',
)
parser.add_argument('-a', '--analysis',
  type = str, dest = 'analysis', metavar = 'hh', required = True,
  help = 'R|Analysis for which the Fake Rates are measured. Options include: hh or tth',
)
parser.add_argument("-n", '--norm',  
    type = bool, dest = 'norm', metavar = 'bool', required = True, 
    help = 'R|Normalize variations pt1/2, be1/2 w.r.t 2lss TTbar MC Fake rates',                
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)



args = parser.parse_args()

input_filename = os.path.abspath(args.input)
out_filename = os.path.abspath(args.output)
apply_norm = args.norm
analysis = args.analysis
verbose = args.verbose

if apply_norm:
   print("Will be normalizing the pt1/2, be1/2 variations to avg. (2lSS) ttbar fake rates") 
else:
   print("Un-normalized variations used for pt1/2, be1/2 shape templates")


assert((analysis == "hh") or (analysis == "tth"))
assert(input_filename != out_filename)


print("Analysis Mode:", analysis)

if not os.path.isfile(input_filename):
  raise RuntimeError("No such file: %s" % input_filename)

infile = ROOT.TFile.Open(input_filename,"READ")
outfile = ROOT.TFile.Open(out_filename,"RECREATE")

input_histogram_names = [ key.GetName() for key in infile.GetListOfKeys() ]
print("input_histogram_names: ", input_histogram_names)

##data_fr_hist_names = ["FR_mva030_el_data_comb", "FR_mva050_mu_data_comb"]
##tt_mc_fr_hist_names = ["FR_mva030_el_data_comb_TT_fakes2", "FR_mva050_mu_data_comb_TT_fakes2_prefit"]

for key in input_histogram_names:
 #if "TT" in key or "QCD" in key:
 if "TT_fakes" in key:
     obj_tt_fakes = infile.Get(key)
     if(not obj_tt_fakes):
         print("Could not find", key)
         break
     h_tt_fakes = obj_tt_fakes.Clone()
     print("type(h_tt_fakes)", type(h_tt_fakes))
     outfile.WriteTObject(h_tt_fakes, h_tt_fakes.GetName())
     continue

 if "data_comb_prefit" in key:
    obj_prefit = infile.Get(key)
    if(not obj_prefit):
        print("Could not find", key)
        break
    h_prefit = obj_prefit.Clone()
    print("type(h_prefit)", type(h_prefit))
    outfile.WriteTObject(h_prefit, h_prefit.GetName())
    continue

 if "QCD" in key:
     print("QCD fr key: ", key)
 elif "TTj_minus_TTg" in key:
     print("Conv. Corrected ttbar fr key: ", key)
 else:
     print("data fr key: ", key)

 key_tt = ""   
 if "el" in  key:
     if "hh" in analysis:
         key_tt = "FR_mva030_el_data_comb_TT_fakes2" 
     elif "tth" in analysis:
         key_tt = "FR_mva080_el_data_comb_TT_fakes2" 
     else:
         print("Invalid analysis identifier")
         break
 elif "mu" in  key:
     if "hh" in analysis:
         key_tt = "FR_mva050_mu_data_comb_TT_fakes2_prefit"
     elif "tth" in analysis:
         key_tt = "FR_mva085_mu_data_comb_TT_fakes2_prefit"
     else:
         print("Invalid analysis identifier")
         break    
 else:
     print("Could not find lepton identifier in", key)
     break
 print("2lSS tt mc fr key: ", key_tt)

 obj_data_or_qcdfr = infile.Get(key)
 if(not obj_data_or_qcdfr):
     print("Could not find", key)
     break
 h_data_or_qcdfr = obj_data_or_qcdfr.Clone()    
 print("type(h_data_or_qcdfr)", type(h_data_or_qcdfr))

 obj_tt = infile.Get(key_tt)
 if(not obj_tt):
     print("Could not find", key_tt)
     break
 h_tt = obj_tt.Clone()    
 print("type(h_tt)", type(h_tt))
 

 variants = makeVariants_CERN(h_data_or_qcdfr, norm=(h_tt if apply_norm else None))
 print("variants", variants)

 for v in variants: outfile.WriteTObject(v, v.GetName())
 outfile.WriteTObject(h_data_or_qcdfr, h_data_or_qcdfr.GetName())



