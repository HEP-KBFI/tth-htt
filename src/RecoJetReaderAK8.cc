#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h" // RecoJetReaderAK8

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetReaderAK8.h" // RecoSubjetReaderAK8

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kBtag_*
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoJetReaderAK8::numInstances_;
std::map<std::string, RecoJetReaderAK8 *> RecoJetReaderAK8::instances_;

RecoJetReaderAK8::RecoJetReaderAK8(int era)
  : RecoJetReaderAK8(era, "FatJet", "SubJet")
{}

RecoJetReaderAK8::RecoJetReaderAK8(int era,
				     const std::string & branchName_jet, const std::string & branchName_subjet)
  : era_(era)
  , max_nJets_(32)
  , branchName_num_(Form("n%s", branchName_jet.data()))
  , branchName_obj_(branchName_jet)
  , subjetReader_(nullptr)
  , jet_pt_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_mass_(nullptr)
  , jet_msoftdrop_(nullptr)
  , subjet_idx1_(nullptr)
  , subjet_idx2_(nullptr)
  , jet_tau1_(nullptr)
  , jet_tau2_(nullptr)
  , jet_tau3_(nullptr)
  , jet_tau4_(nullptr)
  , jet_jetId_(nullptr)
{
  subjetReader_ = new RecoSubjetReaderAK8(era, branchName_subjet);
  setBranchNames();
}

RecoJetReaderAK8::~RecoJetReaderAK8()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    RecoJetReaderAK8 * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->subjetReader_;
    delete[] gInstance->jet_pt_;
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->jet_mass_;
    delete[] gInstance->jet_msoftdrop_;
    delete[] gInstance->subjet_idx1_;
    delete[] gInstance->subjet_idx2_;
    delete[] gInstance->jet_tau1_;
    delete[] gInstance->jet_tau2_;
    delete[] gInstance->jet_tau3_;
    delete[] gInstance->jet_tau4_;
    delete[] gInstance->jet_jetId_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoJetReaderAK8::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_msoftdrop_ = Form("%s_%s", branchName_obj_.data(), "msoftdrop");
    branchName_subJetIdx1_ = Form("%s_%s", branchName_obj_.data(), "subJetIdx1");
    branchName_subJetIdx2_ = Form("%s_%s", branchName_obj_.data(), "subJetIdx2");
    branchName_tau1_ = Form("%s_%s", branchName_obj_.data(), "tau1");
    branchName_tau2_ = Form("%s_%s", branchName_obj_.data(), "tau2");
    branchName_tau3_ = Form("%s_%s", branchName_obj_.data(), "tau3");
    branchName_tau4_ = Form("%s_%s", branchName_obj_.data(), "tau4");
    branchName_jetId_ = Form("%s_%s", branchName_obj_.data(), "jetId");
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
        << " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void
RecoJetReaderAK8::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nJets_);
    subjetReader_->setBranchAddresses(tree);
    bai.setBranchAddress(nJets_, branchName_num_);
    bai.setBranchAddress(jet_pt_, branchName_pt_);
    bai.setBranchAddress(jet_eta_, branchName_eta_);
    bai.setBranchAddress(jet_phi_, branchName_phi_);
    bai.setBranchAddress(jet_mass_, branchName_mass_);
    bai.setBranchAddress(jet_msoftdrop_, branchName_msoftdrop_);
    bai.setBranchAddress(subjet_idx1_, branchName_subJetIdx1_);
    bai.setBranchAddress(subjet_idx2_, branchName_subJetIdx2_);
    bai.setBranchAddress(jet_tau1_, branchName_tau1_);
    bai.setBranchAddress(jet_tau2_, branchName_tau2_);
    bai.setBranchAddress(jet_tau3_, branchName_tau3_);
    bai.setBranchAddress(jet_tau4_, branchName_tau4_);
    bai.setBranchAddress(jet_jetId_, branchName_jetId_);
  }
}

namespace
{
  const RecoSubjetAK8* getSubjet(const std::vector<RecoSubjetAK8>& subjets, int idx)
  {
    if ( idx == -1 ) return nullptr;
    else if (idx >= 0 && idx < (int)subjets.size() ) return &subjets[idx];
    else throw cmsException("<getSubjet>:")
      << "Invalid subjet index = " << idx << ", given number of subjets = " << subjets.size() << " !!\n";
  }
}

std::vector<RecoJetAK8>
RecoJetReaderAK8::read() const
{
  const RecoJetReaderAK8 * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  std::vector<RecoJetAK8> jets;
  const UInt_t nJets = gInstance->nJets_;
  if(nJets > max_nJets_)
  {
    throw cmsException(this)
      << "Number of jets stored in Ntuple = " << nJets << ", exceeds max_nJets = " << max_nJets_ << " !!\n";
  }

  if(nJets > 0)
  {
    jets.reserve(nJets);
    std::vector<RecoSubjetAK8> subjets = subjetReader_->read();
    for(UInt_t idxJet = 0; idxJet < nJets; ++idxJet)
    {
      const RecoSubjetAK8* subJet1 = getSubjet(subjets, gInstance->subjet_idx1_[idxJet]);
      const RecoSubjetAK8* subJet2 = getSubjet(subjets, gInstance->subjet_idx2_[idxJet]);
      jets.push_back({
        {
          gInstance->jet_pt_[idxJet],
          gInstance->jet_eta_[idxJet],
          gInstance->jet_phi_[idxJet],
          gInstance->jet_mass_[idxJet]
        },
	gInstance->jet_msoftdrop_[idxJet],
        ( subJet1 != nullptr ) ? new RecoSubjetAK8(*subJet1) : nullptr,
	( subJet2 != nullptr ) ? new RecoSubjetAK8(*subJet2) : nullptr,
	gInstance->jet_tau1_[idxJet],
	gInstance->jet_tau2_[idxJet],
	gInstance->jet_tau3_[idxJet],
	gInstance->jet_tau4_[idxJet],
	gInstance->jet_jetId_[idxJet],  
        static_cast<Int_t>(idxJet)
      });
    } // idxJet
  } // nJets > 0
  return jets;
}
