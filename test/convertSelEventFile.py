
import os

##inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_LLR_syncNtuple_unformatted.txt"
##outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_LLR_syncNtuple.txt"
##inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_LLR_syncNtuple_unformatted.txt"
##outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_LLR_syncNtuple.txt"
##inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_LLR_syncNtuple_unformatted.txt"
##outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_LLR_syncNtuple.txt"

##inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttW_unformatted.txt"
##outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttW.txt"
##inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttZ_unformatted.txt"
##outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttZ.txt"

#inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/1l2tau_SR_unformatted.txt"
#outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/1l2tau_SR.txt"
#inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/2lss1tau_SR_unformatted.txt"
#outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/2lss1tau_SR.txt"
#inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/ttH_htt_2lss1tau_unformatted.txt"
#outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/ttH_htt_2lss1tau.txt"
#inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/ttH_hww_2lss1tau_unformatted.txt"
#outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Feb24/ttH_hww_2lss1tau.txt"
inputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar02/selEvents_1l_2tau_ttH_htt_SR_LLR_unformatted.txt"
outputFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar02/selEvents_1l_2tau_ttH_htt_SR_LLR.txt"

inputFile = open(inputFileName, "r")
inputFile_content = inputFile.readlines()
inputFile.close()

outputFile_content = ""
 
for idxLine, inputFile_line in enumerate(inputFile_content):
    if idxLine < 3: # CV: skip header
        continue    
    print "inputFile_line =", inputFile_line
    items = inputFile_line.split("*")
    if len(items) < 5 or len(items) > 6:
        continue
    print "items = ", items
    run = int(items[2])
    ls = int(items[3])
    event = int(items[4])
    outputFile_line = "%i:%i:%i\n" % (run, ls, event)
    outputFile_content += outputFile_line

outputFile = open(outputFileName, "w")
outputFile.write(outputFile_content)
outputFile.close()
