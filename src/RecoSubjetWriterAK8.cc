#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetWriterAK8.h" // RecoSubjetWriterAK8

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK8.h" // RecoSubjetAK8
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoSubjetWriterAK8::RecoSubjetWriterAK8(int era)
  : RecoSubjetWriterAK8(era, "SubJet")
{}

RecoSubjetWriterAK8::RecoSubjetWriterAK8(int era,
                                         const std::string & branchName_obj)
  : RecoSubjetWriterAK8(era, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoSubjetWriterAK8::RecoSubjetWriterAK8(int era,
                                         const std::string & branchName_num,
                                         const std::string & branchName_obj)
  : era_(era)
  , btag_(Btag::kDeepCSV) // maybe write DeepJet?
  , max_nJets_(88)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , nJets_(0)
  , jet_pt_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_mass_(nullptr)
  , jet_BtagCSV_(nullptr)
{
  switch(btag_)
  {
    case Btag::kDeepCSV: branchName_btag_ = "DeepB";     break;
    case Btag::kDeepJet: branchName_btag_ = "DeepFlavB"; break;
    case Btag::kCSVv2:   branchName_btag_ = "CSVV2";     break;
  }
  assert(! branchName_btag_.empty());
  setBranchNames();
}

RecoSubjetWriterAK8::~RecoSubjetWriterAK8()
{
  delete[] jet_pt_;
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] jet_mass_;
  delete[] jet_BtagCSV_;
}

void
RecoSubjetWriterAK8::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), Form("btag%s", branchName_btag_.data()));
}

void
RecoSubjetWriterAK8::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree, max_nJets_, branchName_num_);
  bai.setBranch(nJets_, branchName_num_);
  bai.setBranch(jet_pt_, branchName_pt_);
  bai.setBranch(jet_eta_, branchName_eta_);
  bai.setBranch(jet_phi_, branchName_phi_);
  bai.setBranch(jet_mass_, branchName_mass_);
  bai.setBranch(jet_BtagCSV_, branchName_BtagCSV_);
}

void
RecoSubjetWriterAK8::write(const std::vector<const RecoSubjetAK8 *> & jets)
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
    const RecoSubjetAK8 * jet = jets[idxJet];
    assert(jet);

    jet_pt_[idxJet] = jet->pt();
    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
    jet_mass_[idxJet] = jet->mass();
    jet_BtagCSV_[idxJet] = jet->BtagCSV();
  }
}
