#ifndef tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h
#define tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h

#include <vector> // std::vector<>
#include <string> // std::string
#include <map> // std::map<,>

// forward declarations
class L1PreFiringWeightReader;
class LHEInfoReader;
class EventInfo;
class RecoJet;
class Data_to_MC_CorrectionInterface_Base;
class JetToTauFakeRateInterface;
class LeptonFakeRateInterface;

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
  EvtWeightRecorder(const std::vector<std::string> & central_or_shifts,
                    bool isMC);

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
  record_jetToTau_FR_lead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                          double hadTauPt_lead,
                          double hadTauAbsEta_lead);

  void
  record_jetToTau_SF_lead(const JetToTauFakeRateInterface * const jetToTauFakeRateInterface,
                          double hadTauPt_lead,
                          double hadTauAbsEta_lead);

  void
  record_jetToLepton_FR_lead(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                             double leptonPt_lead,
                             double leptonAbsEta_lead,
                             int leptonPdgId);

  void
  record_jetToLepton_FR_sublead(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                                double leptonPt_sublead,
                                double leptonAbsEta_sublead,
                                int leptonPdgId);

  void
  reset();

protected:
  void
  record_jetToLepton_FR(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                        double leptonPt,
                        double leptonAbsEta,
                        int leptonPdgId,
                        std::map<int, double> & weights_FR_lepton);

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
  std::map<int, double> weights_FR_hadTau_lead_;
  std::map<int, double> weights_SF_hadTau_lead_;
  std::map<int, double> weights_FR_lepton_lead_;
  std::map<int, double> weights_FR_lepton_sublead_;
};

#endif
