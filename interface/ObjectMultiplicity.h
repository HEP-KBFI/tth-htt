#ifndef tthAnalysis_HiggsToTauTau_ObjectMultiplicity_h
#define tthAnalysis_HiggsToTauTau_ObjectMultiplicity_h

#include <map> // std::map<,>

// forward declarations
enum class TauID;

class ObjectMultiplicity
{
public:
  ObjectMultiplicity();
  ObjectMultiplicity &
  operator=(const ObjectMultiplicity & eventInfo);

  int
  getNRecoMuon(int selection) const;

  int
  getNRecoElectron(int selection) const;

  int
  getNRecoLepton(int selection) const;

  int
  getNRecoHadTau(TauID tauId,
                 int level) const;

  void
  setNRecoMuon(int nLoose,
               int nFakeable,
               int nTight);

  void
  setNRecoElectron(int nLoose,
                   int nFakeable,
                   int nTight);

  void
  setNRecoHadTau(TauID tauId,
                 int level,
                 int nTau);

  friend class ObjectMultiplicityReader;
  friend class ObjectMultiplicityWriter;

protected:
  std::map<int, int> nRecoMuon_;
  std::map<int, int> nRecoElectron_;
  std::map<TauID, std::map<int, int>> nRecoHadTau_;
};

#endif // tthAnalysis_HiggsToTauTau_ObjectMultiplicity_h
