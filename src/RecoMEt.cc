#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

RecoMEt::RecoMEt()
  : pt_(0.)
  , phi_(0.)
  , covXX_(0.)
  , covXY_(0.)
  , covYY_(0.)
  , p4_{pt_, 0., phi_, 0.}
  , cov_(2,2)
{
  cov_(0,0) = covXX_;
  cov_(0,1) = covXY_;
  cov_(1,0) = covXY_;
  cov_(1,1) = covYY_;
}

RecoMEt::RecoMEt(Double_t pt,
		 Double_t phi,
		 Double_t covXX,
		 Double_t covXY,
		 Double_t covYY)
  : pt_(pt)
  , phi_(phi)
  , covXX_(covXX)
  , covXY_(covXY)
  , covYY_(covYY)
  , p4_{pt_, 0., phi_, 0.}
  , cov_(2,2)
{
  cov_(0,0) = covXX_;
  cov_(0,1) = covXY_;
  cov_(1,0) = covXY_;
  cov_(1,1) = covYY_;
}
    
RecoMEt::RecoMEt(const math::PtEtaPhiMLorentzVector & p4, const TMatrixD& cov)
  : pt_(p4.pt())
  , phi_(p4.phi())
  , covXX_(cov(0,0))
  , covXY_(cov(0,1))
  , covYY_(cov(1,1))
  , p4_(p4)
  , cov_(cov)
{}

std::ostream &
operator<<(std::ostream & os,
           const RecoMEt & o)
{
  os << "pt = " << o.pt_ << "; "
     << "phi = " << o.phi_ << std::endl;
  os << "cov:" << std::endl;
  o.cov_.Print();
  return os;
}
