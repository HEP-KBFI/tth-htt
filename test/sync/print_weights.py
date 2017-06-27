from ROOT import *
#from numpy import array
from array import array

def sgn(x):
  if x == 0:
    return x
  elif x > 0:
    return 1
  else: return -1

def print_weights(filename):

  f = TFile(filename, 'read')
  #gDirectory.cd(  )

  lumi = array( 'l', [0] )
  nRun = array( 'l', [0] )
  nEv = array( 'l', [0] )
  tree = f.Get("syncTree_1l2tau_SR")
  tree.SetBranchAddress( "ls", lumi )
  #tree.SetBranchAddress( "run", nRun )
  #tree.SetBranchAddress( "nEvent", nEv )  
  
  lumis = []
  sum_weights = 0
  sums = [0,0,0,0,0,0,0]
  sums_charge = [0,0,0]
  for i in range( tree.GetEntries() ):
     tree.GetEntry( i )
     lumis.append(lumi[0])
     #print "%d:%d:%d" % (nRun[0], lumi[0], nEv[0])
     #print nRun[0],":", lumi[0], ":",  nEv[0]

  #print "__________________________"
  i=0
  j = 0
  for event in syncTree_1l2tau_SR:
      #if lumis[i] == 23410 and event.nEvent == 9335322: continue
      w = event.PU_weight*sgn(event.MC_weight)*event.bTagSF_weight*event.leptonSF_weight*event.triggerSF_weight#*event.lumiScale
      if True:#event.n_fakeablesel_mu == 2 and event.n_fakeablesel_ele == 0:
        #if event.triggerSF_weight == 0.0: continue
        
        #if lumis[i] == 1513 and event.nEvent == 214853:continue
        #if lumis[i] == 2325 and event.nEvent == 330191:continue
        #if lumis[i] == 23979 and event.nEvent == 3404914:continue
        #if lumis[i] == 2591 and event.nEvent == 367864:continue
        #if lumis[i] == 4443 and event.nEvent == 630798:continue
        
        if event.triggerSF_weight > 0:
          print "%d:%d:%d" % (event.run, lumis[i], event.nEvent), 
          #print event.triggerSF_weight
          #print "%d " % (event.nEvent),
        else: 
          i+= 1
          continue
        #print event.MVA_2lss_ttV, event.MVA_2lss_ttbar, event.bTagSF_weight, event.n_presel_jet, event.jet0_pt, event.jet1_pt, event.jet2_pt, event.jet3_pt, event.jet0_CSV, event.jet1_CSV, event.jet2_CSV, event.jet3_CSV, event.jet0_eta, event.jet1_eta, event.jet2_eta, event.jet3_eta#, event.jet0_heppyFlavour, event.jet1_heppyFlavour, event.jet2_heppyFlavour, event.jet3_heppyFlavour#, event.lumiScale
        print w, event.PU_weight, event.MC_weight, event.leptonSF_weight, event.triggerSF_weight, event.FR_weight, event.n_fakeablesel_mu, event.n_fakeablesel_ele,
        #print event.ele0_ntMVAeleID, event.ele1_ntMVAeleID
        #print event.MVA_2lss_ttV, event.n_presel_jet, event.n_presel_mu, event.n_presel_ele, event.mindr_lep0_jet, event.mindr_lep1_jet, event.PFMET, event.avg_dr_jet, event.MT_met_lep0, event.mu0_pt, event.mu0_eta, event.ele0_pt, event.ele0_eta#, event.n_jet25_recl
        #w, event.PU_weight, event.MC_weight, event.leptonSF_weight, event.triggerSF_weight, event.FR_weight, event.n_fakeablesel_mu, event.n_fakeablesel_ele,
        #print event.ele0_charge, event.mu0_charge, event.tau0_charge 
        #print
        #print event.MVA_2lss_ttV, event.MVA_2lss_ttbar, event.bTagSF_weight, event.n_presel_jet, event.jet0_pt, event.jet1_pt, event.jet2_pt, event.jet3_pt, event.jet0_CSV, event.jet1_CSV, event.jet2_CSV, event.jet3_CSV, event.jet0_eta, event.jet1_eta, event.jet2_eta, event.jet3_eta#, event.jet0_heppyFlavour, event.jet1_heppyFlavour, event.jet2_heppyFlavour, event.jet3_heppyFlavour#, event.lumiScale
        #print event.tau0_pt, event.tau0_eta, event.tau0_phi
        #print event.ele0_ntMVAeleID, event.ele1_ntMVAeleID
        #print event.PU_weight, sgn(event.MC_weight), event.bTagSF_weight, event.leptonSF_weight, event.triggerSF_weight
        #if event.triggerSF_weight > 0:
        print 
        if abs(event.ele0_charge) < 2: sums_charge[0] += event.ele0_charge
        if abs(event.mu0_charge) < 2: sums_charge[1] += event.mu0_charge
        if abs(event.tau0_charge) < 2: sums_charge[2] += event.tau0_charge
      sums[0] += event.PU_weight
      sums[1] += event.MC_weight/abs(event.MC_weight)
      sums[2] += event.bTagSF_weight
      sums[3] += event.leptonSF_weight
      sums[4] += event.triggerSF_weight
      sums[5] += event.FR_weight
      sum_weights += w
      i += 1
      j += 1
  #print sums
  for k in range(len(sums)):
    sums[k] = sums[k] / j
  print "Sum of weights: ", j, sum_weights, sums
  #print sums_charge
  
if __name__ == "__main__":
  #print_weights('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/syncNtuple_event_ttH_80X_Summer16_old.root')
  print_weights('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/sync_ntuples_split_tight.root')
  #print_weights('/home/andres/tth/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync/comparison_ntuples/sync_ntuple_m17_v2_tight_triggerSF.root')

