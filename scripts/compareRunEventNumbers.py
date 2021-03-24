#!/usr/bin/env python

import re

inputFile_ref = '/home/veelken/CMSSW_10_2_10_centOS/CMSSW_10_2_10/src/tthAnalysis/HiggsToTauTau/scripts/fromPeter/ee_old.txt'
inputFile_test = '/home/veelken/CMSSW_10_2_10_centOS/CMSSW_10_2_10/src/tthAnalysis/HiggsToTauTau/scripts/fromPeter/ee_new.txt'

matcher_ref = re.compile('(?P<run>\d*):(?P<lumi>\d*):(?P<evt>\d*)')
matcher_test = matcher_ref

events_ref = set([])
events_test = set([])

def fill(files, matcher, event_set):
    duplicates = {}
    for filename in files:
        print("Opening file = '%s'" % filename)
        num_events = 0
        with open(filename, 'r') as file:
            for line in file.readlines():
                match = matcher.match(line)
                if match:
                    key = ":".join(map(str, map(int, map(match.group, ['run', 'lumi', 'evt']))))
                    if num_events > 0 and (num_events % 1000) == 0:
                        print("Reading event %i" % num_events)
                    num_events += 1
                    if key in duplicates.keys():
                        duplicates[key] += 1
                    else:
                        duplicates[key] = 0
                    event_set.add(tuple(
                        map(int, map(match.group, ['run', 'lumi', 'evt']))
                    ))
        print("Read %i events from file '%s'." % (num_events, filename))
    for key, value in duplicates.items():
        if value > 1:
            print("Warning: %s found %i times!!" % (key, value))

fill([ inputFile_ref ], matcher_ref, events_ref)
fill([ inputFile_test ], matcher_test, events_test)

print("Found %i REF events" % len(events_ref))
print("Found %i TEST events" % len(events_test))

common = events_ref.intersection(events_test)
print("======= COMMON events (%i) ========" % len(common))
for event in common:
    print(":".join(map(str, event)))

only_ref = events_ref - events_test
print("======= REF only events (%i) ========" % len(only_ref))
for event in only_ref:
    print(":".join(map(str, event)))

only_test = events_test - events_ref
print("======= TEST only events (%i) ========" % len(only_test))
for event in only_test:
    print(":".join(map(str, event)))
