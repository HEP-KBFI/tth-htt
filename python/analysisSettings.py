# Integrated luminosity
lumi_2017 = 41.298e+3 # 1/pb

# Systematic uncertainties

class systematics(object):

  # Basic definitions

  central = [ "central" ]

  JES           = [ "CMS_ttHl_JESUp",           "CMS_ttHl_JESDown"           ]
  JER           = [ "CMS_ttHl_JERUp",           "CMS_ttHl_JERDown"           ]
  UnclusteredEn = [ "CMS_ttHl_UnclusteredEnUp", "CMS_ttHl_UnclusteredEnDown" ]
  tauES         = [ "CMS_ttHl_tauESUp",         "CMS_ttHl_tauESDown"         ]

  class LHE(object):

    class TTH(object):
      x1 = [ "CMS_ttHl_thu_shape_ttH_x1Up", "CMS_ttHl_thu_shape_ttH_x1Down" ]
      y1 = [ "CMS_ttHl_thu_shape_ttH_y1Up", "CMS_ttHl_thu_shape_ttH_y1Down" ]

    class TTW(object):
      x1 = [ "CMS_ttHl_thu_shape_ttW_x1Up", "CMS_ttHl_thu_shape_ttW_x1Down" ]
      y1 = [ "CMS_ttHl_thu_shape_ttW_y1Up", "CMS_ttHl_thu_shape_ttW_y1Down" ]

    class TTZ(object):
      x1 = [ "CMS_ttHl_thu_shape_ttZ_x1Up", "CMS_ttHl_thu_shape_ttZ_x1Down" ]
      y1 = [ "CMS_ttHl_thu_shape_ttZ_y1Up", "CMS_ttHl_thu_shape_ttZ_y1Down" ]

    ttH = TTH().x1 + TTH.y1
    ttW = TTW().x1 + TTW.y1
    ttZ = TTZ().x1 + TTZ.y1

    full = ttH + ttW + ttZ

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
    eta        = [ "CMS_ttHl_FRe_shape_etaUp",        "CMS_ttHl_FRe_shape_etaDown"        ]
    eta_barrel = [ "CMS_ttHl_FRe_shape_eta_barrelUp", "CMS_ttHl_FRe_shape_eta_barrelDown" ]

    full = pt + eta + eta_barrel

  class FakeRate_m_shape(object):
    pt  = [ "CMS_ttHl_FRm_shape_ptUp",  "CMS_ttHl_FRm_shape_ptDown"  ]
    eta = [ "CMS_ttHl_FRm_shape_etaUp", "CMS_ttHl_FRm_shape_etaDown" ]

    full = pt + eta

  class FakeRate_t(object):
    jt_norm  = [ "CMS_ttHl_FRjt_normUp",  "CMS_ttHl_FRjt_normDown"  ]
    jt_shape = [ "CMS_ttHl_FRjt_shapeUp", "CMS_ttHl_FRjt_shapeDown" ]
    et_shift = [ "CMS_ttHl_FRet_shiftUp", "CMS_ttHl_FRet_shiftDown" ]
    mt_shift = [ "CMS_ttHl_FRmt_shiftUp", "CMS_ttHl_FRmt_shiftDown" ]

    full = jt_norm + jt_shape + et_shift + mt_shift

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

  lhe        = LHE()
  btag       = Btag()
  FRe_shape  = FakeRate_e_shape()
  FRm_shape  = FakeRate_m_shape()
  FR_t       = FakeRate_t()
  electron_E = Electron_energy()
  muon_E     = Muon_energy()

  # Analysis-specific definitions

  an_leptonFR   = central + JES + JER         + UnclusteredEn
  an_jetToTauFR = central + JES       + tauES
  an_addMEM     = central + JES + JER + tauES + UnclusteredEn

  an_chargeFlip_e  = central + electron_E.full
  an_chargeFlip_mu = central + muon_E.full

  an_ctrl = central + JES + lhe.full

  an_common   = central + JES + tauES + btag.full + FR_t.full + lhe.full
  # CV: enable the CMS_ttHl_FRe_shape and CMS_ttHl_FRm_shape only if you plan to run compShapeSyst 1!
  an_extended = an_common + FRe_shape.full + FRm_shape.full
