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
                 Double_t pullEta,
                 Double_t pullPhi,
                 Double_t pullMag,
                 Int_t jetId,
                 Int_t puId,
                 Int_t genMatchIdx,
                 Int_t idx)
  : RecoJetBase(jet, idx)
  , jetCharge_(charge)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , QGDiscr_(QGDiscr)
  , pullEta_(pullEta)
  , pullPhi_(pullPhi)
  , pullMag_(pullMag)
  , jetId_(jetId)
  , puId_(puId)
  , genMatchIdx_(genMatchIdx)
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
RecoJet::QGDiscr() const
{
  return QGDiscr_;
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

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet)
{
  stream << static_cast<const GenJet &>(jet)         << ","
            " charge = " << jet.charge()             << ","
            " CSV = "    << jet.BtagCSV()            << ","
            " jet ID = " << jet.jetId()              << ","
            " PU ID = "  << jet.puId()               << ","
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
