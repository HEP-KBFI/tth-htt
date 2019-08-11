#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter

#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet, GenLepton, GenHadTau, GenJet
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kBtag_*, kJetMET_*
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
  , ptMassOption_(isMC_ ? kJetMET_central : kJetMET_central_nonNominal)
  , max_nJets_(256)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(nullptr)
  , genHadTauWriter_(nullptr)
  , genJetWriter_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_QGDiscr_(nullptr)
  , jet_jetId_(nullptr)
  , jet_puId_(nullptr)
  , jet_jetIdx_(nullptr)
  , jet_genMatchIdx_(nullptr)
{
  if(isMC_)
  {
    genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_obj_.data()), max_nJets_);
    genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_obj_.data()), max_nJets_);
    genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_obj_.data()), max_nJets_);
  }
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
  delete[] jet_QGDiscr_;
  delete[] jet_pullEta_;
  delete[] jet_pullPhi_;
  delete[] jet_pullMag_;
  delete[] jet_jetId_;
  delete[] jet_puId_;
  delete[] jet_jetIdx_;
  delete[] jet_genMatchIdx_;
  for(auto & kv: jet_pt_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_mass_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_BtagCSVs_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_BtagWeights_systematics_)
  {
    for(auto & kw: kv.second)
    {
      delete[] kw.second;
    }
  }
}

void
RecoJetWriter::setBranchNames()
{
  for(int idxShift = kJetMET_central_nonNominal; idxShift <= kJetMET_jerDown; ++idxShift)
  {
    if(! isValidJESsource(era_, idxShift))
    {
      continue;
    }
    branchNames_pt_systematics_[idxShift]   = getBranchName_jetMET(branchName_obj_, era_, idxShift, true);
    branchNames_mass_systematics_[idxShift] = getBranchName_jetMET(branchName_obj_, era_, idxShift, false);
  }
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_jetCharge_ = Form("%s_%s", branchName_obj_.data(), "jetCharge");
  for(const auto & kv: BtagWP_map.at(era_))
  {
    if(kv.first != Btag::kDeepJet)
    {
      continue;
    }
    std::string btagName;
    switch(kv.first)
    {
      case Btag::kDeepCSV: btagName = "DeepB";     break;
      case Btag::kDeepJet: btagName = "DeepFlavB"; break;
      case Btag::kCSVv2:   btagName = "CSVV2";     break;
    }
    assert(! btagName.empty());
    branchNames_btag_[kv.first] = Form("%s_btag%s", branchName_obj_.data(), btagName.data());
  }
  assert(! branchNames_btag_.empty());
  branchName_QGDiscr_ = Form("%s_%s", branchName_obj_.data(), "qgl");
  branchName_pullEta_ = Form("%s_%s", branchName_obj_.data(), "pullEta");
  branchName_pullPhi_ = Form("%s_%s", branchName_obj_.data(), "pullPhi");
  branchName_pullMag_ = Form("%s_%s", branchName_obj_.data(), "pullMag");
  branchName_jetId_ = Form("%s_%s", branchName_obj_.data(), "jetId");
  branchName_puId_ = Form("%s_%s", branchName_obj_.data(), "puId");
  branchName_jetIdx_ = Form("%s_%s", branchName_obj_.data(), "jetIdx");
  branchName_genMatchIdx_ = Form("%s_%s", branchName_obj_.data(), "genMatchIdx");
  for(auto & kv: BtagWP_map.at(era_))
  {
    if(kv.first != Btag::kDeepJet)
    {
      continue;
    }
    for(int idxShift = kBtag_central; idxShift <= kBtag_jesDown; ++idxShift)
    {
      branchNames_BtagWeight_systematics_[kv.first][idxShift] = getBranchName_bTagWeight(
        kv.first, branchName_obj_, idxShift
      );
    }
  }
}

void
RecoJetWriter::setPtMass_central_or_shift(int central_or_shift)
{
  if(! isMC_ && central_or_shift != kJetMET_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__) << "Data has only non-nominal pt and mass";
  }
  if(! isValidJESsource(era_, central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option for the era = " << era_ << ": " << central_or_shift;
  }
  ptMassOption_ = central_or_shift;
}

void
RecoJetWriter::setBranches(TTree * tree)
{
  if(isMC_)
  {
    genLeptonWriter_->setBranches(tree);
    genHadTauWriter_->setBranches(tree);
    genJetWriter_->setBranches(tree);
  }

  BranchAddressInitializer bai(tree, max_nJets_, branchName_num_);
  bai.setBranch(nJets_, branchName_num_);
  bai.setBranch(jet_pt_systematics_[ptMassOption_], branchNames_pt_systematics_[ptMassOption_]);
  bai.setBranch(jet_mass_systematics_[ptMassOption_], branchNames_mass_systematics_[ptMassOption_]);
  if(isMC_)
  {
    for(int idxShift = kJetMET_central_nonNominal; idxShift <= kJetMET_jerDown; ++idxShift)
    {
      if(! isValidJESsource(era_, idxShift))
      {
        continue;
      }
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
  bai.setBranch(jet_pullEta_, branchName_pullEta_);
  bai.setBranch(jet_pullPhi_, branchName_pullPhi_);
  bai.setBranch(jet_pullMag_, branchName_pullMag_);
  bai.setBranch(jet_jetId_, branchName_jetId_);
  bai.setBranch(jet_puId_, branchName_puId_);
  bai.setBranch(jet_jetIdx_, branchName_jetIdx_);
  if(isMC_)
  {
    bai.setBranch(jet_genMatchIdx_, branchName_genMatchIdx_);
  }
  for(const auto & kv: branchNames_btag_)
  {
    bai.setBranch(jet_BtagCSVs_[kv.first], kv.second);
  }
  if(isMC_)
  {
    for(const auto & kv: branchNames_BtagWeight_systematics_)
    {
      jet_BtagWeights_systematics_[kv.first] = {};
      for(int idxShift = kBtag_central; idxShift <= kBtag_jesDown; ++idxShift)
      {
        bai.setBranch(jet_BtagWeights_systematics_[kv.first][idxShift], branchNames_BtagWeight_systematics_[kv.first][idxShift]);
      }
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

    if(isMC_)
    {
      for(int idxShift = kJetMET_central_nonNominal; idxShift <= kJetMET_jerDown; ++idxShift)
      {
        if(! isValidJESsource(era_, idxShift))
        {
          continue;
        }
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
    for(const auto & kv: branchNames_btag_)
    {
      jet_BtagCSVs_[kv.first][idxJet] = jet->BtagCSVs_.at(kv.first);
    }
    jet_pullEta_[idxJet] = jet->pullEta();
    jet_pullPhi_[idxJet] = jet->pullPhi();
    jet_pullMag_[idxJet] = jet->pullMag();
    jet_jetId_[idxJet] = jet->jetId();
    jet_puId_[idxJet] = jet->puId();
    jet_jetIdx_[idxJet] = jet->idx();
    if(isMC_)
    {
      jet_genMatchIdx_[idxJet] = jet->genMatchIdx();
      for(const auto & kv: branchNames_BtagWeight_systematics_)
      {
        for(int idxShift = kBtag_central; idxShift <= kBtag_jesDown; ++idxShift)
        {
          if(jet->BtagWeight_systematics_.at(kv.first).count(idxShift))
          {
            jet_BtagWeights_systematics_[kv.first][idxShift][idxJet] = jet->BtagWeight_systematics_.at(kv.first).at(idxShift);
          }
          else
          {
            throw cmsException(this, __func__, __LINE__)
              << "Jet #" << idxJet << " is missing b-tagging weight #" << idxShift
              << " for b-tagging algorithm " << static_cast<int>(kv.first)
            ;
          }
        }
      }
    }
    jet_QGDiscr_[idxJet] = jet->QGDiscr();
  }
  if(isMC_)
  {
    writeGenMatching(jets);
  }
}

void
RecoJetWriter::writeGenMatching(const std::vector<const RecoJet *> & jets)
{
  assert(isMC_);
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
