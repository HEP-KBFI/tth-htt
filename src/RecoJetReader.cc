#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kBtag_hfUp,..., kBtag_jesDown

#include <TString.h> // Form

std::map<std::string, int> RecoJetReader::numInstances_;
std::map<std::string, RecoJetReader*> RecoJetReader::instances_;

RecoJetReader::RecoJetReader(int era, bool isMC, bool readGenMatching)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_("nJet")
  , branchName_obj_("Jet")
  , genLeptonReader_(0)
  , genHadTauReader_(0)
  , genJetReader_(0)
  , jetPt_option_(RecoJetReader::kJetPt_central)
  , read_BtagWeight_systematics_(false)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
  , jet_QGDiscr_(0)
  , jet_heppyFlavour_(0)
{
  if ( readGenMatching_ ) {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
    genHadTauReader_ = new GenHadTauReader(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
    genJetReader_ = new GenJetReader(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  }
  setBranchNames();
}

RecoJetReader::RecoJetReader(int era, bool isMC, const std::string& branchName_num, const std::string& branchName_obj, bool readGenMatching)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonReader_(0)
  , genHadTauReader_(0)
  , genJetReader_(0)
  , readGenMatching_(readGenMatching)
  , jetPt_option_(RecoJetReader::kJetPt_central)
  , read_BtagWeight_systematics_(false)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
  , jet_QGDiscr_(0)
  , jet_heppyFlavour_(0)
{
  if ( readGenMatching_ ) {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
    genHadTauReader_ = new GenHadTauReader(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
    genJetReader_ = new GenJetReader(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  }
  setBranchNames();
}

RecoJetReader::~RecoJetReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    RecoJetReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->genLeptonReader_;
    delete gInstance->genHadTauReader_;
    delete gInstance->genJetReader_;
    delete[] gInstance->jet_pt_;
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->jet_mass_;
    delete[] gInstance->jet_corr_;
    delete[] gInstance->jet_corr_JECUp_;
    delete[] gInstance->jet_corr_JECDown_;
    delete[] gInstance->jet_BtagCSV_;
    delete[] gInstance->jet_BtagWeight_;
    delete[] gInstance->jet_QGDiscr_;
    delete[] gInstance->jet_heppyFlavour_;
    for ( std::map<int, Float_t*>::iterator it = gInstance->jet_BtagWeights_systematics_.begin();
	  it != gInstance->jet_BtagWeights_systematics_.end(); ++it ) {
      delete[] it->second;
    }
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
    if ( era_ == kEra_2015 ) {
      branchName_QGDiscr_ = "";
    } else if ( era_ == kEra_2016 ) {
      branchName_QGDiscr_ = Form("%s_%s", branchName_obj_.data(), "qgl");
    } else assert(0);
    if ( isMC_ ) {
      if ( era_ == kEra_2015 ) {
	branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "bTagWeight");
      } else if ( era_ == kEra_2016 ) {
	branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "btagWeightCSV");
      } else assert(0);
      for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
	std::string branchName_BtagWeight = TString(getBranchName_bTagWeight(era_, idxShift)).ReplaceAll("Jet_", Form("%s_", branchName_obj_.data())).Data();
	branchNames_BtagWeight_systematics_[idxShift] = branchName_BtagWeight;
      }      
      //branchName_heppyFlavour_ = Form("%s_%s", branchName_obj_.data(), "heppyFlavour"); // KE (20/03/17): doesn't exist in the latest production/addMEM Ntuples
    }
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
  template <typename T1, typename T2>
  void initializeArray(T1* array, int numElements, T2 value)
  {
    for ( int idxElement = 0; idxElement < numElements; ++idxElement ) {
      array[idxElement] = value;
    }
  }
}

void RecoJetReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    if ( readGenMatching_ ) {
      genLeptonReader_->setBranchAddresses(tree);
      genHadTauReader_->setBranchAddresses(tree);
      genJetReader_->setBranchAddresses(tree);  
    }
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
    if ( read_BtagWeight_systematics_ ) {
      for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
	jet_BtagWeights_systematics_[idxShift] = new Float_t[max_nJets_];
	tree->SetBranchAddress(branchNames_BtagWeight_systematics_[idxShift].data(), jet_BtagWeights_systematics_[idxShift]);
      }
    }
    jet_QGDiscr_ = new Float_t[max_nJets_];
    if ( branchName_QGDiscr_ != "" ) {
      tree->SetBranchAddress(branchName_QGDiscr_.data(), jet_QGDiscr_); 
    } else { 
      initializeArray(jet_QGDiscr_, max_nJets_, 1.);
    }
    jet_heppyFlavour_ = new Int_t[max_nJets_];
    if ( branchName_heppyFlavour_ != "" ) {
      tree->SetBranchAddress(branchName_heppyFlavour_.data(), jet_heppyFlavour_); 
    } else {
      initializeArray(jet_heppyFlavour_, max_nJets_, -1);
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
  if ( nJets > 0 ) {
    jets.reserve(nJets);
    for ( Int_t idxJet = 0; idxJet < nJets; ++idxJet ) {
      Float_t jet_pt = -1.;
      if      ( jetPt_option_ == RecoJetReader::kJetPt_central ) jet_pt = gInstance->jet_pt_[idxJet];
      else if ( jetPt_option_ == RecoJetReader::kJetPt_jecUp   ) jet_pt = gInstance->jet_pt_[idxJet]*gInstance->jet_corr_JECUp_[idxJet]/gInstance->jet_corr_[idxJet];
      else if ( jetPt_option_ == RecoJetReader::kJetPt_jecDown ) jet_pt = gInstance->jet_pt_[idxJet]*gInstance->jet_corr_JECDown_[idxJet]/gInstance->jet_corr_[idxJet];
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
	gInstance->jet_QGDiscr_[idxJet],
	gInstance->jet_heppyFlavour_[idxJet],
	idxJet ));
      RecoJet& jet = jets.back();
      jet.BtagCSV_ = gInstance->jet_BtagCSV_[idxJet];
      if ( read_BtagWeight_systematics_ ) {
	for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
	  std::map<int, Float_t*>::const_iterator jet_BtagWeight_systematics_iter = jet_BtagWeights_systematics_.find(idxShift);
	  if ( jet_BtagWeight_systematics_iter != jet_BtagWeights_systematics_.end() ) {
	    jet.BtagWeight_systematics_[idxShift] = jet_BtagWeight_systematics_iter->second[idxJet];
	  }
	}
      }
    }
    readGenMatching(jets);
  }
  return jets;
}

void RecoJetReader::readGenMatching(std::vector<RecoJet>& jets) const
{
  if ( readGenMatching_ ) {
    assert(genLeptonReader_ && genHadTauReader_ && genJetReader_);
    size_t nJets = jets.size();
    std::vector<GenLepton> matched_genLeptons = genLeptonReader_->read();
    assert(matched_genLeptons.size() == nJets);
    std::vector<GenHadTau> matched_genHadTaus = genHadTauReader_->read();
    assert(matched_genHadTaus.size() == nJets);
    std::vector<GenJet> matched_genJets = genJetReader_->read();
    assert(matched_genJets.size() == nJets);
    for ( size_t idxJet = 0; idxJet < nJets; ++idxJet ) {
      RecoJet* jet = &jets[idxJet];
      const GenLepton& matched_genLepton = matched_genLeptons[idxJet];
      if ( matched_genLepton.isValid() ) jet->set_genLepton(new GenLepton(matched_genLepton), true);
      const GenHadTau& matched_genHadTau = matched_genHadTaus[idxJet];
      if ( matched_genHadTau.isValid() ) jet->set_genHadTau(new GenHadTau(matched_genHadTau), true);
      const GenJet& matched_genJet = matched_genJets[idxJet];
      if ( matched_genJet.isValid() ) jet->set_genJet(new GenJet(matched_genJet), true);
    }
  }
}
