#include "tthAnalysis/HiggsToTauTau/interface/compFakeRateAuxFunctions.h"

#include <TGraphAsymmErrors.h> // TGraphAsymmErrors
#include <TH1.h> // TH1D
#include <TMath.h> // TMath::Nint()

#include <iostream> // std::cout
#include <cassert> // assert()

TArrayD
convertToTArrayD(const std::vector<double> & binEdges)
{
  const int numBins = binEdges.size() - 1;
  assert(numBins >= 1);

  TArrayD binEdges_array(numBins + 1);
  for(int idxBin = 0; idxBin < numBins; ++idxBin)
  {
    binEdges_array[idxBin]     = binEdges[idxBin];
    binEdges_array[idxBin + 1] = binEdges[idxBin + 1];
  }
  return binEdges_array;
}

namespace
{
  double constexpr
  square(double x)
  {
    return x * x;
  }
}

void
compFakeRate(double nPass,
             double nPassErr,
             double nFail,
             double nFailErr,
             double & avFakeRate,
             double & avFakeRateErrUp,
             double & avFakeRateErrDown,
             bool & errorFlag,
	     bool cap_uncerts)
{ 
  const double sumWeights = nPass + nFail;
  const double sumWeights2 = square(nPassErr) + square(nFailErr);

  if(sumWeights > 0. && sumWeights2 > 0.)
  {
    const double n_eff = square(sumWeights/std::sqrt(sumWeights2));
    const double sf = n_eff/(sumWeights);
    const Int_t nPass_int = std::max(TMath::Nint(sf * nPass), 0);

    TH1 * const histogram_pass_tmp = new TH1D(
      "histogram_pass_tmp", "histogram_pass_tmp", 1, -0.5, +0.5
    );
    histogram_pass_tmp->SetBinContent(1, nPass_int);
    histogram_pass_tmp->SetBinError  (1, std::sqrt(nPass_int));
    const Int_t nFail_int = std::max(TMath::Nint(sf * nFail), 0);

    TH1 * const histogram_pass_plus_fail_tmp = new TH1D(
      "histogram_pass_plus_fail_tmp", "histogram_pass_plus_fail_tmp", 1, -0.5, +0.5
    );
    histogram_pass_plus_fail_tmp->SetBinContent(1, nPass_int + nFail_int);
    histogram_pass_plus_fail_tmp->SetBinError(1, std::sqrt(nPass_int + nFail_int));

    TGraphAsymmErrors * const graph_pass_div_pass_plus_fail_tmp = new TGraphAsymmErrors(1);
    graph_pass_div_pass_plus_fail_tmp->Divide(histogram_pass_tmp, histogram_pass_plus_fail_tmp, "cp");

    double dummy;
    graph_pass_div_pass_plus_fail_tmp->GetPoint(0, dummy, avFakeRate);

    if(cap_uncerts){ // Cap uncert.s by 0.01
      avFakeRateErrUp   = std::max(graph_pass_div_pass_plus_fail_tmp->GetErrorYhigh(0), 1.e-2); 
      avFakeRateErrDown = std::max(graph_pass_div_pass_plus_fail_tmp->GetErrorYlow(0), 1.e-2);  
    }else{ // Use actual uncapped uncert.s
      avFakeRateErrUp   = graph_pass_div_pass_plus_fail_tmp->GetErrorYhigh(0); 
      avFakeRateErrDown = graph_pass_div_pass_plus_fail_tmp->GetErrorYlow(0);  
    }
    delete histogram_pass_tmp;
    delete histogram_pass_plus_fail_tmp;
    delete graph_pass_div_pass_plus_fail_tmp;
    errorFlag = false;

    std::cout << " nPass = "      << nPass      << " +/- " << nPassErr << " (int = " << nPass_int << "),"
                 " nFail = "      << nFail      << " +/- " << nFailErr << " (int = " << nFail_int << ") -->"
                 " avFakeRate = " << avFakeRate << " + "   << avFakeRateErrUp
                                                << " - "   << avFakeRateErrDown
              << '\n'
    ;
  }
  else
  {
    avFakeRate        = 0.5;
    avFakeRateErrUp   = 0.5;
    avFakeRateErrDown = 0.5;
    errorFlag = true;
    std::cout << " sumWeights = "  << sumWeights << ","
                 " sumWeights2 = " << sumWeights2 << " -->"
                 " avFakeRate = "  << avFakeRate << " + " << avFakeRateErrUp
                                                 << " - " << avFakeRateErrDown
              << '\n'
    ;
  }
}
