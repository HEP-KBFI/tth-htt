#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriterAK8.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetWriterAK8.h"      // RecoSubjetWriterAK8
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"               // RecoJetAK8
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"         // kFatJet_*

RecoJetWriterAK8::RecoJetWriterAK8(Era era,
                                   bool isMC)
  : RecoJetWriterAK8(era, isMC, "FatJet", "SubJet")
{}

RecoJetWriterAK8::RecoJetWriterAK8(Era era,
                                   bool isMC,
                                   const std::string & branchName_jet,
                                   const std::string & branchName_subjet)  
  : RecoJetWriterAK8(era, isMC, Form("n%s", branchName_jet.data()), branchName_jet, Form("n%s", branchName_subjet.data()), branchName_subjet)
{}

RecoJetWriterAK8::RecoJetWriterAK8(Era era,
                                   bool isMC,
                                   const std::string & branchName_num_jets,
                                   const std::string & branchName_jet,
                                   const std::string & branchName_num_subjets,
                                   const std::string & branchName_subjet)
  : era_(era)
  , isMC_(isMC)
  , sysOption_central_(isMC_ ? kJetMET_central : kJetMET_central_nonNominal)
  , sysOption_(sysOption_central_)
  , ignoreSys_(isMC_ ? kFatJetJMS + kFatJetJMR + kFatJetPUPPI : kFatJetNone)
  , max_nJets_(32)
  , branchName_num_(branchName_num_jets)
  , branchName_obj_(branchName_jet)
  , subjetWriter_(nullptr)
  , pt_str_("pt")
  , mass_str_("mass")
  , msoftdrop_str_("msoftdrop")
  , nJets_(0)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
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
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] subjet_idx1_;
  delete[] subjet_idx2_;
  delete[] jet_tau1_;
  delete[] jet_tau2_;
  delete[] jet_tau3_;
  delete[] jet_tau4_;
  delete[] jet_jetId_;
  for(auto & kv: jet_pt_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_mass_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_msoftdrop_systematics_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_mass_corr_)
  {
    delete[] kv.second;
  }
  for(auto & kv: jet_sd_corr_)
  {
    delete[] kv.second;
  }
}

void
RecoJetWriterAK8::set_central_or_shift(int central_or_shift)
{
  if(! isMC_ && central_or_shift != kFatJet_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__) << "Data has only non-nominal attributes";
  }
  if(! isValidJESsource(era_, central_or_shift, true))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option for the era = " << static_cast<int>(era_) << ": " << central_or_shift;
  }
  if(((ignoreSys_ & kFatJetJMS) && (central_or_shift == kFatJet_jmsUp || central_or_shift == kFatJet_jmsDown)) ||
     ((ignoreSys_ & kFatJetJMR) && (central_or_shift == kFatJet_jmrUp || central_or_shift == kFatJet_jmrDown))  )
  {
    throw cmsException(this, __func__, __LINE__)
      << "Requested systematics " << central_or_shift << " while at the same time ignoring its corrections: " << ignoreSys_
    ;
  }
  sysOption_ = central_or_shift;
}

void
RecoJetWriterAK8::ignoreSys(int flag)
{
  if(((flag & kFatJetJMS) && (sysOption_ == kFatJet_jmsUp || sysOption_ == kFatJet_jmsDown)) ||
     ((flag & kFatJetJMR) && (sysOption_ == kFatJet_jmrUp || sysOption_ == kFatJet_jmrDown))  )
  {
    throw cmsException(this, __func__, __LINE__)
      << "Requested to ignore corrections (" << flag << ") while at the same time enabling its systematics: " << sysOption_
    ;
  }
  ignoreSys_ = flag;
}

void
RecoJetWriterAK8::setBranchNames()
{
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_subJetIdx1_ = Form("%s_%s", branchName_obj_.data(), "subJetIdx1");
  branchName_subJetIdx2_ = Form("%s_%s", branchName_obj_.data(), "subJetIdx2");
  branchName_tau1_ = Form("%s_%s", branchName_obj_.data(), "tau1");
  branchName_tau2_ = Form("%s_%s", branchName_obj_.data(), "tau2");
  branchName_tau3_ = Form("%s_%s", branchName_obj_.data(), "tau3");
  branchName_tau4_ = Form("%s_%s", branchName_obj_.data(), "tau4");
  branchName_jetId_ = Form("%s_%s", branchName_obj_.data(), "jetId");

  for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
  {
    if(! isValidJESsource(era_, idxShift, true))
    {
      continue;
    }
    if(isValidFatJetAttribute(idxShift, pt_str_))
    {
      branchNames_pt_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, era_, pt_str_, idxShift);
    }
    if(isValidFatJetAttribute(idxShift, mass_str_))
    {
      branchNames_mass_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, era_, mass_str_, idxShift);
    }
    if(isValidFatJetAttribute(idxShift, msoftdrop_str_))
    {
      branchNames_msoftdrop_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, era_, msoftdrop_str_, idxShift);
    }
  }

  for(int idxShift = 0; idxShift < 3; ++idxShift)
  {
    const int idxShift_pow = 1 << idxShift;
    const std::string suffix = getCorrectionString(idxShift_pow);
    branchNames_sd_corr_[idxShift_pow] = Form("%s_%s_corr_%s", branchName_obj_.data(), msoftdrop_str_.data(), suffix.data());

    if(! (idxShift_pow & kFatJetPUPPI))
    {
      branchNames_mass_corr_[idxShift_pow] = Form("%s_corr_%s", branchName_obj_.data(), suffix.data());
    }
  }
}

void
RecoJetWriterAK8::setBranches(TTree * tree)
{
  subjetWriter_->setBranches(tree);
  BranchAddressInitializer bai(tree, max_nJets_, branchName_num_);
  bai.setBranch(nJets_, branchName_num_);

  assert(branchNames_pt_systematics_.count(sysOption_central_));
  assert(branchNames_mass_systematics_.count(sysOption_central_));
  assert(branchNames_msoftdrop_systematics_.count(sysOption_central_));
  const int jet_pt_sys = branchNames_pt_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
  const int jet_mass_sys = branchNames_mass_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
  const int jet_msoftdrop_sys = branchNames_msoftdrop_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
  bai.setBranch(jet_pt_systematics_[sysOption_], branchNames_pt_systematics_[jet_pt_sys]);
  bai.setBranch(jet_mass_systematics_[sysOption_], branchNames_mass_systematics_[jet_mass_sys]);
  bai.setBranch(jet_msoftdrop_systematics_[sysOption_], branchNames_msoftdrop_systematics_[jet_msoftdrop_sys]);

  if(isMC_)
  {
    for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
    {
      if(! isValidJESsource(era_, idxShift, true))
      {
        continue;
      }
      if(idxShift == sysOption_)
      {
        continue; // do not overwrite the default branch
      }
      if(branchNames_pt_systematics_.count(idxShift) && ! jet_pt_systematics_.count(idxShift))
      {
        bai.setBranch(jet_pt_systematics_[idxShift], branchNames_pt_systematics_.at(idxShift));
      }
      if(branchNames_mass_systematics_.count(idxShift) && ! jet_mass_systematics_.count(idxShift))
      {
        bai.setBranch(jet_mass_systematics_[idxShift], branchNames_mass_systematics_.at(idxShift));
      }
      if(branchNames_msoftdrop_systematics_.count(idxShift) && ! jet_msoftdrop_systematics_.count(idxShift))
      {
        bai.setBranch(jet_msoftdrop_systematics_[idxShift], branchNames_msoftdrop_systematics_.at(idxShift));
      }
    }

    for(int idxShift = 0; idxShift < 3; ++idxShift)
    {
      const int idxShift_pow = 1 << idxShift;
      if(branchNames_sd_corr_.count(idxShift_pow))
      {
        bai.setBranchAddress(jet_sd_corr_[idxShift_pow], branchNames_sd_corr_.at(idxShift_pow));
      }
      if(branchNames_mass_corr_.count(idxShift_pow))
      {
        bai.setBranchAddress(jet_mass_corr_[idxShift_pow], branchNames_mass_corr_.at(idxShift_pow));
      }
    }
  }

  bai.setBranch(jet_eta_, branchName_eta_);
  bai.setBranch(jet_phi_, branchName_phi_);
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

    const int jet_pt_sys = jet->pt_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
    const int jet_mass_sys = jet->mass_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
    const int jet_msoftdrop_sys = jet->msoftdrop_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
    jet_pt_systematics_[sysOption_][idxJet]   = jet->pt_systematics_.at(jet_pt_sys);
    jet_mass_systematics_[sysOption_][idxJet] = updateWithCorrections(
      jet->mass_systematics_.at(jet_mass_sys), ignoreSys_, jet->mass_corrections_, false
    );
    jet_msoftdrop_systematics_[sysOption_][idxJet] = updateWithCorrections(
      jet->msoftdrop_systematics_.at(jet_msoftdrop_sys), ignoreSys_, jet->sd_corrections_, false
    );

    if(isMC_)
    {
      for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
      {
        if(! isValidJESsource(era_, idxShift, true))
        {
          continue;
        }
        if(idxShift == sysOption_)
        {
          continue; // do not overwrite the value
        }
        if(jet_pt_systematics_.count(idxShift))
        {
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
        }
        if(jet_mass_systematics_.count(idxShift))
        {
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
        if(jet_msoftdrop_systematics_.count(idxShift))
        {
          if(jet->msoftdrop_systematics_.count(idxShift))
          {
            jet_msoftdrop_systematics_[idxShift][idxJet] = jet->msoftdrop_systematics_.at(idxShift);
          }
          else
          {
            throw cmsException(this, __func__, __LINE__)
              << "Jet #" << idxJet << " is missing msoftdrop #" << idxShift
            ;
          }
        }
      }
      for(int idxShift = 0; idxShift < 3; ++idxShift)
      {
        const int idxShift_pow = 1 << idxShift;
        if(jet_mass_corr_.count(idxShift_pow))
        {
          jet_mass_corr_[idxShift_pow][idxJet] = jet->mass_corrections_.at(idxShift_pow);
        }
        if(jet_sd_corr_.count(idxShift_pow))
        {
          jet_sd_corr_[idxShift_pow][idxJet] = jet->sd_corrections_.at(idxShift_pow);
        }
      }
    }

    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
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
