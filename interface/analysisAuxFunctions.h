#ifndef tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetBase.h" // RecoJetBase
#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h" // TrigObj
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <DataFormats/Math/interface/deltaR.h> // deltaR()
#include <DataFormats/Math/interface/LorentzVector.h> // math::PtEtaPhiMLorentzVector

#include <TMath.h> // TMath::Abs()

#include <vector> // std::vector<>
#include <map> // std::map<,>
#include <algorithm> // std::copy_n()
#include <type_traits> // std::underlying_type<>

#define TAU_WP_SEPARATOR   "&"
#define TAU_WP_SEPARATOR_C '&'

// forward declarations
class Particle;
class RecoLepton;
class RecoJet;
class RecoJetAK8;
class RecoHadTau;
class RecoMuon;
class RecoElectron;

enum class EWKJetSys;
enum class EWKBJetSys;

//--- declare constants
const double wBosonMass = 80.379; // GeV
const double z_mass   = 91.1876;
const double z_window = 10.;
const double met_coef =  0.6;
const double mht_coef =  0.4;
const double w_mass   = 80.385;
const double w_window = 10.;

//--- declare data-taking periods
enum
{
  kEra_undefined, kEra_2016, kEra_2017, kEra_2018
};

enum class Btag
{
  kDeepJet, kDeepCSV, kCSVv2
};

//--- declare selection criteria for leptons and hadronic taus
enum { kLoose, kFakeable, kTight };

//--- declare tau ID discriminators

enum class TauID {
  MVAnewDM2017v2, MVAoldDM, MVAoldDMdR032017v2, MVAoldDM2017v1, MVAoldDM2017v2,
  DeepTau2017v2VSe, DeepTau2017v2VSmu, DeepTau2017v2VSjet
};

const std::map<TauID, int> TauID_levels = {
  { TauID::MVAnewDM2017v2,     7 }, // VVLoose  - 1, VVTight - 7
  { TauID::MVAoldDM,           6 }, // VLoose   - 1, VVTight - 7
  { TauID::MVAoldDMdR032017v2, 7 }, // VVLoose  - 1, VVTight - 7
  { TauID::MVAoldDM2017v1,     7 }, // VVLoose  - 1, VVTight - 7
  { TauID::MVAoldDM2017v2,     7 }, // VVLoose  - 1, VVTight - 7
  { TauID::DeepTau2017v2VSe,   8 }, // VVVLoose - 1, VVTight - 8
  { TauID::DeepTau2017v2VSmu,  4 }, // VLoose   - 1, Tight   - 4
  { TauID::DeepTau2017v2VSjet, 8 }, // VVVLoose - 1, VVTight - 8
};

const std::map<int, std::vector<std::string>> TauID_level_strings = {
  { 1, {                                                     "Tight"                      } },
  { 2, {                                  "Loose",           "Tight"                      } },
  { 4, {                        "VLoose", "Loose", "Medium", "Tight"                      } },
  { 5, {                        "VLoose", "Loose", "Medium", "Tight", "VTight"            } },
  { 6, {                        "VLoose", "Loose", "Medium", "Tight", "VTight", "VVTight" } },
  { 7, {             "VVLoose", "VLoose", "Loose", "Medium", "Tight", "VTight", "VVTight" } },
  { 8, { "VVVLoose", "VVLoose", "VLoose", "Loose", "Medium", "Tight", "VTight", "VVTight" } },
};

const std::map<TauID, std::string> TauID_names = {
  { TauID::MVAnewDM2017v2,     "MVAnewDM2017v2"     },
  { TauID::MVAoldDM,           "MVAoldDM"           },
  { TauID::MVAoldDMdR032017v2, "MVAoldDMdR032017v2" },
  { TauID::MVAoldDM2017v1,     "MVAoldDM2017v1"     },
  { TauID::MVAoldDM2017v2,     "MVAoldDM2017v2"     },
  { TauID::DeepTau2017v2VSe,   "DeepTau2017v2VSe"   },
  { TauID::DeepTau2017v2VSmu,  "DeepTau2017v2VSmu"  },
  { TauID::DeepTau2017v2VSjet, "DeepTau2017v2VSjet" },
};

// NB! must be exactly 7 characters!
const std::map<std::string, TauID> TauID_PyMap = {
  { "dR03mva", TauID::MVAoldDMdR032017v2 },
  { "dR05mva", TauID::MVAoldDM2017v2     },
  { "deepVSj", TauID::DeepTau2017v2VSjet },
};

enum class EGammaID {
  Fall17V1noIso, Fall17V1Iso,
  Fall17V2noIso, Fall17V2Iso,
};

enum class EGammaWP {
  WP90, WP80, WPL
};

// read only Fall17V2noIso
const std::map<EGammaID, std::string> EGammaID_map = {
//  { EGammaID::Fall17V1noIso, "mvaFall17V1noIso" },
//  { EGammaID::Fall17V1Iso,   "mvaFall17V1Iso"   },
  { EGammaID::Fall17V2noIso, "mvaFall17V2noIso" },
//  { EGammaID::Fall17V2Iso,   "mvaFall17V2Iso"   },
};

const std::map<EGammaWP, std::string> EGammaWP_map = {
  { EGammaWP::WP90, "WP90" },
  { EGammaWP::WP80, "WP80" },
  { EGammaWP::WPL,  "WPL"  },
};

//--- declare b-tagging working points

enum class BtagWP { kLoose, kMedium, kTight };

const std::map<int, std::map<Btag, std::map<BtagWP, double>>> BtagWP_map = {
  {
    kEra_2016, {
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
      {
        Btag::kDeepJet, {
          { BtagWP::kLoose,  0.0614 },
          { BtagWP::kMedium, 0.3093 },
          { BtagWP::kTight,  0.7221 },
        },
      },
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
      {
        Btag::kDeepCSV, {
          { BtagWP::kLoose,  0.2217 },
          { BtagWP::kMedium, 0.6321 },
          { BtagWP::kTight,  0.8953 },
        }
      },
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
      {
        Btag::kCSVv2, {
          { BtagWP::kLoose,  0.5426 },
          { BtagWP::kMedium, 0.8484 },
          { BtagWP::kTight,  0.9535 },
        },
      },
    },
  },
  {
    kEra_2017, {
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      {
        Btag::kDeepJet, {
          { BtagWP::kLoose,  0.0521 },
          { BtagWP::kMedium, 0.3033 },
          { BtagWP::kTight,  0.7489 },
        },
      },
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      {
        Btag::kDeepCSV, {
          { BtagWP::kLoose,  0.1522 },
          { BtagWP::kMedium, 0.4941 },
          { BtagWP::kTight,  0.8001 },
        },
      },
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      {
        Btag::kCSVv2, {
          { BtagWP::kLoose,  0.5803 },
          { BtagWP::kMedium, 0.8838 },
          { BtagWP::kTight,  0.9693 },
        },
      },
    },
  },
  {
    kEra_2018, {
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
      {
        Btag::kDeepJet, {
          { BtagWP::kLoose,  0.0494 },
          { BtagWP::kMedium, 0.2770 },
          { BtagWP::kTight,  0.7264 },
        },
      },
//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
      {
        Btag::kDeepCSV, {
          { BtagWP::kLoose,  0.1241 },
          { BtagWP::kMedium, 0.4184 },
          { BtagWP::kTight,  0.7527 },
        },
      },
    },
  },
};

double
get_BtagWP(int era,
           Btag btag,
           BtagWP wp);

//--- selector class
template <typename ObjectType>
std::vector<ObjectType>
selectObjects(int objectSelection,
              const std::vector<ObjectType> & fakeableObjects,
              const std::vector<ObjectType> & tightObjects)
{
  switch(objectSelection)
  {
    case kFakeable: return fakeableObjects;
    case kTight:    return tightObjects;
    default:        throw cmsException(__func__, __LINE__) << "Invalid selection: " << objectSelection;
  }
}

//--- selector class
template <typename ObjectType>
std::vector<ObjectType>
selectObjects(int objectSelection,
              const std::vector<ObjectType> & preselObjects,
              const std::vector<ObjectType> & fakeableObjects,
              const std::vector<ObjectType> & tightObjects)
{
  switch(objectSelection)
  {
    case kLoose:    return preselObjects;
    case kFakeable: return fakeableObjects;
    case kTight:    return tightObjects;
    default:        throw cmsException(__func__, __LINE__) << "Invalid selection: " << objectSelection;
  }
}

int
get_selection(const std::string & selectionString);

int
get_era(const std::string & eraString);

std::string
get_era(int era);

TauID
get_tau_id_enum(const std::string & tauId_str);

int
get_tau_id_wp_int(const std::string & tauId_str);

int
get_tau_id_wp_int(TauID tauID,
                  const std::string & wp_str);

std::string
get_tau_id_wp_str(TauID tauID,
                  int wp_int);

double
min_Deta_fwdJet_jet(Particle::LorentzVector FwdJet, std::vector<const RecoJet *> selJets);

Particle::LorentzVector
HighestEtaFwdJet(std::vector<const RecoJet *> selJetsForward);

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool
isHigherPt(const Particle * particle1,
           const Particle * particle2);

template <typename T>
bool
isHigherPtT(const T & particle1,
            const T & particle2)
{
  return particle1.pt() > particle2.pt();
}

/**
 * @brief Auxiliary function used for sorting leptons by decreasing cone pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher cone pT; false if second lepton has higher cone pT
 */
bool
isHigherConePt(const RecoLepton * particle1,
               const RecoLepton * particle2);

/**
 * @brief Auxiliary function for sorting a collection of RecoJet pointers
 *        by their b-tagging CSV score
 * @param jet1 The first jet
 * @param jet2 The second jet
 * @return True, if the 1st jet has higher CSV score
 */
bool
isHigherCSV(const RecoJet * jet1,
            const RecoJet * jet2);

bool
isHigherCSV_ak8(const RecoJetAK8 * jet1,
                const RecoJetAK8 * jet2);

/**
 * @brief Auxiliary function for checking if leptons passing fake-able lepton selection
 *        pass tight lepton identification criteria also
 */
template <typename Tfakeable, typename Ttight>
bool
isMatched(const Tfakeable & fakeableLepton,
          const std::vector<Ttight *> & tightLeptons,
          double dRmax = 1.e-2)
{
  for(const Ttight * tightLepton: tightLeptons)
  {
    const double dR = deltaR(
      fakeableLepton.eta(), fakeableLepton.phi(), tightLepton->eta(), tightLepton->phi()
    );
    if(dR < dRmax)
    {
      return true; // found match
    }
  }
  return false; // no match found
}

/**
 * @brief Return first N objects from collection given as function argument. In case the input
 *        collection contains fewer than N objects, the whole input collection is returned
 */
template <typename T>
std::vector<T>
pickFirstNobjects(const std::vector<T> & objects_input,
                  std::size_t N)
{
  const std::size_t N_input = std::min(objects_input.size(), N);
  std::vector<T> objects_output;
  std::copy_n(objects_input.begin(), N_input, std::back_inserter(objects_output));
  return objects_output;
}

template <typename T,
          typename U,
          typename F>
std::vector<T>
getIntersection(const std::vector<T> & lhs_collection,
                const std::vector<U> & rhs_collection,
                bool (*sortFunction)(const F *, const F *))
{
  std::vector<T> output_collection;
  for(const T & lhs_element: lhs_collection)
  {
    for(const U & rhs_element: rhs_collection)
    {
      if(lhs_element == rhs_element)
      {
        output_collection.push_back(lhs_element);
      }
    }
  }
  std::sort(output_collection.begin(), output_collection.end(), sortFunction);
  return output_collection;
}

int
getHadTau_genPdgId(const RecoHadTau * hadTau);

double
get_BtagWeight(const std::vector<const RecoJet *> & jets);

double
get_BtagWeight(const std::vector<const RecoJet *> & jets,
               int central_or_shift);

double
get_EWK_jet_weight(const std::vector<const RecoJet *> & jets,
                   EWKJetSys ewk_jet_option);

double
get_EWK_bjet_weight(const std::vector<const RecoJet *> & bjets,
                    EWKBJetSys ewk_bjet_option);

/**
 * @brief Compute MHT
 */
math::PtEtaPhiMLorentzVector
compMHT(const std::vector<const RecoLepton *> & leptons,
        const std::vector<const RecoHadTau *> & hadTaus,
        const std::vector<const RecoJet *> & jets);

/**
 * @brief Compute linear discriminator based on MET and MHT
 */
double
compMEt_LD(const math::PtEtaPhiMLorentzVector & met_p4,
           const math::PtEtaPhiMLorentzVector & mht_p4);

/**
 * @brief Compute scalar HT observable
 */

template <typename T>
double
compHT(const std::vector<const RecoLepton *> & leptons,
       const std::vector<const RecoHadTau *> & hadTaus,
       const std::vector<const T *> & jets)
{
  double ht = 0.;
  for(const RecoLepton * lepton: leptons)
  {
    ht += lepton->pt();
  }
  for(const RecoHadTau * hadTau: hadTaus)
  {
    ht += hadTau->pt();
  }
  for(const T * jet: jets)
  {
    ht += jet->pt();
  }
  return ht;
}

/**
 * @brief Compute STMET observable (used in e.g. EXO-17-016 paper)
 */

template <typename T>
double
compSTMEt(const std::vector<const RecoLepton *> & leptons,
          const std::vector<const RecoHadTau *> & hadTaus,
          const std::vector<const T *> & jets,
          const Particle::LorentzVector & met_p4)
{
  double stmet = compHT(leptons, hadTaus, jets) + met_p4.pt();
  return stmet;
}

/**
 * @brief Compute Smin (= mT) observable, as defined in the paper
 *        "Measuring the triple Higgs self-interaction at the Large Hadron Collider";
 *        J.H. Kim, K. Kong, K.T. Matchev, M. Park; arXiv: 1807.11498
 */
double
comp_Smin(const Particle::LorentzVector & visP4,
          double metPx,
          double metPy);

/**
 * @brief Set flags indicating whether or not lepton passes loose, fakeable and/or tight selection criteria
 */
template <typename T>
void
set_selection_flags(std::vector<const T *> & leptons,
                    int selection)
{
  for(const T * lepton: leptons)
  {
    switch (selection) {
      case kLoose:    lepton->set_isLoose();    break;
      case kFakeable: lepton->set_isFakeable(); break;
      case kTight:    lepton->set_isTight();    break;
      default:        assert(0);
    }
  }
}

/**
 * @brief Build collection of selected leptons by merging collections of selected electrons and selected muons
 */
std::vector<const RecoLepton *>
mergeLeptonCollectionsNoSort(const std::vector<const RecoElectron *> & electrons,
                             const std::vector<const RecoMuon *> & muons);

std::vector<const RecoLepton *>
mergeLeptonCollections(const std::vector<const RecoElectron *> & electrons,
                       const std::vector<const RecoMuon *> & muons);

template <typename T>
std::vector<const RecoLepton *>
mergeLeptonCollections(const std::vector<const RecoElectron *> & electrons,
                       const std::vector<const RecoMuon *> & muons,
                       bool (*sortFunction)(const T *, const T *))
{
  std::vector<const RecoLepton *> leptons = mergeLeptonCollectionsNoSort(electrons, muons);
  std::sort(leptons.begin(), leptons.end(), sortFunction);
  return leptons;
}

template <typename T,
          typename = typename std::enable_if<std::is_base_of<Particle, T>::value>::type>
std::vector<const T *>
subtractCollections(const std::vector<const T *> & minuend,
                    const std::vector<const T *> & subtrahend)
{
  std::vector<const T *> difference;
  for(const T * element: minuend)
  {
    if(std::find(subtrahend.cbegin(), subtrahend.cend(), element) == subtrahend.cend())
    {
      difference.push_back(element);
    }
  }
  return difference;
}

template <typename T,
          typename = typename std::enable_if<! std::is_pointer<T>::value>>
void
printCollection(const std::string & collection_name,
                const std::vector<T> & collection)
{
  std::cout << " (#" << collection_name << " = " << collection.size() << ")\n";
  for(std::size_t idx = 0; idx < collection.size(); ++idx)
  {
    std::cout << collection_name << " #" << idx << ": " << collection[idx] << "\n";
  }
}

template <typename T,
          typename = typename std::enable_if<! std::is_pointer<T>::value>>
void
printCollection(const std::string & collection_name,
                const std::vector<const T *> & collection)
{
  std::cout << " (#" << collection_name << " = " << collection.size() << ")\n";
  for(std::size_t idx = 0; idx < collection.size(); ++idx)
  {
    std::cout << collection_name << " #" << idx << ": " << *(collection[idx]) << "\n";
  }
}

/**
 * @brief Count number of reconstructed electrons, muons, and hadronic taus that are due to misidentified quark or gluon jets
 */
int
countFakeElectrons(const std::vector<const RecoLepton *> & leptons);
int
countFakeMuons(const std::vector<const RecoLepton *> & leptons);
int
countFakeHadTaus(const std::vector<const RecoHadTau *> & hadTaus);

/**
 * @brief Count number of reconstructed electrons, muons, hadronic taus, or jets that pass given pT cut
 */
template <typename T>
int
countHighPtObjects(const std::vector<T*>& objects, double pTmin)
{
  int numHighPtObjects = 0;
  for ( typename std::vector<T*>::const_iterator object = objects.begin();
        object != objects.end(); ++object ) {
    if ( (*object)->pt() > pTmin ) ++numHighPtObjects;
  }
  return numHighPtObjects;
}

/**
 * @brief Computes the number of k combinations out of n
 * @param n Number of instances to choose from
 * @param k Length of a single combination
 *
 * Credit to the author of: https://stackoverflow.com/a/9331125
 */
int
nCombinationsK(int n,
               int k);

/**
 * @brief Converts enum class value to corresponding integer value
 *        which is determined by the order in which the enums are declared
 * @param value Enum class value
 * @return Corresponding integer value
 *
 * Taken from: https://stackoverflow.com/a/11421471
 */
template <typename Enumeration>
auto as_integer(Enumeration const value)
  -> typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

/**
 * @brief Count number of trigger objects of given type and passing given pT threshold
 * @param Id type
 * @param min_l1pt pT threshold
 * @return Number of trigger objects passing selection
 */
int
countTrigObjs_passingL1(const std::vector<TrigObj> & trigObjs,
                        int Id,
                        double min_l1pt,
                        double min_l1pt_2 = -1.);

/**
 * @brief Check if a certain string is contained in a given vector of strings
 */
bool
contains(const std::vector<std::string> & list_of_strings,
         const std::string & keyWord);

/**
 * @brief Find file using FileInPatch mechanism
 */
std::string
findFile(const std::string & fileName);

bool
isSFOS(const std::vector<const RecoLepton *> & leptons);

bool
isfailsLowMassVeto(const std::vector<const RecoLepton *> & preselLeptons);

double
massL(const std::vector<const RecoLepton *> & Leptons);

bool
isfailsZbosonMassVeto(const std::vector<const RecoLepton *> & preselLeptons,
                      bool ignoreOS = false);

int
countZbosonSFOSpairs(const std::vector<const RecoLepton *> & preselLeptons,
                     bool ignoreOS = false);

bool
isfailsHtoZZVeto(const std::vector<const RecoLepton *> & preselLeptons);

std::string
get_key_hist(const EventInfo & eventInfo,
             const std::vector<GenParticle> & genWBosons,
             bool isMC_HH,
             bool isMC_VH,
             bool isDebug = false);

std::vector<std::string>
get_key_list_hist(const EventInfo & eventInfo,
                  bool isMC_HH,
                  bool isMC_VH);

std::string
get_prefix(const std::string & process_string,
           bool isMC_tH,
           bool isMC_HH,
           bool isMC_H,
           bool isMC_VH);

std::vector<std::pair<std::string, int>>
get_htxs_binning(bool isMC_ttH);

/**
 * @brief Find generator-level jets produced in W->jj decay
 *
 * This function is used for the HH->multilepton and HH->bbWW analyses, *not* for the ttH analysis.
 * Its code is put into the tthAnalysis/HiggsToTauTau package to avoid that the packages
 * hhAnalysis/multilepton and hhAnalysis/bbww depend on each other.
 *
 */
template<typename T>
std::pair<const T *, const T *>
findGenJetsFromWBoson(const GenParticle& genWBoson,
                      const std::vector<T> & genJets)
{
  const T * genJet1FromWBoson = nullptr;
  const T * genJet2FromWBoson = nullptr;
  double minDeltaMass = 1.e+3;

  for(typename std::vector<T>::const_iterator genJet1 = genJets.begin(); genJet1 != genJets.end(); ++genJet1)
  {
    for(typename std::vector<T>::const_iterator genJet2 = genJet1 + 1; genJet2 != genJets.end(); ++genJet2)
    {
      const Particle::LorentzVector genDijetP4 = genJet1->p4() + genJet2->p4();
      const double deltaMass = TMath::Abs(genDijetP4.mass() - genWBoson.mass());
      const double dR = deltaR(genDijetP4, genWBoson.p4());
      if(deltaMass < 5. && deltaMass < minDeltaMass && dR < 1.)
      {
        genJet1FromWBoson = &(*genJet1);
        genJet2FromWBoson = &(*genJet2);
        minDeltaMass = deltaMass;
      }
    }
  }
  return std::pair<const T*, const T*>(genJet1FromWBoson, genJet2FromWBoson);
}

/**
 * @brief Convert collection of GenLepton, GenHadTau, or GenPhoton objects to collection of GenParticle base-class
 *
 * This function is used to write collections of GenLepton, GenHadTau, or GenPhoton objects to an Ntuple file
 *
 */
template<typename T>
std::vector<GenParticle>
convert_to_genParticles(const std::vector<T>& genParticles_derived)
{
  std::vector<GenParticle> genParticles_base;
  for ( typename std::vector<T>::const_iterator genParticle = genParticles_derived.begin(); genParticle != genParticles_derived.end(); ++genParticle )
  {
    genParticles_base.push_back(*genParticle);
  }
  return genParticles_base;
}

/**
 * @brief Convert collection of RecoJet pointers to collection of pointers to RecoJetBase base-class
 *
 */
std::vector<const RecoJetBase*>
convert_to_RecoJetBase(const std::vector<const RecoJet*>& jets_derived);

double
clip(double value,
     double min_value = -10.,
     double max_value = 10.);

#endif
