#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_charge_flip.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <TMath.h>

EvtHistManager_charge_flip::EvtHistManager_charge_flip(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_charge_flip::bookHistograms(TFileDirectory& dir)
{
  std::vector<std::string> categories_eta_and_pT = {  //B-barrel, E-endcap, L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT >= 50)
    "BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", 
    "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", 
    "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", 
    "total"
  };
  for ( std::vector<std::string>::const_iterator category_eta_and_pT = categories_eta_and_pT.begin();
	category_eta_and_pT != categories_eta_and_pT.end(); ++category_eta_and_pT ) {
    std::string subdirName_SS = Form("SS/%s/%s", category_eta_and_pT->data(), process_.data());
    TDirectory* subdir_SS = createSubdirectory_recursively(dir, subdirName_SS, false);
    subdir_SS->cd();
    TH1* histogram_m_ee_SS = new TH1D(getHistogramName("mass_ll").data(), "m_{ll}", 60,  60., 120. );
    histogram_m_ee_SS->Sumw2();
    histograms_m_ee_SS_[*category_eta_and_pT] = histogram_m_ee_SS;

    std::string subdirName_OS = Form("OS/%s/%s", category_eta_and_pT->data(), process_.data());
    TDirectory* subdir_OS = createSubdirectory_recursively(dir, subdirName_OS, false);
    subdir_OS->cd();
    TH1* histogram_m_ee_OS = new TH1D(getHistogramName("mass_ll").data(), "m_{ll}", 60,  60., 120. );
    histogram_m_ee_OS->Sumw2();
    histograms_m_ee_OS_[*category_eta_and_pT] = histogram_m_ee_OS;
  }

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

namespace
{
  std::string getCategoryLabel_pT(double pT)
  {
    std::string category;
    if      ( pT >= 10. && pT < 25. ) category = "L";
    else if ( pT >= 25. && pT < 50. ) category = "M";
    else if ( pT >= 50.             ) category = "H";
    else assert(0);
    return category;
  }

  std::string getCategoryLabel_absEta(double absEta)
  {
    std::string category;
    if ( absEta <  1.479 ) category = "B";
    else category = "E";
    return category;
  }
}

void EvtHistManager_charge_flip::fillHistograms(const math::PtEtaPhiMLorentzVector& selElectron_lead_p4, 
						const math::PtEtaPhiMLorentzVector& selElectron_sublead_p4, 
						double m_ee, bool isCharge_SS, double evtWeight)
{
  double evtWeightErr = 0.;

  std::map<std::string, TH1*>* histograms_m_ee = 0;
  if ( isCharge_SS ) histograms_m_ee = &histograms_m_ee_SS_;
  else histograms_m_ee = &histograms_m_ee_OS_;
  std::string categoryLabel_absEta_lead = getCategoryLabel_absEta(std::fabs(selElectron_lead_p4.eta()));
  std::string categoryLabel_pT_lead = getCategoryLabel_pT(selElectron_lead_p4.pt());
  std::string categoryLabel_absEta_sublead = getCategoryLabel_absEta(std::fabs(selElectron_sublead_p4.eta()));
  std::string categoryLabel_pT_sublead = getCategoryLabel_pT(selElectron_sublead_p4.pt());
  std::string category;
  if ( categoryLabel_pT_lead == categoryLabel_pT_sublead ) { // symmetric case
    if ( categoryLabel_absEta_lead == "E" && categoryLabel_absEta_sublead == "B" ) category = Form("BE_%s%s", categoryLabel_pT_lead.data(), categoryLabel_pT_sublead.data());
    else category = Form("%s%s_%s%s", categoryLabel_absEta_lead.data(), categoryLabel_absEta_sublead.data(), categoryLabel_pT_lead.data(), categoryLabel_pT_sublead.data());
  } else {
    category = Form("%s%s_%s%s", categoryLabel_absEta_lead.data(), categoryLabel_absEta_sublead.data(), categoryLabel_pT_lead.data(), categoryLabel_pT_sublead.data());
  }
  TH1* histograms_m_ee_category = (*histograms_m_ee)[category];
  assert(histograms_m_ee_category);
  fillWithOverFlow(histograms_m_ee_category, m_ee, evtWeight, evtWeightErr);
  TH1* histograms_m_ee_total = (*histograms_m_ee)["total"];
  assert(histograms_m_ee_total);
  fillWithOverFlow(histograms_m_ee_total, m_ee, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
