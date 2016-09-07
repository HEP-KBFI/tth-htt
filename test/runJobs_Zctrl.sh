
rm tthAnalyzeRun_Zctrl_tmp.py
sed 's/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_Zctrl.py > tthAnalyzeRun_Zctrl_tmp.py

python tthAnalyzeRun_Zctrl_tmp.py
