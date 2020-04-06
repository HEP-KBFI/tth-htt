#ifndef HLTFILTER_H
#define HLTFILTER_H

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

#include <vector> // std::vector<>
#include <map> // std::map<,>

// forward declarations
class RecoLepton;
class RecoHadTau;

enum class hltPathsE
{
  trigger_1e,
  trigger_1mu,
  trigger_2e,
  trigger_2mu,
  trigger_1e1mu,
  trigger_3e,
  trigger_3mu,
  trigger_2e1mu,
  trigger_1e2mu,
  trigger_1e1tau,
  trigger_1mu1tau,
  trigger_2tau,
};

bool
hltFilter(const std::map<hltPathsE, bool> & trigger_bits,
          const std::vector<const RecoLepton *> & leptons,
          const std::vector<const RecoHadTau *> & taus);

bool
hltFilter(const RecoHadTau& tau, const hltPathsE& hltPath);

// HLT filter names specific to 2016 data-taking period
enum { 
  kTauFilterBit2016_notApplied, 
  kTauFilterBit2016_passesLooseIso,                kTauFilterBit2016_failsLooseIso, 
  kTauFilterBit2016_passesMediumIso,               kTauFilterBit2016_failsMediumIso
};

// HLT filter names specific to 2017 and 2018 data-taking periods
enum { 
  kTauFilterBit2017and2018_notApplied, 
  kTauFilterBit2017and2018_passesLooseChargedIso,  kTauFilterBit2017and2018_failsLooseChargedIso, 
  kTauFilterBit2017and2018_passesMediumChargedIso, kTauFilterBit2017and2018_failsMediumChargedIso, 
  kTauFilterBit2017and2018_passesTightChargedIso,  kTauFilterBit2017and2018_failsTightChargedIso 
};

bool
hltFilter(const RecoHadTau& tau, int filterBit, Era era);

#endif // HLTFILTER_H
