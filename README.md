# tth-htt
Code and python config files for ttH, H -> tautau analysis with matrix element techniques

### Necessary steps to run the lepton fake rate analysis

You need to install the CombineHarvester package by following [these](http://cms-analysis.github.io/CombineHarvester/) and [these](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#ROOT6_SLC6_release_CMSSW_7_4_X) instructions.
At the time of writing, the instructions are:
```bash
# open up a new shell session

cmsrel CMSSW_8_1_0
cd CMSSW_8_1_0/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

# IMPORTANT: Checkout the recommended tag on the link above
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v7.0.7
scramv1 b clean; scramv1 b

cd $CMSSW_BASE/src
git clone https://github.com/HEP-KBFI/CombineHarvester CombineHarvester
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

Run the file:
```bash
cd $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau
./tthAnalyzeRun_3l_1tau.py -m VHbb -v 2018Mar20 -e 2017
```
and wait until you're prompted to run the job exectution, e.g.
```bash
Start jobs ? [Y/n]
```
Press enter and wait til the script tells you `"Done"`. Or, you could decline and run `make` later:
```bash
make -f /home/$USER/ttHAnalysis/2017/2018Mar20/Makefile_3l_1tau -j 4
```
This runs a python script (`sbatch_analyze_3l_1tau.py`) which submits the analysis jobs to SLURM and waits them to complete.
The datacards are located under `datacards`; the run-lumi-event numbers of selected events are under `output_rle`.

### Synchronization

TBD
