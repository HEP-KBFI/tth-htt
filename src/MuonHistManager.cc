#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

#include <TMath.h> // TMath::Pi()

MuonHistManager::MuonHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , option_(kOption_undefined)
  , idx_(cfg.getParameter<int>("idx"))
{
  const std::string option_string = cfg.getParameter<std::string>("option");
  if(option_string == "allHistograms")
  {
    option_ = kOption_allHistograms;
  }
  else if(option_string == "minimalHistograms")
  {
    option_ = kOption_minimalHistograms;
  }
  else
  {
    throw cmsException(__func__) << "Invalid Configuration parameter 'option' = " << option_string;
  }
  const std::vector<std::string> sysOpts_central = {
    "cone_pt",
    "eta",
    "phi",
    "abs_genPdgId",
    "pt",
    "assocJet_pt",
    "charge",
    "dxy",
    "dz",
    "relIso",
    "sip3d",
    "mvaRawTTH",
    "jetPtRatio",
    "jetBtagCSV",
    "tightCharge",
    "passesLooseIdPOG",
    "passesMediumIdPOG",
    "gen_times_recCharge",
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
}

void
MuonHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_cone_pt_               = book1D(dir, "cone_pt",             "cone_pt",             40,  0., 200.);
  histogram_eta_                   = book1D(dir, "eta",                 "eta",                 48, -2.4,  +2.4);
  histogram_phi_                   = book1D(dir, "phi",                 "phi",                 36, -TMath::Pi(), +TMath::Pi());
  histogram_abs_genPdgId_          = book1D(dir, "abs_genPdgId",        "abs_genPdgId",        22, -0.5, +21.5);

  if ( option_ == kOption_allHistograms ) {
    histogram_pt_                  = book1D(dir, "pt",                  "pt",                  40,  0.,  200.);
    histogram_assocJet_pt_         = book1D(dir, "assocJet_pt",         "assocJet_pt",         40,  0., 200.);
    histogram_charge_              = book1D(dir, "charge",              "charge",               3, -1.5,  +1.5);
    histogram_dxy_                 = book1D(dir, "dxy",                 "dxy",                 40, -0.05, +0.05);
    histogram_dz_                  = book1D(dir, "dz",                  "dz",                  40, -0.2,  +0.2);
    histogram_relIso_              = book1D(dir, "relIso",              "relIso",              40,  0.,    0.40);
    histogram_sip3d_               = book1D(dir, "sip3d",               "sip3d",               40,  0.,    8.);
    histogram_mvaRawTTH_           = book1D(dir, "mvaRawTTH",           "mvaRawTTH",           40, -1.,   +1.);
    histogram_jetPtRatio_          = book1D(dir, "jetPtRatio",          "jetPtRatio",          24,  0.,    1.2);
    histogram_jetBtagCSV_          = book1D(dir, "jetBtagCSV",          "jetBtagCSV",          40,  0.,    1.);
    histogram_tightCharge_         = book1D(dir, "tightCharge",         "tightCharge",          3, -0.5,  +2.5);
    histogram_passesLooseIdPOG_    = book1D(dir, "passesLooseIdPOG",    "passesLooseIdPOG",     2, -0.5,  +1.5);
    histogram_passesMediumIdPOG_   = book1D(dir, "passesMediumIdPOG",   "passesMediumIdPOG",    2, -0.5,  +1.5);
    histogram_gen_times_recCharge_ = book1D(dir, "gen_times_recCharge", "gen_times_recCharge",  3, -1.5,  +1.5);
  }
}

void
MuonHistManager::fillHistograms(const RecoMuon & muon,
                                double evtWeight)
{
  const double evtWeightErr = 0.;
  
  fillWithOverFlow(histogram_cone_pt_,       muon.cone_pt(),     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_eta_,           muon.eta(),         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_phi_,           muon.phi(),         evtWeight, evtWeightErr);
  
  int abs_genPdgId = 0;
  if      ( muon.genLepton() ) abs_genPdgId = std::abs(muon.genLepton()->pdgId()); // generator level match to electron or muon
  else if ( muon.genHadTau() ) abs_genPdgId = 15; // generator level match to hadronic tau decay
  else if ( muon.genJet()    ) abs_genPdgId = 21; // generator level match to jet; fill histogram with pdgId of gluon
  else                         abs_genPdgId =  0; // no match to any generator level particle (reconstructed muon most likely due to pileup)
  fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);

  if ( option_ == kOption_allHistograms ) {
    fillWithOverFlow(histogram_pt_,          muon.pt(),          evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_assocJet_pt_, muon.assocJet_pt(), evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_charge_,      muon.charge(),      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_dxy_,         muon.dxy(),         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_dz_,          muon.dz(),          evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_relIso_,      muon.relIso(),      evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_sip3d_,       muon.sip3d(),       evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mvaRawTTH_,   muon.mvaRawTTH(),   evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_jetPtRatio_,  muon.jetPtRatio(),  evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_jetBtagCSV_,  muon.jetBtagCSV(),  evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_tightCharge_, muon.tightCharge(), evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_passesLooseIdPOG_,  static_cast<int>(muon.passesLooseIdPOG()),  evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_passesMediumIdPOG_, static_cast<int>(muon.passesMediumIdPOG()), evtWeight, evtWeightErr);
    if ( abs_genPdgId == 13 ) {
      fillWithOverFlow(histogram_gen_times_recCharge_, muon.charge() * muon.genLepton()->charge(), evtWeight, evtWeightErr);
    }
  }
}

void
MuonHistManager::fillHistograms(const std::vector<const RecoMuon *> & muon_ptrs,
                                double evtWeight)
{
  const int numMuons = muon_ptrs.size();
  for(int idxMuon = 0; idxMuon < numMuons; ++idxMuon)
  {
    const RecoMuon * muon = muon_ptrs[idxMuon];

    if(idx_ >= 0 && idxMuon != idx_ )
    {
      continue;
    }

    fillHistograms(*muon, evtWeight);
  }
}


