#!/bin/bash
# File:     sbatch-node.submit_job_version2.sh
# Version:  0.2

# Runs executable, wrapped into failure wrapper + wrapped into node scratchdir

echo 'Running version (sbatch-node.submit_job_version2.sh)'

main() {
    run_failure_wrapped_executable >> "{{wrapper_log_file}}" 2>&1
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
            echo "Will resubmit job to other node: TRY_COUNT=$TRY_COUNT {{sbatch_command}}"
            TRY_COUNT=$TRY_COUNT {{sbatch_command}}
            EXIT_CODE=$?
        else
            echo "Maximum tries reached, will not try to resubmit any more. GL & HF"
        fi
    fi
    return $EXIT_CODE
}


run_the_command() {
  {{command}}
}


# Creates scratch dir on cluster node and runs executable

run_wrapped_executable() {
    export SCRATCH_DIR="{{scratch_dir}}/$SLURM_JOBID"
    EXECUTABLE_LOG_FILE="{{executable_log_file}}"
    EXECUTABLE_LOG_DIR="`dirname $EXECUTABLE_LOG_FILE`"
    EXECUTABLE_LOG_FILE_NAME="`basename $EXECUTABLE_LOG_FILE`"
    TEMPORARY_EXECUTABLE_LOG_DIR="$SCRATCH_DIR/$EXECUTABLE_LOG_DIR/"
    TEMPORARY_EXECUTABLE_LOG_FILE="$TEMPORARY_EXECUTABLE_LOG_DIR/$EXECUTABLE_LOG_FILE_NAME"

    echo "Time is: `date`"
    echo "Hostname: `hostname`"
    echo "Current directory: `pwd`"

    echo "Create scratch directory: mkdir -p $SCRATCH_DIR"
    mkdir -p $SCRATCH_DIR

    echo "Create temporary log directory: mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR"
    mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Create final log directory: mkdir -p $EXECUTABLE_LOG_DIR"
    mkdir -p $EXECUTABLE_LOG_DIR

    echo "Initialize CMSSW run-time environment: source /cvmfs/cms.cern.ch/cmsset_default.sh"
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    cd {{working_dir}}
    cd $SCRATCH_DIR

    echo "Time is: `date`"

    echo "Copying contents of 'tthAnalysis/HiggsToTauTau/data' directory to Scratch: cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data"
    mkdir -p tthAnalysis/HiggsToTauTau/data
    cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data

    echo "Time is: `date`"

    CMSSW_SEARCH_PATH=$SCRATCH_DIR
    echo "Execute command output will be redirected to $TEMPORARY_EXECUTABLE_LOG_FILE"
    run_the_command > $TEMPORARY_EXECUTABLE_LOG_FILE 2>&1
    EXIT_CODE=$?

    echo "Time is: `date`"

    echo "Time is: `date`"

    echo "Contents of temporary log dir: ls -laR $TEMPORARY_EXECUTABLE_LOG_DIR"
    ls -laR $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Copy from temporary output dir to output dir: cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/"
    cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/

    echo "Delete Scratch directory: rm -r $SCRATCH_DIR"
    rm -r $SCRATCH_DIR

    echo "End time is: `date`"

    return $EXIT_CODE
}


# Calls main method

main

EXIT_CODE=$?
echo "Final exit code is: $EXIT_CODE"
exit $EXIT_CODE

# End of file
