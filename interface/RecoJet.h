#ifndef tthAnalysis_HiggsToTauTau_RecoJet_h
#define tthAnalysis_HiggsToTauTau_RecoJet_h

#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#include <map>
#include <ostream>

class RecoJet
  : public GenJet
{
public:
  RecoJet() = default;
  RecoJet(Double_t pt,
          Double_t eta,
          Double_t phi,
          Double_t mass,
	  Double_t corr,
	  Double_t corr_JECUp,
	  Double_t corr_JECDown,
	  Double_t BtagCSV,          
	  Double_t BtagWeight,
          Int_t idx);

  Double_t corr_;         ///< nominal jet energy correction (L1FastL2L3 for MC, L1FastL2L3Residual for data)
  Double_t corr_JECUp_;   ///< +1 sigma (upward shifted) jet energy correction
  Double_t corr_JECDown_; ///< -1 sigma (downward shifted) jet energy correction
  Double_t BtagCSV_;      ///< CSV b-tagging discriminator value
  Double_t BtagWeight_;   ///< weight for data/MC correction of b-tagging efficiency and mistag rate
  Int_t idx_;             ///< index of jet in the ntuple

  //---------------------------------------------------------
  // CV: needed by RecoJetWriter
  Double_t BtagCSVwHipMitigation_;  
  Double_t BtagCSVwoHipMitigation_; 
  std::map<int, Double_t> BtagWeight_systematics_; 
  //---------------------------------------------------------

//--- matching to generator level particles
  const GenLepton* genLepton_;
  const GenHadTau* genHadTau_;
  const GenJet* genJet_;
};

std::ostream& operator<<(std::ostream& stream, const RecoJet& jet);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h

