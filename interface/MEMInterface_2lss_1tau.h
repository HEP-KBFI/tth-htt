#ifndef tthAnalysis_HiggsToTauTau_MEMInterface_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMInterface_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/RunConfig.h" // RunConfig

#include <TMatrixD.h> // TMatrixD

#include <vector>
#include <string>

class MEMInterface_2lss_1tau
{
 public:
  MEMInterface_2lss_1tau(const std::string& configFileName);
  ~MEMInterface_2lss_1tau();

  /**
   * @brief Calculates output of MEM integration.
   * @param pointers to leading and subleading lepton, hadronic tau, MET and MET covariance matrix, collections of b-tagged jets and non-b-tagged jets
   * @return object with         MVA output
   */

  struct MEMOutput
  {
    MEMOutput()
      : errorFlag_(0)
      , type_(-1)
      , weight_ttH_(-1.)
      , weight_ttZ1_(-1.)
      , weight_ttZ2_(-1.)
      , weight_tt1_(-1.)
      , weight_tt2_(-1.)
      , LR_(-1.)
    {}
    ~MEMOutput() {}
    void print(std::ostream& stream)
    {
      stream << "<MEMOutput (2lss_1tau)>:" << std::endl;
      stream << " type = " << type_ << std::endl;
      stream << " weights:" << std::endl;
      stream << "  ttH = " << weight_ttH_ << std::endl;
      stream << "  ttZ(1) = " << weight_ttZ1_ << std::endl;
      stream << "  ttZ(2) = " << weight_ttZ2_ << std::endl;
      stream << "  tt(1) = " << weight_tt1_ << std::endl;
      stream << "  tt(2) = " << weight_tt2_ << std::endl;
      stream << " LR = " << LR_ << std::endl;
      stream << " errorFlag = " << errorFlag_ << std::endl;
    }
    int errorFlag_;
    int type_; // either 0 (fully reconstructed W->jj decay) or 1 (one jet from W->jj decay not reconstructed)
    double weight_ttH_;
    double weight_ttZ1_; // Z->tautau->lep + tauh
    double weight_ttZ2_; // Z->ll
    double weight_tt1_;  // "tt DL, fake lep. from tlep"
    double weight_tt2_;  // "tt DL, fake lep. from tau"
    double LR_;
  };
  MEMOutput
  operator()(const RecoLepton* selLepton_lead, const RecoLepton* selLepton_sublead, const RecoHadTau* selHadTau, 
	     double metPx, double metPy, const TMatrixD& metCov,
	     const std::vector<const RecoJet*>& selJets);

 private:
  RunConfig* config_;
};

#endif // MEMInterface_2lss_1tau_h
