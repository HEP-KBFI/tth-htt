#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorTight::RecoMuonSelectorTight(int era,
                                             int index,
                                             bool debug,
                                             bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , min_pt_(5.) // L
  , min_cone_pt_(10.) // F
  , max_absEta_(2.4) // F
  , max_dxy_(0.05) // F
  , max_dz_(0.1) // F
  , max_relIso_(0.4) // F
  , max_sip3d_(8.) // F
  , apply_looseIdPOG_(true) // F
  , apply_mediumIdPOG_(true) // T
  , max_jetBtagCSV_(get_BtagWP(era_, Btag::kDeepJet, BtagWP::kMedium)) // T
  , min_mvaTTH_(0.85) // T
{
  // L -- inherited from the preselection (loose cut)
  // F -- inherited from the fakeable selection
  // T -- additional tight cut not applied in the fakeable selection
}

bool
RecoMuonSelectorTight::operator()(const RecoMuon & muon) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n muon: " << muon << '\n';
  }

  if(muon.cone_pt() < min_cone_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS cone pT = " << muon.cone_pt() << " >= " << min_cone_pt_ << " tight cut\n";
    }
    return false;
  }
  if(muon.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT = " << muon.pt() << " >= " << min_pt_ << " tight cut\n";
    }
    return false;
  }
  if(muon.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << muon.absEta() << " <= " << max_absEta_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(muon.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) = " << std::fabs(muon.dxy()) << " <= " << max_dxy_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(muon.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) = " << std::fabs(muon.dz()) << " <= " << max_dz_ << " tight cut\n";
    }
    return false;
  }
  if(muon.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso = " << muon.relIso() << " <= " << max_relIso_ << " tight cut\n";
    }
    return false;
  }
  if(muon.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d = " << muon.sip3d() << " <= " << max_sip3d_ << " tight cut\n";
    }
    return false;
  }
  if(apply_looseIdPOG_ && ! muon.passesLooseIdPOG())
  {
    if(debug_)
    {
      std::cout << "FAILS looseIdPOG tight cut\n";
    }
    return false;
  }
  if(muon.jetBtagCSV() > max_jetBtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV " << muon.jetBtagCSV() << " <= " << max_jetBtagCSV_ << " tight cut\n";
    }
    return false;
  }
  if(apply_mediumIdPOG_ && ! muon.passesMediumIdPOG())
  {
    if(debug_)
    {
      std::cout << "FAILS mediumIdPOG tight cut\n";
    }
    return false;
  }
  if(muon.mvaRawTTH() < min_mvaTTH_)
  {
    if(debug_)
    {
      std::cout << "FAILS mvaTTH = " << muon.mvaRawTTH() << " >= " << min_mvaTTH_ << " tight cut\n";
    }
    return false;
  }

  // muon passes all cuts
  if(set_selection_flags_)
  {
    muon.set_isTight();
  }
  return true;
}

void
RecoMuonSelectorTight::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoMuonSelectorTight::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void RecoMuonSelectorTight::set_min_mvaTTH(double min_mvaTTH)
{
  std::cout << "setting cut on prompt-lepton MVA for tight muons: " << min_mvaTTH << '\n';
  min_mvaTTH_ = min_mvaTTH;
}

double
RecoMuonSelectorTight::get_min_pt() const
{
  return min_pt_;
}

double
RecoMuonSelectorTight::get_max_absEta() const
{
  return max_absEta_;
}
 
double 
RecoMuonSelectorTight::get_min_mvaTTH() const
{
  return min_mvaTTH_;
}

void
RecoMuonSelectorTight::set_selection_flags(bool selection_flags)
{
  set_selection_flags_ = selection_flags;
}

RecoMuonCollectionSelectorTight::RecoMuonCollectionSelectorTight(int era,
                                                                 int index,
                                                                 bool debug,
                                                                 bool set_selection_flags)
  : ParticleCollectionSelector<RecoMuon, RecoMuonSelectorTight>(era, index, debug)
{
  selector_.set_selection_flags(set_selection_flags);
}
