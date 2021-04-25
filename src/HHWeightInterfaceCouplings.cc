#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceCouplings.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vstring(), get_fullpath(), to_string_with_precision<>()
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

#include <fstream> // std::ifstream
#include <iostream> // std::cout

// CV: Define 12 benchmark (BM) scenarios for coupling scan.
//     The BM scenarios are defined in this paper: https://arxiv.org/pdf/1507.02245.pdf
//    (SM case is stored at index 0)
const std::size_t HHWeightInterfaceCouplings::nof_JHEP = 13;
const std::vector<double> HHWeightInterfaceCouplings::klJHEP   = { 1.0,     7.5,     1.0,     1.0,    -3.5,     1.0,     2.4,     5.0,    15.0,     1.0,    10.0,     2.4,    15.0     };
const std::vector<double> HHWeightInterfaceCouplings::ktJHEP   = { 1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0,     1.0,     1.0,     1.0,     1.5,     1.0,     1.0     };
const std::vector<double> HHWeightInterfaceCouplings::c2JHEP   = { 0.0,    -1.0,     0.5,    -1.5,    -3.0,     0.0,     0.0,     0.0,     0.0,     1.0,    -1.0,     0.0,     1.0     };
const std::vector<double> HHWeightInterfaceCouplings::cgJHEP   = { 0.0,     0.0,    -0.8,     0.0,     0.0,     0.8,     0.2,     0.2,    -1.0,    -0.6,     0.0,     1.0,     0.0     };
const std::vector<double> HHWeightInterfaceCouplings::c2gJHEP  = { 0.0,     0.0,     0.6,    -0.8,     0.0,    -1.0,    -0.2,    -0.2,     1.0,     0.6,     0.0,    -1.0,     0.0     };

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

  const std::string scanMode = cfg.getParameter<std::string>("scanMode");
  const bool isDEBUG = cfg.getParameter<bool>("isDEBUG");

  const std::string rwgt_nlo_mode = cfg.getParameter<std::string>("rwgt_nlo_mode");
  if     (rwgt_nlo_mode == "v1") { nlo_mode_ = HHWeightInterfaceNLOMode::v1; }
  else if(rwgt_nlo_mode == "v2") { nlo_mode_ = HHWeightInterfaceNLOMode::v2; }
  else if(rwgt_nlo_mode == "v3") { nlo_mode_ = HHWeightInterfaceNLOMode::v3; }

  kl_ = {};
  kt_ = {};
  c2_ = {};
  cg_ = {};
  c2g_ = {};
  bmNames_ = {};
  bmWeightNames_ = {};

  // always make sure we count in the SM point
  const std::size_t nof_bm = (scanMode == "default" || scanMode == "full") ? nof_JHEP : 1;

  //insert JHEP weight BM points
  for(std::size_t bmIdx = 0; bmIdx < nof_bm; ++bmIdx)
  {
    kl_.push_back(klJHEP[bmIdx]);
    kt_.push_back(ktJHEP[bmIdx]);
    c2_.push_back(c2JHEP[bmIdx]);
    cg_.push_back(cgJHEP[bmIdx]);
    c2g_.push_back(c2gJHEP[bmIdx]);
    const std::string bmName = (bmIdx == 0 ) ? "SM" : "BM" + std::to_string(bmIdx);

    assert(std::find(bmNames_.cbegin(), bmNames_.cend(), bmName) == bmNames_.cend());
    bmNames_.push_back(bmName);
    bmWeightNames_.push_back(getWeightName(bmName));
  }
  // Load a file with an specific scan, that we can decide at later stage on the analysis
  // save the closest shape BM to use this value on the evaluation of a BDT
  if(scanMode == "full" || scanMode == "additional")
  {
    if(! applicationLoadFile_klScan.empty()){
      const std::string applicationLoadPath_klScan = get_fullpath(applicationLoadFile_klScan);
      loadScanFile(applicationLoadPath_klScan, "kl_", 0, isDEBUG);
    }
    if(! applicationLoadFile_ktScan.empty())
    {
      const std::string applicationLoadPath_ktScan = get_fullpath(applicationLoadFile_ktScan);
      loadScanFile(applicationLoadPath_ktScan, "kt_", 1, isDEBUG);
    }
    if(! applicationLoadFile_c2Scan.empty())
    {
      const std::string applicationLoadPath_c2Scan = get_fullpath(applicationLoadFile_c2Scan);
      loadScanFile(applicationLoadPath_c2Scan, "c2_", 2, isDEBUG);
    }
    if(! applicationLoadFile_cgScan.empty())
    {
      const std::string applicationLoadPath_cgScan = get_fullpath(applicationLoadFile_cgScan);
      loadScanFile(applicationLoadPath_cgScan, "cg_", 2, isDEBUG);
    }
    if(! applicationLoadFile_c2gScan.empty())
    {
      const std::string applicationLoadPath_c2gScan = get_fullpath(applicationLoadFile_c2gScan);
      loadScanFile(applicationLoadPath_c2gScan, "c2g_", 2, isDEBUG);
    }
  }

  std::cout
      << get_human_line(this, __func__, __LINE__)
      << "Scanning " << bmNames_.size() << " benchmark scenarios: " << format_vstring(bmNames_)
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
    assert(line_split.size() == 5);
    std::vector<double> values;
    std::transform(
      line_split.begin(), line_split.end(), std::back_inserter(values),
      [](const std::string & value_string) -> double { return std::stod(value_string); }
    );
    double to_store = 1.0;
    for(std::size_t colIdx = 0; colIdx < values.size(); ++colIdx)
    {
      const double value = values[colIdx];
      switch(colIdx)
      {
        case 0:
          kl_.push_back(value);
          if (idx == 0) to_store = value;
          break;
        case 1:
          kt_.push_back(value);
          if (idx == 1) to_store = value;
          break;
        case 2:
          c2_.push_back(value);
          if (idx == 2) to_store = value;
          break;
        case 3:
          cg_.push_back(value);
          if (idx == 3) to_store = value;
          break;
        case 4:
          c2g_.push_back(value);
          if (idx == 4) to_store = value;
          break;
        default:
          assert(0);
      }
    }
    std::string bmName = prefix;
    bmName += to_string_with_precision(to_store);
    boost::replace_all(bmName, "-", "m");
    boost::replace_all(bmName, ".", "p");
    if(isDEBUG)
    {
      std::cout << "bmName = " << bmName << '\n';
    }

    assert(std::find(bmNames_.cbegin(), bmNames_.cend(), bmName) == bmNames_.cend());
    bmNames_.push_back(bmName);
    bmWeightNames_.push_back(getWeightName(bmName));
  }
}

std::string
HHWeightInterfaceCouplings::getWeightName(const std::string & suffix)
{
  return "Weight_" + suffix;
}

void
HHWeightInterfaceCouplings::add(const std::array<double, 5> & couplings,
                                const std::string & name)
{
  if(std::find(bmNames_.cbegin(), bmNames_.cend(), name) != bmNames_.cend())
  {
    throw cmsException(this, __func__, __LINE__) << "The coupling name has already been booked: " << name;
  }
  kl_.push_back(couplings.at(0));
  kt_.push_back(couplings.at(1));
  c2_.push_back(couplings.at(2));
  cg_.push_back(couplings.at(3));
  c2g_.push_back(couplings.at(4));
  bmNames_.push_back(name);
  bmWeightNames_.push_back(getWeightName(name));
}

std::vector<std::string>
HHWeightInterfaceCouplings::get_weight_names() const
{
  return bmWeightNames_;
}

std::vector<std::string>
HHWeightInterfaceCouplings::get_bm_names() const
{
  return bmNames_;
}

std::vector<double>
HHWeightInterfaceCouplings::kl() const
{
  return kl_;
}

std::vector<double>
HHWeightInterfaceCouplings::kt() const
{
  return kt_;
}

std::vector<double>
HHWeightInterfaceCouplings::c2() const
{
  return c2_;
}

std::vector<double>
HHWeightInterfaceCouplings::cg() const
{
  return cg_;
}

std::vector<double>
HHWeightInterfaceCouplings::c2g() const
{
  return c2g_;
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
