from ROOT import *
#from numpy import array
from array import array

#def print_event_comparison(filename1, filename2, myRun, myLumi, myEvent):
def print_event_comparison(filename):
  f = TFile(filename, 'read')
  #gDirectory.cd(  )

  lumi = array( 'i', [0] )
  tree = f.Get("syncTree")
  tree.SetBranchAddress( "ls", lumi )

  lumis = []
  sum_weights = 0
  sums = [0,0,0,0,0,0]

  for i in range( tree.GetEntries() ):
     tree.GetEntry( i )
     lumis.append(lumi[0])

  i=0
  for event in syncTree:
      #if lumis[i] == 23410 and event.nEvent == 9335322: continue
      #w = event.PU_weight*event.MC_weight*event.bTagSF_weight*event.leptonSF_weight*event.triggerSF_weight
      if event.MVA_2lss_ttV>0.6:
      #if lumis[i] == 22552 and event.nEvent == 3202381:
        print "%d:%d:%d " % (event.run, lumis[i], event.nEvent),
        print event.MVA_2lss_ttV, event.n_presel_jet, event.n_presel_mu, event.n_presel_ele, event.mindr_lep0_jet, event.mindr_lep1_jet, event.PFMET, event.avg_dr_jet, event.MT_met_lep0, event.mu0_pt, event.mu0_eta, event.ele0_pt, event.ele0_eta#, event.n_jet25_recl
      """sums[0] += event.PU_weight
      sums[1] += event.MC_weight 
      sums[2] += event.bTagSF_weight
      sums[3] += event.leptonSF_weight
      sums[4] += event.triggerSF_weight"""
      #sum_weights += w
      i += 1
  #print "Sum of weights: ", sum_weights#, sums
  
if __name__ == "__main__":
  #print_event_comparison('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/syncNtuple_event_ttH_80X_Summer16.root')
  print_event_comparison('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/sync_ntuples_presel/syncNtuple_ttH_80X_Summer16.root')
  #print_event_comparison('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/sync_ntuples_presel/sync_ntuple_summer_v0.root')
