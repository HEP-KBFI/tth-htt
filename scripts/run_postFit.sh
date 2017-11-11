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

OLD_CMSSW_AREA="$1" # /home/karl/CMSSW_7_4_7/src
NEW_CMSSW_AREA="$2" # /home/karl/VHbbNtuples_8_0_x/CMSSW_8_0_21/src


echo "Going to: '$OLD_CMSSW_AREA'"
cd $OLD_CMSSW_AREA
eval $(scramv1 runtime -sh) # same as cmsenv
echo $SCRAM_ARCH

is_available combine
is_available analyze_2lss_1tau

echo "Going to: '$NEW_CMSSW_AREA'"
cd $NEW_CMSSW_AREA
eval $(scramv1 runtime -sh) # same as cmsenv
echo $SCRAM_ARCH

is_available combine
is_available analyze_2lss_1tau
