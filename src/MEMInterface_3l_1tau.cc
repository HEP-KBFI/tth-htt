#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l_1tau.h" // MEMInterface_3l_1tau
#include "tthAnalysis/tthMEM/interface/Logger.h" // Logger::
#include "tthAnalysis/tthMEM/interface/tthMEMlvFunctions.h" // getLorentzVector()

MEMInterface_3l_1tau::MEMInterface_3l_1tau()
{
  Logger::enableLogging(false);
  std::cout << "<MEMInterface_3l_1tau>:\n";

  // (postponed the creation of the inteface object so that no internal messages printed in
  // the MEM code won't end up on the screen)
  mem_ = std::unique_ptr<MEMInterface_3l1tau>(new MEMInterface_3l1tau());
}

MEMOutput_3l1tau
MEMInterface_3l_1tau::operator()(const RecoLepton * selLepton_lead,
                                 const RecoLepton * selLepton_sublead,
                                 const RecoLepton * selLepton_third,
                                 const RecoHadTau * selHadTau,
                                 const RecoMEt & met,
                                 const std::vector<const RecoJet *> & selJets)
{
  std::vector<MeasuredJet> jets;
  for(const RecoJet * const & j: selJets)
    jets.push_back({ getLorentzVector(j -> p4()) });
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

  if(mem_)
    return mem_ -> operator()(jets, leadingLepton, subLeadingLepton, thirdLepton, tau, m_met);
  else
    return MEMOutput_3l1tau(1);
}

