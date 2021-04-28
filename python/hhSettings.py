import collections
import os

SCANFILES = collections.OrderedDict([
  ('kl', 'hhAnalysis/multilepton/data/kl_scan.dat'),
  ('kt', 'hhAnalysis/multilepton/data/kt_scan.dat'),
  ('c2', 'hhAnalysis/multilepton/data/c2_scan.dat'),
])

def read_couplings(coupling, coupling_as_prefix = False, infix = '_'):
  assert(coupling in SCANFILES)
  coupling_idx = list(SCANFILES.keys()).index(coupling)
  scanFile = SCANFILES[coupling]
  if not scanFile.startswith('/'):
    scanFile = os.path.join(os.environ['CMSSW_BASE'], 'src', scanFile)
  assert(os.path.isfile(scanFile))
  couplings = []
  with open(scanFile, 'r') as scanFilePtr:
    for line in scanFilePtr:
      if line.startswith('#'):
        # it's a comment
        continue
      line_split = line.strip().split()
      assert(len(line_split) > coupling_idx)
      coupling_str = '{:3.2f}'.format(float(line_split[coupling_idx])).replace('.', 'p').replace('-', 'm')
      coupling_str = '{}{}{}'.format(coupling if coupling_as_prefix else '', infix, coupling_str)
      assert(coupling_str not in couplings)
      couplings.append(coupling_str)
  return couplings

NONRESONANT_POINTS = collections.OrderedDict([
    ('JHEP04', [ "BM%d" % idx for idx in range(1, 13) ] + [ 'BM8a' ]),
    ('JHEP03', [ "BM%d" % idx for idx in range(1, 8) ]),
    ('extra',  [ 'box', 'ForMultiDimC2' ]),
    ('c2',     read_couplings('c2')),
])
NONRESONANT_KEYS = list(NONRESONANT_POINTS.keys())
