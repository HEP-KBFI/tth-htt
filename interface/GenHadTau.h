#ifndef tthAnalysis_HiggsToTauTau_GenHadTau_h
#define tthAnalysis_HiggsToTauTau_GenHadTau_h

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle

class GenHadTau : public Particle
{
 public:
  GenHadTau() = default;
  GenHadTau(Double_t pt,
	    Double_t eta,
	    Double_t phi,
	    Double_t mass, 
	    Int_t charge);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Int_t charge() const { return charge_; } 

 protected:
  Int_t charge_; ///< charge of hadronic tau (either +1 or -1)
};

#endif // tthAnalysis_HiggsToTauTau_GenHadTau_h
