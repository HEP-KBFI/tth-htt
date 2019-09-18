#include "tthAnalysis/HiggsToTauTau/interface/GenMatchInterface.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"                  // cmsException()

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"                    // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"                    // RecoHadTau

#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // countLeptonGenMatches, countLeptonChargeFlipGenMatches
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // countHadTauGenMatches

GenMatchInterface::GenMatchInterface(unsigned numLeptons, bool apply_leptonGenMatching, bool useFlips, unsigned numHadTaus, bool apply_hadTauGenMatching)
  : numLeptons_(numLeptons)
  , apply_leptonGenMatching_(apply_leptonGenMatching)
  , useFlips_(useFlips)
  , numHadTaus_(numHadTaus)
  , apply_hadTauGenMatching_(apply_hadTauGenMatching)
  , useGenTau_and_FakeTau_(numHadTaus >= 1 && !apply_hadTauGenMatching)
{
  initialize();
}

GenMatchInterface::GenMatchInterface(unsigned numLeptons, bool apply_leptonGenMatching, bool useFlips)
  : numLeptons_(numLeptons)
  , apply_leptonGenMatching_(apply_leptonGenMatching)
  , useFlips_(useFlips)
  , numHadTaus_(0)
  , apply_hadTauGenMatching_(false)
  , useGenTau_and_FakeTau_(false)
{
  initialize();
}

GenMatchInterface::GenMatchInterface(unsigned numHadTaus, bool apply_hadTauGenMatching)
  : numLeptons_(0)
  , apply_leptonGenMatching_(false)
  , useFlips_(false)
  , numHadTaus_(numHadTaus)
  , apply_hadTauGenMatching_(apply_hadTauGenMatching)
  , useGenTau_and_FakeTau_(numHadTaus >= 1 && !apply_hadTauGenMatching)
{
  initialize();
}

GenMatchInterface::~GenMatchInterface()
{}

void GenMatchInterface::initialize()
{
  genMatchDefinition_fakes_       = nullptr;
  genMatchDefinition_flips_       = nullptr;
  genMatchDefinition_conversions_ = nullptr;
  genMatchDefinition_nonfakes_    = nullptr;
  genMatchDefinition_gentau_      = nullptr;
  genMatchDefinition_faketau_     = nullptr;
  idx_ = 0;
  if ( !(numLeptons_ >= 1 || numHadTaus_ >= 1) ) 
  {
    throw cmsException(__func__, __LINE__)
      << " Invalid configuration parameters 'numLeptons' = " << numLeptons_ << " and 'numHadTaus' = " << numHadTaus_ << " !!";
  }
  addGenMatchDefinition("_fake");
  genMatchDefinition_fakes_ = &genMatchDefinitions_.back();
  if ( useFlips_ )
  {
    if ( !(numLeptons_ >= 1) )
    {
      throw cmsException(__func__, __LINE__)
        << " Invalid configuration parameters 'numLeptons' = " << numLeptons_ << " and 'useFlips' = " << useFlips_ << " !!";
    }
    addGenMatchDefinition("_flip");
    genMatchDefinition_flips_ = &genMatchDefinitions_.back();
  }
  if ( numLeptons_ >= 1 )
  {
    addGenMatchDefinition("_Convs");
    genMatchDefinition_conversions_ = &genMatchDefinitions_.back();
  }
  addGenMatchDefinition(""); // non-fake
  genMatchDefinition_nonfakes_ = &genMatchDefinitions_.back();
  if ( useGenTau_and_FakeTau_ )
  {
    addGenMatchDefinition("_gentau");
    genMatchDefinition_gentau_ = &genMatchDefinitions_.back();
    addGenMatchDefinition("_faketau");
    genMatchDefinition_faketau_ = &genMatchDefinitions_.back();
  }
}

void 
GenMatchInterface::addGenMatchDefinition(const std::string& name)
{
  genMatchDefinitions_.push_back(GenMatchEntry(name, idx_));
  ++idx_;
}

const std::vector<GenMatchEntry>& 
GenMatchInterface::getGenMatchDefinitions() const
{
  return genMatchDefinitions_;
}
  
std::vector<const GenMatchEntry*> 
GenMatchInterface::getGenMatch(const std::vector<const RecoLepton*>& selLeptons, const std::vector<const RecoHadTau*>& selHadTaus)
{
  int selLeptons_numGenMatchedLeptons;
  int selLeptons_numChargeFlippedGenMatchedLeptons;
  int selLeptons_numGenMatchedPhotons;
  int selLeptons_numGenMatchedJets;
  assert(selLeptons.size() >= numLeptons_);
  if ( useFlips_ )
  {
    for ( const RecoLepton* selLepton : selLeptons )
    {
      countLeptonGenMatches(selLepton, selLeptons_numGenMatchedLeptons, selLeptons_numGenMatchedPhotons, selLeptons_numGenMatchedJets);
    }
  }
  else
  {
    for ( const RecoLepton* selLepton : selLeptons )
    {
      countLeptonChargeFlipGenMatches(selLepton, selLeptons_numGenMatchedLeptons, selLeptons_numChargeFlippedGenMatchedLeptons, selLeptons_numGenMatchedPhotons, selLeptons_numGenMatchedJets);
    }
  }
  
  int selHadTaus_numGenMatchedHadTaus   = 0;
  int selHadTaus_numGenMatchedElectrons = 0;
  int selHadTaus_numGenMatchedMuons     = 0;
  int selHadTaus_numGenMatchedJets      = 0;
  assert(selHadTaus.size() >= numHadTaus_);
  for ( const RecoHadTau* selHadTau : selHadTaus )
  {
    countHadTauGenMatches(selHadTau, selHadTaus_numGenMatchedHadTaus, selHadTaus_numGenMatchedElectrons, selHadTaus_numGenMatchedMuons, selHadTaus_numGenMatchedJets);
  }

  std::vector<const GenMatchEntry*> genMatches;
  if ( (apply_leptonGenMatching_ && selLeptons_numGenMatchedJets >= 1) ||
       (apply_hadTauGenMatching_ && selHadTaus_numGenMatchedJets >= 1) )
  {
    assert(genMatchDefinition_fakes_);
    genMatches.push_back(genMatchDefinition_fakes_);
  }
  else if ( useFlips_ && selLeptons_numChargeFlippedGenMatchedLeptons >= 1 )
  {
    assert(genMatchDefinition_flips_);
    genMatches.push_back(genMatchDefinition_flips_);
  }
  else if ( selLeptons_numGenMatchedPhotons >= 1 ) 
  {
    assert(genMatchDefinition_conversions_);
    genMatches.push_back(genMatchDefinition_conversions_);
  }
  else 
  {
    assert(genMatchDefinition_nonfakes_);
    genMatches.push_back(genMatchDefinition_nonfakes_);
    if ( useGenTau_and_FakeTau_ )
    {
      if ( selHadTaus_numGenMatchedJets >= 1 ) 
      {
	assert(genMatchDefinition_faketau_);
	genMatches.push_back(genMatchDefinition_faketau_);
      }
      else
      {
	assert(genMatchDefinition_gentau_);
	genMatches.push_back(genMatchDefinition_gentau_);
      }
    }
  }
  return genMatches;
}
 
std::vector<const GenMatchEntry*> 
GenMatchInterface::getGenMatch(const std::vector<const RecoLepton*>& selLeptons)
{
  // CV: this function must not be used by channels with hadronic taus
  assert(numHadTaus_ == 0);
  return getGenMatch(selLeptons, {});
}

std::vector<const GenMatchEntry*> 
GenMatchInterface::getGenMatch(const std::vector<const RecoHadTau*>& selHadTaus)
{
  // CV: this function must not be used by channels with leptons
  assert(numLeptons_ == 0);
  return getGenMatch({}, selHadTaus);
}
