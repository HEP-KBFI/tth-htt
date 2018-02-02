#ifndef MEtFilter_H
#define MEtFilter_H

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // *_TYPE, *_KEY

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class MEtFilter
{
public:
  MEtFilter();

  bool getFlag_HBHENoiseIsoFilter() const;
  bool getFlag_EcalDeadCellTriggerPrimitiveFilter() const;
  bool getFlag_ecalLaserCorrFilter() const;
  bool getFlag_hcalLaserEventFilter() const;
  bool getFlag_muonBadTrackFilter() const;
  bool getFlag_trkPOGFilters() const;
  bool getFlag_trackingFailureFilter() const;
  bool getFlag_CSCTightHaloFilter() const;
  bool getFlag_HBHENoiseFilter() const;
  bool getFlag_chargedHadronTrackResolutionFilter() const;
  bool getFlag_GlobalTightHalo2016Filter() const;
  bool getFlag_METFilters() const;
  bool getFlag_CSCTightHalo2015Filter() const;
  bool getFlag_eeBadScFilter() const;
  bool getFlag_trkPOG_manystripclus53X() const;
  bool getFlag_trkPOG_toomanystripclus53X() const;
  bool getFlag_trkPOG_logErrorTooManyClusters() const;
  bool getFlag_goodVertices() const;

  friend class MEtFilterReader;

 protected:
  int Flag_HBHENoiseIsoFilter_;
  int Flag_EcalDeadCellTriggerPrimitiveFilter_;
  int Flag_ecalLaserCorrFilter_;
  int Flag_hcalLaserEventFilter_;
  int Flag_muonBadTrackFilter_;
  int Flag_trkPOGFilters_;
  int Flag_trackingFailureFilter_;
  int Flag_CSCTightHaloFilter_;
  int Flag_HBHENoiseFilter_;
  int Flag_chargedHadronTrackResolutionFilter_;
  int Flag_GlobalTightHalo2016Filter_;
  int Flag_METFilters_;
  int Flag_CSCTightHalo2015Filter_;
  int Flag_eeBadScFilter_;
  int Flag_trkPOG_manystripclus53X_;
  int Flag_trkPOG_toomanystripclus53X_;
  int Flag_trkPOG_logErrorTooManyClusters_;
  int Flag_goodVertices_;




  /*
  MEtFilter(bool is_signal,
            bool is_mc,
            bool is_mc_th);
  MEtFilter(const MEtFilter & eventInfo);
  MEtFilter &
  operator=(const MEtFilter & eventInfo);

  RUN_TYPE               run;               ///< run number
  LUMI_TYPE              lumi;              ///< luminosity
  EVT_TYPE               event;             ///< event number
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode; ///< Higgs decay mode (only if MC signal)
  GENWEIGHT_TYPE         genWeight;         ///< generator-level weight (only if MC)
  GENWEIGHTTH_TYPE       genWeight_tH;      ///< reweight tH MC sample from kappa=-1 to kappa=+1 (SM) case
  PUWEIGHT_TYPE          pileupWeight;      ///< pile-up weight (only if MC)

  bool
  is_signal() const;

  bool
  is_mc() const;

  bool
  is_mc_th() const;

  bool
  is_initialized() const;

  std::string
  getDecayModeString() const;

  static std::vector<std::string>
  getDecayModes();

  friend std::ostream &
  operator<<(std::ostream & os,
             const MEtFilter & info);

  friend class MEtFilterWriter;

private:
  bool is_signal_;
  bool is_mc_;
  bool is_mc_th_;

  static const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString;
  */


};

#endif // MEtFilter_H
