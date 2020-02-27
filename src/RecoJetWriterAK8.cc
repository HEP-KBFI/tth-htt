#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriterAK8.h" // RecoJetWriterAK8

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetWriterAK8.h" // RecoSubjetWriterAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

RecoJetWriterAK8::RecoJetWriterAK8(int era)
  : RecoJetWriterAK8(era, "FatJet", "SubJet")
{}

RecoJetWriterAK8::RecoJetWriterAK8(int era,
                                   const std::string & branchName_jet,
                                   const std::string & branchName_subjet)  
  : RecoJetWriterAK8(era, Form("n%s", branchName_jet.data()), branchName_jet, Form("n%s", branchName_subjet.data()), branchName_subjet)
{}

RecoJetWriterAK8::RecoJetWriterAK8(int era,
                                   const std::string & branchName_num_jets,
				   const std::string & branchName_jet,
				   const std::string & branchName_num_subjets,
                                   const std::string & branchName_subjet)
  : era_(era)
  , max_nJets_(32)
  , branchName_num_(branchName_num_jets)
  , branchName_obj_(branchName_jet)
  , subjetWriter_(nullptr)
  , nJets_(0)
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
  subjetWriter_ = new RecoSubjetWriterAK8(era, branchName_num_subjets, branchName_subjet);
  setBranchNames();
}

RecoJetWriterAK8::~RecoJetWriterAK8()
{
  delete subjetWriter_;
  delete[] jet_pt_;
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] jet_mass_;
  delete[] jet_msoftdrop_;
  delete[] subjet_idx1_;
  delete[] subjet_idx2_;
  delete[] jet_tau1_;
  delete[] jet_tau2_;
  delete[] jet_tau3_;
  delete[] jet_tau4_;
  delete[] jet_jetId_;
}

void
RecoJetWriterAK8::setBranchNames()
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
}

void
RecoJetWriterAK8::setBranches(TTree * tree)
{
  subjetWriter_->setBranches(tree);
  BranchAddressInitializer bai(tree, max_nJets_, branchName_num_);
  bai.setBranch(nJets_, branchName_num_);
  bai.setBranch(jet_pt_, branchName_pt_);
  bai.setBranch(jet_eta_, branchName_eta_);
  bai.setBranch(jet_phi_, branchName_phi_);
  bai.setBranch(jet_mass_, branchName_mass_);
  bai.setBranch(jet_msoftdrop_, branchName_msoftdrop_);
  bai.setBranch(subjet_idx1_, branchName_subJetIdx1_);
  bai.setBranch(subjet_idx2_, branchName_subJetIdx2_);
  bai.setBranch(jet_tau1_, branchName_tau1_);
  bai.setBranch(jet_tau2_, branchName_tau2_);
  bai.setBranch(jet_tau3_, branchName_tau3_);
  bai.setBranch(jet_tau4_, branchName_tau4_);
  bai.setBranch(jet_jetId_, branchName_jetId_);
}

void
RecoJetWriterAK8::write(const std::vector<const RecoJetAK8 *> & jets)
{
  nJets_ = jets.size();
  if(nJets_ > max_nJets_)
  {
    std::cout << "Warning: limiting the number of jets to be written from " << nJets_
              << " jets to " << max_nJets_ << " jets\n"
              << "Dropping the following jets:\n"
    ;
    nJets_ = max_nJets_;
    for(unsigned idxJet = nJets_ + 1; idxJet < jets.size(); ++idxJet)
    {
      std::cout << '#' << idxJet << " jet: " << *(jets[idxJet]) << '\n';
    }
    std::cout << "But keeping these jets:\n";
    for(unsigned idxJet = 0; idxJet < nJets_; ++idxJet)
    {
      std::cout << '#' << idxJet << " jet: " << *(jets[idxJet]) << '\n';
    }
  }
  for(UInt_t idxJet = 0; idxJet < nJets_; ++idxJet)
  {
    const RecoJetAK8 * jet = jets[idxJet];
    assert(jet);

    jet_pt_[idxJet] = jet->pt();
    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
    jet_mass_[idxJet] = jet->mass();
    jet_msoftdrop_[idxJet] = jet->msoftdrop();
    subjet_idx1_[idxJet] = -1;
    subjet_idx2_[idxJet] = -1;
    jet_tau1_[idxJet] = jet->tau1();
    jet_tau2_[idxJet] = jet->tau2();
    jet_tau3_[idxJet] = jet->tau3();
    jet_tau4_[idxJet] = jet->tau4();
    jet_jetId_[idxJet] = jet->jetId();
  }
  writeSubjets(jets);
}

void
RecoJetWriterAK8::writeSubjets(const std::vector<const RecoJetAK8 *> & jets)
{
  std::vector<const RecoSubjetAK8 *> subjets;

  for(unsigned idxJet = 0; idxJet < nJets_; ++idxJet)
  {
    const RecoJetAK8 * jet = jets[idxJet];
    assert(jet);
    if ( jet->subJet1() ) 
    { 
      subjets.push_back(jet->subJet1());
      subjet_idx1_[idxJet] = subjets.size() - 1;
    }
    if ( jet->subJet2() ) 
    {
      subjets.push_back(jet->subJet2());
      subjet_idx2_[idxJet] = subjets.size() - 1;
    }
  }
  subjetWriter_->write(subjets);
}

