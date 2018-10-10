#ifndef SYSUNCEROPTIONS_H
#define SYSUNCEROPTIONS_H

#include <string> // std::string

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

//--- declare systematic uncertainties on data/MC corrections for jet pt & mass
enum
{
  kJet_central_nonNominal,  // for data and sync Ntuples
  kJet_central,             // for MC
  kJet_jesUp, kJet_jesDown,
  kJet_jerUp, kJet_jerDown,
};

//--- declare systematic uncertainties on data/MC corrections for MET
enum
{
  kMEt_central_nonNominal, // for data and sync Ntuples
  kMEt_central,            // for MC
  kMEt_shifted_JetEnUp,         kMEt_shifted_JetEnDown,
  kMEt_shifted_JetResUp,        kMEt_shifted_JetResDown,
  kMEt_shifted_UnclusteredEnUp, kMEt_shifted_UnclusteredEnDown,
};

enum
{
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

enum class TriggerSFsys
{
  central,
  shiftUp, shiftDown,
};

enum
{
  kLHE_scale_central,
  kLHE_scale_xUp, kLHE_scale_xDown,
  kLHE_scale_yUp, kLHE_scale_yDown,
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

enum 
{
  kDYMCReweighting_central,
  kDYMCReweighting_shiftUp, kDYMCReweighting_shiftDown 
};

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

int
getHadTauPt_option(const std::string & central_or_shift);

int
getJetToTauFR_option(const std::string & central_or_shift);

FRet
getEToTauFR_option(const std::string & central_or_shift);

FRmt
getMuToTauFR_option(const std::string & central_or_shift);

TriggerSFsys
getTriggerSF_option(const std::string & central_or_shift);

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

int
getDYMCReweighting_option(const std::string & central_or_shift);

void
checkOptionValidity(const std::string & central_or_shift,
                    bool isMC);

std::string
getBranchName_bTagWeight(const std::string & default_collectionName,
                         int era,
                         int central_or_shift);

/**
 * @brief Return branch name to read RecoJet pt and mass
 *
 * isPt -- if true, return pT branch name; if false, return mass branch name
 */
std::string
getBranchName_jetPtMass(const std::string & default_collectionName,
                        int era,
                        int central_or_shift,
                        bool isPt);

/**
 * @brief Return branch name to read MEt pt and phi
 *
 * isPt -- if true, return pT branch name; if false, return phi branch name
 */
std::string
getBranchName_MEt(const std::string & default_branchName,
                  int era,
                  int central_or_shift,
                  bool isPt);

/**
 * @brief Return branch name to read PU weights
 */
std::string
getBranchName_pileup(PUsys puSys_option);

#endif // SYSUNCEROPTIONS_H
