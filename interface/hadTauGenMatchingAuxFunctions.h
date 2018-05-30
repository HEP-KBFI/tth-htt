#ifndef tthAnalysis_HiggsToTauTau_hadTauGenMatchingAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_hadTauGenMatchingAuxFunctions_h

#include <vector> // std::vector<>
#include <string> // std::string
#include <iosfwd> // std::ostream

// forward declarations
class RecoHadTau;

enum {
  kGen_HadTauUndefined1, kGen_HadTauAll1,
  kGen_1t0e0m0j, 
  kGen_0t1e0m0j, kGen_0t0e1m0j, kGen_0t0e0m1j
};

enum
{
  kGen_HadTauUndefined2, kGen_HadTauAll2,
  kGen_2t0e0m0j, 
  kGen_1t1e0m0j, kGen_1t0e1m0j, kGen_1t0e0m1j,
  kGen_0t2e0m0j, kGen_0t1e1m0j, kGen_0t0e2m0j, kGen_0t1e0m1j, kGen_0t0e1m1j, kGen_0t0e0m2j, kGen_1t0e0m2j, 
};


enum
{
  kGen_HadTauUndefined3, kGen_HadTauAll3,
  kGen_3t0e0m0j, 
  kGen_2t1e0m0j, kGen_2t0e1m0j, kGen_2t0e0m1j,
  kGen_1t2e0m0j, kGen_1t1e1m0j, kGen_1t0e2m0j, kGen_1t1e0m1j, kGen_1t0e1m1j, 
  kGen_0t3e0m0j, kGen_0t2e1m0j, kGen_0t1e2m0j, kGen_0t0e3m0j, 
  kGen_0t2e0m1j, kGen_0t1e1m1j, kGen_0t0e2m1j, kGen_0t1e0m2j, kGen_0t0e1m2j, kGen_0t0e0m3j
};

struct hadTauGenMatchEntry
{
  hadTauGenMatchEntry(const std::string & name,
                      int idx,
                      int numGenMatchedHadTaus,
                      int numGenMatchedElectrons,
                      int numGenMatchedMuons,
                      int numGenMatchedJets);
  ~hadTauGenMatchEntry() {}

  std::string name_;
  int idx_;
  int numGenMatchedHadTaus_;
  int numGenMatchedElectrons_;
  int numGenMatchedMuons_;
  int numGenMatchedJets_;
};

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_1tau(bool apply_hadTauGenMatching);

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_2tau(bool apply_hadTauGenMatching);

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_3tau(bool apply_hadTauGenMatching);

std::string
getHadTauGenMatch_string(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                         int hadTauGenMatch_int);

int
getHadTauGenMatch_int(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                      const std::string& hadTauGenMatch_string);

const hadTauGenMatchEntry &
getHadTauGenMatch(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                  const RecoHadTau * hadTau_lead,
                  const RecoHadTau * hadTau_sublead = nullptr,
                  const RecoHadTau * hadTau_third = nullptr);

std::ostream &
operator<<(std::ostream & stream,
           const hadTauGenMatchEntry & hadTauGenMatch_definition);

std::ostream &
operator<<(std::ostream & stream,
           const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions);

#endif // tthAnalysis_HiggsToTauTau_hadTauGenMatchingAuxFunctions_h
