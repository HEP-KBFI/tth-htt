#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

GenEvtHistManager::GenEvtHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , minGenElectronPt_(9.)
  , maxGenElectronAbsEta_(2.7)
  , minGenMuonPt_(9.)
  , maxGenMuonAbsEta_(2.7)
  , minGenHadTauPt_(18.)
  , maxGenHadTauAbsEta_(2.7)
  , minGenJetPt_(20.)
  , maxGenJetAbsEta_(2.7)
{}

void
GenEvtHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_numGenElectrons_withinAcc_                = book1D(dir, "numGenElectrons_withinAcc",                "numGenElectrons_withinAcc",                 7, -0.5,  +6.5);
  histogram_numGenMuons_withinAcc_                    = book1D(dir, "numGenMuons_withinAcc",                    "numGenMuons_withinAcc",                     7, -0.5,  +6.5);
  histogram_numGenLeptons_withinAcc_                  = book1D(dir, "numGenLeptons_withinAcc",                  "numGenLeptons_withinAcc",                   7, -0.5,  +6.5);
  histogram_numGenHadTaus_withinAcc_                  = book1D(dir, "numGenHadTaus_withinAcc",                  "numGenHadTaus_withinAcc",                   7, -0.5,  +6.5);
  histogram_numGenLeptonsAndHadTaus_withinAcc_        = book1D(dir, "numGenLeptonsAndHadTaus_withinAcc",        "numGenLeptonsAndHadTaus_withinAcc",         7, -0.5,  +6.5);
  histogram_numGenJets_withinAcc_                     = book1D(dir, "numGenJets_withinAcc",                     "numGenJets_withinAcc",                     20, -0.5, +19.5);
  histogram_numGenLeptonsAndHadTausAndJets_withinAcc_ = book1D(dir, "numGenLeptonsAndHadTausAndJets_withinAcc", "numGenLeptonsAndHadTausAndJets_withinAcc", 20, -0.5, +19.5);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

namespace
{
  template <typename T,
            typename = typename std::enable_if<std::is_base_of<GenParticle, T>::value>>
  int constexpr
  countGenParticles_withinAcc(const std::vector<T> & genParticles,
                              double minPt,
                              double maxAbsEta)
  {
    return std::count_if(
      genParticles.cbegin(), genParticles.cend(),
      [minPt, maxAbsEta](const T & genParticle) -> bool
      {
        return genParticle.pt() > minPt && genParticle.absEta() < maxAbsEta;
      }
    );
  }
}

void
GenEvtHistManager::fillHistograms(const std::vector<GenLepton> & genElectrons,
                                  const std::vector<GenLepton> & genMuons,
                                  const std::vector<GenHadTau> & genHadTaus,
                                  const std::vector<GenJet> & genJets,
                                  double evtWeight)
{
  const int numGenElectrons_withinAcc = countGenParticles_withinAcc(genElectrons, minGenElectronPt_, maxGenElectronAbsEta_);
  const int numGenMuons_withinAcc     = countGenParticles_withinAcc(genMuons,     minGenMuonPt_,     maxGenMuonAbsEta_);
  const int numGenHadTaus_withinAcc   = countGenParticles_withinAcc(genHadTaus,   minGenHadTauPt_, maxGenHadTauAbsEta_);
  const int numGenJets_withinAcc      = countGenParticles_withinAcc(genJets,      minGenJetPt_,    maxGenJetAbsEta_);

  const int numGenLeptons_withinAcc                  = numGenElectrons_withinAcc + numGenMuons_withinAcc;
  const int numGenLeptonsAndHadTaus_withinAcc        = numGenLeptons_withinAcc + numGenHadTaus_withinAcc;
  const int numGenLeptonsAndHadTausAndJets_withinAcc = numGenLeptons_withinAcc + numGenHadTaus_withinAcc + numGenJets_withinAcc;

  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numGenElectrons_withinAcc_,                numGenElectrons_withinAcc,                evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenMuons_withinAcc_,                    numGenMuons_withinAcc,                    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptons_withinAcc_,                  numGenLeptons_withinAcc,                  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenHadTaus_withinAcc_,                  numGenHadTaus_withinAcc,                  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptonsAndHadTaus_withinAcc_,        numGenLeptonsAndHadTaus_withinAcc,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenJets_withinAcc_,                     numGenJets_withinAcc,                     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptonsAndHadTausAndJets_withinAcc_, numGenLeptonsAndHadTausAndJets_withinAcc, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
