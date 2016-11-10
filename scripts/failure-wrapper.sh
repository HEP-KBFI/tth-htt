#!/bin/bash

# Authors: Lauri L, Margus P
# Resubmits sbatch job if /cvmfs/cms.cern.ch/cmsset_default.sh  missing (no access to network drive)


# Set failure-wrapper absolute path

CURRENT_DIR=pwd
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
FAILURE_WRAPPER="$SCRIPT_DIR/failure-wrapper.sh"
cd $CURRENT_DIR


# Set scratch dir

SCRATCH_DIR="/scratch"
CURRENT_USER=${SLURM_CURRENT_USER}
CURRENT_CURRENT_JOB_ID=${SLURM_CURRENT_JOB_ID}
JOB_DIR="/scratch/$CURRENT_USER/$CURRENT_JOB_ID-failure-wrapper"


# Check if network drive is mounted, then execute argument command
# else mark cluster node a miserable failure, good for nothing and throw it out

main() {

    TRY_COUNT=$((TRY_COUNT+1))
    add_log "Started (Try $RESUBMIT_NUMBER)"

    if [[ -f /cvmfs/cms.cern.ch/cmsset_default.sh ]]; then
        add_log "Network drive mounted, started running"
        prepare_env
        add_log "Will run command: $1"
        . $1
        add_log "Ended"
    else
        add_log "Network drive not mounted, marking cluster node invalid: sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing"
        sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing

        if [[ ${TRY_COUNT} -lt 3 ]]; then
            echo "Will resubmit job to other node: TRY_COUNT=$TRY_COUNT sbatch $FAILURE_WRAPPER $1"
            TRY_COUNT=$TRY_COUNT sbatch $FAILURE_WRAPPER $1
        else
            echo "Maximum tries reached, will not try to resubmit any more. GL & HF"
        fi
    fi
}

prepare_env() {
    mkdir -p "$JOB_DIR"
    cd "$JOB_DIR"
    pwd
}

clean() {
    rm -rvf "$JOB_DIR"
    date
}

add_log() {
    MESSAGE=$1
    echo "$MESSAGE:`date`:$CURRENT_JOB_ID:$CURRENT_USER:$HOSTNAME:$SBATCH_PARTITION"
}

main
