#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h"

#include <TString.h> // Form()

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

#include <cassert> // assert()

#include <iostream>

std::string
getEtaBin(double minAbsEta,
          double maxAbsEta)
{
  std::string absEtaBin;
  if     (minAbsEta > 0. && maxAbsEta > 0.) absEtaBin = Form("absEta%1.1fto%1.1f", minAbsEta, maxAbsEta);
  else if(minAbsEta > 0.                  ) absEtaBin = Form("absEtaGt%1.1f", minAbsEta);
  else if(                  maxAbsEta > 0.) absEtaBin = Form("absEtaLt%1.1f", maxAbsEta);
  else if(minAbsEta < 0. && maxAbsEta < 0.){ 
    absEtaBin = "incl";
    // std::cout<< " minAbsEta " << minAbsEta << " maxAbsEta " << maxAbsEta << std::endl;             
    // assert(0);
  }else{
    assert(0);
  }
  return boost::replace_all_copy(absEtaBin, ".", "_");
}

std::string
getPtBin(double minPt,
         double maxPt)
{
  std::string PtBin = "";
  if     (minPt > 0. && maxPt > 0.) PtBin = Form("Pt%1.1fto%1.1f", minPt, maxPt);
  else if(minPt > 0.              ) PtBin = Form("PtGt%1.1f", minPt);
  else if(              maxPt > 0.) PtBin = Form("PtLt%1.1f", maxPt);
  else if (minPt < 0. && maxPt < 0.){
    PtBin = "incl";                          
    // assert(0);
  }else{
    assert(0);
  }
  return boost::replace_all_copy(PtBin, ".", "_");
}
