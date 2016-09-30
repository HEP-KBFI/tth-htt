# tth-htt
Code and python config files for ttH, H -> tautau analysis with matrix element techniques
### Setup

Clone this repository into `$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau`, i.e.
```bash
git clone git@github.com:HEP-KBFI/tth-htt.git $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau
```
Set up your CMSSW working environment, do `scram b -j8` in `$CMSSW_BASE/src`.

#### Dependencies

One needs to install `ClassicSVfit` and its dependency `SVfitTF` in order to compile the whole project; do
```bash
git clone https://github.com/veelken/ClassicSVfit TauAnalysis/ClassicSVfit
git clone https://github.com/veelken/SVfitTF TauAnalysis/SVfitTF
```
and compile the project..


### Running the analysis

We currently have implemented the analysis for 7 channels (plus charge misid and MVA), the runtime configuration files of which are `test/tthAnalyzeRun*.py`.

Review the `analysis` section in one of these files, e.g. `test/tthAnalyzeRun_3l_1tau.py`:
```python
version = "2016Jul19_dR03mvaTight"

analysis = analyzeConfig_3l_1tau(
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", version),
    executable_analyze = "analyze_3l_1tau",
    lepton_selections = [ "Tight" ],
    hadTau_selection = "dR03mvaTight",
    central_or_shifts = [ "central"],
    max_files_per_job = 30,
    use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    histograms_to_fit = [ "EventCounter", "numJets", "mvaDiscr_3l", "mTauTauVis" ],
    select_rle_output = True)
```
Go to the test folder and run the file:
```bash
cd $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test
python tthAnalyzeRun_3l_1tau.py
```
and wait until you're prompted to run the job exectution, e.g.
```bash
Start jobs ? [Y/n]
```
Press enter and wait til the script tells you `"Done"`. Or, you could decline and run `make` later:
```bash
make -f /home/$USER/ttHAnalysis/2016Jul19_dR03mvaTight/Makefile_3l_1tau -j 4
```
This runs a python script (`sbatch_analyze_3l_1tau.py`) which submits the analysis jobs to SLURM and waits them to complete (approx 30 min per channel).
All the results are stored in `outputDir` defined in `tthAnalyzeRun_3l_1tau.py`:
<details> 
  <summary>Directory structure</summary>
```text
/home/$USER/ttHAnalysis/2016Jul19_dR03mvaTight/
├── cfgs
│   ├── 3l_1tau
│   │   └── Tight
│   │       ├── DoubleEG_Run2015C
│   │       │   ├── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_0_cfg.py
│   │       │   ├── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_0.sh
│   │       │   ├── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_1_cfg.py
│   │       │   └── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_1.sh
│   │       ├── DoubleEG_Run2015D
│   │       │   ├── analyze_3l_1tau_DoubleEG_Run2015D_Tight_central_0_cfg.py
│   │       │   ├── ...
│   │       ...
│   │       └── ZZTo4L
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_0_cfg.py
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_0.sh
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_1_cfg.py
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_1.sh
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_2_cfg.py
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_2.sh
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_3_cfg.py
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_3.sh
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_4_cfg.py
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_4.sh
│   │           ├── analyze_3l_1tau_ZZTo4L_Tight_central_5_cfg.py
│   │           └── analyze_3l_1tau_ZZTo4L_Tight_central_5.sh
│   ├── prepareDatacards_3l_1tau_EventCounter_cfg.py
│   ├── prepareDatacards_3l_1tau_mTauTauVis_cfg.py
│   ├── prepareDatacards_3l_1tau_mvaDiscr_3l_cfg.py
│   └── prepareDatacards_3l_1tau_numJets_cfg.py
├── datacards
│   ├── 3l_1tau
│   │   └── Tight
│   │       ├── DoubleEG_Run2015C
│   │       ├── DoubleEG_Run2015D
│   │       ├── ...
│   │       ├── ZGTo2LG
│   │       └── ZZTo4L
│   ├── prepareDatacards_3l_1tau_EventCounter.root
│   ├── prepareDatacards_3l_1tau_mTauTauVis.root
│   ├── prepareDatacards_3l_1tau_mvaDiscr_3l.root
│   └── prepareDatacards_3l_1tau_numJets.root
├── histograms
│   ├── 3l_1tau
│   │   └── Tight
│   │       ├── DoubleEG_Run2015C
│   │       │   ├── DoubleEG_Run2015C_Tight_central_0.root
│   │       │   └── DoubleEG_Run2015C_Tight_central_1.root
│   │       ├── DoubleEG_Run2015D
│   │       │   ├── DoubleEG_Run2015D_Tight_central_0.root
│   │       │   ├── DoubleEG_Run2015D_Tight_central_10.root
│   │       │   ├── ...
│   │       ...
│   │       └── ZZTo4L
│   │           ├── ZZTo4L_Tight_central_0.root
│   │           ├── ZZTo4L_Tight_central_1.root
│   │           ├── ZZTo4L_Tight_central_2.root
│   │           ├── ZZTo4L_Tight_central_3.root
│   │           ├── ZZTo4L_Tight_central_4.root
│   │           └── ZZTo4L_Tight_central_5.root
│   ├── histograms_harvested_stage1_3l_1tau_DoubleEG_Run2015C.root
│   ├── histograms_harvested_stage1_3l_1tau_DoubleEG_Run2015C_Tight_central.root
│   ├── ...
│   ├── histograms_harvested_stage1_3l_1tau_ZZTo4L.root
│   ├── histograms_harvested_stage1_3l_1tau_ZZTo4L_Tight_central.root
│   └── histograms_harvested_stage2_3l_1tau.root
├── logs
│   └── 3l_1tau
│       └── Tight
│           ├── DoubleEG_Run2015C
│           │   ├── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_0.log
│           │   └── analyze_3l_1tau_DoubleEG_Run2015C_Tight_central_1.log
│           ├── DoubleEG_Run2015D
│           │   ├── analyze_3l_1tau_DoubleEG_Run2015D_Tight_central_0.log
│           │   ├── analyze_3l_1tau_DoubleEG_Run2015D_Tight_central_10.log
│           │   ├── ...
│           ...
│           └── ZZTo4L
│               ├── analyze_3l_1tau_ZZTo4L_Tight_central_0.log
│               ├── analyze_3l_1tau_ZZTo4L_Tight_central_1.log
│               ├── analyze_3l_1tau_ZZTo4L_Tight_central_2.log
│               ├── analyze_3l_1tau_ZZTo4L_Tight_central_3.log
│               ├── analyze_3l_1tau_ZZTo4L_Tight_central_4.log
│               └── analyze_3l_1tau_ZZTo4L_Tight_central_5.log
├── Makefile_3l_1tau
├── output_rle
│   └── 3l_1tau
│       └── Tight
│           ├── DoubleEG_Run2015C
│           │   ├── rle_3l_1tau_DoubleEG_Run2015C_Tight_central_0.txt
│           │   └── rle_3l_1tau_DoubleEG_Run2015C_Tight_central_1.txt
│           ├── DoubleEG_Run2015D
│           │   ├── rle_3l_1tau_DoubleEG_Run2015D_Tight_central_0.txt
│           │   ├── rle_3l_1tau_DoubleEG_Run2015D_Tight_central_10.txt
│           │   ├── ...
│           ...
│           └── ZZTo4L
│               ├── rle_3l_1tau_ZZTo4L_Tight_central_0.txt
│               ├── rle_3l_1tau_ZZTo4L_Tight_central_1.txt
│               ├── rle_3l_1tau_ZZTo4L_Tight_central_2.txt
│               ├── rle_3l_1tau_ZZTo4L_Tight_central_3.txt
│               ├── rle_3l_1tau_ZZTo4L_Tight_central_4.txt
│               └── rle_3l_1tau_ZZTo4L_Tight_central_5.txt
├── sbatch_analyze_3l_1tau.py
├── stderr_3l_1tau.log
└── stdout_3l_1tau.log

```
</details>
The datacards are located under `datacards`; the run-lumi-event numbers of selected events are under `output_rle`.

### Synchronization

If you want to produce the ntuples for the synchronization exercise, run
```bash
sync_ntuples $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test/sync_ntuples_cfg.py
```
Check the input/output parameters in the configuration file first, though. The resulting sync Ntuple can be compared against the other Ntuples w/ appropriate macros.
