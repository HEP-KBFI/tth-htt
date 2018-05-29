#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <iostream> // std::ostream

leptonGenMatchEntry::leptonGenMatchEntry(const std::string & name,
                                         int idx,
                                         int numGenMatchedLeptons,
					 int numGenMatchedPhotons,
                                         int numGenMatchedJets)
  : name_(name)
  , idx_(idx)
  , numGenMatchedLeptons_(numGenMatchedLeptons)
  , numGenMatchedPhotons_(numGenMatchedPhotons)
  , numGenMatchedJets_(numGenMatchedJets)
{}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_1lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l0g0j", kGen_1l0g0j, 1, 0, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l1g0j", kGen_0l1g0j, 0, 1, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l0g1j", kGen_0l0g1j, 0, 0, 1));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll1, -1, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_2lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l0g0j", kGen_2l0g0j, 2, 0, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l1g0j", kGen_1l1g0j, 1, 1, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l0g1j", kGen_1l0g1j, 1, 0, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l2g0j", kGen_0l2g0j, 0, 2, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l1g1j", kGen_0l1g1j, 0, 1, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l0g2j", kGen_0l0g2j, 0, 0, 2));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll2, -1, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_3lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("3l0g0j", kGen_3l0g0j, 3, 0, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l1g0j", kGen_2l1g0j, 2, 1, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l0g1j", kGen_2l0g1j, 2, 0, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l2g0j", kGen_1l2g0j, 1, 2, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l1g1j", kGen_1l1g1j, 1, 1, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l0g2j", kGen_1l0g2j, 1, 0, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l3g0j", kGen_0l3g0j, 0, 3, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l2g1j", kGen_0l2g1j, 0, 2, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l1g2j", kGen_0l1g2j, 0, 1, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l0g3j", kGen_0l0g3j, 0, 0, 3));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll3, -1, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_4lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("4l0g0j", kGen_4l0g0j, 4, 0, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("3l1g0j", kGen_3l1g0j, 3, 1, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("3l0g1j", kGen_3l0g1j, 3, 0, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l2g0j", kGen_2l2g0j, 2, 2, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l1g1j", kGen_2l1g1j, 2, 1, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l0g2j", kGen_2l0g2j, 2, 0, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l3g0j", kGen_1l3g0j, 1, 3, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l2g1j", kGen_1l2g1j, 1, 2, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l1g2j", kGen_1l1g2j, 1, 1, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l0g3j", kGen_1l0g3j, 1, 0, 3));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l4g0j", kGen_0l4g0j, 0, 4, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l3g1j", kGen_0l3g1j, 0, 3, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l2g2j", kGen_0l2g2j, 0, 2, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l1g3j", kGen_0l1g3j, 0, 1, 3));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l0g4j", kGen_0l0g4j, 0, 0, 4));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll4, -1, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::string
getLeptonGenMatch_string(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                         int leptonGenMatch_int)
{
  const leptonGenMatchEntry * leptonGenMatch = nullptr;

  for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
  {
    if(leptonGenMatch_definition.idx_ == leptonGenMatch_int)
    {
      leptonGenMatch = &leptonGenMatch_definition;
    }
  }
  if(! leptonGenMatch)
  {
    throw cmsException(__func__)
      << "Invalid parameter 'leptonGenMatch_int' = " << leptonGenMatch_int;
  }
  return leptonGenMatch->name_;
}

int
getLeptonGenMatch_int(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                      const std::string & leptonGenMatch_string)
{
  const leptonGenMatchEntry * leptonGenMatch = nullptr;
  for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
  {
    if(leptonGenMatch_definition.name_ == leptonGenMatch_string)
    {
      leptonGenMatch = &leptonGenMatch_definition;
    }
  }
  if(! leptonGenMatch)
  {
    throw cmsException(__func__)
      << "Invalid parameter 'leptonGenMatch_string' = " << leptonGenMatch_string;
  }
  return leptonGenMatch->idx_;
}

namespace
{
  void
  resetLeptonGenMatches(int & numGenMatchedLeptons,
			int & numGenMatchedPhotons,
                        int & numGenMatchedJets)
  {
    numGenMatchedLeptons = 0;
    numGenMatchedPhotons = 0;
    numGenMatchedJets = 0;
  }

  void
  countLeptonGenMatches(const RecoLepton * lepton,
                        int & numGenMatchedLeptons,
			int & numGenMatchedPhotons,
                        int & numGenMatchedJets)
  {
    if(lepton->genLepton() || lepton->genHadTau())
    {
      ++numGenMatchedLeptons;
    }
    else if(lepton->is_electron() && lepton->genPhoton() && lepton->genPhoton()->pt() > (0.50*lepton->pt()))
    {
      ++numGenMatchedPhotons;
    }
    else
    {
      ++numGenMatchedJets;
    }
  }

  bool
  matches(int nSel,
          int nMatches)
  {
    return nSel == -1 || nSel == nMatches;
  }

  const leptonGenMatchEntry &
  getLeptonGenMatch(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                    int numGenMatchedLeptons,
		    int numGenMatchedPhotons,
                    int numGenMatchedJets)
  {
    const leptonGenMatchEntry * leptonGenMatch = nullptr;
    for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
    {
      if(matches(leptonGenMatch_definition.numGenMatchedLeptons_, numGenMatchedLeptons) &&
	 matches(leptonGenMatch_definition.numGenMatchedPhotons_, numGenMatchedPhotons) &&
         matches(leptonGenMatch_definition.numGenMatchedJets_,    numGenMatchedJets)     )
      {
        leptonGenMatch = &leptonGenMatch_definition;
      }
    }
    if(! leptonGenMatch)
      throw cmsException(__func__)
        << "Failed to compute 'leptonGenMatch' for numGenMatched:"
           " leptons = " << numGenMatchedLeptons << ","
	   " photons = " << numGenMatchedPhotons << ","
           " jets = "    << numGenMatchedJets;
    return *leptonGenMatch;
  }
}

const leptonGenMatchEntry &
getLeptonGenMatch(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                  const RecoLepton * lepton_lead,
                  const RecoLepton * lepton_sublead,
                  const RecoLepton * lepton_third,
                  const RecoLepton * lepton_fourth)
{
  int numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets;
  resetLeptonGenMatches(numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
  assert(lepton_lead);

  countLeptonGenMatches(lepton_lead, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
  if(lepton_sublead)
  {
    countLeptonGenMatches(lepton_sublead, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
  }
  if(lepton_third)
  {
    countLeptonGenMatches(lepton_third, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
  }
  if(lepton_fourth)
  {
    countLeptonGenMatches(lepton_fourth, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
  }
  return getLeptonGenMatch(leptonGenMatch_definitions, numGenMatchedLeptons, numGenMatchedPhotons, numGenMatchedJets);
}

std::ostream &
operator<<(std::ostream & stream,
           const leptonGenMatchEntry & leptonGenMatch_definition)\
{
  stream << " leptonGenMatch #" << leptonGenMatch_definition.idx_
         << ": "                << leptonGenMatch_definition.name_;
  return stream;
}

std::ostream &
operator<<(std::ostream & stream,
           const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions)
{
  for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
  {
    stream << leptonGenMatch_definition << '\n';
  }
  return stream;
}
