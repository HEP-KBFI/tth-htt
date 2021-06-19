#!/bin/bash

basetopdir=$PWD/cards
mkdir -p $basetopdir
tar -C $basetopdir -I lz4 -xvf /hdfs/local/karl/archives/HIG-19-008/ttHAnalysis_stxs_2020Jun18.tar.lz4

rescale_stxs.py $basetopdir

for f in ~/stxs_rescaled/201*/hadd_stage1_rescaled_*_stxsOnly.root; do resum_stxs.py $f; done

for f in ~/stxs_rescaled/201*/hadd_stage1_rescaled_*_stxsResummed.root; do
  g=$(echo $f | sed 's/stxsResummed/inclusiveOnly/g');
  compare_histograms.py -t 1e-2 -i $f -j $g;
done &> comparison.log # look for lines that don't start with "Comparing"

for era in 2016 2017 2018; do
  for ch in 0l_2tau 1l_1tau 1l_2tau 2l_2tau 2lss_1tau_rest 2lss_1tau_tH 2lss_1tau_ttH 2los_1tau 3l_1tau; do
    hadd -f ~/stxs_rescaled/$era/hadd_stage1_rescaled_${ch}_stxsMerged.root \
            ~/stxs_rescaled/$era/hadd_stage1_rescaled_${ch}_*_stxsOnly.root;
  done;
done
