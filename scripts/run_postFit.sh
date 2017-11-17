#!/bin/bash

# DO NOT SOURCE (it'll kill your shell)
# example:
# run_postFit.sh /home/karl/CMSSW_7_4_7/src /home/karl/VHbbNtuples_8_0_x/CMSSW_8_0_21/src

function is_available { # for testing purposes
  if [[ -z "$1" ]]; then
    echo "you must provide exactly one argument to this function";
    exit 1;
  fi
  command_available=$(which "$1" 2>/dev/null)
  if [[ -z "$command_available" ]]; then
    echo "$1: command not available";
  else
    echo "$1: command available";
  fi
}

OLD_CMSSW_AREA="$1" # /home/ram/VHBB_NTUPLES_2017/CMSSW_8_0_21_LeptonFakeRate_postNov4/src/tthAnalysis/HiggsToTauTau/test
NEW_CMSSW_AREA="$2" # /home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate
DATACARD_AREA="$3" # /home/ram/ttHAnalysis_2017Nov4/2016/2017Nov4/datacards/LeptonFakeRate
OUTPUT_DIR="$4" # /home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST 


# echo "Going to: '$OLD_CMSSW_AREA'"
# cd $OLD_CMSSW_AREA
# eval $(scramv1 runtime -sh) # same as cmsenv
# echo $SCRAM_ARCH

# is_available combine
# is_available analyze_2lss_1tau

echo "Going to: '$NEW_CMSSW_AREA'"
cd $NEW_CMSSW_AREA
eval $(scramv1 runtime -sh) # same as cmsenv
echo $SCRAM_ARCH

cp $DATACARD_AREA/prepareDatacards_mT_fix_L.root $NEW_CMSSW_AREA/shapes/muon/
cp $DATACARD_AREA/prepareDatacards_mT_fix_L.root $NEW_CMSSW_AREA/shapes/electron/

echo $OUTPUT_DIR
python setupDatacards_LeptonFakeRate.py -o $OUTPUT_DIR
combineTool.py -M T2W -o wsp.root -i $OUTPUT_DIR/*/datacard.txt




is_available combine
is_available analyze_2lss_1tau
