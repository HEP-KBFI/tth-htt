from TTH_13TeV_M125_samples import Samples, RESULTS_DIR
from jinja2 import Template
import os, codecs, logging, sys, stat

"""This script generates Python configuration files and bash scripts for SLURM.
   Each script contains the following command:
       SynchTTH <path-to-python-config-file>
   There corresponds a separate Python configuration file for each sample.
   By default, all configuration files are saved into
       $PWD/cfgs/<sample key>.py
   e.g. "cfgs/tth.py" or "cfgs/Z_j.py" ($PWD is current directory where
   the script is executed).
   All bash scripts are stored in cfgs/jobs; the script file names are designated
   by the corresponding sample key; the full path to job file is
       $PWD/cfgs/jobs/<sample key>.sh
   e.g. "cfgs/jobs/tth.sh" or "cfgs/jobs/Z_j.sh". The contents of each job file is
   given by sbatch_template variable, e.g.
       sbatch --output=cfgs/slurm/tth-%a.out cfgs/jobs/tth.sh
   This means that all SLURM stdout and stderr are dumped to
       $PWD/cfgs/slurm/<sample key>-<job id>.out
   Usually, you only need to either run a single job, for which you must execute
   the individual bash script in the parent directory of cfgs, or you need to run
   all the jobs at once. The latter case is also resolved with current Python script,
   which outputs
       $PWD/run_cuts.sh
   The file automatically has execution rights, so in order to run all the cuts at once,
   you only need to is
       mkdir some_folder
       cd some_folder
       python2.7 path/to/RunCuts.py
       ./run_cuts.sh
    Setup of CMSSW is assumed here. The results are dumped into
       $PWD/results/<sample key>
    folder for each sample, e.g. "results/tth" or "results/Z_j".
    
    Output: cfgs, run_cuts.sh
    
    You must run this script with python2.7 due to dependency on jinja2 template module.
"""

"""Function that creates the contents of a job file from a template.
   @param s            TTH_13TeV_M125_samples.Sample key, e.g. "ttH" or "Z_j"
   @param _results_dir directory for job output files, e.g. "results/ttH"
"""
def create_cfg(s, _results_dir):
  cfg_file = """import os
import FWCore.ParameterSet.Config as cms
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
  fileNames = cms.vstring('{{ input_file }}'),
  maxEvents = cms.int32(-1),
  outputEvery = cms.uint32(100000)
)
process.SynchTTH = cms.PSet(
  isMC = cms.bool({{ isMC }}),
  central_or_shift = cms.string('central'),
  outputDir = cms.string(os.path.join('{{ results_dir }}', '{{ sample_name }}')),
  forceOverwrite = cms.bool(True)
)

"""
  return Template(cfg_file).render(
           input_file = Samples[s]["path"],
           isMC = Samples[s]["isMC"],
           results_dir = _results_dir,
           sample_name = s)

def create_job(path):
  contents = """#!/bin/bash
SynchTTH {{ cfg_file }}

"""
  return Template(contents).render(cfg_file = path)

if __name__ == '__main__':
  logging.basicConfig(stream=sys.stdout,
                      level=logging.INFO,
                      format='%(asctime)s - %(levelname)s: %(message)s')

  # create dirs to hold python config files needed by SynchTTH program
  # and dirs for bash scripts needed by sbatch
  cfg_dir = "cfgs"
  job_dir = os.path.join(cfg_dir, "jobs")
  slurm_logdir = os.path.join(cfg_dir, "slurm_logs")
  for _dir in [cfg_dir, job_dir, slurm_logdir]:
    if not os.path.exists(_dir):
      os.makedirs(_dir)
  
  for s in Samples:
    # create the python config files (overwrite them if needed)
    if not os.path.exists(Samples[s]["path"]):
      logging.error("File %s doesn't exists!" % Samples[s]["path"])
      sys.exit()
    cfg_contents = create_cfg(s, RESULTS_DIR)
    cfg_file = os.path.join(cfg_dir, s + ".py")
    with codecs.open(cfg_file, 'w', 'utf-8') as f:
      logging.info("Created configuration file %s" % cfg_file)
      f.write(cfg_contents)
    
    # and a bash script for each job (overwrite them, too)
    bash_file = os.path.join(job_dir, s + ".sh")
    bash_contents = create_job(cfg_file)
    with codecs.open(bash_file, 'w', 'utf-8') as f:
      logging.info("Created job file %s" % bash_file)
      f.write(bash_contents)
    st = os.stat(bash_file)
    os.chmod(bash_file, st.st_mode | stat.S_IEXEC)
  
  # create bash scripts that submits the jobs
  sbatch_script = "run_cuts.sh"
  sbatch_template = """#!/bin/bash
{% for slurm_logfile,bash_file in sb_files %}
sbatch --output={{ slurm_logfile }} {{ bash_file }} {% endfor %}

"""
  slurm_logfiles = [os.path.join(slurm_logdir, x + "-%a.out") for x in Samples]
  bash_files = [os.path.join(job_dir, x + ".sh") for x in Samples]
  sbatch_contents = Template(sbatch_template).render(sb_files = zip(slurm_logfiles, bash_files))
  with codecs.open(sbatch_script, 'w', 'utf-8') as f:
    logging.info("Created a single sbatch script for running all jobs: %s" % sbatch_script)
    f.write(sbatch_contents)
  st = os.stat(sbatch_script)
  os.chmod(sbatch_script, st.st_mode | stat.S_IEXEC)
  
