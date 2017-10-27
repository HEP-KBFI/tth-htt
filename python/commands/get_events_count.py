import ROOT

def get_events_count(root_file):
    f = ROOT.TFile(root_file)
    count = f.Get("analyzedEntries")
    has_entries_count = hasattr(count, 'GetEntries')

    if has_entries_count:
        entries_count = count.GetEntries()
        print("Input file '%s' contains %i analyzed events." % (root_file, entries_count))
        return entries_count
    else:
        entries_count = 0.0
        print("ERROR: Failed to read number of analyzed events in input file '%s' !! Will set number of analyzed events to zero." % root_file)
        return entries_count
