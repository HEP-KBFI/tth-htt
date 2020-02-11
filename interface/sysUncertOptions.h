#ifndef SYSUNCEROPTIONS_H
#define SYSUNCEROPTIONS_H

#include <string> // std::string

enum class Btag;

//--- declare systematic uncertainties on data/MC corrections for
//    b-tagging efficiency and mistag rates
enum
{
  kBtag_central,

  kBtag_hfUp,       kBtag_hfDown,
  kBtag_hfStats1Up, kBtag_hfStats1Down,
  kBtag_hfStats2Up, kBtag_hfStats2Down,

  kBtag_lfUp,       kBtag_lfDown,
  kBtag_lfStats1Up, kBtag_lfStats1Down,
  kBtag_lfStats2Up, kBtag_lfStats2Down,

  kBtag_cErr1Up, kBtag_cErr1Down,
  kBtag_cErr2Up, kBtag_cErr2Down,

  kBtag_jesUp, kBtag_jesDown,
};

//--- declare systematic uncertainties on data/MC corrections for jet pt & mass and MET pt & phi
enum
{
  kJetMET_central_nonNominal,  // for data and sync Ntuples
  kJetMET_central,             // for MC
  kJetMET_jesUp,                   kJetMET_jesDown, // total JES
  // regrouped, sources with era in their names are treated as uncorrelated, the remaining are correlated
  kJetMET_jesAbsoluteUp,           kJetMET_jesAbsoluteDown,
  kJetMET_jesAbsolute_EraUp,       kJetMET_jesAbsolute_EraDown,
  kJetMET_jesBBEC1Up,              kJetMET_jesBBEC1Down,
  kJetMET_jesBBEC1_EraUp,          kJetMET_jesBBEC1_EraDown,
  kJetMET_jesEC2Up,                kJetMET_jesEC2Down,
  kJetMET_jesEC2_EraUp,            kJetMET_jesEC2_EraDown,
  kJetMET_jesFlavorQCDUp,          kJetMET_jesFlavorQCDDown,
  kJetMET_jesHFUp,                 kJetMET_jesHFDown,
  kJetMET_jesHF_EraUp,             kJetMET_jesHF_EraDown,
  kJetMET_jesRelativeBalUp,        kJetMET_jesRelativeBalDown,
  kJetMET_jesRelativeSample_EraUp, kJetMET_jesRelativeSample_EraDown,
  // additional sources
  kJetMET_jerUp,                   kJetMET_jerDown, // total JER
  kJetMET_UnclusteredEnUp,         kJetMET_UnclusteredEnDown, // unclustered energy (only for MET)
};

enum class METSyst
{
  central,
  respUp, respDown,
  resolUp, resolDown,
};

enum
{
  kHadTauPt_uncorrected,
  kHadTauPt_central,
  kHadTauPt_shiftUp, kHadTauPt_shiftDown,
};

enum
{
  kFRjt_central,
  kFRjt_normUp,  kFRjt_normDown,
  kFRjt_shapeUp, kFRjt_shapeDown,
};

enum class FRet
{
  central,
  shiftUp, shiftDown,
};

enum class FRmt
{
  central,
  shiftUp, shiftDown,
};

enum class LeptonIDSFsys
{
  central,
  shiftUp, shiftDown,
};

enum class TauIDSFsys
{
  central,
  shiftUp, shiftDown,
};

enum class TriggerSFsys
{
  central,
  shiftUp,        shiftDown,
  shift_2lssUp,   shift_2lssDown,
  shift_3lUp,     shift_3lDown,
  shift_1l1tauUp, shift_1l1tauDown,
  shift_0l2tauUp, shift_0l2tauDown,
};

enum class TriggerSFsysChoice
{
  any,
  leptonOnly,
  hadTauOnly,
};

enum
{
  kLHE_scale_central,
  kLHE_scale_xUp, kLHE_scale_xDown, // factorization scale
  kLHE_scale_yUp, kLHE_scale_yDown, // renormalization scale
  kLHE_scale_Up,  kLHE_scale_Down,  // envelope (Swiss cross + both up + both down)
};

enum
{
  kTopPtReweighting_central,
  kTopPtReweighting_shiftUp, kTopPtReweighting_shiftDown,
};

enum
{
  kElectronPt_central,
  kElectronPt_scaleUp_barrel, kElectronPt_scaleDown_barrel,
  kElectronPt_scaleUp_endcap, kElectronPt_scaleDown_endcap,
  kElectronPt_resUp,          kElectronPt_resDown,
};

enum
{
  kMuon_central,
  kMuon_ERUp,        kMuon_ERDown,
  kMuon_ESBarrel1Up, kMuon_ESBarrel1Down,
  kMuon_ESBarrel2Up, kMuon_ESBarrel2Down,
  kMuon_ESEndcap1Up, kMuon_ESEndcap1Down,
  kMuon_ESEndcap2Up, kMuon_ESEndcap2Down,
};

enum
{
  kFRl_central,
  kFRe_shape_ptUp,         kFRe_shape_ptDown,
  kFRe_shape_normUp,       kFRe_shape_normDown,
  kFRe_shape_eta_barrelUp, kFRe_shape_eta_barrelDown,
  kFRm_shape_ptUp,         kFRm_shape_ptDown,
  kFRm_shape_normUp,       kFRm_shape_normDown,
  kFRm_shape_eta_barrelUp, kFRm_shape_eta_barrelDown,
};

enum class PUsys
{
  central,
  up, down,
};

enum class L1PreFiringWeightSys
{
  nominal, up, down
};

enum
{
  kDYMCReweighting_central,
  kDYMCReweighting_shiftUp, kDYMCReweighting_shiftDown 
};

enum
{
  kDYMCNormScaleFactors_central,
  kDYMCNormScaleFactors_shiftUp, kDYMCNormScaleFactors_shiftDown
};

enum class MEMsys
{
  nominal, up, down
};

bool
isValidJESsource(int era,
                 int central_or_shift);

/**
 * @brief Return branchName to read weights that need to be applied, per jet, to MC events
 *       in order to correct for data/MC differences in b-tagging efficiency and mistag rates
 */
int
getBTagWeight_option(const std::string & central_or_shift);

int
getJet_option(const std::string & central_or_shift,
              bool isMC);

int
getMET_option(const std::string & central_or_shift,
              bool isMC);

METSyst
getMETsyst_option(const std::string & central_or_shift);

int
getHadTauPt_option(const std::string & central_or_shift);

int
getJetToTauFR_option(const std::string & central_or_shift);

FRet
getEToTauFR_option(const std::string & central_or_shift);

FRmt
getMuToTauFR_option(const std::string & central_or_shift);

LeptonIDSFsys
getLeptonIDSFsys_option(const std::string & central_or_shift);

TauIDSFsys
getTauIDSFsys_option(const std::string & central_or_shift);

TriggerSFsys
getTriggerSF_option(const std::string & central_or_shift,
                    TriggerSFsysChoice choice);

int
getLHEscale_option(const std::string & central_or_shift);

int
getElectronPt_option(const std::string & central_or_shift);

int
getMuon_option(const std::string & central_or_shift);

int
getJetToLeptonFR_option(const std::string & central_or_shift);

PUsys
getPUsys_option(const std::string & central_or_shift);

L1PreFiringWeightSys
getL1PreFiringWeightSys_option(const std::string & central_or_shift);

int
getDYMCReweighting_option(const std::string & central_or_shift);

int
getDYMCNormScaleFactors_option(const std::string & central_or_shift);

int
getTopPtReweighting_option(const std::string & central_or_shift);

MEMsys
getMEMsys_option(const std::string & central_or_shift);

void
checkOptionValidity(const std::string & central_or_shift,
                    bool isMC);

std::string
getBranchName_bTagWeight(Btag btag,
                         const std::string & default_collectionName,
                         int central_or_shift);

/**
 * @brief Return branch name to read RecoJet pt and mass
 *
 * isPt -- if true, return pT branch name; if false, return mass branch name
 */
std::string
getBranchName_jetMET(const std::string & default_branchName,
                     int era,
                     int central_or_shift,
                     bool isPt);

/**
 * @brief Return branch name to read PU weights
 */
std::string
getBranchName_pileup(PUsys puSys_option);

#endif // SYSUNCEROPTIONS_H
