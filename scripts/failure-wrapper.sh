#!/bin/bash

# Resubmits sbatch job if /cvmfs/cms.cern.ch/cmsset_default.sh  missing (no access to network drive)

#SBATCH -o /home/lauri/tmp/slurm-%j.out        # STDOUT
#

args=$1
wrapper="/opt/software/wrapper"
basedir="/scratch"

job_user=${SLURM_JOB_USER}
job_id=${SLURM_JOB_ID}
job_host=${HOSTNAME}
job_part=${SBATCH_PARTITION}

job_dir=${basedir}/${job_user}/${job_id}

prepare_env(){
  mkdir -p ${job_dir}
  cd ${job_dir}
  pwd
}

clean(){
  rm -rvf ${job_dir}
  echo $(date)
}

add_log(){
  lstatus=$1
  echo "### ${lstatus}:$(date):${job_id}:${job_user}:${job_host}:${job_part} ###"
}

#scontrol update NodeName=$HOSTNAME State=drain Reason="Testing"
if [[ -f /cvmfs/cms.cern.ch/cmsset_default.sh ]]; then
  add_log START
  prepare_env
  . $args
  add_log STOP
else
  echo $LSUB
  add_log DRAIN-NODE
  sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing
  add_log TRY-REPOST
  if [[ ${LSUB} -lt 2 ]]; then
    LSUB=$((LSUB+1))
    LSUB=${LSUB} sbatch ${wrapper} ${args}
    add_log START-REPOST
    exit
  fi
  add_log STOP-REPORT-${LSUB}
fi
