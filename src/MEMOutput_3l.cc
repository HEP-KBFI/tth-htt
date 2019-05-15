#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

MEMOutput_3l::MEMOutput_3l()
  : leadLepton_eta_(0.)
  , leadLepton_phi_(0.)
  , subleadLepton_eta_(0.)
  , subleadLepton_phi_(0.)
  , thirdLepton_eta_(0.)
  , thirdLepton_phi_(0.)
  , weight_ttH_(-1.)
  , kinfitscore_ttH_(-1.)
  , weight_tt_(-1.)
  , kinfitscore_tt_(-1.)
  , LR_(-1.)
  , cpuTime_(-1.)
  , realTime_(-1.)
  , isValid_(0)
  , errorFlag_(0)
{}

void
MEMOutput_3l::fillInputs(const RecoLepton * leadLepton,
                         const RecoLepton * subleadLepton,
                         const RecoLepton * thirdLepton)
{
  leadLepton_eta_    = leadLepton -> eta();
  leadLepton_phi_    = leadLepton -> phi();
  subleadLepton_eta_ = subleadLepton -> eta();
  subleadLepton_phi_ = subleadLepton -> phi();
  thirdLepton_eta_   = thirdLepton -> eta();
  thirdLepton_phi_   = thirdLepton -> phi();
}

std::ostream& operator<<(std::ostream& stream,
                         const MEMOutput_3l& memOutput)
{
  stream << "<MEMOutput (3l)>:\n"
            " "       << memOutput.eventInfo_               << "\n"
            " leading lepton:"
            " eta = " << memOutput.leadLepton_eta_          << ","
            " phi = " << memOutput.leadLepton_phi_          << "\n"
            " subleading lepton:"
            " eta = " << memOutput.subleadLepton_eta_       << ","
            " phi = " << memOutput.subleadLepton_phi_       << "\n"
            " third lepton:"
            " eta = " << memOutput.thirdLepton_eta_         << ","
            " phi = " << memOutput.thirdLepton_phi_         << "\n"
            " weights:\n"
            "  ttH = "        << memOutput.weight_ttH()     << " (kinfitscore = " << memOutput.kinfitscore_ttH() << ")\n"
            "  tt = "         << memOutput.weight_tt()      << " (kinfitscore = " << memOutput.kinfitscore_tt()  << ")\n"
            " LR = "          << memOutput.LR()             << "\n"
            " isValid = "     << memOutput.isValid()        << "\n"
            " errorFlag = "   << memOutput.errorFlag()      << "\n"
            " cpuTime = "     << memOutput.cpuTime()        << "\n"
            " realTime = "    << memOutput.realTime()       << "\n";
  return stream;
}
