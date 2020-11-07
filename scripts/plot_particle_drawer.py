#!/usr/bin/env python

import itertools
import collections
import os
import jinja2
import subprocess
import argparse

TYPE_MAP = {
  'idx' : lambda x: int(x),
  'ID' : lambda x: int(x),
  'Name' : lambda x: x,
  'Stat' : lambda x: int(x),
  'Mo1' : lambda x: int(x),
  'Mo2' : lambda x: int(x),
  'Da1' : lambda x: int(x),
  'Da2' : lambda x: int(x),
  'nMo' : lambda x: int(x),
  'nDa' : lambda x: int(x),
  'pt' : lambda x: float(x),
  'eta' : lambda x: float(x),
  'phi' : lambda x: float(x),
  'px' : lambda x: float(x),
  'py' : lambda x: float(x),
  'pz' : lambda x: float(x),
  'm' : lambda x: float(x),
}

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

def read_logfile(filename):
  if not os.path.isfile(filename):
    raise RuntimeError("No such file: %s" % filename)
  results = collections.OrderedDict()
  with open(filename, 'r') as f:
    rle = ''
    header = []
    particles = []
    for line in f:
      line_stripped = line.strip()
      if line.startswith('Begin processing'):
        if rle:
          results[rle] = particles
        line_split = line_stripped.split()
        rle = ':'.join(
          line_split[line_split.index(key) + 1].rstrip(',') for key in [ 'Run', 'LumiSection', 'Event' ]
        )
        header = []
        particles = []
      elif line_stripped.count('|') == 7:
        line_split = list(itertools.chain(*[ col.strip().split() for col in line_stripped.split('|') ]))
        if line_split[0] == 'idx':
          header = line_split
        else:
          particle = {}
          for key in TYPE_MAP:
            particle[key] = TYPE_MAP[key](line_split[header.index(key)])
          particles.append(particle)
    if particles:
      results[rle] = particles
    return results

def save_graph(gen_parts, output_file_name, keep_tmp = False, direct_to_png = True):
  assert(output_file_name.endswith('.png'))
  graph_nodes = []
  graph_edges = []
  graph_edges_parsable = []
  for gen_part in gen_parts:
    graph_nodes.append([
      gen_part['idx'], gen_part['ID'], gen_part['Stat'],
      gen_part['pt'], gen_part['eta'], gen_part['phi'], gen_part['m'],
    ])
    for relative in [ 'Mo', 'Da' ]:
      first_relative = '{}1'.format(relative)
      second_relative = '{}2'.format(relative)
      if gen_part[first_relative] >= 0:
        edge = [ gen_part[first_relative], gen_part['idx']]
        if relative == 'Da':
          edge = list(reversed(edge))
        edge_parseable = '{}_{}'.format(*edge)
        if edge_parseable in graph_edges_parsable:
          continue
        graph_edges.append(edge)
        graph_edges_parsable.append(edge_parseable)
      if gen_part[second_relative] >= 0 and gen_part[first_relative] != gen_part[second_relative]:
        edge = [ gen_part[second_relative], gen_part['idx']]
        if relative == 'Da':
          edge = list(reversed(edge))
        edge_parseable = '{}_{}'.format(*edge)
        if edge_parseable in graph_edges_parsable:
          continue
        graph_edges.append(edge)
        graph_edges_parsable.append(edge_parseable)

  output_file_name_dot = output_file_name.replace('.png', '.dot')
  with open(output_file_name_dot, "w") as dot_file:
    dot_file.write(jinja2.Template(GRAPH_TEMPLATE).render(nodes = graph_nodes, edges = graph_edges))
  if direct_to_png:
    subprocess.call("dot -Tpng {} > {}".format(output_file_name_dot, output_file_name), shell = True)
  else:
    output_file_name_eps = output_file_name.replace('.png', '.eps')
    subprocess.call("dot -Teps {} > {}".format(output_file_name_dot, output_file_name_eps), shell = True)
    subprocess.call("convert -flatten -density 150 {} {}".format(output_file_name_eps, output_file_name), shell = True)
    if not keep_tmp:
      os.remove(output_file_name_eps)
  if not keep_tmp:
    os.remove(output_file_name_dot)

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True,
    help = 'Log file',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'directory', required = False, default = '.',
    help = 'Output directory',
  )
  parser.add_argument('-k', '--keep',
    dest = 'keep', action = 'store_true', default = False,
    help = 'Keep temporary files',
  )
  parser.add_argument('-p', '--direct-png',
    dest = 'direct_png', action = 'store_true', default = False,
    help = 'Try to generate png directly',
  )
  args = parser.parse_args()

  output_dir = os.path.abspath(args.output)
  if not os.path.isdir(output_dir):
    os.makedirs(output_dir)

  results = read_logfile(args.input)
  for rle in results:
    output_filename = os.path.join(output_dir, 'particleDrawer_{}.png'.format(rle.replace(':', '-')))
    save_graph(results[rle], output_filename, keep_tmp = args.keep, direct_to_png = args.direct_png)
