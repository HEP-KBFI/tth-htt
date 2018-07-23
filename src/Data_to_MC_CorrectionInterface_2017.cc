#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperTH2
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

#include <cmath> // std::sqrt()

Data_to_MC_CorrectionInterface_2017::Data_to_MC_CorrectionInterface_2017(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptLt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, -1., 20., lut::kLimit_and_Cut
  ));
  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_gsf_ptGt20.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 20., -1., lut::kLimit_and_Cut
  ));

  sfElectronID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/el_scaleFactors_trkVtxCut_and_isoEff.root",
    "EGamma_SF2D",
    lut::kXetaYpt, -2.5, +2.5, lut::kLimit, 10., 500., lut::kLimit
  ));

  sfElectronID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_e_3l.root",
    "sf",
    lut::kXptYabsEta
  ));
  sfElectronID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_e_2lss.root",
    "sf",
    lut::kXptYabsEta
  ));

  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptLt10.root",
    "ratio_eff_eta3_tk0_dr030e030_corr",
    lut::kXetaYpt, -2.4, +2.4, lut::kLimit, -1., 10., lut::kCut
  ));
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTGraph(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkEff_ptGt10.root",
    "ratio_eff_eta3_dr030e030_corr",
    lut::kXetaYpt, -2.4, +2.4, lut::kLimit, 10., -1., lut::kCut
  ));

  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptLt30.root",
    "NUM_LooseID_DEN_genTracks_pt_abseta",
    lut::kXptYabsEta, -1., 30., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
  ));
  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_ptGt30.root",
    "NUM_LooseID_DEN_genTracks_pt_abseta",
    lut::kXptYabsEta, 30., -1., lut::kLimit_and_Cut, 0., 2.4, lut::kLimit
  ));

  sfMuonID_and_Iso_loose_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/mu_scaleFactors_trkVtxCut_and_isoEff.root",
    "NUM_ttHLoo_DEN_LooseID",
    lut::kXptYabsEta, 10., 120., lut::kLimit, 0., 2.4, lut::kLimit
  ));

  sfMuonID_and_Iso_tight_to_loose_woTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_m_3l.root",
    "sf",
    lut::kXptYabsEta
  ));
  sfMuonID_and_Iso_tight_to_loose_wTightCharge_.push_back(new lutWrapperTH2(
    inputFiles_,
    "tthAnalysis/HiggsToTauTau/data/leptonSF/2017/lepMVAEffSF_m_2lss.root",
    "sf",
    lut::kXptYabsEta
  ));
}

Data_to_MC_CorrectionInterface_2017::~Data_to_MC_CorrectionInterface_2017()
{}

double
Data_to_MC_CorrectionInterface_2017::getWeight_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Not available for 2017 era"
  ;
}

double
Data_to_MC_CorrectionInterface_2017::getSF_leptonTriggerEff() const
{
  double sf = 1.;
  double sfErr = 0.;

  const double lepton_pt_lead = std::max(lepton_pt_[0], lepton_pt_[1]);
  if(numElectrons_ == 2 && numMuons_ == 0)
  {
    if  (lepton_pt_lead >= 30.) { sf = 0.991; sfErr = 0.002; }
    else                        { sf = 0.937; sfErr = 0.027; }
  }
  else if(numElectrons_ == 1 && numMuons_ == 1)
  {
    if     (lepton_pt_lead >= 50.) { sf = 1.000; sfErr = 0.001; }
    else if(lepton_pt_lead >= 35.) { sf = 0.983; sfErr = 0.003; }
    else                           { sf = 0.952; sfErr = 0.008; }
  }
  else if(numElectrons_ == 0 && numMuons_ == 2)
  {
    if  (lepton_pt_lead >= 35.) { sf = 0.994; sfErr = 0.001; }
    else                        { sf = 0.972; sfErr = 0.006; }
  }
  else if((numElectrons_ + numMuons_) >= 3)
  {
    sf = 1.;
    sfErr = 0.050;
  }

  switch(triggerSF_option_)
  {
    case TriggerSFsys::central:   return sf;
    case TriggerSFsys::shiftUp:   return sf + sfErr;
    case TriggerSFsys::shiftDown: return sf - sfErr;
    default: throw cmsException(this, __func__, __LINE__)
                     << "Invalid option: " << static_cast<int>(triggerSF_option_)
                   ;
  }

  return sf;
}

double
Data_to_MC_CorrectionInterface_2017::getSF_hadTauID_and_Iso() const
{
  double sf = 1.;
  double sfErr = 0.;
  const auto square = [](double value) -> double { return value * value; };
  for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 15)
    {
      // CV: take data/MC (SF) measured for MVA-based tau ID with dR = 0.5 from
      //       https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV#Measurement_in_Z_tautau_events ("Measured SF 2017")
      //     as the SF for MVA-based tau ID with dR = 0.3 have not been measured yet.
      if     (hadTauSelection_ == 1) { sf *= 0.88; sfErr += square(0.03); } // take SF for dR03mvaVLoose, as SF for dR03mvaVVLoose has not been measured yet
      else if(hadTauSelection_ == 2) { sf *= 0.88; sfErr += square(0.03); } // dR03mvaVLoose
      else if(hadTauSelection_ == 3) { sf *= 0.89; sfErr += square(0.03); } // dR03mvaLoose
      else if(hadTauSelection_ == 4) { sf *= 0.89; sfErr += square(0.03); } // dR03mvaMedium
      else if(hadTauSelection_ == 5) { sf *= 0.89; sfErr += square(0.03); } // dR03mvaTight
      else if(hadTauSelection_ == 6) { sf *= 0.86; sfErr += square(0.03); } // dR03mvaVTight
      else if(hadTauSelection_ == 7) { sf *= 0.84; sfErr += square(0.03); } // dR03mvaVVTight
    }
  }
  sfErr = std::sqrt(sfErr);
  return sf;
}

double
Data_to_MC_CorrectionInterface_2017::getSF_eToTauFakeRate() const
{
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
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.09; sfErr = 0.01; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.19; sfErr = 0.01; }
            break;
          }
          case 2: // Loose
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.17; sfErr = 0.04; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.25; sfErr = 0.06; }
            break;
          }
          case 3: // Medium
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.40; sfErr = 0.12; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.21; sfErr = 0.26; }
            break;
          }
          case 4: // Tight
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.80; sfErr = 0.20; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.53; sfErr = 0.60; }
            break;
          }
          case 5: // vTight
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.96; sfErr = 0.27; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.66; sfErr = 0.80; }
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
Data_to_MC_CorrectionInterface_2017::getSF_muToTauFakeRate() const
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
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.06; sfErr = 0.05; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 1.02; sfErr = 0.04; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.10; sfErr = 0.04; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 1.03; sfErr = 0.18; }
            else                         { sf_tmp = 1.94; sfErr = 0.35; }
            break;
          }
          case 2: // Tight
          {
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.17; sfErr = 0.12; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 1.29; sfErr = 0.30; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.14; sfErr = 0.05; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 0.93; sfErr = 0.60; }
            else                         { sf_tmp = 1.61; sfErr = 0.60; }
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
