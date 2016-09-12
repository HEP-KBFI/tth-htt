
rm tthAnalyzeRun_jetToTauFakeRate_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_jetToTauFakeRate.py > tthAnalyzeRun_jetToTauFakeRate_tmp.py

python tthAnalyzeRun_jetToTauFakeRate_tmp.py

##cp /home/veelken/ttHAnalysis/2016Sep04/histograms/comp_jetToTauFakeRate_OS.root /home/veelken/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/data/FR_tau.root
