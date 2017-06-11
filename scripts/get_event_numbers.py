from ROOT import *
#from numpy import array
from array import array

def print_event_list(filename):
  f = TFile(filename, 'read')
  #gDirectory.cd(  )

  lumi = array( 'i', [0] )
  tree = f.Get("syncTree_2lss1tau_SR")
  tree.SetBranchAddress( "ls", lumi )

  lumis = []

  for i in range( tree.GetEntries() ):
     tree.GetEntry( i )
     lumis.append(lumi[0])

  i=0
  for event in syncTree_2lss1tau_SR:
      if event.run == myRun and lumis[i] == myLumi and event.nEvent == myEvent:
        print "%d:%d:%d" % (event.run, lumis[i], event.nEvent)
      i += 1
      
if __name__ == "__main__":
  print_event_list('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/syncNtuple_event_ttH_80X.root')
  #print_event_list('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/sync_ntuples_split.root')
  
