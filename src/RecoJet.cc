#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

RecoJet::RecoJet(const GenJet & jet,
                 Double_t jecUncertTotal,
                 Double_t BtagCSV,
                 Double_t BtagWeight,
                 Double_t QGDiscr,
                 Int_t heppyFlavour,
                 Int_t idx)
  : RecoJetBase(jet, idx)
  , jecUncertTotal_(jecUncertTotal)
  , BtagCSV_(BtagCSV)
  , BtagWeight_(BtagWeight)
  , QGDiscr_(QGDiscr)
  , heppyFlavour_(heppyFlavour)
{}

RecoJet::~RecoJet()
{}

Double_t
RecoJet::jecUncertTotal() const
{
  return jecUncertTotal_;
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

Int_t
RecoJet::heppyFlavour() const
{
  return heppyFlavour_;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoJet & jet)
{
  stream << static_cast<const GenJet &>(jet)         << ","
            " CSV = " << jet.BtagCSV()               << ","
            " heppyFlavour = " << jet.heppyFlavour() << ",\n"
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
