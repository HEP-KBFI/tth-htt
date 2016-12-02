#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerMEM.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // isHigherPt()

#include <functional> // std::reference_wrapper<>, std::cref()

typedef math::PtEtaPhiMLorentzVector LV;

#define N_GENHADTAU_IDX     0
#define N_GENBQUARK_IDX     1
#define N_GENLEPFROMTAU_IDX 2
#define N_GENNUFROMTAU_IDX  3
#define N_GENTAU_IDX        4
#define N_GENLEPFROMTOP_IDX 5
#define N_GENNUFROMTOP      6
#define N_GENTOP            7
#define N_GENVBOSONS        8

#define TAU_MASS    1.77700000e+00
#define TAU_WIDTH   1.00000000e-03 // deliberately larger
#define HIGGS_MASS  1.25000000e+02
#define HIGGS_WIDTH 6.38233900e-03
#define Z_MASS      9.11880000e+01
#define Z_WIDTH     2.44140400e+00
#define TOP_MASS    1.74300000e+02
#define TOP_WIDTH   1.49150000e+00
#define B_MASS      4.70000000e+00
#define B_WIDTH     5.00000000e-02 // custom
#define W_MASS      8.02673592e+01
#define W_WIDTH     2.04760000e+00

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
  njet_f_.setBranchName("njets");
  njet_f_.initBranch(tree_);
  for(std::size_t i = 0; i < NOF_RECO_JETS; ++i)
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

      genW_f_[i].setBranchName(Form("genW%lu", i + 1));
      genT_f_[i].setBranchName(Form("genTop%lu", i + 1));

      genTaus_f_[i].initBranches(tree_);
      genLepFromTop_f_[i].initBranches(tree_);
      genBQuark_f_[i].initBranches(tree_);
      genNuFromTop_f_[i].initBranches(tree_);

      genW_f_[i].initBranches(tree_);
      genT_f_[i].initBranches(tree_);
    }

    genHtau_f_.setBranchName("genHtau");
    genLepFromTau_f_.setBranchName("genLepFromTau");
    genNuLepFromTau_f_.setBranchName("genNuLepFromTau");
    genNuFromHTau_f_.setBranchName("genNuFromHtau");
    genNuFromLTau_f_.setBranchName("genNuFromLtau");

    genHZ_f_.setBranchName("genHorZ");

    genHtau_f_.initBranches(tree_);
    genLepFromTau_f_.initBranches(tree_);
    genNuLepFromTau_f_.initBranches(tree_);
    genNuFromHTau_f_.initBranches(tree_);
    genNuFromLTau_f_.initBranches(tree_);

    genHZ_f_.initBranches(tree_);
  }
  genMultiplicity_f_[N_GENHADTAU_IDX    ].setBranchName("nGenHadTau");
  genMultiplicity_f_[N_GENBQUARK_IDX    ].setBranchName("nGenBQuarkFromTop");
  genMultiplicity_f_[N_GENLEPFROMTAU_IDX].setBranchName("nGenLepFromTau");
  genMultiplicity_f_[N_GENNUFROMTAU_IDX ].setBranchName("nGenNuFromTau");
  genMultiplicity_f_[N_GENTAU_IDX       ].setBranchName("nGenTau");
  genMultiplicity_f_[N_GENLEPFROMTOP_IDX].setBranchName("nGenLepFromTop");
  genMultiplicity_f_[N_GENNUFROMTOP     ].setBranchName("nGenNuFromTop");
  genMultiplicity_f_[N_GENTOP           ].setBranchName("nGenTop");
  genMultiplicity_f_[N_GENVBOSONS       ].setBranchName("nGenVbosons");
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
NtupleFillerMEM::isSignal(bool isSignal_b)
{
  isSignal_b_ = isSignal_b;
}

void
NtupleFillerMEM::add(double genHiggsDecayMode)
{
  genHiggsDecayMode_.setValue(genHiggsDecayMode);
  if(std::fabs(genHiggsDecayMode - 15.) > 1e-3)
    errCode_ |= NTUPLE_ERR_HIGGS_DECAY_MODE;
}

void
NtupleFillerMEM::add(const RLEUnit & rleUnit)
{
  rle_ = rleUnit;
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
  // update: it turns out that sorting all jets by their CSV score is the most efficient;
  //         thus, using only selJets should do the trick, but let's keep the jets separated
  //         just as a reminder
  std::sort(selBJets_medium_.begin(), selBJets_medium_.end(), isHigherCSV);
  std::sort(selBJets_loose_.begin(), selBJets_loose_.end(), isHigherCSV);
  std::sort(selJets_.begin(), selJets_.end(), isHigherCSV);
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
    const int nRecoJets = std::min(NOF_RECO_JETS, static_cast<int>(selBJetsMerged_.size()));
    njet_f_.setValue(nRecoJets);
    for(int i = 0; i < nRecoJets; ++i)
      jets_f_[i].setValues(*selBJetsMerged_[i]);
    for(int i = nRecoJets; i < NOF_RECO_JETS; ++i)
      jets_f_[i].setValues({0., 0., 0., 0.});
  }
  else
    errCode_ |= NTUPLE_ERR_NO_2_JETS;
}

void
NtupleFillerMEM::add(const std::vector<const RecoLepton*> & selLeptons)
{
  selLeptons_ = selLeptons;
  if(selLeptons_.size() == 3)
    for(std::size_t i = 0; i < 3; ++i)
      leptons_f_[i].setValues(*selLeptons_[i]);
  else
    errCode_ |= NTUPLE_ERR_NO_3_LEPTONS;
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
                     const std::vector<GenLepton> & genNuFromTop,
                     const std::vector<GenLepton> & genTop,
                     const std::vector<GenLepton> & genVbosons)
{
  // STRATEGY
  //  - select the correct underlying generator level event, the objects of which
  //    correspond to the objects in the hard scattering process
  //  - if such event is found, try to find a match
  //  - check the reconstructed masses?

  // perform generator-level matching
  // enable only if era is 2016
  genMultiplicity_f_[N_GENHADTAU_IDX    ].setValue(genHadTaus.size());
  genMultiplicity_f_[N_GENBQUARK_IDX    ].setValue(genBQuarkFromTop.size());
  genMultiplicity_f_[N_GENLEPFROMTAU_IDX].setValue(genLepFromTau.size());
  genMultiplicity_f_[N_GENNUFROMTAU_IDX ].setValue(genNuFromTau.size());
  genMultiplicity_f_[N_GENTAU_IDX       ].setValue(genTau.size());
  genMultiplicity_f_[N_GENLEPFROMTOP_IDX].setValue(genLepFromTop.size());
  genMultiplicity_f_[N_GENNUFROMTOP     ].setValue(genNuFromTop.size());
  genMultiplicity_f_[N_GENTOP           ].setValue(genTop.size());
  genMultiplicity_f_[N_GENVBOSONS       ].setValue(genVbosons.size());

  std::vector<std::reference_wrapper<const GenLepton>> genWbosons;
  for(const GenLepton & genVboson: genVbosons)
    if(std::abs(genVboson.pdgId_) == 24)
      genWbosons.push_back(std::cref(genVboson));

  // step 0 -- check if all generator level particles are there
  if(genTop.size() != 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_GEN_TOPS;
    return;
  }
  if(genBQuarkFromTop.size() != 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_GEN_BQUARKS;
    return;
  }
  if(genWbosons.size() != 2)
  {
    errCode_ |= NUTPLE_ERR_NO_2_GEN_WBOSONS;
    return;
  }
  if(genTau.size() != 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_GEN_TAUS;
    return;
  }
  if(genNuFromTop.size() != 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_GEN_NU_FROM_TOP;
    return;
  }
  if(genLepFromTop.size() != 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_GEN_LEP_FROM_TOP;
    return;
  }
  if(! genHadTaus.size())
  {
    errCode_ |= NTUPLE_ERR_NO_GEN_HAD_TAU;
    return;
  }
  if(genLepFromTau.size() != 1)
  {
    errCode_ |= NTUPLE_ERR_NO_SINGLE_GEN_LEPT_FROM_TAU;
    return;
  }
  if(genNuFromTau.size() != 3)
  {
    errCode_ |= NTUPLE_ERR_NO_3_GEN_NUS_FROM_TAU;
    return;
  }

  if(selBJetsMerged_.size() < 2)
  {
    errCode_ |= NTUPLE_ERR_NO_2_JETS;
    return;
  }
  if(selLeptons_.size() != 3)
  {
    errCode_ |= NTUPLE_ERR_NO_3_LEPTONS;
    return;
  }
  if(! selHadTau_)
  {
    errCode_ |= NTUPLE_ERR_NO_HAD_TAU;
    return;
  }

  if(genTop[0].pdgId_ * genTop[1].pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_SIGN_TOPS;
    return;
  }
  if(genWbosons[0].get().pdgId_ * genWbosons[1].get().pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_SIGN_WS;
    return;
  }
  if(genBQuarkFromTop[0].pdgId_ * genBQuarkFromTop[1].pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_FLAVOR_BQUARKS;
    return;
  }
  if(genTau[0].pdgId_ * genTau[1].pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_SIGN_TAUS;
    return;
  }
  if(genLepFromTop[0].pdgId_ * genLepFromTop[1].pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_SIGN_LEPS_FROM_TOP;
    return;
  }
  if(genNuFromTop[0].pdgId_ * genNuFromTop[1].pdgId_ > 0)
  {
    errCode_ |= NTUPLE_ERR_SAME_FLAVOR_NUS_FROM_TOP;
    return;
  }

//--- particles that end with underscore are ,,less correct'' than the ones w/o the underscore
  const GenLepton & t_    __attribute__((unused)) = genTop[0].pdgId_ > 0 ? genTop[0] : genTop[1];
  const GenLepton & tbar_ __attribute__((unused)) = genTop[0].pdgId_ < 0 ? genTop[0] : genTop[1];

  const GenLepton & Wpos_lep = genLepFromTop[0].pdgId_ < 0 ? genLepFromTop[0] : genLepFromTop[1];
  const GenLepton & Wneg_lep = genLepFromTop[0].pdgId_ > 0 ? genLepFromTop[0] : genLepFromTop[1];
  const GenLepton & Wpos_nu_ = genNuFromTop[0].pdgId_ > 0 ? genNuFromTop[0] : genNuFromTop[1];
  const GenLepton & Wneg_nu_ = genNuFromTop[0].pdgId_ < 0 ? genNuFromTop[0] : genNuFromTop[1];

  const GenLepton Wpos_nu = getNu(Wpos_lep, Wpos_nu_, W_MASS, Wpos_nu_.pdgId_);
  const GenLepton Wneg_nu = getNu(Wneg_lep, Wneg_nu_, W_MASS, Wneg_nu_.pdgId_);

  const GenLepton & Wpos_ = genWbosons[0].get().pdgId_ > 0 ? genWbosons[0] : genWbosons[1];
  const GenLepton & Wneg_ = genWbosons[0].get().pdgId_ < 0 ? genWbosons[0] : genWbosons[1];
  const GenLepton Wpos = GenLepton((Wpos_nu.p4_ + Wpos_lep.p4_), Wpos_.pdgId_);
  const GenLepton Wneg = GenLepton((Wneg_nu.p4_ + Wneg_lep.p4_), Wneg_.pdgId_);
  const GenLepton & b_    = genBQuarkFromTop[0].pdgId_ > 0 ? genBQuarkFromTop[0] : genBQuarkFromTop[1];
  const GenLepton & bbar_ = genBQuarkFromTop[0].pdgId_ < 0 ? genBQuarkFromTop[0] : genBQuarkFromTop[1];
  const GenLepton b    = getB(b_, Wpos, b_.pdgId_);
  const GenLepton bbar = getB(bbar_, Wneg, bbar_.pdgId_);

  const GenLepton & lepFromTau = genLepFromTau[0];
  const GenLepton & tauPos = genTau[0].pdgId_ < 0 ? genTau[0] : genTau[1];
  const GenLepton & tauNeg = genTau[0].pdgId_ > 0 ? genTau[0] : genTau[1];
  const GenLepton & tauL __attribute__((unused)) = lepFromTau.pdgId_ > 0 ? tauNeg : tauPos;
  const GenLepton & tauH = lepFromTau.pdgId_ < 0 ? tauNeg : tauPos;

  std::vector<std::reference_wrapper<const GenLepton>> nuLepFromTau_candidates,
                                                       nuTauFromLTau_candidates,
                                                       nuTauFromHTau_candidates;
  for(const GenLepton & nu: genNuFromTau)
    if(std::abs(nu.pdgId_) == std::abs(lepFromTau.pdgId_) + 1)
      nuLepFromTau_candidates.push_back(std::cref(nu));
    else if(nu.pdgId_ * lepFromTau.pdgId_ > 0)
      nuTauFromLTau_candidates.push_back(std::cref(nu));
    else if(nu.pdgId_ * lepFromTau.pdgId_ < 0)
      nuTauFromHTau_candidates.push_back(std::cref(nu));
    else
      assert(0);
  if(nuLepFromTau_candidates.size() != 1)
  {
    errCode_ |= NUTPLE_ERR_NO_GEN_NU_LEP_FROM_TAU;
    return;
  }
  if(nuTauFromLTau_candidates.size() != 1)
  {
    errCode_ |= NUTPLE_ERR_NO_GEN_NU_LEP_FROM_LTAU;
    return;
  }
  if(nuTauFromHTau_candidates.size() != 1)
  {
    errCode_ |= NUTPLE_ERR_NO_GEN_NU_LEP_FROM_HTAU;
    return;
  }
  const GenLepton & nuLepFromTau_ = nuLepFromTau_candidates[0];
  const GenLepton & nuTauFromLTau_ = nuTauFromLTau_candidates[0];
  const GenLepton & nuTauFromHTau_ = nuTauFromHTau_candidates[0];

  std::vector<std::reference_wrapper<const GenHadTau>> htau_candidates;
  for(const GenHadTau & htau_candidate: genHadTaus)
    if(std::fabs((htau_candidate.p4_ + nuTauFromHTau_.p4_).mass() - tauH.mass_) < 1e-2 &&
       htau_candidate.charge_ == tauH.charge_)
      htau_candidates.push_back(std::cref(htau_candidate));
  if(htau_candidates.size() != 1)
  {
    errCode_ |= NTUPLE_ERR_NO_SINGLE_HADRONIC_TAU;
    return;
  }
  const GenHadTau & htau = htau_candidates[0];

  // step 1 -- exclude the event if taus from Higgs emitted soft particles
  // step 1.1 -- recompute the neutrino energy/momentum so that it adds up to tau lepton with mass 1.777 GeV
  //             when added to its complementary lepton
  const GenLepton nuTauFromHTau = getNu(GenLepton(htau.p4_, 1), nuTauFromHTau_, TAU_MASS, nuTauFromHTau_.pdgId_);
  const GenLepton reco_hTau(htau.p4_ + nuTauFromHTau.p4_, tauH.pdgId_);
  // step 1.2 -- recompute neutrino energy/momentum of both neutrinos coming from tau decaying leptonically so that
  //               a) the sum of two neutrinos plus the lepton adds up to tau w/ mass of 1.777 GeV
  //               b) the sum of both taus adds up to Higgs w/ mass of 125.000 GeV
  //             if the rescaling fails, drop the event anyways (nothing to do about it)
  const double diTauMass  = isSignal_b_ ? HIGGS_MASS : Z_MASS;
  const double diTauWidth = 3 * (isSignal_b_ ? HIGGS_WIDTH : Z_WIDTH); // 3 sigma window
  const std::array<GenLepton, 2> newNus = getNuNu(reco_hTau, lepFromTau, nuLepFromTau_, nuTauFromLTau_, diTauMass);
//--- the order is the same as passed to getNuNu()
  const GenLepton & nuLepFromTau  = newNus[0];
  const GenLepton & nuTauFromLTau = newNus[1];
  const GenLepton reco_lTau(nuLepFromTau.p4_ + nuTauFromLTau.p4_ + lepFromTau.p4_, tauL.pdgId_);
  const GenLepton reco_hz = GenLepton((reco_lTau.p4_ + reco_hTau.p4_), isSignal_b_ ? 25 : 23);
  if(std::fabs(reco_lTau.mass_ - TAU_MASS) > TAU_WIDTH)
  {
    errCode_ |= NTUPLE_ERR_LTAU_MASS_OFF;
    return;
  }
  if(std::fabs(reco_hTau.mass_ - TAU_MASS) > TAU_WIDTH)
  {
    errCode_ |= NTUPLE_ERR_HTAU_MASS_OFF;
    return;
  }
  if(std::fabs(reco_hz.mass_ - diTauMass) > diTauWidth)
  {
    errCode_ |= NTUPLE_ERR_DITAU_MASS_OFF;
    return;
  }

  // step 2 -- exclude the event if W masses don't match (shouldn't happen, though)
  // use the the W and nu from Ntuples b/c we don't want include events in which the lepton
  // comes from a W
  const LV reco_Wpos_ = Wpos_lep.p4_ + Wpos_nu_.p4_;
  const LV reco_Wneg_ = Wneg_lep.p4_ + Wneg_nu_.p4_;
  if(std::fabs(reco_Wpos_.mass() - Wpos_.mass_) > 1e-2)
  {
    errCode_ |= NTUPLE_ERR_WPOS_MASS_NOT_RECONSTRUCTED;
    return;
  }
  if(std::fabs(reco_Wneg_.mass() - Wneg_.mass_) > 1e-2)
  {
    errCode_ |= NTUPLE_ERR_WNEG_MASS_NOT_RECONSTRUCTED;
    return;
  }

  // step 3 -- exclude the event if there's a soft activity due to b quarks
  // use the new W, b/c by construction the resulting particle must have top mass
  // this check should never fail
  const GenLepton t    = GenLepton((Wpos.p4_ + b.p4_), t_.pdgId_);
  const GenLepton tbar = GenLepton((Wneg.p4_ + bbar.p4_), tbar_.pdgId_);
  if(std::fabs(t.mass_ - TOP_MASS) > 3 * TOP_WIDTH)
  {
    errCode_ |= NTUPLE_ERR_T_MASS_OFF;
    return;
  }
  if(std::fabs(tbar.mass_ - TOP_MASS) > 3 * TOP_WIDTH)
  {
    errCode_ |= NTUPLE_ERR_TBAR_MASS_OFF;
    return;
  }

  // step 4 -- find closest by dR, mutually exclusive objects w/ correct sign
  // corresponding to generator level
  //  - hadronic tau
  //  - 2 b-quarks
  //  - 2 leptons from top
  //  - lepton from tau
  // thus, 6 objects in total which we need to match
  // the strategy is the following:
  //  - select the candidates that are withing dR < 0.5 (and have the correct pdg ID)
  //  - if there are no such candidates, abort
  //  - sort the candidates by the dR, select the smallest
  //  - any of the final candidates coincide, abort (not much to do in order to alleviate that)

  // step 4.1 hadronic tau
  // we have required a single hadronic tau in both generator and reconstructed levels
  // the comparison is straightforward: if not withing dR < 0.5 or not a correct sign, abort
  if(selHadTau_ -> charge_ != htau.charge_ || ! selHadTau_ -> is_overlap(htau, 0.5))
  {
    std::cout << rle_.get_str()
              << "\ngenerator hadronic tau: " << htau
              << "\nselected hadronic tau:  " << (*selHadTau_) << '\n';
    errCode_ |= NTUPLE_ERR_HAD_TAU_MISMATCH;
    return;
  }

  // step 4.2 lepton from tau
  std::vector<const RecoLepton *> leptonFromTauCandidates;
  for(const RecoLepton * const lepton: selLeptons_)
    if(lepton -> is_overlap(lepFromTau, 0.5) &&
       lepton -> pdgId_ == lepFromTau.pdgId_)
      leptonFromTauCandidates.push_back(lepton);
  std::sort(
    leptonFromTauCandidates.begin(), leptonFromTauCandidates.end(),
    [&lepFromTau](const RecoLepton * const lhs,
                  const RecoLepton * const rhs) -> bool
    {
      return lhs -> dR(lepFromTau) < rhs -> dR(lepFromTau);
    }
  );
  if(! leptonFromTauCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_LEP_FROM_TAU_MISMATCH;
    return;
  }
  if(leptonFromTauCandidates.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_LEP_FROM_TAU_CANDIDATES;
  const RecoLepton * const leptonFromTauCandidate = leptonFromTauCandidates[0];

  // step 4.3 leptons from top
  std::vector<const RecoLepton *> leptonFromTCandidates,
                                  leptonFromTbarCandidates;
  for(const RecoLepton * const lepton: selLeptons_)
    if(lepton -> is_overlap(Wpos_lep, 0.5) &&
       lepton -> pdgId_ == Wpos_lep.pdgId_)
      leptonFromTCandidates.push_back(lepton);
    else if(lepton -> is_overlap(Wneg_lep, 0.5) &&
            lepton -> pdgId_ == Wneg_lep.pdgId_)
      leptonFromTbarCandidates.push_back(lepton);
  std::sort(
    leptonFromTCandidates.begin(), leptonFromTCandidates.end(),
    [&Wpos_lep](const RecoLepton * const lhs,
                const RecoLepton * const rhs) -> bool
    {
      return lhs -> dR(Wpos_lep) < rhs -> dR(Wpos_lep);
    }
  );
  std::sort(
    leptonFromTbarCandidates.begin(), leptonFromTbarCandidates.end(),
    [&Wneg_lep](const RecoLepton * const lhs,
                const RecoLepton * const rhs) -> bool
    {
      return lhs -> dR(Wneg_lep) < rhs -> dR(Wneg_lep);
    }
  );
  if(! leptonFromTCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_LEP_FROM_T_MISMATCH;
    return;
  }
  if(! leptonFromTbarCandidates.size())
  {
    errCode_ |= NTUPLE_ERR_LEP_FROM_TBAR_MISMATCH;
    return;
  }
  if(leptonFromTCandidates.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_LEP_FROM_T_CANDIDATES;
  if(leptonFromTbarCandidates.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_LEP_FROM_TBAR_CANDIDATES;
  const RecoLepton * const leptonFromTCandidate = leptonFromTCandidates[0];
  const RecoLepton * const leptonFromTbarCandidate = leptonFromTbarCandidates[0];
  if(leptonFromTauCandidate == leptonFromTCandidate ||
     leptonFromTauCandidate == leptonFromTbarCandidate ||
     leptonFromTCandidate == leptonFromTbarCandidate)
  {
    errCode_ |= NTUPLE_ERR_SAME_LEPTON_MULTIPLE_CANDIDATE;
    return;
  }

  // step 4.4 b-quarks & -jets
  // only dR match possible
  std::vector<const RecoJet *> bJetCandidates,
                               bbarJetCandidates;
  std::vector<const RecoJet *> selBJetsMerged_rest;
  if(selBJetsMerged_.size() > NOF_RECO_JETS)
  {
    std::copy(
      selBJetsMerged_.begin() + NOF_RECO_JETS, selBJetsMerged_.end(), std::back_inserter(selBJetsMerged_rest)
    );
    selBJetsMerged_.resize(NOF_RECO_JETS);
  }
  for(const RecoJet * const jet: selBJetsMerged_)
  {
    if(jet -> is_overlap(b, 0.5))
      bJetCandidates.push_back(jet);
    if(jet -> is_overlap(bbar, 0.5))
      bbarJetCandidates.push_back(jet);
  }
  std::sort(
    bJetCandidates.begin(), bJetCandidates.end(),
    [&b](const RecoJet * const lhs,
         const RecoJet * const rhs) -> bool
    {
      return lhs -> dR(b) < rhs -> dR(b);
    }
  );
  std::sort(
    bbarJetCandidates.begin(), bbarJetCandidates.end(),
    [&bbar](const RecoJet * const lhs,
            const RecoJet * const rhs) -> bool
    {
      return lhs -> dR(bbar) < rhs -> dR(bbar);
    }
  );
  if(! bJetCandidates.size())
  {
    std::cout << rle_.get_str()
              << "\ngen b: " << b
              << "\nFirst 2 selected jets\n";
    for(const RecoJet * const jet: selBJetsMerged_)
      std::cout << "\tb jet: " << static_cast<GenParticle>(*jet) << '\n';
    if(selBJetsMerged_rest.size())
    {
      std::cout << "Remaining selected jets\n";
      for(const RecoJet * const jet: selBJetsMerged_rest)
      {
        std::cout << "\tb jet: " << static_cast<GenParticle>(*jet) << "; ";
        if(jet -> is_overlap(b, 0.5))
        {
          std::cout << "PASS";
          warnCode_ |= NTUPLE_WARN_B_MATCH_OUTSIDE_2_SELJETS;
        }
        else
          std::cout << "FAIL";
        std::cout << '\n';
      }
    }
    errCode_ |= NUTPLE_ERR_B_MISMATCH;
    return;
  }
  if(! bbarJetCandidates.size())
  {
    std::cout << rle_.get_str()
              << "\ngen bbar: " << bbar
              << "\nFirst 2 selected jets\n";
    for(const RecoJet * const jet: selBJetsMerged_)
      std::cout << "\tb jet: " << static_cast<GenParticle>(*jet) << '\n';
    if(selBJetsMerged_rest.size())
    {
      std::cout << "Remaining selected jets\n";
      for(const RecoJet * const jet: selBJetsMerged_rest)
      {
        std::cout << "bbar jet: " << static_cast<GenParticle>(*jet) << "; ";
        if(jet -> is_overlap(bbar, 0.5))
        {
          std::cout << "PASS";
          warnCode_ |= NTUPLE_WARN_BBAR_MATCH_OUTSIDE_2_SELJETS;
        }
        else
          std::cout << "FAIL";
        std::cout << '\n';
      }
    }
    errCode_ |= NUTPLE_ERR_BBAR_MISMATCH;
    return;
  }

  if(bJetCandidates.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_B_CANDIDATES;
  if(bbarJetCandidates.size() > 1)
    warnCode_ |= NTUPLE_WARN_MULTIPLE_BBAR_CANDIDATES;
  const RecoJet * const bJetCandidate = bJetCandidates[0];
  const RecoJet * const bbarJetCandidate = bbarJetCandidates[0];
  if(bJetCandidate == bbarJetCandidate)
  {
    errCode_ |= NTUPLE_ERR_SAME_B_BBAR_CANDIDATES;
    return;
  }

  //TODO: check the t, tbar, W+, W-, tau+, tau- and H masses obtained by summing
  //      the 4-momenta of reco selected objects and generator level neutrinos? Nope..

  // step 5 -- fill the branches
  // we need to pass GenLepton object -> must convert the tau 4-momenta to GenLepton
  // obtained by summing individual generator decay products (if we use GenLepton objects
  // stored directly in the root file, the 4-momentum conservation won't necessarily hold)
  // also, fill b (W+) and then bbar (W-), as required by MG ME
  const GenLepton reco_tauPos = lepFromTau.pdgId_ < 0 ? reco_lTau : reco_hTau;
  const GenLepton reco_tauNeg = lepFromTau.pdgId_ > 0 ? reco_lTau : reco_hTau;
  genTaus_f_[0].setValues      (reco_tauPos);
  genTaus_f_[1].setValues      (reco_tauNeg);
  genBQuark_f_[0].setValues    (b);
  genLepFromTop_f_[0].setValues(Wpos_lep);
  genNuFromTop_f_[0].setValues (Wpos_nu);
  genBQuark_f_[1].setValues    (bbar);
  genLepFromTop_f_[1].setValues(Wneg_lep);
  genNuFromTop_f_[1].setValues (Wneg_nu);
  genHtau_f_.setValues         (htau);
  genNuFromHTau_f_.setValues   (nuTauFromHTau);
  genLepFromTau_f_.setValues   (lepFromTau);
  genNuLepFromTau_f_.setValues (nuLepFromTau);
  genNuFromLTau_f_.setValues   (nuTauFromLTau);

//--- not used, but fill anyways (for visual)
  genW_f_[0].setValues         (Wpos);
  genW_f_[1].setValues         (Wneg);
  genT_f_[0].setValues         (t);
  genT_f_[1].setValues         (tbar);
  genHZ_f_.setValues           (reco_hz);
}

void
NtupleFillerMEM::fill(bool force)
{
  if(errCode_ == 0 || force)
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

GenLepton
NtupleFillerMEM::getB(const GenLepton & b,
                      const GenLepton & W,
                      Int_t pdgId)
{
  const double eW = W.p4_.E();
  const double cosThetaWb = b.p4_.Vect().Unit().Dot(W.p4_.Vect().Unit());
  const double alpha = (TOP_MASS * TOP_MASS - B_MASS * B_MASS - W.mass_ * W.mass_) / 2.;

  const double A = alpha / eW / B_MASS;
  const double B = W.p4_.Beta() * cosThetaWb;
  const double A2 = A * A;
  const double B2 = B * B;
  const double Babs = std::fabs(B);
  const double disc = A2 + B2 - 1.;
  const double sep = disc - A2 * B2;

  const double sol1 = (A + Babs * std::sqrt(disc)) / (1. - B2) * B_MASS;
  const double sol2 = (A - Babs * std::sqrt(disc)) / (1. - B2) * B_MASS;

  const double en = [&]() -> double
  {
    if(B > 0. && sep < 0.) // never happens
      return std::fabs(b.p4_.E() - sol1) < std::fabs(b.p4_.E() - sol2) ? sol1 : sol2;
    if(B > 0. && sep >= 0.)
      return sol1;
    if(B <= 0. && sep > 0.)
      return sol2;
    assert(0);
  }();

  const double sol = std::sqrt(en * en - B_MASS * B_MASS);
  const double pt = sol / std::cosh(b.eta_);

  const GenLepton result(pt, b.eta_, b.phi_, B_MASS, pdgId);
  return result;
}

GenLepton
NtupleFillerMEM::getNu(const GenLepton & l,
                       const GenLepton & nu,
                       double momMass,
                       Int_t pdgId)
{
  const double El = l.p4_.E();
  const double ml = l.mass_;
  const double pl = l.p4_.P();
  const double cosThetaLnu = nu.p4_.Vect().Unit().Dot(l.p4_.Vect().Unit());
  assert(El > pl * cosThetaLnu);
  const double Enu =
    (momMass * momMass - ml * ml) / (2 * (El - pl * cosThetaLnu))
  ;
  const double pt = Enu / std::cosh(nu.eta_);
  const GenLepton result(pt, nu.eta_, nu.phi_, 0., pdgId);
  return result;
}

std::array<GenLepton, 2>
NtupleFillerMEM::getNuNu(const GenLepton & tau1,
                         const GenLepton & l,
                         const GenLepton & nu1,
                         const GenLepton & nu2,
                         double momMass)
{
  const double Etau1 = tau1.p4_.E();
  const double El = l.p4_.E();
  const double ptau1 = tau1.p4_.P();
  const double pl = l.p4_.P();
  const double ml = l.mass_;

  const double cosTheta_l_nu1 = l.p4_.Vect().Unit().Dot(nu1.p4_.Vect().Unit());
  const double cosTheta_l_nu2 = l.p4_.Vect().Unit().Dot(nu2.p4_.Vect().Unit());
  const double cosTheta_tau1_nu1 = tau1.p4_.Vect().Unit().Dot(nu1.p4_.Vect().Unit());
  const double cosTheta_l_tau1 = tau1.p4_.Vect().Unit().Dot(l.p4_.Vect().Unit());
  const double cosTheta_tau1_nu2 = tau1.p4_.Vect().Unit().Dot(nu2.p4_.Vect().Unit());
  const double cosTheta_nu1_nu2 = nu1.p4_.Vect().Unit().Dot(nu2.p4_.Vect().Unit());

  const double beta1 = Etau1 - ptau1 * cosTheta_tau1_nu1;
  const double beta2 = Etau1 - ptau1 * cosTheta_tau1_nu2;
  const double beta12 = Etau1 * El - ptau1 * pl * cosTheta_l_tau1;
  const double beta1_ = El - pl * cosTheta_l_nu1;
  const double beta2_ = El - pl * cosTheta_l_nu2;
  const double beta12_ = 1. - cosTheta_nu1_nu2;
  const double alpha = momMass * momMass / 2. - TAU_MASS * TAU_MASS - beta12;
  const double alpha_ = (TAU_MASS * TAU_MASS - ml * ml) / 2.;

  const double a = beta1 * beta12_ / beta2;
  const double b = (beta1 * beta2_ - beta12_ * alpha) / beta2 - beta1_;
  const double c = alpha_ - beta2_ * alpha / beta2;

  const double Enu1_pos = (-b + std::sqrt(b * b - 4. * a * c)) / (2. * a);
  const double Enu1_neg = (-b - std::sqrt(b * b - 4. * a * c)) / (2. * a);

  bool is_valid = true;
  const double Enu1 = [&]{
    if(Enu1_pos > 0. && Enu1_neg > 0.)
      return std::fabs(Enu1_pos - nu1.p4_.E()) < std::fabs(Enu1_neg - nu1.p4_.E()) ? Enu1_pos : Enu1_neg;
    if(Enu1_pos > 0.) return Enu1_pos;
    if(Enu1_neg > 0.) return Enu1_neg;
    is_valid = false;
    return 0.;
  }();
  const double Enu2 = (alpha - Enu1 * beta1) / beta2;
  if(Enu2 <= 0.)
    is_valid = false;

//--- if no correct solution was found (meaning that rescaling neutrino energies doesn't fit the bill:
//--- directions must change as well), then return the original neutrinos instead
  if(! is_valid)
  {
    warnCode_ |= NTUPLE_WARN_HTAUTAU_RESCALING_FAILURE;
    return {{ nu1, nu2 }};
  }

  const double pt1 = Enu1 / std::cosh(nu1.eta_);
  const GenLepton nu1_new(pt1, nu1.eta_, nu1.phi_, 0, nu1.pdgId_);
  const double pt2 = Enu2 / std::cosh(nu2.eta_);
  const GenLepton nu2_new(pt2, nu2.eta_, nu2.phi_, 0, nu2.pdgId_);

  return {{ nu1_new, nu2_new }};
}

bool
NtupleFillerMEM::isHigherCSV(const RecoJet * jet1,
                             const RecoJet * jet2)
{
  return (jet1 -> BtagCSV_) > (jet2 -> BtagCSV_);
}

