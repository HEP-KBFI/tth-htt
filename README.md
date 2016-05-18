# tth-htt
code and python config files for ttH, H -> tautau analysis with matrix element techniques
### Setup

Clone this repository into `$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau`, i.e. `git clone git@github.com:HEP-KBFI/tth-htt.git $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau`.
Set up your CMSSW working environment, do `scram b -j8` in `$CMSSW_BASE/src`.

### Running the analysis

Review the `__main__` section in `$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test/tthAnalyzeRun.py`:
```python
cfg = analyzeConfig(output_dir = "/home/user/test",
                    exec_name = "analyze_2lss_1tau",
                    charge_selection = "SS",              # or "OS"
                    lepton_selection = "Tight",           # or "Loose", "Fakeable"
                    max_files_per_job = 30,
                    use_lumi = True,                      # if False, creates unweighted histograms
                    debug = False,                        # if True, checks the presence of all input Ntuples
                    running_method = "sbatch",            # or "Makefile"
                    nof_parallel_jobs = 10,
                    poll_interval = 30,                   # job checking update interval in seconds
                    prep_dcard_exec = "prepareDatacards",
                    histogram_to_fit = "mvaDiscr_2lss")
```
Run the file with `python tthAnalyzeRun.py` and wait until you're prompted to run the job exectution, e.g.
```text
Run sbatch, hadder and prepareDatacards? [Y/n]
```
Press enter and wait til the script tells you `"Done"`. Or, you could decline and run `sbatch`/`make` separately. All the results are stored in `output_dir` defined in `tthAnalyzeRun.py`:
<details> 
  <summary>Directory structure</summary>/home/user/test
├── cfgs
│   └── 2lss_1tau_SS_Tight
│       ├── DoubleEG_Run2015C
│       │   ├── DoubleEG_Run2015C_0.py
│       │   └── DoubleEG_Run2015C_1.py
│       ├── DoubleEG_Run2015D
│       │   ├── DoubleEG_Run2015D_0.py
│       │   ├── DoubleEG_Run2015D_10.py
│       │   ├── ...
│       ├── WZZ
│       │   └── WZZ_0.py
│       └── ZGTo2LG
│           ├── ZGTo2LG_0.py
│           ├── ZGTo2LG_1.py
│           ├── ZGTo2LG_2.py
│           └── ZGTo2LG_3.py
├── datacards
│   └── 2lss_1tau_SS_Tight
│       └── prepareDatacards.root
├── histograms
│   └── 2lss_1tau_SS_Tight
│       ├── allHistograms.root
│       ├── data_obs
│       │   ├── DoubleEG_Run2015C_SS_Tight_0.root
│       │   ├── DoubleEG_Run2015C_SS_Tight_1.root
│       │   ├── ...
│       ├── TTZ
│       │   └── TTZToLLNuNu_SS_Tight_0.root
│       └── WZ
│           ├── WZTo3LNu_SS_Tight_0.root
│           └── WZTo3LNu_SS_Tight_1.root
├── jobs
│   └── 2lss_1tau_SS_Tight
│       ├── DoubleEG_Run2015C_0.sh
│       ├── DoubleEG_Run2015C_1.sh
│       ├── ...
│       ├── WZTo3LNu_0.sh
│       ├── WZTo3LNu_1.sh
│       ├── WZZ_0.sh
│       ├── ZGTo2LG_0.sh
│       ├── ZGTo2LG_1.sh
│       ├── ZGTo2LG_2.sh
│       └── ZGTo2LG_3.sh
├── logs
│   └── 2lss_1tau_SS_Tight
│       ├── DoubleEG_Run2015C_0-4294967294.out
│       ├── DoubleEG_Run2015C_1-4294967294.out
│       ├── ...
│       ├── WZTo3LNu_0-4294967294.out
│       ├── WZTo3LNu_1-4294967294.out
│       ├── WZZ_0-4294967294.out
│       ├── ZGTo2LG_0-4294967294.out
│       ├── ZGTo2LG_1-4294967294.out
│       ├── ZGTo2LG_2-4294967294.out
│       └── ZGTo2LG_3-4294967294.out
├── sbatch.sh
├── stderr.log
└── stdout.log
</details>
The datacard is located in e.g. `/home/user/test/datacards/2lss_1tau_SS_Tight/prepareDatacards.root`.

### Cutflow tables

Proceed with
```bash
mkdir -p tth_cutflow && cd $_ # make a folder (of any name, e.g. "tth_cutflow") somewhere
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/RunCuts.py # create jobs and cfgs
./run_cuts.sh # run the jobs; wait
watch -n5 squeue -u `whoami` # check your SLURM queue real time
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/FormatResults.py # once ready, create the cutflow table
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/Diff.py # difference table
```
Now you should have two files in your `$PWD`: the cutflow table `cutflow.txt` and the difference table `diff.txt`. Above Python commands and `sbatch` jobs will overwrite the existing files, so make a copy of your `*.txt`s.

### Synchronization

If you want to produce the ntuples for the synchronization exercise, run
```bash
sync_ntuples $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test/sync_ntuples_cfg.py
```
Check the input/output parameters in the configuration file first, though. The resulting sync Ntuple can be compared against the other Ntuples w/ appropriate macros.
