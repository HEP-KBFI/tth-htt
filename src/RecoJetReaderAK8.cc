#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK8.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetReaderAK8.h"      // RecoSubjetReaderAK8
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"             // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"     // kBtag_*
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"         // kFatJet_*

std::map<std::string, int> RecoJetReaderAK8::numInstances_;
std::map<std::string, RecoJetReaderAK8 *> RecoJetReaderAK8::instances_;

RecoJetReaderAK8::RecoJetReaderAK8(Era era,
                                   bool isMC)
  : RecoJetReaderAK8(era, isMC, "FatJet", "SubJet")
{}

RecoJetReaderAK8::RecoJetReaderAK8(Era era,
                                   bool isMC,
                                   const std::string & branchName_jet,
                                   const std::string & branchName_subjet)
  : era_(era)
  , isMC_(false) // TODO
  , max_nJets_(32)
  , branchName_num_(Form("n%s", branchName_jet.data()))
  , branchName_obj_(branchName_jet)
  , subjetReader_(nullptr)
  , sysOption_central_(isMC_ ? kFatJet_central : kFatJet_central_nonNominal)
  , sysOption_(sysOption_central_)
  , readSys_(false)
  , pt_str_("pt")
  , mass_str_("mass")
  , msoftdrop_str_("msoftdrop")
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
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->subjet_idx1_;
    delete[] gInstance->subjet_idx2_;
    delete[] gInstance->jet_tau1_;
    delete[] gInstance->jet_tau2_;
    delete[] gInstance->jet_tau3_;
    delete[] gInstance->jet_tau4_;
    delete[] gInstance->jet_jetId_;
    for(auto & kv: gInstance->jet_pt_systematics_)
    {
      delete[] kv.second;
    }
    for(auto & kv: gInstance->jet_mass_systematics_)
    {
      delete[] kv.second;
    }
    for(auto & kv: gInstance->jet_msoftdrop_systematics_)
    {
      delete[] kv.second;
    }
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoJetReaderAK8::set_central_or_shift(int central_or_shift)
{
#if 0
  if(! isMC_ && central_or_shift != kFatJet_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__) << "Data has only non-nominal attributes";
  }
  sysOption_ = central_or_shift;
  if(! readSys_)
  {
    read_sys(sysOption_ != sysOption_central_);
  }
#endif
}

void
RecoJetReaderAK8::read_sys(bool flag)
{
  //readSys_ = flag;
}

void
RecoJetReaderAK8::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
    {
      if(isValidFatJetAttribute(idxShift, pt_str_))
      {
        branchNames_pt_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, pt_str_, idxShift);
      }
      if(isValidFatJetAttribute(idxShift, mass_str_))
      {
        branchNames_mass_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, mass_str_, idxShift);
      }
      if(isValidFatJetAttribute(idxShift, msoftdrop_str_))
      {
        branchNames_msoftdrop_systematics_[idxShift] = getBranchName_fatJet(branchName_obj_, msoftdrop_str_, idxShift);
      }
    }
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
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
    bai.setBranchAddress(jet_pt_systematics_[sysOption_],        branchNames_pt_systematics_[sysOption_]);
    bai.setBranchAddress(jet_mass_systematics_[sysOption_],      branchNames_mass_systematics_[sysOption_]);
    bai.setBranchAddress(jet_msoftdrop_systematics_[sysOption_], branchNames_msoftdrop_systematics_[sysOption_]);
    if(isMC_ && readSys_)
    {
      for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
      {
        if(idxShift == sysOption_)
        {
          continue; // do not bind the same branch twice
        }
        if(branchNames_pt_systematics_.count(idxShift))
        {
          bai.setBranchAddress(jet_pt_systematics_[idxShift], branchNames_pt_systematics_[idxShift]);
        }
        if(branchNames_mass_systematics_.count(idxShift))
        {
          bai.setBranchAddress(jet_mass_systematics_[idxShift], branchNames_mass_systematics_[idxShift]);
        }
        if(branchNames_msoftdrop_systematics_.count(idxShift))
        {
          bai.setBranchAddress(jet_msoftdrop_systematics_[idxShift], branchNames_msoftdrop_systematics_[idxShift]);
        }
      }
    }
    assert(jet_pt_systematics_.count(sysOption_central_));
    assert(jet_mass_systematics_.count(sysOption_central_));
    assert(jet_msoftdrop_systematics_.count(sysOption_central_));
    bai.setBranchAddress(jet_eta_, branchName_eta_);
    bai.setBranchAddress(jet_phi_, branchName_phi_);
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
  const RecoSubjetAK8 *
  getSubjet(const std::vector<RecoSubjetAK8> & subjets,
            int idx)
  {
    if(idx == -1)
    {
      return nullptr;
    }
    else if(idx >= 0 && idx < (int)subjets.size())
    {
      return &subjets[idx];
    }
    else
    {
      throw cmsException(__func__, __LINE__)
        << "Invalid subjet index = " << idx << ", given number of subjets = " << subjets.size() << " !!\n";
    }
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
      const RecoSubjetAK8 * subJet1 = subjets.size() > 0 ? getSubjet(subjets, gInstance->subjet_idx1_[idxJet]) : nullptr;
      const RecoSubjetAK8 * subJet2 = subjets.size() > 1 ? getSubjet(subjets, gInstance->subjet_idx2_[idxJet]) : nullptr;
      const int jet_pt_sys        = gInstance->jet_pt_systematics_.count(sysOption_)        ? sysOption_ : sysOption_central_;
      const int jet_mass_sys      = gInstance->jet_mass_systematics_.count(sysOption_)      ? sysOption_ : sysOption_central_;
      const int jet_msoftdrop_sys = gInstance->jet_msoftdrop_systematics_.count(sysOption_) ? sysOption_ : sysOption_central_;
      jets.push_back({
        {
          gInstance->jet_pt_systematics_.at(jet_pt_sys)[idxJet],
          gInstance->jet_eta_[idxJet],
          gInstance->jet_phi_[idxJet],
          gInstance->jet_mass_systematics_.at(jet_mass_sys)[idxJet],
        },
        gInstance->jet_msoftdrop_systematics_.at(jet_msoftdrop_sys)[idxJet],
        subJet1 ? new RecoSubjetAK8(*subJet1) : nullptr,
        subJet2 ? new RecoSubjetAK8(*subJet2) : nullptr,
        gInstance->jet_tau1_[idxJet],
        gInstance->jet_tau2_[idxJet],
        gInstance->jet_tau3_[idxJet],
        gInstance->jet_tau4_[idxJet],
        gInstance->jet_jetId_[idxJet],
        static_cast<Int_t>(idxJet),
        sysOption_,
      });

      RecoJetAK8 & jet = jets.back();
      if(isMC_ && readSys_)
      {
        for(int idxShift = kFatJet_central_nonNominal; idxShift <= kFatJet_jmrDown; ++idxShift)
        {
          // we want to save all pT-s and masses that have been shifted by systematic uncertainties to the maps,
          // including the central nominal and central non-nominal values; crucial for RecoJetWriter
          const int jet_pt_sys_local        = gInstance->jet_pt_systematics_.count(idxShift)        ? idxShift : sysOption_central_;
          const int jet_mass_sys_local      = gInstance->jet_mass_systematics_.count(idxShift)      ? idxShift : sysOption_central_;
          const int jet_msoftdrop_sys_local = gInstance->jet_msoftdrop_systematics_.count(idxShift) ? idxShift : sysOption_central_;
          jet.pt_systematics_[idxShift]        = gInstance->jet_pt_systematics_.at(jet_pt_sys_local)[idxJet];
          jet.mass_systematics_[idxShift]      = gInstance->jet_mass_systematics_.at(jet_mass_sys_local)[idxJet];
          jet.msoftdrop_systematics_[idxShift] = gInstance->jet_msoftdrop_systematics_.at(jet_msoftdrop_sys_local)[idxJet];
        } // idxShift
      }
      else
      {
        // fill the maps with only the central values (either nominal or non-nominal if data)
        jet.pt_systematics_[sysOption_]   = gInstance->jet_pt_systematics_.at(jet_pt_sys)[idxJet];
        jet.mass_systematics_[sysOption_] = gInstance->jet_mass_systematics_.at(jet_mass_sys)[idxJet];
        jet.msoftdrop_systematics_[sysOption_] = gInstance->jet_msoftdrop_systematics_.at(jet_msoftdrop_sys)[idxJet];
      } // isMC_
    } // idxJet
  } // nJets > 0
  return jets;
}
