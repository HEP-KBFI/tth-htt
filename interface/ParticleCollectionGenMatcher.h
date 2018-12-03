#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h"
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
  addGenLeptonMatch(const std::vector<const Trec *> & recParticles,
                    const std::vector<GenLepton> & genLeptons,
                    double dRmax,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenLepton, GenLeptonLinker>(recParticles, genLeptons, dRmax, maxDPtRel, genLeptonLinker_);
  }

  /**
   * @brief Match reconstructed particles to generator level hadronic tau decays by dR
   */
  void
  addGenHadTauMatch(const std::vector<const Trec *> & recParticles,
                    const std::vector<GenHadTau> & genHadTaus,
                    double dRmax,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenHadTau, GenHadTauLinker>(recParticles, genHadTaus, dRmax, maxDPtRel, genHadTauLinker_);
  }

  void
  addGenPhotonMatch(const std::vector<const Trec *> & recParticles,
                    const std::vector<GenPhoton> & genPhotons,
                    double dRmax,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenPhoton, GenPhotonLinker>(recParticles, genPhotons, dRmax, maxDPtRel, genPhotonLinker_);
  }

  /**
   * @brief Match reconstructed particles to generator level jets by dR
   */
  void
  addGenJetMatch(const std::vector<const Trec *> & recParticles,
                 const std::vector<GenJet> & genJets,
                 double dRmax,
                 double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenJet, GenJetLinker>(recParticles, genJets, dRmax, maxDPtRel, genJetLinker_);
  }

protected:
  /**
   * @brief Match reconstructed particles to generator level particles by dR
   */
  template <typename Tgen,
            typename Tlinker>
  void
  addGenMatch(const std::vector<const Trec *> & recParticles,
              const std::vector<Tgen> & genParticles,
              double dRmax,
              double maxDPtRel,
              const Tlinker & linker) const
  {
    for(const Trec * recParticle: recParticles)
    {
      if(recParticle->hasAnyGenMatch())
      {
        // the reco particle has already been matched to a gen particle
        continue;
      }
      Tgen * bestMatch = nullptr;
      double dR_bestMatch = 1.e+3;

      for(const Tgen & genParticle: genParticles)
      {
        const double dR = deltaR(
          recParticle->eta(), recParticle->phi(), genParticle.eta(), genParticle.phi()
        );
        const bool passesPtConstraint = std::abs(recParticle->pt() - genParticle.pt()) / genParticle.pt() < maxDPtRel;
        if(dR < dRmax && dR < dR_bestMatch && passesPtConstraint && ! genParticle.isMatchedToReco())
        {
          bestMatch = const_cast<Tgen *>(&genParticle);
          dR_bestMatch = dR;
        }
      }

      if(bestMatch)
      {
        // forbid the same gen particle to be matched to another reco particle
        bestMatch->setMatchedToReco();
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

  struct GenPhotonLinker
  {
    void operator()(Trec & recParticle,
                    const GenPhoton * genPhoton) const
    {
      recParticle.set_genPhoton(new GenPhoton(*genPhoton));
    }
  };
  GenPhotonLinker genPhotonLinker_;

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
