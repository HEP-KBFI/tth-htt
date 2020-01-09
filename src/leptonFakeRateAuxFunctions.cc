#include "tthAnalysis/HiggsToTauTau/interface/leptonFakeRateAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/GenPhoton.h" // GenPhoton
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin(), getPtBin()
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonFakeRate.h" // EvtHistManager_LeptonFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // METSyst::
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // as_integer

#include <Math/Vector3D.h> // ROOT::Math::XYZVector

double
comp_mT(const RecoLepton & lepton,
        double met_pt,
        double met_phi)
{
  return std::sqrt(2. * lepton.pt() * met_pt * (1. - std::cos(lepton.phi() - met_phi)));
}

double
comp_mT_fix(const RecoLepton & lepton,
            double met_pt,
            double met_phi)
{
  const double pt_fix = 35.;
  return std::sqrt(2. * pt_fix * met_pt * (1. - std::cos(lepton.phi() - met_phi)));
}

numerator_and_denominatorHistManagers::numerator_and_denominatorHistManagers(const std::string & process,
                                                                             bool isMC,
                                                                             const std::string & era_string,
                                                                             const std::string & central_or_shift,
                                                                             const std::string & dir,
                                                                             int lepton_type,
                                                                             double minAbsEta,
                                                                             double maxAbsEta,
                                                                             double minPt,
                                                                             double maxPt,
                                                                             const std::string & subdir_suffix)
  : process_(process)
  , isMC_(isMC)
  , era_string_(era_string)
  , central_or_shift_(central_or_shift)
  , lepton_type_(lepton_type)
  , minAbsEta_(minAbsEta)
  , maxAbsEta_(maxAbsEta)
  , minPt_(minPt)
  , maxPt_(maxPt)
  , isInclusive_(minAbsEta_ == maxAbsEta_ && minPt_ == maxPt_)
  , electronHistManager_(nullptr)
  , electronHistManager_genHadTau_(nullptr)
  , electronHistManager_genLepton_(nullptr)
  , electronHistManager_genHadTauOrLepton_(nullptr)
  , electronHistManager_genJet_(nullptr)
  , electronHistManager_genPhoton_(nullptr)
  , muonHistManager_(nullptr)
  , muonHistManager_genHadTau_(nullptr)
  , muonHistManager_genLepton_(nullptr)
  , muonHistManager_genHadTauOrLepton_(nullptr)
  , muonHistManager_genJet_(nullptr)
  , muonHistManager_genPhoton_(nullptr)
  , evtHistManager_LeptonFakeRate_(nullptr)
  , evtHistManager_LeptonFakeRate_genHadTau_(nullptr)
  , evtHistManager_LeptonFakeRate_genLepton_(nullptr)
  , evtHistManager_LeptonFakeRate_genHadTauOrLepton_(nullptr)
  , evtHistManager_LeptonFakeRate_genJet_(nullptr)
  , evtHistManager_LeptonFakeRate_genPhoton_(nullptr)
{
  if(isInclusive_)
  {
    // inclusive event selection
    subdir_ = Form("%s/incl", dir.data());
  }
  else
  {
    const std::string etaBin = getEtaBin(minAbsEta_, maxAbsEta_);
    const std::string PtBin  = getPtBin(minPt_, maxPt_);
    subdir_ = Form("%s/%s/%s", dir.data(), etaBin.data(), PtBin.data());
  }
  if(! subdir_suffix.empty())
  {
    subdir_ += Form("_%s", subdir_suffix.data());
  }

  switch(lepton_type_)
  {
    case kElectron: label_ = "e";  break;
    case kMuon:     label_ = "mu"; break;
    default:         assert(0);
  }
  if(! subdir_suffix.empty())
  {
    label_ += Form(" (%s)", subdir_suffix.data());
  }
  label_ += Form(", %1.0f < pT < %1.0f && %1.2f < |eta| < %1.2f", minPt, maxPt, minAbsEta, maxAbsEta);
}

numerator_and_denominatorHistManagers::~numerator_and_denominatorHistManagers()
{
  delete electronHistManager_;
  delete electronHistManager_genHadTau_;
  delete electronHistManager_genLepton_;
  delete electronHistManager_genHadTauOrLepton_;
  delete electronHistManager_genJet_;
  delete electronHistManager_genPhoton_;
  delete muonHistManager_;
  delete muonHistManager_genHadTau_;
  delete muonHistManager_genLepton_;
  delete muonHistManager_genHadTauOrLepton_;
  delete muonHistManager_genJet_;
  delete muonHistManager_genPhoton_;
  delete evtHistManager_LeptonFakeRate_;
  delete evtHistManager_LeptonFakeRate_genHadTau_;
  delete evtHistManager_LeptonFakeRate_genLepton_;
  delete evtHistManager_LeptonFakeRate_genHadTauOrLepton_;
  delete evtHistManager_LeptonFakeRate_genJet_;
  delete evtHistManager_LeptonFakeRate_genPhoton_;
}

std::string
numerator_and_denominatorHistManagers::getLabel() const
{
  return label_;
}

void
numerator_and_denominatorHistManagers::bookHistograms(TFileDirectory & dir)
{
  const std::string process_and_genMatchedHadTau         = process_ + "t";
  const std::string process_and_genMatchedLepton         = process_ + "l";
  const std::string process_and_genMatchedHadTauOrLepton = process_ + "l_plus_t";
  const std::string process_and_genMatchedJet            = process_ + "j";
  const std::string process_and_genMatchedPhoton         = process_ + "g";

  const auto mkCfg = [this](const std::string & process) -> edm::ParameterSet
  {
    return makeHistManager_cfg(process, subdir_, era_string_, central_or_shift_, "minimalHistograms");
  };

  if(lepton_type_ == kElectron)
  {
    electronHistManager_ = new ElectronHistManager(mkCfg(process_));
    electronHistManager_->bookHistograms(dir);
    if(isMC_)
    {
      electronHistManager_genHadTau_ = new ElectronHistManager(mkCfg(process_and_genMatchedHadTau));
      electronHistManager_genHadTau_->bookHistograms(dir);

      electronHistManager_genLepton_ = new ElectronHistManager(mkCfg(process_and_genMatchedLepton));
      electronHistManager_genLepton_->bookHistograms(dir);

      electronHistManager_genHadTauOrLepton_ = new ElectronHistManager(mkCfg(process_and_genMatchedHadTauOrLepton));
      electronHistManager_genHadTauOrLepton_->bookHistograms(dir);

      electronHistManager_genJet_ = new ElectronHistManager(mkCfg(process_and_genMatchedJet));
      electronHistManager_genJet_->bookHistograms(dir);

      electronHistManager_genPhoton_ = new ElectronHistManager(mkCfg(process_and_genMatchedPhoton));
      electronHistManager_genPhoton_->bookHistograms(dir);
    }
  }
  else if(lepton_type_ == kMuon)
  {
    muonHistManager_ = new MuonHistManager(mkCfg(process_));
    muonHistManager_->bookHistograms(dir);
    if(isMC_)
    {
      muonHistManager_genHadTau_ = new MuonHistManager(mkCfg(process_and_genMatchedHadTau));
      muonHistManager_genHadTau_->bookHistograms(dir);

      muonHistManager_genLepton_ = new MuonHistManager(mkCfg(process_and_genMatchedLepton));
      muonHistManager_genLepton_->bookHistograms(dir);

      muonHistManager_genHadTauOrLepton_ = new MuonHistManager(mkCfg(process_and_genMatchedHadTauOrLepton));
      muonHistManager_genHadTauOrLepton_->bookHistograms(dir);

      muonHistManager_genJet_ = new MuonHistManager(mkCfg(process_and_genMatchedJet));
      muonHistManager_genJet_->bookHistograms(dir);

      muonHistManager_genPhoton_ = new MuonHistManager(mkCfg(process_and_genMatchedPhoton));
      muonHistManager_genPhoton_->bookHistograms(dir);
    }
  }
  else
  {
    assert(0);
  }

  evtHistManager_LeptonFakeRate_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_));
  evtHistManager_LeptonFakeRate_->bookHistograms(dir);

  if(isMC_)
  {
    evtHistManager_LeptonFakeRate_genHadTau_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedHadTau));
    evtHistManager_LeptonFakeRate_genHadTau_->bookHistograms(dir);

    evtHistManager_LeptonFakeRate_genLepton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedLepton));
    evtHistManager_LeptonFakeRate_genLepton_->bookHistograms(dir);

    evtHistManager_LeptonFakeRate_genHadTauOrLepton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedHadTauOrLepton));
    evtHistManager_LeptonFakeRate_genHadTauOrLepton_->bookHistograms(dir);

    evtHistManager_LeptonFakeRate_genJet_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedJet));
    evtHistManager_LeptonFakeRate_genJet_->bookHistograms(dir);

    evtHistManager_LeptonFakeRate_genPhoton_ = new EvtHistManager_LeptonFakeRate(mkCfg(process_and_genMatchedPhoton));
    evtHistManager_LeptonFakeRate_genPhoton_->bookHistograms(dir);
  }
}

void
numerator_and_denominatorHistManagers::fillHistograms(const RecoLepton & lepton,
                                                      double met,
                                                      double mT,
                                                      double mT_fix,
                                                      double evtWeight,
                                                      cutFlowTableType * cutFlowTable)
{
  const bool performFill = isInclusive_ || (
    lepton.absEta() >= minAbsEta_ && lepton.absEta() < maxAbsEta_  &&
    lepton.cone_pt() >= minPt_    && lepton.cone_pt() < maxPt_
  );

  if(performFill)
  {
    if(lepton_type_ == kElectron)
    {
      const RecoElectron * const electron_ptr = dynamic_cast<const RecoElectron *>(&lepton);
      assert(electron_ptr);
      const RecoElectron & electron = *electron_ptr;

      electronHistManager_->fillHistograms(electron, evtWeight);
      if(isMC_)
      {
        if(electron.genLepton())
        {
          electronHistManager_genLepton_->fillHistograms(electron, evtWeight);
          electronHistManager_genHadTauOrLepton_->fillHistograms(electron, evtWeight);
        }
        else if(electron.genHadTau())
        {
          electronHistManager_genHadTau_->fillHistograms(electron, evtWeight);
          electronHistManager_genHadTauOrLepton_->fillHistograms(electron, evtWeight);
        }
        else if(electron.genPhoton())
        {
          electronHistManager_genPhoton_->fillHistograms(electron, evtWeight);
        }
        else
        {
          electronHistManager_genJet_->fillHistograms(electron, evtWeight);
        }
      }
    }
    else if(lepton_type_ == kMuon)
    {
      const RecoMuon * const muon_ptr = dynamic_cast<const RecoMuon *>(&lepton);
      assert(muon_ptr);
      const RecoMuon & muon = *muon_ptr;

      muonHistManager_->fillHistograms(muon, evtWeight);
      if(isMC_)
      {
        if(muon.genLepton())
        {
          muonHistManager_genLepton_->fillHistograms(muon, evtWeight);
          muonHistManager_genHadTauOrLepton_->fillHistograms(muon, evtWeight);
        }
        else if(muon.genHadTau())
        {
          muonHistManager_genHadTau_->fillHistograms(muon, evtWeight);
          muonHistManager_genHadTauOrLepton_->fillHistograms(muon, evtWeight);
        }
        else
        {
          muonHistManager_genJet_->fillHistograms(muon, evtWeight);
        }
      }
    }
    else
    {
      assert(0);
    }

    evtHistManager_LeptonFakeRate_->fillHistograms(met, mT, mT_fix, evtWeight);
    if(isMC_)
    {
      if(lepton.genLepton())
      {
        evtHistManager_LeptonFakeRate_genLepton_        ->fillHistograms(met, mT, mT_fix, evtWeight);
        evtHistManager_LeptonFakeRate_genHadTauOrLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
      }
      else if(lepton.genHadTau())
      {
        evtHistManager_LeptonFakeRate_genHadTau_        ->fillHistograms(met, mT, mT_fix, evtWeight);
        evtHistManager_LeptonFakeRate_genHadTauOrLepton_->fillHistograms(met, mT, mT_fix, evtWeight);
      }
      else if(lepton.genPhoton())
      {
        evtHistManager_LeptonFakeRate_genPhoton_->fillHistograms(met, mT, mT_fix, evtWeight);
      }
      else
      {
        evtHistManager_LeptonFakeRate_genJet_->fillHistograms(met, mT, mT_fix, evtWeight);
      }
    }

    if(cutFlowTable)
    {
      cutFlowTable->update(label_, evtWeight);
    }
  }
}

void
fillHistograms(std::vector<numerator_and_denominatorHistManagers *> & histograms,
               const RecoLepton & lepton,
               double met_pt,
               double mT,
               double mT_fix,
               double evtWeight_LepJetPair,
               cutFlowTableType * cutFlowTable)
{
  for(numerator_and_denominatorHistManagers * histogram: histograms)
  {
    histogram->fillHistograms(lepton, met_pt, mT, mT_fix, evtWeight_LepJetPair, cutFlowTable);
  }
}

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       const std::string & cut)
{
  // do not increase event counts in cut-flow table, just register cut
  cutFlowTable.update(cut, -1.);
}

void
initializeCutFlowTable(cutFlowTableType & cutFlowTable,
                       std::vector<numerator_and_denominatorHistManagers *> & histograms)
{
  for(const numerator_and_denominatorHistManagers * const histogram: histograms)
  {
    initializeCutFlowTable(cutFlowTable, histogram->getLabel());
  }
}

RecoMEt
METSystComp_LeptonFakeRate(const RecoLepton * lepton,
                           const GenMEt & genmet,
                           const RecoMEt & met,
                           const double & scale,
                           METSyst central_or_shift,
                           bool debug)
{
  if(central_or_shift == METSyst::central)
  {
    // don't even bother spending time on computing modified MET
    return met;
  }

  if(scale <= 0. || scale >= 1.0)
  {
    throw cmsException(__func__, __LINE__) << "Scale should always lie in the interval (0.,1.)";
  }
  const double reco_lepton_px = lepton->pt() * std::cos(lepton->phi());
  const double reco_lepton_py = lepton->pt() * std::sin(lepton->phi());
  const double reco_met_x = met.pt() * std::cos(met.phi());
  const double reco_met_y = met.pt() * std::sin(met.phi());
  const double gen_met_x = genmet.pt() * std::cos(genmet.phi());
  const double gen_met_y = genmet.pt() * std::sin(genmet.phi());

  double gen_lepton_px = 0.;
  double gen_lepton_py = 0.;
  if(lepton->genLepton())
  {
    // check for existence of gen-matched lepton
    gen_lepton_px = lepton->genLepton()->pt() * std::cos(lepton->genLepton()->phi());
    gen_lepton_py = lepton->genLepton()->pt() * std::sin(lepton->genLepton()->phi());
  }
  else
  {
    // in case there is no gen-matched lepton use reco-lepton instead => Had. Recoil (RECO) = Had. Recoil (GEN)
    gen_lepton_px = reco_lepton_px;
    gen_lepton_py = reco_lepton_py;
  }

  if(debug)
  {
    const double reco_lepton_pt = std::sqrt(reco_lepton_px * reco_lepton_px + reco_lepton_py * reco_lepton_py);
    const double gen_lepton_pt  = std::sqrt(gen_lepton_px  * gen_lepton_px  + gen_lepton_py  * gen_lepton_py);
    const double reco_met_pt = std::sqrt(reco_met_x * reco_met_x + reco_met_y * reco_met_y);
    const double gen_met_pt  = std::sqrt(gen_met_x  * gen_met_x  + gen_met_y  * gen_met_y);
    std::cout
      << "reco_lepton_px = " << reco_lepton_px << " "
         "reco_lepton_py = " << reco_lepton_py << " "
         "reco_lepton_pt = " << reco_lepton_pt << " "
         "lepton->pt() = "   << lepton->pt()   << " "
         "lepton->phi() = "  << lepton->phi()  << "\n"
         "reco_met_x = "     << reco_met_x     << " "
         "reco_met_y = "     << reco_met_y     << " "
         "reco_met_pt = "    << reco_met_pt    << " "
         "met.pt() = "       << met.pt()       << " "
         "met.phi() = "      << met.phi()      << "\n"
         "gen_met_x = "      << gen_met_x      << " "
         "gen_met_y = "      << gen_met_y      << " "
         "gen_met_pt = "     << gen_met_pt     << " "
         "genmet.pt() = "    << genmet.pt()    << " "
         "genmet.phi() = "   << genmet.phi()   << "\n"
         "gen_lepton_px = "  << gen_lepton_px  << " "
         "gen_lepton_py = "  << gen_lepton_py  << " "
         "gen_lepton_pt = "  << gen_lepton_pt  << '\n'
    ;
    if(lepton->genLepton())
    {
      std::cout
        << " lepton->genLepton()->pt() = "  << lepton->genLepton()->pt()
        << " lepton->genLepton()->phi() = " << lepton->genLepton()->phi()
        << '\n'
      ;
    }
  }

  const ROOT::Math::XYZVector reco_lepton_vec(reco_lepton_px, reco_lepton_py, 0.);
  const ROOT::Math::XYZVector gen_lepton_vec (gen_lepton_px,  gen_lepton_py,  0.);
  const ROOT::Math::XYZVector reco_met_vec(reco_met_x, reco_met_y, 0.);
  const ROOT::Math::XYZVector gen_met_vec (gen_met_x,  gen_met_y,  0.);
  if(debug)
  {
    std::cout
      << " reco_lepton_vec.Rho() = " << reco_lepton_vec.Rho() << " reco_lepton_vec.Phi() = " << reco_lepton_vec.Phi() << "\n"
         " reco_met_vec.Rho()    = " << reco_met_vec.Rho()    << " reco_met_vec.Phi()    = " << reco_met_vec.Phi()    << "\n"
         " gen_met_vec.Rho()     = " << gen_met_vec.Rho()     << " gen_met_vec.Phi()     = " << gen_met_vec.Phi()     << "\n"
         " gen_lepton_vec.Rho()  = " << gen_lepton_vec.Rho()  << " gen_lepton_vec.Phi()  = " << gen_lepton_vec.Phi()  << '\n'
    ;
  }

  // Computing Reco Hadronic Recoil and its systematic shifts
  const ROOT::Math::XYZVector reco_had_recoil_vec_nom       = (-1.0) * (reco_met_vec + reco_lepton_vec);
  const ROOT::Math::XYZVector reco_had_recoil_vec_ScaleUp   = (1.0 + scale) * (reco_had_recoil_vec_nom);
  const ROOT::Math::XYZVector reco_had_recoil_vec_ScaleDown = (1.0 - scale) * (reco_had_recoil_vec_nom);
  if(debug)
  {
    std::cout
      << " reco_had_recoil_vec_nom.Rho()       = " << reco_had_recoil_vec_nom.Rho()
      << " reco_had_recoil_vec_nom.Phi()       = " << reco_had_recoil_vec_nom.Phi()       << "\n"
         " reco_had_recoil_vec_ScaleUp.Rho()   = " << reco_had_recoil_vec_ScaleUp.Rho()
      << " reco_had_recoil_vec_ScaleUp.Phi()   = " << reco_had_recoil_vec_ScaleUp.Phi()   << "\n"
         " reco_had_recoil_vec_ScaleDown.Rho() = " << reco_had_recoil_vec_ScaleDown.Rho()
      << " reco_had_recoil_vec_ScaleDown.Phi() = " << reco_had_recoil_vec_ScaleDown.Phi() << '\n'
    ;
  }

  // Computing Gen Hadronic Recoil
  const ROOT::Math::XYZVector gen_had_recoil_vec_nom  = (-1.0) * (gen_met_vec + gen_lepton_vec);
  if(debug)
  {
    std::cout
      << " gen_had_recoil_vec_nom.Rho() = " << gen_had_recoil_vec_nom.Rho()
      << " gen_had_recoil_vec_nom.Phi() = " << gen_had_recoil_vec_nom.Phi()
      << '\n'
    ;
  }

  ROOT::Math::XYZVector result;
  if(central_or_shift == METSyst::respUp)
  {
    // Computing MET Response Systematic shift Up
    result = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ScaleUp);
  }
  else if(central_or_shift == METSyst::respDown)
  {
    // Computing MET Response Systematic shift Down
    result = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ScaleDown);
  }
  else if(central_or_shift == METSyst::resolUp)
  {
    // Computing Systematic shifts in Reco Had Recoil Resolution Up
    const ROOT::Math::XYZVector reco_had_recoil_vec_ResolUp = reco_had_recoil_vec_nom  + (scale * (reco_had_recoil_vec_nom - gen_had_recoil_vec_nom));
    if(debug)
    {
      std::cout
        << " reco_had_recoil_vec_ResolUp.Rho() = " << reco_had_recoil_vec_ResolUp.Rho()
        << " reco_had_recoil_vec_ResolUp.Phi() = " << reco_had_recoil_vec_ResolUp.Phi()
        << '\n'
      ;
    }

    // Computing MET Resolution Systematic shifts Up
    result = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ResolUp);
  }
  else if(central_or_shift == METSyst::resolDown)
  {
    // Computing Systematic shifts in Reco Had Recoil Resolution Down
    const ROOT::Math::XYZVector reco_had_recoil_vec_ResolDown = reco_had_recoil_vec_nom  - (scale * (reco_had_recoil_vec_nom - gen_had_recoil_vec_nom));
    if(debug)
    {
      std::cout
        << " reco_had_recoil_vec_ResolDown.Rho() = " << reco_had_recoil_vec_ResolDown.Rho()
        << " reco_had_recoil_vec_ResolDown.Phi() = " << reco_had_recoil_vec_ResolDown.Phi()
        << '\n'
      ;
    }

    // Computing MET Resolution Systematic shifts Down
    result = (-1.) * (reco_lepton_vec + reco_had_recoil_vec_ResolDown);
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Invalid choice of systematics: " << as_integer(central_or_shift);
  }
  if(debug)
  {
    std::cout
      << "METSyst = "      << as_integer(central_or_shift) << " "
         "result.Rho() = " << result.Rho()                 << " "
         "result.Phi() = " << result.Phi()                 << '\n'
    ;
  }

  return RecoMEt(result.Rho(), result.Phi(), 0., 0., 0.);
}
