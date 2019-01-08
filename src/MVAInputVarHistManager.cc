#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

MVAInputVarHistManager::MVAInputVarHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  binningOptions_["avg_dr_jet"]                 = new binningOptionType("avg_dr_jet",                 30,  0.,    5.);
  binningOptions_["res-HTT_2016"]               = new binningOptionType("res-HTT_2016",               30,  0.,    1.);
  binningOptions_["avr_dr_lep_tau"]             = new binningOptionType("avr_dr_lep_tau",             30,  0.,    5.);
  binningOptions_["max_dr_lep_tau"]             = new binningOptionType("max_dr_lep_tau",             30,  0.,    5.);
  binningOptions_["is_OS"]                      = new binningOptionType("is_OS",                       2,  0.,    2.);
  binningOptions_["dr_lep_tau_os"]              = new binningOptionType("dr_lep_tau_os",              50,  0.,    5.);
  binningOptions_["dr_lep_tau_ss"]              = new binningOptionType("dr_lep_tau_ss",              50,  0.,    5.);
  binningOptions_["dr_lep1_tau"]                = new binningOptionType("dr_lep1_tau",                50,  0.,    5.);
  binningOptions_["dr_lep1_tau1"]               = new binningOptionType("dr_lep1_tau1",               50,  0.,    5.);
  binningOptions_["dr_lep1_tau2"]               = new binningOptionType("dr_lep1_tau2",               50,  0.,    5.);
  binningOptions_["dr_lep2_tau"]                = new binningOptionType("dr_lep2_tau",                50,  0.,    5.);
  binningOptions_["dr_lep2_tau1"]               = new binningOptionType("dr_lep2_tau1",               50,  0.,    5.);
  binningOptions_["dr_lep2_tau2"]               = new binningOptionType("dr_lep2_tau2",               50,  0.,    5.);
  binningOptions_["dr_lep3_tau"]                = new binningOptionType("dr_lep3_tau",                50,  0.,    5.);
  binningOptions_["dr_lep1_tau_os"]             = new binningOptionType("dr_lep1_tau_os",             50,  0.,    5.);
  binningOptions_["dr_lep2_tau_ss"]             = new binningOptionType("dr_lep2_tau_ss",             50,  0.,    5.);
  binningOptions_["dr_leps"]                    = new binningOptionType("dr_leps",                    50,  0.,    5.);
  binningOptions_["dr_tau_lep"]                 = new binningOptionType("dr_tau_lep",                 50,  0.,    5.);
  binningOptions_["dr_taus"]                    = new binningOptionType("dr_taus",                    50,  0.,    5.);
  binningOptions_["hadTauPairCharge"]           = new binningOptionType("hadTauPairCharge",            5, -2.5,  +2.5);
  binningOptions_["ht"]                         = new binningOptionType("ht",                         40,  0.,  400.);
  binningOptions_["htmiss"]                     = new binningOptionType("htmiss",                     40,  0.,  200.);
  binningOptions_["TMath::Min(htmiss,500)"]     = new binningOptionType("htmiss",                     40,  0.,  200.);
  binningOptions_["jet_deltaRavg"]              = new binningOptionType("jet_deltaRavg",              50,  0.,    5.);
  binningOptions_["jet_deltaRmax"]              = new binningOptionType("jet_deltaRmax",              75,  0.,    7.5);
  binningOptions_["lep_pt"]                     = new binningOptionType("lep_pt",                     40,  0.,  200.);
  binningOptions_["lep_tth_mva"]                = new binningOptionType("lep_tth_mva",                40, -1.,   +1.);
  binningOptions_["lep1_abs_eta"]               = new binningOptionType("lep1_abs_eta",               50, -2.5,  +2.5);
  binningOptions_["HadTop_eta"]                 = new binningOptionType("HadTop_eta",                 50, 0.,  +2.5);
  binningOptions_["lep1_charge*tau_charge"]     = new binningOptionType("lep1_charge*tau_charge",      3, -1.5,  +1.5);
  binningOptions_["lep1_conePt"]                = new binningOptionType("lep1_conePt",                40,  0.,  200.);
  binningOptions_["lep1_pt"]                    = new binningOptionType("lep1_pt",                    40,  0.,  200.);
  binningOptions_["lep1_tth_mva"]               = new binningOptionType("lep1_tth_mva",               40, -1.,   +1.);
  binningOptions_["lep2_abs_eta"]               = new binningOptionType("lep2_abs_eta",               50, -2.5,  +2.5);
  binningOptions_["lep2_conePt"]                = new binningOptionType("lep2_conePt",                40,  0.,  200.);
  binningOptions_["lep2_pt"]                    = new binningOptionType("lep2_pt",                    40,  0.,  200.);
  binningOptions_["lep2_tth_mva"]               = new binningOptionType("lep2_tth_mva",               40, -1.,   +1.);
  binningOptions_["lep3_abs_eta"]               = new binningOptionType("lep3_abs_eta",               50, -2.5,  +2.5);
  binningOptions_["lep3_conePt"]                = new binningOptionType("lep3_conePt",                40,  0.,  200.);
  binningOptions_["lep3_pt"]                    = new binningOptionType("lep3_pt",                    40,  0.,  200.);
  binningOptions_["lep3_tth_mva"]               = new binningOptionType("lep3_tth_mva",               40, -1.,   +1.);
  binningOptions_["LepGood_conePt[iF_Recl[0]]"] = new binningOptionType("LepGood_conePt[iF_Recl[0]]", 40,  0.,  200.);
  binningOptions_["LepGood_conePt[iF_Recl[1]]"] = new binningOptionType("LepGood_conePt[iF_Recl[1]]", 40,  0.,  200.);
  binningOptions_["LepGood_conePt[iF_Recl[2]]"] = new binningOptionType("LepGood_conePt[iF_Recl[2]]", 40,  0.,  200.);
  binningOptions_["leptonPairCharge"]           = new binningOptionType("leptonPairCharge",            5, -2.5,  +2.5);
  binningOptions_["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = new binningOptionType("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", 50, -2.5, +2.5);
  binningOptions_["tau2_eta"]                   = new binningOptionType("tau2_eta",                   50, -2.5, +2.5);
  binningOptions_["max_lep_eta"]                = new binningOptionType("max_lep_eta",                50, -2.5,  +2.5);
  binningOptions_["memOutput_LR"]               = new binningOptionType("memOutput_LR",               20,  0.,    1.);
  binningOptions_["memOutput_ttZ_LR"]           = new binningOptionType("memOutput_ttZ_LR",           20,  0.,    1.);
  binningOptions_["memOutput_tt_LR"]            = new binningOptionType("memOutput_tt_LR",            20,  0.,    1.);
  binningOptions_["mhtJet25_Recl"]              = new binningOptionType("mhtJet25_Recl",              40,  0.,  400.);
  binningOptions_["min(met_pt,400)"]            = new binningOptionType("min(met_pt,400)",            40,  0.,  200.);
  binningOptions_["mindr_lep_jet"]              = new binningOptionType("mindr_lep_jet",              50,  0.,    5.);
  binningOptions_["mindr_lep1_jet"]             = new binningOptionType("mindr_lep1_jet",             50,  0.,    5.);
  binningOptions_["mindr_lep2_jet"]             = new binningOptionType("mindr_lep2_jet",             50,  0.,    5.);
  binningOptions_["mindr_lep3_jet"]             = new binningOptionType("mindr_lep3_jet",             50,  0.,    5.);
  binningOptions_["mindr_tau_jet"]              = new binningOptionType("mindr_tau_jet",              50,  0.,    5.);
  binningOptions_["mindr_tau1_jet"]             = new binningOptionType("mindr_tau1_jet",             50,  0.,    5.);
  binningOptions_["mindr_tau2_jet"]             = new binningOptionType("mindr_tau2_jet",             50,  0.,    5.);
  binningOptions_["mT_lep"]                     = new binningOptionType("mT_lep",                     40,  0.,  200.);
  binningOptions_["mT_lep1"]                    = new binningOptionType("mT_lep1",                    40,  0.,  200.);
  binningOptions_["mT_lep2"]                    = new binningOptionType("mT_lep2",                    40,  0.,  200.);
  binningOptions_["mT_lep3"]                    = new binningOptionType("mT_lep3",                    40,  0.,  200.);
  binningOptions_["MT_met_lep1"]                = new binningOptionType("MT_met_lep1",                40,  0.,  200.);
  binningOptions_["MT_met_lep2"]                = new binningOptionType("MT_met_lep2",                40,  0.,  200.);
  binningOptions_["mT_tau1"]                    = new binningOptionType("mT_tau1",                    40,  0.,  200.);
  binningOptions_["mT_tau2"]                    = new binningOptionType("mT_tau2",                    40,  0.,  200.);
  binningOptions_["mbb_loose"]                  = new binningOptionType("mbb_loose",                  20,  0.,  200.);
  binningOptions_["mbb"]                        = new binningOptionType("mbb_loose",                  20,  0.,  200.);
  binningOptions_["mTauTau"]                    = new binningOptionType("mTauTau",                    20,  0.,  200.);
  binningOptions_["mTauTauVis"]                 = new binningOptionType("mTauTauVis",                 20,  0.,  200.);
  binningOptions_["mTauTauVis1"]                = new binningOptionType("mTauTauVis1",                20,  0.,  200.);
  binningOptions_["mTauTauVis2"]                = new binningOptionType("mTauTauVis2",                20,  0.,  200.);
  binningOptions_["nJet"]                       = new binningOptionType("nJet",                       20, -0.5, +19.5);
  binningOptions_["nJet25_Recl"]                = new binningOptionType("nJet25_Recl",                20, -0.5, +19.5);
  binningOptions_["njets_inclusive"]            = new binningOptionType("njets_inclusive",            20, -0.5, +19.5);
  binningOptions_["nBJetLoose"]                 = new binningOptionType("nBJetLoose",                 10, -0.5,  +9.5);
  binningOptions_["nBJetMedium"]                = new binningOptionType("nBJetMedium",                10, -0.5,  +9.5);
  binningOptions_["ntags_loose"]                = new binningOptionType("ntags_loose",                10, -0.5,  +9.5);
  binningOptions_["ptmiss"]                     = new binningOptionType("ptmiss",                     40,  0.,  200.);
  binningOptions_["lep_conePt"]                 = new binningOptionType("lep_conePt",                 40,  0.,  200.);
  binningOptions_["dr_lep_tau_lead"]            = new binningOptionType("dr_lep_tau_lead",            50,  0.,    5.);
  binningOptions_["costS_tau"]                  = new binningOptionType("costS_tau",                  30, 0.,   +1.);
  binningOptions_["cosThetaS_hadTau"]           = new binningOptionType("cosThetaS_hadTau",           30, 0.,   +1.);
  binningOptions_["HTT"]                        = new binningOptionType("HTT",                        50, 0.,   +1.);
  binningOptions_["HadTop_pt"]                  = new binningOptionType("HadTop_pt",                  30,  0.,  500.);
  binningOptions_["TMath::Min(ptmiss,500)"]     = new binningOptionType("ptmiss",                     20,  0.,  200.);
  binningOptions_["tau_abs_eta"]                = new binningOptionType("tau_abs_eta",                50, -2.5,  +2.5);
  binningOptions_["tau_pt"]                     = new binningOptionType("tau_pt",                     40,  0.,  200.);
  binningOptions_["tau1_pt"]                    = new binningOptionType("tau1_pt",                    40,  0.,  200.);
  binningOptions_["tau2_pt"]                    = new binningOptionType("tau2_pt",                    40,  0.,  200.);
  binningOptions_["tau_eta"]                    = new binningOptionType("tau_eta",                    50, -2.5,  +2.5);
  binningOptions_["min_lep_eta"]                = new binningOptionType("min_lep_eta",                50, -2.5,  +2.5);
  binningOptions_["tt_deltaR"]                  = new binningOptionType("tt_deltaR",                  50,  0.,    5.);
  binningOptions_["tt_sumpt"]                   = new binningOptionType("tt_sumpt",                   40,  0.,  200.);
  binningOptions_["tt_visiblemass"]             = new binningOptionType("tt_visiblemass",             40,  0.,  200.);
  binningOptions_["TMath::Abs(lep_eta)"]        = new binningOptionType("lep_absEta",                 50,  0.,   +2.5);
  binningOptions_["TMath::Abs(lep1_eta)"]       = new binningOptionType("lep1_absEta",                50,  0.,   +2.5);
  binningOptions_["TMath::Abs(lep2_eta)"]       = new binningOptionType("lep2_absEta",                50,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau_eta)"]        = new binningOptionType("TMath::Abs(tau_eta)",        50,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau1_eta)"]       = new binningOptionType("TMath::Abs(tau1_eta)",       50,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau2_eta)"]       = new binningOptionType("TMath::Abs(tau2_eta)",       50,  0.,   +2.5);
  binningOptions_["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = new binningOptionType("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", 50, 0., +2.5);
  binningOptions_["mvaOutput_hadTopTaggerWithKinFit"]                      = new binningOptionType("mvaOutput_hadTopTaggerWithKinFit",                      50, -1., 1.);

  for(auto & kv: binningOptions_)
  {
    central_or_shiftOptions_[kv.second->histogramName_] = { "central" };
  }
}

MVAInputVarHistManager::~MVAInputVarHistManager()
{
  for(auto & kv: binningOptions_)
  {
    delete kv.second;
  }
}

void
MVAInputVarHistManager::defineBinningOption(const std::string & histogramName,
                                            int numBinsX,
                                            double xMin,
                                            double xMax)
{
  binningOptions_[histogramName] = new binningOptionType(histogramName, numBinsX, xMin, xMax);
}

void
MVAInputVarHistManager::bookHistograms(TFileDirectory & dir,
                                       const std::vector<std::string> & mvaInputVariables)
{
  for(const std::string & mvaInputVariable: mvaInputVariables)
  {
    if(! binningOptions_.count(mvaInputVariable))
    {
      throw cmsException(this, __func__)
        << "No binning options defined for MVA input variable '" << (mvaInputVariable) << '\'';
    }

    const binningOptionType * binningOption = binningOptions_.at(mvaInputVariable);
    TH1 * histogram = book1D(
      dir,
      binningOption->histogramName_,
      binningOption->histogramName_,
      binningOption->numBinsX_,
      binningOption->xMin_,
      binningOption->xMax_
    );
    histograms_mvaInputVariables_[mvaInputVariable] = histogram;
  }
}

void
MVAInputVarHistManager::fillHistograms(const std::map<std::string, double> & mvaInputs,
                                       double evtWeight)
{
  const double evtWeightErr = 0.;
  for(const auto & mvaInput: mvaInputs)
  {
    if(! histograms_mvaInputVariables_.count(mvaInput.first))
    {
      throw cmsException(this, __func__)
        << "No histogram booked for MVA input variable '" << mvaInput.first << '\'';
    }

    fillWithOverFlow(histograms_mvaInputVariables_.at(mvaInput.first), mvaInput.second, evtWeight, evtWeightErr);
  }
}

MVAInputVarHistManager::binningOptionType::binningOptionType(const std::string & histogramName,
                                                             int numBinsX,
                                                             double xMin,
                                                             double xMax)
  : histogramName_(histogramName)
  , numBinsX_(numBinsX)
  , xMin_(xMin)
  , xMax_(xMax)
{}
