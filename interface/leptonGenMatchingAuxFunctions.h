#ifndef tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h

#include <string> // std::string
#include <vector> // std::vector<>
#include <iosfwd> // std::ostream

// forward declarations
class RecoLepton;

enum { kGen_LeptonUndefined1, kGen_LeptonAll1, kGen_1l0j, kGen_0l1j };
enum { kGen_LeptonUndefined2, kGen_LeptonAll2, kGen_2l0j, kGen_1l1j, kGen_0l2j };
enum { kGen_LeptonUndefined3, kGen_LeptonAll3, kGen_3l0j, kGen_2l1j, kGen_1l2j, kGen_0l3j };

struct leptonGenMatchEntry
{
  leptonGenMatchEntry(const std::string & name,
                      int idx,
                      int numGenMatchedLeptons,
                      int numGenMatchedJets);
  ~leptonGenMatchEntry() {}
  std::string name_;
  int idx_;
  int numGenMatchedLeptons_;
  int numGenMatchedJets_;
};

std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_1lepton(bool apply_leptonGenMatching);
std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_2lepton(bool apply_leptonGenMatching);
std::vector<leptonGenMatchEntry> getLeptonGenMatch_definitions_3lepton(bool apply_leptonGenMatching);

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
                  const RecoLepton * lepton_third = nullptr);

std::ostream &
operator<<(std::ostream & stream,
           const leptonGenMatchEntry & leptonGenMatch_definition);

std::ostream &
operator<<(std::ostream & stream,
           const std::vector<leptonGenMatchEntry> & leptonGenMatch_definitions);

#endif // tthAnalysis_HiggsToTauTau_leptonGenMatchingAuxFunctions_h
