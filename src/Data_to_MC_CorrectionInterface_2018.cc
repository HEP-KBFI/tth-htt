#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

#include <cmath> // std::fabs(), std::sqrt()

Data_to_MC_CorrectionInterface_2018::Data_to_MC_CorrectionInterface_2018(const edm::ParameterSet & cfg)
  : Data_to_MC_CorrectionInterface_Base(cfg)
{
#if 0
  throw cmsException(this, __func__, __LINE__)
    << "Not available in 2018 era"
  ;
#endif
#pragma message "Setting data-to-MC corrections to 1 in 2018"
}

Data_to_MC_CorrectionInterface_2018::~Data_to_MC_CorrectionInterface_2018()
{}

double
Data_to_MC_CorrectionInterface_2018::getWeight_leptonTriggerEff() const
{
#if 0
  throw cmsException(this, __func__, __LINE__)
    << "Not available in 2018 era"
  ;
#endif
#pragma message "Setting data-to-MC corrections to 1 in 2018"
  return 1.;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_leptonTriggerEff() const
{
#if 0
  throw cmsException(this, __func__, __LINE__)
    << "Not available in 2018 era"
  ;
#endif
#pragma message "Setting data-to-MC corrections to 1 in 2018"
  return 1.;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_hadTauID_and_Iso() const
{
  double sf = 1.;
  double sfErr = 0.;
  const auto square = [](double value) -> double { return value * value; };
  for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
  {
    if(hadTau_genPdgId_[idxHadTau] == 15)
    {
      // CV: take data/MC (SF) measured for MVA-based tau ID with dR = 0.5 from
      //       https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV#Measurement_in_Z_tautau_events ("2018")
      //     as the SF for MVA-based tau ID with dR = 0.3 have not been measured yet.
      if     (hadTauSelection_ == 1) { sf *= 0.86; sfErr += square(0.04); } // dR03mvaVVLoose
      else if(hadTauSelection_ == 2) { sf *= 0.90; sfErr += square(0.03); } // dR03mvaVLoose
      else if(hadTauSelection_ == 3) { sf *= 0.90; sfErr += square(0.03); } // dR03mvaLoose
      else if(hadTauSelection_ == 4) { sf *= 0.90; sfErr += square(0.02); } // dR03mvaMedium
      else if(hadTauSelection_ == 5) { sf *= 0.90; sfErr += square(0.02); } // dR03mvaTight
      else if(hadTauSelection_ == 6) { sf *= 0.89; sfErr += square(0.02); } // dR03mvaVTight
      else if(hadTauSelection_ == 7) { sf *= 0.89; sfErr += square(0.02); } // dR03mvaVVTight
    }
  }
  sfErr = std::sqrt(sfErr);
  return sf;
}

double
Data_to_MC_CorrectionInterface_2018::getSF_eToTauFakeRate() const
{
  // taken from slide 5 of presentation during CMS week in April 2019:
  //   https://indico.cern.ch/event/803335/contributions/3359969/attachments/1829820/2996253/TauPOG_HTT_workshop_20190415_v0.pdf
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
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.40; sfErr = 0.15; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.21; sfErr = 0.23; }
            break;
          }
          case 4: // Tight
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.78; sfErr = 0.19; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.55; sfErr = 0.52; }
            break;
          }
          case 5: // vTight
          {
            if     (hadTau_absEta < 1.479) { sf_tmp = 1.95; sfErr = 0.27; }
            else if(hadTau_absEta > 1.558) { sf_tmp = 1.68; sfErr = 0.73; }
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
Data_to_MC_CorrectionInterface_2018::getSF_muToTauFakeRate() const
{
  // taken from slide 6 of presentation during CMS week in April 2019:
  //   https://indico.cern.ch/event/803335/contributions/3359969/attachments/1829820/2996253/TauPOG_HTT_workshop_20190415_v0.pdf
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
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.06; sfErr = 0.02; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 0.96; sfErr = 0.02; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.05; sfErr = 0.02; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 1.23; sfErr = 0.05; }
            else                         { sf_tmp = 1.19; sfErr = 0.09; }
            break;
          }
          case 2: // Tight
          {
            if     (hadTau_absEta < 0.4) { sf_tmp = 1.28; sfErr = 0.06; }
            else if(hadTau_absEta < 0.8) { sf_tmp = 1.20; sfErr = 0.10; }
            else if(hadTau_absEta < 1.2) { sf_tmp = 1.08; sfErr = 0.02; }
            else if(hadTau_absEta < 1.7) { sf_tmp = 1.00; sfErr = 0.20; }
            else                         { sf_tmp = 2.30; sfErr = 0.40; }
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
