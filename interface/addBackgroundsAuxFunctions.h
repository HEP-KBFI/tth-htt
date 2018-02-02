#ifndef tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h

#include <vector> // std::vector<>
#include <string> // std::string

// forward declarations
class TDirectory;

std::vector<const TDirectory *>
getSubdirectories(const TDirectory *);

std::vector<std::string>
getSubdirectoryNames(const TDirectory *);

#endif // tthAnalysis_HiggsToTauTau_addBackgroundsAuxFunctions_h
