import CombineHarvester.CombineTools.ch as ch
# import CombineHarvester.CombineTools.pdgRounding as pdgRounding
import ROOT
import math
## for passing command line arguments
import sys

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(ROOT.kTRUE)

ROOT.gSystem.Load('libHiggsAnalysisCombinedLimit')

### WORKSPACE PATH (Output of "text2workspace ..." or "combineTool.py -M T2W ..." step)
fin = ROOT.TFile(sys.argv[1])
wsp = fin.Get('w')

cmb = ch.CombineHarvester()
cmb.SetFlag("workspaces-use-clone", True)
ch.ParseCombineWorkspace(cmb, wsp, 'ModelConfig', 'data_obs', False)

### MLFIT ROOT FILE PATH (Output of "combineTool.py -M FitDiagnostics ..." step)
mlf = ROOT.TFile(sys.argv[2], 'read')
### GETTING THE RooFitResult ###
rfr = mlf.Get('fit_s')

### SHAPE FILE (Output of "PostFitShapesFromWorkspace ..." step) PATH
fin2 = ROOT.TFile(sys.argv[4], 'read')

def AddSystQuad(a,b):
    a2 = math.pow(a, 2.)
    b2 = math.pow(b, 2.)
    x  = a2 + b2
    quad =  math.sqrt(x)
    return quad


def PrintTables(cmb, uargs, fit_status):
    c_m_incl = cmb.cp().bin([sys.argv[3]])

#    print  c_m_incl.cp().PrintAll()
#    print r'data_obs : $%.2f$ \\' % (c_m_incl.cp().GetObservedRate())
#    print r'WJets : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['WJets']).GetRate(), c_m_incl.cp().process(['WJets']).GetUncertainty(*uargs))
#    print r'TTbar : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['TTbar']).GetRate(), c_m_incl.cp().process(['TTbar']).GetUncertainty(*uargs))
#    print r'Diboson : $%.2f$ +/- $%.2f$  \\' % (c_m_incl.cp().process(['Diboson']).GetRate(), c_m_incl.cp().process(['Diboson']).GetUncertainty(*uargs))
#    print r'%s DY_fakes : %.2f +/- %.2f' % (fit_status, c_m_incl.cp().process(['DY_fakes']).GetRate(), c_m_incl.cp().process(['DY_fakes']).GetUncertainty(*uargs))
    print r'%s DY_signal : %.2f +/- %.2f' % (fit_status, c_m_incl.cp().process(['DY_signal']).GetRate(), c_m_incl.cp().process(['DY_signal']).GetUncertainty(*uargs))




def PrintMuToText(fin2, mlf, tree_name):
     histo_pass_prefit_signal = fin2.Get("pass_prefit/DY_signal")
     histo_fail_prefit_signal = fin2.Get("fail_prefit/DY_signal")

     tree=mlf.Get(tree_name)
     nev = tree.GetEntries()
     for iev in range(0,nev):
        tree.GetEntry(iev)
        mu_value = tree.SF         
        mu_err = tree.SFErr  
        mu_low_err = tree.SFLoErr  
        mu_high_err = tree.SFHiErr
     print('\n\n')   
     print('Raw Post-fit mu values:\n')
     print('mu: %.2f, muErr: %.2f, muLoErr: %.2f, muHiErr: %.2f' % (mu_value, mu_err, mu_low_err, mu_high_err))    

     ##---- mu correction taken from Charge Flip rate-----##
     if mu_low_err > 0.:
         print('\n')   
         print("\t\t mu_high_err/mu_low_err: {}".format(mu_high_err / mu_low_err))   

     try:
         # postFit distributions are scaled to scale factor 1, need to multiply by fitted number
         bestFit = mu_value * histo_pass_prefit_signal.Integral() / (histo_fail_prefit_signal.Integral() + histo_pass_prefit_signal.Integral())    

     except AttributeError:
         if histo_fail_prefit_signal.Integral() > 0:
             bestFit = 0.
         else:
             # raise
             print("histo_fail_prefit_signal.Integral() = 0")

     if abs(mu_high_err / mu_low_err) > 2 or abs(mu_high_err / mu_low_err) < 1. / 2:
         # In this case probably failed to find crossing, use symmetric error
         print("Strange asymmetric errors! Probably failed to find crossing.")

     fitHiErr = mu_high_err / mu_value * bestFit
     fitLoErr = mu_low_err / mu_value * bestFit
     print('\n\n')   
     print('Corrected Post-fit mu values:\n')
     print('corr_mu: %.2f, corr_muLoErr: %.2f, corr_muHiErr: %.2f' % (bestFit, fitLoErr, fitHiErr))    
     ##---------------------------------------------------##    
 



def PrintTablesFromShapeFiles(fin2):
    histo_pass_prefit_signal = fin2.Get("pass_prefit/DY_signal")
    error_pass_prefit_signal = ROOT.Double(-1.0)
    integral_pass_prefit_signal = histo_pass_prefit_signal.IntegralAndError(1, histo_pass_prefit_signal.GetNbinsX(), error_pass_prefit_signal, "")
    histo_pass_postfit_signal = fin2.Get("pass_postfit/DY_signal")
    error_pass_postfit_signal = ROOT.Double(-1.0)
    integral_pass_postfit_signal = histo_pass_postfit_signal.IntegralAndError(1, histo_pass_postfit_signal.GetNbinsX(), error_pass_postfit_signal, "")
    histo_fail_prefit_signal = fin2.Get("fail_prefit/DY_signal")
    error_fail_prefit_signal = ROOT.Double(-1.0)
    integral_fail_prefit_signal = histo_fail_prefit_signal.IntegralAndError(1, histo_fail_prefit_signal.GetNbinsX(), error_fail_prefit_signal, "")
    histo_fail_postfit_signal = fin2.Get("fail_postfit/DY_signal")
    error_fail_postfit_signal = ROOT.Double(-1.0)
    integral_fail_postfit_signal = histo_fail_postfit_signal.IntegralAndError(1, histo_fail_postfit_signal.GetNbinsX(), error_fail_postfit_signal, "")
    print 'Pre-fit values (Pass Region):\n'
    print r'%s DY_signal : %.2f +/- %.2f' % ('Pre-fit Pass', integral_pass_prefit_signal, error_pass_prefit_signal)
    print 'Post-fit values (Pass Region):\n'
    print r'%s DY_signal : %.2f +/- %.2f' % ('Post-fit Pass', integral_pass_postfit_signal, error_pass_postfit_signal)
    print 'Pre-fit values (Fail Region):\n'
    print r'%s DY_signal : %.2f +/- %.2f' % ('Pre-fit Fail', integral_fail_prefit_signal, error_fail_prefit_signal)
    print 'Post-fit values (Fail Region):\n'
    print r'%s DY_signal : %.2f +/- %.2f' % ('Post-fit Fail', integral_fail_postfit_signal, error_fail_postfit_signal)



#### ----- TO GET THE PREF-FIT data_fakes VALUE AND UNCERT. ----- #####
#print 'Pre-fit values:\n\n'
#PrintTables(cmb, tuple(), 'Pre-fit')

#### ----- TO GET THE POSTFIT data_fakes VALUE AND UNCERT. ----- #####
#cmb.UpdateParameters(rfr)
#print 'Post-fit values:\n\n'
#PrintTables(cmb, (rfr, 500), 'Post-fit')

#### ----- TO GET THE PRE/POST-FIT DY_signal VALUE AND UNCERT. ----- #####
PrintTablesFromShapeFiles(fin2)


#### ----- TO GET THE POSTFIT mu VALUE AND UNCERT. ----- #####
PrintMuToText(fin2, mlf, 'tree_fit_sb')

