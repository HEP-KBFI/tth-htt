#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile(), loadTH1(), loadTH2(), getSF_from_TH1(), getSF_from_TH2()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TH1.h> // TH1
#include <TFile.h> // TFile

#include <cassert> // assert()

/**
 * @brief Evaluate data/MC correction for electron and muon trigger efficiency (Table 10 in AN-2015/321)
 * @param type (either kElectron or kMuon), pT and eta of all leptons
 * @return data/MC scale-factor, to be applied as event weight to simulated events
 */
double
sf_triggerEff(int numLeptons,
              int lepton1_type, double lepton1_pt, double lepton1_eta,
              int lepton2_type, double lepton2_pt, double lepton2_eta,
              int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  int numElectrons = 0;
  if(numLeptons >= 1 && lepton1_type == kElectron) ++numElectrons;
  if(numLeptons >= 2 && lepton2_type == kElectron) ++numElectrons;
  if(numLeptons >= 3 && lepton3_type == kElectron) ++numElectrons;

  int numMuons = 0;
  if(numLeptons >= 1 && lepton1_type == kMuon) ++numMuons;
  if(numLeptons >= 2 && lepton2_type == kMuon) ++numMuons;
  if(numLeptons >= 3 && lepton3_type == kMuon) ++numMuons;
  if(numElectrons == 2 && numMuons == 0)
  {
    if( std::max(lepton1_pt, lepton2_pt) > 40.)
    {
      return 0.99;
    }
    else
    {
      return 0.95;
    }
  }
  else if(numElectrons == 1 && numMuons == 1)
  {
    return 0.98;
  }
  else
  {
    return 1.00;
  }
}

//-------------------------------------------------------------------------------
double
sf_electronID_and_Iso_loose(double electron_pt,
                            double electron_eta)
{
  // efficiency for electron to pass loose identification criteria: AN-2015/321, Fig. 10 top left
  static TH2 * lut_id_loose = nullptr;
  if(! lut_id_loose)
  {
    const LocalFileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);

    TFile * const inputFile_id_loose = openFile(fileName_id_loose);
    const std::string histogramName_id_loose = "dummy_pt_eta";
    lut_id_loose = loadTH2(inputFile_id_loose, histogramName_id_loose);

    delete inputFile_id_loose;
    TH1::AddDirectory(true);
  }
  assert(lut_id_loose);

  const double sf_id_loose = getSF_from_TH2(lut_id_loose, electron_pt, electron_eta);

  // electron isolation efficiency: AN-2015/321, Fig. 10 top right
  static TH2 * lut_iso = nullptr;
  if(! lut_iso)
  {
    const LocalFileInPath fileName_iso("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);

    TFile * const inputFile_iso = openFile(fileName_iso);
    const std::string histogramName_iso = "dummy_pt_eta";
    lut_iso = loadTH2(inputFile_iso, histogramName_iso);

    delete inputFile_iso;
    TH1::AddDirectory(true);
  }
  assert(lut_iso);

  const double sf_iso = getSF_from_TH2(lut_iso, electron_pt, electron_eta);

  const double sf = sf_id_loose * sf_iso;
  return sf;
}

double
sf_electronID_and_Iso_tight_to_loose(double electron_pt,
                                     double electron_eta)
{
  // efficiency for electron to pass tight conversion veto and missing inner hits cut: AN-2015/321, Fig. 10 bottom
  static TH2 * lut_convVeto = nullptr;
  if (! lut_convVeto)
  {
    const LocalFileInPath fileName_convVeto("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);

    TFile * const inputFile_convVeto = openFile(fileName_convVeto);
    const std::string histogramName_convVeto = "dummy_pt_eta";
    lut_convVeto = loadTH2(inputFile_convVeto, histogramName_convVeto);

    delete inputFile_convVeto;
    TH1::AddDirectory(true);
  }
  assert(lut_convVeto);

  const double sf_convVeto = getSF_from_TH2(lut_convVeto, electron_pt, electron_eta);

  // efficiency for electron to pass tight identification criteria: AN-2015/321, Fig. 12 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;
  if(std::fabs(electron_eta) < 1.479)
  {
    static TH1 * lut_id_tight_barrel = nullptr;
    if(! lut_id_tight_barrel )
    {
      const LocalFileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_id_tight_barrel = openFile(fileName_id_tight_barrel);
      const std::string histogramName_id_tight_barrel = "dummy_pt";

      lut_id_tight_barrel = loadTH1(inputFile_id_tight_barrel, histogramName_id_tight_barrel);
      delete inputFile_id_tight_barrel;
      TH1::AddDirectory(true);
    }

    assert(lut_id_tight_barrel);
    sf_id_tight = getSF_from_TH1(lut_id_tight_barrel, electron_pt);
  }
  else
  {
    static TH1 * lut_id_tight_endcap = nullptr;
    if (! lut_id_tight_endcap)
    {
      const LocalFileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_id_tight_endcap = openFile(fileName_id_tight_endcap);
      const std::string histogramName_id_tight_endcap = "dummy_pt";
      lut_id_tight_endcap = loadTH1(inputFile_id_tight_endcap, histogramName_id_tight_endcap);

      delete inputFile_id_tight_endcap;
      TH1::AddDirectory(true);
    }

    assert(lut_id_tight_endcap);
    sf_id_tight = getSF_from_TH1(lut_id_tight_endcap, electron_pt);
  }

  const double sf = sf_convVeto * sf_id_tight;
  return sf;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double
sf_muonID_and_Iso_loose(double muon_pt,
                        double muon_eta)
{
  // efficiency for muon to pass loose identification criteria: AN-2015/321, Fig. 11 bottom
  static TH2 * lut_id_loose = nullptr;
  if (! lut_id_loose)
  {
    const LocalFileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);

    TFile * const inputFile_id_loose = openFile(fileName_id_loose);
    const std::string histogramName_id_loose = "dummy_pt_eta";
    lut_id_loose = loadTH2(inputFile_id_loose, histogramName_id_loose);

    delete inputFile_id_loose;
    TH1::AddDirectory(true);
  }
  assert(lut_id_loose);

  const double sf_id_loose = getSF_from_TH2(lut_id_loose, muon_pt, muon_eta);

  // muon isolation efficiency: AN-2015/321, Fig. 11 top left (barrel) and center (endcap)
  double sf_iso = 1.;
  if(std::fabs(muon_eta) < 1.2)
  {
    static TH1 * lut_iso_barrel = nullptr;
    if(! lut_iso_barrel)
    {
      const LocalFileInPath fileName_iso_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_iso_barrel = openFile(fileName_iso_barrel);
      const std::string histogramName_iso_barrel = "dummy_pt";
      lut_iso_barrel = loadTH1(inputFile_iso_barrel, histogramName_iso_barrel);

      delete inputFile_iso_barrel;
      TH1::AddDirectory(true);
    }

    assert(lut_iso_barrel);
    sf_iso = getSF_from_TH1(lut_iso_barrel, muon_pt);
  }
  else
  {
    static TH1 * lut_iso_endcap = nullptr;
    if(! lut_iso_endcap)
    {
      const LocalFileInPath fileName_iso_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_iso_endcap = openFile(fileName_iso_endcap);
      const std::string histogramName_iso_endcap = "dummy_pt";
      lut_iso_endcap = loadTH1(inputFile_iso_endcap, histogramName_iso_endcap);

      delete inputFile_iso_endcap;
      TH1::AddDirectory(true);
    }

    assert(lut_iso_endcap);
    sf_iso = getSF_from_TH1(lut_iso_endcap, muon_pt);
  }

  // efficiency for muon to pass transverse impact parameter cut: AN-2015/321, Fig. 11 top right
  static TH1 * lut_ip = nullptr;
  if(! lut_ip)
  {
    const LocalFileInPath fileName_ip("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);

    TFile * const inputFile_ip = openFile(fileName_ip);
    const std::string histogramName_ip = "dummy_eta";
    lut_ip = loadTH1(inputFile_ip, histogramName_ip);

    delete inputFile_ip;
    TH1::AddDirectory(true);
  }
  assert(lut_ip);
  const double sf_ip = getSF_from_TH1(lut_ip, muon_eta);

  const double sf = sf_id_loose * sf_iso * sf_ip;
  return sf;
}

double
sf_muonID_and_Iso_tight_to_loose(double muon_pt,
                                 double muon_eta)
{
  // efficiency for muon to pass tight identification criteria: AN-2015/321, Fig. 13 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;

  if(std::fabs(muon_eta) < 1.2)
  {
    static TH1 * lut_id_tight_barrel = nullptr;
    if(! lut_id_tight_barrel)
    {
      const LocalFileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_id_tight_barrel = openFile(fileName_id_tight_barrel);
      const std::string histogramName_id_tight_barrel = "dummy_pt";
      lut_id_tight_barrel = loadTH1(inputFile_id_tight_barrel, histogramName_id_tight_barrel);

      delete inputFile_id_tight_barrel;
      TH1::AddDirectory(true);
    }

    assert(lut_id_tight_barrel);
    sf_id_tight = getSF_from_TH1(lut_id_tight_barrel, muon_pt);
  }
  else
  {
    static TH1 * lut_id_tight_endcap = nullptr;
    if(! lut_id_tight_endcap)
    {
      const LocalFileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);

      TFile * const inputFile_id_tight_endcap = openFile(fileName_id_tight_endcap);
      const std::string histogramName_id_tight_endcap = "dummy_pt";
      lut_id_tight_endcap = loadTH1(inputFile_id_tight_endcap, histogramName_id_tight_endcap);

      delete inputFile_id_tight_endcap;
      TH1::AddDirectory(true);
    }

    assert(lut_id_tight_endcap);
    sf_id_tight = getSF_from_TH1(lut_id_tight_endcap, muon_pt);
  }

  const double sf = sf_id_tight;
  return sf;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double
sf_leptonID_and_Iso_loose(int numLeptons,
                          int lepton1_type, double lepton1_pt, double lepton1_eta,
                          int lepton2_type, double lepton2_pt, double lepton2_eta,
                          int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  const auto computeSF = [](int lepton_type,
                            double lepton_pt,
                            double lepton_eta) -> double
  {
    switch(lepton_type)
    {
      case kElectron: return sf_electronID_and_Iso_loose(lepton_pt, lepton_eta);
      case kMuon:     return sf_muonID_and_Iso_loose    (lepton_pt, lepton_eta);
      default:        assert(0);
    }
  };

  const double lepton1_sf = numLeptons >= 1 ? computeSF(lepton1_type, lepton1_pt, lepton1_eta) : 1.;
  const double lepton2_sf = numLeptons >= 2 ? computeSF(lepton2_type, lepton2_pt, lepton2_eta) : 1.;
  const double lepton3_sf = numLeptons >= 3 ? computeSF(lepton3_type, lepton3_pt, lepton3_eta) : 1.;

  const double sf = lepton1_sf * lepton2_sf * lepton3_sf;
  return sf;
}

double
sf_leptonID_and_Iso_fakeable_to_loose(int numLeptons,
                                      int lepton1_type, double lepton1_pt, double lepton1_eta,
                                      int lepton2_type, double lepton2_pt, double lepton2_eta,
                                      int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  return 1.;
}

double
sf_leptonID_and_Iso_fakeable(int numLeptons,
                             int lepton1_type, double lepton1_pt, double lepton1_eta,
                             int lepton2_type, double lepton2_pt, double lepton2_eta,
                             int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  const double sf_loose = sf_leptonID_and_Iso_loose(
    numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta,
    lepton2_type, lepton2_pt, lepton2_eta,
    lepton3_type, lepton3_pt, lepton3_eta
  );
  const double sf_fakeable_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(
    numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta,
    lepton2_type, lepton2_pt, lepton2_eta,
    lepton3_type, lepton3_pt, lepton3_eta
  );
  return sf_loose * sf_fakeable_to_loose;
}

double
sf_leptonID_and_Iso_tight_to_loose(int numLeptons,
                                   int lepton1_type, double lepton1_pt, double lepton1_eta,
                                   int lepton2_type, double lepton2_pt, double lepton2_eta,
                                   int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  const auto computeSF = [](int lepton_type,
                            double lepton_pt,
                            double lepton_eta) -> double
  {
    switch(lepton_type)
    {
      case kElectron: return sf_electronID_and_Iso_tight_to_loose(lepton_pt, lepton_eta);
      case kMuon:     return sf_muonID_and_Iso_tight_to_loose    (lepton_pt, lepton_eta);
      default:        assert(0);
    }
  };

  const double lepton1_sf = numLeptons >= 1 ? computeSF(lepton1_type, lepton1_pt, lepton1_eta) : 1.;
  const double lepton2_sf = numLeptons >= 2 ? computeSF(lepton2_type, lepton2_pt, lepton2_eta) : 1.;
  const double lepton3_sf = numLeptons >= 3 ? computeSF(lepton3_type, lepton3_pt, lepton3_eta) : 1.;

  const double sf = lepton1_sf * lepton2_sf * lepton3_sf;
  return sf;
}

double
sf_leptonID_and_Iso_tight(int numLeptons,
                          int lepton1_type, double lepton1_pt, double lepton1_eta,
                          int lepton2_type, double lepton2_pt, double lepton2_eta,
                          int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  const double sf_loose = sf_leptonID_and_Iso_loose(
    numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta, 
    lepton3_type, lepton3_pt, lepton3_eta
  );
  const double sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(
    numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta, 
    lepton3_type, lepton3_pt, lepton3_eta
  );
  return sf_loose*sf_tight_to_loose;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//CV: data/MC scale-factors for e->tau and mu->tau fake-rates taken from
//    https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV

double
sf_eToTauFakeRate_2017(double hadTau_pt, // unused
                       double hadTau_absEta,
                       int hadTauSelection_antiElectron,
                       int central_or_shift)
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
      if  (hadTau_absEta < 1.479) { sf = 1.02; sfErr = 0.05; }
      else                        { sf = 1.11; sfErr = 0.05; }
      break;
    }
    case 2: // Loose
    {
      if  (hadTau_absEta < 1.479) { sf = 1.14; sfErr = 0.04; }
      else                        { sf = 1.09; sfErr = 0.05; }
      break;
    }
    case 3: // Medium
    {
      if  (hadTau_absEta < 1.479) { sf = 1.50; sfErr = 0.13; }
      else                        { sf = 1.06; sfErr = 0.18; }
      break;
    }
    case 4: // Tight
    {
      if  (hadTau_absEta < 1.479) { sf = 1.80; sfErr = 0.23; }
      else                        { sf = 1.30; sfErr = 0.42; }
      break;
    }
    case 5: // vTight
    {
      if  (hadTau_absEta < 1.479) { sf = 1.89; sfErr = 0.35; }
      else                        { sf = 1.69; sfErr = 0.68; }
      break;
    }
    default: throw cmsException(__func__, __LINE__)
               << "Invalid parameter 'hadTauSelection_antiElectron' = " << hadTauSelection_antiElectron;
  }

  switch(central_or_shift)
  {
    case kFRet_shiftUp:   sf += sfErr; break;
    case kFRet_shiftDown: sf -= sfErr; break;
    case kFRet_central:                break;
    default:              throw cmsException(__func__, __LINE__)
                            << "Invalid parameter 'central_or_shift' = " << central_or_shift;
  }

  sf = std::max(sf, 0.); // CV: require e->tau fake-rates to be positive
  return sf;
}

double
sf_muToTauFakeRate_2017(double hadTau_pt, // unused
                        double hadTau_absEta,
                        int hadTauSelection_antiMuon,
                        int central_or_shift)
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
      if     (hadTau_absEta < 0.4) { sf = 1.15; sfErr = 0.05; }
      else if(hadTau_absEta < 0.8) { sf = 1.15; sfErr = 0.05; }
      else if(hadTau_absEta < 1.2) { sf = 1.18; sfErr = 0.05; }
      else if(hadTau_absEta < 1.7) { sf = 1.20; sfErr = 0.20; }
      else if(hadTau_absEta < 2.3) { sf = 1.30; sfErr = 0.30; }
      break;
    }
    case 2: // Tight
    {
      if     (hadTau_absEta < 0.4) { sf = 1.50; sfErr = 0.10; }
      else if(hadTau_absEta < 0.8) { sf = 1.40; sfErr = 0.10; }
      else if(hadTau_absEta < 1.2) { sf = 1.21; sfErr = 0.06; }
      else if(hadTau_absEta < 1.7) { sf = 2.60; sfErr = 0.90; }
      else if(hadTau_absEta < 2.3) { sf = 2.10; sfErr = 0.90; }
      break;
    }
    default: throw cmsException(__func__, __LINE__)
               << "Invalid parameter 'hadTauSelection_antiMuon' = " << hadTauSelection_antiMuon;
  }

  switch(central_or_shift)
  {
    case kFRmt_shiftUp:   sf += sfErr; break;
    case kFRmt_shiftDown: sf -= sfErr; break;
    case kFRmt_central:                break;
    default:              throw cmsException(__func__, __LINE__)
                            << "Invalid parameter 'central_or_shift' = " << central_or_shift;
  }

  sf = std::max(sf, 0.); // CV: require mu->tau fake-rates to be positive
  return sf;
}
//-------------------------------------------------------------------------------
