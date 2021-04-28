#include "tthAnalysis/HiggsToTauTau/interface/HHCoupling.h"

HHCoupling::HHCoupling(double kl,
                       double kt,
                       double c2,
                       double cg,
                       double c2g,
                       const std::string & name,
                       const std::string & training)
  : kl_(kl)
  , kt_(kt)
  , c2_(c2)
  , cg_(cg)
  , c2g_(c2g)
  , name_(name)
  , training_(training)
{}

HHCoupling::HHCoupling(const std::vector<double> & couplings,
                       const std::string & name,
                       const std::string & training)
  : HHCoupling(couplings.at(0), couplings.at(1), couplings.at(2), couplings.at(3), couplings.at(4), name, training)
{}

double
HHCoupling::kl() const
{
  return kl_;
}

double
HHCoupling::kt() const
{
  return kt_;
}

double
HHCoupling::c2() const
{
  return c2_;
}

double
HHCoupling::cg() const
{
  return cg_;
}

double
HHCoupling::c2g() const
{
  return c2g_;
}

std::string
HHCoupling::name() const
{
  return name_;
}

std::string
HHCoupling::weightName() const
{
  return "Weight_" + name_;
}

std::string
HHCoupling::training() const
{
  return training_;
}
