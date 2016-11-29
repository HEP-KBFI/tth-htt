from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

config = {
    'user': run_cmd('whoami').strip()
}
