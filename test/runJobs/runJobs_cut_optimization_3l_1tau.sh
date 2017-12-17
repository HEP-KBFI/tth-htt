
VERSION="2016Aug29"

rm tthAnalyzeRun_3l_1tau_dR03mvaLoose.py
sed 's/dR03mvaTight/dR03mvaLoose/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_3l_1tau.py > tthAnalyzeRun_3l_1tau_dR03mvaLoose.py
rm tthAnalyzeRun_3l_1tau_dR03mvaMedium.py
sed 's/dR03mvaTight/dR03mvaMedium/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_3l_1tau.py > tthAnalyzeRun_3l_1tau_dR03mvaMedium.py
rm tthAnalyzeRun_3l_1tau_dR03mvaTight.py
sed 's/dR03mvaTight/dR03mvaTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_3l_1tau.py > tthAnalyzeRun_3l_1tau_dR03mvaTight.py
rm tthAnalyzeRun_3l_1tau_dR03mvaVTight.py
sed 's/dR03mvaTight/dR03mvaVTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_3l_1tau.py > tthAnalyzeRun_3l_1tau_dR03mvaVTight.py
rm tthAnalyzeRun_3l_1tau_dR03mvaVVTight.py
sed 's/dR03mvaTight/dR03mvaVVTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_3l_1tau.py > tthAnalyzeRun_3l_1tau_dR03mvaVVTight.py

python tthAnalyzeRun_3l_1tau_dR03mvaLoose.py
python tthAnalyzeRun_3l_1tau_dR03mvaMedium.py
python tthAnalyzeRun_3l_1tau_dR03mvaTight.py
python tthAnalyzeRun_3l_1tau_dR03mvaVTight.py
python tthAnalyzeRun_3l_1tau_dR03mvaVVTight.py

cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_3l_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaLoose_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_3l_1tau_mvaDiscr_3l.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaLoose_mvaDiscr_3l.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_3l_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaLoose_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_3l_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaLoose_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_3l_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaMedium_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_3l_1tau_mvaDiscr_3l.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaMedium_mvaDiscr_3l.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_3l_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaMedium_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_3l_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaMedium_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_3l_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_3l_1tau_mvaDiscr_3l.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaTight_mvaDiscr_3l.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_3l_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_3l_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaTight_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_3l_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_3l_1tau_mvaDiscr_3l.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVTight_mvaDiscr_3l.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_3l_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_3l_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVTight_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_3l_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVVTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_3l_1tau_mvaDiscr_3l.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVVTight_mvaDiscr_3l.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_3l_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVVTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_3l_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/3l_1tau/ttH_3l_1tau_${VERSION}_dR03mvaVVTight_mTauTauVis.input.root



