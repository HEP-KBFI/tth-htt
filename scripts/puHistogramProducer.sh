#!/bin/bash

# The script takes a text file as an input which has the following format:
# 1) input files from which the PU distributions are taken from, are listed one per line
# 2) this is followed by a blank line
# 3) which is followed by the output file name
#
# Example:
#
# tree_1.root
# tree_2.root
# tree_3.root
#
# output.root
#
# NB!! Do not source this file, it may kill your shell session!

test_exit_code () {
  EXIT_CODE=$1;
  echo "Last command finished at `date` with exit code: $EXIT_CODE";
  if [ "$EXIT_CODE" != "0" ]; then
    exit $EXIT_CODE; # Fail as early as possible
  fi
}

# Validate the input
INPUT_FILE=$1
if [ -z ${INPUT_FILE+x} ]; then
  echo "Input file not provided";
  exit 1;
fi

if [ ! -f "$INPUT_FILE" ]; then
  echo "Input file does not exist";
  exit 2;
fi

OUTPUT_FILE=`tail -n1 "$INPUT_FILE"`
if [ -z ${OUTPUT_FILE+x} ]; then
  echo "Input file empty";
  exit 3;
fi

INPUT_FILES=()
while read LINE; do
  if [ -z "$LINE" ]; then
    # We've found an empty line
    break;
  fi

  if [ ! -f "$LINE" ]; then
    echo "Input file $LINE does not exist";
    exit 4;
  fi

  if [ "$LINE" == "$OUTPUT_FILE" ]; then
    echo "Input and output files cannot coincide: $LINE";
    exit 5;
  fi

  # Input file should be OK
  INPUT_FILES+=("$LINE");
done < "$INPUT_FILE"

NOF_INPUT_FILES="${#INPUT_FILES[@]}"
if [ "$NOF_INPUT_FILES" == "0" ]; then
  # This shouldn't happen, but who knows..
  echo "Zero input files provided";
  exit 6;
fi

# Assume that when running this script in a distributed environment,
# all output file names are unique; the temporary file names are thus
# constructed from the file name plus index of the input file plus extension
OUTPUT_FILE_BASENAME=$(basename -- "$OUTPUT_FILE")
OUTPUT_FILE_EXTENSION="${OUTPUT_FILE_BASENAME##*.}"
OUTPUT_FILE_FILENAME="${OUTPUT_FILE_BASENAME%.*}"

HADD_FILES="$OUTPUT_FILE_BASENAME"
for INDEX in ${!INPUT_FILES[@]}; do
  INDEX_INCR=$((INDEX+1));
  TMP_OUTPUT_FILENAME="${OUTPUT_FILE_FILENAME}_${INDEX_INCR}.${OUTPUT_FILE_EXTENSION}";
  nano_postproc.py -I tthAnalysis.NanoAODTools.postprocessing.tthModules "puHist2017($TMP_OUTPUT_FILENAME)" --noout . "${INPUT_FILES[INDEX]}";
  test_exit_code $?;
  HADD_FILES+=" $TMP_OUTPUT_FILENAME";
done

hadd $HADD_FILES;
test_exit_code $?;

# Let's leave the cleanup to the user...