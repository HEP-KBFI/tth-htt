#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerMEM.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()

NtupleFillerMEM::NtupleFillerMEM()
  : file_(0)
  , tree_(0)
  , use2016_(false)
  , met_f_(false)
  , selHadTau_(0)
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
}

void
NtupleFillerMEM::setDiTauMass(double diTauMass)
{
  diTauMass_ = diTauMass;
}

int
NtupleFillerMEM::add(const RLEUnit & rleUnit)
{
  rle_f_.setValues(rleUnit);
  return 0;
}

int
NtupleFillerMEM::add(const METUnit<double> & metUnit)
{
  met_f_.setValues(metUnit);
  return 0;
}

int
NtupleFillerMEM::add(const std::map<std::string, double> mva,
                     double ttV,
                     double ttbar)
{
  mva_f_.setValues(mva);
  ttV_f_.setValue(ttV);
  ttbar_f_.setValue(ttbar);
  return 0;
}

int
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
  {
    for(std::size_t i = 0; i < 2; ++i)
      jets_f_[i].setValues(*selBJetsMerged_[i]);
    return 0;
  }
  std::cerr << " << Error: merged b-jets contains less than two jets\n";
  return 1;
}

int
NtupleFillerMEM::add(const std::vector<const RecoLepton*> & selLeptons)
{
  selLeptons_ = selLeptons;
  if(selLeptons_.size() > 2)
  {
    for(std::size_t i = 0; i < 3; ++i)
      leptons_f_[i].setValues(*selLeptons_[i]);
    return 0;
  }
  std::cerr << " << Error: less than three selected leptons\n";
  return 1;
}

int
NtupleFillerMEM::add(const RecoHadTau * selHadTau)
{
  selHadTau_ = selHadTau;
  if(selHadTau_)
  {
    hTau_f_.setValues(*selHadTau_);
    return 0;
  }
  std::cerr << " << Error: empty selected hadronic tau\n";
  return 1;
}

int
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

  // step 0:
  // - check if all generator level particles are there
  if(genBQuarkFromTop.size() < 2)
  {
    std::cerr << " << No two gen lvl b quarks in the first place\n";
    return 1;
  }
  if(! genLepFromTau.size())
  {
    std::cerr << " << No gen lvl leptons from tau to begin with\n";
    return 1;
  }
  if(! genHadTaus.size())
  {
    std::cerr << " << No generator lvl hadronic taus to begin with\n";
    return 1;
  }
  if(genNuFromTau.size() < 3)
  {
    std::cerr << " << Not enough gen lvl neutrinos from tau to begin with\n";
    return 1;
  }
  if(genTau.size() < 2)
  {
    std::cerr << " << Not enough gen lvl taus\n";
    return 1;
  }
  if(genLepFromTop.size() < 2)
  {
    std::cerr << " << Not enough gen lvl leptons coming from top decay\n";
    return 1;
  }
  if(genNuFromTop.size() < 2)
  {
    std::cerr << " << Not enough gen lvl neutrinos from top to begin with\n";
    return 1;
  }
  if(selBJetsMerged_.size() < 2)
    return 1;
  if(selLeptons_.size() < 3)
    return 1;
  if(! selHadTau_)
    return 1;

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
  if(! genBQuarkFromTopPos.size())
  {
    std::cout << " << No gen lvl b quarks\n";
    return 1;
  }
  genBQuarkFromTopNeg.erase(
    std::remove_if(genBQuarkFromTopNeg.begin(), genBQuarkFromTopNeg.end(),
                   [](const GenParticleExt & q) -> bool
                   {
                     return ! (q.pdgId_ < 0);
                   }), genBQuarkFromTopNeg.end()
  );
  if(! genBQuarkFromTopNeg.size())
  {
    std::cout << " << No gen lvl anti-b quarks\n";
    return 1;
  }
  // do generator level matching
  genBQuarkFromTopPos.erase(
    std::remove_if(genBQuarkFromTopPos.begin(), genBQuarkFromTopPos.end(),
                   [this, dR](const GenParticleExt & q) -> bool
                   {
                     for(const auto & b: selBJetsMerged_)
                      if(q.is_overlap(*b, dR))
                        return false;
                     return true;
                   }), genBQuarkFromTopPos.end()
  );
  if(! genBQuarkFromTopPos.size())
  {
    std::cout << " << No gen lvl b quarks that match selected b-jets\n";
    return 1;
  }
  else if(genBQuarkFromTopPos.size() > 1)
    std::cerr << " << Warning: multiple b-quark candidates\n";

  genBQuarkFromTopNeg.erase(
    std::remove_if(genBQuarkFromTopNeg.begin(), genBQuarkFromTopNeg.end(),
                   [this, dR](const GenParticleExt & q) -> bool
                   {
                     for(const auto & b: selBJetsMerged_)
                      if(q.is_overlap(*b, dR))
                        return false;
                     return true;
                   }), genBQuarkFromTopNeg.end()
   );
  if(! genBQuarkFromTopNeg.size())
  {
    std::cerr << " << No gen lvl anti-b quarks that match selected b-jets\n";
    return 1;
  }
  else if(genBQuarkFromTopNeg.size() > 1)
    std::cout << " << Warning: there are multiple anti-b quark candidates\n";

  // step 2.1:
  // - obtain gen lvl hadronic tau
  std::vector<GenHadTau> genHadTaus_(genHadTaus.begin(), genHadTaus.end());
  genHadTaus_.erase(
    std::remove_if(genHadTaus_.begin(), genHadTaus_.end(),
                   [this, dR](const GenHadTau & hadTau) -> bool
                   {
                     if(selHadTau_ -> is_overlap(hadTau, dR) &&
                        selHadTau_ -> charge_ == hadTau.charge_)
                       return false;
                     return true;
                   }), genHadTaus_.end()
  );
  if(genHadTaus_.size() != 1)
  {
    std::cerr << " << Number of generator lvl hadronic taus matching w/ selected htaus not equal to 1\n";
    return 1;
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
    std::cerr << " << No gen lvl leptons from tau with correct charge (" << complLepCharge << ")\n";
    return 1;
  }
  // do dR matching against selected leptons
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
    std::cerr << " << No gen lvl leptons from tau that match w/ selected leptons\n";
    return 1;
  }

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
    std::cerr << " << No gen lvl leptons from tau that have corresponding nu from tau\n";
    return 1;
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
    std::cerr << " << No gen lvl lepton neutrino candidates w/ correct flavor coming from tau decay\n";
    return 1;
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
    std::cerr << " << No gen lvl tau neutrino candidates coming from tau decay\n";
    return 1;
  }
  else if(genNuTauFromLepBranch.size() > 1)
    std::cout << " << Warning: multiple candidates for tau neutrino\n";


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
    std::cerr << " << No gen lvl tau neutrino candidates w/ opposite flavor coming from leptonic tau decay\n";
    return 1;
  }
  else if(genNuTauFromHadronicBranch.size() > 1)
    std::cout << " << Warning: multiple candidates for tau neutrino w/ opposite flavor\n";

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
        return 1;
      if(oTau.charge_ > 0) // so that the 1st tau in the pair is positively charged
        genTauPair.push_back({oTau, iTau});
      else
        genTauPair.push_back({iTau, oTau});
    }
  if(! genTauPair.size()) // expect 1
  {
    std::cerr << " << No proper oppositely charged gen lvl tau pair w/ mass " << diTauMass_ << " GeV\n";
    return 1;
  }
  else if(genTauPair.size() > 1)
    std::cout << " << Warning: multiple candidates for tau pair\n";

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
    std::cerr << " << No gen lvl leptons from top having positive sign\n";
    return 1;
  }
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
    std::cerr << " << No positive gen lvl leptons from top matching w/ selected leptons\n";
    return 1;
  }
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
    std::cerr << " << No positive gen lvl leptons from top having corresponding neutrino\n";
    return 1;
  }
  else if(genLepFromTopPos.size() > 1)
    std::cout << " << Warning: multiple positive lepton candidates coming from top decay\n";

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
    std::cerr << " << No gen lvl leptons from top having positive sign\n";
    return 1;
  }
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
    std::cerr << " << No positive gen lvl leptons from top matching w/ selected leptons\n";
    return 1;
  }
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
    std::cerr << " << No positive gen lvl leptons from top having corresponding neutrino\n";
    return 1;
  }
  else if(genLepFromTopNeg.size() > 1)
    std::cout << " << Warning: multiple negative lepton candidates coming from anti-top decay\n";

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
    std::cerr << " << No proper neutrino coming from top decay\n";
    return 1;
  }
  else if(genNuFromTopPos.size() > 1)
    std::cout << " << Warning: multiple neutrino candidates coming from top decay\n";

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
    std::cerr << " << No proper anti-neutrino coming from top decay\n";
    return 1;
  }
  else if(genNuFromTopNeg.size() > 1)
    std::cout << " << Warning: multiple neutrino candidates coming from anti-top decay\n";

  // step 9:
  // - try to reconstruct W from lepton and neutrino (top decay branch)
  // step 9.1:
  // - positive top (i.e. anti-top) branch (anti-lepton (positively charged) + neutrino)
  const double massW = 80.385;
  const double gammaW = 3 * 2.085;
  std::vector<std::pair<GenParticleExt, GenParticleExt>> topWdecayProductsPos;
  for(const GenParticleExt & l: genLepFromTopPos)
    for(const GenParticleExt & nu: genNuFromTopPos)
    {
      const double massW_qnu = (l.p4_ + nu.p4_).mass();
      std::cout << " << W mass (top branch)      = " << massW_qnu << '\n';
      if(std::fabs(massW - massW_qnu) < gammaW)
        topWdecayProductsPos.push_back({l, nu});
    }
  if(! topWdecayProductsPos.size())
  {
    std::cerr << " << Not possible to reconstruct W from l & nu in top branch\n";
    return 1;
  }
  else if(topWdecayProductsPos.size() > 1)
    std::cout << " << Warning: still too many l & nu candidates in top branch\n";

  // step 9.2:
  // - negative top (i.e. top) branch (lepton (negatively charged) + anti-neutrino)
  std::vector<std::pair<GenParticleExt, GenParticleExt>> topWdecayProductsNeg;
  for(const GenParticleExt & l: genLepFromTopNeg)
    for(const GenParticleExt & nu: genNuFromTopNeg)
    {
      const double massW_qnu = (l.p4_ + nu.p4_).mass();
      std::cout << " << W mass (anti-top branch) = " << massW_qnu << '\n';
      if(std::fabs(massW - massW_qnu) < gammaW)
        topWdecayProductsNeg.push_back({l, nu});
    }
  if(! topWdecayProductsNeg.size())
  {
    std::cerr << " << Not possible to reconstruct W from l & nu in anti-top branch\n";
    return 1;
  }
  else if(topWdecayProductsNeg.size() > 1)
    std::cout << " << Warning: still too many l & nu candidates in anti-top branch\n";

  // step 10:
  // - try to reconstruct top mass
  const double massTop = 173.21;
  const double gammaTop = 3 * 2.0;
  std::vector<std::tuple<GenParticleExt, GenParticleExt, GenParticleExt>>
    topBranchNeg, topBranchPos;
  for(const GenParticleExt & q: genBQuarkFromTopNeg)
    for(const auto & lnu: topWdecayProductsNeg)
    {
      const double massTop_qlnu = (lnu.first.p4_ + lnu.second.p4_ + q.p4_).mass();
      std::cout << " << anti-top mass = " << massTop_qlnu << '\n';
      if(std::fabs(massTop_qlnu - massTop) < gammaTop)
        topBranchNeg.push_back(std::make_tuple(q, lnu.first, lnu.second));
    }
  if(! topBranchNeg.size())
  {
    std::cerr << " << Could not construct anti-top mass\n";
    return 1;
  }
  else if(topBranchNeg.size() > 1)
    std::cout << " << Warning: multiple anti-top branch candidates\n";
  for(const GenParticleExt & q: genBQuarkFromTopPos)
    for(const auto & lnu: topWdecayProductsPos)
    {
      const double massTop_qlnu = (lnu.first.p4_ + lnu.second.p4_ + q.p4_).mass();
      std::cout << " << top mass      = " << massTop_qlnu << '\n';
      if(std::fabs(massTop_qlnu - massTop) < gammaTop)
        topBranchPos.push_back(std::make_tuple(q, lnu.first, lnu.second));
    }
  if(! topBranchPos.size())
  {
    std::cout << " << Could not construct top mass\n";
    return 1;
  }
  else if(topBranchPos.size() > 1)
    std::cout << " << Warning: multiple top branch candidates\n";

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
    std::cerr << " << Could not construct tau mass which decays hadronically\n";
    return 1;
  }
  else if(hadronicBranch.size() > 1)
    std::cout << " << Warning: multiple tau branch candidates which decay hadronically\n";
  if(! leptonicBranch.size())
  {
    std::cerr << " << Could not construct tau mass which decays leptonically\n";
    return 1;
  }
  else if(leptonicBranch.size() > 1)
    std::cout << " << Warning: multiple tau branch candidates which decay leptonically\n";

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

  return 0;
}

void
NtupleFillerMEM::fill()
{
  tree_ -> Fill();

  selLeptons_.clear();
  selBJetsMerged_.clear();
  selHadTau_ = 0;
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

