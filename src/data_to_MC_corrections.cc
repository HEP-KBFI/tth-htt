#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile(), loadTH1(), loadTH2(), getSF_from_TH1(), getSF_from_TH2()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

#include <TH1.h> // TH1
#include <TFile.h> // TFile

#include <cassert> // assert()

//-------------------------------------------------------------------------------
//CV: data/MC scale-factors for e->tau and mu->tau fake-rates taken from
//      https://indico.cern.ch/event/719250/contributions/2971854/attachments/1635435/2609013/tauid_recommendations2017.pdf 

double
sf_eToTauFakeRate_2017(double hadTau_pt, // unused
                       double hadTau_absEta,
                       int hadTauSelection_antiElectron,
                       FRet central_or_shift)
{
  double sf = 1.;
  double sfErr = 0.;

  if(hadTauSelection_antiElectron <= 0)
  {
    // no anti-electron discriminator applied
    return sf;
  }
  switch(hadTauSelection_antiElectron)
  {
    case 1: // vLoose
    {
      if      ( hadTau_absEta < 1.479 ) { sf = 1.09; sfErr = 0.01; }
      else if ( hadTau_absEta > 1.558 ) { sf = 1.19; sfErr = 0.01; }
      break;
    }
    case 2: // Loose
    {
      if      ( hadTau_absEta < 1.479 ) { sf = 1.17; sfErr = 0.04; }
      else if ( hadTau_absEta > 1.558 ) { sf = 1.25; sfErr = 0.06; }
      break;
    }
    case 3: // Medium
    {
      if      ( hadTau_absEta < 1.479 ) { sf = 1.40; sfErr = 0.12; }
      else if ( hadTau_absEta > 1.558 ) { sf = 1.21; sfErr = 0.26; }
      break;
    }
    case 4: // Tight
    {
      if      ( hadTau_absEta < 1.479 ) { sf = 1.80; sfErr = 0.20; }
      else if ( hadTau_absEta > 1.558 ) { sf = 1.53; sfErr = 0.60; }
      break;
    }
    case 5: // vTight
    {
      if      ( hadTau_absEta < 1.479 ) { sf = 1.96; sfErr = 0.27; }
      else if ( hadTau_absEta > 1.558 ) { sf = 1.66; sfErr = 0.80; }
      break;
    }
    default: throw cmsException(__func__, __LINE__)
               << "Invalid parameter 'hadTauSelection_antiElectron' = " << hadTauSelection_antiElectron;
  }

  switch(central_or_shift)
  {
    case FRet::shiftUp:   sf += sfErr; break;
    case FRet::shiftDown: sf -= sfErr; break;
    case FRet::central:                break;
    default:              throw cmsException(__func__, __LINE__)
                            << "Invalid parameter 'central_or_shift' = " << as_integer(central_or_shift);
  }

  sf = std::max(sf, 0.); // CV: require e->tau fake-rates to be positive
  return sf;
}

double
sf_muToTauFakeRate_2017(double hadTau_pt, // unused
                        double hadTau_absEta,
                        int hadTauSelection_antiMuon,
                        FRmt central_or_shift)
{
  double sf = 1.;
  double sfErr = 0.;

  if(hadTauSelection_antiMuon <= 0)
  {
    // no anti-muon discriminator applied
    return sf;
  }

  switch(hadTauSelection_antiMuon)
  {
    case 1: // Loose
    {
      if      ( hadTau_absEta < 0.4 ) { sf = 1.06; sfErr = 0.05; }
      else if ( hadTau_absEta < 0.8 ) { sf = 1.02; sfErr = 0.04; }
      else if ( hadTau_absEta < 1.2 ) { sf = 1.10; sfErr = 0.04; }
      else if ( hadTau_absEta < 1.7 ) { sf = 1.03; sfErr = 0.18; }
      else                            { sf = 1.94; sfErr = 0.35; }
      break;
    }
    case 2: // Tight
    {
      if      ( hadTau_absEta < 0.4 ) { sf = 1.17; sfErr = 0.12; }
      else if ( hadTau_absEta < 0.8 ) { sf = 1.29; sfErr = 0.30; }
      else if ( hadTau_absEta < 1.2 ) { sf = 1.14; sfErr = 0.05; }
      else if ( hadTau_absEta < 1.7 ) { sf = 0.93; sfErr = 0.60; }
      else                            { sf = 1.61; sfErr = 0.60; }
      break;
    }
    default: throw cmsException(__func__, __LINE__)
               << "Invalid parameter 'hadTauSelection_antiMuon' = " << hadTauSelection_antiMuon;
  }

  switch(central_or_shift)
  {
    case FRmt::shiftUp:   sf += sfErr; break;
    case FRmt::shiftDown: sf -= sfErr; break;
    case FRmt::central:                break;
    default:              throw cmsException(__func__, __LINE__)
                            << "Invalid parameter 'central_or_shift' = " << as_integer(central_or_shift);
  }

  sf = std::max(sf, 0.); // CV: require mu->tau fake-rates to be positive
  return sf;
}
//-------------------------------------------------------------------------------
