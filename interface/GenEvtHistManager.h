#ifndef tthAnalysis_HiggsToTauTau_GenEvtHistManager_h
#define tthAnalysis_HiggsToTauTau_GenEvtHistManager_h

/** \class GenEvtHistManager
 *
 * Book and fill histograms for event-level quantities on generator level in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

// forward declarations
class EvtWeightManager;

class GenEvtHistManager
  : public HistManagerBase
{
public:
  GenEvtHistManager(const edm::ParameterSet & cfg);
  ~GenEvtHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const std::vector<GenLepton> & genElectrons,
                 const std::vector<GenLepton> & genMuons,
                 const std::vector<GenHadTau> & genHadTaus,
                 const std::vector<GenPhoton> & genPhotons,
                 const std::vector<GenJet> & genJets,
                 double lumiScale,
                 double evtWeight = 1.);

  void
  bookHistograms(TFileDirectory & dir,
                 const EvtWeightManager * const eventWeightManager);

  void
  fillHistograms(const EvtWeightManager * const eventWeightManager,
                 double evtWeight);

private:
  double minGenElectronPt_;
  double maxGenElectronAbsEta_;
  double minGenMuonPt_;
  double maxGenMuonAbsEta_;
  double minGenHadTauPt_;
  double maxGenHadTauAbsEta_;
  double minGenPhotonPt_;
  double maxGenPhotonAbsEta_;
  double minGenJetPt_;
  double maxGenJetAbsEta_;

  TH1 * histogram_numGenElectrons_withinAcc_;
  TH1 * histogram_numGenMuons_withinAcc_;
  TH1 * histogram_numGenLeptons_withinAcc_;
  TH1 * histogram_numGenPhotons_withinAcc_;
  TH1 * histogram_numGenElectronsAndPhotons_withinAcc_;
  TH1 * histogram_numGenHadTaus_withinAcc_;
  TH1 * histogram_numGenLeptonsAndHadTaus_withinAcc_;
  TH1 * histogram_numGenJets_withinAcc_;
  TH1 * histogram_numGenLeptonsAndHadTausAndJets_withinAcc_;

  TH1 * histogram_lumiScale_;
  TH1 * histogram_EventCounter_;

  TH1 * histogram_evtWeightManager_1D_;
  TH1 * histogram_evtWeightManager_1D_counter_;
  TH2 * histogram_evtWeightManager_2D_;
  TH2 * histogram_evtWeightManager_2D_counter_;
};

#endif
