#ifndef MEMPERMUTATIONWRITER_H
#define MEMPERMUTATIONWRITER_H

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight

#include <string> // std::string
#include <vector> // std::vector<>
#include <array> // std::array<,>
#include <map> // std::map<,>
#include <functional> // std::function<>

// forward declarations
class TTree;
class RecoLepton;
class RecoJet;

typedef std::function<
    int(const std::vector<const RecoLepton *> & /*selLeptons*/,
        const std::vector<const RecoHadTau *> & /*selHadTaus*/,
        const std::vector<const RecoJet *> & /*selBJets_loose*/,
        const std::vector<const RecoJet *> & /*selBJets_medium*/,
        bool /*failsZbosonMassVeto*/)
  > MEMPremutationCondition;

class MEMPermutationWriter
{
public:
  MEMPermutationWriter() = default;
  ~MEMPermutationWriter();

  MEMPermutationWriter &
  setLepSelection(int minLepSelection,
                  int maxLepSelection);

  MEMPermutationWriter &
  setHadTauSelection(int minHadTauSelection,
                     int maxHadTauSelection);

  MEMPermutationWriter &
  setHadTauWorkingPoints(const std::string & minHadTauWorkingPoint);

  MEMPermutationWriter &
  addCondition(const std::string & channel,
               const MEMPremutationCondition & condition);

  MEMPermutationWriter &
  addCondition(const std::string & channel,
               unsigned minSelLeptons,
               unsigned minSelHadTaus,
               unsigned minSelBJets_loose = 2,
               unsigned minSelBJets_medium = 1);

  void
  setBranchNames(TTree * tree,
                 int era,
                 bool verbose = false);

  void
  write(const std::array<const std::vector<const RecoLepton *>, 3> & leptons,
        const std::array<const std::vector<const RecoJet *>, 2> & selBJets,
        const std::vector<const RecoHadTau *> & cleanedHadTaus);

private:
  int minLepSelection_;
  int maxLepSelection_;
  int minHadTauSelection_;
  int maxHadTauSelection_;
  std::vector<std::string> hadTauWorkingPoints_;

  std::map<std::string, MEMPremutationCondition> conditions_;
  std::map<std::string, std::map<int, std::map<int, std::map<std::string, int>>>> branches_;
  std::map<std::string, std::map<int, int>> branches_noTaus_;
  std::map<std::string, RecoHadTauCollectionSelectorFakeable *> hadTauSelectorsFakeable_;
  std::map<std::string, RecoHadTauCollectionSelectorTight *>    hadTauSelectorsTight_;

  static std::string
  find_selection_str(int selection_idx);
};

#endif // MEMPERMUTATIONWRITER_H
