#ifndef tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h

#include "CommonTools/Utils/interface/TFileDirectory.h"

#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TDirectory.h>

#include <vector>
#include <string>

void fill(TH1*, double, double, double = 0.);
void fillWithOverFlow(TH1*, double, double, double = 0.);
void fill2d(TH2*, double, double, double, double = 0.);
void fillWithOverFlow2d(TH2*, double, double, double, double = 0.);

double getLogWeight(double weight);

void checkCompatibleBinning(const TH1*, const TH1*);

TH1* addHistograms(const std::string&, const TH1*, const TH1*, int = 0);
TH1* addHistograms(const std::string&, const std::vector<TH1*>&, int = 0);

TH1* subtractHistograms(const std::string&, const TH1*, const TH1*, int = 0);
TH1* subtractHistograms(const std::string&, const TH1*, const std::vector<TH1*>&, int = 0);

double compIntegral(const TH1*, bool, bool);

void makeBinContentsPositive(TH1*, int = 0);

void dumpHistogram(const TH1*);

TDirectory* getDirectory(const TFile*, const std::string&, bool);
TDirectory* getSubdirectory(const TDirectory*, const std::string&, bool);

TH1* getHistogram(const TDirectory*, const std::string&, const std::string&, const std::string&, bool);

TDirectory* createSubdirectory(TDirectory*, const std::string&);
TDirectory* createSubdirectory_recursively(TFileDirectory&, const std::string&);

TArrayD getBinning(const TH1*);
TH1* getRebinnedHistogram1d(const TH1*, unsigned, const TArrayD&);
TH2* getRebinnedHistogram2d(const TH1*, unsigned, const TArrayD&, unsigned, const TArrayD&);

#endif // tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h
