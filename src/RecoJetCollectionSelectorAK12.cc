#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK12.h" // RecoJetSelectorAK12

RecoJetSelectorAK12::RecoJetSelectorAK12(int era,
                                 int index,
                                 bool debug)
  : min_pt_(130.)
  , max_absEta_(2.4)
  , min_msoftdrop_(50.)
  //, min_subjet_pt_(10.)
  , debug_(debug)
{}

void
RecoJetSelectorAK12::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelectorAK12::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelectorAK12::set_min_msoftdrop(double min_msoftdrop)
{
  min_msoftdrop_ = min_msoftdrop;
}

double
RecoJetSelectorAK12::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelectorAK12::get_max_absEta() const
{
  return max_absEta_;
}

double
RecoJetSelectorAK12::get_min_msoftdrop() const
{
  return min_msoftdrop_;
}

bool
RecoJetSelectorAK12::operator()(const RecoJetAK12 & jet) const
{
  const bool passes =
    jet.pt()        >= min_pt_     &&
    jet.absEta()    <= max_absEta_  &&
    jet.msoftdrop() >= min_msoftdrop_ 
  ;
  if(debug_)
  {
    std::cout << "<RecoJetSelectorAK12::operator()>:\n jet: " << jet << " "
                 "(" << (passes ? "passes" : "fails") << ")\n"
    ;
  }
  return passes;
}
