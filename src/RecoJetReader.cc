#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <TString.h> // Form

std::map<std::string, int> RecoJetReader::numInstances_;
std::map<std::string, RecoJetReader*> RecoJetReader::instances_;

RecoJetReader::RecoJetReader(int era)
  : era_(era)
  , max_nJets_(32)
  , branchName_num_("nJet")
  , branchName_obj_("Jet")
  , jetPt_option_(RecoJetReader::kJetPt_central)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
{
  setBranchNames();
}

RecoJetReader::RecoJetReader(int era, const std::string& branchName_num, const std::string& branchName_obj)
  : era_(era)
  , max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , jetPt_option_(RecoJetReader::kJetPt_central)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
{
  setBranchNames();
}

RecoJetReader::~RecoJetReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    RecoJetReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->jet_pt_;
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->jet_mass_;
    delete[] gInstance->jet_corr_;
    delete[] gInstance->jet_corr_JECUp_;
    delete[] gInstance->jet_corr_JECDown_;
    delete[] gInstance->jet_BtagCSV_;
    delete[] gInstance->jet_BtagWeight_;
    instances_[branchName_obj_] = 0;
  }
}

void RecoJetReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");    
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_corr_ = Form("%s_%s", branchName_obj_.data(), "corr");
    branchName_corr_JECUp_ = Form("%s_%s_%s", branchName_obj_.data(), "corr", "JECUp");
    branchName_corr_JECDown_ = Form("%s_%s_%s", branchName_obj_.data(), "corr", "JECDown");
    branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), "btagCSV");
    if      ( era_ == kEra_2015 ) branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "bTagWeight");
    else if ( era_ == kEra_2016 ) branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "btagWeightCSV");
    else assert(0);
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("RecoJetReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

namespace
{
  void initializeArray(Float_t* array, int numElements, double value = 0.)
  {
    for ( int idxElement = 0; idxElement < numElements; ++idxElement ) {
      array[idxElement] = value;
    }
  }
}

void RecoJetReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nJets_);   
    jet_pt_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_pt_.data(), jet_pt_); 
    jet_eta_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_eta_.data(), jet_eta_); 
    jet_phi_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_phi_.data(), jet_phi_); 
    jet_mass_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_mass_.data(), jet_mass_); 
    jet_corr_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_corr_.data(), jet_corr_); 
    jet_corr_JECUp_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_corr_JECUp_.data(), jet_corr_JECUp_); 
    jet_corr_JECDown_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_corr_JECDown_.data(), jet_corr_JECDown_);     
    jet_BtagCSV_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_BtagCSV_.data(), jet_BtagCSV_); 
    jet_BtagWeight_ = new Float_t[max_nJets_];
    if ( branchName_BtagWeight_ != "" ) {
      tree->SetBranchAddress(branchName_BtagWeight_.data(), jet_BtagWeight_); 
    } else {
      initializeArray(jet_BtagWeight_, max_nJets_, 1.);
    }
  }
}

std::vector<RecoJet> RecoJetReader::read() const
{
  RecoJetReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<RecoJet> jets;
  Int_t nJets = gInstance->nJets_;
  if ( nJets > max_nJets_ ) {
    throw cms::Exception("RecoJetReader") 
      << "Number of jets stored in Ntuple = " << nJets << ", exceeds max_nJets = " << max_nJets_ << " !!\n";
  }
  jets.reserve(nJets);
  for ( Int_t idxJet = 0; idxJet < nJets; ++idxJet ) {
    Float_t jet_pt = -1.;
    if      ( jetPt_option_ == kJetPt_central ) jet_pt = gInstance->jet_pt_[idxJet];
    else if ( jetPt_option_ == kJetPt_jecUp   ) jet_pt = gInstance->jet_pt_[idxJet]*gInstance->jet_corr_JECUp_[idxJet]/gInstance->jet_corr_[idxJet];
    else if ( jetPt_option_ == kJetPt_jecDown ) jet_pt = gInstance->jet_pt_[idxJet]*gInstance->jet_corr_JECDown_[idxJet]/gInstance->jet_corr_[idxJet];    
    else assert(0);
    jets.push_back(RecoJet(
      jet_pt,      
      gInstance->jet_eta_[idxJet],
      gInstance->jet_phi_[idxJet],
      gInstance->jet_mass_[idxJet],
      gInstance->jet_corr_[idxJet],
      gInstance->jet_corr_JECUp_[idxJet],
      gInstance->jet_corr_JECDown_[idxJet],
      gInstance->jet_BtagCSV_[idxJet],
      gInstance->jet_BtagWeight_[idxJet],	
      idxJet ));
  }
  return jets;
}
