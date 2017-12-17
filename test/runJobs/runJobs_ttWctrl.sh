
rm tthAnalyzeRun_ttWctrl_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_ttWctrl.py > tthAnalyzeRun_ttWctrl_tmp.py

python tthAnalyzeRun_ttWctrl_tmp.py
