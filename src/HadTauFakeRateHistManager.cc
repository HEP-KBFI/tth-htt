#include "tthAnalysis/HiggsToTauTau/interface/HadTauFakeRateHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>
#include <TString.h>

HadTauFakeRateHistManager::HadTauFakeRateHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  etaBins_lead_ = cfg.getParameter<vdouble>("etaBins_lead");
  numEtaBins_lead_ = etaBins_lead_.size() - 1;
  etaBins_sublead_ = cfg.getParameter<vdouble>("etaBins_sublead");
  numEtaBins_sublead_ = etaBins_sublead_.size() - 1;
}

namespace
{
  std::string getParticleEtaLabel(double etaMin_lead, double etaMax_lead, double etaMin_sublead, double etaMax_sublead)
  {
    std::string etaBin_label = "";
    if ( etaMin_lead > 0. && etaMax_lead < 5. ) {
      etaBin_label.append(Form("hadTau1Eta%1.1fto%1.1f", etaMin_lead, etaMax_lead));
    } else if ( etaMin_lead > 0. ) {
      etaBin_label.append(Form("hadTau1EtaGt%1.1f", etaMin_lead));
    } else if ( etaMax_lead < 5. ) {
      etaBin_label.append(Form("hadTau1EtaLt%1.1f", etaMax_lead));
    }
    if ( etaMin_sublead > 0. && etaMax_sublead < 5. ) {
      etaBin_label.append(Form("hadTau2Eta%1.1fto%1.1f", etaMin_sublead, etaMax_sublead));
    } else if ( etaMin_sublead > 0. ) {
      etaBin_label.append(Form("hadTau2EtaGt%1.1f", etaMin_sublead));
    } else if ( etaMax_sublead < 5. ) {
      etaBin_label.append(Form("hadTau2EtaLt%1.1f", etaMax_sublead));
    }
    etaBin_label = TString(etaBin_label).ReplaceAll(".", "").Data();
    return etaBin_label;
  }
}

void HadTauFakeRateHistManager::bookHistograms(TFileDirectory& dir)
{
  const int numPtBins = 20;
  float ptBinning[numPtBins + 1] = { 
    0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 90., 100., 120., 140., 160., 180., 200.
  };

  for ( int idxEtaBin_lead = 0; idxEtaBin_lead < numEtaBins_lead_; ++idxEtaBin_lead ) {
    double etaMin_lead = etaBins_lead_[idxEtaBin_lead];
    double etaMax_lead = etaBins_lead_[idxEtaBin_lead + 1];
    std::string etaBin_label = getParticleEtaLabel(etaMin_lead, etaMax_lead, -1., 9.9);
    std::string histogramName_pt_lead = Form("hadTauPt_lead_%s", etaBin_label.data());
    histograms_pt_lead_.push_back(new histogramIn1dParticleEtaBinsEntryType(
      etaMin_lead, etaMax_lead, book1D(dir, histogramName_pt_lead.data(), histogramName_pt_lead.data(), numPtBins, ptBinning)));
  }
  for ( int idxEtaBin_sublead = 0; idxEtaBin_sublead < numEtaBins_sublead_; ++idxEtaBin_sublead ) {
    double etaMin_sublead = etaBins_sublead_[idxEtaBin_sublead];
    double etaMax_sublead = etaBins_sublead_[idxEtaBin_sublead + 1];
    std::string etaBin_label = getParticleEtaLabel(etaMin_sublead, etaMax_sublead, -1., 9.9);
    std::string histogramName_pt_sublead = Form("hadTauPt_sublead_%s", etaBin_label.data());
    histograms_pt_sublead_.push_back(new histogramIn1dParticleEtaBinsEntryType(
      etaMin_sublead, etaMax_sublead, book1D(dir, histogramName_pt_sublead.data(), histogramName_pt_sublead.data(), numPtBins, ptBinning)));
  }
  
  for ( int idxEtaBin_lead = 0; idxEtaBin_lead < numEtaBins_lead_; ++idxEtaBin_lead ) {
    double etaMin_lead = etaBins_lead_[idxEtaBin_lead];
    double etaMax_lead = etaBins_lead_[idxEtaBin_lead + 1];
    for ( int idxEtaBin_sublead = 0; idxEtaBin_sublead < numEtaBins_sublead_; ++idxEtaBin_sublead ) {
      double etaMin_sublead = etaBins_sublead_[idxEtaBin_sublead];
      double etaMax_sublead = etaBins_sublead_[idxEtaBin_sublead + 1];
      std::string etaBin_label = getParticleEtaLabel(etaMin_lead, etaMax_lead, etaMin_sublead, etaMax_sublead);
      histograms_EventCounter_.push_back(new histogramIn2dParticleEtaBinsEntryType(
        etaMin_lead, etaMax_lead, etaMin_sublead, etaMax_sublead, book1D(dir, Form("EventCounter_%s", etaBin_label.data()), "", 1, -0.5, +0.5)));
    }
  }
}

void HadTauFakeRateHistManager::fillHistograms(const RecoHadTau* hadTau_lead, const RecoHadTau* hadTau_sublead, double evtWeight)
{
  double evtWeightErr = 0.;
  
  double hadTau_lead_pt = hadTau_lead->pt_;
  double hadTau_lead_absEta = std::fabs(hadTau_lead->eta_);
  double hadTau_sublead_pt = hadTau_sublead->pt_;
  double hadTau_sublead_absEta = std::fabs(hadTau_sublead->eta_);
  
  for ( std::vector<histogramIn1dParticleEtaBinsEntryType*>::iterator histogram_pt_lead = histograms_pt_lead_.begin();
        histogram_pt_lead != histograms_pt_lead_.end(); ++histogram_pt_lead ) {
    (*histogram_pt_lead)->Fill(hadTau_lead_absEta, hadTau_lead_pt, evtWeight, evtWeightErr); 
  }
  for ( std::vector<histogramIn1dParticleEtaBinsEntryType*>::iterator histogram_pt_sublead = histograms_pt_sublead_.begin();
        histogram_pt_sublead != histograms_pt_sublead_.end(); ++histogram_pt_sublead ) {
    (*histogram_pt_sublead)->Fill(hadTau_sublead_absEta, hadTau_sublead_pt, evtWeight, evtWeightErr); 
  }

  for ( std::vector<histogramIn2dParticleEtaBinsEntryType*>::iterator histogram_EventCounter = histograms_EventCounter_.begin();
        histogram_EventCounter != histograms_EventCounter_.end(); ++histogram_EventCounter ) {
    (*histogram_EventCounter)->Fill(hadTau_lead_absEta, hadTau_sublead_absEta, 0., evtWeight, evtWeightErr); 
  }
}
