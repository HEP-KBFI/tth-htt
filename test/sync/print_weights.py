from ROOT import *
#from numpy import array
from array import array

def print_weights(filename):

  f = TFile(filename, 'read')
  #gDirectory.cd(  )

  lumi = array( 'i', [0] )
  tree = f.Get("syncTree_2lSS1tau_SR")
  tree.SetBranchAddress( "ls", lumi )

  lumis = []
  sum_weights = 0
  sums = [0,0,0,0,0,0,0]

  for i in range( tree.GetEntries() ):
     tree.GetEntry( i )
     lumis.append(lumi[0])

  i=0
  for event in syncTree_2lSS1tau_SR:
      #if lumis[i] == 23410 and event.nEvent == 9335322: continue
      w = event.PU_weight*event.MC_weight*event.bTagSF_weight*event.leptonSF_weight*event.triggerSF_weight#*event.lumiScale
      if True:#event.n_fakeablesel_mu == 2 and event.n_fakeablesel_ele == 0:
        print "%d:%d:%d " % (event.run, lumis[i], event.nEvent),
        print event.bTagSF_weight, event.n_presel_jet, event.jet0_pt, event.jet1_pt, event.jet2_pt, event.jet3_pt, event.jet0_CSV, event.jet1_CSV, event.jet2_CSV, event.jet3_CSV, event.jet0_eta, event.jet1_eta, event.jet2_eta, event.jet3_eta#, event.jet0_heppyFlavour, event.jet1_heppyFlavour, event.jet2_heppyFlavour, event.jet3_heppyFlavour#, event.lumiScale
        #w, event.PU_weight, event.MC_weight, event.leptonSF_weight, event.triggerSF_weight, event.FR_weight, event.n_fakeablesel_mu, event.n_fakeablesel_ele,
         
      sums[0] += event.PU_weight
      sums[1] += event.MC_weight 
      sums[2] += event.bTagSF_weight
      sums[3] += event.leptonSF_weight
      sums[4] += event.triggerSF_weight
      sums[5] += event.FR_weight
      sum_weights += w
      i += 1
  
  for j in range(len(sums)):
    sums[j] = sums[j] / i
  print "Sum of weights: ", sum_weights, sums
  
if __name__ == "__main__":
  #print_weights('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/syncNtuple_event_ttH_80X_Summer16.root')
  print_weights('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/sync_ntuples_split.root')
