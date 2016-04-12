#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

HadTauHistManager::HadTauHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  idx_ = cfg.getParameter<int>("idx");
}

void HadTauHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_pt_ = book1D(dir, "pt", "pt", 40, 0., 200.);
  histogram_eta_ = book1D(dir, "eta", "eta", 46, -2.3, +2.3);
  histogram_phi_ = book1D(dir, "phi", "phi", 36, -TMath::Pi(), +TMath::Pi());
  histogram_mass_ = book1D(dir, "mass", "mass", 40, 0., 2.);
  histogram_charge_ = book1D(dir, "charge", "charge", 3, -1.5, +1.5);

  histogram_dz_ = book1D(dir, "dz", "dz", 40, -0.2, +0.2);
  histogram_decayModeFinding_ = book1D(dir, "decayModeFinding", "decayModeFinding", 2, -0.5, +1.5);
  histogram_id_mva_dR03_ = book1D(dir, "id_mva_dR03", "id_mva_dR03", 7, -0.5, +6.5);  
  histogram_id_mva_dR05_ = book1D(dir, "id_mva_dR05", "id_mva_dR05", 7, -0.5, +6.5); 
  histogram_id_cut_dR03_ = book1D(dir, "id_cut_dR03", "id_cut_dR03", 4, -0.5, +3.5);  
  histogram_id_cut_dR05_ = book1D(dir, "id_cut_dR05", "id_cut_dR05", 4, -0.5, +3.5);  
  histogram_antiElectron_ = book1D(dir, "antiElectron", "antiElectron", 6, -0.5, +5.5); 
  histogram_antiMuon_ = book1D(dir, "antiMuon", "antiMuon", 3, -0.5, +2.5); 
  
  histogram_abs_genPdgId_ = book1D(dir, "abs_genPdgId", "abs_genPdgId", 22, -0.5, +21.5);
}

void HadTauHistManager::fillHistograms(const std::vector<const RecoHadTau*>& hadTau_ptrs, double evtWeight)
{
  double evtWeightErr = 0.;
  
  size_t numHadTaus = hadTau_ptrs.size();
  for ( size_t idxHadTau = 0; idxHadTau < numHadTaus; ++idxHadTau ) {
    const RecoHadTau* hadTau = hadTau_ptrs[idxHadTau];

    if ( idx_ >= 0 && (int)idxHadTau != idx_ ) continue;

    fillWithOverFlow(histogram_pt_, hadTau->pt_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_eta_, hadTau->eta_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_phi_, hadTau->phi_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mass_, hadTau->mass_, evtWeight, evtWeightErr);
    int charge = -hadTau->pdgId_/std::abs(hadTau->pdgId_);
    fillWithOverFlow(histogram_charge_, charge, evtWeight, evtWeightErr);

    fillWithOverFlow(histogram_dz_, hadTau->dz_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_decayModeFinding_, hadTau->decayModeFinding_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_id_mva_dR03_, hadTau->id_mva_dR03_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_id_mva_dR05_, hadTau->id_mva_dR05_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_id_cut_dR03_, hadTau->id_cut_dR03_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_id_cut_dR05_, hadTau->id_cut_dR05_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_antiElectron_, hadTau->antiElectron_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_antiMuon_, hadTau->antiMuon_, evtWeight, evtWeightErr);
  
    int abs_genPdgId = 0;
    if      ( hadTau->genHadTau_ ) abs_genPdgId = 15;                                   // generator level match to hadronic tau decay 
    else if ( hadTau->genLepton_ ) abs_genPdgId = std::abs(hadTau->genLepton_->pdgId_); // generator level match to electron or muon
    else if ( hadTau->genJet_    ) abs_genPdgId = 21;                                   // generator level match to jet; fill histogram with pdgId of gluon
    else                          abs_genPdgId = 0;                                     // no match to any generator level particle (reconstructed tauh most likely due to pileup)
    fillWithOverFlow(histogram_abs_genPdgId_, abs_genPdgId, evtWeight, evtWeightErr);
  }
}
