#ifndef EVTWEIGHTMANAGER_H
#define EVTWEIGHTMANAGER_H

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <Rtypes.h> // UChar_t, Float_t

// forward declarations
class TFile;
class TH1;
class TH2;

class EvtWeightManager
  : public ReaderBase
{
public:
  EvtWeightManager(const edm::ParameterSet & cfg);
  ~EvtWeightManager();

  void
  setBranchAddresses(TTree * tree) override;

  double
  getWeight() const;

protected:
  std::string binnedHistogram_varName_x_;
  std::string binnedHistogram_varName_y_;
  std::string binnedHistogram_varType_x_;
  std::string binnedHistogram_varType_y_;

  UChar_t var_x_uchar_;
  Float_t var_x_float_;
  UChar_t var_y_uchar_;
  Float_t var_y_float_;

  TFile * histogram_file_;
  TH1 * binnedHistogram_1var_;
  TH2 * binnedHistogram_2var_;
};

#endif // EVTWEIGHTMANAGER_H
