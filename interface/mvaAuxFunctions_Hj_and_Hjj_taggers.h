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
                                const EventInfo & eventInfo);
double comp_mvaOutput_Hjj_tagger(const RecoJet* jet1, const RecoJet* jet2, const std::vector<const RecoJet*>& jets,
				 const std::vector<const RecoLepton*>& leptons,
				 std::map<std::string, double>& mvaInputs_Hjj_tagger, TMVAInterface& mva_Hjj_tagger,
				 std::map<std::string, double>& mvaInputs_Hj_tagger, TMVAInterface& mva_Hj_tagger,
				 const EventInfo & eventInfo);

#endif // tthAnalysis_HiggsToTauTau_mvaAuxFunctions_Hj_and_Hjj_taggers_h
