#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h"

#include <TList.h>
#include <TKey.h>
#include <TObject.h>

#include <vector>

std::vector<const TDirectory*> getSubdirectories(const TDirectory* dir)
{
  std::vector<const TDirectory*> subdirectories;
  TList* list = dir->GetListOfKeys();
  TIter next(list);
  TKey* key = 0;
  while ( (key = dynamic_cast<TKey*>(next())) ) {
    TObject* object = key->ReadObj();
    TDirectory* subdirectory = dynamic_cast<TDirectory*>(object);
    if ( subdirectory ) subdirectories.push_back(subdirectory);
  }
  return subdirectories;
}

std::vector<std::string> getSubdirectoryNames(const TDirectory* dir)
{
  std::vector<const TDirectory*> subdirectories = getSubdirectories(dir);
  std::vector<std::string> subdirectoryNames;
  for ( std::vector<const TDirectory*>::const_iterator subdirectory = subdirectories.begin();
	subdirectory != subdirectories.end(); ++subdirectory ) {
    subdirectoryNames.push_back((*subdirectory)->GetName());
  }
  return subdirectoryNames;
}
