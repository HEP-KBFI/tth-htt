
from tthAnalysis.HiggsToTauTau.jobTools import generate_file_ids, generate_input_list

def initDict(dictionary, keys):
    """Auxiliary function to initialize dictionary for access with multiple keys
    """
    dictionary_at_keylevel = dictionary
    numKeys = len(keys)
    for idxKey in range(numKeys - 1):
        key = keys[idxKey]
        if key not in dictionary_at_keylevel.keys():
            dictionary_at_keylevel[key] = {}
        dictionary_at_keylevel = dictionary_at_keylevel[key]

def append_to_key(key, part):
    new_key = key
    if len(new_key) > 0:
        new_key += "_"
    new_key += str(part)
    return new_key

def getKey(*args):
    key = ""
    for part in args:
        key = append_to_key(key, part)
    return key

def create_cfg(cfg_file_original, cfg_file_modified, lines):
    """Auxiliary function to clone config file.
       The lines given as argument are added to the end of the cloned file,
       overwriting some of the configuration parameters defined in the original file.
    """
    f_original = open(cfg_file_original, "r")
    cfg_original = f_original.read()
    f_original.close()
    cfg_modified = cfg_original
    cfg_modified += "\n"
    for line in lines:
        cfg_modified += "%s\n" % line
    cfg_modified += "\n"
    f_modified = open(cfg_file_modified, "w")
    f_modified.write(cfg_modified)
    f_modified.close()

def createFile(fileName, lines, nofNewLines = 2):
    """Auxiliary function to write new config file,
       containg the lines given as argument.
    """
    content = "\n".join(lines)
    content += nofNewLines * "\n"
    with open(fileName, "w") as f:
      f.write(content)

def initializeInputFileIds(sample_info, max_files_per_job):
    """Retrieves the number of input ROOT files (Ntuples) corresponding to a given sample
       and fills the number into the dictionary 'inputFileIds', with the name of the sample as key

       TODO: add blacklist to the secondary storage as well
    """
    #print "<initializeInputFileIds>:"
    nof_inputFiles = sample_info["nof_files"]
    store_dirs = sample_info["local_paths"]
    assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
    primary_store, secondary_store = "", ""
    secondary_files, blacklist = [], []
    for store_dir in store_dirs:
        if store_dir["selection"] == "*":
            primary_store = store_dir["path"]
            if "blacklist" in store_dir:
                blacklist = store_dir["blacklist"]
        else:
            secondary_store = store_dir["path"]
            secondary_files = map(lambda x: int(x), store_dir[
                "selection"].split(","))
    inputFileIds = generate_file_ids(nof_inputFiles, max_files_per_job, blacklist)
    return ( inputFileIds, secondary_files, primary_store, secondary_store )

def generateInputFileList(sample_info, max_files_per_job):
    ( inputFileIds, secondary_files, primary_store, secondary_store ) = initializeInputFileIds(sample_info, max_files_per_job)
    inputFileList = {}
    if max_files_per_job > 1:
        for jobId in range(len(inputFileIds)):
            inputFileList[jobId + 1] = generate_input_list(inputFileIds[jobId], secondary_files, primary_store, secondary_store)
    elif max_files_per_job == 1:
        for jobId_it in range(len(inputFileIds)):
            jobId = inputFileIds[jobId_it]
            inputFileList[jobId[0]] = generate_input_list(jobId, secondary_files, primary_store, secondary_store)
    return inputFileList

def createMakefile(makefileName, targets, lines_makefile, filesToClean = None, isSbatch = False, phoniesToAdd = []):
    """Creates Makefile that runs the complete analysis workfow.
    """

    lines_makefile_with_header = []
    lines_makefile_with_header.append(".DEFAULT_GOAL := all")
    lines_makefile_with_header.append("SHELL := /bin/bash")
    lines_makefile_with_header.append("")
    lines_makefile_with_header.append("all: %s" % " ".join(targets))
    lines_makefile_with_header.append("")
    phonies = []
    if filesToClean:
        phonies.append('clean')
    if isSbatch:
        phonies.append('sbatch_analyze sbatch_addBackgrounds sbatch_addFakes sbatch_addMEM')
        phonies.append(' '.join(phoniesToAdd))
    if phonies:
        lines_makefile_with_header.append(".PHONY: %s" % ' '.join(phonies))
    if filesToClean:
        lines_makefile_with_header.append("clean:")
        for fileToClean in filesToClean:
            lines_makefile_with_header.append("\trm -f %s" % fileToClean)
        lines_makefile_with_header.append("")
    lines_makefile_with_header.extend(lines_makefile)
    createFile(makefileName, lines_makefile_with_header)

def is_dymc_reweighting(dbs_name):
  return dbs_name.startswith('/DY') and 'M-50' in dbs_name and not dbs_name.startswith('/DYBB')
