# tth-htt
Code and python config files for ttH, H -> tautau analysis with matrix element techniques

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

### Synchronization

If you want to produce the ntuples for the synchronization exercise, run
```bash
sync_ntuples $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/test/sync_ntuples_cfg.py
```
Check the input/output parameters in the configuration file first, though. The resulting sync Ntuple can be compared against the other Ntuples w/ appropriate macros.
