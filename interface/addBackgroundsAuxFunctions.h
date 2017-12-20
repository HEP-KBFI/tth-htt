#ifndef tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h

#include <TDirectory.h>

#include <vector>
#include <string>

std::vector<const TDirectory*> getSubdirectories(const TDirectory*);
std::vector<std::string> getSubdirectoryNames(const TDirectory*);

#endif // tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h
