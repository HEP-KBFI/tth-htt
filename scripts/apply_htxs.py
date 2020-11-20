#!/usr/bin/env python
import os, shlex
from subprocess import Popen, PIPE
import glob
import shutil
import ROOT

# python scripts/apply_htxs.py --inputPath /home/acaan/CMSSW_10_2_13/src/cards_set/legacy_TLL_22June20_prepareDatacards_stxs/2016/datacards/2lss_1tau/stxs --era 2016
from optparse import OptionParser
parser = OptionParser()
parser.add_option("--inputPath",    type="string",       dest="inputPath", help="Full path of prepareDatacards.root")
parser.add_option("--era",            type="int",          dest="era",         help="Era to consider (important for list of systematics). Default: 2017",  default=0)
(options, args) = parser.parse_args()

inputPath = options.inputPath
era         = options.era
higgs_procs_plain = ["ttH_hww", "ttH_hzz", "ttH_htt", "ttH_hzg", "ttH_mm"]

def rescale_stxs_pT_bins (inputShapes, stxs_pT_bins, era) :
    ## it assumes no subdirectories in the preparedatacards file,
    tfileout1 = ROOT.TFile(inputShapes, "UPDATE")
    tfileout1.cd()
    for nkey, key in enumerate(tfileout1.GetListOfKeys()) :
        obj =  key.ReadObj()
        obj_name = key.GetName()
        #if type(obj) is not ROOT.TH1F and type(obj) is not ROOT.TH1D and type(obj) is not ROOT.TH1 and type(obj) is not ROOT.TH1S and type(obj) is not ROOT.TH1C and type(obj) is not ROOT.TH1 :
        if type(obj) is not ROOT.TH1F :
            if type(obj) is ROOT.TH1 :
                print ("data_obs can be be TH1")
                continue
            else :
                print ("WARNING: All the histograms that are not data_obs should be TH1F - otherwhise combine will crash!!!")
                sys.exit()
        factor = 1.0
        nominal  = ROOT.TH1F()
        if "PTH" in obj_name:
            if "_fake_" in obj_name or "Convs" in obj_name or "flip" in obj_name :
                continue
            if not "_htt" in obj_name and not "_hww" in obj_name and not "_hzz" in obj_name and not "_hzg" in obj_name and not "_hmm" in obj_name :
                continue
            for key in stxs_pT_bins.keys() :
                if key in obj_name :
                    factor = stxs_pT_bins[key][era]
            if factor == 1.0 :
                print ("Something wrong, it is not scaling ", obj_name)
            nominal = obj.Clone()
            nominal.Scale( factor )
            nominal.Write()
            print ("rescaled ", key, obj_name, factor, nominal.Integral(), obj.Integral())
    tfileout1.Close()

stxs = True
pT_bins = {}
if stxs :
    # take ttH_ as the pT bins
    stxs_pT_bins            = {
        # pT bin           XS (now the cards are done normalizing ttH in each pT bin is normalized to 1pb)
        "PTH_fwd"       : {2016 : 0.002646, 2017 : 0.002486, 2018 : 0.002732},
        "PTH_0_60"      : {2016 : 0.048411, 2017 : 0.047804, 2018 : 0.047128},
        "PTH_60_120"    : {2016 : 0.074606, 2017 : 0.074574, 2018 : 0.073956},
        "PTH_120_200"   : {2016 : 0.053548, 2017 : 0.053988, 2018 : 0.054276},
        "PTH_200_300"   : {2016 : 0.022305, 2017 : 0.022525, 2018 : 0.022999},
        "PTH_300_infty" : {2016 : 0.010284, 2017 : 0.010420, 2018 : 0.010711},
        #"PTH_300_450"   : {2016 : 0.008042, 2017 : 0.008178, 2018 : 0.008397},
        #"PTH_300_infty" : {2016 : 0.002241, 2017 : 0.002242, 2018 : 0.002314},
    }
    for xproc in higgs_procs_plain :
      if "ttH_" in xproc :
        # remove the ttH_br of the list and add the same in a list of pT bins
        higgs_procs_plain        = list(set(higgs_procs_plain) - set([xproc]))
        for pTs in list(stxs_pT_bins.keys()) :
          higgs_procs_plain   = higgs_procs_plain + [ xproc.replace("ttH", "ttH_" + pTs) ]
    print ("higgs_procs == ", higgs_procs_plain)

listproc = glob.glob(inputPath+"/*.root")
inputPathNew = inputPath + "_htxs"
try :
    os.mkdir( inputPathNew )
except :
    print ("already exists: ", inputPathNew)
print ("\n copied \n %s to \n %s \nto rescale the pT bins with the cross sections by pT bins (see this git issue https://github.com/HEP-KBFI/tth-htt/issues/142)" % (inputPath, inputPathNew))

for eras in [2016, 2017, 2018] :
    for prepareDatacard in listproc :
        prepareDatacardNew = prepareDatacard.replace(inputPath, inputPathNew)
        shutil.copy2(prepareDatacard, prepareDatacardNew)
        print ("done", prepareDatacardNew)
        rescale_stxs_pT_bins(prepareDatacardNew, stxs_pT_bins, eras)
