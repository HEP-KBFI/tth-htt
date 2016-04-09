#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h

#include "DataFormats/Math/interface/deltaR.h" // deltaR

template <typename T>
class ParticleCollectionCleaner
{
 public:
  ParticleCollectionCleaner(double dR = 0.4)
    : dR_(dR)
  {}
  ~ParticleCollectionCleaner() {}

  /**
   * @brief Select subset of particles not overlapping with any of the other particles passed as function argument
   * @return Collection of non-overlapping particles
   */
  template <typename Toverlap>
  std::vector<T> operator()(const std::vector<T>& particles, const std::vector<Toverlap>& overlaps)
  {
    std::vector<T> cleanedParticles;
    for ( typename std::vector<T>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      bool isOverlap = false;
      for ( typename std::vector<Toverlap>::const_iterator overlap = overlaps.begin();
	    overlap != overlaps.end(); ++overlap ) {
	double dRoverlap = deltaR(particle->eta_, particle->phi_, overlap->eta_, overlap->phi_);
	if ( dRoverlap < dR_ ) {
	  isOverlap = true;
	  break;
	}
      }
      if ( !isOverlap ) {
	cleanedParticles.push_back(*particle);
      }
    }
    return cleanedParticles;
  }
  template <typename Toverlap, typename... Args>
  std::vector<T> operator()(const std::vector<T>& particles, const std::vector<Toverlap>& overlaps, Args... args)
  {
    std::vector<T> cleanedParticles;
    for ( typename std::vector<T>::const_iterator particle = particles.begin();
	  particle != particles.end(); ++particle ) {
      bool isOverlap = false;
      for ( typename std::vector<Toverlap>::const_iterator overlap = overlaps.begin();
	    overlap != overlaps.end(); ++overlap ) {
	double dRoverlap = deltaR(particle->eta_, particle->phi_, overlap->eta_, overlap->phi_);
	if ( dRoverlap < dR_ ) {
	  isOverlap = true;
	  break;
	}
      }
      if ( !isOverlap ) {
	cleanedParticles.push_back(*particle);
      }
    }
    return this->operator()(cleanedParticles, args);
  }
  
 protected: 
  double dR_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"

typedef ParticleCollectionCleaner<RecoLepton> RecoLeptonCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadronicTau.h"

typedef ParticleCollectionCleaner<RecoHadronicTau> RecoHadronicTauCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

typedef ParticleCollectionCleaner<RecoJet> RecoJetCollectionCleaner;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h

