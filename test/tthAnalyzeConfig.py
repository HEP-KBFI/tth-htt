import json, os, codecs, stat, logging, sys
from jinja2 import Template

local_test = True
if local_test:
    import imp
    samples_module = imp.load_source("", "/home/karl/repos/tth-htt/test/tthAnalyzeSamples.py")
    samples = samples_module.samples
else:
    from tthAnalyzeSamples import samples

delim_list = ["13TeV", "M120", "M125", "M130", "M-10to50", "M-50", "TuneCUETP8M1"]

def iterative_split(s, split_delims):
    t = s
    for delim in split_delims: t = t.split(delim)[0]
    return t

def get_mc_process_name(x):
    return iterative_split(x, delim_list)[1:-1]

def get_data_process_name(x):
    return iterative_split(x, ["-", "_"]).replace("/", "_")[1:]

def add_chmodX(fullpath):
    st = os.stat(fullpath)
    os.chmod(fullpath, st.st_mode | stat.S_IEXEC)

def create_config(root_filenames, exec_name, output_file, category_name,
                  charge_selection, lepton_selection, is_mc, idx):
    cfg_file = """import os
import FWCore.ParameterSet.Config as cms

process = cms.PSet()
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('{{ fileNames|join("',\n                            '") }}'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('{{ outputFile }}')
)

process.{{ execName }} = cms.PSet(
    treeName = cms.string('tree'),
    process = cms.string('{{ categoryName }}'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    {% if execName != "analyze_1l_2tau" %}
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool(True),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
                               "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
                                 "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool(True),
    {% endif %}
    chargeSelection = cms.string('{{ chargeSelection }}'),
    leptonSelection = cms.string('{{ leptonSelection }}'),
    
    isMC = cms.bool({{ isMC }}),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)

"""
    return Template(cfg_file).render(
        fileNames = root_filenames,
        execName = exec_name,
        outputFile = output_file,
        categoryName = category_name,
        chargeSelection = charge_selection,
        leptonSelection = lepton_selection,
        isMC = False, # NOTE: temporary fix; previously: is_mc
        idx = idx)

def create_job(exec_name, py_cfg):
    contents = """#!/bin/bash
{{ exec_name }} {{ py_cfg }}

"""
    return Template(contents).render(exec_name = exec_name, py_cfg = py_cfg)

def create_sbatch(sbatch_logfiles, commands):
    sbatch_meta = zip(sbatch_logfiles, commands)
    sbatch_template = """#!/bin/bash
{% for logfile,command in sbatch_meta %}
sbatch --output={{ logfile }} {{ command }}{% endfor %}
"""
    return Template(sbatch_template).render(sbatch_meta = sbatch_meta)

def create_if_not_exists(dir_fullpath):
    if not os.path.exists(dir_fullpath): os.makedirs(dir_fullpath)

def generate_job_ids(nof_files):
    file_limits = range(1, nof_files, max_files_per_job)
    file_limits.append(nof_files + 1)
    
    job_ids = []
    for i in range(len(file_limits) - 1):
        job_ids.append(range(file_limits[i], file_limits[i + 1]))
    return job_ids

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store, debug = False):
    input_list = []
    for job in job_ids:
        input_file = ""
        subdir = "000" + str(job / 1000)
        if job in secondary_files:
            input_file = os.path.join(secondary_store, subdir, "tree_" + str(job) + ".root")
        else:
            input_file = os.path.join(primary_store, subdir, "tree_" + str(job) + ".root")
        if debug:
            if not os.path.exists(input_file):
                logging.error("File %s doesn't exists!" % input_file)
                sys.exit(2)
        input_list.append(input_file)
    return input_list

def create_setup(output_dir, exec_name, charge_selection, lepton_selection, max_files_per_job, debug = False):
    subdir = "_".join([exec_name.replace("analyze_", ""), charge_selection, lepton_selection])
    bashscript_dir = os.path.join(output_dir, "jobs", subdir) # contains bash scripts
    cfg_dir = os.path.join(output_dir, "cfgs", subdir) # contains python config files
    histogram_dir = os.path.join(output_dir, "histograms", subdir) # contains histograms
    log_dir = os.path.join(output_dir, "logs", subdir) # contains logs of job outputs
    
    for d in [bashscript_dir, cfg_dir, histogram_dir, log_dir]:
        create_if_not_exists(d)
    
    cfg_basenames = []
    
    for k, v in samples.items():
        if not v["use_it"]: continue
        if v["sample_category"] in ["additional_signal_overlap", "background_data_estimate"]: continue
        is_mc = v["type"] == "mc"
        process_name = ""
        if is_mc: process_name = get_mc_process_name(k)
        else:     process_name = get_data_process_name(k)
        category_name = v["sample_category"]
        cfg_outputdir = os.path.join(cfg_dir, process_name)
        create_if_not_exists(cfg_outputdir)
        logging.info("Created config and job files for sample %s" % process_name)

        nof_files = v["nof_files"]
        store_dirs = v["local_paths"]
        assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
        primary_store, secondary_store = "", ""
        secondary_files = []
        for store_dir in store_dirs:
            if store_dir["selection"] == "*": primary_store = store_dir["path"]
            else:
                secondary_store = store_dir["path"]
                secondary_files = map(lambda x: int(x), store_dir["selection"].split(","))
        job_ids = generate_job_ids(nof_files)

        for idx in range(len(job_ids)):
            cfg_filelist = generate_input_list(job_ids[idx], secondary_files,
                                               primary_store, secondary_store, debug)
            cfg_outputfile = "_".join([process_name, charge_selection, lepton_selection, str(idx)]) + ".root"
            histogram_outputdir = os.path.join(histogram_dir, category_name)
            cfg_outputfile_fullpath = os.path.join(histogram_outputdir, cfg_outputfile)
            create_if_not_exists(histogram_outputdir)

            cfg_contents = create_config(cfg_filelist, exec_name, cfg_outputfile_fullpath, category_name,
                                         charge_selection, lepton_selection, is_mc, idx)
            cfg_basename = "_".join([process_name, str(idx)])
            cfg_file_fullpath = os.path.join(cfg_outputdir,  cfg_basename + ".py")
            with codecs.open(cfg_file_fullpath, "w", "utf-8") as f:
                f.write(cfg_contents)

            bsh_contents = create_job(exec_name, cfg_file_fullpath)
            bsh_file_fullpath = os.path.join(bashscript_dir, cfg_basename + ".sh")
            with codecs.open(bsh_file_fullpath, "w", "utf-8") as f:
                f.write(bsh_contents)
            add_chmodX(bsh_file_fullpath)
            cfg_basenames.append(cfg_basename)
    
    logging.info("Creating Makefile")
    commands = map(lambda x: os.path.join(bashscript_dir, x + ".sh"), cfg_basenames)
    makefile_fullpath = os.path.join(output_dir, "Makefile")
    with codecs.open(makefile_fullpath, 'w', 'utf-8') as f:
        num = 20 # number of job items per line in the Makefile
        nof_jobs = len(commands)
        job_labels_seq = map(lambda x: "j" + str(x), range(1, nof_jobs))
        job_labels_nested = [job_labels_seq[i:i + num] for i  in range(0, nof_jobs, num)]
        f.write(".PHONY: " + " \\\n        ".join([" ".join(x) for x in job_labels_nested]) + "\n\n")
        f.write("all: " + " \\\n     ".join([" ".join(x) for x in job_labels_nested]) + "\n\n")
        for idx in range(nof_jobs):
            f.write("j" + str(idx) + ":\n\t@bash " + commands[idx] + "\n")
        f.write("\n")
    
    logging.info("Creating SLURM jobs")
    sbatch_fullpath = os.path.join(output_dir, "sbatch.sh")
    sbatch_logfiles = map(lambda x: os.path.join(log_dir, x + "-%a.out"), cfg_basenames)
    sbatch_contents = create_sbatch(sbatch_logfiles, commands)
    with codecs.open(sbatch_fullpath, 'w', 'utf-8') as f:
        f.write(sbatch_contents)
    add_chmodX(sbatch_fullpath)
    
    logging.info("Done")

if __name__ == '__main__':
    logging.basicConfig(stream=sys.stdout,
                        level=logging.INFO,
                        format='%(asctime)s - %(levelname)s: %(message)s')

    output_dir = "/home/karl/test"
    exec_name = "analyze_2lss_1tau" # other execs: analyze_2los_1tau, analyze_1l_2tau
    charge_selection = "SS" # loop over ["SS", "OS"] ??
    lepton_selection = "Tight" # do we only need tight or loose & fakeable as well?
    max_files_per_job = 30 # chain 30 files per job together
    debug = False

    create_setup(output_dir, exec_name, charge_selection, lepton_selection, max_files_per_job, debug)
