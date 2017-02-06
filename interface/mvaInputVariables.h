#ifndef tthAnalysis_HiggsToTauTau_mvaInputVariables_h
#define tthAnalysis_HiggsToTauTau_mvaInputVariables_h

/**
 * @brief Calculates input variables of the MVA used for signal extraction in the 2lss_1tau category (described in Section 5 of AN-2015/321)
 */

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoJet

double comp_MT_met_lep1(const Particle::LorentzVector& leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep1(const GenParticle& lepton, double met_pt, double met_phi);
double comp_MT_met_lep2(const Particle::LorentzVector& leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep2(const GenParticle& lepton, double met_pt, double met_phi);
double comp_MT_met_hadTau1(const GenParticle& hadTau, double met_pt, double met_phi);
double comp_MT_met_hadTau2(const GenParticle& hadTau, double met_pt, double met_phi);
double comp_n_jet25_recl(const std::vector<const RecoJet*>& jets_cleaned);
double comp_mindr_lep1_jet(const GenParticle& lepton, const std::vector<const RecoJet*>& jets_cleaned);
double comp_mindr_lep2_jet(const GenParticle& lepton, const std::vector<const RecoJet*>& jets_cleaned);
double comp_mindr_hadTau1_jet(const GenParticle& hadTau, const std::vector<const RecoJet*>& jets_cleaned);
double comp_mindr_hadTau2_jet(const GenParticle& hadTau, const std::vector<const RecoJet*>& jets_cleaned);
double comp_lep1_conePt(const RecoLepton& lepton);
double comp_lep2_conePt(const RecoLepton& lepton);
double comp_lep3_conePt(const RecoLepton& lepton);
double comp_avg_dr_jet(const std::vector<const RecoJet*>& jets_cleaned);

#endif // mvaInputVariables_h
