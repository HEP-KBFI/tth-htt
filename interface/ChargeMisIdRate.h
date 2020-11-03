#ifndef tthAnalysis_HiggsToTauTau_ChargeMisIdRate_h
#define tthAnalysis_HiggsToTauTau_ChargeMisIdRate_h

#include <string> // std::string
#include <map> // std::map<,>

enum class Era;

class TFile;
class lutWrapperBase;
class RecoLepton;

class ChargeMisIdRate
{
public:
  ChargeMisIdRate(Era era,
                  const std::string & lep_mva_wp = "default",
                  bool wTightCharge = true,
                  bool isDEBUG = false);

  ~ChargeMisIdRate();

  double
  get(const RecoLepton * const lepton) const;

  double
  get(const RecoLepton * const lepton_lead,
      const RecoLepton * const lepton_sublead) const;

protected:
  std::map<std::string, TFile *> inputFiles_;
  lutWrapperBase * chargeMisId_;

  bool isDEBUG_;
};

#endif // tthAnalysis_HiggsToTauTau_ChargeMisIdRate_h
