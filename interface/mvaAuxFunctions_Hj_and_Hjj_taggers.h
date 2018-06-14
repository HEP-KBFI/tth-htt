#ifndef tthAnalysis_HiggsToTauTau_mvaAuxFunctions_Hj_and_Hjj_taggers_h
#define tthAnalysis_HiggsToTauTau_mvaAuxFunctions_Hj_and_Hjj_taggers_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface

#include <vector> // std::vector<>
#include <map> // std::map<>
#include <string> // std::string

double comp_mvaOutput_Hj_tagger(const RecoJet* jet,
                                const std::vector<const RecoLepton*>& leptons,
                                std::map<std::string, double>& mvaInputs_Hj_tagger,
                                TMVAInterface& mva_Hj_tagger,
                                const EventInfo & eventInfo)
{
  double dRmin_lepton = -1.;
  double dRmax_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(jet->eta(), jet->phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) dRmin_lepton = dR;
    if ( dRmax_lepton == -1. || dR > dRmax_lepton ) dRmax_lepton = dR;
  }

  mvaInputs_Hj_tagger["Jet25_lepdrmin"] = dRmin_lepton;
  mvaInputs_Hj_tagger["max(Jet25_bDiscriminator,0.)"] = std::max(0., jet->());
  mvaInputs_Hj_tagger["max(Jet25_qg,0.)"] = std::max(0., jet->QGDiscr());
  mvaInputs_Hj_tagger["Jet25_lepdrmax"] = dRmax_lepton;
  mvaInputs_Hj_tagger["Jet25_pt"] = jet->pt();

  check_mvaInputs(mvaInputs_Hj_tagger, eventInfo);

  double mvaOutput_Hj_tagger = mva_Hj_tagger(mvaInputs_Hj_tagger);
  return mvaOutput_Hj_tagger;
}
double comp_mvaOutput_Hjj_tagger(const RecoJet* jet1, const RecoJet* jet2, const std::vector<const RecoJet*>& jets,
				 const std::vector<const RecoLepton*>& leptons,
				 std::map<std::string, double>& mvaInputs_Hjj_tagger, TMVAInterface& mva_Hjj_tagger,
				 std::map<std::string, double>& mvaInputs_Hj_tagger, TMVAInterface& mva_Hj_tagger,
				 const EventInfo & eventInfo);

#endif // tthAnalysis_HiggsToTauTau_mvaAuxFunctions_Hj_and_Hjj_taggers_h
