#ifndef tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_analysisAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h" // TrigObj

#include <DataFormats/Math/interface/deltaR.h> // deltaR()
#include <DataFormats/Math/interface/LorentzVector.h> // math::PtEtaPhiMLorentzVector

#include <vector> // std::vector<>
#include <map> // std::map<,>
#include <algorithm> // std::copy_n()
#include <type_traits> // std::underlying_type<>

// forward declarations
class Particle;
class RecoLepton;
class RecoJet;
class RecoHadTau;
class RecoMuon;
class RecoElectron;

//--- declare constants
const double z_mass   = 91.1876;
const double z_window = 10.;
const double met_coef =  0.6;
const double mht_coef =  0.4;

//--- declare data-taking periods
enum
{
  kEra_undefined, kEra_2016, kEra_2017, kEra_2018
};

//--- declare selection criteria for leptons and hadronic taus
enum { kLoose, kFakeable, kTight };

//--- declare b-tagging working points

enum class BtagWP { kLoose, kMedium, kTight };

//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
const std::map<BtagWP, double> BtagWP_CSV_2016 =
{
  { BtagWP::kLoose,  0.5426 },
  { BtagWP::kMedium, 0.8484 },
  { BtagWP::kTight,  0.9535 },
};

//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
const std::map<BtagWP, double> BtagWP_CSVv2_2017 =
{
  { BtagWP::kLoose,  0.5803 },
  { BtagWP::kMedium, 0.8838 },
  { BtagWP::kTight,  0.9693 },
};

//--- source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
const std::map<BtagWP, double> BtagWP_deepCSV_2017 =
{
  { BtagWP::kLoose,  0.1522 },
  { BtagWP::kMedium, 0.4941 },
  { BtagWP::kTight,  0.8001 },
};

double
get_BtagWP(int era,
           BtagWP wp);

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
    default:        throw cmsException(__func__) << "Invalid selection: " << objectSelection;
  }
}

int
get_selection(const std::string & selectionString);

int
get_era(const std::string & eraString);

//--- define the tau MVA ID WPs
const std::map<std::string, int>
id_mva_dr03_map = {
  { "dR03mvaVVLoose", 1 }, // custom WP with 95% signal efficiency, computed in RecoHadTauReader
  { "dR03mvaVLoose",  2 },
  { "dR03mvaLoose",   3 },
  { "dR03mvaMedium",  4 },
  { "dR03mvaTight",   5 },
  { "dR03mvaVTight",  6 },
  { "dR03mvaVVTight", 7 }
};

const std::map<std::string, int>
id_mva_dr05_map = {
  { "dR05isoLoose",  1 },
  { "dR05isoMedium", 2 },
  { "dR05isoTight",  3 }
};

/**
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
bool
isHigherPt(const Particle * particle1,
           const Particle * particle2);

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

double
compHT(const std::vector<const RecoLepton *> & leptons,
       const std::vector<const RecoHadTau *> & hadTaus,
       const std::vector<const RecoJet *> & jets);

/**
 * @brief Compute STMET observable (used in e.g. EXO-17-016 paper)
 */

double
compSTMEt(const std::vector<const RecoLepton *> & leptons,
	  const std::vector<const RecoHadTau *> & hadTaus,
	  const std::vector<const RecoJet *> & jets,
	  const Particle::LorentzVector & met_p4);

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
          typename = typename std::enable_if<! std::is_pointer<T>::value>>
void
printCollection(const std::string & collection_name,
                const std::vector<T> & collection)
{
  std::cout << " (#" << collection_name << " = " << collection.size() << ")\n";
  for(std::size_t idx = 0; idx < collection.size(); ++idx)
  {
    std::cout << collection_name << "  #" << idx << ":\n" << collection[idx];
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
    std::cout << collection_name << "  #" << idx << ":\n" << *(collection[idx]);
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
countTrigObjs_passingL1(const std::vector<TrigObj>& trigObjs, int Id, double min_l1pt, double min_l1pt_2 = -1.);

#endif
