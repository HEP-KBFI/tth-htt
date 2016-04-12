#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

MuonHistManager::MuonHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  idx_ = cfg.getParameter<int>("idx");
}

void MuonHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_pt_ = book1D(dir, "pt", "pt", 40, 0., 200.);
  histogram_eta_ = book1D(dir, "eta", "eta", 48, -2.4, +2.4);
  histogram_phi_ = book1D(dir, "phi", "phi", 36, -TMath::Pi(), +TMath::Pi());
  histogram_charge_ = book1D(dir, "charge", "charge", 3, -1.5, +1.5);

  histogram_dxy_ = book1D(dir, "dxy", "dxy", 40, -0.05, +0.05);
  histogram_dz_ = book1D(dir, "dz", "dz", 40, -0.2, +0.2);
  histogram_relIso_ = book1D(dir, "relIso", "relIso", 40, 0., 0.40);
  histogram_sip3d_ = book1D(dir, "sip3d", "sip3d", 40, 0., 8.);
  histogram_mvaRawTTH_ = book1D(dir, "mvaRawTTH", "mvaRawTTH", 40, -1., +1.);
  histogram_jetPtRatio_ = book1D(dir, "jetPtRatio", "jetPtRatio", 24, 0., 1.2);
  histogram_jetBtagCSV_ = book1D(dir, "jetBtagCSV", "jetBtagCSV", 40, 0., 1.);
  histogram_tightCharge_ = book1D(dir, "tightCharge", "tightCharge", 3, -0.5, +2.5);     
  histogram_passesLooseIdPOG_ = book1D(dir, "passesLooseIdPOG", "passesLooseIdPOG", 2, -0.5, +1.5);
  histogram_passesMediumIdPOG_ = book1D(dir, "passesMediumIdPOG", "passesMediumIdPOG", 2, -0.5, +1.5);

  histogram_abs_genPdgId_ = book1D(dir, "abs_genPdgId", "abs_genPdgId", 22, -0.5, +21.5);
  histogram_gen_times_recCharge_ = book1D(dir, "gen_times_recCharge", "gen_times_recCharge", 3, -1.5, +1.5);
}

void MuonHistManager::fillHistograms(const std::vector<const RecoMuon*>& muon_ptrs, double evtWeight)
{
  double evtWeightErr = 0.;
  
  size_t numMuons = muon_ptrs.size();
  for ( size_t idxMuon = 0; idxMuon < numMuons; ++idxMuon ) {
    const RecoMuon* muon = muon_ptrs[idxMuon];

    if ( idx_ >= 0 && (int)idxMuon != idx_ ) continue;

    fillWithOverFlow(histogram_pt_, muon->pt_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_eta_, muon->eta_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_phi_, muon->phi_, evtWeight, evtWeightErr);
    int charge = -muon->pdgId_/std::abs(muon->pdgId_);
    fillWithOverFlow(histogram_charge_, charge, evtWeight, evtWeightErr);
    
    fillWithOverFlow(histogram_dxy_, muon->dxy_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_dz_, muon->dz_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_relIso_, muon->relIso_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_sip3d_, muon->sip3d_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mvaRawTTH_, muon->mvaRawTTH_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_jetPtRatio_, muon->jetPtRatio_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_jetBtagCSV_, muon->jetBtagCSV_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_tightCharge_, muon->tightCharge_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_passesLooseIdPOG_, muon->passesLooseIdPOG_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_passesMediumIdPOG_, muon->passesMediumIdPOG_, evtWeight, evtWeightErr);
    
    int abs_genPdgId = 0;
    if      ( muon->genLepton_ ) abs_genPdgId = std::abs(muon->genLepton_->pdgId_); // generator level match to electron or muon
    else if ( muon->genHadTau_ ) abs_genPdgId = 15;                                 // generator level match to hadronic tau decay 
    else if ( muon->genJet_    ) abs_genPdgId = 21;                                 // generator level match to jet; fill histogram with pdgId of gluon
    else                         abs_genPdgId = 0;                                  // no match to any generator level particle (reconstructed muon most likely due to pileup)
    fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);
    if ( abs_genPdgId == 13 ) {
      int genCharge = muon->genLepton_->pdgId_/abs_genPdgId;
      fillWithOverFlow(histogram_gen_times_recCharge_, charge*genCharge, evtWeight, evtWeightErr);
    }
  }
}
