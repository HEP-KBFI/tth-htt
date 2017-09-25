import re
import json

##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_Tallinn_syncNtuple.txt'
##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_Tallinn_syncNtuple.txt'
##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_Tallinn_syncNtuple.txt'

#inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttZ.txt'
#inputFile_test = '/home/veelken/ttHAnalysis/2016/2017Jan11/output_rle/3l_1tau/Tight_OS/TTZToLLNuNu_M-10_ext1/rle_3l_1tau_SR_TTZToLLNuNu_M-10_ext1.txt'
#inputFile_ref = '/home/veelken/ttHAnalysis/2016/2017Jan16/output_rle/2lss_1tau/Tight_SS/ttHJetToNonbb_M125/rle_2lss_1tau_ttHJetToNonbb_M125_Tight_SS_central_all.txt'
#inputFile_test = '/home/veelken/ttHAnalysis/2016/2017Jan30_addMEM//output_rle/2lss_1tau/Tight_SS/ttHJetToNonbb_M125/rle_2lss_1tau_ttHJetToNonbb_M125_Tight_SS_central_1.txt'
#inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar02/selEvents_1l_2tau_ttH_htt_SR_LLR.txt'
#inputFile_test = '/home/veelken/ttHAnalysis/2016/2017Mar02/output_rle/1l_2tau/Tight_OS/ttHJetToNonbb_M125_amcatnlo/rle_1l_2tau_ttHJetToNonbb_M125_amcatnlo_Tight_OS_central_all.txt'
#inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar04/selEvents_3l_1tau_Data_fakeBgrCR_LLR.txt'
#inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar02/selEvents_3l_1tau_Data_fakeBgrCR_LLR_selectedByTallinn.txt'
#inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar08/selEvents_3l_1tau_SR_TTZToLL_M10_ext2_LLR.txt'
#inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar08/selEvents_3l_1tau_SR_TTZToLL_M10_ext2_Tallinn.txt'
#inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar17/2lss1tau_SR.txt'
#inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Mar17/selEvents_2lss_1tau_Data.txt'
inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Apr30/selEvents_1l_2tau_Tallinn_ttH_vvTight.txt'
inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/sync_2017Apr30/selEvents_1l_2tau_ND_ttH_vvTight.txt'

matcher_ref = re.compile('(?P<run>\d*):(?P<lumi>\d*):(?P<evt>\d*)')
#matcher_test = re.compile('\*(?P<garbage>[0-9 ]+)\*(?P<run>[0-9 ]+)\*(?P<lumi>[0-9 ]+)\*(?P<evt>[0-9 ]+)\*')
matcher_test = matcher_ref

events_ref = set([])
events_test = set([])

def fill(files, matcher, event_set):
    for filename in files:
        file = open(filename, 'r')
        for line in file.readlines():
            match = matcher.match(line)
            if match:
                event_set.add(tuple(
                    map(int, map(match.group, ['run', 'lumi', 'evt']))
                ))

fill([ inputFile_ref ], matcher_ref, events_ref)
fill([ inputFile_test ], matcher_test, events_test)

print "Found %i REF events" % len(events_ref)
print "Found %i TEST events" % len(events_test)

common = events_ref.intersection(events_test)
print "======= COMMON events (%i) ========" % len(common)
for event in common:
    print ":".join(map(str, event))
    
common_file = open('selEvents_2lss_1tau_Data_common.txt', 'w')
for event in common:
    common_file.write(":".join(map(str, event)) + "\n")

only_ref = events_ref - events_test
print "======= REF only events (%i) ========" % len(only_ref)
for event in only_ref:
    print ":".join(map(str, event))

only_test = events_test - events_ref
print "======= TEST only events (%i) ========" % len(only_test)
for event in only_test:
    print ":".join(map(str, event))

output_file_ref = open('events_REF.txt', 'w')
for event in events_ref:
    output_file_ref.write(":".join(map(str, event)) + "\n")

##only_file_ref = open('events_exclREF.txt', 'w')
only_file_ref = open('selEvents_2lss_1tau_Data_onlyLLR.txt', 'w')
for event in only_ref:
    only_file_ref.write(":".join(map(str, event)) + "\n")

only_file_test = open('selEvents_2lss_1tau_Data_onlyTallinn.txt', 'w')
for event in only_test:
    only_file_test.write(":".join(map(str, event)) + "\n")


