#ifndef tthAnalysis_HiggsToTauTau_mvaInputVariables_h
#define tthAnalysis_HiggsToTauTau_mvaInputVariables_h

/**
 * @brief Calculates input variables of the MVA used for signal extraction in the 2lss_1tau category (described in Section 5 of AN-2015/321)
 */

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

double comp_MT_met_lep1(const Particle::LorentzVector & leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep1(const Particle & lepton,                  double met_pt, double met_phi);
double comp_MT_met_lep2(const Particle::LorentzVector & leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep2(const Particle & lepton,                  double met_pt, double met_phi);
double comp_MT_met_lep3(const Particle::LorentzVector & leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep3(const Particle & lepton,                  double met_pt, double met_phi);
double comp_MT_met_lep4(const Particle::LorentzVector & leptonP4, double met_pt, double met_phi);
double comp_MT_met_lep4(const Particle & lepton,                  double met_pt, double met_phi);

double comp_MT_met_hadTau1(const Particle & hadTau, double met_pt, double met_phi);
double comp_MT_met_hadTau2(const Particle & hadTau, double met_pt, double met_phi);
double comp_MT_met_hadTau3(const Particle & hadTau, double met_pt, double met_phi);

double comp_pZeta(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy);
double comp_pZetaVis(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4);
double comp_pZetaComb(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy);

double comp_n_jet25_recl(const std::vector<const RecoJet *> & jets_cleaned);

double comp_mindr_lep1_jet(const Particle & lepton, const std::vector<const RecoJet *> & jets_cleaned);
double comp_mindr_lep2_jet(const Particle & lepton, const std::vector<const RecoJet *> & jets_cleaned);
double comp_mindr_lep3_jet(const Particle & lepton, const std::vector<const RecoJet *> & jets_cleaned);
double comp_mindr_lep4_jet(const Particle & lepton, const std::vector<const RecoJet *> & jets_cleaned);

double comp_mindr_hadTau1_jet(const Particle & hadTau, const std::vector<const RecoJet *> & jets_cleaned);
double comp_mindr_hadTau2_jet(const Particle & hadTau, const std::vector<const RecoJet *> & jets_cleaned);
double comp_mindr_hadTau3_jet(const Particle & hadTau, const std::vector<const RecoJet *> & jets_cleaned);

double comp_lep1_conePt(const RecoLepton & lepton);
double comp_lep2_conePt(const RecoLepton & lepton);
double comp_lep3_conePt(const RecoLepton & lepton);
double comp_lep4_conePt(const RecoLepton & lepton);

double comp_avg_dr_jet(const std::vector<const RecoJet *> & jets_cleaned);
double comp_max_dr_jet(const std::vector<const RecoJet *> & jets_cleaned);

double comp_cosThetaStar(const Particle::LorentzVector & daughterP4, const Particle::LorentzVector & motherP4);

#endif // mvaInputVariables_h
