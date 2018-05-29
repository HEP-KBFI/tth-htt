#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h"

#include <TList.h> // TList
#include <TKey.h> // TKey
#include <TDirectory.h> // TDirectory

std::vector<const TDirectory *>
getSubdirectories(const TDirectory * dir)
{
  std::vector<const TDirectory *> subdirectories;
  TList * list = dir->GetListOfKeys();
  TIter next(list);
  TKey * key = nullptr;

  while((key = dynamic_cast<TKey*>(next())))
  {
    const TObject * object = key->ReadObj();
    const TDirectory * subdirectory = dynamic_cast<const TDirectory *>(object);
    if(subdirectory)
    {
      subdirectories.push_back(subdirectory);
    }
    else
    {
      delete object;
    }
  }
  return subdirectories;
}

std::vector<std::string>
getSubdirectoryNames(const TDirectory * dir)
{
  const std::vector<const TDirectory *> subdirectories = getSubdirectories(dir);
  std::vector<std::string> subdirectoryNames;
  for(const TDirectory * subdirectory: subdirectories)
  {
    subdirectoryNames.push_back(subdirectory->GetName());
  }
  return subdirectoryNames;
}
