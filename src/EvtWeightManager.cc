#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile(), loadTH1(), loadTH2()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile
#include <TH1.h> // TH1
#include <TH2.h> // TH2

#include <cassert> // assert()
#include <iostream> // std::cout

EvtWeightManager::EvtWeightManager(const edm::ParameterSet & cfg,
                                   bool isDebug)
  : histogram_file_(nullptr)
  , binnedHistogram_1var_(nullptr)
  , binnedHistogram_2var_(nullptr)
  , isDebug_(isDebug)
{
  const std::string histogramFile = cfg.getParameter<std::string>("histogramFile");
  const std::string histogramName = cfg.getParameter<std::string>("histogramName");
  const std::string branchNameXaxis = cfg.getParameter<std::string>("branchNameXaxis");
  const std::string branchNameYaxis = cfg.getParameter<std::string>("branchNameYaxis");
  const std::string branchTypeXaxis = cfg.getParameter<std::string>("branchTypeXaxis");
  const std::string branchTypeYaxis = cfg.getParameter<std::string>("branchTypeYaxis");

  assert(! histogramFile.empty() && ! histogramName.empty() && ! branchNameXaxis.empty() && ! branchTypeXaxis.empty());
  histogram_file_ = openFile(LocalFileInPath(histogramFile));

  binnedHistogram_varName_x_ = branchNameXaxis;
  binnedHistogram_varType_x_ = branchTypeXaxis;
  if(! branchNameXaxis.empty() && ! branchNameYaxis.empty())
  {
    binnedHistogram_2var_ = loadTH2(histogram_file_, histogramName);
    binnedHistogram_varName_y_ = branchNameYaxis;
    binnedHistogram_varType_y_ = branchTypeYaxis;
  }
  else
  {
    binnedHistogram_1var_ = loadTH1(histogram_file_, histogramName);
  }
  std::cout << "Loaded histogram '" << histogramName << "' from file " << histogramFile << '\n';
}

EvtWeightManager::~EvtWeightManager()
{
  if(histogram_file_)
  {
    histogram_file_->Close();
  }
  delete histogram_file_;
}

void
EvtWeightManager::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  if(binnedHistogram_varType_x_ == "UChar_t")
  {
    bai.setBranchAddress(var_x_uchar_, binnedHistogram_varName_x_);
  }
  else if(binnedHistogram_varType_x_ == "Float_t")
  {
    bai.setBranchAddress(var_x_float_, binnedHistogram_varName_x_);
  }

  if(binnedHistogram_2var_)
  {
    if(binnedHistogram_varType_y_ == "UChar_t")
    {
      bai.setBranchAddress(var_y_uchar_, binnedHistogram_varName_y_);
    }
    else if(binnedHistogram_varType_y_ == "Float_t")
    {
      bai.setBranchAddress(var_y_float_, binnedHistogram_varName_y_);
    }
  }
}

int
EvtWeightManager::getBinIdx_1D() const
{
  Double_t val_x = 0.;
  if(binnedHistogram_varType_x_ == "UChar_t")
  {
    val_x = static_cast<Double_t>(var_x_uchar_);
  }
  else if(binnedHistogram_varType_x_ == "Float_t")
  {
    val_x = static_cast<Double_t>(var_x_float_);
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_x_
    ;
  }
  const TAxis * const xAxis = binnedHistogram_1var_->GetXaxis();
  assert(xAxis);
  const Int_t bin_x = xAxis->FindBin(val_x);
  assert(bin_x >= 0);

  if(isDebug_)
  {
    std::cout << get_human_line(this, __func__, __LINE__)
              << ": bin_x("
              << xAxis->GetBinLowEdge(bin_x) << " <= " << val_x << " < "
              << xAxis->GetBinUpEdge(bin_x) << "; "
              << binnedHistogram_varName_x_ << ") = " << bin_x << '\n'
    ;
  }

  return bin_x;
}

std::pair<int, int>
EvtWeightManager::getBinIdx_2D() const
{
  Double_t val_x = 0.;
  if(binnedHistogram_varType_x_ == "UChar_t")
  {
    val_x = static_cast<Double_t>(var_x_uchar_);
  }
  else if(binnedHistogram_varType_x_ == "Float_t")
  {
    val_x = static_cast<Double_t>(var_x_float_);
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_x_
    ;
  }
  const TAxis * const xAxis = binnedHistogram_2var_->GetXaxis();
  assert(xAxis);
  const Int_t bin_x = xAxis->FindBin(val_x);
  assert(bin_x >= 0);

  Double_t val_y = 0.;
  if(binnedHistogram_varType_y_ == "UChar_t")
  {
    val_y = static_cast<Double_t>(var_y_uchar_);
  }
  else if(binnedHistogram_varType_y_ == "Float_t")
  {
    val_y = static_cast<Double_t>(var_y_float_);
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_y_
    ;
  }
  const TAxis * const yAxis = binnedHistogram_2var_->GetYaxis();
  assert(yAxis);
  const Int_t bin_y = yAxis->FindBin(val_y);
  assert(bin_y >= 0);

  if(isDebug_)
  {
    std::cout << get_human_line(this, __func__, __LINE__)
              << ": binIdx("
              << xAxis->GetBinLowEdge(bin_x) << " <= " << val_x << " < "
              << xAxis->GetBinUpEdge(bin_x) << " x "
              << yAxis->GetBinLowEdge(bin_y) << " <= " << val_y << " < "
              << yAxis->GetBinUpEdge(bin_y) << "; "
              << binnedHistogram_varName_x_ << " x " << binnedHistogram_varName_y_
              << ") = " << bin_x << ", " << bin_y << '\n'
    ;
  }

  return std::make_pair(bin_x, bin_y);
}

double
EvtWeightManager::getWeight() const
{
  double weight = 0.;
  if(binnedHistogram_1var_)
  {
    const int bin_x = getBinIdx_1D();
    weight = binnedHistogram_1var_->GetBinContent(bin_x);

    if(isDebug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__)
                << ": weight = " << weight << '\n'
      ;
    }
  }
  else if(binnedHistogram_2var_)
  {
    const std::pair<int, int> bin_xy = getBinIdx_2D();

    weight = binnedHistogram_2var_->GetBinContent(bin_xy.first, bin_xy.second);

    if(isDebug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__)
                << ": weight = " << weight << '\n'
      ;
    }
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "None of the histograms are initialized"
    ;
  }

  return weight;
}

int
EvtWeightManager::getDimension() const
{
  if(binnedHistogram_1var_)
  {
    return 1;
  }
  else if(binnedHistogram_2var_)
  {
    return 2;
  }
  return 0;
}

TH1 *
EvtWeightManager::getHistogram_1D() const
{
  return binnedHistogram_1var_;
}

TH2 *
EvtWeightManager::getHistogram_2D() const
{
  return binnedHistogram_2var_;
}
