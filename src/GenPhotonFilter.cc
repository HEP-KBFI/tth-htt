#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonFilter.h" // GenPhotonFilter

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

GenPhotonFilter::GenPhotonFilter(const std::string & mode, double minPt, double maxAbsEta)
  : minPt_(minPt)
  , maxAbsEta_(maxAbsEta)
{
  if      ( mode == "disabled" ) mode_ = Mode::kDisabled;
  else if ( mode == "enabled"  ) mode_ = Mode::kEnabled;
  else if ( mode == "inverted" ) mode_ = Mode::kInverted;
  else throw cms::Exception("GenPhotonFilter")
    << "Invalid Configuration parameter 'mode' = " << mode << " !!\n";
}

GenPhotonFilter::~GenPhotonFilter()
{}

bool
GenPhotonFilter::operator()(const std::vector<GenPhoton> & genPhotons) const
{
  if ( mode_ == Mode::kDisabled ) return true;

  int numSelPhotons = 0;  
  for ( std::vector<GenPhoton>::const_iterator genPhoton = genPhotons.begin();
        genPhoton != genPhotons.end(); ++genPhoton ) {
    bool isPromptPhoton = genPhoton->pdgId() == 22 && (genPhoton->statusFlags() & (1 << (int)StatusFlag::isPrompt));
    if ( isPromptPhoton && genPhoton->pt() > minPt_ && genPhoton->absEta() < maxAbsEta_ ) ++numSelPhotons;
  }

  if ( (mode_ == Mode::kEnabled && numSelPhotons >= 1) || (mode_ == Mode::kInverted && numSelPhotons == 0) ) return true;
  else return false;
}
