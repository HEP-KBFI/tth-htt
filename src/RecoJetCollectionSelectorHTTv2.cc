#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2

RecoJetSelectorHTTv2::RecoJetSelectorHTTv2(int era,
                                           int index,
                                           bool debug)
  : min_pt_(200.)
  , max_absEta_(2.4) // reccomended to use btag on the subjets
  , subJet1_min_jetId_(0) // it is a bool, it shall be > 0 to be true
  , subJet2_min_jetId_(0) // it is a bool, it shall be > 0 to be true
  , subJet3_min_jetId_(0) // it is a bool, it shall be > 0 to be true
  , subJet1_min_pt_(30.)
  , subJet2_min_pt_(30.)
  , subJet3_min_pt_(30.)
  , debug_(debug)
{}

void
RecoJetSelectorHTTv2::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelectorHTTv2::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelectorHTTv2::set_subJet1_min_jetId(int subJet1_min_jetId)
{
  subJet1_min_jetId_ = subJet1_min_jetId;
}

void
RecoJetSelectorHTTv2::set_subJet2_min_jetId(int subJet2_min_jetId)
{
  subJet2_min_jetId_ = subJet2_min_jetId;
}

void
RecoJetSelectorHTTv2::set_subJet3_min_jetId(int subJet3_min_jetId)
{
  subJet3_min_jetId_ = subJet3_min_jetId;
}

void
RecoJetSelectorHTTv2::set_subJet1_min_pt(int subJet1_min_jetId)
{
  subJet1_min_jetId_ = subJet1_min_jetId;
}

void
RecoJetSelectorHTTv2::set_subJet2_min_pt(int subJet2_min_jetId)
{
  subJet2_min_jetId_ = subJet2_min_jetId;
}

void
RecoJetSelectorHTTv2::set_subJet3_min_pt(int subJet3_min_jetId)
{
  subJet3_min_jetId_ = subJet3_min_jetId;
}

double
RecoJetSelectorHTTv2::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelectorHTTv2::get_max_absEta() const
{
  return max_absEta_;
}

int
RecoJetSelectorHTTv2::get_subJet1_min_jetId() const
{
  return subJet1_min_jetId_;
}

int
RecoJetSelectorHTTv2::get_subJet2_min_jetId() const
{
  return subJet2_min_jetId_;
}

int
RecoJetSelectorHTTv2::get_subJet3_min_jetId() const
{
  return subJet3_min_jetId_;
}

int
RecoJetSelectorHTTv2::get_subJet1_min_pt() const
{
  return subJet1_min_pt_;
}

int
RecoJetSelectorHTTv2::get_subJet2_min_pt() const
{
  return subJet2_min_pt_;
}

int
RecoJetSelectorHTTv2::get_subJet3_min_pt() const
{
  return subJet3_min_pt_;
}

bool
RecoJetSelectorHTTv2::operator()(const RecoJetHTTv2 & jet) const
{
  const bool passes =
    jet.pt()     >= min_pt_     &&
    jet.absEta() <= max_absEta_ &&
    jet.subJet1() && jet.subJet1()->IDPassed() > subJet1_min_jetId_ && jet.subJet1()->pt() >= subJet1_min_pt_ &&
    jet.subJet2() && jet.subJet2()->IDPassed() > subJet2_min_jetId_ && jet.subJet2()->pt() >= subJet2_min_pt_ &&
    jet.subJet3() && jet.subJet3()->IDPassed() > subJet3_min_jetId_ && jet.subJet3()->pt() >= subJet3_min_pt_
  ;
  if(debug_)
  {
    std::cout << "<RecoJetSelectorHTTv2::operator()>:\n jet: " << jet << " "
                 "(" << (passes ? "passes" : "fails") << ")\n"
    ;
  }
  return passes;
}
