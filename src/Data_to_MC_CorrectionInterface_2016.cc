#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::

#include <TString.h> // Form()

#include <cmath> // std::sqrt()

Data_to_MC_CorrectionInterface_2016::Data_to_MC_CorrectionInterface_2016(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "GsfElectronToMVAVLooseFOIDEmuTightIP2D",
     lut::kXptYabsEta));
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "MVAVLooseElectronToMini4",
     lut::kXptYabsEta));
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/el_scaleFactors_Moriond17.root", "MVAVLooseElectronToConvVetoIHit1",
     lut::kXptYabsEta));
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/egammaEffi.txt_EGM2D.root", "EGamma_SF2D",
     lut::kXetaYpt));
  sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_3l.root", "sf",
    lut::kXptYabsEta));
  sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_e_2lss.root", "sf",
    lut::kXptYabsEta));

  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_LooseID_DENOM_generalTracks_VAR_map_pt_eta.root", "SF",
    lut::kXptYabsEta));
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_MiniIsoLoose_DENOM_LooseID_VAR_map_pt_eta.root", "SF",
    lut::kXptYabsEta));
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/TnP_NUM_TightIP2D_DENOM_MediumID_VAR_map_pt_eta.root", "SF",
    lut::kXptYabsEta));
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/ratios_HIP_trkEff.root", "ratio_eta",
    lut::kXeta));
  sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_3l.root", "sf",
    lut::kXptYabsEta));
  sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/leptonSF/2016/lepMVAEffSF_m_2lss.root", "sf",
    lut::kXptYabsEta));

  effTrigger_ee_ = new lutWrapperTH2Poly(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSee2DPt__effic",
    lut::kXptYpt); // X=pt1, Y=pt2
  effTrigger_em_ = new lutWrapperTH2Poly(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSeu2DPt_effic",
    lut::kXptYpt); // X=pt1, Y=pt2
  effTrigger_mm_ = new lutWrapperTH2Poly(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "SSuu2DPt_effic",
    lut::kXptYpt); // X=pt1, Y=pt2
  effTrigger_3l_ = new lutWrapperTH2Poly(
    inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016RunBCD/trig_eff_map_v4.root", "__3l2DPt_effic",
    lut::kXptYpt); // X=pt1, Y=pt2

  const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
  assert(etaBinEdges_1e.size() > 0);
  const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;
  for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
  {
    const double etaMin = etaBinEdges_1e[idxEtaBin];
    const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
    const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
    effTrigger_1e_data_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
      Form("ZMassEta%s_Data", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
    effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
      Form("ZMassEta%s_MC", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
  }

  const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
  assert(etaBinEdges_1m.size() > 0);
  const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;
  for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
  {
    const double etaMin = etaBinEdges_1m[idxEtaBin];
    const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
    const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
    effTrigger_1m_data_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
      Form("ZMassEta%s_Data", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
    effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
      inputFiles_,
      "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
      Form("ZMassEta%s_MC", etaBinLabel.data()),
      lut::kXptYabsEta,
      -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
    ));
  }
}

Data_to_MC_CorrectionInterface_2016::~Data_to_MC_CorrectionInterface_2016()
{}

double
Data_to_MC_CorrectionInterface_2016::getWeight_leptonTriggerEff() const
{
  double weight = 1.;
  if(numLeptons_ >= 2)
  {
    std::vector<double> lepton_pt_sorted;
    for(std::size_t idxLepton = 0; idxLepton < numLeptons_; ++idxLepton)
    {
      lepton_pt_sorted.push_back(lepton_pt_[idxLepton]);
    }
    std::sort(lepton_pt_sorted.begin(), lepton_pt_sorted.end(), std::greater<int>());
    const double pt1 = lepton_pt_sorted[0];
    const double pt2 = lepton_pt_sorted[1];
    if     (numElectrons_ == 2 && numMuons_ == 0) weight = effTrigger_ee_->getSF(pt1, pt2);
    else if(numElectrons_ == 1 && numMuons_ == 1) weight = effTrigger_em_->getSF(pt1, pt2);
    else if(numElectrons_ == 0 && numMuons_ == 2) weight = effTrigger_mm_->getSF(pt1, pt2);
    else if(numLeptons_   >= 3                  ) weight = effTrigger_3l_->getSF(pt1, pt2);
    else assert(0);
  }
  else if(numElectrons_ == 1 && numMuons_ == 0)
  {
    weight = get_from_lut(effTrigger_1e_mc_, electron_pt_[0], electron_eta_[0]);
  }
  else if(numElectrons_ == 0 && numMuons_ == 1)
  {
    weight = get_from_lut(effTrigger_1m_mc_, muon_pt_[0], muon_eta_[0]);
  }
  return weight;
}

double
Data_to_MC_CorrectionInterface_2016::getSF_leptonTriggerEff() const
{
  double sf = 1.;

  if(numElectrons_ == 1 && numMuons_ == 0)
  {
    const double eff_data = get_from_lut(effTrigger_1e_data_, lepton_pt_[0], lepton_eta_[0]);
    const double eff_mc   = get_from_lut(effTrigger_1e_mc_,   lepton_pt_[0], lepton_eta_[0]);
    sf = aux::compSF(eff_data, eff_mc);
  }
  else if(numElectrons_ == 0 && numMuons_ == 1)
  {
    const double eff_data = get_from_lut(effTrigger_1m_data_, lepton_pt_[0], lepton_eta_[0]);
    const double eff_mc   = get_from_lut(effTrigger_1m_mc_,   lepton_pt_[0], lepton_eta_[0]);
    sf = aux::compSF(eff_data, eff_mc);
  }
  else if(numElectrons_ == 2 && numMuons_ == 0)
  {
    sf = 1.01;
  }
  else if(numElectrons_ == 1 && numMuons_ == 1)
  {
    sf = 1.01;
  }
  else if(numElectrons_ == 0 && numMuons_ == 2)
  {
    sf = 1.;
  }
  else
  {
    sf = 1.;
  }

  return sf;
}

double
Data_to_MC_CorrectionInterface_2016::getSF_hadTauID_and_Iso() const
{
  double sf = 1.;
  for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 15)
    {
      // CV: take data/MC correction to be equal to 0.95 for all WPs, following Tau POG recommendation for 2016 data,
      //     cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV
      sf *= 0.95;
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_2016::getSF_eToTauFakeRate() const
{
  // CV: e->tau misidentification rate has not yet been measured in 2016 data,
  //     use data/MC corrections measured in 2015 data for both data-taking periods
  double sf = 1.;
  for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 11)
    {
      double sf_tmp = 1.;
      double sfErr = 0.;

      const double hadTau_absEta = std::fabs(hadTau_eta_[idxHadTau]);
      if(hadTauSelection_antiElectron_[idxHadTau] > 0)
      {
        switch(hadTauSelection_antiElectron_[idxHadTau])
        {
          case 1: // vLoose
          {
            if(hadTau_absEta < 1.479) { sf_tmp = 1.02; sfErr = 0.05; }
            else                      { sf_tmp = 1.11; sfErr = 0.05; }
            break;
          }
          case 2: // Loose
          {
            if(hadTau_absEta < 1.479) { sf_tmp = 1.14; sfErr = 0.04; }
            else                      { sf_tmp = 1.09; sfErr = 0.05; }
            break;
          }
          case 3: // Medium
          {
            if(hadTau_absEta < 1.479) { sf_tmp = 1.50; sfErr = 0.13; }
            else                      { sf_tmp = 1.06; sfErr = 0.18; }
            break;
          }
          case 4: // Tight
          {
            if(hadTau_absEta < 1.479) { sf_tmp = 1.80; sfErr = 0.23; }
            else                      { sf_tmp = 1.30; sfErr = 0.42; }
            break;
          }
          case 5: // vTight
          {
            if(hadTau_absEta < 1.479) { sf_tmp = 1.89; sfErr = 0.35; }
            else                      { sf_tmp = 1.69; sfErr = 0.68; }
            break;
          }
          default: throw cmsException(this, __func__, __LINE__)
                     << "Invalid parameter 'hadTauSelection_antiElectron' = "
                     << hadTauSelection_antiElectron_[idxHadTau]
                   ;
        }
      }

      switch(eToTauFakeRate_option_)
      {
        case FRet::shiftUp:   sf_tmp += sfErr; break;
        case FRet::shiftDown: sf_tmp -= sfErr; break;
        case FRet::central:                    break;
        default:              throw cmsException(this, __func__, __LINE__)
                                << "Invalid parameter 'central_or_shift' = "
                                << as_integer(eToTauFakeRate_option_)
                              ;
      }

      sf_tmp = std::max(sf_tmp, 0.); // CV: require e->tau fake-rates to be positive
      sf *= sf_tmp;
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_2016::getSF_muToTauFakeRate() const
{
  double sf = 1.;
  for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 13)
    {
      double sf_tmp = 1.;
      double sfErr = 0.;

      const double hadTau_absEta = std::fabs(hadTau_eta_[idxHadTau]);
      if(hadTauSelection_antiMuon_[idxHadTau] > 0)
      {
        switch(hadTauSelection_antiMuon_[idxHadTau])
        {
          case 1: // Loose
          {
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.15; sfErr = 0.05; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 1.15; sfErr = 0.05; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.18; sfErr = 0.05; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 1.20; sfErr = 0.20; }
            else if(hadTau_absEta < 2.3) { sf_tmp = 1.30; sfErr = 0.30; }
            break;
          }
          case 2: // Tight
          {
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.50; sfErr = 0.10; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 1.40; sfErr = 0.10; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.21; sfErr = 0.06; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 2.60; sfErr = 0.90; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 2.10; sfErr = 0.90; }
            break;
          }
          default: throw cmsException(__func__, __LINE__)
                     << "Invalid parameter 'hadTauSelection_antiMuon' = "
                     << hadTauSelection_antiMuon_[idxHadTau]
                   ;
        }
      }

      switch(muToTauFakeRate_option_)
      {
        case FRmt::shiftUp:   sf_tmp += sfErr; break;
        case FRmt::shiftDown: sf_tmp -= sfErr; break;
        case FRmt::central:                    break;
        default:              throw cmsException(this, __func__, __LINE__)
                                << "Invalid parameter 'central_or_shift' = "
                                << as_integer(muToTauFakeRate_option_)
                              ;
      }

      sf_tmp = std::max(sf_tmp, 0.); // CV: require mu->tau fake-rates to be positive
      sf *= sf_tmp;
    }
  }
  return sf;
}
