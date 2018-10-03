#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK8.h" // RecoJetSelectorAK8

RecoJetSelectorAK8::RecoJetSelectorAK8(int era,
                                 int index,
                                 bool debug)
  : min_pt_(100.)
  , max_absEta_(2.4)
  , min_msoftdrop_(50.)
  , debug_(debug)
{}

void
RecoJetSelectorAK8::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelectorAK8::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelectorAK8::set_min_msoftdrop(double min_msoftdrop)
{
  min_msoftdrop_ = min_msoftdrop;
}

double
RecoJetSelectorAK8::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelectorAK8::get_max_absEta() const
{
  return max_absEta_;
}

double
RecoJetSelectorAK8::get_min_msoftdrop() const
{
  return min_msoftdrop_;
}

bool
RecoJetSelectorAK8::operator()(const RecoJetAK8 & jet) const
{
  const bool passes =
    jet.pt()     >= min_pt_     &&
    jet.absEta() <= max_absEta_ &&
    jet.msoftdrop() >= min_msoftdrop_
  ;
  if(debug_)
  {
    std::cout << "<RecoJetSelectorAK8::operator()>:\n jet: " << jet << " "
                 "(" << (passes ? "passes" : "fails") << ")\n"
    ;
  }
  return passes;
}
