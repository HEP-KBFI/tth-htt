#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau

MEMOutput_2lss_1tau::MEMOutput_2lss_1tau()
  : run_(0)
  , lumi_(0)
  , evt_(0)
  , leadLepton_eta_(0.)
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
  , isValid_(0)
  , errorFlag_(0)
{}

MEMOutput_2lss_1tau::MEMOutput_2lss_1tau(RUN_TYPE run,
					 LUMI_TYPE lumi,
					 EVT_TYPE evt,
					 Float_t leadLepton_eta,
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
					 Int_t isValid,
					 Int_t errorFlag)
  : run_(run)
  , lumi_(lumi)
  , evt_(evt)
  , leadLepton_eta_(leadLepton_eta)
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
  , isValid_(isValid)
  , errorFlag_(errorFlag)
{}

std::ostream& operator<<(std::ostream& stream, const MEMOutput_2lss_1tau& memOutput)
{
  stream << "<MEMOutput (2lss_1tau)>:" << std::endl;
  stream << " run: " << memOutput.run() << ", lumi = " << memOutput.lumi() << ", event = " << memOutput.evt() << std::endl;
  stream << " leading lepton: eta = " << memOutput.leadLepton_eta() << ", phi = " << memOutput.leadLepton_phi() << std::endl;
  stream << " subleading lepton: eta = " << memOutput.subleadLepton_eta() << ", phi = " << memOutput.subleadLepton_phi() << std::endl;
  stream << " hadTau: eta = " << memOutput.hadTau_eta() << ", phi = " << memOutput.hadTau_phi() << std::endl;
  stream << " type = " << memOutput.type() << std::endl;
  stream << " weights:" << std::endl;
  stream << "  ttH = " << memOutput.weight_ttH() << std::endl;
  stream << "  ttZ = " << memOutput.weight_ttZ() << std::endl;
  stream << "  ttZ(Z->ll) = " << memOutput.weight_ttZ_Zll() << std::endl;
  stream << "  tt = " << memOutput.weight_tt() << std::endl;
  stream << " LR = " << memOutput.LR() << std::endl;
  stream << " isValid = " << memOutput.isValid() << std::endl;
  stream << " errorFlag = " << memOutput.errorFlag() << std::endl;
  stream << " cpuTime = " << memOutput.cpuTime() << std::endl;
  stream << " realTime = " << memOutput.realTime() << std::endl;
  return stream;
}
