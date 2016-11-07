#!/bin/bash
#SBATCH -o /home/lauri/tmp/slurm-%j.out        # STDOUT
#

args=$1
wrapper="/home/software/wrapper"
basedir="/scratch"

job_user=${SLURM_JOB_USER}
job_id=${SLURM_JOB_ID}
job_host=${HOSTNAME}
job_part=${SBATCH_PARTITION}

job_dir=${basedir}/${job_user}/${job_id}

mkenv(){
  mkdir -p ${job_dir}
  cd ${job_dir}
  pwd
}

mkclean(){
  rm -rvf ${job_dir}
  echo $(date)
}

mklog(){
  lstatus=$1
  echo "### ${lstatus}:$(date):${job_id}:${job_user}:${job_host}:${job_part} ###"
}

#scontrol update NodeName=$HOSTNAME State=drain Reason="Testing"
if [[ -f /cvmfs/cms.cern.ch/cmsset_default.sh ]]; then
  mklog START
  mkenv
  . $args
  mklog STOP
else
  echo $LSUB
  mklog DRAIN-NODE
  sudo scontrol update nodename=$HOSTNAME state=drain reason=Testing
  mklog TRY-REPOST
  if [[ ${LSUB} -lt 2 ]]; then
    LSUB=$((LSUB+1))
    LSUB=${LSUB} sbatch ${wrapper} ${args}
    mklog START-REPOST
    exit
  fi
  mklog STOP-REPORT-${LSUB}
fi
