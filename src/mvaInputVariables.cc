#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" 

#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

namespace
{
  double square(double x)
  {
    return x*x;
  }
}

double comp_MT_met_lep1(const GenParticle& lepton, double met_pt, double met_phi)
{
  double met_px = met_pt*std::cos(met_phi);
  double met_py = met_pt*std::sin(met_phi);
  double mT = std::sqrt(square(lepton.p4.Et() + met_pt) - (square(lepton.p4.px() + met_px) + square(lepton.p4.py() + met_py)));
  return mT;
}

double comp_n_jet25_recl(const std::vector<RecoJet>& jets_cleaned)
{
  int n_jets = 0;
  for ( std::vector<RecoJet>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    if ( jet->pt > 25. && std::fabs(jet->eta) < 2.4 ) ++n_jets;
  }
  return n_jets;
}

double comp_mindr_lep1_jet(const GenParticle& lepton, const std::vector<RecoJet>& jets_cleaned)
{
  double dRmin = 1.e+3;
  for ( std::vector<RecoJet>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    double dR = deltaR(lepton.eta, lepton.phi, jet->eta, jet->phi);
    if ( dR < dRmin ) dRmin = dR;
  }
  return dRmin;
}

double comp_mindr_lep2_jet(const GenParticle& lepton, const std::vector<RecoJet>& jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double comp_lep1_conePt(const RecoLepton& lepton)
{
  double conePt = 0.;
  int abs_pdg_id = std::abs(lepton.pdg_id);
  if ( abs_pdg_id == 11 || abs_pdg_id == 13 ) {
    if ( (abs_pdg_id == 11 || lepton.med_mu_id > 0) && lepton.mva_tth > 0.75 ) conePt = lepton.pt;
    else conePt = 0.85*lepton.pt/lepton.jetPtRatio;
  } else {
    conePt = lepton.pt;
  }
  return conePt;
}

double comp_lep2_conePt(const RecoLepton& lepton)
{
  return comp_lep1_conePt(lepton);
}

double comp_avg_dr_jet(const std::vector<RecoJet>& jets_cleaned)
{
  int n_jet_pairs = 0;
  double dRsum = 0.;
  for ( std::vector<RecoJet>::const_iterator jet1 = jets_cleaned.begin();
	jet1 != jets_cleaned.end(); ++jet1 ) {
    if ( jet1->pt > 25. && std::fabs(jet1->eta) < 2.4 ) {
      for ( std::vector<RecoJet>::const_iterator jet2 = jet1 + 1;
	    jet2 != jets_cleaned.end(); ++jet2 ) {
	if ( jet2->pt > 25. && std::fabs(jet2->eta) < 2.4 ) {
	  double dR = deltaR(jet1->eta, jet1->phi, jet2->eta, jet2->phi);
	  dRsum += dR;
	  ++n_jet_pairs;
	}
      }
    }
  }
  double avg_dr_jet = ( n_jet_pairs > 0 ) ? dRsum/n_jet_pairs : 0.;
  return avg_dr_jet;
}
