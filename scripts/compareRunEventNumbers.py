import re

inputFile_ref = 'e_den_Giovanni.txt'
inputFile_test = '/home/ram/VHBB_NTUPLES_2017/NANO_AOD_DEV/CMSSW_9_4_4_Feb19_2018_Latest_After_boosted_code_bugfix/' + \
                 'src/tthAnalysis/HiggsToTauTau/test/rle_LeptonFakeRate_SingleElectron_Run2017E_17Nov2017_v1_central_20_e_den.txt'

matcher_ref = re.compile('(?P<run>\d*):(?P<lumi>\d*):(?P<evt>\d*)')
matcher_test = matcher_ref

events_ref = set([])
events_test = set([])

def fill(files, matcher, event_set):
    for filename in files:
        with open(filename, 'r') as file:
            for line in file.readlines():
                match = matcher.match(line)
                if match:
                    event_set.add(tuple(
                        map(int, map(match.group, ['run', 'lumi', 'evt']))
                    ))

fill([ inputFile_ref ], matcher_ref, events_ref)
fill([ inputFile_test ], matcher_test, events_test)

print("Found %i REF events" % len(events_ref))
print("Found %i TEST events" % len(events_test))

common = events_ref.intersection(events_test)
print("======= COMMON events (%i) ========" % len(common))
for event in common:
    print(":".join(map(str, event)))

common_file = 'selEvents_e_den_Giovanni_Ram_common_iter7_with_assocJetPt_wo_e_trig_dep_cone_pt_cuts_file_20_only.txt'
with open(common_file, 'w') as f:
    for event in common:
        f.write(":".join(map(str, event)) + "\n")

only_ref = events_ref - events_test
print("======= REF only events (%i) ========" % len(only_ref))
for event in only_ref:
    print(":".join(map(str, event)))

only_test = events_test - events_ref
print("======= TEST only events (%i) ========" % len(only_test))
for event in only_test:
    print(":".join(map(str, event)))

output_file_ref = 'events_REF_iter7_with_assocJetPt_wo_e_trig_dep_cone_pt_cuts_file_20_only.txt'
with open(output_file_ref, 'w') as f:
    for event in events_ref:
        f.write(":".join(map(str, event)) + "\n")

only_file_ref = 'selEvents_den_e_Giovanni_notRam_iter7_with_assocJetPt_wo_e_trig_dep_cone_pt_cuts_file_20_only.txt'
with open(only_file_ref) as f:
    for event in only_ref:
        f.write(":".join(map(str, event)) + "\n")

only_file_test = 'selEvents_den_e_Ram_notGiovanni_iter7_with_assocJetPt_wo_e_trig_dep_cone_pt_cuts_file_20_only.txt'
with open(only_file_test, 'w') as f:
    for event in only_test:
        f.write(":".join(map(str, event)) + "\n")
