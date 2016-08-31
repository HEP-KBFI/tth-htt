
rm tthAnalyzeRun_jetToTauFakeRate_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_jetToTauFakeRate.py > tthAnalyzeRun_jetToTauFakeRate_tmp.py

python tthAnalyzeRun_jetToTauFakeRate_tmp.py
