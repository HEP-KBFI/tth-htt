#ifndef tthAnalysis_HiggsToTauTau_copyHistograms_h
#define tthAnalysis_HiggsToTauTau_copyHistograms_h

#include "DataFormats/FWLite/interface/InputSource.h"   // fwlite::InputSource
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService

#include <vector> // std::vector<>
#include <string> // std::string
#include <regex>  // td::regex, std::smatch

/**
 * @brief Copy histograms from input to output ROOT file
 *
 * Used by addMEM executables in order to keep track of the number of processed events
 *
 */
void 
copyHistograms(const fwlite::InputSource& inputFiles, const std::vector<std::regex>& copy_histograms_regex, fwlite::TFileService& fs);

#endif
