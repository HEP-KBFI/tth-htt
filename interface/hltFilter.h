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

#endif // HLTFILTER_H
