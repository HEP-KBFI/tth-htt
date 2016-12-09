#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau

MEMOutput_2lss_1tau::MEMOutput_2lss_1tau()
  : leadLepton_eta_(0.)
  , leadLepton_phi_(0.)
  , subleadLepton_eta_(0.)
  , subleadLepton_phi_(0.)
  , hadTau_eta_(0.)
  , hadTau_phi_(0.)
  , type_(-1)
  , weight_ttH_(-1.)
  , weight_ttZ_(-1.)
  , weight_ttZ_Zll_(-1.)
  , weight_tt_(-1.)
  , LR_(-1.)
  , cpuTime_(-1.)
  , realTime_(-1.)
  , errorFlag_(0)
{}

MEMOutput_2lss_1tau::MEMOutput_2lss_1tau(Float_t leadLepton_eta,
					 Float_t leadLepton_phi,
					 Float_t subleadLepton_eta,
					 Float_t subleadLepton_phi,
					 Float_t hadTau_eta,
					 Float_t hadTau_phi,
					 Int_t type,
					 Float_t weight_ttH,
					 Float_t weight_ttZ,
					 Float_t weight_ttZ_Zll,
					 Float_t weight_tt,
					 Float_t LR,
					 Float_t cpuTime,
					 Float_t realTime,
					 Int_t errorFlag)
  : leadLepton_eta_(leadLepton_eta)
  , leadLepton_phi_(leadLepton_phi)
  , subleadLepton_eta_(subleadLepton_eta)
  , subleadLepton_phi_(subleadLepton_phi)
  , hadTau_eta_(hadTau_eta)
  , hadTau_phi_(hadTau_phi)
  , type_(type)
  , weight_ttH_(weight_ttH)
  , weight_ttZ_(weight_ttZ)
  , weight_ttZ_Zll_(weight_ttZ_Zll)
  , weight_tt_(weight_tt)
  , LR_(LR)
  , cpuTime_(cpuTime)
  , realTime_(realTime)
  , errorFlag_(errorFlag)
{}

void MEMOutput_2lss_1tau::print(std::ostream& stream)
{
  stream << "<MEMOutput (2lss_1tau)>:" << std::endl;
  stream << " leading lepton: eta = " << leadLepton_eta_ << ", phi = " << leadLepton_phi_ << std::endl;
  stream << " subleading lepton: eta = " << subleadLepton_eta_ << ", phi = " << subleadLepton_phi_ << std::endl;
  stream << " hadTau: eta = " << hadTau_eta_ << ", phi = " << hadTau_phi_ << std::endl;
  stream << " type = " << type_ << std::endl;
  stream << " weights:" << std::endl;
  stream << "  ttH = " << weight_ttH_ << std::endl;
  stream << "  ttZ = " << weight_ttZ_ << std::endl;
  stream << "  ttZ(Z->ll) = " << weight_ttZ_Zll_ << std::endl;
  stream << "  tt = " << weight_tt_ << std::endl;
  stream << " LR = " << LR_ << std::endl;
  stream << " errorFlag = " << errorFlag_ << std::endl;
  stream << " cpuTime = " << cpuTime_ << std::endl;
  stream << " realTime = " << realTime_ << std::endl;
}
