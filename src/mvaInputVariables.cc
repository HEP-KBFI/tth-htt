#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

namespace
{
  double square(double x)
  {
    return x*x;
  }
}

double comp_MT_met_lep1(const Particle::LorentzVector& leptonP4, double met_pt, double met_phi)
{
  double met_px = met_pt*std::cos(met_phi);
  double met_py = met_pt*std::sin(met_phi);
  double mT = std::sqrt(std::max(0., square(leptonP4.Et() + met_pt) - (square(leptonP4.px() + met_px) + square(leptonP4.py() + met_py))));
  return mT;
}

double comp_MT_met_lep1(const Particle& lepton, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(lepton.p4(), met_pt, met_phi);
}

double comp_MT_met_lep2(const Particle::LorentzVector& leptonP4, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(leptonP4, met_pt, met_phi);
}

double comp_MT_met_lep2(const Particle& lepton, double met_pt, double met_phi)
{
  return comp_MT_met_lep2(lepton.p4(), met_pt, met_phi);
}

double comp_MT_met_lep3(const Particle::LorentzVector& leptonP4, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(leptonP4, met_pt, met_phi);
}

double comp_MT_met_lep3(const Particle& lepton, double met_pt, double met_phi)
{
  return comp_MT_met_lep3(lepton.p4(), met_pt, met_phi);
}

double comp_MT_met_hadTau1(const Particle& hadTau, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

double comp_MT_met_hadTau2(const Particle& hadTau, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

double comp_MT_met_hadTau3(const Particle& hadTau, double met_pt, double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

double comp_n_jet25_recl(const std::vector<const RecoJet*>& jets_cleaned)
{
  int n_jets = 0;
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    if ( (*jet)->pt() > 25. && std::fabs((*jet)->eta()) < 2.4 ) ++n_jets;
  }
  return n_jets;
}

double comp_mindr_lep1_jet(const Particle& lepton, const std::vector<const RecoJet*>& jets_cleaned)
{
  double dRmin = 1.e+3;
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    double dR = deltaR(lepton.eta(), lepton.phi(), (*jet)->eta(), (*jet)->phi());
    if ( dR < dRmin ) dRmin = dR;
  }
  return dRmin;
}

double comp_mindr_lep2_jet(const Particle& lepton, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double comp_mindr_lep3_jet(const Particle& lepton, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double comp_mindr_hadTau1_jet(const Particle& hadTau, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double comp_mindr_hadTau2_jet(const Particle& hadTau, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double comp_mindr_hadTau3_jet(const Particle& hadTau, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double comp_lep1_conePt(const RecoLepton& lepton)
{
  return lepton.cone_pt();
}

double comp_lep2_conePt(const RecoLepton& lepton)
{
  return comp_lep1_conePt(lepton);
}

double comp_lep3_conePt(const RecoLepton& lepton)
{
  return comp_lep1_conePt(lepton);
}

double comp_avg_dr_jet(const std::vector<const RecoJet*>& jets_cleaned)
{
  int n_jet_pairs = 0;
  double dRsum = 0.;
  for ( std::vector<const RecoJet*>::const_iterator jet1 = jets_cleaned.begin();
	jet1 != jets_cleaned.end(); ++jet1 ) {
    if ( (*jet1)->pt() > 25. && std::fabs((*jet1)->eta()) < 2.4 ) {
      for ( std::vector<const RecoJet*>::const_iterator jet2 = jet1 + 1;
	    jet2 != jets_cleaned.end(); ++jet2 ) {
	if ( (*jet2)->pt() > 25. && std::fabs((*jet2)->eta()) < 2.4 ) {
	  double dR = deltaR((*jet1)->eta(), (*jet1)->phi(), (*jet2)->eta(), (*jet2)->phi());
	  dRsum += dR;
	  ++n_jet_pairs;
	}
      }
    }
  }
  double avg_dr_jet = ( n_jet_pairs > 0 ) ? dRsum/n_jet_pairs : 0.;
  return avg_dr_jet;
}

double comp_max_dr_jet(const std::vector<const RecoJet*>& jets_cleaned)
{
  double dRmax = 0.;
  for ( std::vector<const RecoJet*>::const_iterator jet1 = jets_cleaned.begin();
	jet1 != jets_cleaned.end(); ++jet1 ) {
    if ( (*jet1)->pt() > 25. && std::fabs((*jet1)->eta()) < 2.4 ) {
      for ( std::vector<const RecoJet*>::const_iterator jet2 = jet1 + 1;
	    jet2 != jets_cleaned.end(); ++jet2 ) {
	if ( (*jet2)->pt() > 25. && std::fabs((*jet2)->eta()) < 2.4 ) {
	  double dR = deltaR((*jet1)->eta(), (*jet1)->phi(), (*jet2)->eta(), (*jet2)->phi());
	  if ( dR > dRmax ) dRmax = dR;
	}
      }
    }
  }
  return dRmax;
}

double compHT(const std::vector<const RecoLepton*>& leptons, const std::vector<const RecoHadTau*>& hadTaus, const std::vector<const RecoJet*>& jets_cleaned)
{
  double ht = 0.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    ht += (*lepton)->pt();
  }
  for ( std::vector<const RecoHadTau*>::const_iterator hadTau = hadTaus.begin();
	hadTau != hadTaus.end(); ++hadTau ) {
    ht += (*hadTau)->pt();
  }
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    ht += (*jet)->pt();
  }
  return ht;
}
