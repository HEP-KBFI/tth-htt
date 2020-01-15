#include "tthAnalysis/HiggsToTauTau/interface/TauESTool.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

#include <TString.h> // Form()

#include <TFile.h> // TFile
#include <TH1.h> // TH1

TauESTool::TauESTool(int era,
                     int central_or_shift,
                     bool debug)
  : central_or_shift_(central_or_shift)
{
  const std::string era_str = [&era, this]() -> std::string
  {
    switch(era)
    {
      case kEra_2016: return "2016Legacy";
      case kEra_2017: return "2017ReReco";
      case kEra_2018: return "2018ReReco";
      default: throw cmsException(this, __func__, __LINE__) << "Invalid era: " << era;
    }
  }();
  const std::string input_name = Form("TauPOG/TauIDSFs/data/TauES_dm_MVAoldDM2017v2_%s.root", era_str.data());
  const std::string input_name_full = LocalFileInPath(input_name).fullPath();
  TFile * input = TFile::Open(input_name_full.data(), "read");
  if(! input || input -> IsZombie())
  {
    throw cmsException(this, __func__, __LINE__) << "Cannot open file: " << input_name;
  }

  const std::string hist_name = "tes";
  TH1 * tes = static_cast<TH1 *>(input->Get(hist_name.data()));
  if(! tes)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unable to load histogram '" << hist_name << "' from file" << input_name_full
    ;
  }

  const int ndm = tes->GetNbinsX();
  for(int dm_idx = 0; dm_idx < ndm; ++dm_idx)
  {
    sf_[dm_idx] = tes->GetBinContent(dm_idx + 1);
    sfErr_[dm_idx] = tes->GetBinError(dm_idx + 1);
  }
  input->Close();

  if(debug)
  {
    std::cout << "Loaded the following tau ES SF from file '" << input_name_full << "' for era " << era << ":\n";
    for(const auto & kv: sf_)
    {
      std::cout << "  DM = " << kv.first << " -> SF = " << kv.second << " +/- " << sfErr_[kv.first] << '\n';
    }
  }
}

void
TauESTool::set_central_or_shift(int central_or_shift)
{
  central_or_shift_ = central_or_shift;
}

double
TauESTool::getTES(int dm,
                  int genmatch) const
{
  if(genmatch != 5 || central_or_shift_ == kHadTauPt_uncorrected)
  {
    return 1.0;
  }
  if(! sf_.count(dm))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid decay mode: " << dm;
  }

  double sf = sf_.at(dm);
  double sfErr = sfErr_.at(dm);
  switch(central_or_shift_)
  {
    case kHadTauPt_central:   return sf;
    case kHadTauPt_shiftUp:   return sf + sfErr;
    case kHadTauPt_shiftDown: return sf - sfErr;
    default: throw cmsException(this, __func__, __LINE__) << "Invalid central_or_shift option: " << central_or_shift_;
  }
}
