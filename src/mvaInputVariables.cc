#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <TLorentzVector.h> // TLorentzVector

#include <algorithm> // std::count_if()

namespace
{
  double square(double x)
  {
    return x*x;
  }

  Particle::LorentzVector
  getP4(const ChargedParticle * particle)
  {
    const RecoLepton * lepton = dynamic_cast<const RecoLepton *>(particle);
    const RecoHadTau * hadTau = dynamic_cast<const RecoHadTau *>(particle);
    assert(lepton || hadTau);
    Particle::LorentzVector lv = lepton ? lepton->cone_p4() : hadTau->p4();
    if(lepton)
    {
      // treat all leptons as massless
      lv.SetM(0.);
    }
    return lv;
  }
}

double
comp_MT_met(const Particle::LorentzVector & leptonP4,
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
comp_MT_met(const RecoLepton * lepton,
            double met_pt,
            double met_phi)
{
  return comp_MT_met(::getP4(lepton), met_pt, met_phi);
}

double
comp_MT_met(const RecoHadTau * hadTau,
            double met_pt,
            double met_phi)
{
  return comp_MT_met(::getP4(hadTau), met_pt, met_phi);
}

double
comp_massL2(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            double met_pt,
            double met_phi)
{
  return comp_MT_met(::getP4(particle1) + ::getP4(particle2), met_pt, met_phi);
}

double
comp_massL3(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            const ChargedParticle * particle3,
            double met_pt,
            double met_phi)
{
  return comp_MT_met(::getP4(particle1) + ::getP4(particle2) + ::getP4(particle3), met_pt, met_phi);
}

double
comp_massL4(const ChargedParticle * particle1,
            const ChargedParticle * particle2,
            const ChargedParticle * particle3,
            const ChargedParticle * particle4,
            double met_pt,
            double met_phi)
{
  return comp_MT_met(::getP4(particle1) + ::getP4(particle2) + ::getP4(particle3) + ::getP4(particle4), met_pt, met_phi);
}

namespace
{
  std::pair<double, double>
  comp_zetaX_and_Y(const Particle::LorentzVector & vis1P4,
                   const Particle::LorentzVector & vis2P4)
  {
    double uX1 = 0.;
    double uY1 = 0.;
    if(vis1P4.pt() > 0.)
    {
      uX1 = vis1P4.px() / vis1P4.pt();
      uY1 = vis1P4.py() / vis1P4.pt();
    }

    double uX2 = 0.;
    double uY2 = 0.;
    if(vis2P4.pt() > 0.)
    {
      uX2 = vis2P4.px() / vis2P4.pt();
      uY2 = vis2P4.py() / vis2P4.pt();
    }

    double zetaX = uX1 + uX2;
    double zetaY = uY1 + uY2;
    const double zetaR = std::sqrt(zetaX * zetaX + zetaY * zetaY);
    if(zetaR > 0.)
    {
      zetaX /= zetaR;
      zetaY /= zetaR;
    }
    return std::pair<double, double>(zetaX, zetaY);
  }
}

double
comp_pZeta(const Particle::LorentzVector & vis1P4,
           const Particle::LorentzVector & vis2P4,
           double metPx,
           double metPy)
{
  const std::pair<double, double> zetaX_and_Y = comp_zetaX_and_Y(vis1P4, vis2P4);
  const double zetaX = zetaX_and_Y.first;
  const double zetaY = zetaX_and_Y.second;
  const double sumPx = vis1P4.px() + vis2P4.px() + metPx;
  const double sumPy = vis1P4.py() + vis2P4.py() + metPy;
  const double pZeta = sumPx * zetaX + sumPy * zetaY;
  return pZeta;
}

double
comp_pZetaVis(const Particle::LorentzVector & vis1P4,
              const Particle::LorentzVector & vis2P4)
{
  const std::pair<double, double> zetaX_and_Y = comp_zetaX_and_Y(vis1P4, vis2P4);
  const double zetaX    = zetaX_and_Y.first;
  const double zetaY    = zetaX_and_Y.second;
  const double visSumPx = vis1P4.px() + vis2P4.px();
  const double visSumPy = vis1P4.py() + vis2P4.py();
  const double pZetaVis = visSumPx * zetaX + visSumPy * zetaY;
  return pZetaVis;
}

double
comp_pZetaComb(const Particle::LorentzVector & vis1P4,
               const Particle::LorentzVector & vis2P4,
               double metPx,
               double metPy)
{
  const double pZeta     = comp_pZeta(vis1P4, vis2P4, metPx, metPy);
  const double pZetaVis  = comp_pZetaVis(vis1P4, vis2P4);
  const double pZetaComb = pZeta - 1.85 * pZetaVis;
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
comp_mindr_jet(const Particle & particle,
               const std::vector<const RecoJet *> & jets_cleaned)
{
  double dRmin = 1.e+3;
  for(const RecoJet * jet: jets_cleaned)
  {
    const double dR = deltaR(particle.eta(), particle.phi(), jet->eta(), jet->phi());
    dRmin = std::min(dR, dRmin);
  }
  return dRmin;
}

double
comp_lep_conePt(const RecoLepton & lepton)
{
  return lepton.cone_pt();
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
comp_cosThetaStar(const Particle::LorentzVector & daughterP4_lead,
                  const Particle::LorentzVector & daughterP4_sublead)
{
  // CV: compute "helicity angle" between momentum vectors of daughter and mother particle
  //     in the rest-frame of the mother particle
  //    (cf. Section 2.6.2 and Fig. 59 of AN-2015/001)
  TLorentzVector daughterP4tlv_lead;
  daughterP4tlv_lead.SetPtEtaPhiM(daughterP4_lead.pt(), daughterP4_lead.eta(), daughterP4_lead.phi(), daughterP4_lead.mass());
  TLorentzVector daughterP4tlv_sublead;
  daughterP4tlv_sublead.SetPtEtaPhiM(daughterP4_sublead.pt(), daughterP4_sublead.eta(), daughterP4_sublead.phi(), daughterP4_sublead.mass());
  const TLorentzVector motherP4 = daughterP4tlv_lead + daughterP4tlv_sublead;
  TLorentzVector daughterBoost = daughterP4tlv_lead; // can be subleading, too, doesn't matter
  daughterBoost.Boost(-motherP4.BoostVector());
  return std::fabs(daughterBoost.CosTheta());
}
