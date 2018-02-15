#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h"

template <typename Trec>
class ParticleCollectionGenMatcher
{
public:
  ParticleCollectionGenMatcher() {}
  ~ParticleCollectionGenMatcher() {}

  /**
   * @brief Match reconstructed particles to generator level electrons and muons by dR
   */
  void
  addGenLeptonMatch(std::vector<const Trec *> & recParticles,
                    const std::vector<GenLepton> & genLeptons,
                    double dRmax)
  {
    return addGenMatch<GenLepton, GenLeptonLinker>(recParticles, genLeptons, dRmax, genLeptonLinker_);
  }

  /**
   * @brief Match reconstructed particles to generator level hadronic tau decays by dR
   */
  void
  addGenHadTauMatch(std::vector<const Trec *> & recParticles,
                    const std::vector<GenHadTau> & genHadTaus,
                    double dRmax)
  {
    return addGenMatch<GenHadTau, GenHadTauLinker>(recParticles, genHadTaus, dRmax, genHadTauLinker_);
  }

  /**
   * @brief Match reconstructed particles to generator level jets by dR
   */
  void
  addGenJetMatch(std::vector<const Trec *> & recParticles,
                 const std::vector<GenJet> & genJets,
                 double dRmax)
  {
    return addGenMatch<GenJet, GenJetLinker>(recParticles, genJets, dRmax, genJetLinker_);
  }

protected:
  /**
   * @brief Match reconstructed particles to generator level particles by dR
   */
  template <typename Tgen,
            typename Tlinker>
  void
  addGenMatch(std::vector<const Trec *> & recParticles,
              const std::vector<Tgen> & genParticles,
              double dRmax,
              const Tlinker & linker)
  {
    for(const Trec * recParticle: recParticles)
    {
      const Tgen * bestMatch = nullptr;
      double dR_bestMatch = 1.e+3;

      for (const Tgen & genParticle: genParticles)
      {
        const double dR = deltaR(
          recParticle->eta(), recParticle->phi(), genParticle.eta(), genParticle.phi()
        );
        if(dR < dRmax && dR < dR_bestMatch)
        {
          bestMatch = &genParticle;
          dR_bestMatch = dR;
        }
      }

      if(bestMatch)
      {
        Trec * recParticle_nonconst = const_cast<Trec *>(recParticle);
        linker(*recParticle_nonconst, bestMatch);
      }
    }
  }

  struct GenLeptonLinker
  {
    void
    operator()(Trec & recParticle,
               const GenLepton * genLepton) const
    {
      recParticle.set_genLepton(new GenLepton(*genLepton));
    }
  };
  GenLeptonLinker genLeptonLinker_;

  struct GenHadTauLinker
  {
    void operator()(Trec & recParticle,
                    const GenHadTau * genHadTau) const
    {
      recParticle.set_genHadTau(new GenHadTau(*genHadTau));
    }
  };
  GenHadTauLinker genHadTauLinker_;

  struct GenJetLinker
  {
    void operator()(Trec & recParticle,
                    const GenJet * genJet) const
    {
      recParticle.set_genJet(new GenJet(*genJet));
    }
  };
  GenJetLinker genJetLinker_;
};

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"

typedef ParticleCollectionGenMatcher<RecoElectron> RecoElectronCollectionGenMatcher;

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"

typedef ParticleCollectionGenMatcher<RecoMuon> RecoMuonCollectionGenMatcher;

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"

typedef ParticleCollectionGenMatcher<RecoHadTau> RecoHadTauCollectionGenMatcher;

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

typedef ParticleCollectionGenMatcher<RecoJet> RecoJetCollectionGenMatcher;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h
