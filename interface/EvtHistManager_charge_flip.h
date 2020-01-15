#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_charge_flip_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_charge_flip_h

/** \class EvtHistManager_charge_flip
 *
 * Book and fill histograms for event-level quantities in electron charge misidentification rate measurement
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include <DataFormats/Math/interface/LorentzVector.h> // math::PtEtaPhiMLorentzVector

class EvtHistManager_charge_flip
  : public HistManagerBase
{
public:
  EvtHistManager_charge_flip(const edm::ParameterSet & cfg);
  ~EvtHistManager_charge_flip() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const math::PtEtaPhiMLorentzVector & selElectron_lead_p4,
                 const math::PtEtaPhiMLorentzVector & selElectron_sublead_p4,
                 double m_ee,
                 bool isCharge_SS,
                 double evtWeight);

private:
  std::map<std::string, TH1 *> histograms_m_ee_SS_; // key = event category, based on pT and eta of the two electrons
  std::map<std::string, TH1 *> histograms_m_ee_OS_; // key = event category, based on pT and eta of the two electrons

  std::map<std::string, TH1 *> histograms_m_ee_SS_mllBelow100_; //
  std::map<std::string, TH1 *> histograms_m_ee_OS_mllBelow100_; //

  std::map<std::string, TH1 *> histograms_m_ee_SS_mllAbove100_; //
  std::map<std::string, TH1 *> histograms_m_ee_OS_mllAbove100_; //

  std::map<std::string, TH1 *> histograms_m_ee_SS_ePtThrsh15_; 
  std::map<std::string, TH1 *> histograms_m_ee_OS_ePtThrsh15_; 
  
  std::map<std::string, TH1 *> histograms_pT_eLead_SS_;
  std::map<std::string, TH1 *> histograms_pT_eLead_OS_; 
  std::map<std::string, TH1 *> histograms_pT_eSublead_SS_;
  std::map<std::string, TH1 *> histograms_pT_eSublead_OS_; 
  
  TH1 * histogram_EventCounter_;
};

#endif
