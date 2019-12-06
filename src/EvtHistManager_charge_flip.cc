#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_charge_flip.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), createSubdirectory_recursively()

EvtHistManager_charge_flip::EvtHistManager_charge_flip(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void
EvtHistManager_charge_flip::bookHistograms(TFileDirectory & dir)
{
  // B-barrel, E-endcap
  // L-low pT (10 <= pT < 25), M-med pT (25 <= pT < 50), H-high pT (pT >= 50)
  const std::vector<std::string> categories_eta_and_pT = {
    "BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH",
    "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH",
    "BE_LL", "BE_ML", "BE_MM", "BE_HL", "BE_HM", "BE_HH",
             "EB_ML",          "EB_HL", "EB_HM",
    "total"
  };

  for(const std::string & category_eta_and_pT: categories_eta_and_pT)
  {
    std::string subdirName_SS = Form("SS/%s/%s", category_eta_and_pT.data(), process_.data());
    if(! category_.empty())
    {
      subdirName_SS += Form("/%s", category_.data());
    }
    TDirectory * const subdir_SS = createSubdirectory_recursively(dir, subdirName_SS, false);
    histograms_m_ee_SS_[category_eta_and_pT]             = book1D(subdir_SS, "mass_ll", "m_{ll}", 60,  60., 120.);
    histograms_m_ee_SS_mllBelow100_[category_eta_and_pT] = book1D(subdir_SS, "mass_ll_Below100", "m_{ll}", 40,  60., 100.);
    histograms_m_ee_SS_mllAbove100_[category_eta_and_pT] = book1D(subdir_SS, "mass_ll_Above100", "m_{ll}", 20,  100., 120.);

    std::string subdirName_OS = Form("OS/%s/%s", category_eta_and_pT.data(), process_.data());
    if(! category_.empty())
    {
      subdirName_OS += Form("/%s", category_.data());
    }
    TDirectory * const subdir_OS = createSubdirectory_recursively(dir, subdirName_OS, false);
    histograms_m_ee_OS_[category_eta_and_pT]             = book1D(subdir_OS, "mass_ll", "m_{ll}", 60,  60., 120.);
    histograms_m_ee_OS_mllBelow100_[category_eta_and_pT] = book1D(subdir_OS, "mass_ll_Below100", "m_{ll}", 40,  60., 100.);
    histograms_m_ee_OS_mllAbove100_[category_eta_and_pT] = book1D(subdir_OS, "mass_ll_Above100", "m_{ll}", 20,  100., 120.);
  }

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

namespace
{
  std::string
  getCategoryLabel_pT(double pT)
  {
    std::string category;
    if     (pT >= 10. && pT < 25.) category = "L";
    else if(pT >= 25. && pT < 50.) category = "M";
    else if(pT >= 50.            ) category = "H";
    else                           category = "out-of-range"; // CV: this can happen in
    // case generator-level electron has significantly lower pT than reconstructed electron
    return category;
  }

  std::string
  getCategoryLabel_absEta(double absEta)
  {
    return absEta <  1.479 ? "B" : "E";
  }
}

void
EvtHistManager_charge_flip::fillHistograms(const math::PtEtaPhiMLorentzVector & selElectron_lead_p4,
                                           const math::PtEtaPhiMLorentzVector & selElectron_sublead_p4,
                                           double m_ee,
                                           bool isCharge_SS,
                                           double evtWeight)
{
  const double evtWeightErr = 0.;

  const std::map<std::string, TH1 *> & histograms_m_ee = isCharge_SS ? histograms_m_ee_SS_ : histograms_m_ee_OS_;

  const std::string categoryLabel_absEta_lead = getCategoryLabel_absEta(std::fabs(selElectron_lead_p4.eta()));
  const std::string categoryLabel_pT_lead     = getCategoryLabel_pT(selElectron_lead_p4.pt());
  if(categoryLabel_pT_lead == "out-of-range")
  {
    return;
  }

  const std::string categoryLabel_absEta_sublead = getCategoryLabel_absEta(std::fabs(selElectron_sublead_p4.eta()));
  const std::string categoryLabel_pT_sublead     = getCategoryLabel_pT(selElectron_sublead_p4.pt());
  if(categoryLabel_pT_sublead == "out-of-range")
  {
    return;
  }

  std::string category;
  if(categoryLabel_pT_lead == categoryLabel_pT_sublead) // symmetric case
  {
    if(categoryLabel_absEta_lead == "E" && categoryLabel_absEta_sublead == "B")
    {
      category = Form("BE_%s%s", categoryLabel_pT_lead.data(), categoryLabel_pT_sublead.data());
    }
    else
    {
      category = Form(
        "%s%s_%s%s", categoryLabel_absEta_lead.data(), categoryLabel_absEta_sublead.data(),
                     categoryLabel_pT_lead.data(),     categoryLabel_pT_sublead.data()
      );
    }
  }
  else
  {
    category = Form(
      "%s%s_%s%s", categoryLabel_absEta_lead.data(), categoryLabel_absEta_sublead.data(),
                   categoryLabel_pT_lead.data(),     categoryLabel_pT_sublead.data()
    );
  }

  TH1 * histograms_m_ee_category = histograms_m_ee.at(category);
  assert(histograms_m_ee_category);
  fillWithOverFlow(histograms_m_ee_category, m_ee, evtWeight, evtWeightErr);

  TH1* histograms_m_ee_total = histograms_m_ee.at("total");
  assert(histograms_m_ee_total);
  fillWithOverFlow(histograms_m_ee_total, m_ee, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);

  const std::map<std::string, TH1 *> & histograms_m_ee_mllBelow100 = isCharge_SS ? histograms_m_ee_SS_mllBelow100_ : histograms_m_ee_OS_mllBelow100_;
  const std::map<std::string, TH1 *> & histograms_m_ee_mllAbove100 = isCharge_SS ? histograms_m_ee_SS_mllAbove100_ : histograms_m_ee_OS_mllAbove100_;
  if (m_ee < 100) {
    histograms_m_ee_category = histograms_m_ee_mllBelow100.at(category);
    assert(histograms_m_ee_category);
    fillWithOverFlow(histograms_m_ee_category, m_ee, evtWeight, evtWeightErr);
  } else {
    histograms_m_ee_category = histograms_m_ee_mllAbove100.at(category);
    assert(histograms_m_ee_category);
    fillWithOverFlow(histograms_m_ee_category, m_ee, evtWeight, evtWeightErr);
  }
}
