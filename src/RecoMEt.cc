#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

RecoMEt::RecoMEt()
  : default_(0., 0.)
  , covXX_(0.)
  , covXY_(0.)
  , covYY_(0.)
  , p4_{default_.pt_, 0., default_.phi_, 0.}
  , cov_(2,2)
  , genPt_(0.)
  , genPhi_(0.)
{
  update_cov();
}

RecoMEt::RecoMEt(Float_t pt,
                 Float_t phi,
                 Float_t covXX,
                 Float_t covXY,
                 Float_t covYY)
  : default_(pt, phi)
  , covXX_(covXX)
  , covXY_(covXY)
  , covYY_(covYY)
  , p4_{default_.pt_, 0., default_.phi_, 0.}
  , sumEt_(0.)
  , cov_(2,2)
  , genPt_(0.)
  , genPhi_(0.)
{
  update_cov();
}

RecoMEt::RecoMEt(const math::PtEtaPhiMLorentzVector & p4,
                 const TMatrixD& cov)
  : default_(p4.pt(), p4.phi())
  , covXX_(static_cast<Float_t>(cov(0,0)))
  , covXY_(static_cast<Float_t>(cov(0,1)))
  , covYY_(static_cast<Float_t>(cov(1,1)))
  , p4_(p4)
  , sumEt_(0.)
  , cov_(cov)
  , genPt_(0.)
  , genPhi_(0.)
{}

RecoMEt &
RecoMEt::operator=(const RecoMEt & other)
{
  default_ = other.default_;
  for(const auto & kv: other.systematics_)
  {
    systematics_[kv.first] = kv.second;
  }
  covXX_ = other.covXX_;
  covXY_ = other.covXY_;
  covYY_ = other.covYY_;
  sumEt_ = other.sumEt_;
  update();
  return *this;
}

void
RecoMEt::update()
{
  update_p4();
  update_cov();
}

void
RecoMEt::update_p4()
{
  p4_ = math::PtEtaPhiMLorentzVector(default_.pt_, 0., default_.phi_, 0.);
}

void
RecoMEt::update_cov()
{
  cov_(0,0) = static_cast<Double_t>(covXX_);
  cov_(0,1) = static_cast<Double_t>(covXY_);
  cov_(1,0) = static_cast<Double_t>(covXY_);
  cov_(1,1) = static_cast<Double_t>(covYY_);
}

Double_t
RecoMEt::pt() const
{
  return static_cast<Double_t>(default_.pt_);
}

Double_t
RecoMEt::phi() const
{
  return static_cast<Double_t>(default_.phi_);
}

Double_t 
RecoMEt::sumEt() const
{
  return static_cast<Double_t>(sumEt_);
}
Double_t
RecoMEt::covXX() const
{
  return static_cast<Double_t>(covXX_);
}

Double_t
RecoMEt::covXY() const
{
  return static_cast<Double_t>(covXY_);
}

Double_t
RecoMEt::covYY() const
{
  return static_cast<Double_t>(covYY_);
}

const Particle::LorentzVector &
RecoMEt::p4() const
{
  return p4_;
}

const TMatrixD &
RecoMEt::cov() const
{
  return cov_;
}

void 
RecoMEt::set_genPt(double genPt)
{
  genPt_ = genPt;
}

void 
RecoMEt::set_genPhi(double genPhi)
{
  genPhi_ = genPhi;
}

Double_t 
RecoMEt::genPt() const
{
  return genPt_;
}

Double_t 
RecoMEt::genPhi() const
{
  return genPhi_;
}

std::ostream& operator<<(std::ostream& stream,
                         const RecoMEt& met)
{
  stream << " pT = " << met.pt() << ","
            " phi = " << met.phi() << "\n"
            " cov:\n";
  met.cov().Print();
  return stream;
}

RecoMEt::MEt::MEt(Float_t pt, Float_t phi)
  : pt_(pt)
  , phi_(phi)
{}

RecoMEt::MEt::MEt()
  : pt_(0.)
  , phi_(0.)
{}

RecoMEt::MEt &
RecoMEt::MEt::operator=(const RecoMEt::MEt & other)
{
  pt_ = other.pt_;
  phi_ = other.phi_;
  return *this;
}
