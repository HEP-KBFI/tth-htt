#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Author: Karl Ehatäht

#TODO: implement H-> gammagamma decay properly

'''Manual

The script generates decay chains from MINIADO MC sample files and analyzes them if necessary.
It helps to see, which decay categories are prevalent in a given process; this information is useful when deciding, say,
which decays should be modeled in the MEM.

The workflow is split into the following four steps:
1) generate the cmsRun job that outputs decay chain table, given the sample name

   inputs:        RLE list (of the format run:lumi:event, each number on a separate line)
                  sample name (i.e. 'process_name_specific' value in tthAnalyzeSamples_2016 dictionaries)
                  path to DAS python script
   prerequisites: voms proxy is initialized
   outputs:       a cmsRun job written in python

   example command:

     ./scripts/decay_chain_parser.py -c ~/cli.py -g ttHJetToNonbb_M125 -i ~/rle_list.txt -o ~/printGenParticles_miniAOD_cfg.py -v

      The script takes path to DAS python script (-c), path to RLE list (-i) and sample name (-g) as an input and
      output the cmsRun python job (-o). All internal logging is exposed via the verbose flag (-v).

   comments: What the script does in this step is the following:
               a) test if voms proxy is up (via voms-proxy-info)
               b) request the number of MINIAOD files the sample has through the DAS script provided in the CLI arguments
               c) request the list of MINIAOD files (again, by using the same DAS script)
               d) if it's possible to construct a URI sfor all sample files then the cmsRun
                  script will be generated and the script exits normally
             Note that the voms proxy must be valid for at least an hour; thus initialize the proxy beforehand with:

               voms-proxy-init -voms cms -valid 1:00

             Also, the script works only if the samples are stored on either T2_CH_CERN or T2_FR_IPHC, whereas
             the former has higher priority (b/c it's the EOS storage). The reason behind requesting
             the number of files is that we'd know how to limit the output at step c).
             You can download the DAS CLI script from https://cmsweb.cern.ch/das/.

   output format: see the template held by the variable `printGenParticles_miniAOD_cfg`

2) run the said cmsRun job

   inputs:        path to cmsRun job obtained in 1)
   prerequisites: fist and foremost, voms proxy must be up;
                  the script is known to work only with the following workspace environment:
                    CMSSW_VERSION=CMSSW_8_0_19
                    SCRAM_ARCH=slc6_amd64_gcc530
                  there's no need to pull any packages from git -- a simple workspace initialization
                  does the trick (see comments below)
   outputs:       output of the said job redirected to a file (must be done by the user manually)

   example command:

     cmsRun ~/printGenParticles_miniAOD_cfg.py &> ~/out.log

     The operator &> in Bash redirects both stdout and stderr to the file (since Bash 4);
     you can view the progress in a different shell session with `tail -F` command, e.g.

       tail -F ~/out.log

   comments: As already mentioned earlier, the cmsRun jobs is known to work only in CMSSW_8_0_19 workspace
             and with slc6_amd64_gcc530 architecture settings. If you don't have the workspace available
             you can initialize the environment with the following commands (no need to pull any packages
             from git or anywhere else!):

               mkdir ~/VHbbNtuples_8_0_x
               cd $_
               export SCRAM_ARCH=slc6_amd64_gcc530
               cmsrel CMSSW_8_0_19
               cd $_/src
               cmsenv

             That's it!

   output format: the redirected output should have the following format:

<snip>

Begin processing the 23rd record. Run 1, Event 11547337, LumiSection 28957 at 21-Jan-2017 16:08:02.923 EET

[ParticleListDrawer] analysing particle collection prunedGenParticles
 idx  |    ID -       Name |Stat|  Mo1  Mo2  Da1  Da2 |nMo nDa|    pt       eta     phi   |     px         py         pz        m     |
    0 |  2212 -         p+ |  4 |   -1   -1    2   92 |  0 13 |   0.000  29256.000  0.000 |      0.000      0.000   6500.000    0.938 |
    1 |  2212 -         p+ |  4 |   -1   -1    3   92 |  0 11 |   0.000 -29256.000  0.000 |      0.000      0.000  -6500.000    0.938 |
    2 |    21 -          g | 21 |    0    0    4    7 |  1  4 |   0.000  23288.178  0.000 |      0.000      0.000    532.178    0.000 |
    3 |    21 -          g | 21 |    1    1    4    7 |  1  4 |   0.000 -23946.422  0.000 |      0.000      0.000  -1190.422    0.000 |
    4 |    25 -         h0 | 22 |    2    3    9    9 |  2  1 | 343.670      0.359 -0.732 |    255.631   -229.700    126.177  125.000 |
    5 |     6 -          t | 22 |    2    3    8   90 |  2  4 | 387.929     -0.035  2.493 |   -309.087    234.424    -13.530  174.060 |
    6 |    -6 -       tbar | 22 |    2    3   10   10 |  2  1 | 213.727     -1.378 -1.422 |     31.730   -211.359   -396.828  172.058 |

</snip>

3) aggregate the resulting table into human-readable format

   inputs:  output of the cmsRun job obtained in 2)
   outputs: a new file containing the decay chains in human-readable format

   example command:

     ./scripts/decay_chain_parser.py -i ~/out.log -o ~/out_parsed.log -p tth -v

     The script takes the output of cmsRun job as an input (-i), parses it considering tth process (-p) and places
     the output to ~/out_parsed.log (-o).

   comments: The explanation of how the parsing is carried out is explained in the comments of process() function.

   output format: the output file should contain something similar to the following lines:

<snip>

--------------------------------------------------------------------------------
1:28957:11547337
p+ -> B*+ -> B+ -> D*bar0 -> Dbar0
p+ -> B*+ -> B+ -> D_s+ -> eta -> gamma
p+ -> B*- -> B- -> D*0 -> D0
p+ -> B*- -> B- -> nu_taubar
p+ -> B*- -> B- -> tau- -> nu_tau
p+ -> B*- -> B- -> tau- -> pi+
p+ -> B*- -> B- -> tau- -> pi-
p+ -> B*- -> B- -> tau- -> pi0 -> gamma
p+ -> g -> d
p+ -> g -> dbar
p+ -> g -> h0 -> tau+ -> gamma
p+ -> g -> h0 -> tau+ -> mu+
p+ -> g -> h0 -> tau+ -> nu_mu
p+ -> g -> h0 -> tau+ -> nu_taubar
p+ -> g -> h0 -> tau- -> nu_tau
p+ -> g -> h0 -> tau- -> pi-
p+ -> g -> h0 -> tau- -> pi0 -> gamma

</snip>

4) draw some statistical figures (i.e. event counts) based on some process

   inputs:  output of the parsing obtained in 3)
   outputs: summary of the decays in human-readable format, printed on screen and to a file

   example command:

     ./scripts/decay_chain_parser.py -i ~/out_parsed.log -s tth

      The script takes output of previous point (~/out_parsed.log) as an input (-i) and creates
      a summary for it (-s), while considering tth process. The lines printed on screen can be
      simulataneously saved to a file with -o option.

   comments: see comments in aggregate(), stat() and the functions refered therein

   output format: all output is both printed on screen and saved to a file, and
                  should contain something similar to the following lines:

<snip>

--------------------------------------------------------------------------------
H->ZZ->(l)(l)(q)(q),ttbar->WW->(l)(l)
        Channel: 4l0tau (+ 4 jets)
        Number of events: 4 (0.53%)
        RLE numbers:
                1:8612:1711189
                1:15007:2981892
                1:8907:1769736
                1:16512:3280960
        Initiated by gg: 2 (50.00%)
                1:8612:1711189
                1:16512:3280960
        Initiated by gq: 1 (25.00%)
                1:8907:1769736
        Initiated by qq: 1 (25.00%)
                1:15007:2981892
--------------------------------------------------------------------------------

</snip><snip>

Channels:
        3l1tau: 354 (47.26%)
                H->(tau->h)(tau->l),ttbar->WW->(l)(l)                             298      (84.18%/39.79%)
                H->WW->(l)(tau->h),ttbar->WW->(l)(l)                              51       (14.41%/6.81%)
                H->WW->(tau->h)(tau->l),ttbar->WW->(l)(l)                         5        (1.41%/0.67%)

</snip><snip>

Number of H->tautau events: 421 (56.21%)
Number of H->WW     events: 289 (38.58%)
Number of H->ZZ     events: 37 (4.94%)
Number of H->mumu   events: 2 (0.27%)
Number of pp->gg events: 441 (58.88%)
Number of pp->gq events: 184 (24.57%)
Number of pp->qq events: 124 (16.56%)
Total number of events: 749

</snip>

   The final decay products are surrounded by parentheses. In the example above, 8.57% (or 6 events out of 70)
   contain a process in which Higgs decays into a pair of W boson, from which one W decays leptonically and the other
   decays into a tau, which further decays leptonically; the top pair decays into W bosons (+b quarks which is not
   shown here), from which one W decays leptonically and the other hadronically (thus producing two jets). The final
   signature therefore includes 3l leptons, no hadronic taus and 4 jets. Out of these 6 events, 4 are initated by
   gluon-gluon fusion and the 2 remaining events come from a gluon-quark mix (whatever that means). Each subdivision
   also lists the corresponding RLE numbers for debugging purposes.

                                 ###########################################

In all steps (except for 2nd one of course) the script checks if all input files and the directories to
the output files exist; if they don't the script bails out. Currently, the aggregation and statistical
summary can be performed only for the tth and ttz processes.

In case you want to parse or draw statistics from existing output of the cmsRun job, you can supply a secondary RLE
file which is expected to be a subset of the initial RLE file (passed via -i/--input option at stage 1)). This can
be achieved with -j/--secondary-input option.

Also, if you want to save the RLE numbers of each specific decay channel to a separate file for later processing,
you can do that by specificing the output directory where these files will be saved via -r/--secondary-output option.
If the output directory doesn't exist, you can always pass -f/--force option so that the folder will be created for you.
The RLE files are created for each decay mode, but also split by process initiators. Since the number of such decay
modes may be huge, it is wise to keep them in a dedicated subdirectory as it could be painful to delete them later on.

Disclaimer: the program is tested with only ttHJetToNonbb_M125, TTZToLLNuNu_M-10 and TTZToLLNuNu_M-10_ext1 samples,
            and tth & ttz hypotheses.

'''

################################################### IMPORTS ###################################################

import argparse, logging, sys, subprocess, datetime, os, re, jinja2, codecs, copy, itertools

try:
  __import__('imp').find_module('tthAnalysis')
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
except ImportError:
  sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'python'))
  from tthAnalyzeSamples_2016 import samples_2016

############################################### GLOBAL CONSTANTS ##############################################

SEP = '-' * 80

def run_cmd(cmd_str):
  # runs a shell command
  # if the stderr is empty, then returns stdout; otherwise throw an exception
  logging.debug("Requested command: {cmd}".format(cmd = cmd_str))
  cmd = subprocess.Popen(
    cmd_str,
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE,
    shell  = True,
  )
  cmd_stdout, cmd_stderr = cmd.communicate()
  if cmd_stderr:
    raise ValueError("Command {cmd_str} failed: {reason}".format(cmd_str = cmd_str, reason = cmd_stderr))
  return cmd_stdout

def read_rles(input):
  if not os.path.isfile(input):
    logging.error("No such file: {file}".format(file = input))

  logging.debug("Reading RLE numbers from {rle_input}".format(rle_input = input))
  rles = filter(lambda x: x != '', map(lambda x: x.rstrip('\n'), open(input, 'r').readlines()))
  rle_pattern = re.compile('\d+:\d+:\d+')
  if not all(map(lambda x: rle_pattern.match(x), rles)):
    logging.error("File {rle_filename} contains invalid RLE number(s)".format(rle_filename = input))
    sys.exit(1)
  if not rles:
    logging.error("You must provide at least one RLE number")
    sys.exit(1)
  logging.debug("Read {nof_rles} RLE numbers".format(nof_rles = len(rles)))
  return rles

printGenParticles_miniAOD_cfg = """import FWCore.ParameterSet.Config as cms

# file generated by the following command:
# {{ command }}

process = cms.Process('printGenParticles')
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('80X_mcRun2_asymptotic_2016_v3')

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32({{ rle_list|length }})
)

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(*({% for f in file_list %}
    '{{ f }}',{% endfor %}
  )),
  eventsToProcess = cms.untracked.VEventRange(*({% for rle in rle_list %}
    '{{ rle }}',{% endfor %}
  ))
)

process.s = cms.Sequence()
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.printGenParticleList = cms.EDAnalyzer('ParticleListDrawer',
    src              = cms.InputTag('prunedGenParticles'),
    maxEventsToPrint = cms.untracked.int32(10000)
)
process.s += process.printGenParticleList
process.p = cms.Path(process.s)

"""

################################################### CLASSES ###################################################

class MultipleStream():
  # a class which is able to write the same lines to multiple output streams (e.g. sys.stdout and file() descriptors)

  def __init__(self, streams):
    # pass a list of output streams here, e.g. [sys.stdout, open('filename', 'w'),]
    self.streams = []
    self.filestreams = []
    for stream in streams:
      if stream:
        if isinstance(stream, str):
          self.filestreams.append(open(stream, 'w'))
        else:
          self.streams.append(stream)

  def __enter__(self):
    return self

  def __exit__(self, exc_type, exc_val, exc_tb):
    for stream in self.filestreams:
      stream.close()

  def write(self, lines):
    for stream in self.streams:
      stream.write(lines)
    for stream in self.filestreams:
      stream.write(lines)

  def writeln(self, line):
    # same as write, but append newline character to the output (similar to Java's System.out.println())
    self.write("%s\n" % line)

class Particle:
  def __init__(self, line, header):
    # transforms a line of decay chain table into particle object
    # line -- a line in the decay chain table
    # header -- header of the table in dict form, where the keys are column labels and values column numbers
    line = (''.join(line.split('|'))).split()
    self.idx  = int(line[header['idx']]) # the row id
    self.id   = int(line[header['ID']])  # particle id
    self.name = line[header['Name']]     # particle symbol (must have)
    self.mo1  = int(line[header['Mo1']]) # 1st mother (must have)
    self.mo2  = int(line[header['Mo2']]) # 2nd mother (must have)
    self.da1  = int(line[header['Da1']]) # 1st daughter
    self.da2  = int(line[header['Da2']]) # 2nd daughter
    self.nda  = int(line[header['nDa']]) # number of daughters
    # the fields followed by (must have) must be present! the other fields are optional and only included for the sake
    # of completeness

###################################### FIRST STEP: PARSING CMSRUN OUTPUT ######################################

def recursive_traverse(results, childmap, prefix, children):
  # here we want to build a list of decay chains
  # 0 -> 2 -> 3 -> ...
  # 0 -> 4 -> 5 -> 6 -> ...
  # ...
  # 1 -> 7 -> 8 -> 9 -> ...
  # 1 -> 10 -> 11 -> 12 -> ...
  #
  # from the map
  #
  # 0 -> daughters of 0
  # 1 -> daughters of 1
  # 2 -> daughters of 2
  # etc
  #
  # we just traverse the map by following the each daughter by the row number until we hit a dead end -- the particle
  # we are currently at has no childer, which means that we have one complete decay chain;
  # every time we do a lookup in the map the current (partial) decay chain is passed around
  # looping over daughters is iterative; partial decay chains are deepcopied so that that we won't edit the partial
  # decay chain returned by previous iteration
  if children:
    for child in children:
      new_prefix = copy.deepcopy(prefix)
      new_prefix.append(child)
      recursive_traverse(results, childmap, new_prefix, childmap[child])
  else:
    results.append(prefix)

def process(lines, second_decay_products):
  # the function parses a decay chain table corresponding to one event which is printed out during the cmsRun job

  # first we have to extract the header and split each line by the pipe character (`|`)
  split = lines.split('\n')
  header = (''.join(split[0].split('|'))).split()
  header = { header[i]: i for i in range(len(header)) }

  # build the list of particles such that we can refer to each particle via the row index
  # the row index is crucial part here b/c all mother-daughter relationships are based on the row-index
  # e.g. if a particle at row 5 has two daughters -- 25 and 50 -- then the particles' 25 and 50 mother is 5
  pArr = []
  for line in split[1:]:
    pArr.append(Particle(line, header))

  # build a map: particle row ID -> childern's row IDs
  # the map is built such that we loop over all the particles that we refer to via the row number, and
  # use their mother as the map index and current row number as the daughter index;
  # the reason behind this is simple: one mother might have more than two daughters, which means that
  # directly reading the daughter particles does not suffice as we might not catch all the daughters
  childmap = { i : [] for i in range(len(pArr)) }
  for i in range(2, len(pArr)):
    particle = pArr[i]
    if i not in childmap[particle.mo1]:
      childmap[particle.mo1].append(i)
    if i not in childmap[particle.mo2]:
      childmap[particle.mo2].append(i)

  # at this point we have a map
  # 0 -> daughters of 0
  # 1 -> daughters of 1
  # 2 -> daughters of 2
  # etc
  # since all decay chains start from 0 and 1 (that correspond to the two protons), we have to recursively
  # traverse the decay chain map only for the first two particles
  decay_chain = []
  for i in range(2):
    recursive_traverse(decay_chain, childmap, [i], childmap[i])

  decay_chain_str = [map(lambda y: pArr[y].name, x) for x in decay_chain]           # replace row ID with particle name
  decay_chain_str = [[x[0] for x in itertools.groupby(y)] for y in decay_chain_str] # remove successive duplicates
  decay_chain_str = filter(lambda x: len(x) > 2, decay_chain_str)                   # keep decays w/ at least 3 particles
  if second_decay_products:                                                         # filter out 2nd lvl decay products
    decay_chain_str = filter(lambda x: x[2] in second_decay_products, decay_chain_str)
  return '\n'.join(sorted(set([' -> '.join(x) for x in decay_chain_str])))          # each decay chain connected with an arrow

############################ SECOND STEP: AGGREGATING RESULTS FROM THE FIRSTST STEP ###########################

def get_taup_decay_mode(decay_chains, taup_idx):
  # initialize empty dict (so that all keys and values are present)
  taup = {
    'l' : 0,
    'h' : 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return taup

  # filter out the decay chains that contain only tau- daughters at position taun_idx
  taup_daughters = set(x[taup_idx] for x in decay_chains)

  if {'e+', 'nu_e', 'nu_taubar'}.issubset(taup_daughters) or {'mu+', 'nu_mu', 'nu_taubar'}.issubset(taup_daughters):
    # if tau+ decays either into e+, nu_e and nu_taubar, or into mu+, nu_mu and nu_taubar, then this decay mode is leptonic
    taup['l'] = 1
  else:
    # otherwise it's hadronic tau
    taup['h'] = 1
  return taup

def get_taun_decay_mode(decay_chains, taun_idx):
  # initialize empty dict (so that all keys and values are present)
  taun = {
    'l' : 0,
    'h' : 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return taun

  # filter out the decay chains that contain only tau+ daughters at position taup_idx
  taup_daughters = set(x[taun_idx] for x in decay_chains)

  if {'e-', 'nu_ebar', 'nu_tau'}.issubset(taup_daughters) or {'mu-', 'nu_mubar', 'nu_tau'}.issubset(taup_daughters):
    # if tau- decays either into e-, nu_ebar and nu_tau, or into mu-, nu_mubar and nu_tau, then this decay mode is leptonic
    taun['l'] = 1
  else:
    # otherwise it's hadronic tau
    taun['h'] = 1
  return taun

def get_Wp_decay_mode(decay_chains, Wp_idx):
  # initialize empty dict (so that all keys and values are present)
  Wp = {
    't': get_taup_decay_mode([], 0),
    'q': 0,
    'l': 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return Wp

  # filter out the decay chains that contain only W+ daughters at position Wp_idx
  Wp_daughters = set(x[Wp_idx] for x in decay_chains)

  if {'e+', 'nu_e'}.issubset(Wp_daughters) or {'mu+', 'nu_mu'}.issubset(Wp_daughters):
    # if W+ decays into e+ and nu_e, or mu+ and nu_mu, then the decay mode is leptonic
    Wp['l'] = 1
  elif {'tau+', 'nu_tau'}.issubset(Wp_daughters):
    # if W+ decays into tau+ and nu_tau, then we must further inspect into which particles the tau+ decays
    taup_chains = filter(lambda x: x[Wp_idx] == 'tau+', decay_chains)
    Wp['t'] = get_taup_decay_mode(taup_chains, Wp_idx + 1)
  else:
    # otherwise the decay mode is hadronic (produces two jets)
    Wp['q'] = 2

  return Wp

def get_Wn_decay_mode(decay_chains, Wn_idx):
  # initialize empty dict (so that all keys and values are present)
  Wn = {
    't': get_taun_decay_mode([], 0),
    'q': 0,
    'l': 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return Wn

  # filter out the decay chains that contain only W- daughters at position Wn_idx
  Wn_daughters = set(x[Wn_idx] for x in decay_chains)

  if {'e-', 'nu_ebar'}.issubset(Wn_daughters) or {'mu-', 'nu_mubar'}.issubset(Wn_daughters):
    # if W- decays into e- and nu_ebar, or mu- and nu_mubar, then the decay mode is leptonic
    Wn['l'] = 1
  elif {'tau-', 'nu_taubar'}.issubset(Wn_daughters):
    # if W- decays into tau- and nu_taubar, then we must further inspect into which particles the tau- decays
    taun_chains = filter(lambda x: x[Wn_idx] == 'tau-', decay_chains)
    Wn['t'] = get_taun_decay_mode(taun_chains, Wn_idx + 1)
  else:
    # otherwise the decay mode is hadronic (produces two jets)
    Wn['q'] = 2

  return Wn

def get_gamma_decay_mode(decay_chains, gamma_idx):
  # initialize empty dict (so that all keys and values are present)
  gamma = {
    'l' : 0,
    't' : [get_taup_decay_mode([], 0), get_taun_decay_mode([], 0)],
  }
  # let's consider only the case in which the photon decays into a lepton pair

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return gamma

  gamma_daughters = set(x[gamma_idx + 1] for x in filter(lambda x: len(x) > gamma_idx + 1, decay_chains))
  if {'e+', 'e-'}.issubset(gamma_daughters) or {'mu+', 'mu-'}.issubset(gamma_daughters):
    # photon decays into electron-positron or muon-antimuon pair
    gamma['l'] = 2
  elif {'tau+', 'tau-'}.issubset(gamma_daughters):
    # photon decays into tau-antitau pair, which further decays
    taup_chains = filter(lambda x: x[gamma_idx] == 'tau+', decay_chains)
    taun_chains = filter(lambda x: x[gamma_idx] == 'tau+', decay_chains)
    gamma['t'] = [ get_taup_decay_mode(taup_chains, gamma_idx + 1),
                   get_taun_decay_mode(taun_chains, gamma_idx + 1) ]

  return gamma

def get_ZZ_decay_modes(decay_chains, ZZ_idx):
  # initialize empty dict (so that all keys and values are present)
  Z = {
    't'  : [ get_taup_decay_mode([], 0), get_taun_decay_mode([], 0)],
    'q'  : 0,
    'l'  : 0,
    'nu' : 0,
  }
  ZZ = [copy.deepcopy(Z), copy.deepcopy(Z)]

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return ZZ

  # filter out the decay chains that contain only Z0 daughters at position Z0_idx
  ZZ_daughters = set(x[ZZ_idx] for x in decay_chains)

  # Z -> W+W- adds more complications to the problem, b/c the W's might decay into taus, which further decay into
  # leptons and hadronic taus; this is unlinkely if the Z's come from higgs decay
  # in ttZ this decay mode should be taken into account, though, but then again we don't have to process this decay
  # here b/c there won't be any Z pairs in the process (I think)
  if {'W+', 'W-'}.issubset(ZZ_daughters):
    raise ValueError("Z -> W+ W- unimplemented")

  # the hard part deducing the correct decay chain from a list of decay chains is that the human-readable decay chains
  # (i.e. the input) doesn't distringuish between different Z0's; therefore we must handle the following cases
  # 1) both Z's decay into the same lepton or tau pair
  # 2) the Z's decay into different set of particles
  # we take advantage from the fact that Z always decays into two particles

  if len(ZZ_daughters) == 2:
    # both Z's decay into the same pair of particles

    if {'e+', 'e-'}.issubset(ZZ_daughters) or {'mu+', 'mu-'}.issubset(ZZ_daughters):
      # both Z's decay into either electron-positron or muon-antimuon pair
      ZZ[0]['l'] = 2
      ZZ[1]['l'] = 2

    elif {'tau+', 'tau-'}.issubset(ZZ_daughters):
      # both Z's decay into tau-antitau pair which we need to further investigate
      # this example is even more contrived, because we now have decay chains like
      # p+ -> g -> h0 -> Z -> tau+ -> ...
      # p+ -> g -> h0 -> Z -> tau+ -> ...
      # which might lead to different final products
      # therefore we cannot rely on functions get_taup_decay_mode() and get_taun_decay_mode(), because the tau decay
      # products might contain a mixture of both, which means that we must find the daughter particles manually;
      # note that we don't really care about the order of Z bosons here, we just have to keep track of the variable
      # assignment consistently, nothing else

      # get tau+ and tau- decay products of both Z's
      Z_taup = filter(lambda x: x[ZZ_idx] == 'tau+', decay_chains)
      Z_taun = filter(lambda x: x[ZZ_idx] == 'tau-', decay_chains)
      Z_taup_daughters = set(x[ZZ_idx + 1] for x in Z_taup)
      Z_taun_daughters = set(x[ZZ_idx + 1] for x in Z_taun)

      # record the leptonic decays of both tau+'s
      Z_taup_da = []
      if {'e+', 'nu_e', 'nu_taubar'}.issubset(Z_taup_daughters):
        Z_taup_daughters -= {'e+', 'nu_e', 'nu_taubar'}
        Z_taup_da.append('l')
      if {'mu+', 'nu_mu', 'nu_taubar'}.issubset(Z_taup_daughters):
        Z_taup_daughters -= {'mu+', 'nu_mu', 'nu_taubar'}
        Z_taup_da.append('l')

      if len(Z_taup_da) == 0:
        # if none of the tau+'s decayed leptonically, then this means that they decayed hadronically
        ZZ[0]['t'][0]['h'] = 1
        ZZ[1]['t'][0]['h'] = 1

      elif len(Z_taup_da) == 1:
        # if only one of the tau+'s decayed leptonically
        # however, we must take care of the possibility that both tau+'s decayed into the same leptons
        if Z_taup_daughters:
          # only one of the tau+'s decayed leptonically
          ZZ[0]['t'][0]['h'] = 1
          ZZ[1]['t'][0]['l'] = 1
        else:
          # still, both decayed leptonically, but into different leptons
          ZZ[0]['t'][0]['l'] = 1
          ZZ[1]['t'][0]['l'] = 1

      elif len(Z_taup_da) == 2:
        # if both of the tau+'s decayed leptonically
        ZZ[0]['t'][0]['l'] = 1
        ZZ[1]['t'][0]['l'] = 1

      else:
        raise ValueError("Something's wrong")

      # record the leptonic decays of both tau-'s
      Z_taun_da = []
      if {'e-', 'nu_ebar', 'nu_tau'}.issubset(Z_taun_daughters):
        Z_taun_daughters -= {'e-', 'nu_ebar', 'nu_tau'}
        Z_taun_da.append('l')
      if {'mu-', 'nu_mubar', 'nu_tau'}.issubset(Z_taun_daughters):
        Z_taun_daughters -= {'mu-', 'nu_mubar', 'nu_tau'}
        Z_taun_da.append('l')

      if len(Z_taun_da) == 0:
        # if none of the tau-'s decayed leptonically, then this means that they decayed hadronically
        ZZ[0]['t'][1]['h'] = 1
        ZZ[1]['t'][1]['h'] = 1

      elif len(Z_taun_da) == 1:
        # if only one of the tau-'s decayed leptonically
        # however, we must take care of the possibility that both tau-'s decayed into the same leptons
        if Z_taun_daughters:
          # only one of the tau-'s decayed leptonically
          ZZ[0]['t'][1]['h'] = 1
          ZZ[1]['t'][1]['l'] = 1
        else:
          # still, both decayed leptonically, but into different leptons
          ZZ[0]['t'][1]['l'] = 1
          ZZ[1]['t'][1]['l'] = 1

      elif len(Z_taun_da) == 2:
        # if both of the tau-'s decayed leptonically
        ZZ[0]['t'][1]['l'] = 1
        ZZ[1]['t'][1]['l'] = 1

      else:
        raise ValueError("Something's wrong")

    elif {'nu_e', 'nu_ebar'}.issubset(ZZ_daughters) or {'nu_mu', 'nu_mubar'}.issubset(ZZ_daughters) or \
         {'nu_tau', 'nu_taubar'}.issubset(ZZ_daughters):
      # both Z's decay into either a lepton neutrino pair
      ZZ[0]['nu'] = 2
      ZZ[1]['nu'] = 2

    else:
      # both Z's decay hadronically in exactly the same way, thus producting 2 + 2 = 4 jets
      ZZ[0]['q'] = 2
      ZZ[1]['q'] = 2

  else:
    # the Z's decay into different set of particles

    # this is the list of valid pairs the Z's decayed into
    Z_pairs = []
    for Z_pair in [['e+', 'e-'], ['mu+', 'mu-'], ['tau+', 'tau-'],
                   ['c', 'cbar'], ['d', 'dbar'], ['u', 'ubar'], ['s', 'sbar'], ['b', 'bbar'],
                   ['nu_e', 'nu_ebar'], ['nu_mu', 'nu_mubar'], ['nu_tau', 'nu_taubar']]:
      if set(Z_pair).issubset(ZZ_daughters):
        # if we have a match, record the pair so that we could figure out the individual Z's decay mode
        Z_pairs.append(filter(lambda x: x[ZZ_idx] in Z_pair, decay_chains))

        # subtract the decay products of a Z from the set of decay products of the Z pair
        ZZ_daughters -= set(Z_pair)

    # make sure that we have exactly two sets of Z decay products and nothing else
    assert(len(Z_pairs) == 2 and len(ZZ_daughters) == 0)

    # loop over individual Z decay products and designate its decay mode
    for i in range(len(Z_pairs)):
      Z_decay = Z_pairs[i]
      Z_da = set(x[ZZ_idx] for x in Z_decay)

      if {'e+', 'e-'}.issubset(Z_da) or {'mu+', 'mu-'}.issubset(Z_da):
        # if the Z decayed into electron-positron or muon-antumuon pair, then we're dealing with leptonic Z decay
        # therefore we mark 2 leptons to a given Z here
        ZZ[i]['l'] = 2

      elif {'tau+', 'tau-'}.issubset(Z_da):
        # if the Z decayed into tau-antitau pair, then we must investigate their decay modes further
        Z_taup = filter(lambda x: x[ZZ_idx] == 'tau+', Z_decay)
        Z_taun = filter(lambda x: x[ZZ_idx] == 'tau-', Z_decay)

        ZZ[i]['t'][0] = get_taup_decay_mode(Z_taup, ZZ_idx + 1)
        ZZ[i]['t'][1] = get_taun_decay_mode(Z_taun, ZZ_idx + 1)

      elif {'nu_e', 'nu_ebar'}.issubset(Z_da) or {'nu_mu', 'nu_mubar'}.issubset(Z_da) or \
           {'nu_tau', 'nu_taubar'}.issubset(Z_da):
        # if the Z decayed into a neutrino pair
        ZZ[i]['nu'] = 2

      else:
        # otherwise we're dealing with hadronic Z decay (therefore two jets per Z)
        ZZ[i]['q'] = 2

  return ZZ

def get_z_decay_mode(decay_chains, z0_idx):
  # initialize empty dict (so that all keys and values are present)
  z0 = {
    'tt' : [get_taup_decay_mode([], 0), get_taun_decay_mode([], 0)],
    'WW' : [get_Wp_decay_mode([], 0), get_Wn_decay_mode([], 0)],
    'l'  : 0,
    'q'  : 0,
    'nu' : 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return z0

  # filter out the decay chains that contain only Z0 at position z0_idx
  z0_br = filter(lambda x: x[z0_idx] == 'Z0', decay_chains)

  # filter out the decay chains that contain only h0 daughters at position h0_idx + 1
  z0_daughters = set([x[z0_idx + 1] for x in z0_br])

  if {'W+', 'W-'}.issubset(z0_daughters):
    # filter out W+, W- daughters
    Wp = filter(lambda x: x[z0_idx + 1] == 'W+', z0_br)
    Wn = filter(lambda x: x[z0_idx + 1] == 'W-', z0_br)
    z0['WW'] = [get_Wp_decay_mode(Wp, z0_idx + 2), get_Wn_decay_mode(Wn, z0_idx + 2)]

  elif {'tau+', 'tau-'}.issubset(z0_daughters):
    # filter out tau+, tau- daughters
    taup = filter(lambda x: x[z0_idx + 1] == 'tau+', z0_br)
    taun = filter(lambda x: x[z0_idx + 1] == 'tau-', z0_br)
    z0['tt'] = [get_taup_decay_mode(taup, z0_idx + 2), get_taun_decay_mode(taun, z0_idx + 2)]

  elif {'e+', 'e-'}.issubset(z0_daughters) or {'mu+', 'mu-'}.issubset(z0_daughters):
    # the Z decays into a lepton pair
    z0['l'] = 2

  elif {'nu_e', 'nu_ebar'}.issubset(z0_daughters) or {'nu_mu', 'nu_mubar'}.issubset(z0_daughters) or \
       {'nu_tau', 'nu_taubar'}.issubset(z0_daughters):
    # the Z decays into a lepton neutrino pair
    z0['nu'] = 2

  else:
    # there are no other options left: the Z decays into a quark-antiquark pair
    z0['q'] = 2

  return z0

def get_h_decay_mode(decay_chains, h0_idx):
  # initialize empty dict (so that all keys and values are present)
  h0 = {
    'tt'         : [get_taup_decay_mode([], 0), get_taun_decay_mode([], 0)],
    'WW'         : [get_Wp_decay_mode([], 0),   get_Wn_decay_mode([], 0)],
    'ZZ'         : get_ZZ_decay_modes([], 0),
    'mu'         : 0,
    'g'          : 0,
    'gammagamma' : [get_gamma_decay_mode([], 0), get_gamma_decay_mode([], 0)],
    'qqbar'      : 0,
  }

  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return h0

  # filter out the decay chains that contain only h0 at position h0_idx
  h0_br = filter(lambda x: x[h0_idx] == 'h0', decay_chains)

  # filter out the decay chains that contain only h0 daughters at position h0_idx + 1
  h0_daughters = set([x[h0_idx + 1] for x in h0_br])

  # decide which higgs decay mode we are dealing with: WW, tautau or ZZ
  if {'W+', 'W-'}.issubset(h0_daughters):
    # filter out W+, W- daughters
    Wp = filter(lambda x: x[h0_idx + 1] == 'W+', h0_br)
    Wn = filter(lambda x: x[h0_idx + 1] == 'W-', h0_br)
    h0['WW'] = [get_Wp_decay_mode(Wp, h0_idx + 2), get_Wn_decay_mode(Wn, h0_idx + 2)]

  elif {'tau+', 'tau-'}.issubset(h0_daughters):
    # filter out tau+, tau- daughters
    taup = filter(lambda x: x[h0_idx + 1] == 'tau+', h0_br)
    taun = filter(lambda x: x[h0_idx + 1] == 'tau-', h0_br)
    h0['tt'] = [get_taup_decay_mode(taup, h0_idx + 2), get_taun_decay_mode(taun, h0_idx + 2)]

  elif {'Z0'}.issubset(h0_daughters):
    # filter out Z0 pair daughters
    ZZ = filter(lambda x: x[h0_idx + 1] == 'Z0', h0_br)
    h0['ZZ'] = get_ZZ_decay_modes(ZZ, h0_idx + 2)

  elif {'mu+', 'mu-'}.issubset(h0_daughters):
    # H -> mu+ mu- spotted
    h0['mu'] = 2

  elif {'gamma'}.issubset(h0_daughters):
    # H -> gamma gamma
    #NB! we only consider the case in which only one gamma decays further, the other is part of the final state
    gammagamma = filter(lambda x: x[h0_idx + 1] == 'gamma', h0_br)
    h0['gammagamma'] = [get_gamma_decay_mode(gammagamma, h0_idx + 1), get_gamma_decay_mode([], 0)]

  elif {'c', 'cbar'}.issubset(h0_daughters):
    # H -> c cbar
    #NB! add more quark pair if you see an error that says there's unimplemented h decay mode
    h0['qqbar'] = 2

  elif { 'g' }.issubset(h0_daughters):
    # now this is a weird one, b/c in SM interaction like H -> gg is not possible, but in our decay chains
    # we do have such events (albeit very few)
    h0['g'] = 1 # even though gluon from higgs may decay hadronically or leptonically,
                # it's quite difficult to deduce the final stage b/c it can be literally anything, so we just
                # mark that it exists and carry on;
                # besides, the number of events in which higgs decays into a gluon is relatively small

  else:
    raise ValueError("Unimplemented h0 decay mode: {h0_daughters}".format(h0_daughters = ', '.join(h0_daughters)))

  return h0

def get_t_decay_mode(decay_chains, t_idx):
  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return get_Wp_decay_mode([], t_idx)

  # filter out the decay chains that contain only t quark at position t_idx
  t_br = filter(lambda x: x[t_idx] == 't', decay_chains)

  # assert that the t quark decays into W+ and b quark
  assert ({'W+', 'b'}.issubset(set(x[t_idx + 1] for x in t_br)))

  # filter out the decay chains that contain W+ as t quark's daughter
  t_Wp_br = filter(lambda x: x[t_idx + 1] == 'W+', t_br)

  # t decay mode reduces to W+ decay mode
  t_decay_mode = get_Wp_decay_mode(t_Wp_br, t_idx + 2)

  # include one jet (b)
  t_decay_mode['q'] = 1

  return t_decay_mode

def get_tbar_decay_mode(decay_chains, tbar_idx):
  # legacy from testing: if the input list of decay chains is empty, return empty dict
  if not decay_chains:
    return get_Wn_decay_mode([], 0)

  # filter out the decay chains that contain only t anti-quark at position t_idx
  tbar_br = filter(lambda x: x[tbar_idx] == 'tbar', decay_chains)

  # assert that the t anti-quark decays into W- and b anti-quark
  assert ({'W-', 'bbar'}.issubset(set(x[tbar_idx + 1] for x in tbar_br)))

  # filter out the decay chains that contain W- as t anti-quark's daughter
  tbar_Wn_br = filter(lambda x: x[tbar_idx + 1] == 'W-', tbar_br)

  # tbar decay mode reduces to W- decay mode
  tbar_decay_mode = get_Wn_decay_mode(tbar_Wn_br, tbar_idx + 2)

  # include one jet (bbar)
  tbar_decay_mode['q'] = 1

  return tbar_decay_mode

def get_tthz_decay_mode(decay_chains, tthz_idx, hz):
  get_hz_decay_mode = get_h_decay_mode if hz == 'h0' else get_z_decay_mode
  tthz = {
    hz       : get_hz_decay_mode(decay_chains, tthz_idx),
    'ttbar'  : [get_t_decay_mode(decay_chains, tthz_idx), get_tbar_decay_mode(decay_chains, tthz_idx)],
  }
  return tthz

def stat_tthz(lines, hypothesis):
  # first let's eliminate lines which do not contain t,tbar and h0

  hz = 'h0' if hypothesis == 'tth' else 'Z0'

  second_decay_products = [hz, 't', 'tbar']
  lines = filter(lambda x: x[2] in second_decay_products, lines)

  # initialize the event statistics
  # note that the dictionary has a lot more to its structure than it seems (just follow the get_*_decay_mode() functions)
  evt = { x : get_tthz_decay_mode([], 0, hz) for x in ['gg', 'gq', 'qq'] }

  # let's find out what are p+'s immediate daughters
  pp_daughters = list(set([x[1] for x in lines]))
  pp_da = 'gg'
  if len(pp_daughters) == 2:
    if 'g' in pp_daughters:
      pp_da = 'gq'
    else:
      pp_da = 'qq'

  # don't double-count if pp_da is gq or qq
  # this is necessary b/c the decay chains will be identical past the quark-gluon stage, e.g. the input file may contain
  # p+ -> g -> h0 -> ..
  # p+ -> q -> h0 -> ..
  # so we want to work with only one of those decay chains (doesn't matter which, though, b/c we save the quark-gluon
  # information anyways) so that we wouldn't spend at most twice as much time to process these lines
  lines = filter(lambda x: x[1] == pp_daughters[0], lines)
  evt[pp_da] = get_tthz_decay_mode(lines, 2, hz)

  # return a dictionary, which has complex structure (not everything shown here):
  # {
  #    'gg' : {
  #        'h0' : {
  #            'tt' : [ { 'l' : 0, 'h' : 0, }, { 'l' : 0, 'h' : 0, }, ],
  #            'WW' : [ { 't' : { 'l' : 0, 'h' : 0, }, 'q' : 0, 'l' : 0, },
  #                     { 't' : { 'l' : 0, 'h' : 0, }, 'q' : 0, 'l' : 0, }, ],
  #            'ZZ' : [ ... ],
  #            'mu' : 0,
  #        },
  #        'ttbar' : [
  #            { 't' : { 'l' : 0, 'h' : 0, }, 'q' : 0, 'l' : 0, },
  #            { 't' : { 'l' : 0, 'h' : 0, }, 'q' : 0, 'l' : 0, },
  #        ],
  #    },
  #    'gq' : ...,
  #    'qq' : ...,
  # }
  # the legend in case you need to print out the dictionary while debugging this program
  #   'gg' -- gluon-gluon      'gq' -- gluon-quark         'qq' -- quark-quark
  #   'h0' -- higggs           'ttbar' -- top & anti-top   'tt' -- tau tau pair
  #   'WW' -- W pair           'ZZ' -- Z pair              't' -- tau
  #   'l' -- lepton(s)         'h' -- hadronic tau         'q' -- hadronic jet(s)/quark(s)
  #   'Z0' -- Z boson
  # number behind the symbols show how many such particles are there (applies only to leptons, hadronic taus and jets,
  # though); if the decay chain contains more structure (e.g. h0 decays into a pair of vector bosons), it will be
  # represented by a dictionary or an array
  return evt

def stat(lines, hypothesis):
  # here we parse the human-readable decay chains of an event returned by process()
  if hypothesis in ('tth', 'ttz'):
    return stat_tthz(lines, hypothesis)
  else:
    raise ValueError("Unsupported hypothesis: {hypothesis}".format(hypothesis = hypothesis))

############################ THIRD STEP: PARSING DICT RETURNED IN THE SECOND STEP #############################

def get_tau_cat(entry):
  # returns the tau decay label and multiplicity of visible particles
  # the label is surrounded by parentheses since it's a final state particle
  # also return the number of jets here (the last digit) for the sake of completeness

  # here we check the dictionary entries returned by stat_tth() (or, more specifically, by get_tau[p,n]_decay_mode())
  # if the tau didn't decay into anything, then the respective entry is 0
  if entry['l']:
    # if tau dict contains a non-zero lepton
    return '(tau->l)', entry['l'], 0
  if entry['h']:
    # if tau dict contains a non-zero hadronic tau
    return '(tau->h)', 0, entry['h']

  # if the tau didn't decay into anything, then this probably means that the process initiator wasn't right or
  # the higgs decay mode was different
  return '', 0, 0, 0

def get_WW_cat(entries, check_q = True):
  # returns the WW or ttbar decay label and multiplicity of visible particles
  # the label contains parentheses since its decay products are final state particles
  final_decay_products = []
  nof_l, nof_h, nof_q = 0, 0, 0

  for entry in entries:
    # here we check the dictionary entries returned by stat_tth() (or, more specifically, by get_W[p,n]_decay_mode())
    # if the W didn't decay into anything, then the respective entry is 0

    # get tau label first
    entry_tau = get_tau_cat(entry['t'])

    if entry['l']:
      # we have a leptonic W decay
      final_decay_products.append('(l)')
      nof_l += 1
    elif entry_tau[0]:
      # the W decays into a tau for which we fortunately have a label for
      final_decay_products.append('%s' % entry_tau[0])
      # sum the leptons from direct or indirect (i.e. from tau) W decay
      nof_l += entry_tau[1]
      # a hadronic tau can only come from tau decay in W decay
      nof_h += entry_tau[2]
    elif check_q and entry['q']:
      # we have a hadronic W decay
      final_decay_products.append('(q)(q)')
      nof_q += 2

  if (nof_l + nof_h + nof_q) > 0:
    # keep a consistent label for the WW decay by alphabetically sorting individual label
    # also, if the WW's didn't decay into anything, this probably means that it either wasn't
    # the higgs decay mode or the process initiators weren't correct
    return "WW->%s" % ''.join(list(sorted(final_decay_products))), nof_l, nof_h, nof_q
  return '', 0, 0, 0

def get_gamma_cat(entry, use_double_gamma):
  # returns single photon decay label and multiplicity of visible particles

  # use double instead of single gamma since at the time of writing I'm too lazy to implement gamma decay for the pair
  prefix = "gammagamma" if use_double_gamma else "gamma"

  first_tau  = get_tau_cat(entry['t'][0])
  second_tau = get_tau_cat(entry['t'][1])

  if entry['l']:
    # gamma -> e+ e- or gamma -> mu+ mu-
    return '%s->(l)(l)' % prefix, 2, 0, 0
  elif first_tau[0] and second_tau[0]:
    # gamma -> tau+ tau- -> ...
    nof_l = first_tau[1]
    nof_h = first_tau[2]
    nof_q = first_tau[3]
    return "%s->%s" % (prefix, ''.join([first_tau[0], second_tau[0]])), nof_l, nof_h, nof_q

  return '', 0, 0, 0

def get_ttbar_cat(entries):
  # find ttbar decay label and multiplicity of visible particles by treating it as WW decay
  ttbar = entries['ttbar']
  WW_cat = get_WW_cat(ttbar, check_q = True)
  if WW_cat[0]:
    return "ttbar->%s" % WW_cat[0], WW_cat[1], WW_cat[2], WW_cat[3] + 2

  # if we ended up here then this means that process initiators aren't right
  return '', 0, 0, 0

def get_tautau_cat(entries):
  # find the decay label for the tau pair decay and multiplicity of visible particles
  tau = [
    get_tau_cat(entries[0]),
    get_tau_cat(entries[1]),
  ]

  # total number of leptons and hadronic taus is found by summing the same number of individual taus
  lepton_sum = sum(tau[i][1] for i in range(len(tau)))
  htau_sum   = sum(tau[i][2] for i in range(len(tau)))

  # no jets from tau decay, though
  quark_sum = 0

  # keep a consistent label for the tau pair decay by alphabetically sorting individual label
  decay_str = ''.join(list(sorted([tau[i][0] for i in range(len(tau))])))

  if (lepton_sum + htau_sum + quark_sum):
    # also, if the tau pair didn't decay into anything, this probably means that it either wasn't
    # the higgs decay mode or the process initiators weren't correct
    return decay_str, lepton_sum, htau_sum, quark_sum
  return '', 0, 0, 0

def get_ZZ_cat(entries):
  # find the decay label for the ZZ decay and multiplicity of visible particles
  # the label contains parentheses since its decay products are final state particles
  final_decay_products = []
  nof_l, nof_h, nof_q, nof_nu = 0, 0, 0, 0

  for entry in entries:
    # here we check the dictionary entries returned by stat_tth() (or, more specifically, by get_ZZ_decay_modes())
    # if the Z didn't decay into anything, then the respective entry is 0

    if entry['l']:
      # the Z decays into two leptons (of the same flavor but opposite charge)
      final_decay_products.append('(l)(l)')
      nof_l += entry['l']

    elif entry['q']:
      # the Z decays into two quarks
      final_decay_products.append('(q)(q)')
      nof_q += entry['q']

    elif entry['nu']:
      # the Z decays into a lepton neutrino pair
      final_decay_products.append('(nu)(nu)')
      nof_nu += entry['nu']

    elif entry['t']:
      # the Z decays into a tau pair
      for i in range(len(entry['t'])):

        # get tau label
        entry_tau = get_tau_cat(entry['t'][i])

        if entry_tau[0]:
          # if the Z decayed into a tau, then we can record the number of leptons and hadronic taus it decayed into
          final_decay_products.append('%s' % entry_tau[0])
          nof_l += entry_tau[1]
          nof_h += entry_tau[2]

  if (nof_l + nof_h + nof_q + nof_nu):
    # also, if the Z pair didn't decay into anything, this probably means that it either wasn't
    # the higgs decay mode or the process initiators weren't correct
    return "ZZ->%s" % ''.join(list(sorted(final_decay_products))), nof_l, nof_h, nof_q
  return '', 0, 0, 0

def get_z0_cat(entries):
  # find z0 decay label and multiplicity of visible particles by treating it as a composition of WW, ll, qq and tautau decay
  z0 = entries['Z0']

  WW_cat     = get_WW_cat(z0['WW'], check_q = True)
  tautau_cat = get_tautau_cat(z0['tt'])

  ll_cat = '', 0, 0, 0
  if z0['l']:
    ll_cat = '(l)(l)', 2, 0, 0

  qq_cat = '', 0, 0, 0
  if z0['q']:
    qq_cat = '(q)(q)', 0, 0, 2

  nunu_cat = '', 0, 0, 0
  if z0['nu']:
    nunu_cat = '(nu)(nu)', 0, 0, 0

  for c in [WW_cat, tautau_cat, ll_cat, qq_cat, nunu_cat]:
    if c[0]:
      # if we have a match, return immediately (a single z0 can only decay once :))
      return "Z->%s" % c[0], c[1], c[2], c[3]

  return '', 0, 0, 0

def get_h0_cat(entries):
  # find h0 decay label and multiplicity of visible particles by treating it as a composition of WW, ZZ and tautau decay
  h0 = entries['h0']

  WW_cat         = get_WW_cat(h0['WW'], check_q = True)
  ZZ_cat         = get_ZZ_cat(h0['ZZ'])
  tautau_cat     = get_tautau_cat(h0['tt'])
  gammagamma_cat = get_gamma_cat(h0['gammagamma'][0], use_double_gamma = True)

  mumu_cat = '', 0, 0, 0
  if h0['mu']:
    mumu_cat = 'mumu', 2, 0, 0

  g_cat = '', 0, 0, 0
  if h0['g']:
    g_cat = 'g', 0, 0, 0

  q_cat = '', 0, 0, 0
  if h0['qqbar']:
    q_cat = 'qqbar', 0, 0, 2

  for c in [WW_cat, ZZ_cat, tautau_cat, mumu_cat, g_cat, gammagamma_cat, q_cat]:
    if c[0]:
      # if we have a match, return immediately (a single h0 can only decay once :))
      return "H->%s" % c[0], c[1], c[2], c[3]

  # if we end up here then this means that the process initiatior aren't right
  return 'H->UNRECOGNIZED', 0, 0, 0

def aggregate_tth(evts, hz):
  # the function categorizes each event into different channels of tth/z process, given the output of stat_tthz()
  # it also calculates the total number of visible particles (i.e. leptons, hadronic taus and jets) and keeps
  # track of RLE numbers
  agg = {}
  get_hz_cat = get_h0_cat if hz == 'h0' else get_z0_cat

  for rle, evt in evts.iteritems():
    for pp in ['gg', 'gq', 'qq']:
      # try out different tth process initiators

      # get the label for ttbar decay mode
      ttbar = get_ttbar_cat(evt[pp])

      if ttbar[0]:
        # if we wouldn't have a match, the process label will be an empty string

        # get the label for higgs decay mode
        hz_cat = get_hz_cat(evt[pp])

        # sum the number of visible particles
        nof_l = ttbar[1] + hz_cat[1] # leptons
        nof_h = ttbar[2] + hz_cat[2] # hadronic taus
        nof_q = ttbar[3] + hz_cat[3] # jets

        # create the overall process label (higgs decay mode,ttbar decay mode)
        key = "%s,%s" % (hz_cat[0], ttbar[0])

        # add this information to the map
        if key not in agg:
          agg[key] = []
        agg[key].append({ 'pp' : pp, 'nof_l' : nof_l, 'nof_h' : nof_h, 'nof_q' : nof_q, 'rle' : rle, })

  return agg

def aggregate(evts, hypothesis):
  # aggregates the results by building a dictionary in which the keys are process labels (in which all decay chains
  # are completely expanded, bar b-jets and neutrinos) and the values are dicts, which contain the multiplicity of
  # measurable particles (leptons ('nof_l'), hadronic taus ('nof_h') and jets ('nof_q')), RLE number ('rle') and
  # process initiator pair ('pp')
  # the expected input here is of the form returned by stat() function
  if hypothesis in ('tth', 'ttz'):
    return aggregate_tth(evts, 'h0' if hypothesis == 'tth' else 'Z0')
  else:
    raise ValueError("Unsupported hypothesis: {hypothesis}".format(hypothesis = hypothesis))

################################# FINAL FOURTH STEP: PRINT AGGREGATED RESULTS #################################

def print_aggregate(agg, hypothesis, output_filename, nof_events_total, secondary_output_dir = ''):
  # prints the final results to screen and save the same output to a file

  # sort by decreasin number of events
  agg_sorted = sorted(agg.items(), key = lambda x: len(x[1]), reverse = True)

  if hypothesis in ('tth', 'ttz'):

    # print onto screen and write to a file
    with MultipleStream([sys.stdout, output_filename]) as ms:

      decmodes = ['tautau', 'WW']
      hz = 'H' if hypothesis == 'tth' else 'Z'
      if hypothesis == 'tth':
        # H -> ZZ, H -> mumu, H -> gamma gamma, H -> q qbar or H -> g g (whatever that means)
        decmodes.extend(['ZZ', 'mumu', 'g', 'gammagamma', 'qqbar', 'UNRECOGNIZED'])
      else:
        decmodes.extend(['ll', 'qq'])  # Z -> ll or Z -> qq
      counter_map_keys = decmodes + ['gg', 'gq', 'qq']
      counter_map = {k: 0 for k in counter_map_keys}
      channel_map = {}

      def save_rles(proper_basename, evt_arr):
        # saves RLE numbers of a specific channel (and maybe initiator) to a separate file

        rle_filename = os.path.join(secondary_output_dir, proper_basename)
        with open(rle_filename, 'w') as f2:
          for evt_entry in evt_arr:
            f2.write("%s\n" % evt_entry['rle'])

      def print_initiatiors(init_type, arr, proper_basename = ''):
        # print he number of events (fraction to the event category) and the RLE numbers that correspond to
        # the one process initiator pair; return the number of events which belong to both categories

        evt_init_type = [x for x in arr if x['pp'] == init_type]
        if evt_init_type:
          ms.writeln("\tInitiated by %s: %d (%.2f%%)" %
            (init_type, len(evt_init_type), 100. * len(evt_init_type) / len(arr))
          )
          for evt_init_type_entry in evt_init_type:
            ms.writeln("\t\t%s" % evt_init_type_entry['rle'])

          if proper_basename:
            save_rles(proper_basename, evt_init_type)

        return len(evt_init_type)

      for i in range(len(agg_sorted)):
        evt_str    = agg_sorted[i][0]    # process label
        evt_arr    = agg_sorted[i][1]    # array of events belonging to the process
        nof_events = len(evt_arr) # number of events in the process

        # get the multiplicity of visible particles
        nof_l = evt_arr[0]['nof_l']
        nof_h = evt_arr[0]['nof_h']
        nof_q = evt_arr[0]['nof_q']
        assert (all(evt_arr[i]['nof_l'] == nof_l for i in range(nof_events)))
        assert (all(evt_arr[i]['nof_h'] == nof_h for i in range(nof_events)))
        assert (all(evt_arr[i]['nof_q'] == nof_q for i in range(nof_events)))
        channel = "%dl%dtau" % (nof_l, nof_h)

        ms.writeln(evt_str)
        ms.writeln("\tChannel: %s (+ %d jets)" % (channel, nof_q))
        ms.writeln("\tNumber of events: %d (%.2f%%)" % (nof_events, 100. * nof_events / nof_events_total))
        ms.writeln("\tRLE numbers:")

        # print RLE numbers that belong to this process label
        for evt_entry in evt_arr:
          ms.writeln("\t\t%s" % evt_entry['rle'])

        if secondary_output_dir:
          proper_basename = 'tt%s,%s.txt' % (hz, evt_str.replace('(', '[').replace(')', ']'))
          save_rles(proper_basename, evt_arr)

        # do a breakdown based on particle initiators
        for init_type in ['gg', 'gq', 'qq']:
          proper_basename = '%s->tt%s,%s.txt' % (init_type, hz, evt_str.replace('(', '[').replace(')', ']')) \
                            if secondary_output_dir else ''
          counter_map[init_type] += print_initiatiors(init_type, evt_arr, proper_basename)

        # fill the counter map with the number of events belonging to certain higgs decay modes
        if hypothesis == 'tth':
          if evt_str.startswith('H->WW'):
            counter_map['WW'] += nof_events
          elif evt_str.startswith('H->ZZ'):
            counter_map['ZZ'] += nof_events
          elif evt_str.startswith('H->mumu'):
            counter_map['mumu'] += nof_events
          elif evt_str.startswith('H->gammagamma'):
            counter_map['gammagamma'] += nof_events
          elif evt_str.startswith('H->qqbar'):
            counter_map['qqbar'] += nof_events
          elif evt_str.startswith('H->g'):
            counter_map['g'] += nof_events
          elif evt_str.startswith('H->UNRECOGNIZED'):
            counter_map['UNRECOGNIZED'] += nof_events
          else:
            counter_map['tautau'] += nof_events
        else:
          if evt_str.startswith('Z->WW'):
            counter_map['WW'] += nof_events
          elif evt_str.startswith('Z->(l)(l)'):
            counter_map['ll'] += nof_events
          elif evt_str.startswith('Z->(q)(q)'):
            counter_map['qq'] += nof_events
          else:
            counter_map['tautau'] += nof_events

        if channel not in channel_map:
          channel_map[channel] = []
        channel_map[channel].append({
          'nof_events' : nof_events,
          'evt_type'   : evt_str,
        })

        if i < len(agg_sorted) - 1:
          ms.writeln(SEP)

      # print overall statistics
      ms.writeln(SEP.replace('-', '='))
      ms.writeln("Channels:")
      channel_map_sorted = sorted(channel_map.items(), key = lambda x: sum([y['nof_events'] for y in x[1]]), reverse = True)
      for channel in channel_map_sorted:
        channel_str                = channel[0]
        channel_nof_events         = sum([x['nof_events'] for x in channel[1]])
        channel_nof_events_percent = 100. * channel_nof_events / nof_events_total
        ms.writeln("\t%s: %d (%.2f%%)" % (channel_str, channel_nof_events, channel_nof_events_percent))
        for channel_evt_type in channel[1]:
          ms.writeln("\t\t%s %d\t(%.2f%%/%.2f%%)" % (
            channel_evt_type['evt_type'].ljust(65),
            channel_evt_type['nof_events'],
            100. * channel_evt_type['nof_events'] / channel_nof_events,
            100. * channel_evt_type['nof_events'] / nof_events_total
          ))

      ms.writeln(SEP.replace('-', '='))
      for decmode in decmodes:
        ms.writeln("Number of %s->%s events: %d (%.2f%%)" % (
          hz,
          decmode.ljust(12),
          counter_map[decmode],
          100. * counter_map[decmode] / nof_events_total
        ))

      for pp in ['gg', 'gq', 'qq']:
        ms.writeln("Number of pp->%s events: %d (%.2f%%)" % (pp, counter_map[pp], 100. * counter_map[pp] / nof_events_total))

      ms.writeln("Total number of events: %s" % nof_events_total)
  else:
    raise ValueError("Unsupported hypothesis: {hypothesis}".format(hypothesis = hypothesis))

################################################# MAIN PROGRAM ################################################

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  # set the help description width to 45 characters
  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45))
  parser.add_argument('-o', '--output', metavar = 'file', required = False, type = str, default = '',
                      help = 'R|Output file')
  parser.add_argument('-g', '--generate', metavar = 'name', required = False, type = str, default = '',
                      help = 'R|Sample name for which the decay chain is to be found')
  parser.add_argument('-i', '--input', metavar = 'file', required = True, type = str, default = '',
                      help = 'R|Input RLE file')
  parser.add_argument('-j', '--secondary-input', metavar = 'file', required = False, type = str, default = '',
                      help = 'R|Secondary RLE file (applies only if -p/--parse or -s/--statistics is triggered)')
  parser.add_argument('-c', '--cli', metavar = 'file', required = False, type = str, default = '',
                      help = 'R|Path to cli.py')
  parser.add_argument('-r', '--secondary-output', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Secondary output directory (applies only if -s/--statistics is triggered)')
  parser.add_argument('-s', '--statistics', metavar = 'hypothesis', required = False, type = str, default = '',
                      choices = ('tth', 'ttz'),
                      help = 'R|Create decay statistics, given parsing results')
  parser.add_argument('-p', '--parse', dest = 'parse', action = 'store_true', default = False,
                      help = 'R|Parse results of printGenParticles_miniAOD')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Force the creation of output directory if missing')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if (args.generate and args.parse) or (args.statistics and args.parse) or (args.statistics and args.generate):
    raise parser.error("use only one of the following options: -g/--generate, -p/--parse, -s/--statistics")
  if not (args.generate or args.parse or args.statistics):
    raise parser.error("use one of the following options: -g/--generate, -p/--parse, -s/--statistics")
  if (args.generate and not args.cli) or (not args.generate and args.cli):
    raise parser.error("must use both or neither: -g/--generate, -c/--cli")

  if args.secondary_input and args.generate:
    logging.warning("Using -j/--secondary-input with -g/--generate has no effect")

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  if not os.path.isfile(args.input):
    logging.error("No such file {filename}".format(filename = args.input))
    sys.exit(1)

  if args.generate:
    # create cmsRun job from python template

    if not os.path.isdir(os.path.dirname(args.output)):
      if args.force:
        try:
          os.makedirs(os.path.dirname(args.output))
        except IOError:
          logging.error("Could not create directory {dir_name}".format(dir_name=os.path.dirname(args.output)))
          sys.exit(1)
      else:
        logging.error("Use -f/--force flag to create the directory for output file {filename}".format(
          filename = args.output)
        )

    if not os.path.isfile(args.cli):
      logging.error("No such file: {filename}".format(filename = args.cli))
      sys.exit(1)

    # get the sample name
    sample = ''
    for sample_das_name, sample_info in samples_2016.iteritems():
      if sample_info['process_name_specific'] == args.generate:
        sample = sample_das_name
        break
    if not sample:
      logging.error("Could not find sample name '{sample_name}' in the Python dictionary".format(
        sample_name = args.generate)
      )
      sys.exit(1)

    # read RLE numbers and check if all non-empty lines have the correct RLE number format
    rles = read_rles(args.input)

    logging.debug("Testing if proxy is up")
    try:
      # test if the proxy is up by issuing voms-proxy-info command
      voms_proxy_info_cmd = "voms-proxy-info"
      voms_proxy_info_stdout = run_cmd(voms_proxy_info_cmd)

      # at this point the voms-proxy-info seems to be available, which means that we can read how much time
      # is left until the proxy channel closes (if it's less than an hour, then exit)
      timeleft_str = filter(lambda x: x.startswith('timeleft'), voms_proxy_info_stdout.split('\n'))[0].split()[-1]
      timeleft = datetime.datetime.strptime(timeleft_str, "%H:%M:%S")
      if timeleft.hour == 0:
        raise ValueError("Not enough time to keep proxy alive: {timeleft}\nUse the following command:\n\t{command}".format(
          timeleft = timeleft_str,
          command  = "source /cvmfs/grid.cern.ch/glite/etc/profile.d/setup-ui-example.sh; \n\t"
                     "voms-proxy-init -voms cms -valid 6:00"
        ))
    except ValueError as err:
      logging.error("Aborting, because: {reason}".format(reason = err))
      sys.exit(1)

    # request the number of files using the DAS CLI script
    logging.debug("Retrieving the number of MINIAOD files")
    request_nof_files_cmd = "python {cli} --query='file dataset={sample_name} | count(file.block.name)' " \
                            "| grep 'count(file.block.name)'".format(cli = args.cli, sample_name = sample)
    request_nof_files_stdout = run_cmd(request_nof_files_cmd)
    nof_files = request_nof_files_stdout.rstrip('\n').split('=')[-1]
    nof_files_int = -1
    try:
      nof_files_int = int(nof_files)
    except ValueError:
      logging.error("Got NaN as the number of files: {stdout}".format(stdout = request_nof_files_stdout))
      sys.exit(1)
    if nof_files == 0:
      logging.warning("The sample {sample_name} has no files")
      sys.exit(0)

    # request the list of files by limiting the output to the expected number of files
    # however, if the number of expected files is very large, this might not work (untested!)
    logging.debug("Retrieving the file list")
    request_file_list_cmd = "python {cli} --query='file dataset={sample_name}' --limit={nof_files} " \
                            "| grep '^/store'".format(cli = args.cli, sample_name = sample, nof_files = nof_files)
    request_file_list_stdout = run_cmd(request_file_list_cmd)
    file_list = filter(lambda x: x != '', request_file_list_stdout.split('\n'))
    if len(file_list) != nof_files_int:
      logging.error("Couldn't fetch all files: got {nof_fetched_files}, expected {nof_required_files} files".format(
        nof_fetched_files = len(file_list), nof_required_files = nof_files_int,
      ))
      sys.exit(1)

    # generate the cfg from template and save it
    logging.debug("Generating {output_filename} from the template".format(output_filename = args.output))
    root_urls = map(lambda x: os.path.join("root://cms-xrd-global.cern.ch//", x[1:]), file_list)
    with open(args.output, 'w') as f:
      f.write(jinja2.Template(printGenParticles_miniAOD_cfg).render(
        file_list = root_urls,
        rle_list  = rles,
        command   = 'python %s' % ' '.join(sys.argv),
      ))

    # print out more instructions
    logfile_example = os.path.join(
      os.path.dirname(args.output), '{sample_name}_decayChain.log'.format(sample_name = args.generate)
    )
    logging.info("Run the script with e.g.\n\tcmsRun {script_location} &> {logfile}".format(
      script_location = args.output,
      logfile         = logfile_example,
    ))
    logging.info("You can track the progress in another shell session with the following command:\n"
                 "\ttail -F {logfile}".format(logfile = logfile_example))
    logging.info("Once the script has finished its jobs, run it with\n"
                 "\tpython {cmd} -i {logfile} -o {output} -p -v".format(
      cmd     = sys.argv[0],
      logfile = logfile_example,
      output  = os.path.join(os.path.dirname(args.output), '{sample_name}_parsed.log'.format(sample_name = args.generate))
    ))
    logging.info("The script should work with CMSSW_VERSION=CMSSW_8_0_19 and SCRAM_ARCH=slc6_amd64_gcc530")

  elif args.parse:
    # here we perform parsing on the file that was produced by running the code in the last step

    if not os.path.isdir(os.path.dirname(args.output)):
      if args.force:
        try:
          os.makedirs(os.path.dirname(args.output))
        except IOError:
          logging.error("Could not create directory {dir_name}".format(dir_name = os.path.dirname(args.output)))
          sys.exit(1)
      else:
        logging.error("Use -f/--force flag to create the directory for output file {filename}".format(
          filename = args.output)
        )

    secondary_rles = { k : False for k in read_rles(args.secondary_input) } if args.secondary_input else {}
    second_decay_products, rles = [], []
    with codecs.open(args.output, 'w', 'utf-8') as of:
      with codecs.open(args.input, 'r', 'utf-8') as f:

        lines = ''
        for line in f:
          line = str(line)

          if line.startswith('Begin processing'):
            # we hit the line
            #   Begin processing the nth record. Run 1, Event ..., LumiSection ,,,
            # if we already have collected some lines of the decay chains, process them
            # if not, keep just record the RLE number and continue
            if len(rles) > 0:
              last_rle = rles[-1]
              if (secondary_rles and last_rle in secondary_rles) or not secondary_rles:
                of.write('%s\n' % last_rle)
                of.write('%s\n%s\n' % (process(lines.rstrip('\n'), second_decay_products), SEP))
                if secondary_rles:
                  secondary_rles[last_rle] = True
              lines = ''

            # get the RLE number and record it
            ssplit = line.split()
            rle = str(':'.join([ssplit[6][:-1], ssplit[10], ssplit[8][:-1]]))
            rles.append(rle)
            logging.debug("Processing event {rle}".format(rle = rles[-1]))

          elif line == '=============================================\n':
            # we finished reading the last entry, which we have to now process
            of.write('%s\n' % rles[-1])
            of.write('%s\n%s\n' % (process(lines.rstrip('\n'), second_decay_products), SEP))
            break

          else:

            split = line.split()
            if len(split) < 4:
              continue
            elif split[3] == '-':
              # record a line of the decay chain table
              lines += str(line)

    if secondary_rles:
      unmatched_rles = [k for k in secondary_rles if not secondary_rles[k]]
      if unmatched_rles:
        logging.warning("The following {nof} RLE numbers werent caught here:".format(nof = len(unmatched_rles)))
        print('\n'.join(unmatched_rles))
      else:
        logging.info("Successfully masked all {nof} RLE numbers".format(nof = len(secondary_rles)))

    # print further instructions
    logging.debug("Processed {nof_events} events".format(nof_events = len(rles)))
    logging.info("Find statistics about the parsed result with the following command:\n\t{cmd}".format(
      cmd = "python {this_file} -i {input_file} -o {output_file} -s tth".format(
        this_file   = sys.argv[0],
        input_file  = args.output,
        output_file = "%s.statistics" % args.output,
      )
    ))

  elif args.statistics:
    # here we create decay statistics about the parsed results

    if args.secondary_output:
      if not args.statistics:
        logging.warning("Using -r/--secondary-output makes sense only with -s/--statistics")
      if not os.path.isdir(args.secondary_output):
        logging.warning("No such directory: {output_dir}".format(output_dir = args.secondary_output))
        if not args.force:
          logging.error("Use the -f/--force to create missing output directory {output_dir}".format(
            output_dir = args.secondary_output,
          ))
          sys.exit(1)
        else:
          try:
            os.makedirs(args.secondary_output)
          except IOError as err:
            logging.error("Could not create directory {output_dir} for the following reasons: {reasons}".format(
              output_dir = args.secondary_output,
              reasons    = err,
            ))
          logging.info("Successfully created directory {output_dir}".format(output_dir = args.secondary_output))

    secondary_rles = {k: False for k in read_rles(args.secondary_input)} if args.secondary_input else {}
    lines, rles, evt = [], [], {}
    with codecs.open(args.input, 'r', 'utf-8') as f:
      for line in f:
        line = str(line.rstrip('\n'))
        if line.startswith('1:'):
          if (secondary_rles and line in secondary_rles) or not secondary_rles:
            # record the RLE number
            rles.append(line)
            if secondary_rles:
              secondary_rles[line] = True
        elif line == SEP:
          # process the recorded decay chains of the event, since we hit a separator
          if lines:
            if rles:
              evt[rles[-1]] = stat(lines, args.statistics)
          lines = []
        else:
          # record the decay chain
          lines.append(line.split(' -> '))

    if secondary_rles:
      unmatched_rles = [k for k in secondary_rles if not secondary_rles[k]]
      if unmatched_rles:
        logging.warning("The following {nof} RLE numbers werent caught here:".format(nof = len(unmatched_rles)))
        print('\n'.join(unmatched_rles))
      else:
        logging.info("Successfully masked all {nof} RLE numbers".format(nof = len(secondary_rles)))

    # aggregate and print the results
    # each complete decay mode is sorted by its frequency (followed by alphabetical ordering)
    agg = aggregate(evt, args.statistics)
    print_aggregate(agg, args.statistics, args.output, len(rles), args.secondary_output)

  else:
    logging.error("Well that's awkward ...")

  logging.debug("Done!")
