#ifndef tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h
#define tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h"
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h"
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon

#include <algorithm> // std::find()

enum class GenParticleType
{
  kGenElectron,
  kGenMuon,
  kGenPhoton,
  kGenAnyLepton,
  kGenAny,
};

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
                    double dRmax = 0.2,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenLepton, GenLeptonLinker>(recParticles, genLeptons, dRmax, maxDPtRel, genLeptonLinker_);
  }

  void
  addGenLeptonMatchByIndex(const std::vector<const Trec *> & recParticles,
                           const std::vector<GenParticle> & genParticles,
                           GenParticleType genParticleType) const
  {
    if(genParticleType == GenParticleType::kGenPhoton)
    {
      throw cmsException(this, __func__, __LINE__) << "Cannot match to gen photons in this function";
    }
    return addGenMatchByIndex<GenLeptonLinker>(recParticles, genParticles, genLeptonLinker_, genParticleType);
  }

  /**
   * @brief Match reconstructed particles to generator level hadronic tau decays by dR
   */
  void
  addGenHadTauMatch(const std::vector<const Trec *> & recParticles,
                    const std::vector<GenHadTau> & genHadTaus,
                    double dRmax = 0.2,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenHadTau, GenHadTauLinker>(recParticles, genHadTaus, dRmax, maxDPtRel, genHadTauLinker_);
  }

  void
  addGenPhotonMatch(const std::vector<const Trec *> & recParticles,
                    const std::vector<GenPhoton> & genPhotons,
                    double dRmax = 0.2,
                    double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenPhoton, GenPhotonLinker>(recParticles, genPhotons, dRmax, maxDPtRel, genPhotonLinker_);
  }

  void
  addGenPhotonMatchByIndex(const std::vector<const Trec *> & recParticles,
                           const std::vector<GenParticle> & genParticles) const
  {
    return addGenMatchByIndex<GenPhotonLinker>(recParticles, genParticles, genPhotonLinker_, GenParticleType::kGenPhoton);
  }

  /**
   * @brief Match reconstructed particles to generator level jets by dR
   */
  void
  addGenJetMatch(const std::vector<const Trec *> & recParticles,
                 const std::vector<GenJet> & genJets,
                 double dRmax = 0.2,
                 double maxDPtRel = 0.5) const
  {
    return addGenMatch<GenJet, GenJetLinker>(recParticles, genJets, dRmax, maxDPtRel, genJetLinker_);
  }

  void
  addGenJetMatchByIndex(const std::vector<const Trec *> & recParticles,
                        const std::vector<GenParticle> & genJets) const
  {
    return addGenMatchByIndex<GenJetLinker>(recParticles, genJets, genJetLinker_, GenParticleType::kGenAny);
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

  template <typename Tlinker,
            typename Tgen = GenParticle>
  void
  addGenMatchByIndex(const std::vector<const Trec *> & recParticles,
                     const std::vector<Tgen> & genParticles,
                     const Tlinker & linker,
                     GenParticleType genParticleType) const
  {
    const int genParticleSize = genParticles.size();
    for(const Trec * recParticle: recParticles)
    {
      if(recParticle->hasAnyGenMatch())
      {
        // the reco particle has already been matched to a gen particle
        continue;
      }

      const int genMatchIdx = recParticle->genMatchIdx();

      if(genMatchIdx >= 0)
      {
        if(genMatchIdx >= genParticleSize)
        {
          throw cmsException(this, __func__, __LINE__)
            << "Expected gen matching index = " << genMatchIdx << " but gen collection has size of " << genParticleSize
          ;
        }
        Tgen * genMatch = const_cast<Tgen *>(&genParticles.at(genMatchIdx));

        std::vector<unsigned int> genAbsPdgIds;
        switch(genParticleType)
        {
          case GenParticleType::kGenElectron:  genAbsPdgIds = { 11 };     break;
          case GenParticleType::kGenMuon:      genAbsPdgIds = { 13 };     break;
          case GenParticleType::kGenAnyLepton: genAbsPdgIds = { 11, 13 }; break;
          case GenParticleType::kGenPhoton:    genAbsPdgIds = { 22 };     break;
          case GenParticleType::kGenAny:                                 break;
        }

        if(genAbsPdgIds.empty() ||
            (! genAbsPdgIds.empty() &&
             std::find(genAbsPdgIds.begin(), genAbsPdgIds.end(), std::abs(genMatch->pdgId())) != genAbsPdgIds.end())
           )
        {
          Trec * recParticle_nonconst = const_cast<Trec *>(recParticle);
          linker(*recParticle_nonconst, genMatch);
        }
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

    void
    operator()(Trec & recParticle,
               const GenParticle * genLepton) const
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

    void operator()(Trec & recParticle,
                    const GenParticle * genPhoton) const
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

    void operator()(Trec & recParticle,
                    const GenParticle * genJet) const
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

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // CV: used for generator-level matching of subjets in boosted H->bb and boosted W->jj decays

typedef ParticleCollectionGenMatcher<RecoJetBase> RecoJetBaseCollectionGenMatcher;

#endif // tthAnalysis_HiggsToTauTau_ParticleCollectionGenMatcher_h
