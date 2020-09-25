import sys
import pandas
import cPickle as pickle
import itertools
import collections
import traceback
import xgboost


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
        except Exception as e:
          print(traceback.format_exc(e))
      f.close()
  return pkldata

def evaluate(vec_values, vec_names, pkldata):
  #cols_when_model_builds =  pkldata.get_booster().feature_names ## Take column names from pkl file
  #print("cols_when_model_builds: ", cols_when_model_builds)
  new_dict = collections.OrderedDict(itertools.izip(vec_names, vec_values))
  data = pandas.DataFrame(columns = list(new_dict.keys()))
  data = data.append(new_dict, ignore_index = True)
  #data = data[cols_when_model_builds] ## Reordering dataframe columns as per pkl file
  #print("data", data)
  result = -20
  if 'XGBClassifier' in str(type(pkldata)):
    try:
      proba = pkldata.predict_proba(data[data.columns.values.tolist()].values)
    except:
      print('Caught error:', sys.exc_info())
    else:
      result = proba[:,1][0]
  else:
    try:
      matrix = xgboost.DMatrix(data,feature_names=new_dict.keys())
      proba = pkldata.predict(matrix)
    except:
      print('Caught error:', sys.exc_info())
    else:
      result = proba[:,1][0]
  return result
