#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerMEM.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()

#define ENABLE_DR_CUTS 0

#define N_GENHADTAU_IDX     0
#define N_GENBQUARK_IDX     1
#define N_GENLEPFROMTAU_IDX 2
#define N_GENNUFROMTAU_IDX  3
#define N_GENTAU_IDX        4
#define N_GENLEPFROMTOP_IDX 5
#define N_GENNUFROMTOP      6

NtupleFillerMEM::NtupleFillerMEM()
  : file_(0)
  , tree_(0)
  , use2016_(false)
  , met_f_(false)
  , selHadTau_(0)
  , errCode_(NTUPLE_ERR_OK)
  , warnCode_(NTUPLE_WARN_OK)
{}

NtupleFillerMEM::~NtupleFillerMEM()
{
  close();
}

void
NtupleFillerMEM::use2016(bool use2016)
{
  use2016_ = use2016;
  met_f_ = METFiller<double>(use2016_);
}

void
NtupleFillerMEM::setFileName(const std::string & fileName)
{
  file_ = new TFile(fileName.c_str(), "recreate");
  tree_ = new TTree("tree", "Selected events created for 3l1tau MEM");

  /* basics */
  rle_f_.initBranches(tree_);
  met_f_.initBranches(tree_);

  genHiggsDecayMode_.setBranchName("genHiggsDecayMode");
  genHiggsDecayMode_.initBranch(tree_);

  /* reconstructed */
  for(std::size_t i = 0; i < 3; ++i)
  {
    leptons_f_[i].setBranchName(Form("lepton%lu", i + 1));
    leptons_f_[i].initBranches(tree_);
  }
  for(std::size_t i = 0; i < 2; ++i)
  {
    jets_f_[i].setBranchName(Form("jets%lu", i + 1));
    jets_f_[i].initBranches(tree_);
  }
  hTau_f_.setBranchName("htau");
  hTau_f_.initBranches(tree_);

  /* mva */
  mva_f_.setBranchNameMap(mvaMap_);
  ttV_f_.setBranchName("mvaOutput_3l_ttV");
  ttbar_f_.setBranchName("mvaOutput_3l_ttbar");
  mva_f_.initBranches(tree_);
  ttV_f_.initBranch(tree_);
  ttbar_f_.initBranch(tree_);

  /* generator level, enabled only if use2016_ is true */
  if(use2016_)
  {
    for(std::size_t i = 0; i < 2; ++i)
    {
      genTaus_f_[i].setBranchName(Form("genTau%lu", i + 1));
      genLepFromTop_f_[i].setBranchName(Form("genLepFromTop%lu", i + 1));
      genBQuark_f_[i].setBranchName(Form("genBQuarkFromTop%lu", i + 1));
      genNuFromTop_f_[i].setBranchName(Form("genNuFromTop%lu", i + 1));

      genTaus_f_[i].initBranches(tree_);
      genLepFromTop_f_[i].initBranches(tree_);
      genBQuark_f_[i].initBranches(tree_);
      genNuFromTop_f_[i].initBranches(tree_);
    }

    genHtau_f_.setBranchName("genHtau");
    genLepFromTau_f_.setBranchName("genLepFromTau");
    genNuLepFromTau_f_.setBranchName("genNuLepFromTau");
    genNuFromHTau_f_.setBranchName("genNuFromHtau");
    genNuFromLTau_f_.setBranchName("genNuFromLtau");

    genHtau_f_.initBranches(tree_);
    genLepFromTau_f_.initBranches(tree_);
    genNuLepFromTau_f_.initBranches(tree_);
    genNuFromHTau_f_.initBranches(tree_);
    genNuFromLTau_f_.initBranches(tree_);
  }
  genMultiplicity_f_[N_GENHADTAU_IDX    ].setBranchName("nGenHadTau");
  genMultiplicity_f_[N_GENBQUARK_IDX    ].setBranchName("nGenBQuarkFromTop");
  genMultiplicity_f_[N_GENLEPFROMTAU_IDX].setBranchName("nGenLepFromTau");
  genMultiplicity_f_[N_GENNUFROMTAU_IDX ].setBranchName("nGenNuFromTau");
  genMultiplicity_f_[N_GENTAU_IDX       ].setBranchName("nGenTau");
  genMultiplicity_f_[N_GENLEPFROMTOP_IDX].setBranchName("nGenLepFromTop");
  genMultiplicity_f_[N_GENNUFROMTOP     ].setBranchName("nGenNuFromTop");
  for(auto & filler: genMultiplicity_f_)
    filler.initBranch(tree_);

  /* logging */
  errCode_f_.setBranchName("errCode");
  warnCode_f_.setBranchName("warnCode");
  errCode_f_.setValuePtr(&errCode_);
  warnCode_f_.setValuePtr(&warnCode_);
  errCode_f_.initBranch(tree_);
  warnCode_f_.initBranch(tree_);
}

void
NtupleFillerMEM::setDiTauMass(double diTauMass)
{
  diTauMass_ = diTauMass;
}

void
NtupleFillerMEM::add(double genHiggsDecayMode)
{
  genHiggsDecayMode_.setValue(genHiggsDecayMode);
}

void
NtupleFillerMEM::add(const RLEUnit & rleUnit)
{
  rle_f_.setValues(rleUnit);
}

void
NtupleFillerMEM::add(const METUnit<double> & metUnit)
{
  met_f_.setValues(metUnit);
}

void
NtupleFillerMEM::add(const std::map<std::string, double> mva,
                     double ttV,
                     double ttbar)
{
  mva_f_.setValues(mva);
  ttV_f_.setValue(ttV);
  ttbar_f_.setValue(ttbar);
}

void
NtupleFillerMEM::add(const std::vector<const RecoJet*> & selBJets_loose,
                     const std::vector<const RecoJet*> & selBJets_medium,
                     const std::vector<const RecoJet*> & selJets)
{
  // copy over
  std::vector<const RecoJet *> selBJets_loose_(selBJets_loose.begin(), selBJets_loose.end());
  std::vector<const RecoJet *> selBJets_medium_(selBJets_medium.begin(), selBJets_medium.end());
  std::vector<const RecoJet *> selJets_(selJets.begin(), selJets.end());

  // unique merge loose and medium B-jets, and hadronic jets
  std::sort(selBJets_medium_.begin(), selBJets_medium_.end(), isHigherPt);
  std::sort(selBJets_loose_.begin(), selBJets_loose_.end(), isHigherPt);
  std::sort(selJets_.begin(), selJets_.end(), isHigherCSV); // optional: sort by pT
  std::vector<const RecoJet *> selBJetsMerged(selBJets_medium_);
  auto unique_push_back = [&selBJetsMerged](const std::vector<const RecoJet *> & v) -> void
  {
    for(const RecoJet * j: v)
      if(std::find(selBJetsMerged.begin(), selBJetsMerged.end(), j) == selBJetsMerged.end())
        selBJetsMerged.push_back(j);
  };
  unique_push_back(selBJets_loose_);
  unique_push_back(selJets_);
  selBJetsMerged_ = selBJetsMerged;

  if(selBJetsMerged_.size() > 1)
    for(std::size_t i = 0; i < 2; ++i)
      jets_f_[i].setValues(*selBJetsMerged_[i]);
  else
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_JETS;
}

void
NtupleFillerMEM::add(const std::vector<const RecoLepton*> & selLeptons)
{
  selLeptons_ = selLeptons;
  if(selLeptons_.size() > 2)
    for(std::size_t i = 0; i < 3; ++i)
      leptons_f_[i].setValues(*selLeptons_[i]);
  else
    errCode_ |= NTUPLE_ERR_LESS_THAN_3_LEPTONS;
}

void
NtupleFillerMEM::add(const RecoHadTau * selHadTau)
{
  selHadTau_ = selHadTau;
  if(selHadTau_)
    hTau_f_.setValues(*selHadTau_);
  else
    errCode_ |= NTUPLE_ERR_NO_HAD_TAU;
}

void
NtupleFillerMEM::add(const std::vector<GenHadTau> & genHadTaus,
                     const std::vector<GenLepton> & genBQuarkFromTop,
                     const std::vector<GenLepton> & genLepFromTau,
                     const std::vector<GenLepton> & genNuFromTau,
                     const std::vector<GenLepton> & genTau,
                     const std::vector<GenLepton> & genLepFromTop,
                     const std::vector<GenLepton> & genNuFromTop)
{
  // perform generator-level matching
  // enable only if era is 2016
  // if there are multiple candidates then pick the first one?
  genMultiplicity_f_[N_GENHADTAU_IDX    ].setValue(genHadTaus.size());
  genMultiplicity_f_[N_GENBQUARK_IDX    ].setValue(genBQuarkFromTop.size());
  genMultiplicity_f_[N_GENLEPFROMTAU_IDX].setValue(genLepFromTau.size());
  genMultiplicity_f_[N_GENNUFROMTAU_IDX ].setValue(genNuFromTau.size());
  genMultiplicity_f_[N_GENTAU_IDX       ].setValue(genTau.size());
  genMultiplicity_f_[N_GENLEPFROMTOP_IDX].setValue(genLepFromTop.size());
  genMultiplicity_f_[N_GENNUFROMTOP     ].setValue(genNuFromTop.size());

  // step 0:
  // - check if all generator level particles are there
  if(genBQuarkFromTop.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_GEN_BQUARKS;
    return;
  }
  if(! genLepFromTau.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_LEPT_FROM_TAU;
    return;
  }
  if(! genHadTaus.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_HAD_TAU;
    return;
  }
  if(genNuFromTau.size() < 3)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_3_GEN_NUS_FROM_TAU;
    return;
  }
  if(genTau.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_GEN_TAUS;
    return;
  }
  if(genLepFromTop.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_GEN_LEP_FROM_TOP;
    return;
  }
  if(genNuFromTop.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_GEN_NU_FROM_TOP;
    return;
  }
  if(selBJetsMerged_.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_2_JETS;
    return;
  }
  if(selLeptons_.size() < 3)
  {
    errCode_ |= NTUPLE_ERR_LESS_THAN_3_LEPTONS;
    return;
  }
  if(! selHadTau_)
  {
    errCode_ |= NTUPLE_ERR_NO_HAD_TAU;
    return;
  }

  // step 0:
  // - keep only first 2 elements which we used to fill the Ntuples
  selBJetsMerged_.resize(2);

  // step 1:
  // - find b+/b- in gen lvl b quarks
  // - find corresponding dR match from the recos
  const double dR = 0.5;
  std::vector<GenParticleExt> genBQuarkFromTopPos(genBQuarkFromTop.begin(), genBQuarkFromTop.end());
  std::vector<GenParticleExt> genBQuarkFromTopNeg(genBQuarkFromTop.begin(), genBQuarkFromTop.end());
  // select only b-quarks and anti-b quarks
  genBQuarkFromTopPos.erase(
    std::remove_if(genBQuarkFromTopPos.begin(), genBQuarkFromTopPos.end(),
                   [](const GenParticleExt & q) -> bool
                   {
                     return ! (q.pdgId_ > 0);
                   }), genBQuarkFromTopPos.end()
  );
  genBQuarkFromTopNeg.erase(
    std::remove_if(genBQuarkFromTopNeg.begin(), genBQuarkFromTopNeg.end(),
                   [](const GenParticleExt & q) -> bool
                   {
                     return ! (q.pdgId_ < 0);
                   }), genBQuarkFromTopNeg.end()
  );
  if(! genBQuarkFromTopPos.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_POS_BQUARKS;
    return;
  }
  if(! genBQuarkFromTopNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NEG_BQUARKS;
    return;
  }
#if ENABLE_DR_CUTS
  // do generator level matching
  genBQuarkFromTopPos.erase(
    std::remove_if(genBQuarkFromTopPos.begin(), genBQuarkFromTopPos.end(),
                   [this, dR](const GenParticleExt & q) -> bool
                   {
                     for(const RecoJet * & b: selBJetsMerged_)
                      if(q.is_overlap(*b, dR))
                        return false;
                     return true;
                   }), genBQuarkFromTopPos.end()
  );
  genBQuarkFromTopNeg.erase(
    std::remove_if(genBQuarkFromTopNeg.begin(), genBQuarkFromTopNeg.end(),
                   [this, dR](const GenParticleExt & q) -> bool
                   {
                     for(const RecoJet * & b: selBJetsMerged_)
                      if(q.is_overlap(*b, dR))
                        return false;
                     return true;
                   }), genBQuarkFromTopNeg.end()
   );
  if(! genBQuarkFromTopPos.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_POS_BQUARKS_DR;
    return;
  }
  if(! genBQuarkFromTopNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NEG_BQUARKS_DR;
    return;
  }
#endif
  if(genBQuarkFromTopPos.size() > 1)
  {
    errCode_ |= NTUPLE_ERR_MORE_THAN_1_GEN_POS_BQUARKS;
    return;
  }
  if(genBQuarkFromTopNeg.size() > 1)
  {
    errCode_ |= NTUPLE_ERR_MORE_THAN_1_GEN_NEG_BQUARKS;
    return;
  }
#if ENABLE_DR_CUTS
  // step 1.2:
  // - make sure that both b-quarks are covered by selected jets
  for(const GenParticleExt & pos: genBQuarkFromTopPos)
    for(const GenParticleExt & neg: genBQuarkFromTopNeg)
      for(const RecoJet * & b: selBJetsMerged_)
        if(b -> is_overlap(pos, dR) && b -> is_overlap(neg, dR))
        {
          errCode_ |= NTUPLE_ERR_SAME_JET_OVERLAP;
          return;
        }
#endif

  // step 2.1:
  // - obtain gen lvl hadronic tau
  std::vector<GenHadTau> genHadTaus_(genHadTaus.begin(), genHadTaus.end());
  genHadTaus_.erase(
    std::remove_if(genHadTaus_.begin(), genHadTaus_.end(),
                   [this, dR](const GenHadTau & hadTau) -> bool
                   {
                     if(
#if ENABLE_DR_CUTS
                        selHadTau_ -> is_overlap(hadTau, dR) &&
#endif
                        selHadTau_ -> charge_ == hadTau.charge_
                     )
                       return false;
                     return true;
                   }), genHadTaus_.end()
  );
  if(! genHadTaus_.size())
  {
    errCode_ |= NTUPLE_ERR_NO_MATCHING_GEN_HAD_TAU;
    return;
  }

  // step 2.2:
  // - determine the hadronic tau charge -> complementary lepton has the opposite charge
  const int hadTauCharge = genHadTaus_[0].charge_;
  const int complLepCharge = -hadTauCharge;
  const int nuLepFromTauSign = static_cast<int>(-16 * boost::math::sign(complLepCharge));

  // step 3:
  // - loop over leptons coming from tau decay, collect the ones with complementary sign
  // - dR match these leptons against selected gen lvl leptons (hopefully we're left w/ only 1)
  //   and check if there is a corresponding lepton neutrino
  std::vector<GenParticleExt> genLepFromTauCandidates(genLepFromTau.begin(), genLepFromTau.end());
  // select only the leptons which have complementary charge
  genLepFromTauCandidates.erase(
    std::remove_if(genLepFromTauCandidates.begin(), genLepFromTauCandidates.end(),
                   [complLepCharge](const GenParticleExt & lep) -> bool
                   {
                     return lep.charge_ != complLepCharge;
                   }), genLepFromTauCandidates.end()
  );
  if(! genLepFromTauCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_LEPTONS_FROM_TAU_CORRECT_CHARGE;
    return;
  }
  // do dR matching against selected leptons
#if ENABLE_DR_CUTS
  genLepFromTauCandidates.erase(
    std::remove_if(genLepFromTauCandidates.begin(), genLepFromTauCandidates.end(),
                   [this, dR](const GenParticleExt & lep) -> bool
                   {
                     for(const auto & selLep: selLeptons_)
                       if(lep.is_overlap(*selLep, dR))
                         return false;
                     return true;
                   }), genLepFromTauCandidates.end()
  );
  if(! genLepFromTauCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_LEPTONS_FROM_TAU_DR;
    return;
  }
#endif

  // check the leptons against neutrinos coming from tau
  genLepFromTauCandidates.erase(
    std::remove_if(genLepFromTauCandidates.begin(), genLepFromTauCandidates.end(),
                   [&genNuFromTau](const GenParticleExt & lep) -> bool
                   {
                     for(const GenParticleExt & nu: genNuFromTau)
                       if(nu.pdgId_ * lep.pdgId_ < 0                   && // lepton & anti-nu or anti-lepton & nu
                          (std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_))
                         return false;
                     return true;
                   }), genLepFromTauCandidates.end()
  );
  if(! genLepFromTauCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_LEPTONS_FROM_TAU_CORRESPONDING_NU;
    return;
  }

  // step 4:
  // - find corresponding neutrino to complementary lepton (should have opposite signs)
  std::vector<GenParticleExt> genNuLepFromTauCandidates(genNuFromTau.begin(), genNuFromTau.end());
  // select only those which have correct flavor
  genNuLepFromTauCandidates.erase(
    std::remove_if(genNuLepFromTauCandidates.begin(), genNuLepFromTauCandidates.end(),
                   [&genLepFromTauCandidates](const GenParticleExt & nu) -> bool
                   {
                     for(const GenParticleExt & lep: genLepFromTauCandidates)
                       if(lep.pdgId_ * nu.pdgId_ < 0 &&
                          (std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_))
                         return false;
                     return true;
                   }), genNuLepFromTauCandidates.end()
  );
  if(! genNuLepFromTauCandidates.size()) // expect 1
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_LEPT_NUS_FROM_TAU_CORRECT_FLAVOR;
    return;
  }

  // step 5.1:
  // - find tau neutrinos by pdgId (leptonic branch: same sign as complementary lepton)
  std::vector<GenParticleExt> genNuTauFromLepBranch(genNuFromTau.begin(), genNuFromTau.end());
  genNuTauFromLepBranch.erase(
    std::remove_if(genNuTauFromLepBranch.begin(), genNuTauFromLepBranch.end(),
                   [nuLepFromTauSign](const GenParticleExt & nu) -> bool
                   {
                     return nu.pdgId_!= nuLepFromTauSign;
                   }), genNuTauFromLepBranch.end()
  );
  if(! genNuTauFromLepBranch.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_TAU_NUS_FROM_TAU;
    return;
  }
  else if(genNuTauFromLepBranch.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_TAU_NUS;


  // step 5.2:
  std::vector<GenParticleExt> genNuTauFromHadronicBranch(genNuFromTau.begin(), genNuFromTau.end());
  genNuTauFromHadronicBranch.erase(
    std::remove_if(genNuTauFromHadronicBranch.begin(), genNuTauFromHadronicBranch.end(),
                   [nuLepFromTauSign](const GenParticleExt & nu) -> bool
                   {
                     return nu.pdgId_ == nuLepFromTauSign;
                   }), genNuTauFromHadronicBranch.end()
  );
  if(! genNuTauFromHadronicBranch.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_TAU_NUS_FROM_TAU_OPPOSITE_FLAVOR;
    return;
  }
  else if(genNuTauFromHadronicBranch.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_TAU_NUS_OPPOSITE_FLAVOR;

  // step 6:
  // - find oppositely charged tau pairs the mass of which sums up to diTauMass
  std::vector<std::pair<GenParticleExt, GenParticleExt>> genTauPair;
  for(unsigned oIdx = 0; oIdx < genTau.size(); ++oIdx)
    for(unsigned iIdx = oIdx + 1; iIdx < genTau.size(); ++iIdx)
    {
      // Let's construct the 4-momenta for both
      // pt, eta, phi, m
      const GenParticleExt & oTau = genTau[oIdx];
      const GenParticleExt & iTau = genTau[iIdx];
      if(oTau.charge_ * iTau.charge_ > 0 ||
         std::fabs((oTau.p4_ + iTau.p4_).mass() - diTauMass_) > 10.) // let's use large, 10 GeV mass window
        continue;
      if(oTau.charge_ > 0) // so that the 1st tau in the pair is positively charged
        genTauPair.push_back({oTau, iTau});
      else
        genTauPair.push_back({iTau, oTau});
    }
  if(! genTauPair.size()) // expect 1
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_TAU_PAIRS;
    return;
  }
  else if(genTauPair.size() > 1)
    warnCode_ |= NTUPLE_ERR_MORE_THAN_ONE_GEN_TAU_PAIR;

  // step 7:
  // - find leptons coming from top decay
  std::vector<GenParticleExt> genLepFromTopPos(genLepFromTop.begin(), genLepFromTop.end());
  genLepFromTopPos.erase(
    std::remove_if(genLepFromTopPos.begin(), genLepFromTopPos.end(),
                   [](const GenParticleExt & lep) -> bool
                   {
                     return ! (lep.charge_ > 0);
                   }), genLepFromTopPos.end()
  );
  if(! genLepFromTopPos.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_POS_LEPT_FROM_TOP;
    return;
  }
#if ENABLE_DR_CUTS
  genLepFromTopPos.erase(
    std::remove_if(genLepFromTopPos.begin(), genLepFromTopPos.end(),
                   [this, dR](const GenParticleExt & lep) -> bool
                   {
                     for(const auto & selLep: selLeptons_)
                       if(lep.is_overlap(*selLep, dR) &&
                          lep.pdgId_ == selLep -> pdgId_)
                         return false;
                     return true;
                   }), genLepFromTopPos.end()
  );
  if(! genLepFromTopPos.size())
  {
    errCode_ |= NTUPLE_ERR_GEN_POS_LEPT_FROM_TOP_DR;
    return;
  }
#endif
  genLepFromTopPos.erase(
    std::remove_if(genLepFromTopPos.begin(), genLepFromTopPos.end(),
                   [&genNuFromTop](const GenParticleExt & lep) -> bool
                   {
                     for(const GenParticleExt & nu: genNuFromTop)
                       if((std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_) &&
                          lep.pdgId_ * nu.pdgId_ < 0)
                         return false;
                     return true;
                   }), genLepFromTopPos.end()
  );
  if(! genLepFromTopPos.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_POS_LEPT_FROM_TOP_W_MATCHING_NU;
    return;
  }
  else if(genLepFromTopPos.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_GEN_POS_LEPT_FROM_TOP_W_MATCHING_NU;

  std::vector<GenLepton> genLepFromTopNeg(genLepFromTop.begin(), genLepFromTop.end());
  genLepFromTopNeg.erase(
    std::remove_if(genLepFromTopNeg.begin(), genLepFromTopNeg.end(),
                   [](const GenParticleExt & lep) -> bool
                   {
                     return ! (lep.charge_ < 0);
                   }), genLepFromTopNeg.end()
  );
  if(! genLepFromTopNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NEG_LEPT_FROM_TOP;
    return;
  }
#if ENABLE_DR_CUTS
  genLepFromTopNeg.erase(
    std::remove_if(genLepFromTopNeg.begin(), genLepFromTopNeg.end(),
                   [this, dR](const GenParticleExt & lep) -> bool
                   {
                     for(const auto & selLep: selLeptons_)
                       if(lep.is_overlap(*selLep, dR) &&
                          lep.pdgId_ == selLep -> pdgId_)
                         return false;
                     return true;
                   }), genLepFromTopNeg.end()
  );
  if(! genLepFromTopNeg.size())
  {
    errCode_ |= NTUPLE_ERR_GEN_NEG_LEPT_FROM_TOP_DR;
    return;
  }
#endif
  genLepFromTopNeg.erase(
    std::remove_if(genLepFromTopNeg.begin(), genLepFromTopNeg.end(),
                   [&genNuFromTop](const GenParticleExt & lep) -> bool
                   {
                     for(const GenParticleExt & nu: genNuFromTop)
                       if((std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_) &&
                          lep.pdgId_ * nu.pdgId_ < 0)
                         return false;
                     return true;
                   }), genLepFromTopNeg.end()
  );
  if(! genLepFromTopNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NEG_LEPT_FROM_TOP_W_MATCHING_NU;
    return;
  }
  else if(genLepFromTopNeg.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_GEN_NEG_LEPT_FROM_TOP_W_MATCHING_NU;

  // step 8:
  // - find corresponding neutrinos to the leptons coming from top decay
  std::vector<GenParticleExt> genNuFromTopPos(genNuFromTop.begin(), genNuFromTop.end());
  genNuFromTopPos.erase(
    std::remove_if(genNuFromTopPos.begin(), genNuFromTopPos.end(),
                   [&genLepFromTopPos](const GenParticleExt & nu) -> bool
                   {
                     for(const GenParticleExt & lep: genLepFromTopPos)
                       if(nu.pdgId_ * lep.pdgId_ < 0 &&
                          (std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_) &&
                           std::abs(nu.pdgId_) != 16)
                         return false;
                     return true;
                   }), genNuFromTopPos.end()
  );
  if(! genNuFromTopPos.size()) // expect 1
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NU_FROM_POS_TOP;
    return;
  }
  else if(genNuFromTopPos.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_GEN_NU_FROM_POS_TOP;

  std::vector<GenParticleExt> genNuFromTopNeg(genNuFromTop.begin(), genNuFromTop.end());
  genNuFromTopNeg.erase(
    std::remove_if(genNuFromTopNeg.begin(), genNuFromTopNeg.end(),
                   [&genLepFromTopNeg](const GenParticleExt & nu) -> bool
                   {
                     for(const GenParticleExt & lep: genLepFromTopNeg)
                       if(nu.pdgId_ * lep.pdgId_ < 0 &&
                          (std::abs(lep.pdgId_) + 1) == std::abs(nu.pdgId_) &&
                           std::abs(nu.pdgId_) != 16)
                         return false;
                     return true;
                   }), genNuFromTopNeg.end()
  );
  if(! genNuFromTopNeg.size()) // expect 1
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_NU_FROM_NEG_TOP;
    return;
  }
  else if(genNuFromTopNeg.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_GEN_NU_FROM_NEG_TOP;

  // step 9:
  // - try to reconstruct W from lepton and neutrino (top decay branch)
  // step 9.1:
  // - positive top (i.e. anti-top) branch (anti-lepton (positively charged) + neutrino)
  const double massW = 80.385;
  const double gammaW = 3 * 2.085;
  std::vector<std::pair<GenParticleExt, GenParticleExt>> topWdecayProductsPos;
  for(const GenParticleExt & l: genLepFromTopPos)
    for(const GenParticleExt & nu: genNuFromTopPos)
      if(std::fabs(massW - (l.p4_ + nu.p4_).mass()) < gammaW)
        topWdecayProductsPos.push_back({l, nu});
  if(! topWdecayProductsPos.size())
  {
    errCode_ |= NTUPLE_ERR_NOT_POSSIBLE_POS_W_RECONSTRUCTION;
    return;
  }
  else if(topWdecayProductsPos.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_POS_W_CANDIDATES;

  // step 9.2:
  // - negative top (i.e. top) branch (lepton (negatively charged) + anti-neutrino)
  std::vector<std::pair<GenParticleExt, GenParticleExt>> topWdecayProductsNeg;
  for(const GenParticleExt & l: genLepFromTopNeg)
    for(const GenParticleExt & nu: genNuFromTopNeg)
      if(std::fabs(massW - (l.p4_ + nu.p4_).mass()) < gammaW)
        topWdecayProductsNeg.push_back({l, nu});
  if(! topWdecayProductsNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NOT_POSSIBLE_NEG_W_RECONSTRUCTION;
    return;
  }
  else if(topWdecayProductsNeg.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_NEG_W_CANDIDATES;

  // step 10:
  // - try to reconstruct top mass
  const double massTop = 173.21;
  const double gammaTop = 3 * 2.0;
  std::vector<std::tuple<GenParticleExt, GenParticleExt, GenParticleExt>>
    topBranchNeg, topBranchPos;
  for(const GenParticleExt & q: genBQuarkFromTopNeg)
    for(const auto & lnu: topWdecayProductsNeg)
      if(std::fabs((lnu.first.p4_ + lnu.second.p4_ + q.p4_).mass() - massTop) < gammaTop)
        topBranchNeg.push_back(std::make_tuple(q, lnu.first, lnu.second));
  if(! topBranchNeg.size())
  {
    errCode_ |= NTUPLE_ERR_NOT_POSSIBLE_NEG_TOP_RECONSTRUCTION;
    return;
  }
  else if(topBranchNeg.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_NEG_TOP_CANDIDATES;
  for(const GenParticleExt & q: genBQuarkFromTopPos)
    for(const auto & lnu: topWdecayProductsPos)
      if(std::fabs((lnu.first.p4_ + lnu.second.p4_ + q.p4_).mass() - massTop) < gammaTop)
        topBranchPos.push_back(std::make_tuple(q, lnu.first, lnu.second));
  if(! topBranchPos.size())
  {
      errCode_ |= NTUPLE_ERR_NOT_POSSIBLE_POS_TOP_RECONSTRUCTION;
      return;
  }
  else if(topBranchPos.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_POS_TOP_CANDIDATES;

  // step 11:
  // - reconstruct taus individually
  const double gammaTau = 1.5; // it's a huge window, though
  std::vector<std::tuple<GenHadTau, GenParticleExt, GenParticleExt>>
    hadronicBranch;
  std::vector<std::tuple<GenParticleExt, GenParticleExt, GenParticleExt, GenParticleExt>>
    leptonicBranch;
  for(const auto & htauPair: genTauPair)
  {
    const GenParticleExt & tau2htau   = hadTauCharge > 0 ? htauPair.first : htauPair.second;
    const GenParticleExt & tau2lepton = hadTauCharge < 0 ? htauPair.first : htauPair.second;
    for(const GenParticleExt & nu: genNuTauFromHadronicBranch)
        if(std::fabs((nu.p4_ + genHadTaus_[0].p4_).mass() - tau2htau.mass_) < gammaTau)
          hadronicBranch.push_back(std::make_tuple(genHadTaus_[0], nu, tau2htau));
    for(const GenParticleExt & nut: genNuTauFromLepBranch)
      for(const GenParticleExt & nul: genNuLepFromTauCandidates)
        for(const GenParticleExt & lep: genLepFromTauCandidates)
          if(std::fabs((nut.p4_ + nul.p4_ + lep.p4_).mass() - tau2lepton.mass_) < gammaTau)
            leptonicBranch.push_back(std::make_tuple(lep, nul, nut, tau2lepton));
  }
  if(! hadronicBranch.size())
  {
    errCode_ |= NTUPLE_ERR_HADRONICALLY_DECAYING_TAU_RECONSTRUCTION;
    return;
  }
  else if(hadronicBranch.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_TAU_BRANCHES_DECAY_HADRONICALLY;
  if(! leptonicBranch.size())
  {
    errCode_ |= NTUPLE_ERR_LEPTONICALLY_DECAYING_TAU_RECONSTRUCTION;
    return;
  }
  else if(leptonicBranch.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_TAU_BRANCHES_DECAY_LEPTONICALLY;

  // step 12:
  // - select 0th tau decay branch as the branch which has the tau charge positive
  genTauPair.clear();
  const GenParticleExt & genHtau = std::get<2>(hadronicBranch[0]);
  const GenParticleExt & genLtau = std::get<3>(leptonicBranch[0]);
  if(genHtau.charge_ > 0) genTauPair.push_back({ genHtau, genLtau });
  else                    genTauPair.push_back({ genLtau, genHtau });

  // step 13:
  genTaus_f_[0].setValues      (genTauPair[0].first);
  genTaus_f_[1].setValues      (genTauPair[0].second);
  genBQuark_f_[0].setValues    (std::get<0>(topBranchPos[0]));
  genLepFromTop_f_[0].setValues(std::get<1>(topBranchPos[0]));
  genNuFromTop_f_[0].setValues (std::get<2>(topBranchPos[0]));
  genBQuark_f_[1].setValues    (std::get<0>(topBranchNeg[0]));
  genLepFromTop_f_[1].setValues(std::get<1>(topBranchNeg[0]));
  genNuFromTop_f_[1].setValues (std::get<2>(topBranchNeg[0]));
  genHtau_f_.setValues         (std::get<0>(hadronicBranch[0]));
  genNuFromHTau_f_.setValues   (std::get<1>(hadronicBranch[0]));
  genLepFromTau_f_.setValues   (std::get<0>(leptonicBranch[0]));
  genNuLepFromTau_f_.setValues (std::get<1>(leptonicBranch[0]));
  genNuFromLTau_f_.setValues   (std::get<2>(leptonicBranch[0]));
}

void
NtupleFillerMEM::fill(bool force)
{
  if(! errCode_ || force)
    tree_ -> Fill();
  selLeptons_.clear();
  selBJetsMerged_.clear();
  selHadTau_ = 0;
  errCode_ = NTUPLE_ERR_OK;
  warnCode_ = NTUPLE_WARN_OK;
}

void
NtupleFillerMEM::close()
{
  if(file_)
  {
    file_ -> Write();
    delete file_;
    file_ = 0;
    tree_ = 0;
  }
}

bool
NtupleFillerMEM::isHigherCSV(const RecoJet * jet1,
                             const RecoJet * jet2)
{
  return (jet1 -> BtagCSV_) > (jet2 -> BtagCSV_);
}

