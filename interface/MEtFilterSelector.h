#ifndef tthAnalysis_HiggsToTauTau_MEtFilterSelector_h
#define tthAnalysis_HiggsToTauTau_MEtFilterSelector_h

/** \class MEtFilterSelector
 *
 * Select events based on run + luminosity section + event number pairs
 * written (a three columns separated by white-space character) into an ASCII file
 * 
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" // NEW !


#include <FWCore/Framework/interface/EDFilter.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

#include <TObject.h>

#include <string>
#include <map>

class MEtFilterSelector 
{
 public:
  // constructor 
  explicit MEtFilterSelector(const edm::ParameterSet&);
    
  // destructor
  virtual ~MEtFilterSelector();

  // Returns value true if the event passes all the filters that are applied 
  bool operator()(const MEtFilter& metFilter) const;
  


 protected: 
  // Following JetMEt POG Recipe "Moriond 2017" 
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Moriond_2017
  bool apply_Flag_goodVertices_;
  bool apply_Flag_HBHENoiseIsoFilter_;
  bool apply_Flag_EcalDeadCellTriggerPrimitiveFilter_;
  bool apply_Flag_ecalLaserCorrFilter_;
  bool apply_Flag_muonBadTrackFilter_;
  bool apply_Flag_HBHENoiseFilter_;
  bool apply_Flag_chargedHadronTrackResolutionFilter_;
  bool apply_Flag_GlobalTightHalo2016Filter_;
  bool apply_Flag_eeBadScFilter_;

  // FIlters not recommended in Moriond 2017 recipe but are present inside the VHBB 2016 Ntuples   
  bool apply_Flag_hcalLaserEventFilter_;
  bool apply_Flag_trkPOGFilters_;
  bool apply_Flag_trackingFailureFilter_;
  bool apply_Flag_CSCTightHaloFilter_;
  bool apply_Flag_METFilters_;
  bool apply_Flag_CSCTightHalo2015Filter_;
  bool apply_Flag_trkPOG_manystripclus53X_;
  bool apply_Flag_trkPOG_toomanystripclus53X_;
  bool apply_Flag_trkPOG_logErrorTooManyClusters_;

};

#endif // tthAnalysis_HiggsToTauTau_MEtFilterSelector_h
