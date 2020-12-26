#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceLOtoNLO.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"          // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterface2.h"    // HHWeightInterface2
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // dumpHistogram()

#include <TString.h> // Form()
#include <TMath.h>   // TMath::Nint()

#include <stdlib.h>  // atof()
#include <algorithm> // std::min()
#include <fstream>   // std::ifstream
#include <sstream>   // std::istringstream
#include <iostream>  // std::cout, std::endl

namespace
{
  std::vector<std::vector<double>>
  loadCoeffFile(const LocalFileInPath & fileName, bool isDEBUG)
  {
    std::vector<std::vector<double>> retVal;
    if ( fileName.fullPath().empty() )
    {
      throw cmsException(__func__, __LINE__)
        << " Failed to find file = '" << fileName << "' !!\n";
    }
    std::ifstream inputFile(fileName.fullPath());
    std::string line;
    while ( std::getline(inputFile, line) ) 
    {
      std::istringstream line_stringstream(line);
      std::vector<double> row;
      std::string value;
      while ( std::getline(line_stringstream, value, ',') ) 
      {
        row.push_back(atof(value.c_str()));
      }
      retVal.push_back(row);
    }
    return retVal;
  }

  const TH1*
  compXsec(const std::string & histogramName, const std::vector<double> & eft_parameters, const std::vector<std::vector<double>> & A, bool isDEBUG)
  {
    assert(eft_parameters.size() == 5);
    double c3  = eft_parameters[0];
    double ct  = eft_parameters[1];
    double ctt = eft_parameters[2];
    double cg  = eft_parameters[3];
    double cgg = eft_parameters[4];

    std::vector<double> couplings = { 
      pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
      ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
      ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
      pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
      pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg 
    };

    // WARNING: the values of the parameters xMin, xMax, and binWidth
    //          need to match the values used in the 'LO-Ais-13TeV.csv' and 'NLO-Ais-13TeV.csv' files !!
    const double xMin = 240.;
    const double xMax = 1040.;
    const double binWidth = 20.;

    int numBins = TMath::Nint((xMax - xMin)/binWidth);
    TH1* histogram = new TH1D(histogramName.data(), histogramName.data(), numBins, xMin, xMax);

    for ( int idxBin = 1; idxBin <= numBins; ++idxBin )
    {
      double mHH = histogram->GetBinCenter(idxBin);
      const std::vector<double> A_at_mHH = A[idxBin - 1];
      assert(couplings.size() >= (A_at_mHH.size() - 1) && std::fabs(A_at_mHH[0] - mHH) < 1.);
      double dXsec = 0.;
      for( size_t i = 1; i < A_at_mHH.size(); ++i )
      {
        dXsec += A_at_mHH[i]*couplings[i - 1];
      }
      if ( dXsec < 0. ) dXsec = 0.;
      histogram->SetBinContent(idxBin, dXsec);
      histogram->SetBinError(idxBin, 0.);
    }
    if ( histogram->Integral() > 0. )
    {
      histogram->Scale(1./histogram->Integral());
    }
    return histogram;
  }
  
  std::vector<double> 
  convertCouplingsToEWChL(double kl, double kt, double c2, double cg, double c2g)
  {
    std::vector<double> retVal = { kl, kt, c2, (2./3.)*cg, (-1./3.)*c2g };
    return retVal;
  }
}

HHWeightInterfaceLOtoNLO::HHWeightInterfaceLOtoNLO(double max_reWeight, bool isDEBUG)
  : xsecFileName_lo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceLOtoNLO/LO-Ais-13TeV.csv")
  , xsecFileName_nlo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceLOtoNLO/NLO-Ais-13TeV.csv")
  , max_reWeight_(max_reWeight)
  , isDEBUG_(isDEBUG)
{
  std::vector<std::string> bmNames = { "SM", "BM1", "BM2", "BM3", "BM4", "BM5", "BM6", "BM7", "BM8", "BM9", "BM10", "BM11", "BM12" };
  size_t nof_JHEP = bmNames.size();
  const std::vector<double> & klJHEP = HHWeightInterface2::klJHEP();
  const std::vector<double> & ktJHEP = HHWeightInterface2::ktJHEP();
  const std::vector<double> & c2JHEP = HHWeightInterface2::c2JHEP();
  const std::vector<double> & cgJHEP = HHWeightInterface2::cgJHEP();
  const std::vector<double> & c2gJHEP = HHWeightInterface2::c2gJHEP();
  if ( klJHEP.size()  != nof_JHEP || 
       ktJHEP.size()  != nof_JHEP || 
       c2JHEP.size()  != nof_JHEP || 
       cgJHEP.size()  != nof_JHEP || 
       c2gJHEP.size() != nof_JHEP )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid coupling parameters !!\n";
  }

  std::vector<std::vector<double>> A_lo = loadCoeffFile(xsecFileName_lo_, isDEBUG);
  std::vector<std::vector<double>> A_nlo = loadCoeffFile(xsecFileName_nlo_, isDEBUG);

  for ( std::size_t bmIdx = 0; bmIdx < nof_JHEP; ++bmIdx )
  {
    const std::string & bmName = bmNames[bmIdx];
    std::vector<double> eft_parameters = convertCouplingsToEWChL(klJHEP[bmIdx], ktJHEP[bmIdx], c2JHEP[bmIdx], cgJHEP[bmIdx], c2gJHEP[bmIdx]);

    std::string histogramName_lo = Form("%s_lo", bmName.data());
    const TH1 * histogram_lo = compXsec(histogramName_lo, eft_parameters, A_lo, isDEBUG_);    
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_lo);
    }
    dXsec_lo_[bmName] = histogram_lo;

    std::string histogramName_nlo = Form("%s_nlo", bmName.data());
    const TH1 * histogram_nlo = compXsec(histogramName_nlo, eft_parameters, A_nlo, isDEBUG_);
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_nlo);
    }
    dXsec_nlo_[bmName] = histogram_nlo;

    std::string histogramName_reWeights = Form("%s_reWeights", bmName.data());
    TH1* histogram_reWeights = (TH1*)histogram_lo->Clone(histogramName_reWeights.data());    
    histogram_reWeights->SetName(histogramName_reWeights.data());
    histogram_reWeights->SetTitle(histogramName_reWeights.data());
    histogram_reWeights->Reset();
    assert(histogram_lo->GetNbinsX() == histogram_nlo->GetNbinsX());
    int numBins = histogram_lo->GetNbinsX();
    for ( int idxBin = 1; idxBin <= numBins; ++idxBin )
    {
      double loWeight = histogram_lo->GetBinContent(idxBin);
      double nloWeight = histogram_nlo->GetBinContent(idxBin);
      double reWeight = 1.;
      if      ( nloWeight > 0. ) reWeight = std::min(max_reWeight_, nloWeight/loWeight);
      else if (  loWeight > 0. ) reWeight = max_reWeight_;
      else                       reWeight = 1.;
      histogram_reWeights->SetBinContent(idxBin, reWeight);
      histogram_reWeights->SetBinError(idxBin, 0.);
    }
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_reWeights);
    }
    reWeights_[bmName] = histogram_reWeights;
  }
}

HHWeightInterfaceLOtoNLO::~HHWeightInterfaceLOtoNLO()
{}

namespace
{
  double
  getReWeight_private(const TH1 * histogram_reWeight, double mHH)
  {
    const TAxis * xAxis = histogram_reWeight->GetXaxis();
    int firstBin = 1;
    int lastBin = xAxis->GetNbins();
    const double epsilon = 1.e-1;
    double xMin = xAxis->GetBinLowEdge(firstBin) + epsilon;
    double xMax = xAxis->GetBinUpEdge(lastBin) - epsilon;
    double x = mHH;
    if ( x < xMin ) x = xMin;
    if ( x > xMax ) x = xMax;
    int idxBin = (const_cast<TH1 *>(histogram_reWeight))->FindBin(x);
    assert(idxBin >= firstBin && idxBin <= lastBin);
    double reWeight = histogram_reWeight->GetBinContent(idxBin);
    return reWeight;
  }
}

double
HHWeightInterfaceLOtoNLO::getReWeight(const std::string & bmName,
                                      double mHH,
                                      double cosThetaStar,
                                      bool isDEBUG) const
{
  std::map<std::string, const TH1 *>::const_iterator reWeight_iter = reWeights_.find(bmName);
  if ( reWeight_iter == reWeights_.end() )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid parameter 'bmName' = " << bmName << " !!\n";
  }
  double reWeight = getReWeight_private(reWeight_iter->second, mHH);
  if ( isDEBUG )
  {
    std::cout << "<HHWeightInterfaceLOtoNLO::getReWeight>: bmName = '" << bmName << "', mHH = " << mHH << " --> reWeight = " << reWeight << std::endl;
  }
  return reWeight;
}
