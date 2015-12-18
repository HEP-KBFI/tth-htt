#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"

#define _USE_MATH_DEFINES // M_PI
#include <cmath> // std::abs(), std::fabs(), std::sqrt(), std::pow()

RecoLepton::RecoLepton(Int_t _pdg_id,
                       Double_t _pt,
                       Double_t _eta,
                       Double_t _phi,
                       Double_t _mass,
                       Double_t _dxy,
                       Double_t _dz,
                       Double_t _rel_iso,
                       Double_t _sip3d,
                       Double_t _mva_tth,
                       Int_t _med_mu_id,
                       Int_t _ele_mva_id,
                       Int_t _lost_hits,
                       Int_t _loose_id,
                       Int_t _tight_charge,
                       Int_t _pass_conv_veto)

  : GenLepton(_pdg_id, _pt, _eta, _phi, _mass)
  , dxy(_dxy)
  , dz(_dz)
  , rel_iso(_rel_iso)
  , sip3d(_sip3d)
  , mva_tth(_mva_tth)
  , med_mu_id(_med_mu_id)
  , ele_mva_id(_ele_mva_id)
  , lost_hits(_lost_hits)
  , loose_id(_loose_id)
  , tight_charge(_tight_charge)
  , pass_conv_veto(_pass_conv_veto)
{ }

bool
RecoLepton::is_electron() const
{
  return std::abs(pdg_id) == 11;
}

bool
RecoLepton::is_muon() const
{
  return std::abs(pdg_id) == 13;
}

inline double
RecoLepton::dR(const GenLepton & other) const
{
  const double d_eta = std::fabs(eta - other.eta);
  double d_phi = std::fabs(phi - other.phi);
  if (d_phi > static_cast<double>(M_PI))
    d_phi -= 2 * static_cast<double>(M_PI);
  return std::sqrt(std::pow(d_eta, 2) + std::pow(d_phi, 2));
}

bool
RecoLepton::is_overlap(const GenLepton & other,
                       double dR_min) const
{
  return dR(other) < dR_min;
}
