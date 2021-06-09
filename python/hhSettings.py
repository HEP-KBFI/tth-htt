import collections
import os

SCANFILES = collections.OrderedDict([
  ('JHEP04', 'hhAnalysis/multilepton/data/jhep04_scan.dat'),
  ('JHEP03', 'hhAnalysis/multilepton/data/jhep03_scan.dat'),
  ('kl',     'hhAnalysis/multilepton/data/kl_scan.dat'),
  ('kt',     'hhAnalysis/multilepton/data/kt_scan.dat'),
  ('c2',     'hhAnalysis/multilepton/data/c2_scan.dat'),
  ('extra',  'hhAnalysis/multilepton/data/extra_scan.dat'),
])

def read_couplings(coupling):
  assert(coupling in SCANFILES)
  scanFile = SCANFILES[coupling]
  if not scanFile.startswith('/'):
    scanFile = os.path.join(os.environ['CMSSW_BASE'], 'src', scanFile)
  assert(os.path.isfile(scanFile))
  couplings = []
  with open(scanFile, 'r') as scanFilePtr:
    for line in scanFilePtr:
      line_comment_pos = line.find('#')
      line_before_comment = (line[:line_comment_pos] if line_comment_pos >= 0 else line).strip()
      if not line_before_comment:
        continue
      line_mapping = dict([ tuple(part.split('=')) for part in line_before_comment.split() ])
      if 'name' in line_mapping:
        name = line_mapping['name']
      else:
        parts = []
        for coupling_type in [ 'kl', 'kt', 'c2', 'cg', 'c2g' ]:
          assert(coupling_type in line_mapping)
          coupling_str = line_mapping[coupling_type]
          if '/' in coupling_str:
            coupling_str_split = coupling_str.split('/')
            assert(len(coupling_str_split) == 2)
            coupling_num = float(coupling_str_split[0])
            coupling_denom = float(coupling_str_split[1])
            coupling_val = coupling_num / coupling_denom
          else:
            coupling_val = float(coupling_str)
          if (coupling_type in [ 'kl', 'kt' ] and coupling_val != 1.) or \
             (coupling_type in [ 'c2', 'cg', 'c2g' ] and coupling_val != 0.):
            parts.append('{}_{:3.2f}'.format(coupling_type, coupling_val).replace('.', 'p').replace('-', 'm'))
        name = '_'.join(parts) if parts else "SM"
      assert(name not in couplings)
      couplings.append(name)
  return couplings

NONRESONANT_POINTS = collections.OrderedDict([
  (coupling_type, read_couplings(coupling_type)) for coupling_type in SCANFILES if coupling_type != 'kt'
])
NONRESONANT_KEYS = list(NONRESONANT_POINTS.keys())
