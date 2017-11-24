#!/bin/bash

test_exit_code () {
  EXIT_CODE=$1;
  echo "Last command finished at `date` with exit code: $EXIT_CODE";
  if [ $EXIT_CODE -ne 0 ]; then
    exit $EXIT_CODE; # Fail as early as possible
  fi
}

# The script expects only one argument: the python cfg for the produceNtuple executable, which
# contains the list of files that need pre-processing by nano-AOD tools, as well as the name of
# the executable

SCRIPT="$1"
SCRIPT_DIR=$(dirname "$SCRIPT")
SCRIPT_BASE=$(basename "$SCRIPT")
SCRIPT_FILE="${SCRIPT_BASE%.*}"
SCRIPT_EXT="${SCRIPT_BASE##*.}"

# Check if the file is indeed a Python script; file is unreliable, so let's check the extension
if [[ $(echo "$SCRIPT_EXT" | tr '[:upper:]' '[:lower:]') != "py" ]]; then
  echo "File '$SCRIPT' not a Phython script";
  exit 1;
fi

echo "Current working directory: `pwd`"

# First we have to gather the full list of file names
echo "Going to $SCRIPT_DIR"
cd "$SCRIPT_DIR"
echo "Parsing $SCRIPT_BASE"
FILES=$(python -c "from $SCRIPT_FILE import inputFiles; print(' '.join(inputFiles))")
EXECUTABLE=$(python -c "from $SCRIPT_FILE import executable; print(executable)")
echo "Found the following file(s): '$FILES'"
echo "Found the following executable: '$EXECUTABLE'"
echo "Going back to $OLDPWD"
cd -

if [[ -z $(which "$EXECUTABLE" 2>/dev/null) ]]; then
  echo "Executable '$EXECUTABLE' not in \$PATH";
  exit 2;
fi

# Pre-processing files one-by-one:
echo "Starting nanoAOD pre-processing in `pwd` at `date`"
for F in $FILES; do
  #NB! The various input files cannot have the same basename!
  F_i=$(basename "${F%.*}_i.${F##*.}")
  F_ii=$(basename "${F%.*}_ii.${F##*.}")
  echo "Adding new branches: $F -> $F_i"
  nano_postproc.py -s _i -I tthAnalysis.NanoAODTools.postprocessing.tthModules                                                \
                             genHiggsDecayMode,lepJetVar,genLepton,btagSF,puWeight,jecUncert_cpp,jetmetUncertainties,tauIDLog \
                   . $F;
  test_exit_code $?
  echo "Removing useless branches: $F_i -> $F_ii"
  nano_postproc.py -s i -b $CMSSW_BASE/src/tthAnalysis/NanoAODTools/data/keep_or_drop.txt \
                   . $F_i;
  test_exit_code $?
done
echo "Finished nanoAOD pre-processing at `date`"

# Run the Ntuple production
echo "Starting Ntuple production"
$EXECUTABLE $SCRIPT
test_exit_code
echo "Finished Ntuple production"
