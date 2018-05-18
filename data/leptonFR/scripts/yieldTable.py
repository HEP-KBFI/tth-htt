import CombineHarvester.CombineTools.ch as ch
# import CombineHarvester.CombineTools.pdgRounding as pdgRounding
import ROOT
import math
## for passing command line arguments
import sys

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(ROOT.kTRUE)

ROOT.gSystem.Load('libHiggsAnalysisCombinedLimit')


### WORKSPACE PATH  [CHANGE BOTH WORKSPACE AND MLFIT ROOT FILE AT THE SAME TIME]
# fin = ROOT.TFile('/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2/mu_incl/wsp.root')
# fin = ROOT.TFile('/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2/e_incl/wsp.root')
fin = ROOT.TFile(sys.argv[1])

wsp = fin.Get('w')

cmb = ch.CombineHarvester()
cmb.SetFlag("workspaces-use-clone", True)
ch.ParseCombineWorkspace(cmb, wsp, 'ModelConfig', 'data_obs', False)

### MLFIT ROOT FILE PATH [CHANGE BOTH WORKSPACE AND MLFIT ROOT FILE AT THE SAME TIME]
# mlf = ROOT.TFile('/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2/mu_incl/mlfitmu_incl.root')
# mlf = ROOT.TFile('/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2/e_incl/mlfite_incl.root')
mlf = ROOT.TFile(sys.argv[2])


### GETTING THE RooFitResult ###
rfr = mlf.Get('fit_s')

def AddSystQuad(a,b):
    a2 = math.pow(a, 2.)
    b2 = math.pow(b, 2.)
    x  = a2 + b2
    quad =  math.sqrt(x)
    return quad




def PrintTables(cmb, uargs, fit_status):
#    c_m_incl = cmb.cp().bin(['muons_tight_incl_shapes'])
    c_m_incl = cmb.cp().bin([sys.argv[3]])
#    print  c_m_incl.cp().PrintAll()

#    print r'data_obs : $%.2f$ \\' % (c_m_incl.cp().GetObservedRate())
#    print r'EWK : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['EWK']).GetRate(), c_m_incl.cp().process(['EWK']).GetUncertainty(*uargs))
#    print r'ttZ : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['TTZ']).GetRate(), c_m_incl.cp().process(['TTZ']).GetUncertainty(*uargs))
#    print r'ttW : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['TTW']).GetRate(), c_m_incl.cp().process(['TTW']).GetUncertainty(*uargs))
    print r'%s fakes_data : %.2f +/- %.2f' % (fit_status, c_m_incl.cp().process(['fakes_data']).GetRate(), c_m_incl.cp().process(['fakes_data']).GetUncertainty(*uargs))




def PrintMuToText(mlf, tree_name):
     tree=mlf.Get(tree_name)
     nev = tree.GetEntries()
     for iev in range(0,nev):
       tree.GetEntry(iev)
       mu_value = tree.r         ## in CMSSW_7_4_7 the branch name was tree.mu
       mu_low_err = tree.rLoErr  ## in CMSSW_7_4_7 the branch name was tree.muLoErr
       mu_high_err = tree.rHiErr ## in CMSSW_7_4_7 the branch name was tree.muHiErr
       print r'r: %.2f + %.2f - %.2f' % (mu_value, mu_high_err, mu_low_err)


#### ----- TO GET THE PREF-FIT fakes_data VALUE AND UNCERT. ----- #####
print 'Pre-fit values:'
PrintTables(cmb, tuple(), 'Pre-fit')



#### ----- TO GET THE POSTFIT fakes_data VALUE AND UNCERT. ----- #####
cmb.UpdateParameters(rfr)
print 'Post-fit values:\n\n'
PrintTables(cmb, (rfr, 500), 'Post-fit')


#### ----- TO GET THE POSTFIT r VALUE AND UNCERT. ----- #####
print 'Post-fit mu values:\n\n'
PrintMuToText(mlf, 'tree_fit_sb')

