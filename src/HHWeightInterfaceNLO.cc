#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceNLO.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"          // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceLO.h"   // HHWeightInterfaceLO
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // dumpHistogram(), getTArrayDfromVector()
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"   // format_vdouble

#include <TString.h> // Form()
#include <TMath.h>   // TMath::Nint()
#include <TArrayD.h> // TArrayD
#include <TAxis.h>   // TAxis

#include <stdlib.h>  // atof()
#include <set>       // std::set
#include <algorithm> // std::min(), std::sort()
#include <fstream>   // std::ifstream
#include <sstream>   // std::istringstream
#include <iostream>  // std::cout, std::endl
#include <assert.h>  // assert

enum { kLO, kNLO };

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
      std::string value;

      std::vector<double> row;
      while ( std::getline(line_stringstream, value, ',') ) 
      {
        row.push_back(atof(value.c_str()));
      }
      retVal.push_back(row);
    }
    return retVal;
  }

  std::vector<std::vector<double>>
  loadCoeffFile_V2(const LocalFileInPath & fileName, const std::string & error_set, bool isDEBUG)
  {
    std::vector<std::vector<double>> retVal;
    if ( fileName.fullPath().empty() )
    {
      throw cmsException(__func__, __LINE__)
        << " Failed to find file = '" << fileName << "' !!\n";
    }
    std::ifstream inputFile(fileName.fullPath());
    std::string error_set_tmp = "\"" + error_set + "\"";
    std::string line;
    while ( std::getline(inputFile, line) ) 
    {
      std::istringstream line_stringstream(line);
      std::string value;

      if ( error_set_tmp != "\"V0\"" )
      {
        std::getline(line_stringstream, value, ',');
        if ( value != error_set_tmp ) continue;
      }

      std::vector<double> row;
      while ( std::getline(line_stringstream, value, ',') ) 
      {
        row.push_back(atof(value.c_str()));
      }
      if ( error_set_tmp == "\"V0\"" )
      {
        size_t N = row.size() + 1;
        for ( size_t i = 0; i < N; ++i )
        {
          row.push_back(0.);
        }
      }
      retVal.push_back(row);
    }
    return retVal;
  }

  std::vector<double>
  fix_couplings_CMS(const std::vector<double> & couplings, Era era)
  {
    std::vector<double> retVal = couplings;
    if ( era == Era::k2016 )
    {
      retVal[0] = couplings[1];
      retVal[1] = couplings[0];
    }
    else if ( era == Era::k2017 || era == Era::k2018 )
    {
      retVal[0] = couplings[1];
      retVal[1] = couplings[0];
      retVal[4] = 1.0;
    }
    else throw cmsException(__func__, __LINE__) << "Invalid parameter 'era' = " << (int)era << " !!\n";
    return retVal;
  }

  std::vector<double> 
  convertCouplingsToEWChL(double kl, double kt, double c2, double cg, double c2g)
  {
    std::vector<double> retVal = { kl, kt, c2, (2./3.)*cg, (-1./3.)*c2g };
    return retVal;
  }

  std::vector<double> 
  convertCouplingsToEWChL(const std::vector<double> & couplings)
  {
    return convertCouplingsToEWChL(couplings[0], couplings[1], couplings[2], couplings[3], couplings[4]);
  }

  std::vector<double>
  getCouplings(const std::vector<double> & eft_parameters, int mode)
  {
    assert(eft_parameters.size() == 5);
    double c3  = eft_parameters[0];
    double ct  = eft_parameters[1];
    double ctt = eft_parameters[2];
    double cg  = eft_parameters[3];
    double cgg = eft_parameters[4];

    std::vector<double> couplings;
    if ( mode == kLO ) 
    { 
      couplings = {
        pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
        ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
        ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg
      };
    }
    else if ( mode == kNLO ) 
    { 
      couplings = {
        pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
        ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
        ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
        pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
        pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg 
      };
    }
    else throw cmsException(__func__, __LINE__) << "Invalid mode parameter; supported values are LO and NLO !!\n";
    return couplings;
  }

  const TH1*
  compXsec_V1(const std::string & histogramName, const std::vector<double> & eft_parameters, const std::vector<std::vector<double>> & A, int mode, bool isDEBUG)
  {
    std::vector<double> couplings = getCouplings(eft_parameters, mode);

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
      assert(A_at_mHH.size() >= (couplings.size() + 1) && std::fabs(A_at_mHH[0] - mHH) < 1.);
      double dXsec = 0.;
      for( size_t i = 0; i < couplings.size(); ++i )
      {
        dXsec += couplings[i]*A_at_mHH[i + 1];
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
  getBinEdges_sorted(const std::set<double> & binEdges)
  {
    std::vector<double> binEdges_sorted;
    for ( std::set<double>::const_iterator binEdge = binEdges.begin();
          binEdge != binEdges.end(); ++binEdge ) {
      binEdges_sorted.push_back(*binEdge);
    }
    std::sort(binEdges_sorted.begin(), binEdges_sorted.end()); 
    return binEdges_sorted;
  }

  const TH2*
  compXsec_V2(const std::string & histogramName, const std::vector<double> & eft_parameters, const std::vector<std::vector<double>> & A, int mode, bool isDEBUG)
  {
    std::vector<double> couplings = getCouplings(eft_parameters, mode);

    std::set<double> binEdges_mHH;
    std::set<double> binEdges_cosTheta;
    for ( std::vector<std::vector<double>>::const_iterator row = A.begin(); 
          row != A.end(); ++row ) {
      double min_mHH = row->at(0);
      double max_mHH = row->at(1);
      binEdges_mHH.insert(min_mHH);
      binEdges_mHH.insert(max_mHH);

      double min_cosTheta = row->at(2);
      double max_cosTheta = row->at(3);
      binEdges_cosTheta.insert(min_cosTheta);
      binEdges_cosTheta.insert(max_cosTheta);
    }

    std::vector<double> binEdges_mHH_sorted = getBinEdges_sorted(binEdges_mHH);
    int numBinsX = binEdges_mHH_sorted.size() - 1;
    assert(numBinsX >= 1);
    TArrayD binEdgesX = getTArrayDfromVector(binEdges_mHH_sorted);

    std::vector<double> binEdges_cosTheta_sorted = getBinEdges_sorted(binEdges_cosTheta);
    int numBinsY = binEdges_cosTheta_sorted.size() - 1;
    assert(numBinsY >= 1);
    TArrayD binEdgesY = getTArrayDfromVector(binEdges_cosTheta_sorted);

    TH2* histogram = new TH2D(histogramName.data(), histogramName.data(), numBinsX, binEdgesX.GetArray(), numBinsY, binEdgesY.GetArray());
    TAxis* xAxis = histogram->GetXaxis();
    TAxis* yAxis = histogram->GetYaxis();

    for ( std::vector<std::vector<double>>::const_iterator row = A.begin(); 
          row != A.end(); ++row ) {
      double min_mHH = row->at(0);
      double max_mHH = row->at(1);
      double mHH = 0.5*(min_mHH + max_mHH);
      int idxBinX = xAxis->FindBin(mHH);
      assert(idxBinX >= 1 && idxBinX <= numBinsX);

      double min_cosTheta = row->at(2);
      double max_cosTheta = row->at(3);
      double cosTheta = 0.5*(min_cosTheta + max_cosTheta);
      int idxBinY = yAxis->FindBin(cosTheta);
      assert(idxBinY >= 1 && idxBinY <= numBinsY);

      assert(row->size() >= (couplings.size() + 4));

      double dXsec = 0.;
      for( size_t i = 0; i < couplings.size(); ++i )
      {
        dXsec += couplings[i]*row->at(i + 4);
      }
      if ( dXsec < 0. ) dXsec = 0.;
      histogram->SetBinContent(idxBinX, idxBinY, dXsec);
      histogram->SetBinError(idxBinX, idxBinY, 0.);
    }
    if ( histogram->Integral() > 0. )
    {
      histogram->Scale(1./histogram->Integral());
    }
    return histogram;
  }
  
  double 
  compReWeight(double loWeight, double nloWeight, double max_weight)
  {
    double weight = 1.;
    if      (  loWeight > 0. ) weight = std::min(max_weight, nloWeight/loWeight);
    else if ( nloWeight > 0. ) weight = max_weight;
    else                       weight = 1.;
    return weight;
  }

  TH1*
  makeHistogram_V1_weights(const std::string & histogramName_weights, const TH1 * histogram_lo, const TH1 * histogram_nlo, double max_weight)
  {
    TH1* histogram_weights = (TH1*)histogram_lo->Clone(histogramName_weights.data());    
    histogram_weights->SetName(histogramName_weights.data());
    histogram_weights->SetTitle(histogramName_weights.data());
    histogram_weights->Reset();
    assert(histogram_lo->GetNbinsX() == histogram_nlo->GetNbinsX());
    int numBins = histogram_lo->GetNbinsX();
    for ( int idxBin = 1; idxBin <= numBins; ++idxBin )
    {
      double loWeight = histogram_lo->GetBinContent(idxBin);
      double nloWeight = histogram_nlo->GetBinContent(idxBin);
      double weight = compReWeight(loWeight, nloWeight, max_weight);
      histogram_weights->SetBinContent(idxBin, weight);
      histogram_weights->SetBinError(idxBin, 0.);
    }
    return histogram_weights;
  }

  TH2*
  makeHistogram_V2_weights(const std::string & histogramName_weights, const TH2 * histogram_lo, const TH2 * histogram_nlo, double max_weight)
  {
    TH2* histogram_weights = (TH2*)histogram_lo->Clone(histogramName_weights.data());    
    histogram_weights->SetName(histogramName_weights.data());
    histogram_weights->SetTitle(histogramName_weights.data());
    histogram_weights->Reset();
    assert(histogram_lo->GetNbinsX() == histogram_nlo->GetNbinsX() && histogram_lo->GetNbinsY() == histogram_nlo->GetNbinsY());
    int numBinsX = histogram_lo->GetNbinsX();
    int numBinsY = histogram_lo->GetNbinsY();
    for ( int idxBinX = 1; idxBinX <= numBinsX; ++idxBinX )
    {
      for ( int idxBinY = 1; idxBinY <= numBinsY; ++idxBinY )
      {
        double loWeight = histogram_lo->GetBinContent(idxBinX, idxBinY);
        double nloWeight = histogram_nlo->GetBinContent(idxBinX, idxBinY);
        double weight = compReWeight(loWeight, nloWeight, max_weight);
        histogram_weights->SetBinContent(idxBinX, idxBinY, weight);
        histogram_weights->SetBinError(idxBinX, idxBinY, 0.);
      }
    }
    return histogram_weights;
  }
}

HHWeightInterfaceNLO::HHWeightInterfaceNLO(Era era, bool apply_coupling_fix_CMS, double max_weight, bool isDEBUG)
  : xsecFileName_V1_lo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceNLO/LO-Ais-13TeV.csv")
  , xsecFileName_V1_nlo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceNLO/NLO-Ais-13TeV.csv")
  , xsecFileName_V2_lo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceNLO/pm_mg_LO-Ais-13TeV_V2.txt")
  , xsecFileName_V2_nlo_("tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceNLO/pm_pw_NLO-Ais-13TeV_V2.txt")
  , era_(era)
  , apply_coupling_fix_CMS_(apply_coupling_fix_CMS)
  , max_weight_(max_weight)
  , isDEBUG_(isDEBUG)
{
  std::vector<std::string> bmNames = { "SM", "BM1", "BM2", "BM3", "BM4", "BM5", "BM6", "BM7", "BM8", "BM9", "BM10", "BM11", "BM12" };
  size_t nof_JHEP = bmNames.size();
  const std::vector<double> & klJHEP  = HHWeightInterfaceLO::klJHEP();
  const std::vector<double> & ktJHEP  = HHWeightInterfaceLO::ktJHEP();
  const std::vector<double> & c2JHEP  = HHWeightInterfaceLO::c2JHEP();
  const std::vector<double> & cgJHEP  = HHWeightInterfaceLO::cgJHEP();
  const std::vector<double> & c2gJHEP = HHWeightInterfaceLO::c2gJHEP();
  if ( klJHEP.size()  != nof_JHEP || 
       ktJHEP.size()  != nof_JHEP || 
       c2JHEP.size()  != nof_JHEP || 
       cgJHEP.size()  != nof_JHEP || 
       c2gJHEP.size() != nof_JHEP )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid coupling parameters !!\n";
  }

  std::vector<std::vector<double>> A_V1_lo = loadCoeffFile(xsecFileName_V1_lo_, isDEBUG);
  std::vector<std::vector<double>> A_V1_nlo = loadCoeffFile(xsecFileName_V1_nlo_, isDEBUG);

  std::vector<std::vector<double>> A_V2_lo = loadCoeffFile_V2(xsecFileName_V2_lo_, "", isDEBUG);
  std::vector<std::vector<double>> A_V2_nlo = loadCoeffFile_V2(xsecFileName_V2_nlo_, "", isDEBUG);

  for ( std::size_t bmIdx = 0; bmIdx < nof_JHEP; ++bmIdx )
  {
    const std::string & bmName = bmNames[bmIdx];

    std::vector<double> eft_parameters_nlo = { klJHEP[bmIdx], ktJHEP[bmIdx], c2JHEP[bmIdx], cgJHEP[bmIdx], c2gJHEP[bmIdx] };
    std::vector<double> eft_parametersEWChL_nlo = convertCouplingsToEWChL(eft_parameters_nlo);
    std::vector<double> eft_parameters_lo;
    if ( apply_coupling_fix_CMS_ )
    {
      eft_parameters_lo = fix_couplings_CMS(eft_parameters_nlo, era_);
    }
    else
    {
      eft_parameters_lo = eft_parameters_nlo; 
    }
    std::vector<double> eft_parametersEWChL_lo = convertCouplingsToEWChL(eft_parameters_lo);
    
    std::string histogramName_V1_lo = Form("%s_V1_lo", bmName.data());
    const TH1 * histogram_V1_lo = compXsec_V1(histogramName_V1_lo, eft_parametersEWChL_lo, A_V1_lo, kLO, isDEBUG_);    
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V1_lo);
    }
    dXsec_V1_lo_[bmName] = histogram_V1_lo;

    std::string histogramName_V1_nlo = Form("%s_V1_nlo", bmName.data());
    const TH1 * histogram_V1_nlo = compXsec_V1(histogramName_V1_nlo, eft_parametersEWChL_nlo, A_V1_nlo, kNLO, isDEBUG_);
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V1_nlo);
    }
    dXsec_V1_nlo_[bmName] = histogram_V1_nlo;

    std::string histogramName_V1_weights = Form("%s_V1_weights", bmName.data());
    TH1* histogram_V1_weights = makeHistogram_V1_weights(histogramName_V1_weights, histogram_V1_lo, histogram_V1_nlo, max_weight_);
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V1_weights);
    }
    weights_V1_[bmName] = histogram_V1_weights;
  }

  for ( std::size_t bmIdx = 0; bmIdx < nof_JHEP; ++bmIdx )
  {
    const std::string & bmName = bmNames[bmIdx];

    std::vector<double> eft_parameters_nlo = { klJHEP[bmIdx], ktJHEP[bmIdx], c2JHEP[bmIdx], cgJHEP[bmIdx], c2gJHEP[bmIdx] };
    std::vector<double> eft_parameters_lo;
    if ( apply_coupling_fix_CMS_ )
    {
      eft_parameters_lo = fix_couplings_CMS(eft_parameters_nlo, era_);
    }
    else
    {
      eft_parameters_lo = eft_parameters_nlo;
    }

    std::string histogramName_V2_lo = Form("%s_V2_lo", bmName.data());
    const TH2 * histogram_V2_lo = compXsec_V2(histogramName_V2_lo, eft_parameters_lo, A_V2_lo, kLO, isDEBUG_);    
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V2_lo);
    }
    dXsec_V2_lo_[bmName] = histogram_V2_lo;

    std::string histogramName_V2_nlo = Form("%s_V2_nlo", bmName.data());
    const TH2 * histogram_V2_nlo = compXsec_V2(histogramName_V2_nlo, eft_parameters_nlo, A_V2_nlo, kNLO, isDEBUG_);
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V2_nlo);
    }
    dXsec_V2_nlo_[bmName] = histogram_V2_nlo;

    std::string histogramName_V2_weights = Form("%s_V2_weights", bmName.data());
    TH2* histogram_V2_weights = makeHistogram_V2_weights(histogramName_V2_weights, histogram_V2_lo, histogram_V2_nlo, max_weight_);
    if ( isDEBUG_ )
    {
      dumpHistogram(histogram_V2_weights);
    }
    weights_V2_[bmName] = histogram_V2_weights;
  }
}

HHWeightInterfaceNLO::~HHWeightInterfaceNLO()
{}

namespace
{
  int getIdxBin(const TAxis * xAxis, double x)
  {
    int firstBin = 1;
    int lastBin = xAxis->GetNbins();
    const double epsilon = 1.e-1;
    double xMin = xAxis->GetBinLowEdge(firstBin) + epsilon;
    double xMax = xAxis->GetBinUpEdge(lastBin) - epsilon;
    double x_tmp = x;
    if ( x_tmp < xMin ) x_tmp = xMin;
    if ( x_tmp > xMax ) x_tmp = xMax;
    int idxBin = xAxis->FindBin(x_tmp);
    assert(idxBin >= firstBin && idxBin <= lastBin);
    return idxBin;
  }

  double
  getWeight_V1_private(const TH1 * histogram_weight, double mHH)
  {
    const TAxis * xAxis = histogram_weight->GetXaxis();
    int idxBin = getIdxBin(xAxis, mHH);
    double weight = histogram_weight->GetBinContent(idxBin);
    return weight;
  }

  double
  getWeight_V2_private(const TH1 * histogram_weight, double mHH, double cosThetaStar)
  {
    const TAxis * xAxis = histogram_weight->GetXaxis();
    int idxBinX = getIdxBin(xAxis, mHH);
    const TAxis * yAxis = histogram_weight->GetYaxis();
    int idxBinY = getIdxBin(yAxis, cosThetaStar);
    double weight = histogram_weight->GetBinContent(idxBinX, idxBinY);
    return weight;
  }
}

double
HHWeightInterfaceNLO::getWeight_V1(const std::string & bmName,
                                   double mHH,
                                   double cosThetaStar,
                                   bool isDEBUG) const
{
  std::map<std::string, const TH1 *>::const_iterator weight_iter = weights_V1_.find(bmName);
  if ( weight_iter == weights_V1_.end() )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid parameter 'bmName' = " << bmName << " !!\n";
  }
  double weight = getWeight_V1_private(weight_iter->second, mHH);
  if ( isDEBUG )
  {
    std::cout << "<HHWeightInterfaceNLO::getWeight_V1>: bmName = '" << bmName << "'," 
              << " mHH = " << mHH 
              << " --> weight = " << weight << std::endl;
  }
  return weight;
}

double
HHWeightInterfaceNLO::getWeight_V2(const std::string & bmName,
                                   double mHH,
                                   double cosThetaStar,
                                   bool isDEBUG) const
{
  std::map<std::string, const TH2 *>::const_iterator weight_iter = weights_V2_.find(bmName);
  if ( weight_iter == weights_V2_.end() )
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid parameter 'bmName' = " << bmName << " !!\n";
  }
  double weight = getWeight_V2_private(weight_iter->second, mHH, cosThetaStar);
  if ( isDEBUG )
  {
    std::cout << "<HHWeightInterfaceNLO::getWeight_V2>: bmName = '" << bmName << "'," 
              << " mHH = " << mHH << ", cosTheta* = " << cosThetaStar 
              << " --> weight = " << weight << std::endl;
  }
  return weight;
}

double
HHWeightInterfaceNLO::getReWeight_V1(const std::string & bmName,
                                     double mHH,
                                     double cosThetaStar,
                                     bool isDEBUG) const
{
  return getReWeight(bmName, mHH, cosThetaStar, kMode_V1, isDEBUG);
}

double
HHWeightInterfaceNLO::getReWeight_V2(const std::string & bmName,
                                     double mHH,
                                     double cosThetaStar,
                                     bool isDEBUG) const
{
  return getReWeight(bmName, mHH, cosThetaStar, kMode_V2, isDEBUG);
}

double
HHWeightInterfaceNLO::getReWeight(const std::string & bmName,
                                  double mHH,
                                  double cosThetaStar,
                                  mode_type mode,
                                  bool isDEBUG) const
{
  double reWeight = 1.;
  if ( bmName == "SM" )
  {
    reWeight = 1.;
  }
  else
  {
    double smWeight = 1.;
    double bmWeight = 1.;
    if ( mode == kMode_V1 )
    {
      smWeight = getWeight_V1("SM", mHH, cosThetaStar, isDEBUG);
      bmWeight = getWeight_V1(bmName, mHH, cosThetaStar, isDEBUG);
    }
    else if ( mode == kMode_V2 )
    {
      smWeight = getWeight_V2("SM", mHH, cosThetaStar, isDEBUG);
      bmWeight = getWeight_V2(bmName, mHH, cosThetaStar, isDEBUG);
    } else assert(0);
    reWeight = ( smWeight > 0. ) ? bmWeight/smWeight : 1.;
  }
  return reWeight;
}
