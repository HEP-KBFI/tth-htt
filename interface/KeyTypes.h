#ifndef tthAnalysis_HiggsToTauTau_KeyTypes_h
#define tthAnalysis_HiggsToTauTau_KeyTypes_h

#include <Rtypes.h> // UInt_t, ULong64_t, Float_t

#define RUN_TYPE               UInt_t
#define LUMI_TYPE              UInt_t
#define EVT_TYPE               ULong64_t
#define GENHIGGSDECAYMODE_TYPE Float_t

#define PUWEIGHT_TYPE          Float_t
#define GENWEIGHT_TYPE         Float_t

#define MET_PT_TYPE            Float_t
#define MET_ETA_TYPE           Float_t
#define MET_PHI_TYPE           Float_t
#define MET_MASS_TYPE          Float_t
#define MET_COVXX_TYPE         Float_t
#define MET_COVXY_TYPE         Float_t
#define MET_COVYY_TYPE         Float_t

///////////////////////////////////////////////////////

#define RUN_KEY               "run"
#define LUMI_KEY              "lumi"
#define EVT_KEY               "evt"
#define GENHIGGSDECAYMODE_KEY "genHiggsDecayMode"

#define GENWEIGHT_KEY         "genWeight"
#define PUWEIGHT_KEY          "puWeight"

#define MET_PT_KEY            "met_pt"
#define MET_ETA_KEY           "met_eta"
#define MET_PHI_KEY           "met_phi"
#define MET_MASS_KEY          "met_mass"
#define MET_COVXX_KEY         "met_covXX"
#define MET_COVXY_KEY         "met_covXY"
#define MET_COVYY_KEY         "met_covYY"

#endif // tthAnalysis_HiggsToTauTau_KeyTypes_h
