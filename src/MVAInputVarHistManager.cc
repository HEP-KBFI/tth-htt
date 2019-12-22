#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMath.h> // TMath::Pi()

MVAInputVarHistManager::MVAInputVarHistManager(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  binningOptions_["avg_dr_jet"]                 = new binningOptionType("avg_dr_jet",                 10,  0.,    5.);
  binningOptions_["Lep_min_dr_jet"]             = new binningOptionType("Lep_min_dr_jet",             10,  0.,    5.);
  binningOptions_["max_Lep_eta"]                = new binningOptionType("max_Lep_eta",                10,  0.,    2.5);
  binningOptions_["maxeta"]                      = new binningOptionType("maxeta",                10,  0.,    2.5);
  binningOptions_["min_dr_Lep"]                 = new binningOptionType("min_dr_Lep",                 10,  0.,    5.);
  binningOptions_["res-HTT_2016"]               = new binningOptionType("res-HTT_2016",               10,  0.,    1.);
  binningOptions_["avr_dr_lep_tau"]             = new binningOptionType("avr_dr_lep_tau",             10,  0.,    5.);
  binningOptions_["max_dr_lep_tau"]             = new binningOptionType("max_dr_lep_tau",             10,  0.,    5.);
  binningOptions_["is_OS"]                      = new binningOptionType("is_OS",                       2,  0.,    2.);
  binningOptions_["dr_lep_tau_os"]              = new binningOptionType("dr_lep_tau_os",              10,  0.,    5.);
  binningOptions_["dr_lep_tau_ss"]              = new binningOptionType("dr_lep_tau_ss",              10,  0.,    5.);
  binningOptions_["dr_lep1_tau"]                = new binningOptionType("dr_lep1_tau",                10,  0.,    5.);
  binningOptions_["dr_lep1_tau1"]               = new binningOptionType("dr_lep1_tau1",               10,  0.,    5.);
  binningOptions_["dr_lep1_tau2"]               = new binningOptionType("dr_lep1_tau2",               10,  0.,    5.);
  binningOptions_["dr_lep2_tau"]                = new binningOptionType("dr_lep2_tau",                10,  0.,    5.);
  binningOptions_["dr_lep2_tau1"]               = new binningOptionType("dr_lep2_tau1",               10,  0.,    5.);
  binningOptions_["dr_lep2_tau2"]               = new binningOptionType("dr_lep2_tau2",               10,  0.,    5.);
  binningOptions_["dr_lep3_tau"]                = new binningOptionType("dr_lep3_tau",                10,  0.,    5.);
  binningOptions_["dr_lep1_tau_os"]             = new binningOptionType("dr_lep1_tau_os",             10,  0.,    5.);
  binningOptions_["dr_lep2_tau_ss"]             = new binningOptionType("dr_lep2_tau_ss",             10,  0.,    5.);
  binningOptions_["dr_leps"]                    = new binningOptionType("dr_leps",                    10,  0.,    5.);
  binningOptions_["dr_tau_lep"]                 = new binningOptionType("dr_tau_lep",                 10,  0.,    5.);
  binningOptions_["dr_taus"]                    = new binningOptionType("dr_taus",                    10,  0.,    5.);
  binningOptions_["hadTauPairCharge"]           = new binningOptionType("hadTauPairCharge",            5, -2.5,  +2.5);
  binningOptions_["sum_Lep_charge"]             = new binningOptionType("sum_Lep_charge",              9, -4.5,  +4.5);
  binningOptions_["ht"]                         = new binningOptionType("ht",                         40,  0.,  400.);
  binningOptions_["htmiss"]                     = new binningOptionType("htmiss",                     40,  0.,  200.);
  binningOptions_["TMath::Min(htmiss,500)"]     = new binningOptionType("htmiss",                     40,  0.,  200.);
  binningOptions_["jet_deltaRavg"]              = new binningOptionType("jet_deltaRavg",              10,  0.,    5.);
  binningOptions_["jet_deltaRmax"]              = new binningOptionType("jet_deltaRmax",              10,  0.,    7.5);
  binningOptions_["min_Deta_leadfwdJet_jet"]    = new binningOptionType("min_Deta_leadfwdJet_jet",    40,  0.,   10.);
  binningOptions_["leadFwdJet_eta"]             = new binningOptionType("leadFwdJet_eta",             40, 0.,    2.5);
  binningOptions_["leadFwdJet_pt"]              = new binningOptionType("leadFwdJet_pt",              40,  0.,  400.);
  binningOptions_["lep_pt"]                     = new binningOptionType("lep_pt",                     40,  0.,  200.);
  binningOptions_["lep_tth_mva"]                = new binningOptionType("lep_tth_mva",                40, -1.,   +1.);
  binningOptions_["lep1_abs_eta"]               = new binningOptionType("lep1_abs_eta",               10, -2.5,  +2.5);
  binningOptions_["lep1_eta"]                   = new binningOptionType("lep1_eta",                   10, 0.,  +2.5);
  binningOptions_["lep2_eta"]                   = new binningOptionType("lep2_eta",                   10, 0.,  +2.5);
  binningOptions_["lep3_eta"]                   = new binningOptionType("lep3_eta",                   10, 0.,  +2.5);
  binningOptions_["eta_LepLep_los"]             = new binningOptionType("eta_LepLep_los",             10, 0.,  +3.5);
  binningOptions_["lep1_phi"]                   = new binningOptionType("lep1_phi",                   10, -TMath::Pi(),  +TMath::Pi());
  binningOptions_["lep2_phi"]                   = new binningOptionType("lep2_phi",                   10, -TMath::Pi(),  +TMath::Pi());
  binningOptions_["lep3_phi"]                   = new binningOptionType("lep3_phi",                   10, -TMath::Pi(),  +TMath::Pi());
  binningOptions_["HadTop_eta"]                 = new binningOptionType("HadTop_eta",                 10, 0.,  +2.5);
  binningOptions_["lep1_charge*tau_charge"]     = new binningOptionType("lep1_charge*tau_charge",      3, -1.5,  +1.5);
  binningOptions_["lep1_conePt"]                = new binningOptionType("lep1_conePt",                30,  0.,  300.);
  binningOptions_["lep1_pt"]                    = new binningOptionType("lep1_pt",                    20,  0.,  200.);
  binningOptions_["lep1_tth_mva"]               = new binningOptionType("lep1_tth_mva",               40, -1.,   +1.);
  binningOptions_["lep2_abs_eta"]               = new binningOptionType("lep2_abs_eta",               10, -2.5,  +2.5);
  binningOptions_["lep2_conePt"]                = new binningOptionType("lep2_conePt",                20,  0.,  200.);
  binningOptions_["lep2_pt"]                    = new binningOptionType("lep2_pt",                    20,  0.,  200.);
  binningOptions_["lep2_tth_mva"]               = new binningOptionType("lep2_tth_mva",               10, -1.,   +1.);
  binningOptions_["lep3_abs_eta"]               = new binningOptionType("lep3_abs_eta",               10, -2.5,  +2.5);
  binningOptions_["lep3_conePt"]                = new binningOptionType("lep3_conePt",                15,  0.,  150.);
  binningOptions_["lep4_conePt"]                = new binningOptionType("lep4_conePt",                10,  0.,  100.);
  binningOptions_["lep3_pt"]                    = new binningOptionType("lep3_pt",                    20,  0.,  200.);
  binningOptions_["jet1_pt"]                    = new binningOptionType("jet1_pt",                    40,  0.,  400.);
  binningOptions_["jet2_pt"]                    = new binningOptionType("jet2_pt",                    40,  0.,  400.);
  binningOptions_["jet3_pt"]                    = new binningOptionType("jet3_pt",                    15,  0.,  150.);
  binningOptions_["jet4_pt"]                    = new binningOptionType("jet4_pt",                    15,  0.,  150.);
  binningOptions_["jet1_eta"]                   = new binningOptionType("jet1_eta",                   10, 0.,   +5.);
  binningOptions_["jet2_eta"]                   = new binningOptionType("jet2_eta",                   10, 0.,   +5.);
  binningOptions_["jet3_eta"]                   = new binningOptionType("jet3_eta",                   10, 0.,   +5.);
  binningOptions_["jet4_eta"]                   = new binningOptionType("jet4_eta",                   10, 0.,   +5.);
  binningOptions_["lep1_eta"]                   = new binningOptionType("lep1_eta",                   10, 0.,  +2.5);
  binningOptions_["jetFwd1_eta"]                = new binningOptionType("jetFwd1_eta",                10, 0.,   +2.5);
  binningOptions_["jetFwd1_pt"]                 = new binningOptionType("jetFwd1_pt",                 40,  0.,  400.);
  binningOptions_["jet1_phi"]                   = new binningOptionType("jet1_phi",                   10, -TMath::Pi(),   +TMath::Pi());
  binningOptions_["jet2_phi"]                   = new binningOptionType("jet2_phi",                   10, -TMath::Pi(),   +TMath::Pi());
  binningOptions_["jet3_phi"]                   = new binningOptionType("jet3_phi",                   10, -TMath::Pi(),   +TMath::Pi());
  binningOptions_["jet4_phi"]                   = new binningOptionType("jet4_phi",                   10, -TMath::Pi(),   +TMath::Pi());
  binningOptions_["lep3_tth_mva"]               = new binningOptionType("lep3_tth_mva",               10, -1.,   +1.);
  binningOptions_["LepGood_conePt[iF_Recl[0]]"] = new binningOptionType("LepGood_conePt[iF_Recl[0]]", 40,  0.,  200.);
  binningOptions_["LepGood_conePt[iF_Recl[1]]"] = new binningOptionType("LepGood_conePt[iF_Recl[1]]", 40,  0.,  200.);
  binningOptions_["LepGood_conePt[iF_Recl[2]]"] = new binningOptionType("LepGood_conePt[iF_Recl[2]]", 40,  0.,  200.);
  binningOptions_["leptonPairCharge"]           = new binningOptionType("leptonPairCharge",            5, -2.5,  +2.5);
  binningOptions_["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = new binningOptionType("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", 10, -2.5, +2.5);
  binningOptions_["tau2_eta"]                   = new binningOptionType("tau2_eta",                   10, 0, +2.5);
  binningOptions_["max_lep_eta"]                = new binningOptionType("max_lep_eta",                10, -2.5,  +2.5);
  binningOptions_["memOutput_LR"]               = new binningOptionType("memOutput_LR",               20,  0.,    1.);
  binningOptions_["memOutput_ttZ_LR"]           = new binningOptionType("memOutput_ttZ_LR",           20,  0.,    1.);
  binningOptions_["memOutput_tt_LR"]            = new binningOptionType("memOutput_tt_LR",            20,  0.,    1.);
  binningOptions_["mhtJet25_Recl"]              = new binningOptionType("mhtJet25_Recl",              40,  0.,  400.);
  binningOptions_["min(met_pt,400)"]            = new binningOptionType("min(met_pt,400)",            40,  0.,  200.);
  binningOptions_["met_LD"]                     = new binningOptionType("met_LD",                     50,  0.,  500.);
  binningOptions_["metLD"]                     = new binningOptionType("metLD",                     50,  0.,  500.);
  binningOptions_["mindr_lep_jet"]              = new binningOptionType("mindr_lep_jet",              10,  0.,    5.);
  binningOptions_["mindr_lep1_jet"]             = new binningOptionType("mindr_lep1_jet",             10,  0.,    5.);
  binningOptions_["mindr_lep2_jet"]             = new binningOptionType("mindr_lep2_jet",             10,  0.,    5.);
  binningOptions_["mindr_lep3_jet"]             = new binningOptionType("mindr_lep3_jet",             10,  0.,    5.);
  binningOptions_["mindr_tau_jet"]              = new binningOptionType("mindr_tau_jet",              10,  0.,    5.);
  binningOptions_["mindr_tau1_jet"]             = new binningOptionType("mindr_tau1_jet",             10,  0.,    5.);
  binningOptions_["mindr_tau2_jet"]             = new binningOptionType("mindr_tau2_jet",             10,  0.,    5.);
  binningOptions_["mT_lep"]                     = new binningOptionType("mT_lep",                     20,  0.,  200.);
  binningOptions_["mT_lep1"]                    = new binningOptionType("mT_lep1",                    20,  0.,  200.);
  binningOptions_["mT_lep2"]                    = new binningOptionType("mT_lep2",                    20,  0.,  200.);
  binningOptions_["mT_lep3"]                    = new binningOptionType("mT_lep3",                    20,  0.,  200.);
  binningOptions_["MT_met_lep1"]                = new binningOptionType("MT_met_lep1",                20,  0.,  200.);
  binningOptions_["MT_met_lep2"]                = new binningOptionType("MT_met_lep2",                20,  0.,  200.);
  binningOptions_["massL3"]                     = new binningOptionType("massL3",                     50,  0.,  500.);
  binningOptions_["massL"]                     = new binningOptionType("massL",                     50,  0.,  500.);
  binningOptions_["mT_tau1"]                    = new binningOptionType("mT_tau1",                    20,  0.,  200.);
  binningOptions_["mT_tau2"]                    = new binningOptionType("mT_tau2",                    20,  0.,  200.);
  binningOptions_["mbb_loose"]                  = new binningOptionType("mbb_loose",                  20,  0.,  200.);
  binningOptions_["mbb_medium"]                  = new binningOptionType("mbb_medium",                20,  0.,  200.);
  binningOptions_["mbb"]                        = new binningOptionType("mbb",                        20,  0.,  200.);
  binningOptions_["mTauTau"]                    = new binningOptionType("mTauTau",                    20,  0.,  300.);
  binningOptions_["mTauTauVis"]                 = new binningOptionType("mTauTauVis",                 20,  0.,  200.);
  binningOptions_["mTauTauVis1"]                = new binningOptionType("mTauTauVis1",                20,  0.,  200.);
  binningOptions_["mTauTauVis2"]                = new binningOptionType("mTauTauVis2",                20,  0.,  200.);
  binningOptions_["nJet"]                       = new binningOptionType("nJet",                       20, -0.5, +19.5);
  binningOptions_["nJet25_Recl"]                = new binningOptionType("nJet25_Recl",                20, -0.5, +19.5);
  binningOptions_["n_presel_jet"]                = new binningOptionType("n_presel_jet",                20, -0.5, +19.5);
  binningOptions_["njets_inclusive"]            = new binningOptionType("njets_inclusive",            20, -0.5, +19.5);
  binningOptions_["nBJetLoose"]                 = new binningOptionType("nBJetLoose",                 10, -0.5,  +9.5);
  binningOptions_["nBJetMedium"]                = new binningOptionType("nBJetMedium",                6, -0.5,  +5.5);
  binningOptions_["nJetForward"]                = new binningOptionType("nJetForward",                6, -0.5,  +5.5);
  binningOptions_["n_presel_jetFwd"]            = new binningOptionType("n_presel_jetFwd",                6, -0.5,  +5.5);
  binningOptions_["nElectron"]                  = new binningOptionType("nElectron",                  10, -0.5,  +5.5);
  binningOptions_["has_SFOS"]                   = new binningOptionType("has_SFOS",                  2, -0.5,  +0.5);
  binningOptions_["lep1_charge"]                = new binningOptionType("lep1_charge",               3, -1.5,  +1.5);
  binningOptions_["Dilep_pdgId"]                = new binningOptionType("Dilep_pdgId",               3, 0.5,  +3.5);

  binningOptions_["ntags_loose"]                = new binningOptionType("ntags_loose",                10, -0.5,  +9.5);
  binningOptions_["ptmiss"]                     = new binningOptionType("ptmiss",                     40,  0.,  200.);
  binningOptions_["lep_conePt"]                 = new binningOptionType("lep_conePt",                 40,  0.,  200.);
  binningOptions_["dr_lep_tau_lead"]            = new binningOptionType("dr_lep_tau_lead",            10,  0.,    5.);
  binningOptions_["costS_tau"]                  = new binningOptionType("costS_tau",                  10, 0.,   +1.);
  binningOptions_["cosThetaS_hadTau"]           = new binningOptionType("cosThetaS_hadTau",           10, 0.,   +1.);
  binningOptions_["hadTop_BDT"]                 = new binningOptionType("hadTop_BDT",                        10, 0.,   +1.);
  binningOptions_["HTT"]                        = new binningOptionType("HTT",                        10, 0.,   +1.);
  binningOptions_["res_HTT"]                    = new binningOptionType("res_HTT",                    10, 0.,   +1.);
  binningOptions_["Hj_tagger_hadTop"]           = new binningOptionType("Hj_tagger_hadTop",                    10, 0.,   +1.);

  binningOptions_["HadTop_pt"]                  = new binningOptionType("HadTop_pt",                  10,  0.,  500.);
  binningOptions_["res_HTT_2"]                    = new binningOptionType("res_HTT_2",                    10, 0.,   +1.);
  binningOptions_["HadTop_pt_2"]                  = new binningOptionType("HadTop_pt_2",                  10,  0.,  500.);
  binningOptions_["semi_HTT"]                    = new binningOptionType("semi_HTT",                    10, 0.,   +1.);
  binningOptions_["HadTop_pt_semi"]                  = new binningOptionType("HadTop_pt_semi",                  10,  0.,  500.);
  binningOptions_["pZetaComb"]                  = new binningOptionType("pZetaComb",                  10,  0.,  100.);

  binningOptions_["TMath::Min(ptmiss,500)"]     = new binningOptionType("ptmiss",                     20,  0.,  200.);
  binningOptions_["tau_abs_eta"]                = new binningOptionType("tau_abs_eta",                10, -2.5,  +2.5);
  binningOptions_["tau_pt"]                     = new binningOptionType("tau_pt",                     20,  0.,  200.);
  binningOptions_["tau1_pt"]                    = new binningOptionType("tau1_pt",                    20,  0.,  200.);
  binningOptions_["tau2_pt"]                    = new binningOptionType("tau2_pt",                    20,  0.,  200.);
  binningOptions_["tau_eta"]                    = new binningOptionType("tau_eta",                    10, -2.5,  +2.5);
  binningOptions_["tau1_eta"]                   = new binningOptionType("tau1_eta",                   10, 0.,  +2.5);
  binningOptions_["tau1_phi"]                   = new binningOptionType("tau1_phi",                   10, -TMath::Pi(),  +TMath::Pi());
  binningOptions_["min_lep_eta"]                = new binningOptionType("min_lep_eta",                10, -2.5,  +2.5);
  binningOptions_["tt_deltaR"]                  = new binningOptionType("tt_deltaR",                  10,  0.,    5.);
  binningOptions_["tt_sumpt"]                   = new binningOptionType("tt_sumpt",                   20,  0.,  200.);
  binningOptions_["tt_visiblemass"]             = new binningOptionType("tt_visiblemass",             20,  0.,  200.);
  binningOptions_["TMath::Abs(lep_eta)"]        = new binningOptionType("lep_absEta",                 10,  0.,   +2.5);
  binningOptions_["TMath::Abs(lep1_eta)"]       = new binningOptionType("lep1_absEta",                10,  0.,   +2.5);
  binningOptions_["TMath::Abs(lep2_eta)"]       = new binningOptionType("lep2_absEta",                10,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau_eta)"]        = new binningOptionType("TMath::Abs(tau_eta)",        10,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau1_eta)"]       = new binningOptionType("TMath::Abs(tau1_eta)",       10,  0.,   +2.5);
  binningOptions_["TMath::Abs(tau2_eta)"]       = new binningOptionType("TMath::Abs(tau2_eta)",       10,  0.,   +2.5);
  binningOptions_["TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))"] = new binningOptionType("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", 10, 0., +2.5);
  binningOptions_["mvaOutput_hadTopTaggerWithKinFit"]                      = new binningOptionType("mvaOutput_hadTopTaggerWithKinFit",                      10, -1., 1.);

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
