#!/bin/bash

test_exit_code () {
  EXIT_CODE=$1;
  echo "Last command finished at `date` with exit code: $EXIT_CODE";
  if [ "$EXIT_CODE" != "0" ]; then
    exit $EXIT_CODE; # Fail as early as possible
  fi
}

# The script expects only one argument: the python cfg for the produceNtuple executable, which
# contains the list of files that need pre-processing by nano-AOD tools, as well as the name of
# the executable

SCRIPT="$1"
SCRIPT_DIR=$(dirname "$SCRIPT")
SCRIPT_BASE=$(basename "$SCRIPT")
SCRIPT_EXT="${SCRIPT_BASE##*.}"

# Check if the file is indeed a Python script; file is unreliable, so let's check the extension
if [[ $(echo "$SCRIPT_EXT" | tr '[:upper:]' '[:lower:]') != "py" ]]; then
  echo "File '$SCRIPT' not a Phython script";
  exit 1;
fi

echo "Current working directory: `pwd`"

# First we have to gather the full list of file names
echo "Parsing $SCRIPT"
FILES=$(python -c "execfile('$SCRIPT'); print(' '.join(inputFiles))")
EXECUTABLE=$(python -c "execfile('$SCRIPT'); print(executable)")
IS_MC=$(python -c "execfile('$SCRIPT'); print(isMC)")
IS_HH_NONRES=$(python -c "execfile('$SCRIPT'); print(isHHnonRes)")
ERA=$(python -c "execfile('$SCRIPT'); print(era)")
IS_TUNECP5=$(python -c "execfile('$SCRIPT'); print(isTuneCP5)")
PILEUP=$(python -c "execfile('$SCRIPT'); print(pileup)")
PROCESS_NAME=$(python -c "execfile('$SCRIPT'); print(process_name)")
GOLDEN_JSON=$(python -c "execfile('$SCRIPT'); print(golden_json)")
SKIP_TOOLS_STEP=$(python -c "execfile('$SCRIPT'); print(skip_tools_step)")
REMOVE_INTERMEDIATE=$(python -c "execfile('$SCRIPT'); print(remove_intermediate)")
COMP_TOP_RWGT=$(python -c "execfile('$SCRIPT'); print(compTopRwgt)")
COMP_HTXS=$(python -c "execfile('$SCRIPT'); print(compHTXS)")
SPLIT_BY_LHENJET=$(python -c "execfile('$SCRIPT'); print(splitByNlheJet)")
SPLIT_BY_LHEHT=$(python -c "execfile('$SCRIPT'); print(splitByNlheHT)")
SPLIT_BY_LHENJETHT=$(python -c "execfile('$SCRIPT'); print(splitByNlheJetHT)")
MLL4WZTO3LNU=$(python -c "execfile('$SCRIPT'); print(mllForWZTo3LNu)")
MLL4WZTO3LNU_MLLMIN01=$(python -c "execfile('$SCRIPT'); print(mllForWZTo3LNu_mllmin01)")
RECOMPUTE_RUN_LS=$(python -c "execfile('$SCRIPT'); print(recomp_run_ls)")
REF_GENWEIGHT=$(python -c "execfile('$SCRIPT'); print(ref_genWeight)")

echo "Found the following file(s): '$FILES'"
echo "Found the following executable: '$EXECUTABLE'"
echo "Era? '$ERA'"
echo "Is MC? '$IS_MC'"
echo "Is TuneCP5? '$IS_TUNECP5'"
echo "Skip tools step? '$SKIP_TOOLS_STEP'"
echo "Remove intermediate file? '$REMOVE_INTERMEDIATE'"
echo "Compute SFs for top reweighting? '$COMP_TOP_RWGT'"
echo "Count events in bins of Higgs pT? '$COMP_HTXS'"
echo "Splitting event counts by # LHE jets? '$SPLIT_BY_LHENJET'"
echo "Splitting event counts by LHE HT? '$SPLIT_BY_LHEHT'"
echo "Splitting event counts by # LHE jets and LHE HT? '$SPLIT_BY_LHENJETHT'"
echo "Finding mll for WZTo3LNu? '$MLL4WZTO3LNU'"
echo "Finding mll for WZTo3LNu (mllmin01)? '$MLL4WZTO3LNU_MLLMIN01'"
echo "Recompute run and luminosityBlock? '$RECOMPUTE_RUN_LS'"
echo "Reference gen weight: $REF_GENWEIGHT"

if [[ -z $(which "$EXECUTABLE" 2>/dev/null) ]]; then
  echo "Executable '$EXECUTABLE' not in \$PATH";
  exit 2;
fi

NANO_MODULES_DATA="absIso,tauIDLog,trigObjMatcher,jetIdx,lepJetVarBTagAll_${ERA}"
NANO_MODULES_MC="$NANO_MODULES_DATA,genHiggsDecayMode,genAll,genMatchCollection,\
puWeight${ERA}($PILEUP;$PROCESS_NAME),jetmetUncertainties${ERA}All,fatjetUncertainties${ERA}Total,\
fatjetAK8LSLooseUncertainties${ERA}Total"

NANO_BTAGGING_SF_MODULE="btagSF_deepFlav_${ERA}"
if [ "$IS_TUNECP5" == "True" ]; then
  NANO_BTAGGING_SF_MODULE="${NANO_BTAGGING_SF_MODULE}_TuneCP5";
fi
NANO_MODULES_MC="$NANO_MODULES_MC,$NANO_BTAGGING_SF_MODULE"

if [ "$IS_HH_NONRES" == "True" ]; then
  NANO_MODULES_MC="$NANO_MODULES_MC,diHiggsVar_${ERA}"
fi

if [ "$MLL4WZTO3LNU" == "True" ]; then
  NANO_MODULES_MC="$NANO_MODULES_MC,mllWZTo3LNu"
fi

if [ "$MLL4WZTO3LNU_MLLMIN01" == "True" ]; then
  # run the module before everything else, because it also skims the events
  NANO_MODULES_MC="mllWZTo3LNu_mllmin01,$NANO_MODULES_MC"
fi

if [ "$IS_MC" == "True" ]; then
  NANO_MODULES=$NANO_MODULES_MC;
else
  NANO_MODULES=$NANO_MODULES_DATA;
fi

if [ "$SKIP_TOOLS_STEP" == "False" ]; then
  # Pre-processing files one-by-one:
  echo "Starting nanoAOD pre-processing in `pwd` at `date`"
  for F in $FILES; do
    #NB! The various input files cannot have the same basename!
    G=$F

    if [ "$RECOMPUTE_RUN_LS" = "True" ]; then
      F_j=$(basename "${F%.*}_j.${F##*.}")
      echo "Removing old run and luminosityBlock branches: $G -> $F_j"
      nano_postproc.py -s _j -b $CMSSW_BASE/src/tthAnalysis/NanoAODTools/data/keep_and_drop_rle.txt . $G
      test_exit_code $?

      F_jj=$(basename "${F%.*}_jj.${F##*.}")
      echo "Adding new run and luminosityBlock branches: $F_j -> $F_jj"
      nano_postproc.py -s j -I tthAnalysis.NanoAODTools.postprocessing.tthModules rle . $F_j
      test_exit_code $?

      if [ "$REMOVE_INTERMEDIATE" == "True" ]; then
        echo "Removing intermediate file $F_j";
        rm -f $F_j;
      fi
      G=$F_jj
    fi

    F_i=$(basename "${G%.*}_i.${G##*.}")
    F_ii=$(basename "${G%.*}_ii.${G##*.}")
    echo "Adding new branches: $G -> $F_i"
    nano_postproc.py -s _i -I tthAnalysis.NanoAODTools.postprocessing.tthModules $NANO_MODULES . $G
    test_exit_code $?

    if [[ "$REMOVE_INTERMEDIATE" == "True" ]] && [[ ! -z ${F_jj+x} ]]; then
      echo "Removing intermediate file $F_jj";
      rm -f $F_jj;
    fi

    echo "Creating counter histograms: $F_i -> $F_ii"
    COUNTHISTOGRAM_MODULE="countHistogramAll"
    if [ "$IS_MC" == "True" ]; then
      if [ "$COMP_TOP_RWGT" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}CompTopRwgt";
      elif [ "$COMP_HTXS" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}CompHTXS";
      elif [ "$SPLIT_BY_LHENJET" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}SplitByLHENjet";
      elif [ "$SPLIT_BY_LHEHT" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}SplitByLHEHT";
      elif [ "$SPLIT_BY_LHENJETHT" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}SplitByLHENjetHT";
      fi
      COUNTHISTOGRAM_MODULE="$COUNTHISTOGRAM_MODULE(;;$REF_GENWEIGHT)";
      nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules "$COUNTHISTOGRAM_MODULE" \
                       . $F_i
    else
      COUNTHISTOGRAM_MODULE="$COUNTHISTOGRAM_MODULE($REF_GENWEIGHT)";
      nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules "$COUNTHISTOGRAM_MODULE" \
                       -J $GOLDEN_JSON                                                                     \
                       . $F_i
    fi
    test_exit_code $?
    if [ "$REMOVE_INTERMEDIATE" == "True" ]; then
      echo "Removing intermediate file $F_i";
      rm -f $F_i;
    fi
  done
  echo "Finished nanoAOD pre-processing at `date`"
else
  echo "Skipping the nanoAOD pre-processing step"
fi

# Run the Ntuple production
echo "Starting Ntuple production (`date`)"
$EXECUTABLE $SCRIPT
test_exit_code $?
echo "Finished Ntuple production (`date`)"
