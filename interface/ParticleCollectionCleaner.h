#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

template <typename T>
class ParticleCollectionCleaner
{
public:
  ParticleCollectionCleaner(double dR = 0.4,
                            bool debug = false)
    : dR_(dR)
    , debug_(debug)
  {}
  ~ParticleCollectionCleaner() {}

  /**
   * @brief Select subset of particles not overlapping with any of the other particles passed as function argument
   * @return Collection of non-overlapping particles
   */
  template <typename Toverlap>
  std::vector<const T *> operator()(const std::vector<const T *> & particles,
                                    const std::vector<const Toverlap *> & overlaps) const
  {
    std::vector<const T *> cleanedParticles;
    for(const T * particle: particles)
    {
      bool isOverlap = false;
      for(const Toverlap * overlap: overlaps)
      {
        const double dRoverlap = deltaR(particle->eta(), particle->phi(), overlap->eta(), overlap->phi());
        if(dRoverlap < dR_)
        {
          isOverlap = true;
          if(debug_)
          {
            std::cout << "Removed:\n"                    << *particle
                      << "because it overlapped with:\n" << *overlap
                      << "within "                       << dRoverlap
                      << '\n'
            ;
          }
          break;
        }
      }
      if(! isOverlap)
      {
        cleanedParticles.push_back(particle);
      }
    }
    return cleanedParticles;
  }

  template <typename Toverlap,
            typename... Args>
  std::vector<const T *> operator()(const std::vector<const T *> & particles,
                                    const std::vector<const Toverlap *> & overlaps,
                                    Args... args) const
  {
    std::vector<const T *> cleanedParticles = (*this)(particles, overlaps);
    return (*this)(cleanedParticles, args...);
  }

protected:
  double dR_;
  bool debug_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"

typedef ParticleCollectionCleaner<RecoElectron> RecoElectronCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"

typedef ParticleCollectionCleaner<RecoMuon> RecoMuonCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"

typedef ParticleCollectionCleaner<RecoHadTau> RecoHadTauCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

typedef ParticleCollectionCleaner<RecoJet> RecoJetCollectionCleaner;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

typedef ParticleCollectionCleaner<RecoJetHTTv2> RecoJetCollectionCleanerHTTv2;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h"

typedef ParticleCollectionCleaner<RecoJetAK12> RecoJetCollectionCleanerAK12;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"

typedef ParticleCollectionCleaner<RecoJetAK8> RecoJetCollectionCleanerAK8;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h
