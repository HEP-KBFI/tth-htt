#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h"

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <TLorentzVector.h> // TLorentzVector

#include <algorithm> // std::count_if()

namespace
{
  double square(double x)
  {
    return x*x;
  }
}

double
comp_MT_met_lep1(const Particle::LorentzVector & leptonP4,
                 double met_pt,
                 double met_phi)
{
  const double met_px = met_pt*std::cos(met_phi);
  const double met_py = met_pt*std::sin(met_phi);
  const double mT = std::sqrt(
    std::max(
      0.,
      square(leptonP4.Et() + met_pt) - (square(leptonP4.px() + met_px) + square(leptonP4.py() + met_py)))
  );
  return mT;
}

double
comp_MT_met_lep1(const Particle & lepton,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep1(lepton.p4(), met_pt, met_phi);
}

double
comp_MT_met_lep2(const Particle::LorentzVector & leptonP4,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep1(leptonP4, met_pt, met_phi);
}

double
comp_MT_met_lep2(const Particle & lepton,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep2(lepton.p4(), met_pt, met_phi);
}

double
comp_MT_met_lep3(const Particle::LorentzVector & leptonP4,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep1(leptonP4, met_pt, met_phi);
}

double
comp_MT_met_lep3(const Particle & lepton,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep3(lepton.p4(), met_pt, met_phi);
}

double
comp_MT_met_lep4(const Particle::LorentzVector & leptonP4,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep1(leptonP4, met_pt, met_phi);
}

double
comp_MT_met_lep4(const Particle & lepton,
                 double met_pt,
                 double met_phi)
{
  return comp_MT_met_lep4(lepton.p4(), met_pt, met_phi);
}

double
comp_MT_met_hadTau1(const Particle & hadTau,
                    double met_pt,
                    double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

double
comp_MT_met_hadTau2(const Particle & hadTau,
                    double met_pt,
                    double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

double
comp_MT_met_hadTau3(const Particle & hadTau,
                    double met_pt,
                    double met_phi)
{
  return comp_MT_met_lep1(hadTau, met_pt, met_phi);
}

namespace
{
  std::pair<double, double> comp_zetaX_and_Y(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4)
  {
    double uX1 = 0.;
    double uY1 = 0.;
    if ( vis1P4.pt() > 0. ) {
      uX1 = vis1P4.px()/vis1P4.pt();
      uY1 = vis1P4.py()/vis1P4.pt();
    }
    double uX2 = 0.;
    double uY2 = 0.;
    if ( vis2P4.pt() > 0. ) {
      uX2 = vis2P4.px()/vis2P4.pt();
      uY2 = vis2P4.py()/vis2P4.pt();
    }
    double zetaX = uX1 + uX2;
    double zetaY = uY1 + uY2;
    double zetaR = TMath::Sqrt(zetaX*zetaX + zetaY*zetaY);
    if ( zetaR > 0. ) {
      zetaX /= zetaR;
      zetaY /= zetaR;
    }
    return std::pair<double, double>(zetaX, zetaY);
  }
}

double comp_pZeta(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy)
{
  std::pair<double, double> zetaX_and_Y = comp_zetaX_and_Y(vis1P4, vis2P4);
  double zetaX = zetaX_and_Y.first;
  double zetaY = zetaX_and_Y.second;
  double sumPx = vis1P4.px() + vis2P4.px() + metPx;
  double sumPy = vis1P4.py() + vis2P4.py() + metPy;
  double pZeta = sumPx*zetaX + sumPy*zetaY;
  return pZeta;
}

double comp_pZetaVis(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4)
{
  std::pair<double, double> zetaX_and_Y = comp_zetaX_and_Y(vis1P4, vis2P4);
  double zetaX    = zetaX_and_Y.first;
  double zetaY    = zetaX_and_Y.second;
  double visSumPx = vis1P4.px() + vis2P4.px();
  double visSumPy = vis1P4.py() + vis2P4.py();
  double pZetaVis = visSumPx*zetaX + visSumPy*zetaY;
  return pZetaVis;
}

double comp_pZetaComb(const Particle::LorentzVector & vis1P4, const Particle::LorentzVector & vis2P4, double metPx, double metPy)
{
  double pZeta     = comp_pZeta(vis1P4, vis2P4, metPx, metPy);
  double pZetaVis  = comp_pZetaVis(vis1P4, vis2P4);
  double pZetaComb = pZeta - 1.85*pZetaVis;
  return pZetaComb;
}

double
comp_n_jet25_recl(const std::vector<const RecoJet *> & jets_cleaned)
{
  return std::count_if(
    jets_cleaned.cbegin(), jets_cleaned.cend(),
    [](const RecoJet * jet) -> bool
    {
      return jet->pt() > 25. && std::fabs(jet->eta()) < 2.4;
    }
  );
}

double
comp_mindr_lep1_jet(const Particle & lepton,
                    const std::vector<const RecoJet *> & jets_cleaned)
{
  double dRmin = 1.e+3;
  for(const RecoJet * jet: jets_cleaned)
  {
    const double dR = deltaR(lepton.eta(), lepton.phi(), jet->eta(), jet->phi());
    dRmin = std::min(dR, dRmin);
  }
  return dRmin;
}

double
comp_mindr_lep2_jet(const Particle & lepton,
                    const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double
comp_mindr_lep3_jet(const Particle & lepton,
                    const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double
comp_mindr_lep4_jet(const Particle & lepton,
                    const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(lepton, jets_cleaned);
}

double
comp_mindr_hadTau1_jet(const Particle & hadTau,
                       const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double
comp_mindr_hadTau2_jet(const Particle & hadTau,
                       const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double
comp_mindr_hadTau3_jet(const Particle & hadTau,
                       const std::vector<const RecoJet *> & jets_cleaned)
{
  return comp_mindr_lep1_jet(hadTau, jets_cleaned);
}

double
comp_lep1_conePt(const RecoLepton & lepton)
{
  return lepton.cone_pt();
}

double
comp_lep2_conePt(const RecoLepton & lepton)
{
  return comp_lep1_conePt(lepton);
}

double
comp_lep3_conePt(const RecoLepton & lepton)
{
  return comp_lep1_conePt(lepton);
}

double
comp_lep4_conePt(const RecoLepton & lepton)
{
  return comp_lep1_conePt(lepton);
}

double
comp_avg_dr_jet(const std::vector<const RecoJet *> & jets_cleaned)
{
  int n_jet_pairs = 0;
  double dRsum = 0.;
  for(auto jet1_it = jets_cleaned.cbegin(); jet1_it != jets_cleaned.cend(); ++jet1_it)
  {
    const RecoJet * jet1 = *jet1_it;
    if(jet1->pt() > 25. && std::fabs(jet1->eta()) < 2.4)
    {
      for(auto jet2_it = jet1_it + 1; jet2_it != jets_cleaned.cend(); ++jet2_it)
      {
        const RecoJet * jet2 = *jet2_it;
        if(jet2->pt() > 25. && std::fabs(jet2->eta()) < 2.4)
        {
          const double dR = deltaR(jet1->eta(), jet1->phi(), jet2->eta(), jet2->phi());
          dRsum += dR;
          ++n_jet_pairs;
        }
      }
    }
  }
  return n_jet_pairs > 0 ? dRsum / n_jet_pairs : 0.;
}

double
comp_max_dr_jet(const std::vector<const RecoJet *> & jets_cleaned)
{
  double dRmax = 0.;
  for(auto jet1_it = jets_cleaned.cbegin(); jet1_it != jets_cleaned.cend(); ++jet1_it)
  {
    const RecoJet * jet1 = *jet1_it;
    if(jet1->pt() > 25. && std::fabs(jet1->eta()) < 2.4)
    {
      for(auto jet2_it = jet1_it + 1; jet2_it != jets_cleaned.cend(); ++jet2_it)
      {
        const RecoJet * jet2 = *jet2_it;
        if(jet2->pt() > 25. && std::fabs(jet2->eta()) < 2.4)
        {
          const double dR = deltaR(jet1->eta(), jet1->phi(), jet2->eta(), jet2->phi());
          dRmax = std::max(dRmax, dR);
        }
      }
    }
  }
  return dRmax;
}

double 
comp_cosThetaStar(const Particle::LorentzVector & daughterP4, const Particle::LorentzVector & motherP4)
{
  // CV: compute "helicity angle" between momentum vectors of daughter and mother particle
  //     in the rest-frame of the mother particle
  //    (cf. Section 2.6.2 and Fig. 59 of AN-2015/001)
  TLorentzVector daughterP4_lv;
  daughterP4_lv.SetPtEtaPhiM(daughterP4.pt(), daughterP4.eta(), daughterP4.phi(), daughterP4.mass());
  TLorentzVector motherP4_lv;
  motherP4_lv.SetPtEtaPhiM(motherP4.pt(), motherP4.eta(), motherP4.phi(), motherP4.mass());
  daughterP4_lv.Boost(-motherP4_lv.BoostVector());
  const double cosThetaStar = std::fabs(daughterP4_lv.CosTheta());
  return cosThetaStar;
}
