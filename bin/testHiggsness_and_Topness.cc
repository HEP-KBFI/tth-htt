
/**
   \class testHiggsness_and_Topness testHiggsness_and_Topness.cc "tthAnalysis/HiggsToTauTau/bin/testHiggsness_and_Topness.cc"
   \brief Basic example of the use of the code that computes the "Higgsness" and "Topness" variables described in the paper
          "Measuring the triple Higgs self-interaction at the Large Hadron Collider"; J.H. Kim, K. Kong, K.T. Matchev, M. Park; arXiv: 1807.11498
*/

#include "tthAnalysis/HiggsToTauTau/interface/Higgsness.h" // Higgsness
#include "tthAnalysis/HiggsToTauTau/interface/Topness.h" // Topness
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // compSmin

#include <TBenchmark.h> // TBenchmark

int main(int argc, char* argv[])
{
//--- keep track of time it takes the "Higgsness" and "Topness" computation to execute
  TBenchmark clock;
  clock.Start("testHiggsness_and_Topness");

  Higgsness algoHiggsness(Higgsness::kPublishedChi2);
  Topness algoTopness(Topness::kPublishedChi2);

  /*
     This is a single HH->bbWW->bb lnu lnu signal event for testing purposes.
  */

  Particle::LorentzVector lepton1P4_sig(173.796, 0.805758, 2.85071, 0.268879); // muon with mass different from PDG value due to rounding errors
  Particle::LorentzVector lepton2P4_sig(69.1767, 1.01891, 2.34244, -0.247972); // electron with mass different from PDG value due to rounding errors
  Particle::LorentzVector jet1P4_sig(63.6049, 0.705758, 0.166227, 5.45375);
  Particle::LorentzVector jet2P4_sig(28.1414, -0.351487, 4.93853, 4.9031);
  double metPx_sig = 10.1954;
  double metPy_sig = -10.9762;
    
  algoHiggsness.fit(lepton1P4_sig, lepton2P4_sig, metPx_sig, metPy_sig);
  double logHiggsness_sig = algoHiggsness.logHiggsness();
  algoTopness.fit(lepton1P4_sig, lepton2P4_sig, jet1P4_sig, jet2P4_sig, metPx_sig, metPy_sig);
  double logTopness_sig = algoTopness.logTopness();
  std::cout << "signal event:" << std::endl;
  std::cout << " log(Higgsness) = " << logHiggsness_sig << " (expected value = 5.34402),"
	    << " log(Topness) = " << logTopness_sig << " (expected value = 4.07724)" << std::endl;
  std::cout << " Smin(bbll) = " << comp_Smin(lepton1P4_sig + lepton2P4_sig + jet1P4_sig + jet2P4_sig, metPx_sig, metPy_sig) << " (expected value = 338.929),"
	    << " Smin(ll) = " << comp_Smin(lepton1P4_sig + lepton2P4_sig, metPx_sig, metPy_sig) << " (expected value = 132.146)" << std::endl;

  /*
    This is a single tt->b lnu b lnu background event for testing purposes.
  */

  Particle::LorentzVector lepton1P4_bgr(47.9858, 2.2177, 4.66543, -0.125059); // muon with mass different from PDG value due to rounding errors
  Particle::LorentzVector lepton2P4_bgr(27.0065, 1.65893, 5.34423, 0.117962); // muon with mass different from PDG value due to rounding errors
  Particle::LorentzVector jet1P4_bgr(61.1435, 0.985798, 4.24091, 7.74251);
  Particle::LorentzVector jet2P4_bgr(48.9992, 1.94858, 2.58681, 8.04078);
  double metPx_bgr = 55.572;
  double metPy_bgr = 106.657;
    
  algoHiggsness.fit(lepton1P4_bgr, lepton2P4_bgr, metPx_bgr, metPy_bgr);
  double logHiggsness_bgr = algoHiggsness.logHiggsness();
  algoTopness.fit(lepton1P4_bgr, lepton2P4_bgr, jet1P4_bgr, jet2P4_bgr, metPx_bgr, metPy_bgr);
  double logTopness_bgr = algoTopness.logTopness();
  std::cout << "background event:" << std::endl;
  std::cout << " log(Higgsness) = " << logHiggsness_bgr << " (expected value = 7.27764)" << ","
	    << " log(Topness) = " << logTopness_bgr << " (expected value = 3.30145)" << std::endl;
  std::cout << " Smin(bbll) = " << comp_Smin(lepton1P4_bgr + lepton2P4_bgr + jet1P4_bgr + jet2P4_bgr, metPx_bgr, metPy_bgr) << " (expected value = 330.792),"
	    << " Smin(ll) = " << comp_Smin(lepton1P4_bgr + lepton2P4_bgr, metPx_bgr, metPy_bgr) << " (expected value = 181.75)" << std::endl;
  
  clock.Show("testHiggsness_and_Topness");

  std::cout << std::endl;
  std::cout << "************************************************************************************************************************" << std::endl;
  std::cout << "* If you use this code, please cite:                                                                                   *" << std::endl;
  std::cout << "*   J.H. Kim, K. Kong, K.T. Matchev, M. Park,                                                                          *" << std::endl;
  std::cout << "*   \"Measuring the triple Higgs self-interaction at the Large Hadron Collider\",                                         *" << std::endl;
  std::cout << "*   arXiv: 1807.11498                                                                                                   *" << std::endl;
  std::cout << "************************************************************************************************************************" << std::endl;
  std::cout << std::endl;

  return 0;
}
