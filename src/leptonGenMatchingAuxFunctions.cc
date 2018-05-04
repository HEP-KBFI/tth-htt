#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <iostream> // std::ostream

leptonGenMatchEntry::leptonGenMatchEntry(const std::string & name,
                                         int idx,
                                         int numGenMatchedLeptons,
                                         int numGenMatchedJets)
  : name_(name)
  , idx_(idx)
  , numGenMatchedLeptons_(numGenMatchedLeptons)
  , numGenMatchedJets_(numGenMatchedJets)
{}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_1lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l0j", kGen_1l0j, 1, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l1j", kGen_0l1j, 0, 1));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll1, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_2lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l0j", kGen_2l0j, 2, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l1j", kGen_1l1j, 1, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l2j", kGen_0l2j, 0, 2));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll2, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_3lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("3l0j", kGen_3l0j, 3, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l1j", kGen_2l1j, 2, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l2j", kGen_1l2j, 1, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l3j", kGen_0l3j, 0, 3));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll3, -1, -1));
  }
  return leptonGenMatch_definitions;
}

std::vector<leptonGenMatchEntry>
getLeptonGenMatch_definitions_4lepton(bool apply_leptonGenMatching)
{
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions;
  if(apply_leptonGenMatching)
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("4l0j", kGen_4l0j, 4, 0));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("3l1j", kGen_3l1j, 3, 1));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("2l2j", kGen_2l2j, 2, 2));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("1l3j", kGen_1l3j, 1, 3));
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("0l4j", kGen_0l4j, 0, 4));
  }
  else
  {
    leptonGenMatch_definitions.push_back(leptonGenMatchEntry("all", kGen_LeptonAll4, -1, -1));
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
                        int & numGenMatchedJets)
  {
    numGenMatchedLeptons = 0;
    numGenMatchedJets = 0;
  }

  void
  countLeptonGenMatches(const RecoLepton * lepton,
                        int & numGenMatchedLeptons,
                        int & numGenMatchedJets)
  {
    if(lepton->genLepton() || lepton->genHadTau())
    {
      ++numGenMatchedLeptons;
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
                    int numGenMatchedJets)
  {
    const leptonGenMatchEntry * leptonGenMatch = nullptr;
    for(const leptonGenMatchEntry & leptonGenMatch_definition: leptonGenMatch_definitions)
    {
      if(matches(leptonGenMatch_definition.numGenMatchedLeptons_, numGenMatchedLeptons) &&
         matches(leptonGenMatch_definition.numGenMatchedJets_,    numGenMatchedJets)     )
      {
        leptonGenMatch = &leptonGenMatch_definition;
      }
    }
    if(! leptonGenMatch)
      throw cmsException(__func__)
        << "Failed to compute 'leptonGenMatch' for numGenMatched:"
           " leptons = " << numGenMatchedLeptons << ","
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
  int numGenMatchedLeptons, numGenMatchedJets;
  resetLeptonGenMatches(numGenMatchedLeptons, numGenMatchedJets);
  assert(lepton_lead);

  countLeptonGenMatches(lepton_lead, numGenMatchedLeptons, numGenMatchedJets);
  if(lepton_sublead)
  {
    countLeptonGenMatches(lepton_sublead, numGenMatchedLeptons, numGenMatchedJets);
  }
  if(lepton_third)
  {
    countLeptonGenMatches(lepton_third, numGenMatchedLeptons, numGenMatchedJets);
  }
  if(lepton_fourth)
  {
    countLeptonGenMatches(lepton_fourth, numGenMatchedLeptons, numGenMatchedJets);
  }
  return getLeptonGenMatch(leptonGenMatch_definitions, numGenMatchedLeptons, numGenMatchedJets);
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
