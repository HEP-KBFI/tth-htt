#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer()

RecoJet::RecoJet(const GenJet & jet,
                 Double_t charge,
                 Double_t BtagCSV,
                 Double_t BtagWeight,
                 Double_t QGDiscr,
                 Double_t bRegCorr,
                 Double_t bRegRes,
                 Double_t pullEta,
                 Double_t pullPhi,
                 Double_t pullMag,
                 Int_t jetId,
                 Int_t puId,
                 Int_t genMatchIdx,
                 Int_t idx,
                 Btag btag,
                 Int_t central_or_shift)
  : RecoJetBase(jet, idx)
  , jetCharge_(charge)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , QGDiscr_(QGDiscr)
  , bRegCorr_(bRegCorr)
  , bRegRes_(bRegRes)
  , pullEta_(pullEta)
  , pullPhi_(pullPhi)
  , pullMag_(pullMag)
  , jetId_(jetId)
  , puId_(puId)
  , genMatchIdx_(genMatchIdx)
  , btag_(btag)
  , default_systematics_(central_or_shift)
{}

RecoJet::~RecoJet()
{}

Double_t
RecoJet::charge() const
{
  return jetCharge_;
}

Double_t
RecoJet::BtagCSV() const
{
  return BtagCSV_;
}

Double_t
RecoJet::BtagCSV(Btag btag) const
{
  if(! BtagCSVs_.count(btag))
  {
    throw cmsException(this, __func__, __LINE__)
      << "No such b-tagging score available: " << as_integer(btag)
    ;
  }
  return BtagCSVs_.at(btag);
}

Double_t
RecoJet::BtagWeight() const
{
  return BtagWeight_;
}

Double_t
RecoJet::BtagWeight(Btag btag,
                    int central_or_shift) const
{
  return BtagWeight_systematics_.at(btag).at(central_or_shift);
}

Double_t
RecoJet::BtagWeight(int central_or_shift) const
{
  return BtagWeight(btag_, central_or_shift);
}

Double_t
RecoJet::QGDiscr() const
{
  return QGDiscr_;
}

Double_t
RecoJet::bRegCorr() const
{
  return bRegCorr_;
}

Particle::LorentzVector
RecoJet::p4_bRegCorr() const
{
  return math::PtEtaPhiMLorentzVector(this->pt()*bRegCorr_, this->eta(), this->phi(), this->mass());
}

Double_t
RecoJet::bRegRes() const
{
  return bRegRes_;
}

Double_t
RecoJet::pullEta() const
{
  return pullEta_;
}

Double_t
RecoJet::pullPhi() const
{
  return pullPhi_;
}

Double_t
RecoJet::pullMag() const
{
  return pullMag_;
}

Int_t
RecoJet::jetId() const
{
  return jetId_;
}

Int_t
RecoJet::puId() const
{
  return puId_;
}

Int_t
RecoJet::genMatchIdx() const
{
  return genMatchIdx_;
}

Double_t
RecoJet::maxPt() const
{
  double max_Pt = this->pt();
  for(const auto & kv: pt_systematics_)
  {
    if(kv.second > max_Pt)
    {
      max_Pt = kv.second;
    }
  }
  return max_Pt;
}

bool
RecoJet::hasBtag(Btag btag) const
{
  return BtagCSVs_.count(btag);
}

bool
RecoJet::passesPUID(int puIdWP) const
{
  return this->puId() & puIdWP;
}

int
RecoJet::get_default_systematics() const
{
  return default_systematics_;
}

const Particle::LorentzVector
RecoJet::get_systematics_p4(int central_or_shift) const
{
  if(! pt_systematics_.count(central_or_shift) && ! mass_systematics_.count(central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "No such systematics available: " << central_or_shift;
  }
  return { pt_systematics_.at(central_or_shift), eta_, phi_, mass_systematics_.at(central_or_shift) };
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet)
{
  stream << static_cast<const GenJet &>(jet)                                 << ","
            " charge = "          << jet.charge()                            << ","
            " CSV = "             << jet.BtagCSV()                           << ","
            " jet ID = "          << jet.jetId()                             << ","
            " PU ID = "           << jet.puId()                              << ","
            " QGL = "             << jet.QGDiscr()                           << ","
            " bReg corr (res) = " << jet.bRegCorr() << " (" << jet.bRegRes() << "),"
            " sysunc = "          << jet.get_default_systematics()           << ","
            "\n"
            " gen. matching:";
  stream << ",\n  lepton = " << jet.genLepton();
  if(jet.genLepton())
  {
    stream << ": " << *(jet.genLepton());
  }
  stream << ",\n  hadTau = " << jet.genHadTau();
  if(jet.genHadTau())
  {
    stream << ": " << *(jet.genHadTau());
  }
  stream << ",\n  jet    = " << jet.genJet();
  if(jet.genJet())
  {
    stream << ": " << *(jet.genJet());
  }
  stream << '\n';
  return stream;
}
