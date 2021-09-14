#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenMEt.h" // GenMEt

#include <CommonTools/Utils/interface/TFileDirectory.h> // TFileDirectory

// forward declarations
class cutFlowTableType;
class ElectronHistManager;
class MuonHistManager;
class EvtHistManager_LeptonFakeRate;
class EvtHistManager_LeptonEfficiency;
enum class METSyst;

double
comp_mT(const RecoLepton & lepton,
        double met_pt,
        double met_phi);

double
comp_mT_fix(const RecoLepton & lepton,
            double met_pt,
            double met_phi);

//--- define histograms (same histogram manager class used for numerator and denominator)
struct numerator_and_denominatorHistManagers
{
  numerator_and_denominatorHistManagers(const std::string & process,
                                        bool isMC,
                                        const std::string & era_string,
                                        const std::string & central_or_shift,
                                        const std::string & dir,
                                        int lepton_type,
                                        double minAbsEta = -1.,
                                        double maxAbsEta = -1.,
                                        double minPt = -1.,
                                        double maxPt = -1.,
                                        const std::string & subdir_suffix = "");

  ~numerator_and_denominatorHistManagers();

  std::string
  getLabel() const;


  void
  bookHistograms(TFileDirectory & dir, bool forLepEff = false);

  void
  fillHistograms(const RecoLepton & lepton,
                 double m_ll,
                 double evtWeight,
                 cutFlowTableType * cutFlowTable = nullptr);

  void
  fillHistograms(const RecoLepton & lepton_probe,
   		 const RecoLepton & lepton_tag,
                 double m_ll,
                 double evtWeight,
                 cutFlowTableType * cutFlowTable = nullptr);

  void
  fillHistograms(const RecoLepton & lepton,
                 double met,
                 double mT,
                 double mT_fix,
                 double evtWeight,
                 cutFlowTableType * cutFlowTable = nullptr);

private:
  std::string process_;
  bool isMC_;
  std::string era_string_;
  std::string central_or_shift_;

  int lepton_type_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  bool isInclusive_;

  std::string subdir_;
  std::string label_;

  ElectronHistManager * electronHistManager_;
  ElectronHistManager * electronHistManager_genHadTau_;
  ElectronHistManager * electronHistManager_genLepton_;
  ElectronHistManager * electronHistManager_genHadTauOrLepton_;
  ElectronHistManager * electronHistManager_genJet_;
  ElectronHistManager * electronHistManager_genPhoton_;
  ElectronHistManager * electronHistManager_no_genPhoton_;

  MuonHistManager * muonHistManager_;
  MuonHistManager * muonHistManager_genHadTau_;
  MuonHistManager * muonHistManager_genLepton_;
  MuonHistManager * muonHistManager_genHadTauOrLepton_;
  MuonHistManager * muonHistManager_genJet_;
  MuonHistManager * muonHistManager_genPhoton_;


  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTau_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genJet_;
  EvtHistManager_LeptonFakeRate * evtHistManager_LeptonFakeRate_genPhoton_;


  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_genHadTau_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_genLepton_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_genHadTauOrLepton_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_genJet_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_genPhoton_;
  EvtHistManager_LeptonEfficiency * evtHistManager_LeptonEfficiency_no_genPhoton_;
};

void
fillHistograms(std::vector<numerator_and_denominatorHistManagers *> & histograms,
               const RecoLepton & lepton,
               double met_pt,
               double mT,
               double mT_fix,
               double evtWeight_LepJetPair,
               cutFlowTableType * cutFlowTable = nullptr);

void
fillHistograms(std::vector<numerator_and_denominatorHistManagers *> & histograms,
               const RecoLepton & lepton_probe,
               const RecoLepton & lepton_tag,
               double m_ll,
               double evtWeight,
               cutFlowTableType * cutFlowTable = nullptr);



void
fillHistograms(std::vector<numerator_and_denominatorHistManagers *> & histograms,
               const RecoLepton & lepton,
               double m_ll,
               double evtWeight,
               cutFlowTableType * cutFlowTable = nullptr);

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       const std::string & cut);

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       std::vector<numerator_and_denominatorHistManagers *> & histograms);

RecoMEt
METSystComp_LeptonFakeRate(const RecoLepton * const lepton,
                           const GenMEt & genmet,
                           const RecoMEt & met,
                           const double & scale,
                           METSyst central_or_shift,
                           bool debug);
