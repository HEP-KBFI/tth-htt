# tth-htt
Code and python config files for ttH, H -> tautau analysis with matrix element techniques. For more information visit our [Wiki](https://github.com/HEP-KBFI/tth-htt/wiki).

## Necessary steps to run the lepton fake rate analysis

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
