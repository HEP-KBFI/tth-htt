#define _USE_MATH_DEFINES // M_PI

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE, std::abs()
#include <iostream> // std::cerr
#include <string> // std::string
#include <vector> // std::vector<>
#include <memory> // std::unique_ptr<>
#include <algorithm> // std::min(), std::remove_if(), std::sort()
#include <cmath> // std::fabs(), std::sqrt(), std::pow()
#include <unordered_map> // std::unordered_map<>
#include <array> // std::array<>
#include <utility> // std::pair<>

#include <boost/filesystem.hpp> // boost::filesystem::exists()

#ifndef DISABLE_BOOST_LOG
#include <boost/log/utility/setup/console.hpp> // boost::log::add_console_log(),
                                               // boost::log::keywords::format()
#include <boost/log/sources/severity_logger.hpp> // boost::log::sources::severity_logger<>
#include <boost/log/trivial.hpp> // boost::log::trivial::severity_level
#include <boost/log/attributes/clock.hpp> // boost::log::attributes::local_clock()
#endif

#include <boost/algorithm/string/predicate.hpp> // boost::iequals()

#include <Rtypes.h> // UInt_t, Long64_t
#include <TChain.h> // TChain
#include <TFile.h> // TFile
#include <TTree.h> // TTree

#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#ifdef PYTHON_CONFIG
#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#endif

#define MAX_NOBJS       32
#define NAN_PLACEHOLDER -9999

[[ noreturn ]] void
msg_exit(const std::string & msg)
{
  std::cerr << msg << "\n";
  std::exit(EXIT_FAILURE);
}

std::string
operator ""_s(const char * str,
              std::size_t)
{
  return std::string(str);
}

struct
FloatArray
{
  FloatArray() : arr(nullptr) {}
  FloatArray(Float_t _arr[MAX_NOBJS]) : arr(_arr) {}
  Float_t & operator[](Int_t idx) { return arr[idx]; }
  Float_t * arr;
};

struct
IntArray
{
  IntArray() : arr(nullptr) {}
  IntArray(Int_t _arr[MAX_NOBJS]) : arr(_arr) {}
  Int_t & operator[](Int_t idx) { return arr[idx]; }
  Int_t * arr;
};

struct
RecoObject
{
  RecoObject() = default;
  virtual ~RecoObject() {}
  RecoObject(Float_t _pt,
             Float_t _eta,
             Float_t _phi,
             Float_t _mass)
    : pt(_pt)
    , eta(_eta)
    , phi(_phi)
    , mass(_mass)
  {
    p4 = math::PtEtaPhiMLorentzVector(pt, eta, phi, mass);
    E = p4.E();
  }

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }

  bool
  overlaps(const RecoObject & other,
           double dR_min) const
  {
    return dR(other) < dR_min;
  }

  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t mass;

  math::PtEtaPhiMLorentzVector p4;
  Float_t E;

private:
  inline double
  dR(const RecoObject & other) const
  {
    const double d_eta = std::fabs(eta - other.eta);
    double d_phi = std::fabs(phi - other.phi);
    if(d_phi > static_cast<double>(M_PI))
      d_phi -= 2 * static_cast<double>(M_PI);
    return std::sqrt(std::pow(d_eta, 2) + std::pow(d_phi, 2));
  }
};

template<>
Float_t
RecoObject::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "pt"))  return pt;
  if(boost::iequals(key, "eta")) return eta;
  if(boost::iequals(key, "phi")) return phi;
  if(boost::iequals(key, "E"))   return E;
  return NAN_PLACEHOLDER;
}

bool
sort_by_pt(const RecoObject & o1,
        const RecoObject & o2)
{
  return o2.pt < o1.pt;
}

struct
Jet
  : public RecoObject
{
  Jet() = default;
  Jet(Float_t _pt,
      Float_t _eta,
      Float_t _phi,
      Float_t _mass,
      Float_t _btagCSV,
      Int_t   _idx)
    : RecoObject(_pt, _eta, _phi, _mass)
    , btagCSV(_btagCSV)
    , idx(_idx)
  {}

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }

  Float_t btagCSV;
  Int_t   idx;
};

template<>
Float_t
Jet::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "btagCSV") ||
     boost::iequals(key, "CSV"))       return btagCSV;
  return RecoObject::get<Float_t>(key);
}

struct
TauGood
  : public RecoObject
{
  TauGood() = default;
  TauGood(Float_t _pt,
          Float_t _eta,
          Float_t _phi,
          Float_t _mass,
          Int_t   _charge,
          Int_t   _idDecayMode,
          Int_t   _idDecayModeNewDMs,
          Float_t _dxy,
          Float_t _dz,
          Int_t   _idMVArun2dR03,
          Int_t   _idCI3hit,
          Int_t   _idCI3hitdR03,
          Int_t   _idAntiMu,
          Int_t   _idAntiErun2,
          Float_t _isoCI3hit)
    : RecoObject(_pt, _eta, _phi, _mass)
    , charge(_charge)
    , idDecayMode(_idDecayMode)
    , idDecayModeNewDMs(_idDecayModeNewDMs)
    , dxy(_dxy)
    , dz(_dz)
    , idMVArun2dR03(_idMVArun2dR03)
    , idCI3hit(_idCI3hit)
    , idCI3hitdR03(_idCI3hitdR03)
    , idAntiMu(_idAntiMu)
    , idAntiErun2(_idAntiErun2)
    , isoCI3hit(_isoCI3hit)
    , byLooseCombinedIsolationDeltaBetaCorr3Hits(0)
    , byMediumCombinedIsolationDeltaBetaCorr3Hits(0)
    , byTightCombinedIsolationDeltaBetaCorr3Hits(0)
    , byLooseCombinedIsolationDeltaBetaCorr3HitsdR03(0)
    , byMediumCombinedIsolationDeltaBetaCorr3HitsdR03(0)
    , byTightCombinedIsolationDeltaBetaCorr3HitsdR03(0)
    , byLooseIsolationMVArun2v1DBdR03oldDMwLT(0)
    , byMediumIsolationMVArun2v1DBdR03oldDMwLT(0)
    , byTightIsolationMVArun2v1DBdR03oldDMwLT(0)
    , byVTightIsolationMVArun2v1DBdR03oldDMwLT(0)
    , againstMuonLoose3(0)
    , againstMuonTight3(0)
    , againstElectronVLooseMVA6(0)
    , againstElectronLooseMVA6(0)
    , againstElectronMediumMVA6(0)
    , againstElectronTightMVA6(0)
  {
    if(idCI3hit >= 1) byLooseCombinedIsolationDeltaBetaCorr3Hits = 1;
    if(idCI3hit >= 2) byMediumCombinedIsolationDeltaBetaCorr3Hits = 1;
    if(idCI3hit >= 3) byTightCombinedIsolationDeltaBetaCorr3Hits = 1;

    if(idCI3hitdR03 >= 1) byLooseCombinedIsolationDeltaBetaCorr3HitsdR03 = 1;
    if(idCI3hitdR03 >= 2) byMediumCombinedIsolationDeltaBetaCorr3HitsdR03 = 1;
    if(idCI3hitdR03 >= 3) byTightCombinedIsolationDeltaBetaCorr3HitsdR03 = 1;

    if(idMVArun2dR03 >= 2) byLooseIsolationMVArun2v1DBdR03oldDMwLT = 1;
    if(idMVArun2dR03 >= 3) byMediumIsolationMVArun2v1DBdR03oldDMwLT = 1;
    if(idMVArun2dR03 >= 4) byTightIsolationMVArun2v1DBdR03oldDMwLT = 1;
    if(idMVArun2dR03 >= 5) byVTightIsolationMVArun2v1DBdR03oldDMwLT = 1;

    if(idAntiMu >= 1) againstMuonLoose3 = 1;
    if(idAntiMu >= 2) againstMuonTight3 = 1;

    if(idAntiErun2 >= 1) againstElectronVLooseMVA6 = 1;
    if(idAntiErun2 >= 2) againstElectronLooseMVA6 = 1;
    if(idAntiErun2 >= 3) againstElectronMediumMVA6 = 1;
    if(idAntiErun2 >= 4) againstElectronTightMVA6 = 1;
  }

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }

  Int_t   charge;
  Int_t   idDecayMode;
  Int_t   idDecayModeNewDMs;
  Float_t dxy;
  Float_t dz;
  Int_t   idMVArun2dR03;
  Int_t   idCI3hit;
  Int_t   idCI3hitdR03;
  Int_t   idAntiMu;
  Int_t   idAntiErun2;
  Float_t isoCI3hit;

  Int_t byLooseCombinedIsolationDeltaBetaCorr3Hits;
  Int_t byMediumCombinedIsolationDeltaBetaCorr3Hits;
  Int_t byTightCombinedIsolationDeltaBetaCorr3Hits;

  Int_t byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  Int_t byTightCombinedIsolationDeltaBetaCorr3HitsdR03;

  Int_t byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t byTightIsolationMVArun2v1DBdR03oldDMwLT;
  Int_t byVTightIsolationMVArun2v1DBdR03oldDMwLT;

  Int_t againstMuonLoose3;
  Int_t againstMuonTight3;

  Int_t againstElectronVLooseMVA6;
  Int_t againstElectronLooseMVA6;
  Int_t againstElectronMediumMVA6;
  Int_t againstElectronTightMVA6;
};

template<>
Float_t
TauGood::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "dxy"))                                   return dxy;
  if(boost::iequals(key, "dz"))                                    return dz;
  if(boost::iequals(key, "isoCI3hit") ||
     boost::iequals(key, "byCombinedIsolationDeltaBetaCorr3Hits")) return isoCI3hit;
  return RecoObject::get<Float_t>(key);
}

template<>
Int_t
TauGood::get<Int_t>(const std::string & key) const
{
  if(boost::iequals(key, "charge"))                                          return charge;
  if(boost::iequals(key, "idDecayMode") ||
     boost::iequals(key, "decayModeFindingOldDMs"))                          return idDecayMode;
  if(boost::iequals(key, "idDecayModeNewDMs") ||
     boost::iequals(key, "decayModeFindingNewDMs"))                          return idDecayModeNewDMs;
  if(boost::iequals(key, "byLooseCombinedIsolationDeltaBetaCorr3Hits"))      return byLooseCombinedIsolationDeltaBetaCorr3Hits;
  if(boost::iequals(key, "byMediumCombinedIsolationDeltaBetaCorr3Hits"))     return byMediumCombinedIsolationDeltaBetaCorr3Hits;
  if(boost::iequals(key, "byTightCombinedIsolationDeltaBetaCorr3Hits"))      return byTightCombinedIsolationDeltaBetaCorr3Hits;
  if(boost::iequals(key, "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03"))  return byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  if(boost::iequals(key, "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03")) return byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  if(boost::iequals(key, "byTightCombinedIsolationDeltaBetaCorr3HitsdR03"))  return byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  if(boost::iequals(key, "byLooseIsolationMVArun2v1DBdR03oldDMwLT"))         return byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  if(boost::iequals(key, "byMediumIsolationMVArun2v1DBdR03oldDMwLT"))        return byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  if(boost::iequals(key, "byTightIsolationMVArun2v1DBdR03oldDMwLT"))         return byTightIsolationMVArun2v1DBdR03oldDMwLT;
  if(boost::iequals(key, "byVTightIsolationMVArun2v1DBdR03oldDMwLT"))        return byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  if(boost::iequals(key, "againstMuonLoose3"))                               return againstMuonLoose3;
  if(boost::iequals(key, "againstMuonTight3"))                               return againstMuonTight3;
  if(boost::iequals(key, "againstElectronVLooseMVA6"))                       return againstElectronVLooseMVA6;
  if(boost::iequals(key, "againstElectronLooseMVA6"))                        return againstElectronLooseMVA6;
  if(boost::iequals(key, "againstElectronMediumMVA6"))                       return againstElectronMediumMVA6;
  if(boost::iequals(key, "againstElectronTightMVA6"))                        return againstElectronTightMVA6;
  return NAN_PLACEHOLDER;
}

struct
selLeptons
  : public RecoObject
{
  selLeptons() = default;
  selLeptons(Float_t _pt,
             Float_t _eta,
             Float_t _phi,
             Float_t _mass,
             Int_t   _charge,
             Float_t _dxy,
             Float_t _dz,
             Float_t _sip3d,
             Float_t _miniRelIso,
             Float_t _eleMissingHits,
             Float_t _mvaTTH,
             Float_t _jetPtRatio,
             Float_t _jetBTagCSV,
             Float_t _miniIsoCharged,
             Float_t _miniIsoNeutral,
             Float_t _mvaTTHjetPtRel,
             Float_t _mvaTTHjetNDauChargedMVASel)
    : RecoObject(_pt, _eta, _phi, _mass)
    , charge(_charge)
    , dxy(_dxy)
    , dz(_dz)
    , sip3d(_sip3d)
    , miniRelIso(_miniRelIso)
    , eleMissingHits(_eleMissingHits)
    , mvaTTH(_mvaTTH)
    , jetPtRatio(_jetPtRatio)
    , jetBTagCSV(_jetBTagCSV)
    , miniIsoCharged(_miniIsoCharged)
    , miniIsoNeutral(_miniIsoNeutral)
    , mvaTTHjetPtRel(_mvaTTHjetPtRel)
    , mvaTTHjetNDauChargedMVASel(_mvaTTHjetNDauChargedMVASel)
  {}

  Int_t   charge;
  Float_t dxy;
  Float_t dz;
  Float_t sip3d;
  Float_t miniRelIso;
  Float_t eleMissingHits;
  Float_t mvaTTH;
  Float_t jetPtRatio;
  Float_t jetBTagCSV;
  Float_t miniIsoCharged;
  Float_t miniIsoNeutral;
  Float_t mvaTTHjetPtRel;
  Float_t mvaTTHjetNDauChargedMVASel;

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }
};

template<>
Float_t
selLeptons::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "dxy"))                          return dxy;
  if(boost::iequals(key, "dz"))                           return dz;
  if(boost::iequals(key, "sip3d"))                        return sip3d;
  if(boost::iequals(key, "miniRelIso"))                   return miniRelIso;
  if(boost::iequals(key, "mvaTTH") ||
     boost::iequals(key, "leptonMVA"))                    return mvaTTH;
  if(boost::iequals(key, "jetPtRatio"))                   return jetPtRatio;
  if(boost::iequals(key, "jetBTagCSV") ||
     boost::iequals(key, "jetCSV"))                       return jetBTagCSV;
  if(boost::iequals(key, "miniIsoCharged"))               return miniIsoCharged;
  if(boost::iequals(key, "miniIsoNeutral"))               return miniIsoNeutral;
  if(boost::iequals(key, "mvaTTHjetPtRel") ||
     boost::iequals(key, "jetPtRel"))                     return mvaTTHjetPtRel;
  if(boost::iequals(key, "mvaTTHjetNDauChargedMVASel") ||
     boost::iequals(key, "jetNDauChargedMVASel"))         return mvaTTHjetNDauChargedMVASel;
  return RecoObject::get<Float_t>(key);
}

template<>
Int_t
selLeptons::get<Int_t>(const std::string & key) const
{
  if(boost::iequals(key, "charge")) return charge;
  return NAN_PLACEHOLDER;
}

struct
Muon
  : public selLeptons
{
  Muon() = default;
  Muon(Float_t _pt,
       Float_t _eta,
       Float_t _phi,
       Float_t _mass,
       Int_t _charge,
       Float_t _dxy,
       Float_t _dz,
       Float_t _sip3d,
       Float_t _miniRelIso,
       Float_t _eleMissingHits,
       Float_t _mvaTTH,
       Float_t _jetPtRatio,
       Float_t _jetBTagCSV,
       Float_t _miniIsoCharged,
       Float_t _miniIsoNeutral,
       Float_t _mvaTTHjetPtRel,
       Float_t _mvaTTHjetNDauChargedMVASel,
       Float_t _segmentCompatibility,
       Int_t   _looseIdPOG,
       Int_t   _idx)
    : selLeptons(
        _pt
      , _eta
      , _phi
      , _mass
      , _charge
      , _dxy
      , _dz
      , _sip3d
      , _miniRelIso
      , _eleMissingHits
      , _mvaTTH
      , _jetPtRatio
      , _jetBTagCSV
      , _miniIsoCharged
      , _miniIsoNeutral
      , _mvaTTHjetPtRel
      , _mvaTTHjetNDauChargedMVASel)
      , segmentCompatibility(_segmentCompatibility)
      , looseIdPOG(_looseIdPOG)
      , idx(_idx)
  {}

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }

  Float_t segmentCompatibility;
  Int_t looseIdPOG;
  Int_t idx;
};

template<>
Float_t
Muon::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "segmentCompatibility")) return segmentCompatibility;
  return selLeptons::get<Float_t>(key);
}

template<>
Int_t
Muon::get<Int_t>(const std::string & key) const
{
  if(boost::iequals(key, "idx")) return idx;
  return selLeptons::get<Int_t>(key);
}

struct
Electron
  : public selLeptons
{
  Electron() = default;
  Electron(Float_t _pt,
           Float_t _eta,
           Float_t _phi,
           Float_t _mass,
           Int_t   _charge,
           Float_t _dxy,
           Float_t _dz,
           Float_t _sip3d,
           Float_t _miniRelIso,
           Float_t _eleMissingHits,
           Float_t _mvaTTH,
           Float_t _jetPtRatio,
           Float_t _jetBTagCSV,
           Float_t _miniIsoCharged,
           Float_t _miniIsoNeutral,
           Float_t _mvaTTHjetPtRel,
           Float_t _mvaTTHjetNDauChargedMVASel,
           Float_t _eleMVArawSpring15NonTrig,
           Int_t   _lostHits,
           Int_t   _convVeto,
           Int_t   _idx)
    : selLeptons(
        _pt
      , _eta
      , _phi
      , _mass
      , _charge
      , _dxy
      , _dz
      , _sip3d
      , _miniRelIso
      , _eleMissingHits
      , _mvaTTH
      , _jetPtRatio
      , _jetBTagCSV
      , _miniIsoCharged
      , _miniIsoNeutral
      , _mvaTTHjetPtRel
      , _mvaTTHjetNDauChargedMVASel)
      , eleMVArawSpring15NonTrig(_eleMVArawSpring15NonTrig)
      , lostHits(_lostHits)
      , convVeto(_convVeto)
      , idx(_idx)
  {}

  template<typename T>
  T
  get(const std::string & key) const
  {
    return T();
  }

  Float_t eleMVArawSpring15NonTrig;
  Int_t lostHits;
  Int_t convVeto;
  Int_t idx;
};

template<>
Float_t
Electron::get<Float_t>(const std::string & key) const
{
  if(boost::iequals(key, "eleMVArawSpring15NonTrig") ||
     boost::iequals(key, "ntMVAeleID")) return eleMVArawSpring15NonTrig;
  return selLeptons::get<Float_t>(key);
}

template<>
Int_t
Electron::get<Int_t>(const std::string & key) const
{
  if(boost::iequals(key, "idx")) return idx;
  return selLeptons::get<Int_t>(key);
}

int
main(int argc,
     char ** argv)
{
#ifndef DISABLE_BOOST_LOG
  using namespace boost::log::trivial;
  boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
  boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] >> %Message%");
  boost::log::sources::severity_logger<severity_level> lg;
#endif

#ifdef PYTHON_CONFIG
  if(argc < 2)
    msg_exit("Missing argument!\nUsage: "_s + argv[0] + " [parameters.py]");
  if(! edm::readPSetsFrom(argv[1]) -> existsAs<edm::ParameterSet>("process"))
    throw cms::Exception("ntuples_ttHJetToTT")
      << "No ParameterSet \"process\" found in configuration file " << argv[1] << "!\n";
  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1]) -> getParameter<edm::ParameterSet>("process");
  const fwlite::InputSource input_files_cfg(cfg);
  const std::vector<std::string> input_filenames = input_files_cfg.files();
  const Long64_t nof_max_entries = input_files_cfg.maxEvents();
  const UInt_t report_every = input_files_cfg.reportAfter();
  const edm::ParameterSet cfg_out = cfg.getParameter<edm::ParameterSet>("ioFormat");
  const std::string output_filename = cfg_out.getParameter<std::string>("outputFilename");
  const std::string input_treename = cfg_out.getParameter<std::string>("inputTreename");
  const std::string output_treename = cfg_out.getParameter<std::string>("outputTreename");
#else
  const std::vector<std::string> input_filenames =
      { "/home/karl/cms/root_files/ttHJetToTT_M125_13TeV_ntuples_new.root" };
  const std::string output_filename =
    "/home/karl/cms/root_files/ttHJetToTT_M125_13TeV_ntuples_sync.root";
  const std::string input_treename = "tree";
  const std::string output_treename = "tree";

  const Long64_t nof_max_entries = -1;
  const UInt_t report_every = 5000;
#endif

  std::unique_ptr<TChain> input_tree(new TChain(input_treename.c_str()));
  for(const std::string & s: input_filenames)
  {
    if(! boost::filesystem::exists(s))
      msg_exit("No such file: "_s + s);
#ifndef DISABLE_BOOST_LOG
    BOOST_LOG_SEV(lg, info) << "Chaining file: " << s;
#else
    std::cout << ">> Chaining file: " << s << "\n";
#endif
    input_tree -> AddFile(s.c_str());
  }
  input_tree -> LoadTree(0);
#ifndef DISABLE_BOOST_LOG
  BOOST_LOG_SEV(lg, info)
    << "Input tree contains " << input_tree -> GetEntries() << " entries in "
    << input_tree -> GetListOfFiles() -> GetEntries() << " files";
#else
  std::cout << ">> Input tree contains " << input_tree -> GetEntries() << " entries in "
            << input_tree -> GetListOfFiles() -> GetEntries() << " files\n";
#endif

  std::unique_ptr<TFile> output_file(new TFile(output_filename.c_str(), "recreate"));
  std::unique_ptr<TTree> output_tree(new TTree(output_treename.c_str(),
                                               output_treename.c_str()));

  ULong64_t evt;

  Float_t met_pt;
  Float_t met_phi;

  Int_t   nselLeptons;
  Float_t selLeptons_pt                         [MAX_NOBJS];
  Float_t selLeptons_eta                        [MAX_NOBJS];
  Float_t selLeptons_phi                        [MAX_NOBJS];
  Float_t selLeptons_mass                       [MAX_NOBJS];
  Int_t   selLeptons_looseIdPOG                 [MAX_NOBJS];
  Int_t   selLeptons_charge                     [MAX_NOBJS];
  Float_t selLeptons_dxy                        [MAX_NOBJS];
  Float_t selLeptons_dz                         [MAX_NOBJS];
  Float_t selLeptons_sip3d                      [MAX_NOBJS];
  Int_t   selLeptons_lostHits                   [MAX_NOBJS];
  Int_t   selLeptons_convVeto                   [MAX_NOBJS];
  Float_t selLeptons_miniRelIso                 [MAX_NOBJS];
  Int_t   selLeptons_pdgId                      [MAX_NOBJS];
  Float_t selLeptons_eleMissingHits             [MAX_NOBJS];
  Float_t selLeptons_eleMVArawSpring15NonTrig   [MAX_NOBJS];
  Float_t selLeptons_segmentCompatibility       [MAX_NOBJS];
  Float_t selLeptons_mvaTTH                     [MAX_NOBJS];
  Float_t selLeptons_jetPtRatio                 [MAX_NOBJS];
  Float_t selLeptons_jetBTagCSV                 [MAX_NOBJS];
  Float_t selLeptons_miniIsoCharged             [MAX_NOBJS];
  Float_t selLeptons_miniIsoNeutral             [MAX_NOBJS];
  Float_t selLeptons_mvaTTHjetPtRel             [MAX_NOBJS];
  Float_t selLeptons_mvaTTHjetNDauChargedMVASel [MAX_NOBJS];
  std::map<std::string, IntArray>   selLeptons_int;
  std::map<std::string, FloatArray> selLeptons_float;
  selLeptons_int.insert(std::make_pair("charge",     selLeptons_charge));
  selLeptons_int.insert(std::make_pair("looseIdPOG", selLeptons_looseIdPOG));
  selLeptons_int.insert(std::make_pair("pdgId",      selLeptons_pdgId));
  selLeptons_int.insert(std::make_pair("lostHits",   selLeptons_lostHits));
  selLeptons_int.insert(std::make_pair("convVeto",   selLeptons_convVeto));
  selLeptons_float.insert(std::make_pair("pt",                         selLeptons_pt));
  selLeptons_float.insert(std::make_pair("eta",                        selLeptons_eta));
  selLeptons_float.insert(std::make_pair("phi",                        selLeptons_phi));
  selLeptons_float.insert(std::make_pair("mass",                       selLeptons_mass));
  selLeptons_float.insert(std::make_pair("dxy",                        selLeptons_dxy));
  selLeptons_float.insert(std::make_pair("dz",                         selLeptons_dz));
  selLeptons_float.insert(std::make_pair("sip3d",                      selLeptons_sip3d));
  selLeptons_float.insert(std::make_pair("miniRelIso",                 selLeptons_miniRelIso));
  selLeptons_float.insert(std::make_pair("eleMissingHits",             selLeptons_eleMissingHits));
  selLeptons_float.insert(std::make_pair("eleMVArawSpring15NonTrig",   selLeptons_eleMVArawSpring15NonTrig));
  selLeptons_float.insert(std::make_pair("segmentCompatibility",       selLeptons_segmentCompatibility));
  selLeptons_float.insert(std::make_pair("mvaTTH",                     selLeptons_mvaTTH));
  selLeptons_float.insert(std::make_pair("jetPtRatio",                 selLeptons_jetPtRatio));
  selLeptons_float.insert(std::make_pair("jetBTagCSV",                 selLeptons_jetBTagCSV));
  selLeptons_float.insert(std::make_pair("miniIsoCharged",             selLeptons_miniIsoCharged));
  selLeptons_float.insert(std::make_pair("miniIsoNeutral",             selLeptons_miniIsoNeutral));
  selLeptons_float.insert(std::make_pair("mvaTTHjetPtRel",             selLeptons_mvaTTHjetPtRel));
  selLeptons_float.insert(std::make_pair("mvaTTHjetNDauChargedMVASel", selLeptons_mvaTTHjetNDauChargedMVASel));

  Int_t nTauGood;
  Int_t   TauGood_charge           [MAX_NOBJS];
  Int_t   TauGood_idDecayMode      [MAX_NOBJS];
  Int_t   TauGood_idDecayModeNewDMs[MAX_NOBJS];
  Float_t TauGood_dxy              [MAX_NOBJS];
  Float_t TauGood_dz               [MAX_NOBJS];
  Int_t   TauGood_idMVArun2dR03    [MAX_NOBJS];
  Int_t   TauGood_idCI3hit         [MAX_NOBJS];
  Int_t   TauGood_idCI3hitdR03     [MAX_NOBJS];
  Int_t   TauGood_idAntiMu         [MAX_NOBJS];
  Int_t   TauGood_idAntiErun2      [MAX_NOBJS];
  Float_t TauGood_isoCI3hit        [MAX_NOBJS];
  Float_t TauGood_pt               [MAX_NOBJS];
  Float_t TauGood_eta              [MAX_NOBJS];
  Float_t TauGood_phi              [MAX_NOBJS];
  Float_t TauGood_mass             [MAX_NOBJS];
  std::map<std::string, IntArray>   TauGood_int;
  std::map<std::string, FloatArray> TauGood_float;
  TauGood_int.insert(std::make_pair("charge",            TauGood_charge));
  TauGood_int.insert(std::make_pair("idDecayMode",       TauGood_idDecayMode));
  TauGood_int.insert(std::make_pair("idDecayModeNewDMs", TauGood_idDecayModeNewDMs));
  TauGood_int.insert(std::make_pair("idMVArun2dR03",     TauGood_idMVArun2dR03));
  TauGood_int.insert(std::make_pair("idCI3hit",          TauGood_idCI3hit));
  TauGood_int.insert(std::make_pair("idCI3hitdR03",      TauGood_idCI3hitdR03));
  TauGood_int.insert(std::make_pair("idAntiMu",          TauGood_idAntiMu));
  TauGood_int.insert(std::make_pair("idAntiErun2",       TauGood_idAntiErun2));
  TauGood_float.insert(std::make_pair("dxy",       TauGood_dxy));
  TauGood_float.insert(std::make_pair("dz",        TauGood_dz));
  TauGood_float.insert(std::make_pair("isoCI3hit", TauGood_isoCI3hit));
  TauGood_float.insert(std::make_pair("pt",        TauGood_pt));
  TauGood_float.insert(std::make_pair("eta",       TauGood_eta));
  TauGood_float.insert(std::make_pair("phi",       TauGood_phi));
  TauGood_float.insert(std::make_pair("mass",      TauGood_mass));

  Int_t nJet;
  Float_t Jet_pt      [MAX_NOBJS];
  Float_t Jet_eta     [MAX_NOBJS];
  Float_t Jet_phi     [MAX_NOBJS];
  Float_t Jet_mass    [MAX_NOBJS];
  Float_t Jet_btagCSV [MAX_NOBJS];
  std::map<std::string, FloatArray> jet_in;
  jet_in.insert(std::make_pair("pt",      Jet_pt));
  jet_in.insert(std::make_pair("eta",     Jet_eta));
  jet_in.insert(std::make_pair("phi",     Jet_phi));
  jet_in.insert(std::make_pair("mass",    Jet_mass));
  jet_in.insert(std::make_pair("btagCSV", Jet_btagCSV));

  input_tree -> SetBranchAddress("evt",  &evt);

  input_tree -> SetBranchAddress("met_pt",  &met_pt);
  input_tree -> SetBranchAddress("met_phi", &met_phi);

  input_tree -> SetBranchAddress("nselLeptons", &nselLeptons);
  for(auto & kv: selLeptons_int)
    input_tree -> SetBranchAddress(("selLeptons_" + kv.first).c_str(), kv.second.arr);
  for(auto & kv: selLeptons_float)
    input_tree -> SetBranchAddress(("selLeptons_" + kv.first).c_str(), kv.second.arr);

  input_tree -> SetBranchAddress("nTauGood", &nTauGood);
  for(auto & kv: TauGood_int)
    input_tree -> SetBranchAddress(("TauGood_" + kv.first).c_str(), kv.second.arr);
  for(auto & kv: TauGood_float)
    input_tree -> SetBranchAddress(("TauGood_" + kv.first).c_str(), kv.second.arr);

  input_tree -> SetBranchAddress("nJet", &nJet);
  for(auto & kv: jet_in)
    input_tree -> SetBranchAddress(("Jet_" + kv.first).c_str(), kv.second.arr);

  ULong64_t nEvent;
  ULong64_t n_presel_mu;
  ULong64_t n_presel_ele;
  ULong64_t n_presel_tau;
  ULong64_t n_presel_jet;

  Float_t PFMET;
  Float_t PFMETphi;

  output_tree -> Branch("nEvent",       &nEvent,       "nEvent/l");
  output_tree -> Branch("n_presel_mu",  &n_presel_mu,  "n_presel_mu/l");
  output_tree -> Branch("n_presel_ele", &n_presel_ele, "n_presel_ele/l");
  output_tree -> Branch("n_presel_tau", &n_presel_tau, "n_presel_tau/l");
  output_tree -> Branch("n_presel_jet", &n_presel_jet, "n_presel_jet/l");

  const std::vector<std::string> lepton_int_keys = { "charge" };
  const std::vector<std::string> lepton_float_keys = { "pt", "eta", "phi", "E", "miniRelIso", "jetPtRatio",
                                                       "jetCSV", "sip3D", "dxy", "dz", "leptonMVA", "miniIsoCharged",
                                                       "miniIsoNeutral", "jetPtRel", "jetNDauChargedMVASel"};
  const std::vector<std::string> mu_int_keys = lepton_int_keys;
  std::vector<std::string> mu_float_keys = lepton_float_keys;
  mu_float_keys.push_back("segmentCompatibility");
  const std::vector<std::string> ele_int_keys = lepton_int_keys;
  std::vector<std::string> ele_float_keys = lepton_float_keys;
  ele_float_keys.push_back("ntMVAeleID");
  const std::vector<std::string> tau_int_keys = { "charge", "decayModeFindingOldDMs", "decayModeFindingNewDMs",
                                                  "byLooseCombinedIsolationDeltaBetaCorr3Hits",
                                                  "byMediumCombinedIsolationDeltaBetaCorr3Hits",
                                                  "byTightCombinedIsolationDeltaBetaCorr3Hits",
                                                  "byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",
                                                  "byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",
                                                  "byTightCombinedIsolationDeltaBetaCorr3HitsdR03",
                                                  "byLooseIsolationMVArun2v1DBdR03oldDMwLT",
                                                  "byMediumIsolationMVArun2v1DBdR03oldDMwLT",
                                                  "byTightIsolationMVArun2v1DBdR03oldDMwLT",
                                                  "byVTightIsolationMVArun2v1DBdR03oldDMwLT",
                                                  "againstMuonLoose3", "againstMuonTight3",
                                                  "againstElectronVLooseMVA6", "againstElectronLooseMVA6",
                                                  "againstElectronMediumMVA6", "againstElectronTightMVA6" };
  const std::vector<std::string> tau_float_keys = { "pt", "eta", "phi", "E", "dxy", "dz",
                                                    "byCombinedIsolationDeltaBetaCorr3Hits" };
  const std::vector<std::string> jet_keys = { "pt", "eta", "phi", "E", "CSV" };

  std::unordered_map<std::string, std::array<Int_t, 2>> mus_int, eles_int, taus_int;
  std::unordered_map<std::string, std::array<Float_t, 2>> mus_float, eles_float, taus_float;

  for(const std::string & var: mu_int_keys)
    mus_int.insert(std::make_pair(var, std::array<Int_t, 2>{{NAN_PLACEHOLDER}}));
  for(const std::string & var: mu_float_keys)
    mus_float.insert(std::make_pair(var, std::array<Float_t, 2>{{NAN_PLACEHOLDER}}));
  for(Int_t i = 0; i < 2; ++i)
  {
    const std::string mu_i = "mu" + std::to_string(i) + "_";
    for(auto & kv: mus_int)
      output_tree -> Branch((mu_i + kv.first).c_str(), &(kv.second[i]), (mu_i + kv.first + "/I").c_str());
    for(auto & kv: mus_float)
      output_tree -> Branch((mu_i + kv.first).c_str(), &(kv.second[i]), (mu_i + kv.first + "/F").c_str());
  }

  for(const std::string & var: ele_int_keys)
    eles_int.insert(std::make_pair(var, std::array<Int_t, 2>{{NAN_PLACEHOLDER}}));
  for(const std::string & var: ele_float_keys)
    eles_float.insert(std::make_pair(var, std::array<Float_t, 2>{{NAN_PLACEHOLDER}}));
  for(Int_t i = 0; i < 2; ++i)
  {
    const std::string ele_i = "ele" + std::to_string(i) + "_";
    for(auto & kv: eles_int)
      output_tree -> Branch((ele_i + kv.first).c_str(), &(kv.second[i]), (ele_i + kv.first + "/I").c_str());
    for(auto & kv: eles_float)
      output_tree -> Branch((ele_i + kv.first).c_str(), &(kv.second[i]), (ele_i + kv.first + "/F").c_str());
  }

  for(const std::string & var: tau_int_keys)
    taus_int.insert(std::make_pair(var, std::array<Int_t, 2>{{NAN_PLACEHOLDER}}));
  for(const std::string & var: tau_float_keys)
    taus_float.insert(std::make_pair(var, std::array<Float_t, 2>{{NAN_PLACEHOLDER}}));
  for(Int_t i = 0; i < 2; ++i)
  {
    const std::string tau_i = "tau" + std::to_string(i) + "_";
    for(auto & kv: taus_int)
      output_tree -> Branch((tau_i + kv.first).c_str(), &(kv.second[i]), (tau_i + kv.first + "/I").c_str());
    for(auto & kv: taus_float)
      output_tree -> Branch((tau_i + kv.first).c_str(), &(kv.second[i]), (tau_i + kv.first + "/F").c_str());
  }

  std::unordered_map<std::string, std::array<Float_t, 4>> jets_out;
  for(const std::string & var: jet_keys)
    jets_out.insert(std::make_pair(var, std::array<Float_t, 4>{{NAN_PLACEHOLDER}}));

  for(Int_t i = 0; i < 4; ++i)
    for(auto & kv: jets_out)
    {
      const std::string j = "jet" + std::to_string(i) + "_" + kv.first;
      output_tree -> Branch(j.c_str(), &(kv.second[i]), (j + "/F").c_str());
    }

  output_tree -> Branch("PFMET",    &PFMET,    "PFMET/F");
  output_tree -> Branch("PFMETphi", &PFMETphi, "PFMETphi/F");

  const Long64_t nof_entries = nof_max_entries < 0 ?
                               input_tree -> GetEntries() :
                               std::min(nof_max_entries,
                                        input_tree -> GetEntries());

  auto reset = [](auto & m) mutable -> void
  {
    for(auto & kv: m)
      for(std::size_t i = 0; i < kv.second.size(); ++i)
        kv.second[i] = NAN_PLACEHOLDER;
  };
  auto reset_all = [reset, &jets_out,
                    &mus_int, &mus_float,
                    &eles_int, &eles_float,
                    &taus_int, &taus_float]() mutable -> void
  {
    reset(jets_out);
    reset(mus_int);
    reset(mus_float);
    reset(eles_int);
    reset(eles_float);
    reset(taus_int);
    reset(taus_float);
  };

  for(Long64_t i = 0; i < nof_entries; ++i)
  {
    input_tree -> GetEntry(i);
    if(i > 0 && i % report_every == 0)
#ifndef DISABLE_BOOST_LOG
      BOOST_LOG_SEV(lg, info)
        << "Processing entry number " << i;
#else
      std::cout << ">> Processing entry number " << i << "\n";
#endif

    reset_all();

    nEvent = evt;

    std::vector<Electron> eles;
    std::vector<Muon> mus;
    for(Int_t j = 0; j < nselLeptons; ++j)
      if(std::abs(selLeptons_pdgId[j]) == 11)
        eles.push_back({selLeptons_pt[j], selLeptons_eta[j], selLeptons_phi[j],
                        selLeptons_mass[j], selLeptons_charge[j], selLeptons_dxy[j],
                        selLeptons_dz[j], selLeptons_sip3d[j], selLeptons_miniRelIso[j],
                        selLeptons_eleMissingHits[j], selLeptons_mvaTTH[j],
                        selLeptons_jetPtRatio[j], selLeptons_jetBTagCSV[j],
                        selLeptons_miniIsoCharged[j], selLeptons_miniIsoNeutral[j],
                        selLeptons_mvaTTHjetPtRel[j], selLeptons_mvaTTHjetNDauChargedMVASel[j],
                        selLeptons_eleMVArawSpring15NonTrig[j], selLeptons_lostHits[j],
                        selLeptons_convVeto[j], j});
      else if(std::abs(selLeptons_pdgId[j]) == 13)
        mus.push_back({selLeptons_pt[j], selLeptons_eta[j], selLeptons_phi[j],
                       selLeptons_mass[j], selLeptons_charge[j], selLeptons_dxy[j],
                       selLeptons_dz[j], selLeptons_sip3d[j], selLeptons_miniRelIso[j],
                       selLeptons_eleMissingHits[j], selLeptons_mvaTTH[j],
                       selLeptons_jetPtRatio[j], selLeptons_jetBTagCSV[j],
                       selLeptons_miniIsoCharged[j], selLeptons_miniIsoNeutral[j],
                       selLeptons_mvaTTHjetPtRel[j], selLeptons_mvaTTHjetNDauChargedMVASel[j],
                       selLeptons_segmentCompatibility[j], selLeptons_looseIdPOG[j], j});

    std::sort(eles.begin(), eles.end(), sort_by_pt);
    std::sort(mus.begin(), mus.end(), sort_by_pt);

    mus.erase(
       std::remove_if(mus.begin(), mus.end(), [](const Muon & mu) {
         return !(mu.sip3d < 8 &&
                  mu.miniRelIso < 0.4 &&
                  std::fabs(mu.dz) < 0.1 &&
                  std::fabs(mu.dxy) < 0.05 &&
                  mu.pt > 5 &&
                  std::fabs(mu.eta) < 2.4 &&
                  mu.looseIdPOG >= 1);
         }),
         mus.end()
    );
    n_presel_mu = mus.size();

    for(Int_t j = 0; j < std::min(static_cast<int>(mus.size()), 2); ++j)
    {
      for(auto & kv: mus_int)
        kv.second[j] = mus[j].get<Int_t>(kv.first);
      for(auto & kv: mus_float)
        kv.second[j] = mus[j].get<Float_t>(kv.first);
    }

    eles.erase(
       std::remove_if(eles.begin(), eles.end(), [](const Electron & ele) {
         return !(ele.sip3d < 8 &&
                  ele.miniRelIso < 0.4 &&
                  std::fabs(ele.dz) < 0.1 &&
                  std::fabs(ele.dxy) < 0.05 &&
                  ele.pt > 7 &&
                  std::fabs(ele.eta) < 2.5 && // we've already cut at 2.4 in place
                  // VLooseIdEmu WP
                  ((std::fabs(ele.eta) < 0.8 && ele.eleMVArawSpring15NonTrig > -0.7) ||
                   (std::fabs(ele.eta) >= 0.8 && std::fabs(ele.eta) < 1.479 && ele.eleMVArawSpring15NonTrig > -0.83) ||
                   (std::fabs(ele.eta) >= 1.479 && ele.eleMVArawSpring15NonTrig > -0.92)
                   ) &&
                  ele.lostHits <= 1 &&
                  ele.convVeto >= 1);
         }),
         eles.end()
    );
    eles.erase(
      std::remove_if(eles.begin(), eles.end(), [&mus](const Electron & ele) {
        bool no_overlap = true;
        for(const auto & mu: mus)
          if(mu.overlaps(ele, 0.05))
          {
            no_overlap = false;
            break;
          }
        return ! no_overlap;
        }),
        eles.end()
    );
    n_presel_ele = eles.size();

    for(Int_t j = 0; j < std::min(static_cast<int>(eles.size()), 2); ++j)
    {
      for(auto & kv: eles_int)
        kv.second[j] = eles[j].get<Int_t>(kv.first);
      for(auto & kv: eles_float)
        kv.second[j] = eles[j].get<Float_t>(kv.first);
    }

    std::vector<TauGood> tau_goods;
    for(Int_t j = 0; j < nTauGood; ++j)
      tau_goods.push_back({TauGood_pt[j], TauGood_eta[j], TauGood_phi[j], TauGood_mass[j],
                           TauGood_charge[j], TauGood_idDecayMode[j], TauGood_idDecayModeNewDMs[j],
                           TauGood_dxy[j], TauGood_dz[j], TauGood_idMVArun2dR03[j],
                           TauGood_idCI3hit[j], TauGood_idCI3hitdR03[j], TauGood_idAntiMu[j],
                           TauGood_idAntiErun2[j], TauGood_isoCI3hit[j]});

    std::sort(tau_goods.begin(), tau_goods.end(), sort_by_pt);
    tau_goods.erase(
      std::remove_if(tau_goods.begin(), tau_goods.end(), [](const TauGood & tau) {
        return !(std::fabs(tau.eta) < 2.3 &&
                 tau.pt > 20 &&
                 std::fabs(tau.dz) < 0.2 &&
                 tau.byLooseCombinedIsolationDeltaBetaCorr3Hits == 1 &&
                 tau.idDecayMode >= 1);
      }),
      tau_goods.end()
    );
    tau_goods.erase(
      std::remove_if(tau_goods.begin(), tau_goods.end(), [&eles,&mus](const TauGood & tau) {
        bool no_overlap = true;
        for(const auto & mu: mus)
          if(mu.overlaps(tau, 0.4))
          {
            no_overlap = false;
            break;
          }
        if(no_overlap)
          for(const auto & ele: eles)
            if(ele.overlaps(tau, 0.4))
            {
              no_overlap = false;
              break;
            }
        return ! no_overlap;
        }),
        tau_goods.end()
    );
    n_presel_tau = tau_goods.size();

    for(Int_t j = 0; j < std::min(static_cast<int>(tau_goods.size()), 2); ++j)
    {
        for(auto & kv: taus_int)
          kv.second[j] = tau_goods[j].get<Int_t>(kv.first);
        for(auto & kv: taus_float)
          kv.second[j] = tau_goods[j].get<Float_t>(kv.first);
    }

    std::vector<Jet> jets;
    for(Int_t j = 0; j < nJet; ++j)
      jets.push_back({Jet_pt[j], Jet_eta[j], Jet_phi[j], Jet_mass[j], Jet_btagCSV[j], j});
    std::sort(jets.begin(), jets.end(), sort_by_pt);

    jets.erase(
      std::remove_if(jets.begin(), jets.end(), [](const Jet & jet) {
        return !(std::fabs(jet.eta) < 2.4 &&
                 jet.pt > 25); // loose pf jet?
      }),
      jets.end()
    );
    jets.erase(
      std::remove_if(jets.begin(), jets.end(), [&eles,&mus,&tau_goods](const Jet & jet) {
        bool no_overlap = true;
        for(const auto & mu: mus)
          if(mu.overlaps(jet, 0.4))
          {
            no_overlap = false;
            break;
          }
        if(no_overlap)
          for(const auto & ele: eles)
            if(ele.overlaps(jet, 0.4))
            {
              no_overlap = false;
              break;
            }
        if(no_overlap)
          for(const auto & tau: tau_goods)
            if(tau.overlaps(jet, 0.4))
            {
              no_overlap = false;
              break;
            }
        return ! no_overlap;
        }),
        jets.end()
    );
    n_presel_jet = jets.size();

    for(Int_t j = 0; j < std::min(static_cast<int>(jets.size()), 4); ++j)
      for(auto & kv: jets_out)
        kv.second[j] = jets[j].get<Float_t>(kv.first);

    PFMET = met_pt;
    PFMETphi = met_phi;

    output_tree -> Fill();
  }

#ifndef DISABLE_BOOST_LOG
  BOOST_LOG_SEV(lg, info)
    << output_tree -> GetEntries() << " entries pass selection";
  BOOST_LOG_SEV(lg, info)
    << "writing output tree to file " << output_filename;
#else
  std::cout << ">> " << output_tree -> GetEntries() << " entries pass selection\n"
            << ">> " << "writing output tree to file " << output_filename << "\n";
#endif
  output_file -> cd();
  output_tree -> Write();

  return EXIT_SUCCESS;
}
