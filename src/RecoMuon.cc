#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon, RecoLepton, GenLepton

RecoMuon::RecoMuon(const RecoLepton & lepton,
                   Bool_t passesLooseIdPOG,
                   Bool_t passesMediumIdPOG,
                   Float_t segmentCompatibility)
  : RecoLepton(lepton)
  , passesLooseIdPOG_(passesLooseIdPOG)
  , passesMediumIdPOG_(passesMediumIdPOG)
  , segmentCompatibility_(segmentCompatibility)
{}

Bool_t
RecoMuon::passesLooseIdPOG() const
{
  return passesLooseIdPOG_;
}

Bool_t
RecoMuon::passesMediumIdPOG() const
{
  return passesMediumIdPOG_;
}

Float_t
RecoMuon::segmentCompatibility() const
{
  return segmentCompatibility_;
}

bool
RecoMuon::is_electron() const
{
  return false;
}

bool
RecoMuon::is_muon() const
{
  return true;
}

std::ostream &
operator<<(std::ostream & stream,
           const RecoMuon & muon)
{
  stream << static_cast<const RecoLepton &>(muon) << ",\n "
            "passesLooseIdPOG = "     << muon.passesLooseIdPOG()  << ", "
            "passesMediumIdPOG = "    << muon.passesMediumIdPOG() << ", "
            "segmentCompatibility = " << muon.segmentCompatibility() << '\n';
  return stream;
}
