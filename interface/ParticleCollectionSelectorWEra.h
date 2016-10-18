#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionSelectorWEra_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionSelectorWEra_h

#include <vector> // std::vector<>

/* Same class as ParticleCollectionSelector, but supporting era option in the selector */

template <typename Tobj, typename Tsel>
class ParticleCollectionSelectorWEra
{
 public:
  ParticleCollectionSelectorWEra(int era, int index = -1, bool debug = false)
    : selIndex_(index)
    , selector_(era, index, debug)
  {}
  ~ParticleCollectionSelectorWEra() {}

  /**
   * @brief Select subset of particles passing selection, by applying selector specified as template parameter
   *        to each particle in collection passed as function argument
   * @return Collection of selected particles
   */
  std::vector<const Tobj*> operator()(const std::vector<const Tobj*> & particles) const
  {
    std::vector<const Tobj*> selParticles;
    int idx = 0;
    for(const Tobj * const & particle: particles)
      if ( selector_(*particle) ) {
        if ( idx == selIndex_ || selIndex_ == -1 ) {
          selParticles.push_back(particle);
        }
        ++idx;
      }
    return selParticles;
  }

 protected:
  int selIndex_;
  Tsel selector_;
};

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionSelectorWEra_h
