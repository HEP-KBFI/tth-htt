#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"

#include <assert.h> // assert

/**
 * @brief Evaluate data/MC correction for electron and muon trigger efficiency (Table 10 in AN-2015/321)
 * @param type (either kElectron or kMuon), pT and eta of all leptons
 * @return data/MC scale-factor, to be applied as event weight to simulated events
 */
double sf_triggerEff(
  int numLeptons,		     
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta, 
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  int numElectrons = 0;
  if ( numLeptons >= 1 && lepton1_type == kElectron ) ++numElectrons;
  if ( numLeptons >= 2 && lepton2_type == kElectron ) ++numElectrons;
  if ( numLeptons >= 3 && lepton3_type == kElectron ) ++numElectrons;
  int numMuons = 0;
  if ( numLeptons >= 1 && lepton1_type == kMuon     ) ++numMuons;
  if ( numLeptons >= 2 && lepton2_type == kMuon     ) ++numMuons;
  if ( numLeptons >= 3 && lepton3_type == kMuon     ) ++numMuons;
  if ( numElectrons == 2 && numMuons == 0 ) {
    if ( std::max(lepton1_pt, lepton2_pt) > 40. ) return 0.99;
    else return 0.95;
  } else if ( numElectrons == 1 && numMuons == 1 ) {
    return 0.98;
  } else {
    return 1.00;
  }
}

//-------------------------------------------------------------------------------
double sf_electronID_and_Iso_loose(double electron_pt, double electron_eta)
{
  // efficiency for electron to pass loose identification criteria: AN-2015/321, Fig. 10 top left
  static TH2* lut_id_loose = 0;
  if ( !lut_id_loose ) {
    edm::FileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);
    TFile* inputFile_id_loose = openFile(fileName_id_loose);
    std::string histogramName_id_loose = "dummy_pt_eta";
    lut_id_loose = loadTH2(inputFile_id_loose, histogramName_id_loose);
    delete inputFile_id_loose;
    TH1::AddDirectory(true);
  }
  assert(lut_id_loose);
  double sf_id_loose = getSF_from_TH2(lut_id_loose, electron_pt, electron_eta);
  
  // electron isolation efficiency: AN-2015/321, Fig. 10 top right
  static TH2* lut_iso = 0;
  if ( !lut_iso ) {
    edm::FileInPath fileName_iso("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);
    TFile* inputFile_iso = openFile(fileName_iso);
    std::string histogramName_iso = "dummy_pt_eta";
    lut_iso = loadTH2(inputFile_iso, histogramName_iso);
    delete inputFile_iso;
    TH1::AddDirectory(true);
  }
  assert(lut_iso);
  double sf_iso = getSF_from_TH2(lut_iso, electron_pt, electron_eta);

  double sf = sf_id_loose*sf_iso;
  return sf;
}

double sf_electronID_and_Iso_tight_to_loose(double electron_pt, double electron_eta)
{
  // efficiency for electron to pass tight conversion veto and missing inner hits cut: AN-2015/321, Fig. 10 bottom
  static TH2* lut_convVeto = 0;
  if ( !lut_convVeto ) {
    edm::FileInPath fileName_convVeto("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);
    TFile* inputFile_convVeto = openFile(fileName_convVeto);
    std::string histogramName_convVeto = "dummy_pt_eta";
    lut_convVeto = loadTH2(inputFile_convVeto, histogramName_convVeto);
    delete inputFile_convVeto;
    TH1::AddDirectory(true);
  }
  assert(lut_convVeto);
  double sf_convVeto = getSF_from_TH2(lut_convVeto, electron_pt, electron_eta);

  // efficiency for electron to pass tight identification criteria: AN-2015/321, Fig. 12 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;
  if ( fabs(electron_eta) < 1.479 ) {
    static TH1* lut_id_tight_barrel = 0;
    if ( !lut_id_tight_barrel ) {
      edm::FileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_id_tight_barrel = openFile(fileName_id_tight_barrel);
      std::string histogramName_id_tight_barrel = "dummy_pt";
      lut_id_tight_barrel = loadTH1(inputFile_id_tight_barrel, histogramName_id_tight_barrel);
      delete inputFile_id_tight_barrel;
      TH1::AddDirectory(true);
    }
    assert(lut_id_tight_barrel);
    sf_id_tight = getSF_from_TH1(lut_id_tight_barrel, electron_pt);
  } else {
    static TH1* lut_id_tight_endcap = 0;
    if ( !lut_id_tight_endcap ) {
      edm::FileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_id_tight_endcap = openFile(fileName_id_tight_endcap);
      std::string histogramName_id_tight_endcap = "dummy_pt";
      lut_id_tight_endcap = loadTH1(inputFile_id_tight_endcap, histogramName_id_tight_endcap);
      delete inputFile_id_tight_endcap;
      TH1::AddDirectory(true);
    }
    assert(lut_id_tight_endcap);
    sf_id_tight = getSF_from_TH1(lut_id_tight_endcap, electron_pt);
  }

  double sf = sf_convVeto*sf_id_tight;
  return sf;
}

//double sf_electronID_and_Iso_tight(double electron_pt, double electron_eta)
//{
//  double sf_loose = sf_electronID_and_Iso_loose(electron_pt, electron_eta);
//  double sf_tight_to_loose = sf_electronID_and_Iso_tight_to_loose(electron_pt, electron_eta);
//  return sf_loose*sf_tight_to_loose;
//}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double sf_muonID_and_Iso_loose(double muon_pt, double muon_eta)
{
  // efficiency for muon to pass loose identification criteria: AN-2015/321, Fig. 11 bottom
  static TH2* lut_id_loose = 0;
  if ( !lut_id_loose ) {
    edm::FileInPath fileName_id_loose("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);
    TFile* inputFile_id_loose = openFile(fileName_id_loose);
    std::string histogramName_id_loose = "dummy_pt_eta";
    lut_id_loose = loadTH2(inputFile_id_loose, histogramName_id_loose);
    delete inputFile_id_loose;
    TH1::AddDirectory(true);
  }
  assert(lut_id_loose);
  double sf_id_loose = getSF_from_TH2(lut_id_loose, muon_pt, muon_eta);

  // muon isolation efficiency: AN-2015/321, Fig. 11 top left (barrel) and center (endcap)
  double sf_iso = 1.;
  if ( fabs(muon_eta) < 1.2 ) {
    static TH1* lut_iso_barrel = 0;
    if ( !lut_iso_barrel ) {
      edm::FileInPath fileName_iso_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_iso_barrel = openFile(fileName_iso_barrel);
      std::string histogramName_iso_barrel = "dummy_pt";
      lut_iso_barrel = loadTH1(inputFile_iso_barrel, histogramName_iso_barrel);
      delete inputFile_iso_barrel;
      TH1::AddDirectory(true);
    }
    assert(lut_iso_barrel);
    sf_iso = getSF_from_TH1(lut_iso_barrel, muon_pt);
  } else {
    static TH1* lut_iso_endcap = 0;
    if ( !lut_iso_endcap ) {
      edm::FileInPath fileName_iso_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_iso_endcap = openFile(fileName_iso_endcap);
      std::string histogramName_iso_endcap = "dummy_pt";
      lut_iso_endcap = loadTH1(inputFile_iso_endcap, histogramName_iso_endcap);
      delete inputFile_iso_endcap;
      TH1::AddDirectory(true);
    }
    assert(lut_iso_endcap);
    sf_iso = getSF_from_TH1(lut_iso_endcap, muon_pt);
  }
  
  // efficiency for muon to pass transverse impact parameter cut: AN-2015/321, Fig. 11 top right
  static TH1* lut_ip = 0;
  if ( !lut_ip ) {
    edm::FileInPath fileName_ip("tthAnalysis/HiggsToTauTau/data/dummy.root");
    TH1::AddDirectory(false);
    TFile* inputFile_ip = openFile(fileName_ip);
    std::string histogramName_ip = "dummy_eta";
    lut_ip = loadTH1(inputFile_ip, histogramName_ip);
    delete inputFile_ip;
    TH1::AddDirectory(true);
  }
  assert(lut_ip);
  double sf_ip = getSF_from_TH1(lut_ip, muon_eta);
  
  double sf = sf_id_loose*sf_iso*sf_ip;
  return sf;
}

double sf_muonID_and_Iso_tight_to_loose(double muon_pt, double muon_eta)
{
  // efficiency for muon to pass tight identification criteria: AN-2015/321, Fig. 13 top left (barrel) and center (endcap)
  double sf_id_tight = 1.;
  if ( fabs(muon_eta) < 1.2 ) {
    static TH1* lut_id_tight_barrel = 0;
    if ( !lut_id_tight_barrel ) {
      edm::FileInPath fileName_id_tight_barrel("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_id_tight_barrel = openFile(fileName_id_tight_barrel);
      std::string histogramName_id_tight_barrel = "dummy_pt";
      lut_id_tight_barrel = loadTH1(inputFile_id_tight_barrel, histogramName_id_tight_barrel);
      delete inputFile_id_tight_barrel;
      TH1::AddDirectory(true);
    }
    assert(lut_id_tight_barrel);
    sf_id_tight = getSF_from_TH1(lut_id_tight_barrel, muon_pt);
  } else {
    static TH1* lut_id_tight_endcap = 0;
    if ( !lut_id_tight_endcap ) {
      edm::FileInPath fileName_id_tight_endcap("tthAnalysis/HiggsToTauTau/data/dummy.root");
      TH1::AddDirectory(false);
      TFile* inputFile_id_tight_endcap = openFile(fileName_id_tight_endcap);
      std::string histogramName_id_tight_endcap = "dummy_pt";
      lut_id_tight_endcap = loadTH1(inputFile_id_tight_endcap, histogramName_id_tight_endcap);
      delete inputFile_id_tight_endcap;
      TH1::AddDirectory(true);
    }
    assert(lut_id_tight_endcap);
    sf_id_tight = getSF_from_TH1(lut_id_tight_endcap, muon_pt);
  }

  double sf = sf_id_tight;
  return sf;
}

//double sf_muonID_and_Iso_tight(double muon_pt, double muon_eta)
//{
//  double sf_loose = sf_muonID_and_Iso_loose(muon_pt, muon_eta);
//  double sf_tight_to_loose = sf_muonID_and_Iso_tight_to_loose(muon_pt, muon_eta);
//  return sf_loose*sf_tight_to_loose;
//}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double sf_leptonID_and_Iso_loose(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta, 
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  double lepton1_sf = 1.;
  if ( numLeptons >= 1 ) {
    if      ( lepton1_type == kElectron ) lepton1_sf = sf_electronID_and_Iso_loose(lepton1_pt, lepton1_eta);
    else if ( lepton1_type == kMuon     ) lepton1_sf = sf_muonID_and_Iso_loose(lepton1_pt, lepton1_eta);
    else assert(0);
  }

  double lepton2_sf = 1.;
  if ( numLeptons >= 2 ) {
    if      ( lepton2_type == kElectron ) lepton2_sf = sf_electronID_and_Iso_loose(lepton2_pt, lepton2_eta);
    else if ( lepton2_type == kMuon     ) lepton2_sf = sf_muonID_and_Iso_loose(lepton2_pt, lepton2_eta);
    else assert(0);
  }

  double lepton3_sf = 1.;
  if ( numLeptons >= 3 ) {
    if      ( lepton3_type == kElectron ) lepton3_sf = sf_electronID_and_Iso_loose(lepton3_pt, lepton3_eta);
    else if ( lepton3_type == kMuon     ) lepton3_sf = sf_muonID_and_Iso_loose(lepton3_pt, lepton3_eta);
    else assert(0);
  }

  double sf = lepton1_sf*lepton2_sf*lepton3_sf;
  return sf;
}

double sf_leptonID_and_Iso_fakeable_to_loose(int numLeptons,					     
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta,
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  return 1.;
}

double sf_leptonID_and_Iso_fakeable(
  int numLeptons,				    
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta,
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta,
    lepton3_type, lepton3_pt, lepton3_eta);
  double sf_fakeable_to_loose = sf_leptonID_and_Iso_fakeable_to_loose(numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta, 
    lepton3_type, lepton3_pt, lepton3_eta);
  return sf_loose*sf_fakeable_to_loose;
}

double sf_leptonID_and_Iso_tight_to_loose(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta,
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  double lepton1_sf = 1.;
  if ( numLeptons >= 1 ) {
    if      ( lepton1_type == kElectron ) lepton1_sf = sf_electronID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
    else if ( lepton1_type == kMuon     ) lepton1_sf = sf_muonID_and_Iso_tight_to_loose(lepton1_pt, lepton1_eta);
    else assert(0);
  }

  double lepton2_sf = 1.;
  if ( numLeptons >= 2 ) {
    if      ( lepton2_type == kElectron ) lepton2_sf = sf_electronID_and_Iso_tight_to_loose(lepton2_pt, lepton2_eta);
    else if ( lepton2_type == kMuon     ) lepton2_sf = sf_muonID_and_Iso_tight_to_loose(lepton2_pt, lepton2_eta);
    else assert(0);
  }

  double lepton3_sf = 1.;
  if ( numLeptons >= 3 ) {
    if      ( lepton3_type == kElectron ) lepton3_sf = sf_electronID_and_Iso_tight_to_loose(lepton3_pt, lepton3_eta);
    else if ( lepton3_type == kMuon     ) lepton3_sf = sf_muonID_and_Iso_tight_to_loose(lepton3_pt, lepton3_eta);
    else assert(0);
  }

  double sf = lepton1_sf*lepton2_sf*lepton3_sf;
  return sf;
}

double sf_leptonID_and_Iso_tight(int numLeptons,
  int lepton1_type, double lepton1_pt, double lepton1_eta, 
  int lepton2_type, double lepton2_pt, double lepton2_eta,
  int lepton3_type, double lepton3_pt, double lepton3_eta)
{
  double sf_loose = sf_leptonID_and_Iso_loose(numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta, 
    lepton3_type, lepton3_pt, lepton3_eta);
  double sf_tight_to_loose = sf_leptonID_and_Iso_tight_to_loose(numLeptons,
    lepton1_type, lepton1_pt, lepton1_eta, 
    lepton2_type, lepton2_pt, lepton2_eta, 
    lepton3_type, lepton3_pt, lepton3_eta);
  return sf_loose*sf_tight_to_loose;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//CV: data/MC scale-factors for e->tau and mu->tau fake-rates taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendation13TeV

double sf_eToTauFakeRate_2016(double hadTau_pt, double hadTau_absEta, int hadTauSelection_antiElectron, int central_or_shift)
{
  double sf = 1.;
  double sfErr = 0.;
  if ( hadTauSelection_antiElectron == 1 ) { // vLoose
    if   ( hadTau_absEta < 1.479 ) { sf = 1.02; sfErr = 0.05; }
    else                           { sf = 1.11; sfErr = 0.05; }
  } else if ( hadTauSelection_antiElectron == 2 ) { // Loose
    if   ( hadTau_absEta < 1.479 ) { sf = 1.14; sfErr = 0.04; }
    else                           { sf = 1.09; sfErr = 0.05; }
  } else if ( hadTauSelection_antiElectron == 3 ) { // Medium
    if   ( hadTau_absEta < 1.479 ) { sf = 1.50; sfErr = 0.13; }
    else                           { sf = 1.06; sfErr = 0.18; }
  } else if ( hadTauSelection_antiElectron == 4 ) { // Tight
    if   ( hadTau_absEta < 1.479 ) { sf = 1.80; sfErr = 0.23; }
    else                           { sf = 1.30; sfErr = 0.42; }
  } else if ( hadTauSelection_antiElectron == 5 ) { // vTight
    if   ( hadTau_absEta < 1.479 ) { sf = 1.89; sfErr = 0.35; }
    else                           { sf = 1.69; sfErr = 0.68; }
  } else throw cms::Exception("sf_eToTauFakeRate") 
    << "Invalid parameter 'hadTauSelection_antiElectron' = " << hadTauSelection_antiElectron << " !!\n";
  if      ( central_or_shift == kFRet_shiftUp   ) sf += sfErr;
  else if ( central_or_shift == kFRet_shiftDown ) sf -= sfErr;
  else if ( central_or_shift != kFRet_central   ) throw cms::Exception("sf_eToTauFakeRate") 
    << "Invalid parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  if ( sf < 0. ) sf = 0.; // CV: require e->tau fake-rates to be positive
  return sf;
}

double sf_muToTauFakeRate_2016(double hadTau_pt, double hadTau_absEta, int hadTauSelection_antiMuon, int central_or_shift)
{
  double sf = 1.;
  double sfErr = 0.;
  if ( hadTauSelection_antiMuon == 1 ) { // Loose
    if      ( hadTau_absEta < 0.4 ) { sf = 1.15; sfErr = 0.05; }
    else if ( hadTau_absEta < 0.8 ) { sf = 1.15; sfErr = 0.05; }
    else if ( hadTau_absEta < 1.2 ) { sf = 1.18; sfErr = 0.05; }
    else if ( hadTau_absEta < 1.7 ) { sf = 1.20; sfErr = 0.20; }
    else if ( hadTau_absEta < 2.3 ) { sf = 1.30; sfErr = 0.30; }
  } else if ( hadTauSelection_antiMuon == 2 ) { // Tight
    if      ( hadTau_absEta < 0.4 ) { sf = 1.50; sfErr = 0.10; }
    else if ( hadTau_absEta < 0.8 ) { sf = 1.40; sfErr = 0.10; }
    else if ( hadTau_absEta < 1.2 ) { sf = 1.21; sfErr = 0.06; }
    else if ( hadTau_absEta < 1.7 ) { sf = 2.60; sfErr = 0.90; }
    else if ( hadTau_absEta < 2.3 ) { sf = 2.10; sfErr = 0.90; }
  } else throw cms::Exception("sf_muToTauFakeRate") 
    << "Invalid parameter 'hadTauSelection_antiMuon' = " << hadTauSelection_antiMuon << " !!\n";
  if      ( central_or_shift == kFRet_shiftUp   ) sf += sfErr;
  else if ( central_or_shift == kFRet_shiftDown ) sf -= sfErr;
  else if ( central_or_shift != kFRet_central   ) throw cms::Exception("sf_muToTauFakeRate") 
    << "Invalid parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  if ( sf < 0. ) sf = 0.; // CV: require mu->tau fake-rates to be positive
  return sf;
}
//-------------------------------------------------------------------------------
