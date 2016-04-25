#ifndef SYNCNTUPLEMANAGER_H
#define SYNCNTUPLEMANAGER_H

#include <string> // std::string
#include <vector> // std::vector<>

#include <TFile.h> // TFile
#include <TTree.h> // TTree
#include <Rtypes.h> // Float_t, Int_t

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

class SyncNtupleManager
{
public:
  SyncNtupleManager(const std::string & outputFileName,
                    const std::string & outputTreeName);
  ~SyncNtupleManager();

  void initializeBranches();
  void read(std::vector<const RecoJet *> & jets);
  void read(std::vector<const RecoMuon *> & muons);
  void fill();
  void write();
private:
  void reset();

  TFile * outputFile;
  TTree * outputTree;
  const Int_t placeholder_value;

  const Int_t nof_mus;
  const Int_t nof_eles;
  const Int_t nof_taus;
  const Int_t nof_jets;

  Int_t n_presel_jet;
  Float_t * jet_pt;
  Float_t * jet_eta;
  Float_t * jet_phi;
  Float_t * jet_mass;
  Float_t * jet_btagCSV;

  Int_t n_presel_mu;
  Float_t * mu_pt;
  Float_t * mu_eta;
  Float_t * mu_phi;
  Float_t * mu_E;
  Int_t * mu_charge;
  Float_t * mu_miniRelIso;
  Float_t * mu_miniIsoCharged;
  Float_t * mu_miniIsoNeutral;
  Float_t * mu_jetNDauChargedMVASel;
  Float_t * mu_jetPtRel;
  Float_t * mu_jetPtRatio;
  Float_t * mu_jetCSV;
  Float_t * mu_sip3D;
  Float_t * mu_dxy;
  Float_t * mu_dz;
  Int_t * mu_segmentCompatibility;
  Float_t * mu_leptonMVA;
  Float_t * mu_mediumID;
  Float_t * mu_dpt_div_pt;
  Int_t * mu_isfakeablesel;
  Int_t * mu_iscutsel;
  Int_t * mu_ismvasel;
};

#endif // SYNCNTUPLEMANAGER_H
