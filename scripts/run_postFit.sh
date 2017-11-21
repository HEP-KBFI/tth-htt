#!/bin/bash

# DO NOT SOURCE (it'll kill your shell)
# example:
# run_postFit.sh /home/ram/VHBB_NTUPLES_2017/CMSSW_8_0_21_LeptonFakeRate_postNov4/src/tthAnalysis/HiggsToTauTau/test /home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate /home/ram/ttHAnalysis_2017Nov4/2016/2017Nov4/datacards/LeptonFakeRate /home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2 

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
OUTPUT_DIR="$4" # /home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_LATEST2 


echo "Going to: '$OLD_CMSSW_AREA'"
cd $OLD_CMSSW_AREA
eval $(scramv1 runtime -sh) # same as cmsenv
echo $SCRAM_ARCH

# is_available combine
# is_available analyze_2lss_1tau

echo "Going to: '$NEW_CMSSW_AREA'"
cd $NEW_CMSSW_AREA
eval $(scramv1 runtime -sh) # same as cmsenv
echo $SCRAM_ARCH

echo "copying the datacard to the '$NEW_CMSSW_AREA'"
cp $DATACARD_AREA/prepareDatacards_mT_fix_L.root $NEW_CMSSW_AREA/shapes/muon/
cp $DATACARD_AREA/prepareDatacards_mT_fix_L.root $NEW_CMSSW_AREA/shapes/electron/

echo $OUTPUT_DIR
echo "creating datacards for electrons and muons both inclusively and in pT and eta bins"
python setupDatacards_LeptonFakeRate.py -o $OUTPUT_DIR
# echo "creating the roo-workspaces out of the datacards"
# combineTool.py -M T2W -o wsp.root -i $OUTPUT_DIR/*/datacard.txt


printf '\n Running script for Electrons \n'
e_array=(e_incl e_tight_absEtaLt1_5_Pt15_0to20_0 e_tight_absEtaLt1_5_Pt20_0to30_0 e_tight_absEtaLt1_5_Pt30_0to45_0 e_tight_absEtaLt1_5_Pt45_0to65_0 e_tight_absEtaLt1_5_Pt65_0to100000_0 e_tight_absEta1_5to9_9_Pt15_0to20_0 e_tight_absEta1_5to9_9_Pt20_0to30_0 e_tight_absEta1_5to9_9_Pt30_0to45_0 e_tight_absEta1_5to9_9_Pt45_0to65_0 e_tight_absEta1_5to9_9_Pt65_0to100000_0)
e_range=('-10.0,15.0' '-10.0,10.0' '-10.0,10.0' '-10.0,20.0' '-10.0,10.0' '-10.0,10.0' '-100.0,100.0' '-5.0,13.0' '-5.0,20.0' '-100.0,100.0' '-5.0,5.0')

e_sub_dir=(electrons_tight_incl electrons_tight_absEtaLt1_5_Pt15_0to20_0 electrons_tight_absEtaLt1_5_Pt20_0to30_0 electrons_tight_absEtaLt1_5_Pt30_0to45_0 electrons_tight_absEtaLt1_5_Pt45_0to65_0 electrons_tight_absEtaLt1_5_Pt65_0to100000_0 electrons_tight_absEta1_5to9_9_Pt15_0to20_0 electrons_tight_absEta1_5to9_9_Pt20_0to30_0 electrons_tight_absEta1_5to9_9_Pt30_0to45_0 electrons_tight_absEta1_5to9_9_Pt45_0to65_0 electrons_tight_absEta1_5to9_9_Pt65_0to100000_0)






for i in "${!e_array[@]}"
do

printf '\n Making Workspace for %s \n' "$OUTPUT_DIR/${e_array[i]}/datacard.txt"
combineTool.py -M T2W -o wsp.root -i $OUTPUT_DIR/${e_array[i]}/datacard.txt

printf '\n Running MaxLikelihood Fit on %s \n' "${e_array[i]}"
combineTool.py -M MaxLikelihoodFit -m 125 --robustFit 1 --minimizerAlgoForMinos Minuit2,Migrad -d $OUTPUT_DIR/${e_array[i]}/datacard.txt --skipBOnlyFit --setPhysicsModelParameterRanges r=${e_range[i]} --there -n ${e_array[i]}


printf '\n Extracting PostFit shapes from the mlfit \n'
NAME=${e_array[i]}'_mlfit_shapes.root'
echo $NAME

MLFIT_OUPUT='mlfit'${e_array[i]}'.root'

PostFitShapesFromWorkspace -w $OUTPUT_DIR/${e_array[i]}/wsp.root -d $OUTPUT_DIR/${e_array[i]}/datacard.txt -o $OUTPUT_DIR/${e_array[i]}/$NAME -f $OUTPUT_DIR/${e_array[i]}/$MLFIT_OUPUT:fit_s -m 90 --postfit  --sampling --print                                                                                                                                                                             
                          
LABEL=${e_array[i]}
OUTLABEL1=$LABEL"_prefit_linear"
OUTLABEL2=$LABEL"_postfit_linear"
OUTLABEL3=$LABEL"_prefit_log"
OUTLABEL4=$LABEL"_postfit_log"
MLFIT_FILE=$OUTPUT_DIR/${e_array[i]}/$NAME

printf '\n Making PostFit plots \n'
if [ -f "$MLFIT_FILE" ]
then
    echo "$MLFIT_FILE exists."
    python scripts/postFitPlot.py -i $MLFIT_FILE:${e_sub_dir[i]}"_shapes_prefit" -c e --x-title 'm_{T}^{fix}' -o $OUTLABEL1
    python scripts/postFitPlot.py -i $MLFIT_FILE:${e_sub_dir[i]}"_shapes_postfit" -c e --x-title 'm_{T}^{fix}' -o $OUTLABEL2
    python scripts/postFitPlot.py -i $MLFIT_FILE:${e_sub_dir[i]}"_shapes_prefit" -c e --x-title 'm_{T}^{fix}' --logy -o $OUTLABEL3
    python scripts/postFitPlot.py -i $MLFIT_FILE:${e_sub_dir[i]}"_shapes_postfit" -c e --x-title 'm_{T}^{fix}' --logy -o $OUTLABEL4
else
    echo "$MLFIT_FILE does not exist."
fi

done


printf '\n Running script for Muons \n'

mu_array=(mu_incl mu_tight_absEtaLt1_5_Pt10_0to15_0 mu_tight_absEtaLt1_5_Pt15_0to20_0 mu_tight_absEtaLt1_5_Pt20_0to30_0 mu_tight_absEtaLt1_5_Pt30_0to45_0 mu_tight_absEtaLt1_5_Pt45_0to65_0 mu_tight_absEtaLt1_5_Pt65_0to100000_0 mu_tight_absEta1_5to9_9_Pt10_0to15_0 mu_tight_absEta1_5to9_9_Pt15_0to20_0 mu_tight_absEta1_5to9_9_Pt20_0to30_0 mu_tight_absEta1_5to9_9_Pt30_0to45_0 mu_tight_absEta1_5to9_9_Pt45_0to65_0 mu_tight_absEta1_5to9_9_Pt65_0to100000_0)

mu_range=('-15.0,15.0' '-100.0,100.0' '-20.0,20.0' '-10.0,10.0' '-15.0,15.0' '-10.0,10.0' '-100.0,100.0' '-5.0,5.0' '-100.0,100.0' '-15.0,15.0' '-50.0,50.0' '-50.0,50.0' '-20.0,20.0')

mu_sub_dir=(muons_tight_incl muons_tight_absEtaLt1_5_Pt10_0to15_0 muons_tight_absEtaLt1_5_Pt15_0to20_0 muons_tight_absEtaLt1_5_Pt20_0to30_0 muons_tight_absEtaLt1_5_Pt30_0to45_0 muons_tight_absEtaLt1_5_Pt45_0to65_0 muons_tight_absEtaLt1_5_Pt65_0to100000_0 muons_tight_absEta1_5to9_9_Pt10_0to15_0 muons_tight_absEta1_5to9_9_Pt15_0to20_0 muons_tight_absEta1_5to9_9_Pt20_0to30_0 muons_tight_absEta1_5to9_9_Pt30_0to45_0 muons_tight_absEta1_5to9_9_Pt45_0to65_0 muons_tight_absEta1_5to9_9_Pt65_0to100000_0)




for i in "${!mu_array[@]}"
do

printf '\n Making Workspace for %s \n' "$OUTPUT_DIR/${mu_array[i]}/datacard.txt"
combineTool.py -M T2W -o wsp.root -i $OUTPUT_DIR/${mu_array[i]}/datacard.txt

printf '\n Running MaxLikelihood Fit on %s \n' "${mu_array[i]}"
combineTool.py -M MaxLikelihoodFit -m 125 --robustFit 1 --minimizerAlgoForMinos Minuit2,Migrad -d $OUTPUT_DIR/${mu_array[i]}/datacard.txt --skipBOnlyFit --setPhysicsModelParameterRanges r=${mu_range[i]} --there -n ${mu_array[i]}
# # -v 3                                                                                                                                                                                                   

printf '\n Extracting PostFit shapes from the mlfit \n'
NAME=${mu_array[i]}'_mlfit_shapes.root'
echo $NAME

MLFIT_OUTPUT='mlfit'${mu_array[i]}'.root'

PostFitShapesFromWorkspace -w $OUTPUT_DIR/${mu_array[i]}/wsp.root -d $OUTPUT_DIR/${mu_array[i]}/datacard.txt -o $OUTPUT_DIR/${mu_array[i]}/$NAME -f $OUTPUT_DIR/${mu_array[i]}/$MLFIT_OUTPUT:fit_s -m 90 --postfit  --sampling --print                                                                                                                                                                                                     

LABEL=${mu_array[i]}
OUTLABEL1=$LABEL"_prefit_linear"
OUTLABEL2=$LABEL"_postfit_linear"
OUTLABEL3=$LABEL"_prefit_log"
OUTLABEL4=$LABEL"_postfit_log"
MLFIT_FILE=$OUTPUT_DIR/${mu_array[i]}/$NAME

printf '\n Making PostFit plots \n'
if [ -f "$MLFIT_FILE" ]
then
    echo "$MLFIT_FILE exists."
    python scripts/postFitPlot.py -i $MLFIT_FILE:${mu_sub_dir[i]}"_shapes_prefit" -c mu --x-title 'm_{T}^{fix}' -o $OUTLABEL1
    python scripts/postFitPlot.py -i $MLFIT_FILE:${mu_sub_dir[i]}"_shapes_postfit" -c mu --x-title 'm_{T}^{fix}' -o $OUTLABEL2
    python scripts/postFitPlot.py -i $MLFIT_FILE:${mu_sub_dir[i]}"_shapes_prefit" -c mu --x-title 'm_{T}^{fix}' --logy -o $OUTLABEL3
    python scripts/postFitPlot.py -i $MLFIT_FILE:${mu_sub_dir[i]}"_shapes_postfit" -c mu --x-title 'm_{T}^{fix}' --logy -o $OUTLABEL4
else
    echo "$MLFIT_FILE does not exist."
fi

done



is_available combine
is_available analyze_2lss_1tau
