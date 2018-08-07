#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter

#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet, GenLepton, GenHadTau, GenJet
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kBtag_*, kJet_*
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC)
  : RecoJetWriter(era, isMC, "Jet")
{}

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC,
                             const std::string & branchName_obj)
  : RecoJetWriter(era, isMC, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC,
                             const std::string & branchName_num,
                             const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , ptMassOption_(isMC_ ? kJet_central : kJet_central_nonNominal)
  , write_ptMass_systematics_(false)
  , write_BtagWeight_systematics_(false)
  , max_nJets_(256)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(nullptr)
  , genHadTauWriter_(nullptr)
  , genJetWriter_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_BtagCSV_(nullptr)
  , jet_BtagWeight_(nullptr)
  , jet_QGDiscr_(nullptr)
  , jet_jetId_(nullptr)
{
  switch(era_)
  {
    case kEra_2016: branchName_btag_ = "CSVV2"; break;
    case kEra_2017: branchName_btag_ = "DeepB"; break;
    case kEra_2018: throw cmsException(this) << "Implement me!";
    default: throw cmsException(this) << "Invalid era = " << era_;
  }
  assert(! branchName_btag_.empty());
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_obj_.data()), max_nJets_);
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_obj_.data()), max_nJets_);
  genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_obj_.data()), max_nJets_);
  setBranchNames();
}

RecoJetWriter::~RecoJetWriter()
{
  delete genLeptonWriter_;
  delete genHadTauWriter_;
  delete genJetWriter_;
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] jet_charge_;
  delete[] jet_BtagCSV_;
  delete[] jet_BtagWeight_;
  delete[] jet_QGDiscr_;
  delete[] jet_pullEta_;
  delete[] jet_pullPhi_;
  delete[] jet_pullMag_;
  delete[] jet_jetId_;
  for(auto & kv: jet_pt_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_mass_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_BtagWeights_systematics_)
  {
    delete[] kv.second;
  }
}

void
RecoJetWriter::setBranchNames()
{
  for(int idxShift = kJet_central_nonNominal; idxShift <= kJet_jerDown; ++idxShift)
  {
    branchNames_pt_systematics_[idxShift]   = getBranchName_jetPtMass(branchName_obj_, era_, idxShift, true);
    branchNames_mass_systematics_[idxShift] = getBranchName_jetPtMass(branchName_obj_, era_, idxShift, false);
  }
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_jetCharge_ = Form("%s_%s", branchName_obj_.data(), "jetCharge");
  branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), Form("btag%s", branchName_btag_.data()));
  branchName_QGDiscr_ = Form("%s_%s", branchName_obj_.data(), "qgl");
  branchName_pullEta_ = Form("%s_%s", branchName_obj_.data(), "pullEta");
  branchName_pullPhi_ = Form("%s_%s", branchName_obj_.data(), "pullPhi");
  branchName_pullMag_ = Form("%s_%s", branchName_obj_.data(), "pullMag");
  branchName_jetId_ = Form("%s_%s", branchName_obj_.data(), "jetId");
  branchName_BtagWeight_ = getBranchName_bTagWeight(branchName_obj_, era_, kBtag_central);
  for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
  {
    branchNames_BtagWeight_systematics_[idxShift] = getBranchName_bTagWeight(
      branchName_obj_, era_, idxShift
    );
  }
}

void
RecoJetWriter::setPtMass_central_or_shift(int central_or_shift)
{
  if(! isMC_ && central_or_shift != kJet_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Data has only non-nominal pt and mass"
    ;
  }
  ptMassOption_ = central_or_shift;
}

void
RecoJetWriter::write_ptMass_systematics(bool flag)
{
  if(! isMC_ && flag)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Cannot write jet pT & mass systematics in data"
    ;
  }
  write_ptMass_systematics_ = flag;
}

void
RecoJetWriter::write_BtagWeight_systematics(bool flag)
{
  if(! isMC_ && flag)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Cannot write jet b-tagging systematics in data"
    ;
  }
  write_BtagWeight_systematics_ = flag;
}

void
RecoJetWriter::setBranches(TTree * tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);

  BranchAddressInitializer bai(tree, max_nJets_, branchName_num_);
  bai.setBranch(nJets_, branchName_num_);
  bai.setBranch(jet_pt_systematics_[ptMassOption_], branchNames_pt_systematics_[ptMassOption_]);
  bai.setBranch(jet_mass_systematics_[ptMassOption_], branchNames_mass_systematics_[ptMassOption_]);
  if(write_ptMass_systematics_)
  {
    for(int idxShift = kJet_central_nonNominal; idxShift <= kJet_jerDown; ++idxShift)
    {
      if(idxShift == ptMassOption_)
      {
        continue; // do not overwrite the default branch
      }
      bai.setBranch(jet_pt_systematics_[idxShift], branchNames_pt_systematics_[idxShift]);
      bai.setBranch(jet_mass_systematics_[idxShift], branchNames_mass_systematics_[idxShift]);
    }
  }
  bai.setBranch(jet_eta_, branchName_eta_);
  bai.setBranch(jet_phi_, branchName_phi_);
  bai.setBranch(jet_charge_, branchName_jetCharge_);
  bai.setBranch(jet_BtagCSV_, branchName_BtagCSV_);
  bai.setBranch(jet_BtagWeight_, branchName_BtagWeight_);
  bai.setBranch(jet_pullEta_, branchName_pullEta_);
  bai.setBranch(jet_pullPhi_, branchName_pullPhi_);
  bai.setBranch(jet_pullMag_, branchName_pullMag_);
  bai.setBranch(jet_jetId_, branchName_jetId_);
  if(write_BtagWeight_systematics_)
  {
    for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
    {
      bai.setBranch(jet_BtagWeights_systematics_[idxShift], branchNames_BtagWeight_systematics_[idxShift]);
    }
  }
  bai.setBranch(jet_QGDiscr_, branchName_QGDiscr_);
}

void
RecoJetWriter::write(const std::vector<const RecoJet *> & jets)
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
    const RecoJet * jet = jets[idxJet];
    assert(jet);

    jet_pt_systematics_[ptMassOption_][idxJet]   = jet->pt_systematics_.at(ptMassOption_);
    jet_mass_systematics_[ptMassOption_][idxJet] = jet->mass_systematics_.at(ptMassOption_);

    if(write_ptMass_systematics_)
    {
      for(int idxShift = kJet_central_nonNominal; idxShift <= kJet_jerDown; ++idxShift)
      {
        if(idxShift == ptMassOption_)
        {
          continue; // do not overwrite the value (it doesn't do any harm, but still)
        }
        if(jet->pt_systematics_.count(idxShift))
        {
          jet_pt_systematics_[idxShift][idxJet] = jet->pt_systematics_.at(idxShift);
        }
        else
        {
          throw cmsException(this, __func__, __LINE__)
            << "Jet #" << idxJet << " is missing pT #" << idxShift
          ;
        }
        if(jet->mass_systematics_.count(idxShift))
        {
          jet_mass_systematics_[idxShift][idxJet] = jet->mass_systematics_.at(idxShift);
        }
        else
        {
          throw cmsException(this, __func__, __LINE__)
            << "Jet #" << idxJet << " is missing mass #" << idxShift
          ;
        }
      }
    }
    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
    jet_charge_[idxJet] = jet->charge();
    jet_BtagCSV_[idxJet] = jet->BtagCSV();
    jet_BtagWeight_[idxJet] = jet->BtagWeight();
    jet_pullEta_[idxJet] = jet->pullEta();
    jet_pullPhi_[idxJet] = jet->pullPhi();
    jet_pullMag_[idxJet] = jet->pullMag();
    jet_jetId_[idxJet] = jet->jetId();
    if(write_BtagWeight_systematics_)
    {
      for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
      {
        if(jet->BtagWeight_systematics_.count(idxShift))
        {
          jet_BtagWeights_systematics_[idxShift][idxJet] = jet->BtagWeight_systematics_.at(idxShift);
        }
        else
        {
          throw cmsException(this, __func__, __LINE__)
            << "Jet #" << idxJet << " is missing b-tagging weight #" << idxShift
          ;
        }
      }
    }
    jet_QGDiscr_[idxJet] = jet->QGDiscr();
  }
  writeGenMatching(jets);
}

void
RecoJetWriter::writeGenMatching(const std::vector<const RecoJet *> & jets)
{
  std::vector<GenParticle> matched_genLeptons;
  std::vector<GenParticle> matched_genHadTaus;
  std::vector<GenParticle> matched_genJets;

  for(unsigned idxJet = 0; idxJet < nJets_; ++idxJet)
  {
    const RecoJet * const jet = jets[idxJet];
    assert(jet);
    const GenLepton * matched_genLepton = jet->genLepton();
    if(matched_genLepton) matched_genLeptons.push_back(*reinterpret_cast<const GenParticle *>(matched_genLepton));
    else                  matched_genLeptons.push_back(dummyGenParticle_);

    const GenHadTau * matched_genHadTau = jet->genHadTau();
    if(matched_genHadTau) matched_genHadTaus.push_back(*reinterpret_cast<const GenParticle *>(matched_genHadTau));
    else                  matched_genHadTaus.push_back(dummyGenParticle_);

    const GenJet * matched_genJet = jet->genJet();
    if(matched_genJet) matched_genJets.push_back(*reinterpret_cast<const GenParticle *>(matched_genJet));
    else               matched_genJets.push_back(dummyGenParticle_);
  }
  genLeptonWriter_->write(matched_genLeptons);
  genHadTauWriter_->write(matched_genHadTaus);
  genJetWriter_->write(matched_genJets);
}
