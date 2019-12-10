#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // MEMsys::

MEMOutput_2lss_1tau::MEMOutput_2lss_1tau()
  : leadLepton_eta_(0.)
  , leadLepton_phi_(0.)
  , subleadLepton_eta_(0.)
  , subleadLepton_phi_(0.)
  , hadTau_eta_(0.)
  , hadTau_phi_(0.)
  , errorFlag_(0)
  , type_(-1)
  , weight_ttH_(-1.)
  , weight_ttH_error_(-1.)
  , weight_ttZ_(-1.)
  , weight_ttZ_error_(-1.)
  , weight_ttZ_Zll_(-1.)
  , weight_ttZ_Zll_error_(-1.)
  , weight_tt_(-1.)
  , weight_tt_error_(-1.)
  , LR_(-1.)
  , LR_error_(-1.)
  , LR_up_(-1.)
  , LR_down_(-1.)
  , ttZ_LR_(-1.)
  , ttZ_LR_error_(-1.)
  , ttZ_LR_up_(-1.)
  , ttZ_LR_down_(-1.)
  , ttbar_LR_(-1.)
  , ttbar_LR_error_(-1.)
  , ttbar_LR_up_(-1.)
  , ttbar_LR_down_(-1.)
  , cpuTime_(-1.)
  , realTime_(-1.)
  , isValid_(0)
  , isValid_ttZ_LR_(0)
  , errorFlag_ttZ_LR_(0)
  , isValid_ttbar_LR_(0)
  , errorFlag_ttbar_LR_(0)
{}

std::map<MEMsys, double>
MEMOutput_2lss_1tau::get_LR_map() const
{
  return {
    { MEMsys::nominal, isValid() ? LR()      : -1. },
    { MEMsys::up,      isValid() ? LR_up()   : -1. },
    { MEMsys::down,    isValid() ? LR_down() : -1. },
  };
}

void
MEMOutput_2lss_1tau::fillInputs(const RecoLepton * leadLepton,
                                const RecoLepton * subleadLepton,
                                const RecoHadTau * hadTau)
{
  leadLepton_eta_    = leadLepton -> eta();
  leadLepton_phi_    = leadLepton -> phi();
  subleadLepton_eta_ = subleadLepton -> eta();
  subleadLepton_phi_ = subleadLepton -> phi();
  hadTau_eta_        = hadTau -> eta();
  hadTau_phi_        = hadTau -> phi();
}

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_2lss_1tau& memOutput)
{
  stream << "<MEMOutput (2lss_1tau)>:\n"
            " "       << memOutput.eventInfo_               << "\n"
            " leading lepton:"
            " eta = " << memOutput.leadLepton_eta_          << ","
            " phi = " << memOutput.leadLepton_phi_          << "\n"
            " subleading lepton:"
            " eta = " << memOutput.subleadLepton_eta_       << ","
            " phi = " << memOutput.subleadLepton_phi_       << "\n"
            " hadTau:"
            " eta = " << memOutput.hadTau_eta_              << ","
            " phi = " << memOutput.hadTau_phi_              << "\n"
            " type = " << memOutput.type()                  << "\n"
            " weights:\n"
            "  ttH = "        << memOutput.weight_ttH()     << " (+/- " << memOutput.weight_ttH_error()     << ")\n"
            "  ttZ = "        << memOutput.weight_ttZ()     << " (+/- " << memOutput.weight_ttZ_error()     << ")\n"
            "  ttZ(Z->ll) = " << memOutput.weight_ttZ_Zll() << " (+/- " << memOutput.weight_ttZ_Zll_error() << ")\n"
            "  tt = "         << memOutput.weight_tt()      << " (+/- " << memOutput.weight_tt_error()      << ")\n"
            " LR = "          << memOutput.LR()             << " (+/- " << memOutput.LR_error()             << ")\n"
            " isValid = "     << memOutput.isValid()        << "\n"
            " errorFlag = "   << memOutput.errorFlag()      << "\n"
            " cpuTime = "     << memOutput.cpuTime()        << "\n"
            " realTime = "    << memOutput.realTime()       << "\n";
  return stream;
}
