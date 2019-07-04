#include "tthAnalysis/HiggsToTauTau/interface/SyncNtupleManagerBase.h"

#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath

#include <TFile.h> // TFile

const Int_t SyncNtupleManagerBase::placeholder_value = -9999;
const std::regex SyncNtupleManagerBase::endsWithNumberRegex(".*\\d+$");

SyncNtupleManagerBase::SyncNtupleManagerBase(TFile * outputTreePtr,
                                             const std::string & outputTreeName)
  : outputFile(outputTreePtr)
  , outputDir(nullptr)
  , outputTree(nullptr)
{
  std::string outputDirName_;
  std::string outputTreeName_ = outputTreeName;
  const auto nofSlashes = std::count(outputTreeName.cbegin(), outputTreeName.cend(), '/');
  if(nofSlashes == 1)
  {
    const std::size_t slashPos = outputTreeName.find('/');
    outputDirName_ = outputTreeName.substr(0, slashPos);
    outputTreeName_ = outputTreeName.substr(slashPos + 1);
  }
  else if(nofSlashes > 1)
  {
    throw cmsException(this) << "Invalid name for TTree = " << outputTreeName;
  }

  if(! outputDirName_.empty())
  {
    outputDir = outputFile->mkdir(outputDirName_.c_str());
    outputDir -> cd();
  }

  outputTree = new TTree(outputTreeName_.c_str(), outputTreeName_.c_str());
  if(outputDir)
  {
    outputTree->SetDirectory(outputDir);
  }
}

SyncNtupleManagerBase::~SyncNtupleManagerBase()
{}

void
SyncNtupleManagerBase::fill()
{
  if(outputDir)
  {
    outputDir -> cd();
  }
  else
  {
    outputFile -> cd();
  }
  outputTree -> Fill();
  resetBranches();
}

void
SyncNtupleManagerBase::write()
{
  if(outputDir)
  {
    outputDir -> cd();
  }
  else
  {
    outputFile -> cd();
  }
  outputTree -> Write();
}

bool
SyncNtupleManagerBase::endsWithNumber(const std::string & infix)
{
  std::smatch match;
  return std::regex_match(infix, match, endsWithNumberRegex);
}
