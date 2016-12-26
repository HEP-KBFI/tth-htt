from tthAnalysis.HiggsToTauTau.jobTools import run_cmd


# initialize properties

user = run_cmd('whoami').strip()
cmssw_base = run_cmd('echo $CMSSW_BASE').strip()
temp_dir = '/home/%s/tmp/' % user
fixtures_dir = '%s/src/tthAnalysis/HiggsToTauTau/specification/fixtures/' % cmssw_base


# create config

config = {
    'user': user,
    'cmssw_base': cmssw_base,
    'temp_dir': temp_dir,
    'fixtures_dir': fixtures_dir
}


# output load config so user would know what values might need tuning

print('Started with config: ')
print(config)
