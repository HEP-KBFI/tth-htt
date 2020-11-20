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
ADD_HTXS=$(python -c "execfile('$SCRIPT'); print(addHTXS)")
HTXS_FILE=$(python -c "execfile('$SCRIPT'); print(fileHTXS)")

echo "Found the following file(s): '$FILES'"
echo "Found the following executable: '$EXECUTABLE'"
echo "Era? '$ERA'"
echo "Is MC? '$IS_MC'"
echo "Is TuneCP5? '$IS_TUNECP5'"
echo "Skip tools step? '$SKIP_TOOLS_STEP'"
echo "Remove intermediate file? '$REMOVE_INTERMEDIATE'"
echo "Compute SFs for top reweighting? '$COMP_TOP_RWGT'"
echo "Count events in bins of Higgs pT? '$COMP_HTXS'"
echo "Add HTXS? '$ADD_HTXS'"
echo "HTXS file? '$HTXS_FILE'"

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

if [ "$ADD_HTXS" == "True" ]; then
  NANO_MODULES_MC="$NANO_MODULES_MC,htxs($HTXS_FILE;$PROCESS_NAME)";
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
    F_i=$(basename "${F%.*}_i.${F##*.}")
    F_ii=$(basename "${F%.*}_ii.${F##*.}")
    echo "Adding new branches: $F -> $F_i"
    nano_postproc.py -s _i -I tthAnalysis.NanoAODTools.postprocessing.tthModules $NANO_MODULES . $F
    test_exit_code $?
    echo "Creating counter histograms: $F_i -> $F_ii"
    COUNTHISTOGRAM_MODULE="countHistogramAll"
    if [ "$IS_MC" == "True" ]; then
      if [ "$COMP_TOP_RWGT" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}CompTopRwgt";
      elif [ "$COMP_HTXS" == "True" ]; then
        COUNTHISTOGRAM_MODULE="${COUNTHISTOGRAM_MODULE}CompHTXS";
      fi
      nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules $COUNTHISTOGRAM_MODULE \
                       . $F_i
    else
      nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules $COUNTHISTOGRAM_MODULE \
                       -J $GOLDEN_JSON                                                                   \
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
