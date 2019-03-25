#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

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
                 Int_t genJetMatchIdx,
                 Int_t idx)
  : RecoJetBase(jet, idx)
  , charge_(charge)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , QGDiscr_(QGDiscr)
  , pullEta_(pullEta)
  , pullPhi_(pullPhi)
  , pullMag_(pullMag)
  , jetId_(jetId)
  , puId_(puId)
  , genJetMatchIdx_(genJetMatchIdx)
{}

RecoJet::~RecoJet()
{}

Double_t
RecoJet::charge() const
{
  return charge_;
}

Double_t
RecoJet::BtagCSV() const
{
  return BtagCSV_;
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
RecoJet::genJetMatchIdx() const
{
  return genJetMatchIdx_;
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
