# tth-htt
code and python config files for ttH, H -> tautau analysis with matrix element techniques
### Setup

Set up your CMSSW working environment, do `scram b -j8` in `$CMSSW_BASE/src`. Then proceed with
```bash
mkdir -p tth_cutflow && cd $_ # make a folder (of any name, e.g. "tth_cutflow") somewhere
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/RunCuts.py # create jobs and cfgs
./run_cuts.sh # run the jobs; wait
watch -n5 squeue -u `whoami` # check your SLURM queue real time
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/FormatResults.py # once ready, create the cutflow table
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/Diff.py # difference table
```
Now you should have two files in your `$PWD`: the cutflow table `cutflow.txt` and the difference table `diff.txt`. Above Python commands and `sbatch` jobs will overwrite the existing files, so make a copy of your `*.txt`s.
