#ifndef tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h

#include <string> // std::string
#include <vector> // std::vector<>
#include <iosfwd> // std::ostream

// forward declarations
class RecoLepton;

enum { 
  kGen_LeptonUndefined1, 
  kGen_LeptonAll1, kGen_1l0g0j, kGen_0l1g0j, kGen_0l0g1j 
};

enum { 
  kGen_LeptonUndefined2, kGen_LeptonAll2, 
  kGen_2l0g0j, 
  kGen_1l1g0j, kGen_1l0g1j, 
  kGen_0l2g0j, kGen_0l1g1j, kGen_0l0g2j 
};

enum { 
  kGen_LeptonUndefined3, kGen_LeptonAll3, 
  kGen_3l0g0j, 
  kGen_2l1g0j, kGen_2l0g1j, 
  kGen_1l2g0j, kGen_1l1g1j, kGen_1l0g2j, 
  kGen_0l3g0j, kGen_0l2g1j, kGen_0l1g2j, kGen_0l0g3j 
};

enum { 
  kGen_LeptonUndefined4, kGen_LeptonAll4, 
  kGen_4l0g0j, 
  kGen_3l1g0j, kGen_3l0g1j, 
  kGen_2l2g0j, kGen_2l1g1j, kGen_2l0g2j, 
  kGen_1l3g0j, kGen_1l2g1j, kGen_1l1g2j, kGen_1l0g3j, 
  kGen_0l4g0j, kGen_0l3g1j, kGen_0l2g2j, kGen_0l1g3j, kGen_0l0g4j
 };

struct leptonGenMatchEntry
{
  leptonGenMatchEntry(const std::string & name,
                      int idx,
                      int numGenMatchedLeptons,
		      int numGenMatchedPhotons,
                      int numGenMatchedJets);
  ~leptonGenMatchEntry() {}
  std::string name_;
  int idx_;
  int numGenMatchedLeptons_;
  int numGenMatchedPhotons_;
  int numGenMatchedJets_;
};

std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_1lepton(bool apply_leptonGenMatching);
std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_2lepton(bool apply_leptonGenMatching);
std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_3lepton(bool apply_leptonGenMatching);
std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_4lepton(bool apply_leptonGenMatching);

std::string
getLeptonGenMatch_string(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                         int leptonGenMatch_int);

int
getLeptonGenMatch_int(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                      const std::string & leptonGenMatch_string);

const leptonGenMatchEntry &
getLeptonGenMatch(const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions,
                  const RecoLepton * lepton_lead,
                  const RecoLepton * lepton_sublead = nullptr,
                  const RecoLepton * lepton_third = nullptr,
                  const RecoLepton * lepton_fourth = nullptr);

std::ostream &
operator<<(std::ostream & stream,
           const leptonGenMatchEntry & leptonGenMatch_definition);

std::ostream &
operator<<(std::ostream & stream,
           const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions);

#endif // tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h
