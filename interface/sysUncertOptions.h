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
  kJetMET_jesUp,                                 kJetMET_jesDown, // total JES
  kJetMET_jesAbsoluteFlavMapUp,                  kJetMET_jesAbsoluteFlavMapDown,
  kJetMET_jesAbsoluteMPFBiasUp,                  kJetMET_jesAbsoluteMPFBiasDown,
  kJetMET_jesAbsoluteSampleUp,                   kJetMET_jesAbsoluteSampleDown, // not in 2016, 2017
  kJetMET_jesAbsoluteScaleUp,                    kJetMET_jesAbsoluteScaleDown,
  kJetMET_jesAbsoluteStatUp,                     kJetMET_jesAbsoluteStatDown,
  kJetMET_jesCorrelationGroupbJESUp,             kJetMET_jesCorrelationGroupbJESDown,
  kJetMET_jesCorrelationGroupFlavorUp,           kJetMET_jesCorrelationGroupFlavorDown,
  kJetMET_jesCorrelationGroupIntercalibrationUp, kJetMET_jesCorrelationGroupIntercalibrationDown,
  kJetMET_jesCorrelationGroupMPFInSituUp,        kJetMET_jesCorrelationGroupMPFInSituDown,
  kJetMET_jesCorrelationGroupUncorrelatedUp,     kJetMET_jesCorrelationGroupUncorrelatedDown,
  kJetMET_jesFlavorPhotonJetUp,                  kJetMET_jesFlavorPhotonJetDown,
  kJetMET_jesFlavorPureBottomUp,                 kJetMET_jesFlavorPureBottomDown,
  kJetMET_jesFlavorPureCharmUp,                  kJetMET_jesFlavorPureCharmDown,
  kJetMET_jesFlavorPureGluonUp,                  kJetMET_jesFlavorPureGluonDown,
  kJetMET_jesFlavorPureQuarkUp,                  kJetMET_jesFlavorPureQuarkDown,
  kJetMET_jesFlavorQCDUp,                        kJetMET_jesFlavorQCDDown,
  kJetMET_jesFlavorZJetUp,                       kJetMET_jesFlavorZJetDown,
  kJetMET_jesFragmentationUp,                    kJetMET_jesFragmentationDown,
  kJetMET_jesPileUpDataMCUp,                     kJetMET_jesPileUpDataMCDown,
  kJetMET_jesPileUpEnvelopeUp,                   kJetMET_jesPileUpEnvelopeDown,
  kJetMET_jesPileUpMuZeroUp,                     kJetMET_jesPileUpMuZeroDown,
  kJetMET_jesPileUpPtBBUp,                       kJetMET_jesPileUpPtBBDown,
  kJetMET_jesPileUpPtEC1Up,                      kJetMET_jesPileUpPtEC1Down,
  kJetMET_jesPileUpPtEC2Up,                      kJetMET_jesPileUpPtEC2Down,
  kJetMET_jesPileUpPtHFUp,                       kJetMET_jesPileUpPtHFDown,
  kJetMET_jesPileUpPtRefUp,                      kJetMET_jesPileUpPtRefDown,
  kJetMET_jesRelativeBalUp,                      kJetMET_jesRelativeBalDown,
  kJetMET_jesRelativeFSRUp,                      kJetMET_jesRelativeFSRDown,
  kJetMET_jesRelativeJEREC1Up,                   kJetMET_jesRelativeJEREC1Down,
  kJetMET_jesRelativeJEREC2Up,                   kJetMET_jesRelativeJEREC2Down,
  kJetMET_jesRelativeJERHFUp,                    kJetMET_jesRelativeJERHFDown,
  kJetMET_jesRelativePtBBUp,                     kJetMET_jesRelativePtBBDown,
  kJetMET_jesRelativePtEC1Up,                    kJetMET_jesRelativePtEC1Down,
  kJetMET_jesRelativePtEC2Up,                    kJetMET_jesRelativePtEC2Down,
  kJetMET_jesRelativePtHFUp,                     kJetMET_jesRelativePtHFDown,
  kJetMET_jesRelativeSampleUp,                   kJetMET_jesRelativeSampleDown,
  kJetMET_jesRelativeStatECUp,                   kJetMET_jesRelativeStatECDown,
  kJetMET_jesRelativeStatFSRUp,                  kJetMET_jesRelativeStatFSRDown,
  kJetMET_jesRelativeStatHFUp,                   kJetMET_jesRelativeStatHFDown,
  kJetMET_jesSinglePionECALUp,                   kJetMET_jesSinglePionECALDown,
  kJetMET_jesSinglePionHCALUp,                   kJetMET_jesSinglePionHCALDown,
  kJetMET_jesSubTotalAbsoluteUp,                 kJetMET_jesSubTotalAbsoluteDown,
  kJetMET_jesSubTotalMCUp,                       kJetMET_jesSubTotalMCDown,
  kJetMET_jesSubTotalPileUpUp,                   kJetMET_jesSubTotalPileUpDown,
  kJetMET_jesSubTotalPtUp,                       kJetMET_jesSubTotalPtDown,
  kJetMET_jesSubTotalRelativeUp,                 kJetMET_jesSubTotalRelativeDown,
  kJetMET_jesSubTotalScaleUp,                    kJetMET_jesSubTotalScaleDown,
  kJetMET_jesTimePtEtaUp,                        kJetMET_jesTimePtEtaDown,
  kJetMET_jesTimeRunBUp,                         kJetMET_jesTimeRunBDown, // not in 2016, 2018
  kJetMET_jesTimeRunBCDUp,                       kJetMET_jesTimeRunBCDDown, // not in 2017, 2018
  kJetMET_jesTimeRunCUp,                         kJetMET_jesTimeRunCDown, // not in 2016, 2018
  kJetMET_jesTimeRunDEUp,                        kJetMET_jesTimeRunDEDown, // not in 2016, 2018
  kJetMET_jesTimeRunEFUp,                        kJetMET_jesTimeRunEFDown, // not in 2017, 2018
  kJetMET_jesTimeRunFUp,                         kJetMET_jesTimeRunFDown, // not in 2016, 2018
  kJetMET_jesTimeRunGHUp,                        kJetMET_jesTimeRunGHDown, // not in 2017, 2018
  kJetMET_jesTotalNoFlavorUp,                    kJetMET_jesTotalNoFlavorDown,
  kJetMET_jesTotalNoFlavorNoTimeUp,              kJetMET_jesTotalNoFlavorNoTimeDown,
  kJetMET_jesTotalNoTimeUp,                      kJetMET_jesTotalNoTimeDown,
  kJetMET_jerUp,                                 kJetMET_jerDown, // total JER
  kJetMET_UnclusteredEnUp,                       kJetMET_UnclusteredEnDown, // unclustered energy (only for MET)
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

enum class TauIDSFsys
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

TauIDSFsys
getTauIDSFsys_option(const std::string & central_or_shift);

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
