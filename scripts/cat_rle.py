import logging, sys, argparse, os, getpass, re

'''Example usage:

python scripts/cat_rle.py -e 2016 -c 2lss_1tau -v 2016Dec11 -u veelken -V

'''

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-e', '--era', dest = 'era', metavar = 'year', required = True, type = int,
                      choices = [2015, 2016],
                      help='R|Data/MC era')
  parser.add_argument('-c', '--channel', dest = 'channel', metavar = 'channel', required = True, type = str,
                      choices = ['0l_2tau', '0l_3ltau', '1l_1tau', '1l_2tau', '2los_1tau', '2lss_1tau', '3l_1tau'],
                      help='R|Channel')
  parser.add_argument('-v', '--version', dest = 'version', metavar = 'version', required = True, type = str,
                      help='R|Version of the analysis')
  parser.add_argument('-u', '--user', dest = 'user', metavar = 'name', required = False, type = str,
                      default = getpass.getuser(),
                      help = 'R|User name')
  parser.add_argument('-V', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help='R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  path_pattern = os.path.join(
    '/home', '%s', 'ttHAnalysis', str(args.era), args.version, '%s', args.channel
  )
  analysis_path = path_pattern % (args.user, 'output_rle')
  logging.debug("Checking if path '{directory_name}' is there".format(directory_name = analysis_path))
  if not os.path.exists(analysis_path):
    logging.error("No such directory: '{directory_name}'".format(directory_name = analysis_path))
    sys.exit(1)

  rle_pattern = re.compile('\d+:\d+:\d+')

  rles = {}
  logging.debug("Sweeping over the directories ...")
  for analysis_type in os.listdir(analysis_path):
    logging.debug("Processing subdirectory '{analysis_type}'".format(analysis_type = analysis_type))
    analysis_path_w_type = os.path.join(analysis_path, analysis_type)

    for sample_name in os.listdir(analysis_path_w_type):
      logging.debug("Processing subdirectory '{rle_directory}'".format(
        rle_directory = os.path.join(analysis_type, sample_name)
      ))
      rle_directory = os.path.join(analysis_path_w_type, sample_name)

      rles_arr = []
      for rle_filename in os.listdir(rle_directory):
        rle_file = os.path.join(rle_directory, rle_filename)
        if os.path.isfile(rle_file) and rle_file.endswith(rle_file):
          with open(rle_file, 'r') as f:
            for line in f:
              line = line.rstrip('\n')
              if line:
                matches = rle_pattern.match(line)
                if matches:
                  rles_arr.append(matches.group())

      logging.debug("Found {nof_rles} RLE numbers".format(nof_rles = len(rles_arr)))
      if rles_arr:
        if sample_name in rles:
          rles[sample_name].extend(rles_arr)
        else:
          rles[sample_name] = rles_arr

  logging.debug("Selecting only unique RLE numbers")
  for sample_name in rles:
    rles[sample_name] = list(set(rles[sample_name]))

  logging.info("Result:")
  max_key_len = max(map(len, rles.keys()))
  padding = lambda x: ' ' * (max_key_len - len(x))
  for sample_name in rles:
    print("{sample_name}: %s{nof_rles}".format(
      sample_name = sample_name,
      nof_rles    = len(rles[sample_name])
    ) % padding(sample_name))
  print("Total: %s{nof_rles}".format(nof_rles = sum(map(len, rles.values()))) % padding("Total"))

  save_path = path_pattern % (args.user, 'rles')
  logging.info("Checking if parent of '{directory_name}' is writable by the user".format(
    directory_name = save_path
  ))
  if not os.access(os.path.dirname(save_path), os.W_OK):
    new_dirname = path_pattern % (getpass.getuser(), 'rles')
    logging.info("Directory '{fail_dirname}' is not writable, switching over to '{new_dirname}'".format(
      fail_dirname = save_path,
      new_dirname = new_dirname
    ))
    save_path = new_dirname

  if not os.path.isdir(save_path):
    logging.info("Path '{save_path}' is not a directory, trying to create one".format(save_path = save_path))
    try:
      os.makedirs(save_path)
    except IOError:
      logging.error("Couldn't create '{save_path}', aborting".format(save_path = save_path))
      sys.exit(1)

  for sample_name in rles:
    rle_sample_file = os.path.join(save_path, '{base_name}.txt'.format(base_name = sample_name))
    logging.debug("Writing file '{rle_sample_file}'".format(rle_sample_file = rle_sample_file))
    with open(rle_sample_file, 'w') as f:
      for event in rles[sample_name]:
        f.write('{line}\n'.format(line = event))

  logging.debug("Done!")
