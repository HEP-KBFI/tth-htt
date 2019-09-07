#ifndef tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h
#define tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h

#include <vector> // std::vector<>
#include <string> // std::string
#include <map> // std::map<,>

class L1PreFiringWeightReader;
class LHEInfoReader;
class EventInfo;
class RecoJet;
class Data_to_MC_CorrectionInterface_Base;

enum class L1PreFiringWeightSys;
enum class PUsys;
enum class TriggerSFsys;
enum class TauIDSFsys;
enum class FRet;
enum class FRmt;

class EvtWeightRecorder
{
public:
  EvtWeightRecorder();
  EvtWeightRecorder(const std::vector<std::string> & central_or_shifts);

  double
  get(const std::string & central_or_shift) const;

  double
  get_inclusive() const;

  double
  get_btag() const;

  double
  get_sf_triggerEff() const;

  double
  get_leptonSF() const;

  double
  get_tauSF() const;

  EvtWeightRecorder &
  operator*=(double weight);

  void
  record_leptonSF(double weight);

  void
  record_l1PrefireWeight(const L1PreFiringWeightReader * const l1PreFiringWeightReader);

  void
  record_lheScaleWeight(const LHEInfoReader * const lheInfoReader);

  void
  record_puWeight(const EventInfo * const eventInfo);

  void
  record_btagWeight(const std::vector<const RecoJet *> & jets);

  void
  record_leptonTriggerEff(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface);

  void
  record_hadTauID_and_Iso(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface);

  void
  record_eToTauFakeRate(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface);

  void
  record_muToTauFakeRate(const Data_to_MC_CorrectionInterface_Base * const dataToMCcorrectionInterface);

  void
  reset();

protected:
  double central_;
  double leptonSF_;
  std::vector<std::string> central_or_shifts_;
  std::map<std::string, double> weights_;

  std::map<L1PreFiringWeightSys, double> weights_l1PreFiring_;
  std::map<int, double> weights_lheScale_;
  std::map<PUsys, double> weights_pu_;
  std::map<int, double> weights_btag_;
  std::map<TriggerSFsys, double> weights_leptonTriggerEff_;
  std::map<TauIDSFsys, double> weights_hadTauID_and_Iso_;
  std::map<FRet, double> weights_eToTauFakeRate_;
  std::map<FRmt, double> weights_muToTauFakeRate_;
};

#endif
