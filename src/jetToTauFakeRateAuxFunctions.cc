#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "DataFormats/Math/interface/deltaR.h" // deltaR

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
  }else{
    assert(0);
  }
  return boost::replace_all_copy(PtBin, ".", "_");
}

int
getTrigMatchingOption(const std::string& trigMatching)
{
  int trigMatching_int;
  if      ( trigMatching == "woTriggerMatching"                ) trigMatching_int = kFilterBit_notApplied;
  else if ( trigMatching == "wTriggerMatchingLooseChargedIso"  ) trigMatching_int = kFilterBit_looseChargedIso;
  else if ( trigMatching == "wTriggerMatchingMediumChargedIso" ) trigMatching_int = kFilterBit_mediumChargedIso;
  else if ( trigMatching == "wTriggerMatchingTightChargedIso"  ) trigMatching_int = kFilterBit_tightChargedIso;
  else throw cms::Exception("getTrigMatchingOption") 
    << "Invalid parameter 'trigMatching' = " << trigMatching << " !!\n";
  return trigMatching_int;
}

bool 
matchesTrigObj(const RecoJet& jet, const std::vector<TrigObj>& triggerObjects, int filterBit, double dRmatch)
{ 
  int filterBit_mask = 0;
  // CV: bit masks defined in https://github.com/HEP-KBFI/cmssw/blob/master/PhysicsTools/NanoAOD/python/triggerObjects_cff.py#L94
  if      ( filterBit == kFilterBit_looseChargedIso  ) filterBit_mask = 1;
  else if ( filterBit == kFilterBit_mediumChargedIso ) filterBit_mask = 2;
  else if ( filterBit == kFilterBit_tightChargedIso  ) filterBit_mask = 4;
  else throw cms::Exception("matchesTrigObj") 
    << "Invalid parameter 'filterBit' = " << filterBit << " !!\n";
  bool isMatched = false;
  for ( const TrigObj& triggerObject : triggerObjects )
  {
    if ( triggerObject.id() == 15 && triggerObject.filterBits() & filterBit_mask )
    {
      double dR = deltaR(jet.eta(), jet.phi(), triggerObject.eta(), triggerObject.phi());
      if ( dR < dRmatch )
      {
        isMatched = true;
        break;
      }
    }
  }
  return isMatched;
}
