#ifndef KEYTYPES125_H
#define KEYTYPES125_H

#include <Rtypes.h> // Int_t, Long64_t, Float_t

#define RUN_TYPE               UInt_t
#define LUMI_TYPE              UInt_t
#define EVT_TYPE               ULong64_t

#define NLEPTONS_TYPE          Int_t
#define LEPT_PT_TYPE           Float_t
#define LEPT_ETA_TYPE          Float_t
#define LEPT_PHI_TYPE          Float_t
#define LEPT_MASS_TYPE         Float_t
#define LEPT_DXY_TYPE          Float_t
#define LEPT_DZ_TYPE           Float_t
#define LEPT_REL_ISO_TYPE      Float_t
#define LEPT_SIP3D_TYPE        Float_t
#define LEPT_MVA_TTH_TYPE      Float_t
#define LEPT_MED_MU_ID_TYPE    Int_t
#define LEPT_PDG_ID_TYPE       Int_t
#define LEPT_ELE_MVA_ID_TYPE   Int_t
#define LEPT_LOST_HITS_TYPE    Int_t
#define LEPT_LOOSE_ID_TYPE     Int_t
#define LEPT_TIGHT_CHARGE_TYPE Int_t
#define LEPT_CONV_VETO_TYPE    Int_t

#define MET_PT_TYPE            Float_t
#define MET_ETA_TYPE           Float_t
#define MET_PHI_TYPE           Float_t
#define MET_MASS_TYPE          Float_t

#define NJETS_TYPE             Int_t
#define JET_PT_TYPE            Float_t
#define JET_ETA_TYPE           Float_t
#define JET_PHI_TYPE           Float_t
#define JET_MASS_TYPE          Float_t
#define JET_CSV_TYPE           Float_t

#define NTAUS_TYPE             Int_t
#define TAU_PT_TYPE            Float_t
#define TAU_ETA_TYPE           Float_t
#define TAU_PHI_TYPE           Float_t
#define TAU_MASS_TYPE          Float_t
#define TAU_DECMODE_TYPE       Int_t
#define TAU_ID_MVA_TYPE        Int_t
#define TAU_ANTI_E_TYPE        Int_t
#define TAU_ANTI_MU_TYPE       Int_t

#define GEN_NLEPTONS_TYPE      Int_t
#define GEN_PT_TYPE            Float_t
#define GEN_ETA_TYPE           Float_t
#define GEN_PHI_TYPE           Float_t
#define GEN_MASS_TYPE          Float_t
#define GEN_PDG_ID_TYPE        Int_t

#define GEN_NJETS_TYPE         Int_t
#define GEN_JET_PT_TYPE        Float_t
#define GEN_JET_ETA_TYPE       Float_t
#define GEN_JET_PHI_TYPE       Float_t
#define GEN_JET_MASS_TYPE      Float_t

///////////////////////////////////////////////////////

#define RUN_KEY               "run"
#define LUMI_KEY              "lumi"
#define EVT_KEY               "evt"

#define NLEPTONS_KEY          "nselLeptons"
#define LEPT_PT_KEY           "selLeptons_pt"
#define LEPT_ETA_KEY          "selLeptons_eta"
#define LEPT_PHI_KEY          "selLeptons_phi"
#define LEPT_MASS_KEY         "selLeptons_mass"
#define LEPT_DXY_KEY          "selLeptons_dxy"
#define LEPT_DZ_KEY           "selLeptons_dz"
#define LEPT_REL_ISO_KEY      "selLeptons_relIso03"
#define LEPT_SIP3D_KEY        "selLeptons_sip3d"
#define LEPT_MVA_TTH_KEY      "selLeptons_mvaTTH"
#define LEPT_MED_MU_ID_KEY    "selLeptons_mediumMuonId"
#define LEPT_PDG_ID_KEY       "selLeptons_pdgId"
#define LEPT_ELE_MVA_ID_KEY   "selLeptons_eleMVAIdPhys14NonTrig"
#define LEPT_LOST_HITS_KEY    "selLeptons_lostHits"
#define LEPT_LOOSE_ID_KEY     "selLeptons_looseIdPOG"
#define LEPT_TIGHT_CHARGE_KEY "selLeptons_tightCharge"
#define LEPT_CONV_VETO_KEY    "selLeptons_convVeto"

#define MET_PT_KEY            "met_pt"
#define MET_ETA_KEY           "met_eta"
#define MET_PHI_KEY           "met_phi"
#define MET_MASS_KEY          "met_mass"

#define NJETS_KEY             "nJet"
#define JET_PT_KEY            "Jet_pt"
#define JET_ETA_KEY           "Jet_eta"
#define JET_PHI_KEY           "Jet_phi"
#define JET_MASS_KEY          "Jet_mass"
#define JET_CSV_KEY           "Jet_btagCSV"

#define NTAUS_KEY             "nTauGood"
#define TAU_PT_KEY            "TauGood_pt"
#define TAU_ETA_KEY           "TauGood_eta"
#define TAU_PHI_KEY           "TauGood_phi"
#define TAU_MASS_KEY          "TauGood_mass"
#define TAU_DECMODE_KEY       "TauGood_idDecayMode"
#define TAU_ID_MVA_KEY        "TauGood_idMVA"
#define TAU_ANTI_E_KEY        "TauGood_idAntiE"
#define TAU_ANTI_MU_KEY       "TauGood_idAntiMu"

#define GEN_NLEPTONS_KEY      "nGenLep"
#define GEN_PT_KEY            "GenLep_pt"
#define GEN_ETA_KEY           "GenLep_eta"
#define GEN_PHI_KEY           "GenLep_phi"
#define GEN_MASS_KEY          "GenLep_mass"
#define GEN_PDG_ID_KEY        "GenLep_pdgId"

#define GEN_NJETS_KEY         "nGenJet"
#define GEN_JET_PT_KEY        "GenJet_pt"
#define GEN_JET_ETA_KEY       "GenJet_eta"
#define GEN_JET_PHI_KEY       "GenJet_phi"
#define GEN_JET_MASS_KEY      "GenJet_mass"

#endif // KEYTYPES125_H
