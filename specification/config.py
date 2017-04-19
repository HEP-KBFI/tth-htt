import os
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd


# set tests to fastest priority queue
if not os.environ.get('SBATCH_PRIORITY'):
    print('Will run tests in cluster using SBATCH_PRIORITY="prio". For faster execution on Quasar, use SBATCH_PRIORITY="test". ;)')
    os.environ['SBATCH_PRIORITY'] = 'prio'


# initialize properties

user = run_cmd('whoami').strip()
cmssw_base = run_cmd('echo $CMSSW_BASE').strip()
temp_dir = '/home/%s/tmp/' % user
fixtures_dir = '%s/src/tthAnalysis/HiggsToTauTau/specification/fixtures/' % cmssw_base
sbatch_priority = run_cmd('echo $SBATCH_PRIORITY').strip()


# create config

config = {
    'user': user,
    'cmssw_base': cmssw_base,
    'temp_dir': temp_dir,
    'fixtures_dir': fixtures_dir,
    'sbatch_priority': sbatch_priority
}


# output load config so user would know what values might need tuning

print('Started with config: ')
print(config)
