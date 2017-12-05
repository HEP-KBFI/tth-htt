# tth-htt
Code and python config files for ttH, H -> tautau analysis with matrix element techniques

### Necessary steps to run the lepton fake rate analysis

You need to install the CombineHarvester package by following [these](http://cms-analysis.github.io/CombineHarvester/) and [these](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#ROOT6_SLC6_release_CMSSW_7_4_X) instructions.
At the time of writing, the instructions are:
```bash
# open up a new shell session

export SCRAM_ARCH=slc6_amd64_gcc491
scram project CMSSW CMSSW_7_4_7
cd CMSSW_7_4_7/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

# IMPORTANT: Checkout the recommended tag on the link above
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v6.3.1
cd $CMSSW_BASE/src

git clone https://github.com/cms-analysis/CombineHarvester.git CombineHarvester
scram b -j8
```

### HDFS plugin

Since FUSE appears to be buggy, accessing files via /hdfs mountpoint is really slow (especially when a given folder contains thousands of files).
One of the (viable) solutions is to build the HDFS plugin ourselves because CMSSW stack doesn't ship ROOT with HDFS support.
This can be done by executing the following command which builds the plugin and sets necessary environment variables to access any file via the HDFS protocol:

```bash
source $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/misc/set_env.sh
```
The files residing on /hdfs can be read via
```c++
TFile * f = TFile::Open("hdfs:///your/desired/path");
```
anywhere. NB! The plugin does not support writing via this protocol.

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
All the results are stored in `outputDir` defined in `tthAnalyzeRun_3l_1tau.py.
The datacards are located under `datacards`; the run-lumi-event numbers of selected events are under `output_rle`.

### Analysis OptionParser

1) mode

    1.a) VHbb -- runs the analysis on all the samples, except for the FastSim samples; the final products of this analysis are datacard files that contain the distributions of various variables used in signal extraction across all event categories (signal, ttbar, ewk, fakes, rares etc); these datacards are used as an input to combine which calculates the limits;

    1.b) forBDTtraining -- runs the analysis exclusively on the FastSim samples; the final products are root files which contain an Ntuple; these Ntuples are used as an input to a BDT training algorithm; no datacards, no limits here;

2) use_prod_ntuples

    2.a) disabled -- runs the analysis on ,,VHbb Ntuples'', i.e. the original Ntuples which we produced ~1 year ago with Heppy; these Ntuples contain all information;

    2.b) enabled -- runs the analysis on ,,production Ntuples'', i.e. the Ntuples that are derived from the ,,VHbb Ntuples'' by removing branches which we don't use in our analysis; by default, the events are required to pass a very loose preselection containing at least 1 fakeable lepton and 1 fakeable tau passing the medium tau WP; in case of FastSim samples, there is no preselection applied, only the unused branches are stripped.

### Synchronization

If you want to produce the ntuples for the synchronization exercise, run
```bash
sync_ntuples $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test/sync_ntuples_cfg.py
```
Check the input/output parameters in the configuration file first, though. The resulting sync Ntuple can be compared against the other Ntuples w/ appropriate macros.
