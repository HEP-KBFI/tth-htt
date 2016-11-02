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
      , weight_ttZ_(-1.)
      , weight_ttZ_Zll_(-1.)
      , weight_tt_(-1.)
      , LR_(-1.)
    {}
    ~MEMOutput() {}
    void print(std::ostream& stream)
    {
      stream << "<MEMOutput (2lss_1tau)>:" << std::endl;
      stream << " type = " << type_ << std::endl;
      stream << " weights:" << std::endl;
      stream << "  ttH = " << weight_ttH_ << std::endl;
      stream << "  ttZ = " << weight_ttZ_ << std::endl;
      stream << "  ttZ(Z->ll) = " << weight_ttZ_Zll_ << std::endl;
      stream << "  tt = " << weight_tt_ << std::endl;
      stream << " LR = " << LR_ << std::endl;
      stream << " errorFlag = " << errorFlag_ << std::endl;
    }
    int errorFlag_;
    int type_; // either 0 (fully reconstructed W->jj decay) or 1 (one jet from W->jj decay not reconstructed)
    double weight_ttH_;
    double weight_ttZ_; // ttZ, Z->tautau->lep+tauh
    double weight_ttZ_Zll_; // ttZ, Z->ll
    double weight_tt_; // tt+jets (dilepton)
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
