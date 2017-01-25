#ifndef NTUPLEFILLERUNITS_H
#define NTUPLEFILLERUNITS_H

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TypeTraits.h" // Traits<>
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_*, LUMI_*, EVT_*

#include <Rtypes.h> // *_t types
#include <TTree.h> // TTree
#include <TString.h> // TString, Form()
#include <TBranch.h> // TBranch

#include <type_traits> // std::enable_if<>, std::is_floating_point<>
#include <string> // std::string
#include <map> // std::map<,>
#include <iostream> // std::cerr
#include <sstream> // std::stringstream

#define PLACEHOLDER -9999

/**
  * @file Provides a bunch of structs (,,units'') which can be used
  *       to fill a given tree w/ Ntuples
  */

/* ************************ helper structs **************************** */

/**
 * @brief Holds run, luminosity and event numbers
 */
struct RLEUnit
{
  RLEUnit()
    : run_(0)
    , lumi_(0)
    , evt_(0)
  {}
  RLEUnit(RUN_TYPE  run,
          LUMI_TYPE lumi,
          EVT_TYPE  evt)
    : run_(run)
    , lumi_(lumi)
    , evt_(evt)
  {}

  std::string
  get_str() const
  {
    std::stringstream ss;
    ss << run_ << ':' << lumi_ << ':' << evt_;
    return ss.str();
  }

  RUN_TYPE  run_;
  LUMI_TYPE lumi_;
  EVT_TYPE  evt_;
};

/**
 * @brief Holds MET information (optionally covariance matrix)
 *
 * Note that the template type can only be a floating point type
 */
template<typename FloatType,
         typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct METUnit
{
  METUnit()
    : pt_(PLACEHOLDER)
    , phi_(PLACEHOLDER)
    , covXX_(PLACEHOLDER)
    , covXY_(PLACEHOLDER)
    , covYY_(PLACEHOLDER)
    , useCov_(false)
  {}
  METUnit(FloatType pt,
          FloatType phi)
    : pt_(pt)
    , phi_(phi)
    , covXX_(PLACEHOLDER)
    , covXY_(PLACEHOLDER)
    , covYY_(PLACEHOLDER)
    , useCov_(false)
  {}
  METUnit(FloatType pt,
          FloatType phi,
          FloatType covXX,
          FloatType covXY,
          FloatType covYY,
          bool useCov = true)
    : pt_(pt)
    , phi_(phi)
    , covXX_(covXX)
    , covXY_(covXY)
    , covYY_(covYY)
    , useCov_(useCov)
  {}

  FloatType pt_;
  FloatType phi_;
  FloatType covXX_;
  FloatType covXY_;
  FloatType covYY_;
  const bool useCov_;
};

/* ************************ filler structs **************************** */

template <typename NumberType,
          typename = typename std::enable_if<std::is_arithmetic<NumberType>::value>::type>
struct BasicFiller
{
  BasicFiller()
    : branchName_("")
    , var_(PLACEHOLDER)
    , varPtr_(0)
    , branch_(0)
  {}
  BasicFiller(const std::string & branchName)
    : branchName_(branchName)
    , var_(PLACEHOLDER)
    , varPtr_(0)
    , branch_(0)
  {}
  ~BasicFiller()
  {
    branch_ = 0;
  }

  void
  setBranchName(const std::string & branchName)
  {
    branchName_ = branchName;
  }

  void
  setValuePtr(const NumberType * varPtr)
  {
    var_ = (*varPtr);
    varPtr_ = &var_;
  }

  void
  setValuePtr(NumberType var)
  {
    var_ = var;
    varPtr_ = &var_;
  }

  int
  initBranch(TTree * tree)
  {
    if(branchName_.empty()) return 1;
    if(! tree)              return 2;

    if(! varPtr_)
      varPtr_ = &var_;
    branch_ = tree -> Branch(
      branchName_.c_str(), varPtr_, Form("%s/%s", branchName_.c_str(), Traits<NumberType>::TYPE_NAME)
    );
    return 0;
  }

  template <typename OtherType>
  void
  setValue(OtherType val)
  {
    var_ = static_cast<NumberType>(val);
  }

  std::string branchName_;
  NumberType var_;
  NumberType * varPtr_;
  TBranch * branch_;
};

struct RLEFiller
{
  RLEFiller()
    : unitPtr_(0)
  {}
  RLEFiller(RLEUnit * unitPtr)
    : unitPtr_(unitPtr)
  {}

  int
  initBranches(TTree * tree)
  {
    run_ = BasicFiller<RUN_TYPE>(RUN_KEY);
    lumi_ = BasicFiller<LUMI_TYPE>(LUMI_KEY);
    evt_ = BasicFiller<EVT_TYPE>(EVT_KEY);
    if(unitPtr_)
    {
      run_.setValuePtr(unitPtr_ -> run_);
      lumi_.setValuePtr(unitPtr_ -> lumi_);
      evt_.setValuePtr(unitPtr_ -> evt_);
    }
    int err = 0;
    err |= (run_.initBranch(tree) << 0);
    err |= (lumi_.initBranch(tree) << 1);
    err |= (evt_.initBranch(tree) << 2);
    return err;
  }

  void
  setValues(const RLEUnit & unit)
  {
    run_.setValue(unit.run_);
    lumi_.setValue(unit.lumi_);
    evt_.setValue(unit.evt_);
  }

  void
  setPtr(RLEUnit * unitPtr)
  {
    unitPtr_ = unitPtr;
  }

  BasicFiller<RUN_TYPE>  run_;
  BasicFiller<LUMI_TYPE> lumi_;
  BasicFiller<EVT_TYPE>  evt_;

  RLEUnit * unitPtr_;
};

template <typename FloatType,
          typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct METFiller
{
  METFiller(bool useCov)
    : unitPtr_(0)
    , useCov_(useCov)
  {}

  METFiller(METUnit<FloatType> * unitPtr)
    : unitPtr_(unitPtr)
    , useCov_(unitPtr_ ? unitPtr_ -> useCov_ : false)
  {}

  int
  initBranches(TTree * tree)
  {
    pt_ = BasicFiller<FloatType>("met_pt");
    phi_ = BasicFiller<FloatType>("met_phi");
    if(useCov_)
    {
      covXX_ = BasicFiller<FloatType>("met_covXX");
      covXY_ = BasicFiller<FloatType>("met_covXY");
      covYY_ = BasicFiller<FloatType>("met_covYY");
    }

    if(unitPtr_)
    {
      pt_.setValuePtr(unitPtr_ -> pt_);
      phi_.setValuePtr(unitPtr_ -> phi_);
      if(useCov_)
      {
        covXX_.setValuePtr(unitPtr_ -> covXX_);
        covXY_.setValuePtr(unitPtr_ -> covXY_);
        covYY_.setValuePtr(unitPtr_ -> covYY_);
      }
    }

    int err = 0;
    err |= (pt_.initBranch(tree) << 0);
    err |= (phi_.initBranch(tree) << 1);
    if(useCov_)
    {
      err |= (covXX_.initBranch(tree) << 2);
      err |= (covXY_.initBranch(tree) << 3);
      err |= (covYY_.initBranch(tree) << 4);
    }
    return err;
  }

  template<typename OtherType,
           typename = typename std::enable_if<std::is_floating_point<OtherType>::value>::type>
  void
  setValues(const METUnit<OtherType> & unit)
  {
    pt_.setValue(unit.pt_);
    phi_.setValue(unit.phi_);
    covXX_.setValue(unit.covXX_);
    covXY_.setValue(unit.covXY_);
    covYY_.setValue(unit.covYY_);
  }

  void
  setPtr(METUnit<FloatType> * unitPtr)
  {
    unitPtr_ = unitPtr;
    if(unitPtr_)
      useCov_ = unitPtr_ -> useCov_;
  }

  BasicFiller<FloatType> pt_;
  BasicFiller<FloatType> phi_;
  BasicFiller<FloatType> covXX_;
  BasicFiller<FloatType> covXY_;
  BasicFiller<FloatType> covYY_;

  METUnit<FloatType> * unitPtr_;
  bool useCov_;
};

template <typename FloatType,
          typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct GenParticleFiller
{
  GenParticleFiller()
    : particle_(0)
  {}
  GenParticleFiller(const std::string & name)
    : pt_(Form("%s_%s", name.c_str(), "pt"))
    , eta_(Form("%s_%s", name.c_str(), "eta"))
    , phi_(Form("%s_%s", name.c_str(), "phi"))
    , mass_(Form("%s_%s", name.c_str(), "mass"))
    , particle_(0)
  {}
  GenParticleFiller(const std::string & name,
                    GenParticle * particle)
    : pt_(Form("%s_%s", name.c_str(), "pt"))
    , eta_(Form("%s_%s", name.c_str(), "eta"))
    , phi_(Form("%s_%s", name.c_str(), "phi"))
    , mass_(Form("%s_%s", name.c_str(), "mass"))
    , particle_(particle)
  {}

  int
  initBranches(TTree * tree)
  {
    if(particle_)
    {
      pt_.setValuePtr(particle_ -> pt());
      eta_.setValuePtr(particle_ -> eta());
      phi_.setValuePtr(particle_ -> phi());
      mass_.setValuePtr(particle_ -> mass());
    }

    int err = 0;
    err |= (pt_.initBranch(tree) << 0);
    err |= (eta_.initBranch(tree) << 1);
    err |= (phi_.initBranch(tree) << 2);
    err |= (mass_.initBranch(tree) << 3);
    return err;
  }

  void
  setValues(const GenParticle & particle)
  {
    pt_.setValue(particle.pt());
    eta_.setValue(particle.eta());
    phi_.setValue(particle.phi());
    mass_.setValue(particle.mass());
  }

  void
  setPtr(GenParticle * particle)
  {
    particle_ = particle;
  }

  void
  setBranchName(const std::string & name)
  {
    pt_.setBranchName(Form("%s_%s", name.c_str(), "pt"));
    eta_.setBranchName(Form("%s_%s", name.c_str(), "eta"));
    phi_.setBranchName(Form("%s_%s", name.c_str(), "phi"));
    mass_.setBranchName(Form("%s_%s", name.c_str(), "mass"));
  }

protected:
  BasicFiller<FloatType> pt_;
  BasicFiller<FloatType> eta_;
  BasicFiller<FloatType> phi_;
  BasicFiller<FloatType> mass_;

  GenParticle * particle_;
};

template <typename FloatType,
          typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct GenLeptonFiller
  : public GenParticleFiller<FloatType>
{
  GenLeptonFiller()
    : GenParticleFiller<FloatType>()
    , lepton_(0)
  {}
  GenLeptonFiller(const std::string & name)
    : GenParticleFiller<FloatType>(name)
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , pdgId_(Form("%s_%s", name.c_str(), "pdgId"))
    , lepton_(0)
  {}
  GenLeptonFiller(const std::string & name,
                  GenLepton * lepton)
    : GenParticleFiller<FloatType>(name, static_cast<GenParticle *>(lepton))
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , pdgId_(Form("%s_%s", name.c_str(), "pdgId"))
    , lepton_(lepton)
  {}

  int
  initBranches(TTree * tree)
  {
    if(lepton_)
    {
      charge_.setValuePtr(lepton_ -> charge());
      pdgId_.setValuePtr(lepton_ -> pdgId());
    }

    int err = GenParticleFiller<FloatType>::initBranches(tree);
    err |= (charge_.initBranch(tree) << 4);
    err |= (pdgId_.initBranch(tree) << 5);
    return err;
  }

  void
  setValues(const GenLepton & lepton)
  {
    GenParticleFiller<FloatType>::setValues(static_cast<const GenParticle &>(lepton));
    charge_.setValue(lepton.charge());
    pdgId_.setValue(lepton.pdgId());
  }

  void
  setPtr(GenLepton * lepton)
  {
    GenParticleFiller<FloatType>::setPtr(static_cast<GenParticle *>(lepton));
    lepton_ = lepton;
  }

  void
  setBranchName(const std::string & name)
  {
    GenParticleFiller<FloatType>::setBranchName(name);
    charge_.setBranchName(Form("%s_%s", name.c_str(), "charge"));
    pdgId_.setBranchName(Form("%s_%s", name.c_str(), "pdgId"));
  }

protected:
  BasicFiller<Int_t> charge_;
  BasicFiller<Int_t> pdgId_;

  GenLepton * lepton_;
};

template <typename FloatType,
          typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct RecoHadTauFiller
  : public GenParticleFiller<FloatType>
{
  RecoHadTauFiller()
    : GenParticleFiller<FloatType>()
    , hadTau_(0)
  {}
  RecoHadTauFiller(const std::string & name)
    : GenParticleFiller<FloatType>(name)
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , decayMode_(Form("%s_%s", name.c_str(), "decayMode"))
    , hadTau_(0)
  {}
  RecoHadTauFiller(const std::string & name,
                  RecoHadTau * hadTau)
    : GenParticleFiller<FloatType>(name, static_cast<GenParticle *>(hadTau))
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , decayMode_(Form("%s_%s", name.c_str(), "decayMode"))
    , hadTau_(hadTau)
  {}

  int
  initBranches(TTree * tree)
  {
    if(hadTau_)
    {
      charge_.setValuePtr(hadTau_ -> charge());
      decayMode_.setValuePtr(hadTau_ -> decayMode());
    }

    int err = GenParticleFiller<FloatType>::initBranches(tree);
    err |= (charge_.initBranch(tree) << 4);
    err |= (decayMode_.initBranch(tree) << 5);
    return err;
  }

  void
  setValues(const RecoHadTau & hadTau)
  {
    GenParticleFiller<FloatType>::setValues(static_cast<const GenParticle &>(hadTau));
    charge_.setValue(hadTau.charge());
    decayMode_.setValue(hadTau.decayMode());
  }

  void
  setPtr(RecoHadTau * hadTau)
  {
    GenParticleFiller<FloatType>::setPtr(static_cast<GenParticle *>(hadTau));
    hadTau_ = hadTau;
  }

  void
  setBranchName(const std::string & name)
  {
    GenParticleFiller<FloatType>::setBranchName(name);
    charge_.setBranchName(Form("%s_%s", name.c_str(), "charge"));
    decayMode_.setBranchName(Form("%s_%s", name.c_str(), "decayMode"));
  }

protected:
  BasicFiller<Int_t> charge_;
  BasicFiller<Int_t> decayMode_;

  RecoHadTau * hadTau_;
};

template <typename FloatType,
          typename = typename std::enable_if<std::is_floating_point<FloatType>::value>::type>
struct GenHadTauFiller
  : public GenParticleFiller<FloatType>
{
  GenHadTauFiller()
    : GenParticleFiller<FloatType>()
    , genHadTau_(0)
  {}
  GenHadTauFiller(const std::string & name)
    : GenParticleFiller<FloatType>(name)
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , genHadTau_(0)
  {}
  GenHadTauFiller(const std::string & name,
                  GenHadTau * genHadTau)
    : GenParticleFiller<FloatType>(name, static_cast<GenParticle *>(genHadTau))
    , charge_(Form("%s_%s", name.c_str(), "charge"))
    , genHadTau_(genHadTau)
  {}

  int
  initBranches(TTree * tree)
  {
    if(genHadTau_)
      charge_.setValuePtr(genHadTau_ -> charge());

    int err = GenParticleFiller<FloatType>::initBranches(tree);
    err |= (charge_.initBranch(tree) << 4);
    return err;
  }

  void
  setValues(const GenHadTau & genHadTau)
  {
    GenParticleFiller<FloatType>::setValues(static_cast<const GenParticle &>(genHadTau));
    charge_.setValue(genHadTau.charge());
  }

  void
  setPtr(GenHadTau * genHadTau)
  {
    GenParticleFiller<FloatType>::setPtr(static_cast<GenParticle *>(genHadTau));
    genHadTau_ = genHadTau;
  }

  void
  setBranchName(const std::string & name)
  {
    GenParticleFiller<FloatType>::setBranchName(name);
    charge_.setBranchName(Form("%s_%s", name.c_str(), "charge"));
  }

protected:
  BasicFiller<Int_t> charge_;

  GenHadTau * genHadTau_;
};

template <typename NumberType,
          typename = typename std::enable_if<std::is_arithmetic<NumberType>::value>::type>
struct MapFiller
{
  MapFiller() = default;
  MapFiller(const std::map<std::string, std::string> & branchNameMap)
    : branchNameMap_(branchNameMap)
  {}

  void
  setBranchNameMap(const std::map<std::string, std::string> & branchNameMap)
  {
    branchNameMap_ = branchNameMap;
  }

  void
  setBranchNameMap(const std::vector<std::string> & branchNames)
  {
    for(const std::string & branchName: branchNames)
      branchNameMap_[branchName] = branchName;
  }

  int
  initBranches(TTree * tree)
  {
    int err = 0;
    int errShift = 0;
    for(const auto & kv: branchNameMap_)
    {
      map_[kv.first] = BasicFiller<NumberType>(kv.second);
      err |= (map_[kv.first].initBranch(tree) << errShift);
      ++errShift;
      // if err is non-zero, should we delete the entry from the map?
    }
    return map_.size() ? err : -1;
  }

  void
  setValues(const std::map<std::string, NumberType> & values)
  {
    for(const auto & kv: values)
      if(map_.count(kv.first))
        map_[kv.first].setValue(kv.second);
      else
        std::cerr << "No such key: " << kv.first << '\n';
  }

  std::map<std::string, BasicFiller<NumberType>> map_;
  std::map<std::string, std::string> branchNameMap_;
};

#endif // NTUPLEFILLERUNITS_H
