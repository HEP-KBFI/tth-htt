#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kLoose, kFakeable, kTight, TauID::
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

ObjectMultiplicityWriter::ObjectMultiplicityWriter(bool verbose)
  : verbose_(verbose)
  , branchName_nMuon_("Muon")
  , branchName_nElectron_("Electron")
  , branchName_nHadTau_("Tau")
{}

void
ObjectMultiplicityWriter::setBranches(TTree * tree)
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

    if(! objectMultiplicity_.nRecoMuon_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "Level missing for muons: " << selection;
    }
    if(! objectMultiplicity_.nRecoElectron_.count(selection))
    {
      throw cmsException(this, __func__, __LINE__) << "Level missing for electrons: " << selection;
    }
    const std::string branchName_nMuon     = Form("n%s%s", branchName_nMuon_.data(),     selection_str.data());
    const std::string branchName_nElectron = Form("n%s%s", branchName_nElectron_.data(), selection_str.data());
    bai.setBranch(objectMultiplicity_.nRecoMuon_[selection],     branchName_nMuon);
    bai.setBranch(objectMultiplicity_.nRecoElectron_[selection], branchName_nElectron);
    if(verbose_)
    {
      std::cout << "adding branch: " << branchName_nMuon     << " (type = I)\n";
      std::cout << "adding branch: " << branchName_nElectron << " (type = I)\n";
    }
  }
  for(const auto & kv: TauID_PyMap)
  {
    const int max_level = TauID_levels.at(kv.second);
    const std::vector<std::string> & level_strs = TauID_level_strings.at(max_level);
    for(int level = 1; level <= max_level; ++level)
    {
      const std::string branchName_nHadTau = Form(
        "n%s%s%s", branchName_nHadTau_.data(), kv.first.data(), level_strs.at(level - 1).data()
      );
      bai.setBranch(objectMultiplicity_.nRecoHadTau_[kv.second][level], branchName_nHadTau);
      if(verbose_)
      {
        std::cout << "adding branch: " << branchName_nHadTau << " (type = I)\n";
      }
    }
  }
}

void
ObjectMultiplicityWriter::write(const ObjectMultiplicity & objectMultiplicity)
{
  objectMultiplicity_ = objectMultiplicity;
}
