#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // openFile(), loadTH1(), loadTH2()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile
#include <TH1.h> // TH1
#include <TH2.h> // TH2

#include <cassert> // assert()
#include <iostream> // std::cout

EvtWeightManager::EvtWeightManager(const edm::ParameterSet & cfg)
  : histogram_file_(nullptr)
  , binnedHistogram_1var_(nullptr)
  , binnedHistogram_2var_(nullptr)
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
  delete binnedHistogram_1var_;
  delete binnedHistogram_2var_;
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

double
EvtWeightManager::getWeight() const
{
  double weight = 0.;
  if(binnedHistogram_1var_)
  {
    Int_t bin_x = -1;
    if(binnedHistogram_varType_x_ == "UChar_t")
    {
      bin_x = binnedHistogram_1var_->GetXaxis()->FindBin(static_cast<Double_t>(var_x_uchar_));
    }
    else if(binnedHistogram_varType_x_ == "Float_t")
    {
      bin_x = binnedHistogram_1var_->GetXaxis()->FindBin(static_cast<Double_t>(var_x_float_));
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_x_
      ;
    }
    assert(bin_x >= 0);

    weight = binnedHistogram_1var_->GetBinContent(bin_x);
  }
  else if(binnedHistogram_2var_)
  {
    Int_t bin_x = -1;
    Int_t bin_y = -1;
    if(binnedHistogram_varType_x_ == "UChar_t")
    {
      bin_x = binnedHistogram_2var_->GetXaxis()->FindBin(static_cast<Double_t>(var_x_uchar_));
    }
    else if(binnedHistogram_varType_x_ == "Float_t")
    {
      bin_x = binnedHistogram_2var_->GetXaxis()->FindBin(static_cast<Double_t>(var_x_float_));
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_x_
      ;
    }
    assert(bin_x >= 0);

    if(binnedHistogram_varType_y_ == "UChar_t")
    {
      bin_y = binnedHistogram_2var_->GetYaxis()->FindBin(static_cast<Double_t>(var_y_uchar_));
    }
    else if(binnedHistogram_varType_y_ == "Float_t")
    {
      bin_y = binnedHistogram_2var_->GetYaxis()->FindBin(static_cast<Double_t>(var_y_float_));
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
        << "Unknown type for the x-axis quantity: " << binnedHistogram_varType_y_
      ;
    }
    assert(bin_y >= 0);

    weight = binnedHistogram_2var_->GetBinContent(bin_x, bin_y);
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "None of the histograms are initialized"
    ;
  }

  if(weight == 0.)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << ": got 0 event weight\n";
  }
  return weight;
}
