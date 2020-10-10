#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kLoose, kFakeable, kTight, TauID::
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

ObjectMultiplicityReader::ObjectMultiplicityReader()
  : ObjectMultiplicityReader(nullptr)
{}

ObjectMultiplicityReader::ObjectMultiplicityReader(ObjectMultiplicity * objectMultiplicity)
  : objectMultiplicity_(objectMultiplicity)
  , branchName_nMuon_("Muon")
  , branchName_nElectron_("Electron")
  , branchName_nHadTau_("Tau")
{}

ObjectMultiplicityReader::~ObjectMultiplicityReader()
{}

std::vector<std::string>
ObjectMultiplicityReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  for(int selection = kLoose; selection <= kTight; ++selection)
  {
    std::string selection_str;
    switch(selection)
    {
      case kLoose:    selection_str = "Loose";    break;
      case kFakeable: selection_str = "Fakeable"; break;
      case kTight:    selection_str = "Tight";    break;
      default: throw cmsException(this, __func__, __LINE__) << "Invalid level: " << selection;
    }
    assert(! selection_str.empty());

    if(! objectMultiplicity_->nRecoMuon_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "Level missing for muons: " << selection;
    }
    if(! objectMultiplicity_->nRecoElectron_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "Level missing for electrons: " << selection;
    }
    bai.setBranchAddress(
      objectMultiplicity_->nRecoMuon_[selection], Form("n%s%s", branchName_nMuon_.data(), selection_str.data())
    );
    bai.setBranchAddress(
      objectMultiplicity_->nRecoElectron_[selection], Form("n%s%s", branchName_nElectron_.data(), selection_str.data())
    );
  }
  for(const auto & kv: TauID_PyMap)
  {
    const int max_level = TauID_levels.at(kv.second);
    const std::vector<std::string> & level_strs = TauID_level_strings.at(max_level);
    for(int level = 1; level <= max_level; ++level)
    {
      bai.setBranchAddress(
        objectMultiplicity_->nRecoHadTau_[kv.second][level],
        Form("n%s%s%s", branchName_nHadTau_.data(), kv.first.data(), level_strs.at(level - 1).data())
      );
    }
  }
  return bai.getBoundBranchNames();
}

void
ObjectMultiplicityReader::setObjectMultiplicity(ObjectMultiplicity * objectMultiplicity)
{
  objectMultiplicity_ = objectMultiplicity;
}
