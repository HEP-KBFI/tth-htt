#ifndef tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutput_2lss_1tau_h

#include <Rtypes.h> // Int_t, Float_t

#include <iostream> 
#include <iomanip> 

class MEMOutput_2lss_1tau
{
 public:
  MEMOutput_2lss_1tau();
  MEMOutput_2lss_1tau(Float_t leadLepton_eta,
		      Float_t leadLepton_phi,
		      Float_t subleadLepton_eta,
		      Float_t subleadLepton_phi,
		      Float_t hadTau_eta,
		      Float_t hadTau_phi,
		      Int_t type,
		      Float_t weight_ttH,
		      Float_t weight_ttZ,
		      Float_t weight_ttZ_Zll,
		      Float_t weight_tt,
		      Float_t LR,
		      Float_t cpuTime,
		      Float_t realTime,
		      Int_t errorFlag);
  ~MEMOutput_2lss_1tau() {}

  void print(std::ostream& stream);

  Float_t leadLepton_eta_;
  Float_t leadLepton_phi_;
  Float_t subleadLepton_eta_;
  Float_t subleadLepton_phi_;
  Float_t hadTau_eta_;
  Float_t hadTau_phi_;
  Int_t type_; // either 0 (fully reconstructed W->jj decay) or 1 (one jet from W->jj decay not reconstructed)
  Float_t weight_ttH_;
  Float_t weight_ttZ_; // ttZ, Z->tautau->lep+tauh
  Float_t weight_ttZ_Zll_; // ttZ, Z->ll
  Float_t weight_tt_; // tt+jets (dilepton)
  Float_t LR_;
  Float_t cpuTime_;
  Float_t realTime_;
  Int_t errorFlag_;
};

#endif // MEMOutput_2lss_1tau_h
