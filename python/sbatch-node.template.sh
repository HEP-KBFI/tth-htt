#!/bin/bash
# File: sbatch-node.template.sh
# Version: 0.2

# unset JAVA_HOME, because hadoop commands might not work
# this is especially true if one has sourced necessary files for the GRID proxy
echo 'Unsetting JAVA_HOME=$JAVA_HOME'
unset JAVA_HOME

# This value is provided by sbatchManager.py that creates sbatch scripts based this template
echo 'Running script {{ script_file }} (created from template sbatch-node.template.sh)'


RUNNING_COMMAND="{{ RUNNING_COMMAND }}"


# Runs executable, wrapped into failure wrapper + wrapped into node scratchdir

main() {
    run_failure_wrapped_executable >> "{{ wrapper_log_file }}" 2>&1
    EXIT_CODE=$?
    return $EXIT_CODE
}


# Executed on node, checks that CVMFS is mounted to this cluster node, or redirects task

run_failure_wrapped_executable() {
    TRY_COUNT=$[TRY_COUNT+1]
    echo "Started (Try $TRY_COUNT)"
    EXIT_CODE=1

    if [[ -f /cvmfs/cms.cern.ch/cmsset_default.sh ]]; then
        echo "Network drive mounted, started running on $HOSTNAME"
        run_wrapped_executable
        EXIT_CODE=$?
    else
        echo "Unable to use node $HOSTNAME, will mark node offline: sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing"
        sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing

        if [[ $TRY_COUNT -lt 3 ]]; then
            echo "Will resubmit job to other node: TRY_COUNT=$TRY_COUNT $RUNNING_COMMAND"
            TRY_COUNT=$TRY_COUNT $RUNNING_COMMAND
            EXIT_CODE=$?
        else
            echo "Maximum tries reached, will not try to resubmit any more. GL & HF"
        fi
    fi
    return $EXIT_CODE
}


# Creates scratch dir on cluster node and runs executable

run_wrapped_executable() {
    export SCRATCH_DIR="{{ scratch_dir }}/$SLURM_JOBID"
    EXECUTABLE_LOG_FILE="{{ executable_log_file }}"
    EXECUTABLE_LOG_DIR="`dirname $EXECUTABLE_LOG_FILE`"
    EXECUTABLE_LOG_FILE_NAME="`basename $EXECUTABLE_LOG_FILE`"
    TEMPORARY_EXECUTABLE_LOG_DIR="$SCRATCH_DIR/$EXECUTABLE_LOG_DIR/"
    TEMPORARY_EXECUTABLE_LOG_FILE="$TEMPORARY_EXECUTABLE_LOG_DIR/$EXECUTABLE_LOG_FILE_NAME"
    RANDOM_SLEEP={{ random_sleep }}

    echo "Time is: `date`"
    echo "Hostname: `hostname`"
    echo "Current directory: `pwd`"

    echo "Sleeping for $RANDOM_SLEEP seconds"
    sleep $RANDOM_SLEEP

    echo "Create scratch directory: mkdir -p $SCRATCH_DIR"
    mkdir -p $SCRATCH_DIR

    echo "Create temporary log directory: mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR"
    mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Create final log directory: mkdir -p $EXECUTABLE_LOG_DIR"
    mkdir -p $EXECUTABLE_LOG_DIR

    cd {{ working_dir }}
    cd $SCRATCH_DIR

    echo "Time is: `date`"

    echo "Copying contents of 'tthAnalysis/HiggsToTauTau/data' directory to Scratch: cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data"
    mkdir -p tthAnalysis/HiggsToTauTau/data
    cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data

    echo "Time is: `date`"

    CMSSW_SEARCH_PATH="$SCRATCH_DIR:{{ cmssw_base_dir }}/src"

    echo "Execute command: {{ exec_name }} {{ command_line_parameter }} &> $TEMPORARY_EXECUTABLE_LOG_FILE"
    {{ exec_name }} {{ command_line_parameter }} &> $TEMPORARY_EXECUTABLE_LOG_FILE
    EXIT_CODE=$?
    echo "Command {{ exec_name }} exited with code $EXIT_CODE"

    echo "Time is: `date`"

    echo "Listing of current directory:"
    ls -l

    OUTPUT_FILES="{{ outputFiles }}"
    echo "Copying output files: {{ outputFiles }}"
    for OUTPUT_FILE in $OUTPUT_FILES
    do
      OUTPUT_DIR="{{ outputDir }}"
      if [[ "$OUTPUT_DIR" =~ ^/hdfs* && ( ! -z $(which hadoop) ) ]]; then
        cp_cmd="hadoop fs -copyFromLocal";
        st_cmd="hadoop fs -stat '%b'"
        OUTPUT_DIR=${OUTPUT_DIR#/hdfs}
      else
        cp_cmd=cp;
        st_cmd="stat --printf='%s'"
      fi
      cp_cmd="$cp_cmd -f"

      OUTPUT_FILE_SIZE=$(stat -c '%s' $OUTPUT_FILE)
      if [ -n "$OUTPUT_FILE_SIZE" ] && [ $OUTPUT_FILE_SIZE -ge 1000 ]; then
        echo "$cp_cmd $OUTPUT_FILE $OUTPUT_DIR/$OUTPUT_FILE"

        CP_RETRIES=0
        COPIED=false
        while [ $CP_RETRIES -lt 3 ]; do
          CP_RETRIES=$[CP_RETRIES + 1];
          $cp_cmd $OUTPUT_FILE $OUTPUT_DIR/$OUTPUT_FILE

          # add a small delay before stat'ing the file
          sleep 5s

          REMOTE_SIZE=$($st_cmd $OUTPUT_DIR/$OUTPUT_FILE)
          if [ "$REMOTE_SIZE" == "$OUTPUT_FILE_SIZE" ]; then
            COPIED=true
            break;
          else
            continue;
          fi
        done

        if [ ! $COPIED ]; then
          EXIT_CODE=1;
        fi

      else
        echo "$OUTPUT_FILE is broken, will exit with code 1."
        rm $OUTPUT_FILE
        EXIT_CODE=1
      fi
    done

    echo "Time is: `date`"

    echo "Contents of temporary log dir: ls -laR $TEMPORARY_EXECUTABLE_LOG_DIR"
    ls -laR $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Copy from temporary output dir to output dir: cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/"
    cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/

    echo "Delete Scratch directory: rm -r $SCRATCH_DIR"
    rm -r $SCRATCH_DIR

    echo "End time is: `date`"

    echo "Waiting for 10 seconds before returning"
    sleep 10

    return $EXIT_CODE
}


# Calls main method

main

EXIT_CODE=$?
echo "Final exit code is: $EXIT_CODE"
exit $EXIT_CODE

# End of file
