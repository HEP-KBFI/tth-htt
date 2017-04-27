import ROOT

def get_events_count(root_file):
    f = ROOT.TFile(root_file)
    count = f.Get("analyzedEntries")
    has_entries_count = hasattr(count, 'GetEntries')

    if has_entries_count:
        entries_count = count.GetEntries()
        print('Event count for %s is %s' % (root_file, entries_count))
        return entries_count
    else:
        entries_count = 0.0
        print('Event count for %s is %s, because files does not have count entries' % (root_file, entries_count))
        return entries_count
