
# cmsenv in the release you are going to work (eg CMSSW_9_4_0_pre1)
# install conda to a home directory -- it will install python2.7 althoguether
# https://conda.io/docs/user-guide/install/linux.html (with prefix)
# https://www.anaconda.com/download/ 
# install pip: https://pip.pypa.io/en/stable/installing/ (--user)
# pip install scikit-learn --user
# pip install xgboost --user
# pip install catboost --user
# pip uninstall numpy (yes, unistall, otherwise will conflict with ROOT)

export PYTHONUSERBASE=/home/acaan/python_local/
export PATH=/home/acaan/python_local/bin:$PATH
export PYTHONPATH=/home/acaan/python_local/lib/python2.7/site-packages:$PYTHONPATH

