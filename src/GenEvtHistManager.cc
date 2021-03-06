#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TH2.h> // TH2

GenEvtHistManager::GenEvtHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , minGenElectronPt_(9.)
  , maxGenElectronAbsEta_(2.7)
  , minGenMuonPt_(9.)
  , maxGenMuonAbsEta_(2.7)
  , minGenHadTauPt_(18.)
  , maxGenHadTauAbsEta_(2.7)
  , minGenPhotonPt_(1.) // taken from [*]
  , maxGenPhotonAbsEta_(2.7)
  , minGenJetPt_(20.)
  , maxGenJetAbsEta_(2.7)
  , bookRecoHistograms_(false)
  , histogram_evtWeightManager_1D_(nullptr)
  , histogram_evtWeightManager_1D_counter_(nullptr)
  , histogram_evtWeightManager_2D_(nullptr)
  , histogram_evtWeightManager_2D_counter_(nullptr)
  , central_or_shift_(cfg.getParameter<std::string>("central_or_shift"))
{
  const std::vector<std::string> sysOpts_central = {
    "numGenElectrons_withinAcc",
    "numGenMuons_withinAcc",
    "numGenLeptons_withinAcc",
    "numGenPhotons_withinAcc",
    "numGenElectronsAndPhotons_withinAcc",
    "numGenHadTaus_withinAcc",
    "numGenLeptonsAndHadTaus_withinAcc",
    "numGenJets_withinAcc",
    "numGenLeptonsAndHadTausAndJets_withinAcc",
    "lumiScale",
  };
  const std::vector<std::string> sysOpts_all = {
    "EventCounter",
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
  for(const std::string & sysOpt: sysOpts_all)
  {
    central_or_shiftOptions_[sysOpt] = { "*" };
  }
}

// [*] https://github.com/CERN-PH-CMG/cmg-cmssw/blob/534b379810bf806c75837c4e3a8e2193275fe79e/PhysicsTools/Heppy/python/analyzers/objects/LeptonAnalyzer.py#L708

void
GenEvtHistManager::bookHistograms(TFileDirectory & dir)
{
  histogram_numGenElectrons_withinAcc_                = book1D(dir, "numGenElectrons_withinAcc",                "numGenElectrons_withinAcc",                 7, -0.5,  +6.5);
  histogram_numGenMuons_withinAcc_                    = book1D(dir, "numGenMuons_withinAcc",                    "numGenMuons_withinAcc",                     7, -0.5,  +6.5);
  histogram_numGenLeptons_withinAcc_                  = book1D(dir, "numGenLeptons_withinAcc",                  "numGenLeptons_withinAcc",                   7, -0.5,  +6.5);
  histogram_numGenPhotons_withinAcc_                  = book1D(dir, "numGenPhotons_withinAcc",                  "numGenPhotons_withinAcc",                   7, -0.5,  +6.5);
  histogram_numGenElectronsAndPhotons_withinAcc_      = book1D(dir, "numGenElectronsAndPhotons_withinAcc",      "numGenElectronsAndPhotons_withinAcc",       7, -0.5,  +6.5);
  histogram_numGenHadTaus_withinAcc_                  = book1D(dir, "numGenHadTaus_withinAcc",                  "numGenHadTaus_withinAcc",                   7, -0.5,  +6.5);
  histogram_numGenLeptonsAndHadTaus_withinAcc_        = book1D(dir, "numGenLeptonsAndHadTaus_withinAcc",        "numGenLeptonsAndHadTaus_withinAcc",         7, -0.5,  +6.5);
  histogram_numGenJets_withinAcc_                     = book1D(dir, "numGenJets_withinAcc",                     "numGenJets_withinAcc",                     20, -0.5, +19.5);
  histogram_numGenLeptonsAndHadTausAndJets_withinAcc_ = book1D(dir, "numGenLeptonsAndHadTausAndJets_withinAcc", "numGenLeptonsAndHadTausAndJets_withinAcc", 20, -0.5, +19.5);

  histogram_lumiScale_    = book1D(dir, "lumiScale",    "lumiScale",    1, -0.5, +0.5);
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
                                  const std::vector<GenPhoton> & genPhotons,
                                  const std::vector<GenJet> & genJets,
                                  double lumiScale,
                                  double evtWeight)
{
  const int numGenElectrons_withinAcc = countGenParticles_withinAcc(genElectrons, minGenElectronPt_, maxGenElectronAbsEta_);
  const int numGenMuons_withinAcc     = countGenParticles_withinAcc(genMuons,     minGenMuonPt_,     maxGenMuonAbsEta_);
  const int numGenHadTaus_withinAcc   = countGenParticles_withinAcc(genHadTaus,   minGenHadTauPt_,   maxGenHadTauAbsEta_);
  const int numGenPhotons_withinAcc   = countGenParticles_withinAcc(genPhotons,   minGenPhotonPt_,   maxGenPhotonAbsEta_);
  const int numGenJets_withinAcc      = countGenParticles_withinAcc(genJets,      minGenJetPt_,      maxGenJetAbsEta_);

  const int numGenLeptons_withinAcc                  = numGenElectrons_withinAcc + numGenMuons_withinAcc;
  const int numGenElectronsAndPhotons_withinAcc      = numGenElectrons_withinAcc + numGenPhotons_withinAcc;
  const int numGenLeptonsAndHadTaus_withinAcc        = numGenLeptons_withinAcc + numGenHadTaus_withinAcc;
  const int numGenLeptonsAndHadTausAndJets_withinAcc = numGenLeptons_withinAcc + numGenHadTaus_withinAcc + numGenJets_withinAcc;

  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numGenElectrons_withinAcc_,                numGenElectrons_withinAcc,                evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenMuons_withinAcc_,                    numGenMuons_withinAcc,                    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptons_withinAcc_,                  numGenLeptons_withinAcc,                  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenPhotons_withinAcc_,                  numGenPhotons_withinAcc,                  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenElectronsAndPhotons_withinAcc_,      numGenElectronsAndPhotons_withinAcc,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenHadTaus_withinAcc_,                  numGenHadTaus_withinAcc,                  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptonsAndHadTaus_withinAcc_,        numGenLeptonsAndHadTaus_withinAcc,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenJets_withinAcc_,                     numGenJets_withinAcc,                     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numGenLeptonsAndHadTausAndJets_withinAcc_, numGenLeptonsAndHadTausAndJets_withinAcc, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_lumiScale_,    0., lumiScale, lumiScale);
  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}

void
GenEvtHistManager::bookHistograms(TFileDirectory & dir,
                                  const EvtWeightManager * const eventWeightManager,
                                  bool bookRecoHistograms)
{
  assert(eventWeightManager);
  const int histogramDimension = eventWeightManager->getDimension();
  bookRecoHistograms_ = bookRecoHistograms;

  TDirectory * const subdir = createHistogramSubdirectory(dir);
  subdir->cd();

  switch(histogramDimension)
  {
    case 1:
    {
      histogram_evtWeightManager_1D_ = static_cast<TH1 *>(
        (
          eventWeightManager->has_central_or_shift(central_or_shift_) ?
          eventWeightManager->getHistogram_1D(central_or_shift_) :
          eventWeightManager->getHistogram_1D()
        )->Clone()
      );
      histogram_evtWeightManager_1D_->Reset();
      histogram_evtWeightManager_1D_->SetName(Form(
        "%s%s",
        central_or_shift_.empty() || central_or_shift_ == "central" ? "" : Form("%s_", central_or_shift_.data()),
        histogram_evtWeightManager_1D_->GetName()
      ));
      histogram_evtWeightManager_1D_->SetTitle(Form(
        "%s%s",
        central_or_shift_.empty() || central_or_shift_ == "central" ? "" : Form("%s_", central_or_shift_.data()),
        histogram_evtWeightManager_1D_->GetTitle()
      ));
      histogram_evtWeightManager_1D_counter_ = static_cast<TH1 *>(histogram_evtWeightManager_1D_->Clone());
      histogram_evtWeightManager_1D_counter_->SetName(Form("%s_counter",  histogram_evtWeightManager_1D_->GetName()));
      histogram_evtWeightManager_1D_counter_->SetTitle(Form("%s_counter", histogram_evtWeightManager_1D_->GetTitle()));
      book1D(subdir, histogram_evtWeightManager_1D_);
      book1D(subdir, histogram_evtWeightManager_1D_counter_);

      if(bookRecoHistograms_)
      {
        const int nbins = histogram_evtWeightManager_1D_->GetXaxis()->GetNbins();
        for(int bin_idx = 0; bin_idx <= nbins + 1; ++bin_idx)
        {
          const std::string bin_name = Form("%s%d_%s",
            eventWeightManager->get_x_var().data(), bin_idx,
            histogram_evtWeightManager_1D_->GetTitle()
          );
          const std::string numJets_title = Form("%s_%s", bin_name.data(), "numJets");
          const std::string ht_title      = Form("%s_%s", bin_name.data(), "HT");
          histogram_evtWeightManager_numJets_[bin_name] = book1D(dir, numJets_title, numJets_title,  20, -0.5, +19.5);
          histogram_evtWeightManager_HT_     [bin_name] = book1D(dir, ht_title,      ht_title,      150,  0., 1500.);
          book1D(subdir, histogram_evtWeightManager_numJets_[bin_name]);
          book1D(subdir, histogram_evtWeightManager_HT_[bin_name]);
        }
      }

      break;
    }
    case 2:
    {
      histogram_evtWeightManager_2D_ = static_cast<TH2 *>(
        (
          eventWeightManager->has_central_or_shift(central_or_shift_) ?
          eventWeightManager->getHistogram_2D(central_or_shift_) :
          eventWeightManager->getHistogram_2D()
        )->Clone()
      );
      histogram_evtWeightManager_2D_->Reset();
      histogram_evtWeightManager_2D_->SetName(Form(
        "%s%s",
        central_or_shift_.empty() || central_or_shift_ == "central" ? "" : Form("%s_", central_or_shift_.data()),
        histogram_evtWeightManager_2D_->GetName()
      ));
      histogram_evtWeightManager_2D_->SetTitle(Form(
        "%s%s",
        central_or_shift_.empty() || central_or_shift_ == "central" ? "" : Form("%s_", central_or_shift_.data()),
        histogram_evtWeightManager_2D_->GetTitle()
      ));
      histogram_evtWeightManager_2D_->SetOption("col text");
      histogram_evtWeightManager_2D_counter_ = static_cast<TH2 *>(histogram_evtWeightManager_2D_->Clone());
      histogram_evtWeightManager_2D_counter_->SetName(Form("%s_counter",  histogram_evtWeightManager_2D_->GetName()));
      histogram_evtWeightManager_2D_counter_->SetTitle(Form("%s_counter", histogram_evtWeightManager_2D_->GetTitle()));
      histogram_evtWeightManager_2D_counter_->SetOption("col text");
      book2D(subdir, histogram_evtWeightManager_2D_);
      book2D(subdir, histogram_evtWeightManager_2D_counter_);

      if(bookRecoHistograms_)
      {
        const int nbins_x = histogram_evtWeightManager_2D_->GetXaxis()->GetNbins();
        const int nbins_y = histogram_evtWeightManager_2D_->GetYaxis()->GetNbins();
        for(int bin_idx_x = 0; bin_idx_x <= nbins_x + 1; ++bin_idx_x)
        {
          for(int bin_idx_y = 0; bin_idx_y <= nbins_y + 1; ++bin_idx_y)
          {
            const std::string bin_name = Form("%s%d_%s%d_%s",
              eventWeightManager->get_x_var().data(), bin_idx_x,
              eventWeightManager->get_y_var().data(), bin_idx_y,
              histogram_evtWeightManager_2D_->GetTitle()
            );
            const std::string numJets_title = Form("%s_%s", bin_name.data(), "numJets");
            const std::string ht_title      = Form("%s_%s", bin_name.data(), "HT");
            histogram_evtWeightManager_numJets_[bin_name] = book1D(dir, numJets_title, numJets_title,  20, -0.5, +19.5);
            histogram_evtWeightManager_HT_     [bin_name] = book1D(dir, ht_title,      ht_title,      150,  0., 1500.);
            book1D(subdir, histogram_evtWeightManager_numJets_[bin_name]);
            book1D(subdir, histogram_evtWeightManager_HT_[bin_name]);
          }
        }
      }

      break;
    }
    default: throw cmsException(this, __func__, __LINE__) << "Invalid dimension = " << histogramDimension;
  }
}

void
GenEvtHistManager::fillHistograms(const EvtWeightManager * const eventWeightManager,
                                  double evtWeight,
                                  int numJets,
                                  double ht)
{
  assert(eventWeightManager);
  if(histogram_evtWeightManager_1D_)
  {
    const int bin_x = eventWeightManager->has_central_or_shift(central_or_shift_) ?
      eventWeightManager->getBinIdx_1D(central_or_shift_) :
      eventWeightManager->getBinIdx_1D()
    ;
    const double binCenter_x = histogram_evtWeightManager_1D_->GetXaxis()->GetBinCenter(bin_x);
    histogram_evtWeightManager_1D_->Fill(binCenter_x, evtWeight);
    histogram_evtWeightManager_1D_counter_->Fill(binCenter_x, 1.);

    if(bookRecoHistograms_)
    {
      const std::string bin_name = Form("%s%d_%s",
        eventWeightManager->get_x_var().data(), bin_x,
        histogram_evtWeightManager_1D_->GetTitle()
      );
      if(! histogram_evtWeightManager_numJets_.count(bin_name) ||
         ! histogram_evtWeightManager_HT_.count(bin_name))
      {
        throw cmsException(this, __func__, __LINE__) << "Histogram with the name '" << bin_name << "' has not been booked";
      }
      fillWithOverFlow(histogram_evtWeightManager_numJets_[bin_name], numJets, evtWeight);
      fillWithOverFlow(histogram_evtWeightManager_HT_     [bin_name], ht,      evtWeight);
    }

  }
  else if(histogram_evtWeightManager_2D_)
  {
    const std::pair<int, int> bin_xy = eventWeightManager->has_central_or_shift(central_or_shift_) ?
      eventWeightManager->getBinIdx_2D(central_or_shift_) :
      eventWeightManager->getBinIdx_2D()
    ;
    const double binCenter_x = histogram_evtWeightManager_2D_->GetXaxis()->GetBinCenter(bin_xy.first);
    const double binCenter_y = histogram_evtWeightManager_2D_->GetYaxis()->GetBinCenter(bin_xy.second);
    histogram_evtWeightManager_2D_->Fill(binCenter_x, binCenter_y, evtWeight);
    histogram_evtWeightManager_2D_counter_->Fill(binCenter_x, binCenter_y, 1.);

    if(bookRecoHistograms_)
    {
      const std::string bin_name = Form("%s%d_%s%d_%s",
        eventWeightManager->get_x_var().data(), bin_xy.first,
        eventWeightManager->get_y_var().data(), bin_xy.second,
        histogram_evtWeightManager_2D_->GetTitle()
      );
      if(! histogram_evtWeightManager_numJets_.count(bin_name) ||
         ! histogram_evtWeightManager_HT_.count(bin_name))
      {
        throw cmsException(this, __func__, __LINE__) << "Histogram with the name '" << bin_name << "' has not been booked";
      }
      fillWithOverFlow(histogram_evtWeightManager_numJets_[bin_name], numJets, evtWeight);
      fillWithOverFlow(histogram_evtWeightManager_HT_     [bin_name], ht,      evtWeight);
    }

  }
  else
  {
    throw cmsException(this, __func__, __LINE__) << "Neither 1D or 2D histograms initialized";
  }
}
