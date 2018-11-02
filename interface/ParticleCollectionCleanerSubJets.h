#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionCleanerSubJets_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionCleanerSubJets_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h"
#include <DataFormats/Math/interface/deltaR.h> // deltaR()
#include <type_traits>

template<typename TT> using toStringFn = decltype(std::declval<const TT>().subJet3());

template < class TT, toStringFn<TT>* = nullptr>
const RecoSubjetHTTv2* optionalToString(const TT* obj, int)
{
    return obj->subJet3();
}

template <class TT>
const RecoSubjetHTTv2* optionalToString(const TT* obj, long)
{
    return nullptr;
}

template <typename TT>
constexpr bool toStringExists(long)
{
    return false;
}

template <typename TT, toStringFn<TT>* = nullptr>
constexpr bool toStringExists(int)
{
    return true;
}

template <typename T>


class ParticleCollectionCleanerSubJets
{
public:
  ParticleCollectionCleanerSubJets(double dR = 0.4,
                            bool debug = false)
    : dR_(dR)
    , debug_(debug)
  {}
  ~ParticleCollectionCleanerSubJets() {}

  /**
   * @brief Select subset of particles not overlapping with any of the other particles passed as function argument
   * @return Collection of non-overlapping particles
   */
  template <typename Toverlap>
  std::vector<const T *> operator()(const std::vector<const T *> & particles,
                                    const std::vector<const Toverlap *> & overlaps) const
  {
    std::vector<const T *> cleanedParticles;
    const bool istypeHTTv2 = std::is_same<T, RecoJetHTTv2>::value;
    for(const T * particle: particles)
    {
      bool isOverlap = false;
      if ( !(particle->subJet1() && particle->subJet2()) ) continue;
      for(const Toverlap * overlap: overlaps)
      {
        const double dRoverlap1 = deltaR(
          particle->subJet1()->eta(), particle->subJet1()->phi(), overlap->eta(), overlap->phi()
        );
        const double dRoverlap2 = deltaR(
          particle->subJet2()->eta(), particle->subJet2()->phi(), overlap->eta(), overlap->phi()
        );
        const bool has_subjet3 =  toStringExists<T>(0);
        double dRoverlap3 = 100.;
        if (has_subjet3) {
        const RecoSubjetHTTv2* sub3 = optionalToString(particle, 0);
        if (istypeHTTv2 && !(sub3 == 0)) dRoverlap3 = deltaR(
          sub3->p4().eta(), sub3->p4().phi(), overlap->eta(), overlap->phi()
        );
        }
        if ( dRoverlap1 < dR_ || dRoverlap2 < dR_ || dRoverlap3 < dR_) //
        {
          isOverlap = true;
          if(debug_)
          {
            std::cout << "TypeJet: " << typeid(particles).name() << " " << dRoverlap1 << " " << dRoverlap2 << " " << dRoverlap3 << std::endl;
            std::cout << toStringExists<T>(0) << std::endl;
            std::cout << "Removed:\n"                    << *particle
                      << "because it overlapped with:\n" << *overlap
                      << "within "                       << dRoverlap1
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

typedef ParticleCollectionCleanerSubJets<RecoJetHTTv2> RecoJetCollectionCleanerHTTv2SubJets;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h"

typedef ParticleCollectionCleanerSubJets<RecoJetAK12> RecoJetCollectionCleanerAK12SubJets;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"

typedef ParticleCollectionCleanerSubJets<RecoJetAK8> RecoJetCollectionCleanerAK8SubJets;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h
