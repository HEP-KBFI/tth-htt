import re
import json

##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_2lss_1tau_Tallinn_syncNtuple.txt'
##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_3l_1tau_Tallinn_syncNtuple.txt'
##inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_LLR_syncNtuple.txt'
##inputFile_test = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/selEvents_1l_2tau_Tallinn_syncNtuple.txt'

inputFile_ref = '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/synchronization/Events_3l1tau_ttZ.txt'
inputFile_test = '/home/veelken/ttHAnalysis/2016/2017Jan11/output_rle/3l_1tau/Tight_OS/TTZToLLNuNu_M-10_ext1/rle_3l_1tau_SR_TTZToLLNuNu_M-10_ext1.txt'

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

print "There are %i common events" % len(events_ref.intersection(events_test))

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
only_file_ref = open('selEvents_analyze_3l_1tau_onlyLLR.txt', 'w')
for event in only_ref:
    only_file_ref.write(":".join(map(str, event)) + "\n")

only_file_test = open('selEvents_analyze_3l_1tau_onlyTallinn.txt', 'w')
for event in only_test:
    only_file_test.write(":".join(map(str, event)) + "\n")


