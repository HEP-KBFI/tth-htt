#ifndef tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h
#define tthAnalysis_HiggsToTauTau_EvtWeightRecorder_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::VParameterSet

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
  get_inclusive(const std::string & central_or_shift = "") const;

  double
  get_genWeight() const;

  double
  get_auxWeight() const;

  double
  get_lumiScale(const std::string & central_or_shift = "") const;

  double
  get_nom_tH_weight() const;

  double
  get_puWeight(const std::string & central_or_shift = "") const;

  double
  get_l1PreFiringWeight(const std::string & central_or_shift = "") const;

  double
  get_lheScaleWeight(const std::string & central_or_shift = "") const;

  double
  get_leptonSF() const;

  double
  get_chargeMisIdProb() const;

  double
  get_data_to_MC_correction(const std::string & central_or_shift = "") const;

  double
  get_btag(const std::string & central_or_shift = "") const;

  double
  get_sf_triggerEff(const std::string & central_or_shift = "") const;

  double
  get_tauSF(const std::string & central_or_shift = "") const;

  double
  get_FR(const std::string & central_or_shift = "") const;

  void
  record_genWeight(double genWeight);

  void
  record_auxWeight(double auxWeight);

  void
  record_lumiScale(const edm::VParameterSet & lumiScales);

  void
  record_nom_tH_weight(double nom_tH_weight);

  void
  record_leptonSF(double weight);

  void
  record_chargeMisIdProb(double weight);

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
  compute_FR_2l1tau(bool passesTight_lepton_lead,
                    bool passesTight_lepton_sublead,
                    bool passesTight_hadTau);

  void
  compute_FR_2l(bool passesTight_lepton_lead,
                bool passesTight_lepton_sublead);

  void
  compute_FR_1tau();

protected:
  void
  record_jetToLepton_FR(const LeptonFakeRateInterface * const leptonFakeRateInterface,
                        double leptonPt,
                        double leptonAbsEta,
                        int leptonPdgId,
                        std::map<int, double> & weights_FR_lepton);

  bool isMC_;
  double genWeight_;
  double auxWeight_;
  std::map<std::string, double> lumiScale_;
  double nom_tH_weight_;
  double leptonSF_;
  double chargeMisIdProb_;
  std::vector<std::string> central_or_shifts_;

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
  std::map<std::string, double> weights_FR_;
};

#endif
