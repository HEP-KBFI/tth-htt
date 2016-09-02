
VERSION="2016Aug31"

rm tthAnalyzeRun_2los_1tau_dR03mvaLoose.py
sed 's/dR03mvaTight/dR03mvaLoose/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_2los_1tau.py > tthAnalyzeRun_2los_1tau_dR03mvaLoose.py
rm tthAnalyzeRun_2los_1tau_dR03mvaMedium.py
sed 's/dR03mvaTight/dR03mvaMedium/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_2los_1tau.py > tthAnalyzeRun_2los_1tau_dR03mvaMedium.py
rm tthAnalyzeRun_2los_1tau_dR03mvaTight.py
sed 's/dR03mvaTight/dR03mvaTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_2los_1tau.py > tthAnalyzeRun_2los_1tau_dR03mvaTight.py
rm tthAnalyzeRun_2los_1tau_dR03mvaVTight.py
sed 's/dR03mvaTight/dR03mvaVTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_2los_1tau.py > tthAnalyzeRun_2los_1tau_dR03mvaVTight.py
rm tthAnalyzeRun_2los_1tau_dR03mvaVVTight.py
sed 's/dR03mvaTight/dR03mvaVVTight/g; s/query_yes_no("Start jobs ?")/True/g' tthAnalyzeRun_2los_1tau.py > tthAnalyzeRun_2los_1tau_dR03mvaVVTight.py

python tthAnalyzeRun_2los_1tau_dR03mvaLoose.py
python tthAnalyzeRun_2los_1tau_dR03mvaMedium.py
python tthAnalyzeRun_2los_1tau_dR03mvaTight.py
python tthAnalyzeRun_2los_1tau_dR03mvaVTight.py
python tthAnalyzeRun_2los_1tau_dR03mvaVVTight.py

cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_2los_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaLoose_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_2los_1tau_mvaDiscr_2lss.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaLoose_mvaDiscr_2lss.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaLoose_mvaOutput_2los_1tau_ttbar.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_2los_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaLoose_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaLoose/datacards/prepareDatacards_2los_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaLoose_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_2los_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaMedium_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_2los_1tau_mvaDiscr_2lss.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaMedium_mvaDiscr_2lss.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaMedium_mvaOutput_2los_1tau_ttbar.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_2los_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaMedium_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaMedium/datacards/prepareDatacards_2los_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaMedium_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_2los_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_2los_1tau_mvaDiscr_2lss.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaTight_mvaDiscr_2lss.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaTight_mvaOutput_2los_1tau_ttbar.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_2los_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaTight/datacards/prepareDatacards_2los_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaTight_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_2los_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_2los_1tau_mvaDiscr_2lss.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVTight_mvaDiscr_2lss.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVTight_mvaOutput_2los_1tau_ttbar.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_2los_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVTight/datacards/prepareDatacards_2los_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVTight_mTauTauVis.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_EventCounter.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVVTight_EventCounter.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_mvaDiscr_2lss.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVVTight_mvaDiscr_2lss.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVVTight_mvaOutput_2los_1tau_ttbar.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_numJets.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVVTight_numJets.input.root
cp /home/veelken/ttHAnalysis/${VERSION}_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_mTauTauVis.root /home/veelken/public/HIG15008_datacards/Tallinn/cut_optimization/2los_1tau/ttH_2los_1tau_${VERSION}_dR03mvaVVTight_mTauTauVis.input.root


