
rm tthAnalyzeRun_ttZctrl_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_ttZctrl.py > tthAnalyzeRun_ttZctrl_tmp.py

python tthAnalyzeRun_ttZctrl_tmp.py
