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
ERA=$(python -c "execfile('$SCRIPT'); print(era)")
PILEUP=$(python -c "execfile('$SCRIPT'); print(pileup)")
PROCESS_NAME=$(python -c "execfile('$SCRIPT'); print(process_name)")
GOLDEN_JSON=$(python -c "execfile('$SCRIPT'); print(golden_json)")
echo "Found the following file(s): '$FILES'"
echo "Found the following executable: '$EXECUTABLE'"
echo "Is MC? '$IS_MC'"

if [[ -z $(which "$EXECUTABLE" 2>/dev/null) ]]; then
  echo "Executable '$EXECUTABLE' not in \$PATH";
  exit 2;
fi

NANO_MODULES_DATA="absIso,tauIDLog_$ERA,jetSubstructureObservablesHTTv2,trigObjMatcher"
NANO_MODULES_MC="$NANO_MODULES_DATA,genHiggsDecayMode,genAll,puWeight_$ERA($PILEUP;$PROCESS_NAME),jetmetUncertainties$ERA"
if [ "$ERA" = "2016" ]; then
  NANO_MODULES_MC="$NANO_MODULES_MC,btagSF_csvv2_$ERA";
elif [ "$ERA" == "2017" ]; then
  NANO_MODULES_MC="$NANO_MODULES_MC,btagSF_deep_$ERA";
fi

if [ "$IS_MC" == "True" ]; then
  NANO_MODULES=$NANO_MODULES_MC;
else
  NANO_MODULES=$NANO_MODULES_DATA;
fi

# Pre-processing files one-by-one:
echo "Starting nanoAOD pre-processing in `pwd` at `date`"
for F in $FILES; do
  #NB! The various input files cannot have the same basename!
  F_i=$(basename "${F%.*}_i.${F##*.}")
  F_ii=$(basename "${F%.*}_ii.${F##*.}")
  echo "Adding new branches: $F -> $F_i"
  nano_postproc.py -s _i -I tthAnalysis.NanoAODTools.postprocessing.tthModules $NANO_MODULES . $F
  test_exit_code $?
  echo "Removing useless branches: $F_i -> $F_ii"
  if [ "$IS_MC" == "True" ]; then
    nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules "countHistogramAll_$ERA" \
                     -b $CMSSW_BASE/src/tthAnalysis/NanoAODTools/data/keep_or_drop.txt                   \
                     . $F_i
  else
    nano_postproc.py -s i -I tthAnalysis.NanoAODTools.postprocessing.tthModules "countHistogramAll_$ERA" \
                     -b $CMSSW_BASE/src/tthAnalysis/NanoAODTools/data/keep_or_drop.txt                   \
                     -J $GOLDEN_JSON                                                                     \
                     . $F_i
  fi
  test_exit_code $?
done
echo "Finished nanoAOD pre-processing at `date`"

# Run the Ntuple production
echo "Starting Ntuple production"
$EXECUTABLE $SCRIPT
test_exit_code $?
echo "Finished Ntuple production"
