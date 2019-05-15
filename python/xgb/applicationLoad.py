import imp
import os
import pandas
import cPickle as pickle
import itertools
import collections

try:
  imp.find_module('xgboost')
  found_xgboost = True
except:
  found_xgboost = False

if found_xgboost:
  import xgboost
else:
  xgb_path = os.path.join('/cvmfs/cms.cern.ch', os.environ['SCRAM_ARCH'] ,'external/py2-pippkgs_depscipy/3.0-njopjo7/lib/python2.7/site-packages')
  if not os.path.isdir(xgb_path):
    raise ValueError('Cannot import xgboost')
  sys.path.insert(0, xgb_path)
  import xgboost as xgb

def load(pklfile):
  f = None
  pkldata = None
  try:
    f = open(pklfile,'rb')
  except IOError as e:
    print('Couldnt open or read from file (%s).' % e)
  else:
      try:
        pkldata = pickle.load(f)
      except pickle.UnpicklingError as e: # normal, somewhat expected
        try:
          model = pkldata.booster().get_dump() # this only tests load was ok
        except (AttributeError,  EOFError, ImportError, IndexError) as e:
          print(traceback.format_exc(e))
        except Exception as e: print(traceback.format_exc(e))
      f.close()
  return pkldata

def evaluate(vec, vec2, pkldata):
  new_dict = collections.OrderedDict(itertools.izip(vec2,vec))
  data = pandas.DataFrame(columns = list(new_dict.keys()))
  data = data.append(new_dict, ignore_index = True)
  result = -20
  try:
    proba = pkldata.predict_proba(data[data.columns.values.tolist()].values  )
  except:
    print('Oops!',sys.exc_info()[0],'occured.')
  else:
    result = proba[:,1][0]
  return result
