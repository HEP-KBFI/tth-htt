#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h

/** \class RecoSubjetAK12
 *
 * Class to access information for subjets of jets reconstructed by the anti-kT algorithm with R=1.2 (AK12),
 * used for reconstruction of boosted W bosons (produced in hadronic top decays with resolved b-jets)
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase

class RecoSubjetAK12
  : public RecoJetBase
{
public:
  RecoSubjetAK12() = default;
  RecoSubjetAK12(const GenJet & particle,
		 Int_t idx);

  virtual ~RecoSubjetAK12();
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoSubjetAK12 & jet);

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetAK12_h

