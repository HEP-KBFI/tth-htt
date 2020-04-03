#ifndef HLTFILTER_H
#define HLTFILTER_H

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

enum TauFilterBit { 
  kTauFilterBit_notApplied, 
  kTauFilterBit_passesLooseChargedIso,  kTauFilterBit_failsLooseChargedIso, 
  kTauFilterBit_passesMediumChargedIso, kTauFilterBit_failsMediumChargedIso, 
  kTauFilterBit_passesTightChargedIso,  kTauFilterBit_failsTightChargedIso 
};

bool
hltFilter(const RecoHadTau& tau, TauFilterBit filterBit);

#endif // HLTFILTER_H
