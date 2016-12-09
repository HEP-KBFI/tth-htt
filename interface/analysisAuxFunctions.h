#ifndef tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonSelectorTight

#include <vector>

//--- declare constants
const double z_mass   = 91.1876;
const double z_window = 10.;
const double met_coef =  0.00397;
const double mht_coef =  0.00265;

//--- declare data-taking periods
enum { kEra_2015, kEra_2016 };

//--- declare systematic uncertainties on data/MC corrections for b-tagging efficiency and mistag rates
enum { kBtag_central, 
       kBtag_hfUp, kBtag_hfDown, kBtag_hfStats1Up, kBtag_hfStats1Down, kBtag_hfStats2Up, kBtag_hfStats2Down,
       kBtag_lfUp, kBtag_lfDown, kBtag_lfStats1Up, kBtag_lfStats1Down, kBtag_lfStats2Up, kBtag_lfStats2Down,
       kBtag_cErr1Up, kBtag_cErr1Down, kBtag_cErr2Up, kBtag_cErr2Down, 
       kBtag_jesUp, kBtag_jesDown };

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2);

/**
 * @brief Auxiliary function for checking if leptons passing fake-able lepton selection pass tight lepton identification criteria also
 */
template <typename Tfakeable, typename Ttight>
bool isMatched(const Tfakeable& fakeableLepton, const std::vector<Ttight*>& tightLeptons, double dRmax = 1.e-2)
{
  for ( typename std::vector<const Ttight*>::const_iterator tightLepton = tightLeptons.begin();
        tightLepton != tightLeptons.end(); ++tightLepton ) {
    double dR = deltaR(fakeableLepton.eta_, fakeableLepton.phi_, (*tightLepton)->eta_, (*tightLepton)->phi_);
    if ( dR < dRmax ) return true; // found match
  }
  return false; // no match found
}

/**
 * @brief Return branchName to read weights that need to be applied, per jet, to MC events in order to correct for data/MC differences in b-tagging efficiency and mistag rates
 */
std::string getBranchName_bTagWeight(int era, const std::string& central_or_shift);
std::string getBranchName_bTagWeight(int era, int central_or_shift);

/**
 * @brief Return first N objects from collection given as function argument. In case the input collection contains fewer than N objects, the whole input collection is returned
 */
template <typename T>
std::vector<T> pickFirstNobjects(const std::vector<T>& objects_input, size_t N)
{
  std::vector<T> objects_output;
  size_t N_input = objects_input.size();
  for ( size_t idx = 0; idx < std::min(N_input, N); ++idx ) {
    objects_output.push_back(objects_input[idx]);
  }
  return objects_output;
}

/**
 * @brief Compute MHT
 */
math::PtEtaPhiMLorentzVector compMHT(const std::vector<const RecoLepton*>& leptons, const std::vector<const RecoHadTau*>& hadTaus, const std::vector<const RecoJet*>& jets);

/**
 * @brief Compute linear discriminator based on MET and MHT
 */
double compMEt_LD(const math::PtEtaPhiMLorentzVector& met_p4, const math::PtEtaPhiMLorentzVector& mht_p4);

/**
 * @brief Set "cone pT" for leptons that pass the "fakeable" lepton selection, but fail the "tight" lepton selection, 
 *        as described in lines 304-306 of AN-2016/211
 */
void set_cone_pT(std::vector<const RecoElectron*>& fakeableElectrons, int era);
void set_cone_pT(std::vector<const RecoMuon*>& fakeableMuons, int era);

/**
 * @brief Build collection of selected leptons by merging collections of selected electrons and selected muons
 */
std::vector<const RecoLepton*> mergeLeptonCollections(const std::vector<const RecoElectron*>& electrons, const std::vector<const RecoMuon*>& muons);

#endif
