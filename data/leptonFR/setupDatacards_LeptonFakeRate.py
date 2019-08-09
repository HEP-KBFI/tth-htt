#!/usr/bin/env python
import CombineHarvester.CombineTools.ch as ch
import argparse
import os

# import sys

# Need this later
def RenameSyst(cmb, syst, old, new):
    if old in syst.name():
        oldname = syst.name()
        syst.set_name(new)
        # Should change the ch::Parameter names too
        cmb.RenameParameter(oldname, new)


parser = argparse.ArgumentParser()
parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_LATEST', help="""Output directory""")
parser.add_argument('--input', '-i', default='prepareDatacards_mT_fix_L.root', help="""Input shapes file""")
# parser.add_argument('--lepton', '-l', default='e', help="""Lepton type can only take e or mu""")
# parser.add_argument('--category', '-c', default='incl', help="""category""")


# parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_new/inclusive', help="""Output directory""")
# parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_new/absEta1_0to1_5_low_pt', help="""Output directory""")
# parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_new/absEta1_5to9_9_low_pt', help="""Output directory""")
# parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_new/absEta1_0to1_5_high_pt', help="""Output directory""")
# parser.add_argument('--output', '-o', default='./output/mlfit_LeptonFakeRate_new/absEta1_5to9_9_high_pt', help="""Output directory""")
# parser.add_argument('--constrain-tau-eff', action='store_true', help="""The tau efficiency will be a constrained nuisance parameter""")
# parser.add_argument('--constrain-tau-scale', action='store_true', help="""The tau energy scale will be a constrained nuisance parameter""")
# parser.add_argument('--variable', choices=['svfit', 'mvis'], default='svfit', help="""Choice of input variable shape files""")
# parser.add_argument('--constrain-zllSyst-em-mm', action='store_true', help="""The zll Norm. will be a constrained nuisance parameter""")



args = parser.parse_args()

shapes_dir = os.environ['CMSSW_BASE'] + '/src/CombineHarvester/ttH_htt_LeptonFakeRate/shapes'

cb = ch.CombineHarvester()


# args.output


##########################################################################
# Set the processes and categories
##########################################################################
sig_procs = ['data_fakes']

bkg_procs = {
    'e_tight_incl': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEtaLt1_5_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEtaLt1_5_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEtaLt1_5_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEtaLt1_5_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEtaLt1_5_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEta1_5to9_9_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEta1_5to9_9_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEta1_5to9_9_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEta1_5to9_9_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_tight_absEta1_5to9_9_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_incl': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt10_0to15_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEtaLt1_5_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt10_0to15_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_tight_absEta1_5to9_9_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],

    'e_fakeable_incl': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEtaLt1_5_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEtaLt1_5_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEtaLt1_5_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEtaLt1_5_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEtaLt1_5_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEta1_5to9_9_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEta1_5to9_9_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEta1_5to9_9_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEta1_5to9_9_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'e_fakeable_absEta1_5to9_9_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_incl': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt10_0to15_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEtaLt1_5_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt10_0to15_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt15_0to20_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt20_0to30_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt30_0to45_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt45_0to65_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal'],
    'mu_fakeable_absEta1_5to9_9_Pt65_0to100000_0': ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal']
}

### BELOW FIRST ENTRY NUMBER (0) IS $BINID AND SECOND 'STRING LABEL' IS $BIN
bins = {
#    'e': [(0, 'electrons_tight_incl_shapes'), (1, 'electrons_tight_absEtaLt1_5_Pt15_0to20_0_shapes'), (2, 'electrons_tight_absEtaLt1_5_Pt20_0to30_0_shapes'), (3, 'electrons_tight_absEtaLt1_5_Pt30_0to45_0_shapes'), (4, 'electrons_tight_absEtaLt1_5_Pt45_0to65_0_shapes'), (5, 'electrons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes'), (6, 'electrons_tight_absEta1_5to9_9_Pt15_0to20_0_shapes'), (7, 'electrons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes'), (8, 'electrons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes'), (9, 'electrons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes'), (10, 'electrons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes')],   
#    'mu': [(0, 'muons_tight_incl_shapes'), (1, 'muons_tight_absEtaLt1_5_Pt10_0to15_0_shapes'), (2, 'muons_tight_absEtaLt1_5_Pt15_0to20_0_shapes'), (3, 'muons_tight_absEtaLt1_5_Pt20_0to30_0_shapes'), (4, 'muons_tight_absEtaLt1_5_Pt30_0to45_0_shapes'), (5, 'muons_tight_absEtaLt1_5_Pt45_0to65_0_shapes'), (6, 'muons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes'), (7, 'muons_tight_absEta1_5to9_9_Pt10_0to15_0_shapes'), (8, 'muons_tight_absEta1_5to9_9_Pt15_0to20_0_shapes'), (9, 'muons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes'), (10, 'muons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes'), (11, 'muons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes'), (12, 'muons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes')]       

    'e_tight_incl': [(0, 'electrons_tight_incl_shapes')],
    'mu_tight_incl': [(0, 'muons_tight_incl_shapes')],

    'e_tight_absEtaLt1_5_Pt15_0to20_0': [(0, 'electrons_tight_absEtaLt1_5_Pt15_0to20_0_shapes')],
    'mu_tight_absEtaLt1_5_Pt10_0to15_0': [(0, 'muons_tight_absEtaLt1_5_Pt10_0to15_0_shapes')],

    'e_tight_absEtaLt1_5_Pt20_0to30_0': [(0, 'electrons_tight_absEtaLt1_5_Pt20_0to30_0_shapes')],
    'mu_tight_absEtaLt1_5_Pt15_0to20_0': [(0, 'muons_tight_absEtaLt1_5_Pt15_0to20_0_shapes')],

    'e_tight_absEtaLt1_5_Pt30_0to45_0': [(0, 'electrons_tight_absEtaLt1_5_Pt30_0to45_0_shapes')],
    'mu_tight_absEtaLt1_5_Pt20_0to30_0': [(0, 'muons_tight_absEtaLt1_5_Pt20_0to30_0_shapes')],

    'e_tight_absEtaLt1_5_Pt45_0to65_0': [(0, 'electrons_tight_absEtaLt1_5_Pt45_0to65_0_shapes')],
    'mu_tight_absEtaLt1_5_Pt30_0to45_0': [(0, 'muons_tight_absEtaLt1_5_Pt30_0to45_0_shapes')],

    'e_tight_absEtaLt1_5_Pt65_0to100000_0': [(0, 'electrons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes')],
    'mu_tight_absEtaLt1_5_Pt45_0to65_0': [(0, 'muons_tight_absEtaLt1_5_Pt45_0to65_0_shapes')],

    'mu_tight_absEtaLt1_5_Pt65_0to100000_0': [(0, 'muons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes')],

    'e_tight_absEta1_5to9_9_Pt15_0to20_0': [(0, 'electrons_tight_absEta1_5to9_9_Pt15_0to20_0_shapes')],
    'mu_tight_absEta1_5to9_9_Pt10_0to15_0': [(0, 'muons_tight_absEta1_5to9_9_Pt10_0to15_0_shapes')],

    'e_tight_absEta1_5to9_9_Pt20_0to30_0': [(0, 'electrons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes')],
    'mu_tight_absEta1_5to9_9_Pt15_0to20_0': [(0, 'muons_tight_absEta1_5to9_9_Pt15_0to20_0_shapes')],

    'e_tight_absEta1_5to9_9_Pt30_0to45_0': [(0, 'electrons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes')],
    'mu_tight_absEta1_5to9_9_Pt20_0to30_0': [(0, 'muons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes')],

    'e_tight_absEta1_5to9_9_Pt45_0to65_0': [(0, 'electrons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes')],
    'mu_tight_absEta1_5to9_9_Pt30_0to45_0': [(0, 'muons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes')],

    'e_tight_absEta1_5to9_9_Pt65_0to100000_0': [(0, 'electrons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes')],
    'mu_tight_absEta1_5to9_9_Pt45_0to65_0': [(0, 'muons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes')],

    'mu_tight_absEta1_5to9_9_Pt65_0to100000_0': [(0, 'muons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes')],

    
    'e_fakeable_incl': [(0, 'electrons_fakeable_incl_shapes')],
    'mu_fakeable_incl': [(0, 'muons_fakeable_incl_shapes')],

    'e_fakeable_absEtaLt1_5_Pt15_0to20_0': [(0, 'electrons_fakeable_absEtaLt1_5_Pt15_0to20_0_shapes')],
    'mu_fakeable_absEtaLt1_5_Pt10_0to15_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt10_0to15_0_shapes')],

    'e_fakeable_absEtaLt1_5_Pt20_0to30_0': [(0, 'electrons_fakeable_absEtaLt1_5_Pt20_0to30_0_shapes')],
    'mu_fakeable_absEtaLt1_5_Pt15_0to20_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt15_0to20_0_shapes')],

    'e_fakeable_absEtaLt1_5_Pt30_0to45_0': [(0, 'electrons_fakeable_absEtaLt1_5_Pt30_0to45_0_shapes')],
    'mu_fakeable_absEtaLt1_5_Pt20_0to30_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt20_0to30_0_shapes')],

    'e_fakeable_absEtaLt1_5_Pt45_0to65_0': [(0, 'electrons_fakeable_absEtaLt1_5_Pt45_0to65_0_shapes')],
    'mu_fakeable_absEtaLt1_5_Pt30_0to45_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt30_0to45_0_shapes')],

    'e_fakeable_absEtaLt1_5_Pt65_0to100000_0': [(0, 'electrons_fakeable_absEtaLt1_5_Pt65_0to100000_0_shapes')],
    'mu_fakeable_absEtaLt1_5_Pt45_0to65_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt45_0to65_0_shapes')],

    'mu_fakeable_absEtaLt1_5_Pt65_0to100000_0': [(0, 'muons_fakeable_absEtaLt1_5_Pt65_0to100000_0_shapes')],

    'e_fakeable_absEta1_5to9_9_Pt15_0to20_0': [(0, 'electrons_fakeable_absEta1_5to9_9_Pt15_0to20_0_shapes')],
    'mu_fakeable_absEta1_5to9_9_Pt10_0to15_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt10_0to15_0_shapes')],

    'e_fakeable_absEta1_5to9_9_Pt20_0to30_0': [(0, 'electrons_fakeable_absEta1_5to9_9_Pt20_0to30_0_shapes')],
    'mu_fakeable_absEta1_5to9_9_Pt15_0to20_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt15_0to20_0_shapes')],

    'e_fakeable_absEta1_5to9_9_Pt30_0to45_0': [(0, 'electrons_fakeable_absEta1_5to9_9_Pt30_0to45_0_shapes')],
    'mu_fakeable_absEta1_5to9_9_Pt20_0to30_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt20_0to30_0_shapes')],

    'e_fakeable_absEta1_5to9_9_Pt45_0to65_0': [(0, 'electrons_fakeable_absEta1_5to9_9_Pt45_0to65_0_shapes')],
    'mu_fakeable_absEta1_5to9_9_Pt30_0to45_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt30_0to45_0_shapes')],

    'e_fakeable_absEta1_5to9_9_Pt65_0to100000_0': [(0, 'electrons_fakeable_absEta1_5to9_9_Pt65_0to100000_0_shapes')],
    'mu_fakeable_absEta1_5to9_9_Pt45_0to65_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt45_0to65_0_shapes')],

    'mu_fakeable_absEta1_5to9_9_Pt65_0to100000_0': [(0, 'muons_fakeable_absEta1_5to9_9_Pt65_0to100000_0_shapes')]
}


channels = ['e_tight_incl', 'e_tight_absEtaLt1_5_Pt15_0to20_0', 'e_tight_absEtaLt1_5_Pt20_0to30_0', 'e_tight_absEtaLt1_5_Pt30_0to45_0', 'e_tight_absEtaLt1_5_Pt45_0to65_0',
            'e_tight_absEtaLt1_5_Pt65_0to100000_0', 'e_tight_absEta1_5to9_9_Pt15_0to20_0', 'e_tight_absEta1_5to9_9_Pt20_0to30_0', 'e_tight_absEta1_5to9_9_Pt30_0to45_0',
            'e_tight_absEta1_5to9_9_Pt45_0to65_0', 'e_tight_absEta1_5to9_9_Pt65_0to100000_0', 
            'mu_tight_incl', 'mu_tight_absEtaLt1_5_Pt10_0to15_0', 'mu_tight_absEtaLt1_5_Pt15_0to20_0', 'mu_tight_absEtaLt1_5_Pt20_0to30_0', 'mu_tight_absEtaLt1_5_Pt30_0to45_0',
            'mu_tight_absEtaLt1_5_Pt45_0to65_0', 'mu_tight_absEtaLt1_5_Pt65_0to100000_0', 'mu_tight_absEta1_5to9_9_Pt10_0to15_0', 'mu_tight_absEta1_5to9_9_Pt15_0to20_0',
            'mu_tight_absEta1_5to9_9_Pt20_0to30_0', 'mu_tight_absEta1_5to9_9_Pt30_0to45_0', 'mu_tight_absEta1_5to9_9_Pt45_0to65_0', 'mu_tight_absEta1_5to9_9_Pt65_0to100000_0',

            'e_fakeable_incl', 'e_fakeable_absEtaLt1_5_Pt15_0to20_0', 'e_fakeable_absEtaLt1_5_Pt20_0to30_0', 'e_fakeable_absEtaLt1_5_Pt30_0to45_0', 'e_fakeable_absEtaLt1_5_Pt45_0to65_0',
            'e_fakeable_absEtaLt1_5_Pt65_0to100000_0', 'e_fakeable_absEta1_5to9_9_Pt15_0to20_0', 'e_fakeable_absEta1_5to9_9_Pt20_0to30_0', 'e_fakeable_absEta1_5to9_9_Pt30_0to45_0',
            'e_fakeable_absEta1_5to9_9_Pt45_0to65_0', 'e_fakeable_absEta1_5to9_9_Pt65_0to100000_0',
            'mu_fakeable_incl', 'mu_fakeable_absEtaLt1_5_Pt10_0to15_0', 'mu_fakeable_absEtaLt1_5_Pt15_0to20_0', 'mu_fakeable_absEtaLt1_5_Pt20_0to30_0', 'mu_fakeable_absEtaLt1_5_Pt30_0to45_0',
            'mu_fakeable_absEtaLt1_5_Pt45_0to65_0', 'mu_fakeable_absEtaLt1_5_Pt65_0to100000_0', 'mu_fakeable_absEta1_5to9_9_Pt10_0to15_0', 'mu_fakeable_absEta1_5to9_9_Pt15_0to20_0',
            'mu_fakeable_absEta1_5to9_9_Pt20_0to30_0', 'mu_fakeable_absEta1_5to9_9_Pt30_0to45_0', 'mu_fakeable_absEta1_5to9_9_Pt45_0to65_0', 'mu_fakeable_absEta1_5to9_9_Pt65_0to100000_0'
      ]

##########################################################################
# Set input shape files
##########################################################################
files = {
    'e_tight_incl': args.input,
    'e_tight_absEtaLt1_5_Pt15_0to20_0': args.input,
    'e_tight_absEtaLt1_5_Pt20_0to30_0': args.input,
    'e_tight_absEtaLt1_5_Pt30_0to45_0': args.input,
    'e_tight_absEtaLt1_5_Pt45_0to65_0': args.input,
    'e_tight_absEtaLt1_5_Pt65_0to100000_0': args.input,
    'e_tight_absEta1_5to9_9_Pt15_0to20_0': args.input,
    'e_tight_absEta1_5to9_9_Pt20_0to30_0': args.input,
    'e_tight_absEta1_5to9_9_Pt30_0to45_0': args.input,
    'e_tight_absEta1_5to9_9_Pt45_0to65_0': args.input,
    'e_tight_absEta1_5to9_9_Pt65_0to100000_0': args.input,
    'mu_tight_incl': args.input,
    'mu_tight_absEtaLt1_5_Pt10_0to15_0': args.input,
    'mu_tight_absEtaLt1_5_Pt15_0to20_0': args.input,
    'mu_tight_absEtaLt1_5_Pt20_0to30_0': args.input,
    'mu_tight_absEtaLt1_5_Pt30_0to45_0': args.input,
    'mu_tight_absEtaLt1_5_Pt45_0to65_0': args.input,
    'mu_tight_absEtaLt1_5_Pt65_0to100000_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt10_0to15_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt15_0to20_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt20_0to30_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt30_0to45_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt45_0to65_0': args.input,
    'mu_tight_absEta1_5to9_9_Pt65_0to100000_0': args.input,

    'e_fakeable_incl': args.input,
    'e_fakeable_absEtaLt1_5_Pt15_0to20_0': args.input,
    'e_fakeable_absEtaLt1_5_Pt20_0to30_0': args.input,
    'e_fakeable_absEtaLt1_5_Pt30_0to45_0': args.input,
    'e_fakeable_absEtaLt1_5_Pt45_0to65_0': args.input,
    'e_fakeable_absEtaLt1_5_Pt65_0to100000_0': args.input,
    'e_fakeable_absEta1_5to9_9_Pt15_0to20_0': args.input,
    'e_fakeable_absEta1_5to9_9_Pt20_0to30_0': args.input,
    'e_fakeable_absEta1_5to9_9_Pt30_0to45_0': args.input,
    'e_fakeable_absEta1_5to9_9_Pt45_0to65_0': args.input,
    'e_fakeable_absEta1_5to9_9_Pt65_0to100000_0': args.input,
    'mu_fakeable_incl': args.input,
    'mu_fakeable_absEtaLt1_5_Pt10_0to15_0': args.input,
    'mu_fakeable_absEtaLt1_5_Pt15_0to20_0': args.input,
    'mu_fakeable_absEtaLt1_5_Pt20_0to30_0': args.input,
    'mu_fakeable_absEtaLt1_5_Pt30_0to45_0': args.input,
    'mu_fakeable_absEtaLt1_5_Pt45_0to65_0': args.input,
    'mu_fakeable_absEtaLt1_5_Pt65_0to100000_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt10_0to15_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt15_0to20_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt20_0to30_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt30_0to45_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt45_0to65_0': args.input,
    'mu_fakeable_absEta1_5to9_9_Pt65_0to100000_0': args.input
}

inputs = {
    'e_tight_incl': 'electron',
    'e_tight_absEtaLt1_5_Pt15_0to20_0': 'electron',
    'e_tight_absEtaLt1_5_Pt20_0to30_0': 'electron',
    'e_tight_absEtaLt1_5_Pt30_0to45_0': 'electron',
    'e_tight_absEtaLt1_5_Pt45_0to65_0': 'electron',
    'e_tight_absEtaLt1_5_Pt65_0to100000_0': 'electron',
    'e_tight_absEta1_5to9_9_Pt15_0to20_0': 'electron',
    'e_tight_absEta1_5to9_9_Pt20_0to30_0': 'electron',
    'e_tight_absEta1_5to9_9_Pt30_0to45_0': 'electron',
    'e_tight_absEta1_5to9_9_Pt45_0to65_0': 'electron',
    'e_tight_absEta1_5to9_9_Pt65_0to100000_0': 'electron',
    'mu_tight_incl': 'muon',
    'mu_tight_absEtaLt1_5_Pt10_0to15_0': 'muon',
    'mu_tight_absEtaLt1_5_Pt15_0to20_0': 'muon',
    'mu_tight_absEtaLt1_5_Pt20_0to30_0': 'muon',
    'mu_tight_absEtaLt1_5_Pt30_0to45_0': 'muon',
    'mu_tight_absEtaLt1_5_Pt45_0to65_0': 'muon',
    'mu_tight_absEtaLt1_5_Pt65_0to100000_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt10_0to15_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt15_0to20_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt20_0to30_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt30_0to45_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt45_0to65_0': 'muon',
    'mu_tight_absEta1_5to9_9_Pt65_0to100000_0': 'muon',

    'e_fakeable_incl': 'electron',
    'e_fakeable_absEtaLt1_5_Pt15_0to20_0': 'electron',
    'e_fakeable_absEtaLt1_5_Pt20_0to30_0': 'electron',
    'e_fakeable_absEtaLt1_5_Pt30_0to45_0': 'electron',
    'e_fakeable_absEtaLt1_5_Pt45_0to65_0': 'electron',
    'e_fakeable_absEtaLt1_5_Pt65_0to100000_0': 'electron',
    'e_fakeable_absEta1_5to9_9_Pt15_0to20_0': 'electron',
    'e_fakeable_absEta1_5to9_9_Pt20_0to30_0': 'electron',
    'e_fakeable_absEta1_5to9_9_Pt30_0to45_0': 'electron',
    'e_fakeable_absEta1_5to9_9_Pt45_0to65_0': 'electron',
    'e_fakeable_absEta1_5to9_9_Pt65_0to100000_0': 'electron',
    'mu_fakeable_incl': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt10_0to15_0': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt15_0to20_0': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt20_0to30_0': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt30_0to45_0': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt45_0to65_0': 'muon',
    'mu_fakeable_absEtaLt1_5_Pt65_0to100000_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt10_0to15_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt15_0to20_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt20_0to30_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt30_0to45_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt45_0to65_0': 'muon',
    'mu_fakeable_absEta1_5to9_9_Pt65_0to100000_0': 'muon'
}




##########################################################################
# Create CH entries and load shapes
##########################################################################
for chn in channels:
    ana = ['ttH']
    era = ['13TeV']
    cb.AddObservations(['*'], ana, era, [chn], bins[chn])                       ### DEF LINES
    cb.AddProcesses(['*'], ana, era, [chn], bkg_procs[chn], bins[chn], False)   ### DEF LINES
    cb.AddProcesses(['*'], ana, era, [chn], sig_procs, bins[chn], True)         ### DEF LINES





##########################################################################
# Define systematic uncertainties
##########################################################################

#signal = cb.cp().signals().process_set()


#################### Yield systematics ############################

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'EWK_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['EWK'], 1.5))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'TT_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['TT'], 1.5))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'TTW_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['TTW'], 1.2))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'TTZ_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['TTZ'], 1.2))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'signal_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['signal'], 2.0))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'Rares_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['Rares'], 1.5))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'tH_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['tH'], 2.0))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'TTWW_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['TTWW'], 1.5))

cb.cp().AddSyst( ## Correl. across $CHANNEL and $BIN
    cb, 'ttH_hbb_unc', 'lnN', ch.SystMap('channel', 'process')
        (channels, ['ttH_hbb'], 2.0))

################### Shape systematics #############################

cb.cp().AddSyst(  ## CORREL ACROSS $CHANNEL, CORREL ACROSS $BIN 
        cb, 'CMS_ttHl_JES', 'shape', ch.SystMap('channel', 'process')
            (channels, ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal','data_fakes'], 1.00)) 

cb.cp().AddSyst(  ## CORREL ACROSS $CHANNEL, CORREL ACROSS $BIN 
        cb, 'CMS_ttHl_JER', 'shape', ch.SystMap('channel', 'process')
            (channels, ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal','data_fakes'], 1.00)) 

cb.cp().AddSyst(  ## CORREL ACROSS $CHANNEL, CORREL ACROSS $BIN 
        cb, 'CMS_ttHl_UnclusteredEn', 'shape', ch.SystMap('channel', 'process')
            (channels, ['EWK', 'TT', 'TTW','TTZ','Rares','tH', 'TTWW', 'ttH_hbb', 'signal','data_fakes'], 1.00)) 





##########################################################################
# Load the shapes
##########################################################################
for chn in channels:
    cb.cp().channel([chn]).ExtractShapes(
        '%s/%s/%s' % (shapes_dir, inputs[chn], files[chn]),
        '$BIN/$PROCESS', '$BIN/$PROCESS_$SYSTEMATIC')





##########################################################################
# Create bin-by-bin
##########################################################################
bbb = ch.BinByBinFactory()
bbb.SetPattern('CMS_$ANALYSIS_$BIN_$ERA_$PROCESS_bin_$#')   #### DEFAULT LINE
bbb.SetAddThreshold(0.1)
bbb.SetMergeThreshold(0.5)  # For now we merge, but to be checked
bbb.SetFixNorm(True)
bbb.MergeAndAdd(cb.cp().backgrounds(), cb)

cb.PrintAll()


##########################################################################
# Write the cards
##########################################################################
writer = ch.CardWriter('$TAG/datacard.txt',
                       '$TAG/shapes.root')
writer.SetWildcardMasses([])  # We don't use the $MASS property here
writer.SetVerbosity(1)
x = writer.WriteCards('%s/cmb' % args.output, cb)  # All cards combined
print x
x['%s/cmb/datacard.txt' % args.output].PrintAll()
for chn in channels:  # plus a subdir per channel
    writer.WriteCards('%s/%s' % (args.output, chn), cb.cp().channel([chn]))



