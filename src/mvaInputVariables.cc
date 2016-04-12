#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" 

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

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
  double mT = std::sqrt(square(lepton.p4_.Et() + met_pt) - (square(lepton.p4_.px() + met_px) + square(lepton.p4_.py() + met_py)));
  return mT;
}

double comp_n_jet25_recl(const std::vector<const RecoJet*>& jets_cleaned)
{
  int n_jets = 0;
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    if ( (*jet)->pt_ > 25. && std::fabs((*jet)->eta_) < 2.4 ) ++n_jets;
  }
  return n_jets;
}

double comp_mindr_lep1_jet(const GenParticle& lepton, const std::vector<const RecoJet*>& jets_cleaned)
{
  double dRmin = 1.e+3;
  for ( std::vector<const RecoJet*>::const_iterator jet = jets_cleaned.begin();
	jet != jets_cleaned.end(); ++jet ) {
    double dR = deltaR(lepton.eta_, lepton.phi_, (*jet)->eta_, (*jet)->phi_);
    if ( dR < dRmin ) dRmin = dR;
  }
  return dRmin;
}

double comp_mindr_lep2_jet(const GenParticle& lepton, const std::vector<const RecoJet*>& jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double comp_lep1_conePt(const RecoLepton& lepton)
{
  double conePt = 0.;
  int abs_pdgId = std::abs(lepton.pdgId_);
  if ( abs_pdgId == 11 || abs_pdgId == 13 ) {
    const RecoElectron* electron = dynamic_cast<const RecoElectron*>(&lepton);
    const RecoMuon* muon = dynamic_cast<const RecoMuon*>(&lepton);
    if ( (electron || muon->passesMediumIdPOG_ > 0) && lepton.mvaRawTTH_ > 0.75 ) conePt = lepton.pt_;
    else conePt = 0.85*lepton.pt_/lepton.jetPtRatio_;
  } else {
    conePt = lepton.pt_;
  }
  return conePt;
}

double comp_lep2_conePt(const RecoLepton& lepton)
{
  return comp_lep1_conePt(lepton);
}

double comp_avg_dr_jet(const std::vector<const RecoJet*>& jets_cleaned)
{
  int n_jet_pairs = 0;
  double dRsum = 0.;
  for ( std::vector<const RecoJet*>::const_iterator jet1 = jets_cleaned.begin();
	jet1 != jets_cleaned.end(); ++jet1 ) {
    if ( (*jet1)->pt_ > 25. && std::fabs((*jet1)->eta_) < 2.4 ) {
      for ( std::vector<const RecoJet*>::const_iterator jet2 = jet1 + 1;
	    jet2 != jets_cleaned.end(); ++jet2 ) {
	if ( (*jet2)->pt_ > 25. && std::fabs((*jet2)->eta_) < 2.4 ) {
	  double dR = deltaR((*jet1)->eta_, (*jet1)->phi_, (*jet2)->eta_, (*jet2)->phi_);
	  dRsum += dR;
	  ++n_jet_pairs;
	}
      }
    }
  }
  double avg_dr_jet = ( n_jet_pairs > 0 ) ? dRsum/n_jet_pairs : 0.;
  return avg_dr_jet;
}
