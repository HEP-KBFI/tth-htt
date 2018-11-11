# Integrated luminosity

# Reproduced https://github.com/HEP-KBFI/tth-nanoAOD/blob/756030a1229b9ad037c4ef59f8755537508114e9/test/datasets_data_2016_v1.txt#L50
# Official figures: https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/688.html
lumi_2016 = 35.922e+3 # 1/pb (uncertainty: 2.5%)

# Reproduced https://github.com/HEP-KBFI/tth-nanoAOD/blob/4564463eed45251a4fd274ed754b1a37bae8e98e/test/datasets_data_2017_v2.txt#L33
# Official figures: https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/761/1.html
lumi_2017 = 41.529e+3 # 1/pb (uncertainty: 2.3%)

def get_lumi(era):
  if era == "2016":
    return lumi_2016
  elif era == "2017":
    return lumi_2017
  elif era == "2018":
    raise ValueError("Implement me!")
  else:
    raise ValueError("Invalid era: %s" % era)

# Systematic uncertainties

class systematics(object):

  # Basic definitions

  central = [ "central" ]

  JES             = [ "CMS_ttHl_JESUp",             "CMS_ttHl_JESDown"             ]
  JER             = [ "CMS_ttHl_JERUp",             "CMS_ttHl_JERDown"             ]
  UnclusteredEn   = [ "CMS_ttHl_UnclusteredEnUp",   "CMS_ttHl_UnclusteredEnDown"   ]
  tauES           = [ "CMS_ttHl_tauESUp",           "CMS_ttHl_tauESDown"           ]
  triggerSF       = [ "CMS_ttHl_triggerUp",         "CMS_ttHl_triggerDown"         ]
  DYMCReweighting = [ "CMS_ttHl_DYMCReweightingUp", "CMS_ttHl_DYMCReweightingDown" ]
  DYMCNormScaleFactors = [ "CMS_ttHl_DYMCNormScaleFactorsUp", "CMS_ttHl_DYMCNormScaleFactorsDown" ]

  class PU_(object):
    up   = "CMS_ttHl_pileupUp"
    down = "CMS_ttHl_pileupDown"
    full = [ up, down ]

  PU = PU_().full

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

      full = x1_().full + y1_().full

    class TTW(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_ttW_x1Up"
        down = "CMS_ttHl_thu_shape_ttW_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_ttW_y1Up"
        down = "CMS_ttHl_thu_shape_ttW_y1Down"
        full = [ up, down ]

      full = x1_().full + y1_().full

    class TTZ(object):

      class x1_(object):
        up   = "CMS_ttHl_thu_shape_ttZ_x1Up"
        down = "CMS_ttHl_thu_shape_ttZ_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_ttZ_y1Up"
        down = "CMS_ttHl_thu_shape_ttZ_y1Down"
        full = [ up, down ]

      full = x1_().full + y1_().full

    class HH(object):
      class x1_(object):

        up   = "CMS_ttHl_thu_shape_HH_x1Up"
        down = "CMS_ttHl_thu_shape_HH_x1Down"
        full = [ up, down ]

      class y1_(object):
        up   = "CMS_ttHl_thu_shape_HH_y1Up"
        down = "CMS_ttHl_thu_shape_HH_y1Down"
        full = [ up, down ]

      full = x1_().full + y1_().full

    ttH = TTH().full
    ttW = TTW().full
    ttZ = TTZ().full
    hh  = HH().full

    x1_up   = [ TTH().x1_().up,   TTW().x1_().up,   TTZ().x1_().up,   HH().x1_().up   ]
    y1_up   = [ TTH().y1_().up,   TTW().y1_().up,   TTZ().y1_().up,   HH().y1_().up   ]
    x1_down = [ TTH().x1_().down, TTW().x1_().down, TTZ().x1_().down, HH().x1_().down ]
    y1_down = [ TTH().y1_().down, TTW().y1_().down, TTZ().y1_().down, HH().y1_().down ]

    full = ttH + ttW + ttZ
    full_hh = full + hh

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

  an_leptonFR        =    central +  JES +  JER           + UnclusteredEn
  an_leptonFR_opts   = [ "central", "JES", "JER",          "UnclusteredEn" ]
  an_jetToTauFR      =    central +  JES         + tauES
  an_jetToTauFR_opts = [ "central", "JES", "JER",          "UnclusteredEn" ]
  an_addMEM          =    central +  JES +  JER +  tauES +  UnclusteredEn
  an_addMEM_opts     = [ "central", "JES", "JER", "tauES", "UnclusteredEn" ]

  an_chargeFlip_e       =    central +  electron_E
  an_chargeFlip_e_opts  = [ "central", "electron_E" ]
  an_chargeFlip_mu      =    central +  muon_E
  an_chargeFlip_mu_opts = [ "central", "muon_E" ]

  an_common      =    central +  JES +  JER +  tauES +  UnclusteredEn +  btag +  FR_t +  lhe +  triggerSF +  PU +  DYMCReweighting + DYMCNormScaleFactors
  an_common_opts = [ "central", "JES", "JER", "tauES", "UnclusteredEn", "btag", "FR_t", "lhe", "triggerSF", "PU", "DYMCReweighting", "DYMCNormScaleFactors" ]
  # CV: enable the CMS_ttHl_FRe_shape and CMS_ttHl_FRm_shape only if you plan to run compShapeSyst 1!
  an_extended      = an_common      +    FRe_shape +  FRm_shape
  an_extended_opts = an_common_opts + [ "FRe_shape", "FRm_shape" ]

  an_inclusive      =    central +  JES +  JER +  tauES +  UnclusteredEn +  btag
  an_inclusive_opts = [ "central", "JES", "JER", "tauES", "UnclusteredEn", "btag" ]

  # Karl: for HH analysis only
  lhe_hh = LHE().full_hh
  an_common_hh      =    central +  JES +  JER +  tauES +  UnclusteredEn +  btag +  FR_t +  lhe_hh +  triggerSF +  PU +  DYMCReweighting
  an_common_opts_hh = [ "central", "JES", "JER", "tauES", "UnclusteredEn", "btag", "FR_t", "lhe_hh", "triggerSF", "PU", "DYMCReweighting" ]
  an_extended_hh      = an_common_hh      +    FRe_shape +  FRm_shape
  an_extended_opts_hh = an_common_opts_hh + [ "FRe_shape", "FRm_shape" ]

class Triggers(object):

  def __init__(self, era):

    if era == "2016":
      self.triggers_analysis = {
        '3mu' : {
          'HLT_TripleMu_12_10_5',
        },
        '1e2mu' : {
          'HLT_DiMu9_Ele9_CaloIdL_TrackIdL',
        },
        '2e1mu' : {
          'HLT_Mu8_DiEle12_CaloIdL_TrackIdL',
        },
        '3e' : {
          'HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL',
        },
        '2mu' : {
          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ',
          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ',
        },
        '1e1mu' : {
          'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
          'HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
        },
        '2e' : {
          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
        },
        '1mu' : {
          'HLT_IsoMu22',
          'HLT_IsoTkMu22',
          'HLT_IsoMu22_eta2p1',
          'HLT_IsoTkMu22_eta2p1',
          'HLT_IsoMu24',
          'HLT_IsoTkMu24',
        },
        '1e' : {
          'HLT_Ele25_WPTight_Gsf',
          'HLT_Ele27_WPTight_Gsf',
          'HLT_Ele25_eta2p1_WPTight_Gsf',
          'HLT_Ele27_eta2p1_WPLoose_Gsf',
#          'HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded',
        },
        '1mu1tau' : {
          'HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1',
        },
        '1e1tau' : {
          'HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30',
#          'HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1',
#          'HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20',
        },
        '2tau' : {
          'HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg',
          'HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg',
        },
      }
      self.triggers_leptonFR = {
        '1e' : set(),
        '1mu': {
          'HLT_Mu27',
        },
        '2e' : {
          'HLT_Ele17_CaloIdM_TrackIdM_PFJet30',
          'HLT_Ele12_CaloIdM_TrackIdM_PFJet30',
        },
        '2mu': {
          'HLT_Mu17',
          'HLT_Mu8',
          'HLT_Mu3_PFJet40',
        }
      }
    elif era == "2017":

      self.triggers_analysis = {
        '3mu' : {
          'HLT_TripleMu_12_10_5',
        },
        '1e2mu' : {
#          'HLT_DiMu9_Ele9_CaloIdL_TrackIdL',     # prescale of 2
          'HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ',  # unprescaled
        },
        '2e1mu' : {
          'HLT_Mu8_DiEle12_CaloIdL_TrackIdL',
        },
        '3e' : {
          'HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL',  # has PU dependence
        },
        '2mu' : {
#          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL',             # heavily prescaled throughout 2017 data-taking period
          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ',          # unprescaled in 2017B; heavily prescaled since 2017C
          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',  # introduced in 2017C
        },
        '1e1mu' : {
          'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',  # not present in 2017B
          'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
          'HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
        },
        '2e' : {
          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL',    # higher efficiency than non-DZ; not present in 2017B
          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
        },
        '1mu' : {
          'HLT_IsoMu24',  # not enabled at high lumi
          'HLT_IsoMu27',
        },
        '1e' : {
          'HLT_Ele32_WPTight_Gsf', # not present in 2017BC (or, equivalently, not enabled at high lumi)
          'HLT_Ele35_WPTight_Gsf',
        },
        # CV: tau trigger paths taken from slide 6 of presentation given by Hale Sert at HTT workshop in December 2017
        #    (https://indico.cern.ch/event/684622/contributions/2807071/attachments/1575421/2487940/141217_triggerStatusPlans_hsert.pdf),
        #     except that the 'HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1' path has been dropped,
        #     as it was found to increase the trigger acceptance only marginally
        #    (cf. slide 19 of https://indico.cern.ch/event/683144/contributions/2814995/attachments/1570846/2478034/Ruggles_TauTriggers_TauPOG_20171206_v7.pdf)
        '1mu1tau' : { # stored in SingleMuon dataset
          'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1',
        },
        '1e1tau' : { # stored in SingleElectron dataset
          'HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1',
        },
        '2tau' : { # stored in Tau dataset
          'HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg',
          'HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg',
          'HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg',
          'HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg',
        },
      }

      self.triggers_leptonFR = {
        '1e' : {
          'HLT_Ele8_CaloIdM_TrackIdM_PFJet30',
          'HLT_Ele17_CaloIdM_TrackIdM_PFJet30',
          'HLT_Ele23_CaloIdM_TrackIdM_PFJet30',
        },
        '1mu' : {
          'HLT_Mu27',
          'HLT_Mu20',
          'HLT_Mu3_PFJet40',
        },
        '2e' : set(),
        '2mu' : {
          'HLT_Mu17',
          'HLT_Mu8',
        }
      }

    elif era == "2018":
      raise ValueError("Implement me!")
    else:
      raise ValueError("Invalid era: %s" % era)

    self.triggers_all = {}
    for trigger_name in list(set(self.triggers_analysis.keys()) | set(self.triggers_leptonFR.keys())):
      self.triggers_all[trigger_name] = set()
      if trigger_name in self.triggers_analysis:
        self.triggers_all[trigger_name].update(self.triggers_analysis[trigger_name])
      if trigger_name in self.triggers_leptonFR:
        self.triggers_all[trigger_name].update(self.triggers_leptonFR[trigger_name])

    self.triggers_analysis_flat = { trigger for triggers in self.triggers_analysis for trigger in triggers }
    self.triggers_leptonFR_flat = { trigger for triggers in self.triggers_leptonFR for trigger in triggers }
    self.triggers_flat          = self.triggers_analysis_flat | self.triggers_leptonFR_flat
