#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetSelector

RecoJetSelector::RecoJetSelector(int era,
                                 int index,
                                 bool debug)
  : min_pt_(25.)
  , max_absEta_(2.4)
  , min_jetId_(3) // 3 means tight (sum of loose bit + 2 * tight bit)
  , debug_(debug)
{}

void
RecoJetSelector::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelector::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelector::set_min_jetId(int min_jetId)
{
  min_jetId_ = min_jetId;
}

double
RecoJetSelector::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelector::get_max_absEta() const
{
  return max_absEta_;
}

int
RecoJetSelector::get_min_jetId() const
{
  return min_jetId_;
}

bool
RecoJetSelector::operator()(const RecoJet & jet) const
{
  const bool passes =
    jet.pt()     >= min_pt_     &&
    jet.absEta() <= max_absEta_ &&
    jet.jetId()  >= min_jetId_
  ;
  if(debug_)
  {
    std::cout << "<RecoJetSelector::operator()>:\n jet: " << jet << " "
                 "(" << (passes ? "passes" : "fails") << ")\n"
    ;
  }
  return passes;
}
