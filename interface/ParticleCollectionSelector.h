#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

template <typename Tobj, typename Tsel>
class ParticleCollectionSelector
{
 public:
  ParticleCollectionSelector(int era, int index = -1, bool debug = false) 
    : selIndex_(index)
    , selector_(era, index, debug)
  {}
  ~ParticleCollectionSelector() {}

  /**
   * @brief Select subset of particles passing selection, by applying selector specified as template parameter to each particle in collection passed as function argument
   * @return Collection of selected particles
   */
  std::vector<const Tobj*> operator()(const std::vector<const Tobj*>& particles) const
  {
    std::vector<const Tobj*> selParticles;
    int idx = 0;
    for ( typename std::vector<const Tobj*>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      if ( selector_(**particle) ) {
	if ( idx == selIndex_ || selIndex_ == -1 ) {
	  selParticles.push_back(*particle);
	}
	++idx;
      }
    }
    return selParticles;
  }
  
 protected: 
  int selIndex_;
  Tsel selector_;
};

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionSelector_h

