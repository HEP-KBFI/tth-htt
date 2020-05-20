#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoReader::EventInfoReader(bool read_genHiggsDecayMode,
                                 bool read_puWeight)
  : EventInfoReader(nullptr, read_genHiggsDecayMode, read_puWeight)
{}

EventInfoReader::EventInfoReader(EventInfo * info,
                                 bool read_genHiggsDecayMode,
                                 bool read_puWeight)
  : read_genHiggsDecayMode_(read_genHiggsDecayMode)
  , read_puWeight_(read_puWeight)
  , info_(info)
  , branchName_run("run")
  , branchName_lumi("luminosityBlock")
  , branchName_event("event")
  , branchName_genHiggsDecayMode("genHiggsDecayMode")
  , branchName_genWeight("genWeight")
  , branchName_LHEReweightingWeight("LHEReweightingWeight")
  , branchName_nLHEReweightingWeight(Form("n%s", branchName_LHEReweightingWeight.data()))
  , branchName_gen_mHH("mHH_lhe")
  , branchName_gen_cosThetaStar("cosThetaStar_lhe")
  , branchName_htxs_pt("HTXS_Higgs_pt")
  , branchName_htxs_y("HTXS_Higgs_y")
{}

EventInfoReader::~EventInfoReader()
{
  if(info_ -> is_mc())
  {
    delete[] info_ -> LHEReweightingWeight;
  }
}

void
EventInfoReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  bai.setBranchAddress(info_ -> run, branchName_run);
  bai.setBranchAddress(info_ -> lumi, branchName_lumi);
  bai.setBranchAddress(info_ -> event, branchName_event);
  if(info_ -> is_signal())
  {
    if(info_ -> read_htxs())
    {
      bai.setBranchAddress(info_ -> htxs_.pt_, branchName_htxs_pt);
      bai.setBranchAddress(info_ -> htxs_.y_, branchName_htxs_y);
    }
    if(read_genHiggsDecayMode_)
    {
      bai.setBranchAddress(info_ -> genHiggsDecayMode, branchName_genHiggsDecayMode);
    }
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight, branchName_genWeight);
    if(read_puWeight_)
    {
      bai.setBranchAddress(info_ -> pileupWeight, getBranchName_pileup(PUsys::central));
      bai.setBranchAddress(info_ -> pileupWeightUp, getBranchName_pileup(PUsys::up));
      bai.setBranchAddress(info_ -> pileupWeightDown, getBranchName_pileup(PUsys::down));
    }
    if(info_ -> is_ttbar_rwgt())
    {
      bai.setBranchAddress(info_ -> topPtRwgtSF, branchName_topPtRwgt);
    }
  }
  if(info_ -> is_mc() && ! info_ -> tH_sf.empty())
  {
    BranchAddressInitializer bai_LHEReweight(tree, info_ -> LHEReweightingWeight_max);
    bai_LHEReweight.setBranchAddress(info_ -> nLHEReweightingWeight, branchName_nLHEReweightingWeight);
    bai_LHEReweight.setBranchAddress(info_ -> LHEReweightingWeight, branchName_LHEReweightingWeight);
  }
  if(info_ -> is_hh_nonresonant())
  {
    bai.setBranchAddress(info_ -> gen_mHH, branchName_gen_mHH);
    bai.setBranchAddress(info_ -> gen_cosThetaStar, branchName_gen_cosThetaStar);
  }
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}

void
EventInfoReader::setTopPtRwgtBranchName(const std::string & branchName)
{
  branchName_topPtRwgt = Form("topPtRwgt_%s", branchName.data());
}

std::string
EventInfoReader::getTopPtRwgtBranchName() const
{
  return branchName_topPtRwgt;
}
