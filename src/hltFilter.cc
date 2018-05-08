#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

bool
hltFilter(const std::map<hltPathsE, bool> & trigger_bits,
          const std::vector<const RecoLepton *> & leptons,
          const std::vector<const RecoHadTau *> & taus)
{
  static const unsigned trigger_eleIdx = 0;
  static const unsigned trigger_muIdx  = 1;
  static const unsigned trigger_tauIdx = 2;

  static const std::map<hltPathsE, std::array<int, 3>> trigger_multiplicities = {
    { hltPathsE::trigger_1e,      {{ 1, 0, 0 }} },
    { hltPathsE::trigger_1mu,     {{ 0, 1, 0 }} },
    { hltPathsE::trigger_2e,      {{ 2, 0, 0 }} },
    { hltPathsE::trigger_2mu,     {{ 0, 2, 0 }} },
    { hltPathsE::trigger_1e1mu,   {{ 1, 1, 0 }} },
    { hltPathsE::trigger_1e2mu,   {{ 1, 1, 0 }} }, // [*] ideally: { 1, 2, 0 }
    { hltPathsE::trigger_2e1mu,   {{ 2, 1, 0 }} },
    { hltPathsE::trigger_3e,      {{ 3, 0, 0 }} },
    { hltPathsE::trigger_3mu,     {{ 0, 2, 0 }} }, // [*] ideally: { 0, 3, 0 }
    { hltPathsE::trigger_1e1tau,  {{ 1, 0, 1 }} },
    { hltPathsE::trigger_1mu1tau, {{ 0, 1, 1 }} },
    { hltPathsE::trigger_2tau,    {{ 0, 0, 2 }} },
  };
  // [*] There's a bug in HLTMuonL3PreFilter module, which loses one muon trigger object, see
  //     https://hypernews.cern.ch/HyperNews/CMS/get/muon-hlt/593.html for more information

  static const std::map<hltPathsE, std::array<int, 3>> trigger_filterBits = {
    { hltPathsE::trigger_1e,      {{   2,   0,   0 }} },
    { hltPathsE::trigger_1mu,     {{   0,   8,   0 }} },
    { hltPathsE::trigger_2e,      {{  16,   0,   0 }} },
    { hltPathsE::trigger_2mu,     {{   0,  16,   0 }} },
    { hltPathsE::trigger_1e1mu,   {{  32,  32,   0 }} },
    { hltPathsE::trigger_1e2mu,   {{ 512, 256,   0 }} },
    { hltPathsE::trigger_2e1mu,   {{ 256, 512,   0 }} },
    { hltPathsE::trigger_3e,      {{ 128,   0,   0 }} },
    { hltPathsE::trigger_3mu,     {{   0, 128,   0 }} },
    { hltPathsE::trigger_1e1tau,  {{  64,   0, 128 }} },
    { hltPathsE::trigger_1mu1tau, {{   0, 256,  64 }} },
    { hltPathsE::trigger_2tau,    {{   0,   0,  64 }} },
  };

  bool is_matched = false;
  for(const auto & kv: trigger_bits)
  {
    const bool is_triggered = kv.second;
    if(! is_triggered)
    {
      // If the trigger hasn't fired, there is no point trying to check if any of the reco objects
      // match to trigger objects that come from this (non-fired) HLT trigger path.
      continue;
    }

    const hltPathsE path = kv.first;
    int nof_electrons = 0;
    int nof_muons = 0;
    int nof_taus = 0;

    for(const RecoLepton * lepton: leptons)
    {
      const UInt_t filterBits = lepton->filterBits();
      if(lepton->is_electron())
      {
        if(filterBits & trigger_filterBits.at(path).at(trigger_eleIdx))
        {
          ++nof_electrons;
        }
      }
      else if(lepton->is_muon())
      {
        if(filterBits & trigger_filterBits.at(path).at(trigger_muIdx))
        {
          ++nof_muons;
        }
      }
      else
      {
        throw cmsException(__func__, __LINE__)
          << "Invalid lepton flavor";
      }
    }
    for(const RecoHadTau * tau: taus)
    {
      const UInt_t filterBits = tau->filterBits();
      if(filterBits & trigger_filterBits.at(path).at(trigger_tauIdx))
      {
        ++nof_taus;
      }
    }

    // There are at least two ways of how the HLT filter could be applied:
    // 1) require that all trigger objects that come from any fired HLT paths are matched to the reco objects
    // 2) require that all reco objects are matched to trigger objects that come from fired HLT paths
    // In the current implementation, we perform 1) here: if the reco objects are matched to at least one set
    // of trigger objects that originate from a fired trigger, we can say that the event passes HLT filter cuts.
    if(nof_electrons == trigger_multiplicities.at(path).at(trigger_eleIdx) &&
       nof_muons     == trigger_multiplicities.at(path).at(trigger_muIdx) &&
       nof_taus      == trigger_multiplicities.at(path).at(trigger_tauIdx))
    {
      is_matched = true;
      break;
    }
  }
  return is_matched;
}
