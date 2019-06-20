#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionCleanerSubJets_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionCleanerSubJets_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h"

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <cxxabi.h> // abi::__cxa_demangle()

#include <type_traits>

class RecoJetHTTv2;

template <typename T>
std::string
get_human_name()
{
  return std::string(abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr));
}

// credit to: https://stackoverflow.com/a/47064058
// If the class T has function subJet3, hasSubjet3Functor won't be nullptr, which in turn means that
// the functions that take int as the first argument will be enabled (because the second template argument is not
// a nullptr); if the class T has no function subJet3, the hasSubJet3Functor functor will be a nullptr and
// the functions taking long as the first argument are called. When calling these functions with an integer literal
// (such as 0), the functions that take int as the first argument are tried; if that fails, then overloaded functions
// that take long as the first argument are called. This mechanism makes sure that 3rd subjet (or nullptr) is returned
// when it's (not) available in the class T at compile time.
template<typename T> using hasSubJet3Functor = decltype(std::declval<const T>().subJet3());

template <typename T,
          hasSubJet3Functor<T> * = nullptr>
const RecoSubjetHTTv2 *
optionalToSubJet3(const T * obj, int)
{
  return obj->subJet3();
}

template <typename T>
const RecoSubjetHTTv2 *
optionalToSubJet3(const T *, long)
{
  return nullptr;
}

template <typename T>
constexpr bool
subJet3Exists(long)
{
  return false;
}

template <typename T,
          hasSubJet3Functor<T> * = nullptr>
constexpr bool
subJet3Exists(int)
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
      if(! (particle->subJet1() && particle->subJet2()))
      {
        isOverlap = true;
        if(debug_)
        {
          std::cout << "Jet of type '" << get_human_name<T>() << "' "
                    << "removed:\n"    << *particle
                    << "because it does not have subjets\n"
          ;
        }
      }
      for(const Toverlap * overlap: overlaps)
      {
        if(isOverlap)
        {
          break;
        }

        const double dRoverlap1 = deltaR(
          particle->subJet1()->eta(), particle->subJet1()->phi(), overlap->eta(), overlap->phi()
        );
        const double dRoverlap2 = deltaR(
          particle->subJet2()->eta(), particle->subJet2()->phi(), overlap->eta(), overlap->phi()
        );

        double dRoverlap3 = 100.;
        const bool has_subjet3 = subJet3Exists<T>(0);
        if(has_subjet3)
        {
          const RecoSubjetHTTv2 * sub3 = optionalToSubJet3(particle, 0);
          if(istypeHTTv2 && sub3)
          {
            dRoverlap3 = deltaR(sub3->p4().eta(), sub3->p4().phi(), overlap->eta(), overlap->phi());
          }
        }

        if(dRoverlap1 < dR_ || dRoverlap2 < dR_ || dRoverlap3 < dR_)
        {
          isOverlap = true;
          if(debug_)
          {
            std::cout
              << "Jet of type '" << get_human_name<T>() << "' (that has 3rd subjet =" << subJet3Exists<T>(0) << ") "
                 "removed:\n" << *particle << "because it overlapped with:\n" << *overlap << " "
                 "within dR1 = " << dRoverlap1 << " dR2 = " << dRoverlap2 << " dR3 = " << dRoverlap3 << '\n'
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"

typedef ParticleCollectionCleanerSubJets<RecoJetAK8> RecoJetCollectionCleanerAK8SubJets;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionCleaner_h
