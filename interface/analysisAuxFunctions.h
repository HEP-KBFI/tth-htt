#ifndef tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle, Candidate::LorentzVector
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

//--- declare selection criteria for leptons and hadronic taus
enum { kLoose, kFakeable, kTight };

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool isHigherPt(const GenParticle* particle1, const GenParticle* particle2);

/**
 * @brief Auxiliary function used for sorting leptons by decreasing cone pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher cone pT; false if second lepton has higher cone pT
 */
bool isHigherConePt(const RecoLepton* particle1, const RecoLepton* particle2);

/**
 * @brief Auxiliary function for sorting a collection of RecoJet pointers
 *        by their b-tagging CSV score
 * @param jet1 The first jet
 * @param jet2 The second jet
 * @return True, if the 1st jet has higher CSV score
 */
bool isHigherCSV(const RecoJet * jet1, const RecoJet * jet2);

/**
 * @brief Auxiliary function for checking if leptons passing fake-able lepton selection pass tight lepton identification criteria also
 */
template <typename Tfakeable, typename Ttight>
bool isMatched(const Tfakeable& fakeableLepton, const std::vector<Ttight*>& tightLeptons, double dRmax = 1.e-2)
{
  for ( typename std::vector<const Ttight*>::const_iterator tightLepton = tightLeptons.begin();
        tightLepton != tightLeptons.end(); ++tightLepton ) {
    double dR = deltaR(fakeableLepton.eta(), fakeableLepton.phi(), (*tightLepton)->eta(), (*tightLepton)->phi());
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

int getHadTau_genPdgId(const RecoHadTau* hadTau);

/**
 * @brief Compute MHT
 */
math::PtEtaPhiMLorentzVector compMHT(const std::vector<const RecoLepton*>& leptons, const std::vector<const RecoHadTau*>& hadTaus, const std::vector<const RecoJet*>& jets);

/**
 * @brief Compute linear discriminator based on MET and MHT
 */
double compMEt_LD(const Particle::LorentzVector& met_p4, const Particle::LorentzVector& mht_p4);

/**
 * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
 */
template <typename T>
void set_selection_flags(std::vector<const T*>& leptons, int selection)
{
  for ( typename std::vector<const T*>::iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    if      ( selection == kLoose    ) (*lepton)->set_isLoose();
    else if ( selection == kFakeable ) (*lepton)->set_isFakeable();
    else if ( selection == kTight    ) (*lepton)->set_isTight();
    else assert(0);
  }
}

/**
 * @brief Build collection of selected leptons by merging collections of selected electrons and selected muons
 */
std::vector<const RecoLepton*> mergeLeptonCollections(const std::vector<const RecoElectron*>& electrons, const std::vector<const RecoMuon*>& muons);

/**
 * @brief Print values of pT, eta, phi as well as ID and isolation variables for electrons and muons (for debugging purposes)
 */
void printGenLeptonCollection(const std::string& collection_name, const std::vector<GenLepton>& genLeptons);
void printLeptonCollection(const std::string& collection_name, const std::vector<const RecoLepton*>& leptons);

/**
 * @brief Print values of pT, eta, phi as well as of tau ID/isolation variables for hadronic taus (for debugging purposes)
 */
void printGenHadTauCollection(const std::string& collection_name, const std::vector<GenHadTau>& genHadTaus);
void printHadTauCollection(const std::string& collection_name, const std::vector<const RecoHadTau*>& hadTaus);

/**
 * @brief Print values of pT, eta, phi as well as the b-tagging discriminator values for jets (for debugging purposes)
 */
void printGenJetCollection(const std::string& collection_name, const std::vector<GenJet>& genJets);
void printJetCollection(const std::string& collection_name, const std::vector<const RecoJet*>& jets);

/**
 * @brief Compute sign of value given as function parameter
 * @return +1 if val > 0, 0 if val = 0, -1 of val < 0
 */
template <typename T> 
int sgn(T val) 
{
  if      ( val > 0 ) return +1;
  else if ( val < 0 ) return -1;
  else                return  0;
}

#endif
