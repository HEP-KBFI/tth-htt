from tthAnalysis.NanoAOD.triggers import Triggers

trigger_runs_2016 = Triggers('2016').runs
trigger_runs_2017 = Triggers('2017').runs
trigger_runs_2018 = Triggers('2018').runs

# Integrated luminosity

# Reproduced https://github.com/HEP-KBFI/tth-nanoAOD/blob/dde7a1e5640f7a66ad635cb6f618dd1119bc1244/test/datasets/txt/datasets_data_2016_17Jul18.txt#L50
# Official figures: https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/688.html & PAS LUM-17-001
lumi_2016 = 35.922e+3 # 1/pb (uncertainty: 2.5%)

# Reproduced https://github.com/HEP-KBFI/tth-nanoAOD/blob/dde7a1e5640f7a66ad635cb6f618dd1119bc1244/test/datasets/txt/datasets_data_2017_31Mar18.txt#L38
# Official figures: https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/761/1.html & PAS LUM-17-004
lumi_2017 = 41.529e+3 # 1/pb (uncertainty: 2.3%)

# Reproduced https://github.com/HEP-KBFI/tth-nanoAOD/blob/dde7a1e5640f7a66ad635cb6f618dd1119bc1244/test/datasets/txt/datasets_data_2018_17Sep18.txt#L24
# Official figures: https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/860.html & PAS LUM-18-002
lumi_2018 = 59.741e+3 # 1/pb (uncertainty: 2.5%)

# Reproduced

def get_lumi(era):
  if era == "2016":
    return lumi_2016
  elif era == "2017":
    return lumi_2017
  elif era == "2018":
    return lumi_2018
  else:
    raise ValueError("Invalid era: %s" % era)

# Systematic uncertainties

class systematics(object):

  # Basic definitions

  central = [ "central" ]

  JES                  = [ "CMS_ttHl_JESUp",                  "CMS_ttHl_JESDown"                  ]
  JER                  = [ "CMS_ttHl_JERUp",                  "CMS_ttHl_JERDown"                  ]
  UnclusteredEn        = [ "CMS_ttHl_UnclusteredEnUp",        "CMS_ttHl_UnclusteredEnDown"        ]
  tauES                = [ "CMS_ttHl_tauESUp",                "CMS_ttHl_tauESDown"                ]
  leptonIDSF           = [ "CMS_ttHl_leptonIDSFUp",           "CMS_ttHl_leptonIDSFDown"           ]
  tauIDSF              = [ "CMS_ttHl_tauIDSFUp",              "CMS_ttHl_tauIDSFDown"              ]
  triggerSF            = [ "CMS_ttHl_triggerUp",              "CMS_ttHl_triggerDown"              ]
  DYMCReweighting      = [ "CMS_ttHl_DYMCReweightingUp",      "CMS_ttHl_DYMCReweightingDown"      ]
  DYMCNormScaleFactors = [ "CMS_ttHl_DYMCNormScaleFactorsUp", "CMS_ttHl_DYMCNormScaleFactorsDown" ]
  MET_ResponseSyst     = [ "MET_RespUp",                      "MET_RespDown"                      ]
  MET_ResolutionSyst   = [ "MET_ResolUp",                     "MET_ResolDown"                     ]

  JEC_regrouped = [
    "CMS_ttHl_JESAbsoluteUp",           "CMS_ttHl_JESAbsoluteDown",
    "CMS_ttHl_JESAbsolute_EraUp",       "CMS_ttHl_JESAbsolute_EraDown",
    "CMS_ttHl_JESBBEC1Up",              "CMS_ttHl_JESBBEC1Down",
    "CMS_ttHl_JESBBEC1_EraUp",          "CMS_ttHl_JESBBEC1_EraDown",
    "CMS_ttHl_JESEC2Up",                "CMS_ttHl_JESEC2Down",
    "CMS_ttHl_JESEC2_EraUp",            "CMS_ttHl_JESEC2_EraDown",
    "CMS_ttHl_JESFlavorQCDUp",          "CMS_ttHl_JESFlavorQCDDown",
    "CMS_ttHl_JESHFUp",                 "CMS_ttHl_JESHFDown",
    "CMS_ttHl_JESHF_EraUp",             "CMS_ttHl_JESHF_EraDown",
    "CMS_ttHl_JESRelativeBalUp",        "CMS_ttHl_JESRelativeBalDown",
    "CMS_ttHl_JESRelativeSample_EraUp", "CMS_ttHl_JESRelativeSample_EraDown",
  ]

  MEM_3l        = [ "CMS_ttHl_MEM_3l_LRUp",        "CMS_ttHl_MEM_3l_LRDown"        ]
  MEM_2lss_1tau = [ "CMS_ttHl_MEM_2lss_1tau_LRUp", "CMS_ttHl_MEM_2lss_1tau_LRDown" ]
  MEM_3l_1tau   = [ "CMS_ttHl_MEM_3l_1tau_LRUp",   "CMS_ttHl_MEM_3l_1tau_LRDown"   ]
  MEM = MEM_3l + MEM_2lss_1tau + MEM_3l_1tau

  class L1PreFiring_(object):
    up   = "CMS_ttHl_l1PreFireUp"
    down = "CMS_ttHl_l1PreFireDown"
    full = [ up, down ]

  L1PreFiring = L1PreFiring_().full

  class PU_(object):
    up   = "CMS_ttHl_pileupUp"
    down = "CMS_ttHl_pileupDown"
    full = [ up, down ]

  PU = PU_().full

  class topPtReweighting_(object):
    up   = "CMS_ttHl_topPtReweightingUp"
    down = "CMS_ttHl_topPtReweightingDown"
    full = [ up, down ]

  topPtReweighting = topPtReweighting_().full

  class LHE(object):

    class TTH(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_ttH_x1Up"
        down = "CMS_ttHl_thu_shape_ttH_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_ttH_y1Up"
        down = "CMS_ttHl_thu_shape_ttH_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_ttH_Up"
        down = "CMS_ttHl_thu_shape_ttH_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class THQ(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_tHq_x1Up"
        down = "CMS_ttHl_thu_shape_tHq_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_tHq_y1Up"
        down = "CMS_ttHl_thu_shape_tHq_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_tHq_Up"
        down = "CMS_ttHl_thu_shape_tHq_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class THW(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_tHW_x1Up"
        down = "CMS_ttHl_thu_shape_tHW_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_tHW_y1Up"
        down = "CMS_ttHl_thu_shape_tHW_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_tHW_Up"
        down = "CMS_ttHl_thu_shape_tHW_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class TTW(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_ttW_x1Up"
        down = "CMS_ttHl_thu_shape_ttW_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_ttW_y1Up"
        down = "CMS_ttHl_thu_shape_ttW_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_ttW_Up"
        down = "CMS_ttHl_thu_shape_ttW_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class TTZ(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_ttZ_x1Up"
        down = "CMS_ttHl_thu_shape_ttZ_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_ttZ_y1Up"
        down = "CMS_ttHl_thu_shape_ttZ_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_ttZ_Up"
        down = "CMS_ttHl_thu_shape_ttZ_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class HH(object):
      class x1_(object):

        up   = "CMS_ttHl_thu_shape_HH_x1Up"
        down = "CMS_ttHl_thu_shape_HH_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_HH_y1Up"
        down = "CMS_ttHl_thu_shape_HH_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_HH_Up"
        down = "CMS_ttHl_thu_shape_HH_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class DY(object):
      class x1_(object):

        up   = "CMS_ttHl_thu_shape_DY_x1Up"
        down = "CMS_ttHl_thu_shape_DY_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_DY_y1Up"
        down = "CMS_ttHl_thu_shape_DY_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_DY_Up"
        down = "CMS_ttHl_thu_shape_DY_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    class TT(object):
      class x1_(object):

        up   = "CMS_ttHl_thu_shape_TT_x1Up"
        down = "CMS_ttHl_thu_shape_TT_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_TT_y1Up"
        down = "CMS_ttHl_thu_shape_TT_y1Down"
        full = [ up, down ]

      class env_(object):
        up   = "CMS_ttHl_thu_shape_TT_Up"
        down = "CMS_ttHl_thu_shape_TT_Down"
        full = [ up, down ]

      full = x1_().full + y1_().full + env_().full

    ttH   = TTH().full
    tHq   = THQ().full
    tHW   = THW().full
    ttW   = TTW().full
    ttZ   = TTZ().full
    hh    = HH().full
    dy    = DY().full
    ttbar = TT().full

    x1_up    = [ TTH().x1_().up,    THQ().x1_().up,    THW().x1_().up,    TTW().x1_().up,    TTZ().x1_().up,    HH().x1_().up,    DY().x1_().up,    TT().x1_().up    ]
    y1_up    = [ TTH().y1_().up,    THQ().y1_().up,    THW().y1_().up,    TTW().y1_().up,    TTZ().y1_().up,    HH().y1_().up,    DY().y1_().up,    TT().y1_().up    ]
    x1_down  = [ TTH().x1_().down,  THQ().x1_().down,  THW().x1_().down,  TTW().x1_().down,  TTZ().x1_().down,  HH().x1_().down,  DY().x1_().down,  TT().x1_().down  ]
    y1_down  = [ TTH().y1_().down,  THQ().y1_().down,  THW().y1_().down,  TTW().y1_().down,  TTZ().y1_().down,  HH().y1_().down,  DY().y1_().down,  TT().y1_().down  ]
    env_up   = [ TTH().env_().up,   THQ().env_().up,   THW().env_().up,   TTW().env_().up,   TTZ().env_().up,   HH().env_().up,   DY().env_().up,   TT().env_().up   ]
    env_down = [ TTH().env_().down, THQ().env_().down, THW().env_().down, TTW().env_().down, TTZ().env_().down, HH().env_().down, DY().env_().down, TT().env_().down ]

    full = ttH + tHq + tHW + ttW + ttZ + dy + hh + ttbar

  class Btag(object):

    HF       = [ "CMS_ttHl_btag_HFUp",       "CMS_ttHl_btag_HFDown"       ]
    HFStats1 = [ "CMS_ttHl_btag_HFStats1Up", "CMS_ttHl_btag_HFStats1Down" ]
    HFStats2 = [ "CMS_ttHl_btag_HFStats2Up", "CMS_ttHl_btag_HFStats2Down" ]

    LF       = [ "CMS_ttHl_btag_LFUp",       "CMS_ttHl_btag_LFDown"       ]
    LFStats1 = [ "CMS_ttHl_btag_LFStats1Up", "CMS_ttHl_btag_LFStats1Down" ]
    LFStats2 = [ "CMS_ttHl_btag_LFStats2Up", "CMS_ttHl_btag_LFStats2Down" ]

    cErr1 = [ "CMS_ttHl_btag_cErr1Up", "CMS_ttHl_btag_cErr1Down" ]
    cErr2 = [ "CMS_ttHl_btag_cErr2Up", "CMS_ttHl_btag_cErr2Down" ]

    full = HF + HFStats1 + HFStats2 + LF + LFStats1 + LFStats2 + cErr1 + cErr2

  class FakeRate_e_shape(object):
    pt         = [ "CMS_ttHl_FRe_shape_ptUp",         "CMS_ttHl_FRe_shape_ptDown"         ]
    norm       = [ "CMS_ttHl_FRe_shape_normUp",       "CMS_ttHl_FRe_shape_normDown"       ]
    eta_barrel = [ "CMS_ttHl_FRe_shape_eta_barrelUp", "CMS_ttHl_FRe_shape_eta_barrelDown" ]

    full = pt + norm + eta_barrel

  class FakeRate_m_shape(object):
    pt         = [ "CMS_ttHl_FRm_shape_ptUp",         "CMS_ttHl_FRm_shape_ptDown"         ]
    norm       = [ "CMS_ttHl_FRm_shape_normUp",       "CMS_ttHl_FRm_shape_normDown"       ]
    eta_barrel = [ "CMS_ttHl_FRm_shape_eta_barrelUp", "CMS_ttHl_FRm_shape_eta_barrelDown" ]

    full = pt + norm + eta_barrel

  class FakeRate_t(object):
    jt_norm  = [ "CMS_ttHl_FRjt_normUp",  "CMS_ttHl_FRjt_normDown"  ]
    jt_shape = [ "CMS_ttHl_FRjt_shapeUp", "CMS_ttHl_FRjt_shapeDown" ]
    et_shift = [ "CMS_ttHl_FRet_shiftUp", "CMS_ttHl_FRet_shiftDown" ]
    mt_shift = [ "CMS_ttHl_FRmt_shiftUp", "CMS_ttHl_FRmt_shiftDown" ]

    jt   = jt_norm + jt_shape
    full = jt + et_shift + mt_shift

  class Electron_energy(object):
    ER       = [ "CMS_ttHl_electronERUp",       "CMS_ttHl_electronERDown"       ]
    ESEndcap = [ "CMS_ttHl_electronESEndcapUp", "CMS_ttHl_electronESEndcapDown" ]
    ESBarrel = [ "CMS_ttHl_electronESBarrelUp", "CMS_ttHl_electronESBarrelDown" ]

    full = ER + ESEndcap + ESBarrel

  class Muon_energy(object):
    ER        = [ "CMS_ttHl_muonERUp",        "CMS_ttHl_muonERDown"        ]
    ESBarrel1 = [ "CMS_ttHl_muonESBarrel1Up", "CMS_ttHl_muonESBarrel1Down" ]
    ESBarrel2 = [ "CMS_ttHl_muonESBarrel2Up", "CMS_ttHl_muonESBarrel2Down" ]
    ESEndcap1 = [ "CMS_ttHl_muonESEndcap1Up", "CMS_ttHl_muonESEndcap1Down" ]
    ESEndcap2 = [ "CMS_ttHl_muonESEndcap2Up", "CMS_ttHl_muonESEndcap2Down" ]

    full = ER + ESBarrel1 + ESBarrel2 + ESEndcap1 + ESEndcap2

  lhe        = LHE().full
  btag       = Btag().full
  FRe_shape  = FakeRate_e_shape().full
  FRm_shape  = FakeRate_m_shape().full
  FR_t       = FakeRate_t().full
  electron_E = Electron_energy().full
  muon_E     = Muon_energy().full
  FR_all     = FRe_shape + FRm_shape + FR_t

  # Analysis-specific definitions
  an_leptonFR        =    central +  JES +  JER          + UnclusteredEn  + MET_ResponseSyst +  MET_ResolutionSyst
  an_leptonFR_opts   = [ "central", "JES", "JER",         "UnclusteredEn", "MET_ResponseSyst", "MET_ResolutionSyst" ]
  an_jetToTauFR      =    central +  JES         + tauES                   + tauIDSF
  an_jetToTauFR_opts = [ "central", "JES", "JER",          "UnclusteredEn", "tauIDSF" ]
  an_addMEM          =    central +  JES +  JER +  tauES +  UnclusteredEn
  an_addMEM_opts     = [ "central", "JES", "JER", "tauES", "UnclusteredEn" ]

  an_chargeFlip_e       =    central +  electron_E
  an_chargeFlip_e_opts  = [ "central", "electron_E" ]
  an_chargeFlip_mu      =    central +  muon_E
  an_chargeFlip_mu_opts = [ "central", "muon_E" ]

  an_common      =    central +  JES +  JER +  tauES +  leptonIDSF +  tauIDSF +  UnclusteredEn +  btag +  FR_t +  lhe +  triggerSF +  PU +  DYMCReweighting +  DYMCNormScaleFactors  + L1PreFiring
  an_common_opts = [ "central", "JES", "JER", "tauES", "leptonIDSF", "tauIDSF", "UnclusteredEn", "btag", "FR_t", "lhe", "triggerSF", "PU", "DYMCReweighting", "DYMCNormScaleFactors", "L1PreFiring"]
  # CV: enable the CMS_ttHl_FRe_shape and CMS_ttHl_FRm_shape only if you plan to run compShapeSyst 1!
  an_extended      = an_common      +    FRe_shape +  FRm_shape
  an_extended_opts = an_common_opts + [ "FRe_shape", "FRm_shape" ]

  an_inclusive      =    central +  JES +  JER +  tauES +  UnclusteredEn +  btag
  an_inclusive_opts = [ "central", "JES", "JER", "tauES", "UnclusteredEn", "btag" ]

  # Karl: for HH analysis only
  an_common_hh      = an_common
  an_common_opts_hh = an_common_opts
  an_extended_hh      = an_extended
  an_extended_opts_hh = an_extended_opts

  an_internal_no_mem      =    central +  leptonIDSF +  tauIDSF +  btag +  FR_t +  lhe +  triggerSF +  PU +  L1PreFiring +  FRe_shape +  FRm_shape +  DYMCReweighting  + DYMCNormScaleFactors  + topPtReweighting
  an_internal_opts_no_mem = [ "central", "leptonIDSF", "tauIDSF", "btag", "FR_t", "lhe", "triggerSF", "PU", "L1PreFiring", "FRe_shape", "FRm_shape", "DYMCReweighting", "DYMCNormScaleFactors", "topPtReweighting" ]

  an_internal      = an_internal_no_mem      +    MEM
  an_internal_opts = an_internal_opts_no_mem + [ "MEM" ]
