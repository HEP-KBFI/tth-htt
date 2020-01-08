#ifndef tthAnalysis_HiggsToTauTau_mvaInputVariables_h
#define tthAnalysis_HiggsToTauTau_mvaInputVariables_h

/**
 * @brief Calculates input variables of the MVA used for signal extraction in the 2lss_1tau category (described in Section 5 of AN-2015/321)
 */

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton, ChargedParticle, Particle

// forward declarations
class RecoJet;
class RecoHadTau;

double comp_MT_met(const Particle::LorentzVector & leptonP4, double met_pt, double met_phi);
double comp_MT_met(const RecoLepton * lepton,                double met_pt, double met_phi);
double comp_MT_met(const RecoHadTau * hadTau,                double met_pt, double met_phi);

double
comp_massL2(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            double met_pt,
            double met_phi);

double
comp_massL3(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            const ChargedParticle * particle3,
            double met_pt,
            double met_phi);

double
comp_massL4(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            const ChargedParticle * particle3,
            const ChargedParticle * particle4,
            double met_pt,
            double met_phi);

double comp_pZeta    (const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy);
double comp_pZetaVis (const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4);
double comp_pZetaComb(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy);

double comp_n_jet25_recl(const std::vector<const RecoJet *> & jets_cleaned);

double comp_mindr_jet(const Particle & particle, const std::vector<const RecoJet *> & jets_cleaned);
double comp_lep_conePt(const RecoLepton & lepton);

double comp_avg_dr_jet(const std::vector<const RecoJet *> & jets_cleaned);
double comp_max_dr_jet(const std::vector<const RecoJet *> & jets_cleaned);

double comp_cosThetaStar(const Particle::LorentzVector & daughterP4_lead, const Particle::LorentzVector & daughterP4_sublead);

#endif // mvaInputVariables_h
