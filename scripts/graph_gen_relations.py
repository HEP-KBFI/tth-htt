#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import argparse
import os.path
import re
import array
import subprocess
import jinja2

MAX_OBJS = 9999
GENPART_NAME = 'GenPart'
GRAPH_TEMPLATE = """
digraph G {
  graph [nodesep="0.5"];
  {% for node in nodes -%}
    {{ node[0] }} [label=<{{ node[1] }}<FONT POINT-SIZE="10"> (status = {{ node[2] }}) <BR /> 
    ({{ '{:.3f}'.format(node[3]) }}, {{ '{:+.3f}'.format(node[4]) }}, {{ '{:+.3f}'.format(node[5]) }}, {{ '{:.3f}'.format(node[6]) }})
  </FONT>>];
  {% endfor -%}
  {% for edge in edges -%}
    {{ edge[0] }} -> {{ edge[1] }};
  {% endfor -%}
}
"""

class MassTable:
  def __init__(self):
    self.pdgTable = ROOT.TDatabasePDG()

  def getMass(self, mass, pdgId):
    if mass > 10. or (pdgId == 22 and mass > 1.) or abs(pdgId) == 24 or pdgId == 23:
      return mass
    else:
      genParticleInstance = self.pdgTable.GetParticle(pdgId)
      if not genParticleInstance:
        return 0.
      return genParticleInstance.Mass()

class GenPart(object):
  def __init__(self, idx, pt, eta, phi, mass, pdgId, momIdx, daughterIdx1, daughterIdx2, status, statusFlag):
    self.idx = idx
    self.pt = pt
    self.eta = eta
    self.phi = phi
    self.mass = mass
    self.pdgId = pdgId
    self.momIdx = momIdx
    self.dauIdx1 = daughterIdx1
    self.dauIdx2 = daughterIdx2
    self.status = status
    self.statusFlag = statusFlag

  def __str__(self):
    return "idx = %d pt = %.3f eta = %+.3f phi = %+.3f mass = %.3f pdgId = %+d momIdx = %d (daughters %d, %d) status = %d statusFlags = %d" % \
      (self.idx, self.pt, self.eta, self.phi, self.mass, self.pdgId, self.momIdx, self.dauIdx1, self.dauIdx2, self.status, self.statusFlag)

class GenPartCollection(object):
  def __init__(self, input_tree, mtable, delphes):
    self.nGenPart_branch = array.array('I', [0])
    self.genPart_eta_branch = array.array('f', [0.] * MAX_OBJS)
    self.genPart_mass_branch = array.array('f', [0.] * MAX_OBJS)
    self.genPart_phi_branch = array.array('f', [0.] * MAX_OBJS)
    self.genPart_pt_branch = array.array('f', [0.] * MAX_OBJS)
    self.genPart_genPartIdxMother_branch = array.array('i', [-1] * MAX_OBJS)
    self.genPart_genPartIdxDaugher1_branch = array.array('i', [-1] * MAX_OBJS)
    self.genPart_genPartIdxDaugher2_branch = array.array('i', [-1] * MAX_OBJS)
    self.genPart_pdgId_branch = array.array('i', [0] * MAX_OBJS)
    self.genPart_status_branch = array.array('I', [0] * MAX_OBJS)
    self.genPart_statusFlags_branch = array.array('I', [0] * MAX_OBJS)

    self.mtable = mtable

    input_tree.SetBranchAddress('n{}'.format(GENPART_NAME), self.nGenPart_branch)
    input_tree.SetBranchAddress('{}_eta'.format(GENPART_NAME), self.genPart_eta_branch)
    input_tree.SetBranchAddress('{}_mass'.format(GENPART_NAME), self.genPart_mass_branch)
    input_tree.SetBranchAddress('{}_phi'.format(GENPART_NAME), self.genPart_phi_branch)
    input_tree.SetBranchAddress('{}_pt'.format(GENPART_NAME), self.genPart_pt_branch)
    input_tree.SetBranchAddress('{}_genPartIdxMother'.format(GENPART_NAME), self.genPart_genPartIdxMother_branch)
    if delphes:
      input_tree.SetBranchAddress('{}_d1'.format(GENPART_NAME), self.genPart_genPartIdxDaugher1_branch)
      input_tree.SetBranchAddress('{}_d2'.format(GENPART_NAME), self.genPart_genPartIdxDaugher2_branch)
    input_tree.SetBranchAddress('{}_pdgId'.format(GENPART_NAME), self.genPart_pdgId_branch)
    input_tree.SetBranchAddress('{}_status'.format(GENPART_NAME), self.genPart_status_branch)
    if not delphes:
      input_tree.SetBranchAddress('{}_statusFlags'.format(GENPART_NAME), self.genPart_statusFlags_branch)

  def read(self):
    genParts = []
    for idx in range(self.nGenPart_branch[0]):
      mass = self.mtable.getMass(self.genPart_mass_branch[idx], self.genPart_pdgId_branch[idx])
      genParts.append(GenPart(
        idx, self.genPart_pt_branch[idx], self.genPart_eta_branch[idx], self.genPart_phi_branch[idx], mass,
        self.genPart_pdgId_branch[idx], self.genPart_genPartIdxMother_branch[idx],
        self.genPart_genPartIdxDaugher1_branch[idx], self.genPart_genPartIdxDaugher2_branch[idx],
        self.genPart_status_branch[idx], self.genPart_statusFlags_branch[idx],
      ))
    return genParts

def get_graph(input_file_name, rles, mtable, delphes):
  logging.debug('Opening file {}'.format(input_file_name))
  input_file = ROOT.TFile.Open(input_file_name, 'read')
  assert(input_file)
  input_tree = input_file.Get('Events')
  assert(input_tree)

  run_branch = array.array('I', [0])
  luminosityBlock_branch = array.array('I', [0])
  event_branch = array.array('L', [0])

  if not delphes:
    input_tree.SetBranchAddress('run', run_branch)
    input_tree.SetBranchAddress('luminosityBlock', luminosityBlock_branch)
  input_tree.SetBranchAddress('event', event_branch)
  genPartCollection = GenPartCollection(input_tree, mtable, delphes)

  graph_map = {}
  nof_events = input_tree.GetEntries()
  logging.debug('Found {} events in the file'.format(nof_events))
  for event_idx in range(nof_events):
    input_tree.GetEntry(event_idx)
    rle = ':'.join(map(lambda branch: str(branch[0]), [ run_branch, luminosityBlock_branch, event_branch ]))
    if rle not in rles:
      continue
    logging.debug('Found event {} at index {}'.format(rle, event_idx))
    gen_parts = genPartCollection.read()
    logging.debug('Found {} generator level particles in the event'.format(len(gen_parts)))
    for gen_part in gen_parts:
      logging.debug(gen_part)
    graph_map[rle] = gen_parts

    if all(requested_rle in graph_map for requested_rle in rles):
      break

  input_file.Close()
  logging.debug('Found {} matches in file {}'.format(len(graph_map), input_file_name))

  return graph_map

def save_graph(gen_parts, output_file_name, keep_tmp = False):
  graph_nodes = []
  graph_edges = []
  for gen_part in gen_parts:
    graph_nodes.append([
      gen_part.idx, gen_part.pdgId, gen_part.status, gen_part.pt, gen_part.eta, gen_part.phi, gen_part.mass
    ])
    pairs = []
    if gen_part.momIdx >= 0:
      pairs.append([ gen_part.momIdx, gen_part.idx ])
    if gen_part.dauIdx1 >= 0:
      pairs.append([ gen_part.idx, gen_part.dauIdx1 ])
    if gen_part.dauIdx2 >= 0:
      pairs.append([ gen_part.idx, gen_part.dauIdx2 ])
    for pair in pairs:
      if pair not in graph_edges:
        graph_edges.append(pair)
  output_file_name_dot = output_file_name.replace('.png', '.dot')
  with open(output_file_name_dot, "w") as dot_file:
    dot_file.write(jinja2.Template(GRAPH_TEMPLATE).render(nodes = graph_nodes, edges = graph_edges))
  output_file_name_eps = output_file_name.replace('.png', '.eps')
  subprocess.call("dot -Teps {} > {}".format(output_file_name_dot, output_file_name_eps), shell = True)
  subprocess.call("convert -flatten -density 150 {} {}".format(output_file_name_eps, output_file_name), shell = True)
  logging.debug("Created file {}".format(output_file_name))
  if not keep_tmp:
    os.remove(output_file_name_dot)
    os.remove(output_file_name_eps)

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True, nargs = '+',
    help = 'R|Input NanoAOD Ntuple',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'directory', required = False, default = '.',
    help = 'R|Output directory',
  )
  parser.add_argument('-r', '--rle',
    type = str, dest = 'rle', metavar = 'number', required = True, nargs = '+',
    help = 'R|Run:lumi:event number',
  )
  parser.add_argument('-d', '--delphes',
    dest = 'delphes', action = 'store_true', default = False,
    help = 'R|Assume Delphes flat tree as input',
  )
  parser.add_argument('-k', '--keep',
    dest = 'keep', action = 'store_true', default = False,
    help = 'R|Keep temporary files',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()
  input_file_names = args.input
  output_dir = os.path.abspath(args.output)
  rles = args.rle
  logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)
  delphes = args.delphes

  for input_file_name in input_file_names:
    if not hdfs.isfile(input_file_name):
      raise ValueError("No such file: %s" % input_file_name)

  if delphes:
    rles = [ '0:0:{}'.format(rle) for rle in rles ]
  for rle in rles:
    assert(re.match('^\d+:\d+:\d+$', rle))

  mtable = MassTable()

  for input_file_name in input_file_names:
    graph_map = get_graph(input_file_name, rles, mtable, delphes)
    for rle in graph_map:
      output_file_filename = '{}-{}.png'.format(
        os.path.splitext(os.path.basename(input_file_name))[0], rle.replace(':', '-')
      )
      output_file_name = os.path.join(output_dir, output_file_filename)
      save_graph(graph_map[rle], output_file_name, args.keep)
