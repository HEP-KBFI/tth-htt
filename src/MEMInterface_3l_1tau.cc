#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l_1tau.h" // MEMInterface_3l_1tau

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherCSV()
#include "tthAnalysis/tthMEM/interface/Logger.h" // Logger::
#include "tthAnalysis/tthMEM/interface/general/lvFunctions.h" // getLorentzVector()

#include <TBenchmark.h> // TBenchmark

MEMInterface_3l_1tau::MEMInterface_3l_1tau()
  : clock_(nullptr)
{
  Logger::enableLogging(false);
  std::cout << "<MEMInterface_3l_1tau>:\n";

  // (postponed the creation of the inteface object so that no internal messages printed in
  // the MEM code won't end up on the screen)
  mem_ = std::unique_ptr<MEMInterface_3l1tau>(new MEMInterface_3l1tau());
  mem_ -> initialize();

  clock_ = new TBenchmark();
}

MEMInterface_3l_1tau::~MEMInterface_3l_1tau()
{
  delete clock_;
}

MEMOutput_3l_1tau
MEMInterface_3l_1tau::operator()(const RecoLepton * selLepton_lead,
                                 const RecoLepton * selLepton_sublead,
                                 const RecoLepton * selLepton_third,
                                 const RecoHadTau * selHadTau,
                                 const RecoMEt & met,
                                 const std::vector<const RecoJet *> & selJets)
{
  std::vector<const RecoJet *> selJets_copy = selJets;
  std::sort(selJets_copy.begin(), selJets_copy.end(), isHigherCSV);
  std::vector<MeasuredJet> jets;
  for(const RecoJet * const & j: selJets_copy)
  {
    jets.push_back({ getLorentzVector(j -> p4()) });
    if(jets.size() >= MAX_NOF_RECO_JETS)
    {
      break;
    }
  }
  const MeasuredLepton leadingLepton(
    getLorentzVector(selLepton_lead -> p4()), selLepton_lead -> charge()
  );
  const MeasuredLepton subLeadingLepton(
    getLorentzVector(selLepton_sublead -> p4()), selLepton_sublead -> charge()
  );
  const MeasuredLepton thirdLepton(
    getLorentzVector(selLepton_third -> p4()), selLepton_third -> charge()
  );
  const MeasuredHadronicTau tau(
    getLorentzVector(selHadTau -> p4()), selHadTau -> charge(), selHadTau -> decayMode()
  );
  const MeasuredMET m_met(
    met.pt(), met.phi(), met.covXX(), met.covXY(), met.covYY()
  );

  MEMOutput_3l_1tau result;
  if(mem_)
  {
    clock_->Reset();
    clock_->Start("<MEMInterface_3l_1tau::operator()>");

    const MEMOutput_3l1tau tmpResult = mem_->operator()(
      jets, leadingLepton, subLeadingLepton, thirdLepton, tau, m_met
    );

    clock_->Stop("<MEMInterface_3l_1tau::operator()>");
    clock_->Show("<MEMInterface_3l_1tau::operator()>");

    result.fillInputs(selLepton_lead, selLepton_sublead, selLepton_third, selHadTau);
    result.weight_ttH_     = tmpResult.prob_tth;
    result.weight_ttZ_     = tmpResult.prob_ttz;
    result.weight_ttH_hww_ = tmpResult.prob_tth_h2ww;
    result.LR_             = tmpResult.lr;
    result.isValid_        = ! tmpResult.err ? 1 : 0;
    result.errorFlag_      = tmpResult.err;

    result.cpuTime_  = clock_->GetCpuTime("<MEMInterface_3l_1tau::operator()>");
    result.realTime_ = clock_->GetRealTime("<MEMInterface_3l_1tau::operator()>");
  }
  else
  {
    result.isValid_ = 0;
  }

  return result;
}

