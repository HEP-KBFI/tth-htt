
rm tthAnalyzeRun_WZctrl_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_WZctrl.py > tthAnalyzeRun_WZctrl_tmp.py

python tthAnalyzeRun_WZctrl_tmp.py
