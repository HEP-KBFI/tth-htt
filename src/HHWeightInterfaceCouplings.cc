#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceCouplings.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring(), get_fullpath(), to_string_with_precision<>()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // contains()
#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceLO.h" // HHWeightInterfaceLO

#include <TFile.h> // TFile
#include <TH2.h> // TH2

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#if defined(__OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/algorithm/string.hpp> // boost::split(), boost::is_any_of()
#pragma GCC diagnostic pop

#include <boost/algorithm/string/replace.hpp> // boost::replace_all()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/range/algorithm/copy.hpp> // boost::copy()

#include <fstream> // std::ifstream
#include <iostream> // std::cout

const std::vector<HHCoupling> HHWeightInterfaceCouplings::JHEP04_ = {
  {  7.5, 1.0, -1.0,  0.0,    0.0,  "JHEP04BM1",  "BM1" },
  {  1.0, 1.0,  0.5, -0.8,    0.6,  "JHEP04BM2",  "BM2" },
  {  1.0, 1.0, -1.5,  0.0,   -0.8,  "JHEP04BM3",  "BM3" },
  { -3.5, 1.5, -3.0,  0.0,    0.0,  "JHEP04BM4",  "BM4" },
  {  1.0, 1.0,  0.0,  0.8,   -1.0,  "JHEP04BM5",  "BM5" },
  {  2.4, 1.0,  0.0,  0.2,   -0.2,  "JHEP04BM6",  "BM6" },
  {  5.0, 1.0,  0.0,  0.2,   -0.2,  "JHEP04BM7",  "BM7" },
  { 15.0, 1.0,  0.0, -1.0,    1.0,  "JHEP04BM8",  "BM8" },
  {  1.0, 1.0,  1.0, -0.6,    0.6,  "JHEP04BM9",  "BM9" },
  { 10.0, 1.5, -1.0,  0.0,    0.0, "JHEP04BM10", "BM10" },
  {  2.4, 1.0,  0.0,  1.0,   -1.0, "JHEP04BM11", "BM11" },
  { 15.0, 1.0,  1.0,  0.0,    0.0, "JHEP04BM12", "BM12" },
  {  1.0, 1.0,  0.5,  0.8/3,  0.0, "JHEP04BM8a",  "BM9" }, // [*]
};
const std::vector<HHCoupling> HHWeightInterfaceCouplings::JHEP03_ = {
  {  3.94, 0.94, -1./3.,  0.5*1.5,    1./3.*(-3.), "JHEP03BM1", "BM11" }, // [*]
  {  6.84, 0.61,  1./3.,  0.0*1.5,   -1./3.*(-3.), "JHEP03BM2", "BM11" }, // [*]
  {  2.21, 1.05, -1./3.,  0.5*1.5,    0.5 *(-3.),  "JHEP03BM3",  "BM5" }, // [*]
  {  2.79, 0.61,  1./3., -0.5*1.5,    1./6.*(-3.), "JHEP03BM4",  "BM3" }, // [*]
  {  3.95, 1.17, -1./3.,  1./6.*1.5, -0.5 *(-3.),  "JHEP03BM5",  "BM9" }, // [*]
  {  5.68, 0.83,  1./3., -0.5*1.5,    1./3.*(-3.), "JHEP03BM6",  "BM3" }, // [*]
  { -0.10, 0.94,  1.,     1./6.*1.5, -1./6.*(-3.), "JHEP03BM7",  "BM9" }, // [*]
};
// [*] https://github.com/HEP-KBFI/hh-multilepton/issues/38#issuecomment-821278740

TH2 *
HHWeightInterfaceCouplings::loadDenominatorHist(const std::string & fileName,
                                                const std::string & histTitle)
{
  const std::string fileNameFullPath = get_fullpath(fileName);
  TFile * denomFile = TFileOpenWrapper::Open(fileNameFullPath.c_str(), "READ");
  if(! denomFile)
  {
    throw cmsException(__func__, __LINE__)
      << "Could not open file " << fileNameFullPath << " !!\n";
  }
  if(denomFile -> IsZombie())
  {
    throw cmsException(__func__, __LINE__) << "The file '" << fileNameFullPath << "' appears to be a zombie";
  }
  TH2 * denomHist = static_cast<TH2 *>(denomFile -> Get(histTitle.c_str()));
  if(! denomHist)
  {
    throw cmsException(__func__, __LINE__) << "The file '" << fileNameFullPath << "' does not have a TH2 named " << histTitle;
  }
  denomHist->SetDirectory(0);
  denomFile->Close();
  return denomHist;
}

double
HHWeightInterfaceCouplings::getBinContent(const TH2 * const hist,
                                          double mHH,
                                          double cosThetaStar)
{
  const double value = hist->GetBinContent(
    hist->GetXaxis()->FindBin(mHH),
    hist->GetYaxis()->FindBin(std::fabs(cosThetaStar))
  );
  return value;
}

HHWeightInterfaceCouplings::HHWeightInterfaceCouplings(const edm::ParameterSet & cfg)
  : nlo_mode_(HHWeightInterfaceNLOMode::none)
  , denominator_file_lo_(cfg.getParameter<std::string>("denominator_file_lo"))
  , denominator_file_nlo_(cfg.getParameter<std::string>("denominator_file_nlo"))
  , histtitle_(cfg.getParameter<std::string>("histtitle"))
{
  const std::string applicationLoadFile_klScan = cfg.getParameter<std::string>("klScan_file");
  const std::string applicationLoadFile_ktScan = cfg.getParameter<std::string>("ktScan_file");
  const std::string applicationLoadFile_c2Scan = cfg.getParameter<std::string>("c2Scan_file");
  const std::string applicationLoadFile_cgScan = cfg.getParameter<std::string>("cgScan_file");
  const std::string applicationLoadFile_c2gScan = cfg.getParameter<std::string>("c2gScan_file");
  const std::string applicationLoadFile_extraScan = cfg.getParameter<std::string>("extraScan_file");

  const std::vector<std::string> scanMode = cfg.getParameter<std::vector<std::string>>("scanMode");
  const bool isDEBUG = cfg.getParameter<bool>("isDEBUG");

  const std::string rwgt_nlo_mode = cfg.getParameter<std::string>("rwgt_nlo_mode");
  if     (rwgt_nlo_mode == "v1") { nlo_mode_ = HHWeightInterfaceNLOMode::v1; }
  else if(rwgt_nlo_mode == "v2") { nlo_mode_ = HHWeightInterfaceNLOMode::v2; }
  else if(rwgt_nlo_mode == "v3") { nlo_mode_ = HHWeightInterfaceNLOMode::v3; }

  couplings_ = { { "SM", HHCoupling() } };
  if(contains(scanMode, "JHEP04"))
  {
    for(const HHCoupling & coupling: JHEP04_)
    {
      assert(! couplings_.count(coupling.name()));
      couplings_[coupling.name()] = coupling;
    }
  }
  if(contains(scanMode, "JHEP03"))
  {
    for(const HHCoupling & coupling: JHEP03_)
    {
      assert(! couplings_.count(coupling.name()));
      couplings_[coupling.name()] = coupling;
    }
  }

  // Load a file with an specific scan, that we can decide at later stage on the analysis
  // save the closest shape BM to use this value on the evaluation of a BDT
  if(contains(scanMode, "kl") && ! applicationLoadFile_klScan.empty()){
    const std::string applicationLoadPath_klScan = get_fullpath(applicationLoadFile_klScan);
    loadScanFile(applicationLoadPath_klScan, "kl_", 0, isDEBUG);
  }
  if(contains(scanMode, "kt") && ! applicationLoadFile_ktScan.empty())
  {
    const std::string applicationLoadPath_ktScan = get_fullpath(applicationLoadFile_ktScan);
    loadScanFile(applicationLoadPath_ktScan, "kt_", 1, isDEBUG);
  }
  if(contains(scanMode, "c2") && ! applicationLoadFile_c2Scan.empty())
  {
    const std::string applicationLoadPath_c2Scan = get_fullpath(applicationLoadFile_c2Scan);
    loadScanFile(applicationLoadPath_c2Scan, "c2_", 2, isDEBUG);
  }
  if(contains(scanMode, "cg") && ! applicationLoadFile_cgScan.empty())
  {
    const std::string applicationLoadPath_cgScan = get_fullpath(applicationLoadFile_cgScan);
    loadScanFile(applicationLoadPath_cgScan, "cg_", 3, isDEBUG);
  }
  if(contains(scanMode, "c2g") && ! applicationLoadFile_c2gScan.empty())
  {
    const std::string applicationLoadPath_c2gScan = get_fullpath(applicationLoadFile_c2gScan);
    loadScanFile(applicationLoadPath_c2gScan, "c2g_", 4, isDEBUG);
  }
  if(contains(scanMode, "extra") && ! applicationLoadFile_extraScan.empty())
  {
    const std::string applicationLoadPath_extraScan = get_fullpath(applicationLoadFile_extraScan);
    loadScanFile(applicationLoadPath_extraScan, "extra_", 5, isDEBUG);
  }

  std::cout
      << get_human_line(this, __func__, __LINE__)
      << "Scanning " << couplings_.size() << " benchmark scenarios: " << format_vstring(get_bm_names())
      << '\n'
  ;
}

void
HHWeightInterfaceCouplings::loadScanFile(const std::string & filePath,
                                         const std::string & prefix,
                                         int idx,
                                         bool isDEBUG)
{
  // CV: read coupling scans from text files
  std::ifstream inFile_scan(filePath);
  if(! inFile_scan)
  {
    throw cmsException(this, __func__, __LINE__) << "Error on opening file " << filePath;
  }
  for (std::string line; std::getline(inFile_scan, line); )
  {
    if(boost::starts_with(line, "#"))
    {
      continue; // it's a comment
    }
    std::vector<std::string> line_split;
    boost::split(line_split, line, boost::is_any_of(" "), boost::token_compress_on);
    const std::size_t nof_cols = line_split.size();
    assert(nof_cols == 5 || nof_cols == 6);

    std::vector<double> values;
    std::transform(
      line_split.begin(), line_split.begin() + 5, std::back_inserter(values),
      [](const std::string & value_string) -> double { return std::stod(value_string); }
    );

    std::string bmName = prefix;
    if(idx < 5)
    {
      bmName += to_string_with_precision(values.at(idx));
      boost::replace_all(bmName, "-", "m");
      boost::replace_all(bmName, ".", "p");
    }
    else if(idx == 5)
    {
      assert(nof_cols == 6);
      bmName += line_split.at(idx);
    }
    else
    {
      throw cmsException(this, __func__, __LINE__) << "Invalid number of columns in file: " << filePath;
    }
    if(isDEBUG)
    {
      std::cout << "bmName = " << bmName << '\n';
    }

    assert(! couplings_.count(bmName));
    couplings_[bmName] = { values, bmName };
  }
}

void
HHWeightInterfaceCouplings::add(const HHCoupling & coupling)
{
  if(couplings_.count(coupling.name()))
  {
    throw cmsException(this, __func__, __LINE__) << "The coupling name has already been booked: " << coupling.name();
  }
  couplings_[coupling.name()] = coupling;
}

std::map<std::string, HHCoupling>
HHWeightInterfaceCouplings::getCouplings() const
{
  return couplings_;
}

HHCoupling
HHWeightInterfaceCouplings::getCoupling(const std::string & name) const
{
  if(! couplings_.count(name))
  {
    throw cmsException(this, __func__, __LINE__) << "No such coupling booked: " << name;
  }
  const HHCoupling & coupling = couplings_.at(name);
  assert(name == coupling.name());
  return coupling;
}

std::vector<std::string>
HHWeightInterfaceCouplings::get_bm_names() const
{
  std::vector<std::string> bmNames;
  boost::copy(couplings_ | boost::adaptors::map_keys, std::back_inserter(bmNames));
  return bmNames;
}

std::vector<std::string>
HHWeightInterfaceCouplings::get_weight_names() const
{
  std::vector<std::string> weightNames;
  std::transform(
    couplings_.cbegin(), couplings_.cend(), std::back_inserter(weightNames),
    [](const std::pair<std::string, HHCoupling> & kv) -> std::string
    {
      return kv.second.weightName();
    }
  );
  return weightNames;
}

HHWeightInterfaceNLOMode
HHWeightInterfaceCouplings::nlo_mode() const
{
  return nlo_mode_;
}

std::string
HHWeightInterfaceCouplings::denominator_file_lo() const
{
  return denominator_file_lo_;
}

std::string
HHWeightInterfaceCouplings::denominator_file_nlo() const
{
  return denominator_file_nlo_;
}

std::string
HHWeightInterfaceCouplings::histtitle() const
{
  return histtitle_;
}
