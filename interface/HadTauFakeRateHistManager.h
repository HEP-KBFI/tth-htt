#ifndef tthAnalysis_HiggsToTauTau_HadTauFakeRateHistManager_h
#define tthAnalysis_HiggsToTauTau_HadTauFakeRateHistManager_h

/** \class HadTauFakeRateHistManager
 *
 * Book and fill histograms for measuring jet->tau misidentification rate in tt+jets events
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

class HadTauFakeRateHistManager
  : public HistManagerBase
{
 public:
  HadTauFakeRateHistManager(edm::ParameterSet const& cfg);
  ~HadTauFakeRateHistManager() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const RecoHadTau* hadTau_lead, const RecoHadTau* hadTau_sublead, double evtWeight);

 private:
  typedef std::vector<double> vdouble;
  vdouble etaBins_lead_;
  int numEtaBins_lead_;
  vdouble etaBins_sublead_;
  int numEtaBins_sublead_;

  struct histogramIn1dParticleEtaBinsEntryType
  {
    histogramIn1dParticleEtaBinsEntryType(double etaMin, double etaMax, TH1* histogram)
      : etaMin_(etaMin),
        etaMax_(etaMax),
        histogram_(histogram)
    {}
    ~histogramIn1dParticleEtaBinsEntryType() {}
    void Fill(double absEta, double x, double evtWeight, double evtWeightErr)
    {
      if ( (etaMin_ < 0. || absEta > etaMin_) && (etaMax_ > 5. || absEta < etaMax_) ) {
        fillWithOverFlow(histogram_, x, evtWeight, evtWeightErr);
      }
    }
    double etaMin_;
    double etaMax_;
    TH1* histogram_;
  };
  std::vector<histogramIn1dParticleEtaBinsEntryType*> histograms_pt_lead_;
  std::vector<histogramIn1dParticleEtaBinsEntryType*> histograms_pt_sublead_;

  struct histogramIn2dParticleEtaBinsEntryType
  {
    histogramIn2dParticleEtaBinsEntryType(double etaMin_lead, double etaMax_lead, double etaMin_sublead, double etaMax_sublead, TH1* histogram)
      : etaMin_lead_(etaMin_lead),
        etaMax_lead_(etaMax_lead),
        etaMin_sublead_(etaMin_sublead),
        etaMax_sublead_(etaMax_sublead),
        histogram_(histogram)
    {}
    ~histogramIn2dParticleEtaBinsEntryType() {}
    void Fill(double absEta_lead, double absEta_sublead, double x, double evtWeight, double evtWeightErr)
    {
      if ( (etaMin_lead_ < 0. || absEta_lead > etaMin_lead_) && (etaMax_lead_ > 5. || absEta_lead < etaMax_lead_) &&
           (etaMin_sublead_ < 0. || absEta_sublead > etaMin_sublead_) && (etaMax_sublead_ > 5. || absEta_sublead < etaMax_sublead_) ) {
        fillWithOverFlow(histogram_, x, evtWeight, evtWeightErr);
      }
    }
    double etaMin_lead_;
    double etaMax_lead_;
    double etaMin_sublead_;
    double etaMax_sublead_;
    TH1* histogram_;
  };

  std::vector<histogramIn2dParticleEtaBinsEntryType*> histograms_EventCounter_;
};

#endif
