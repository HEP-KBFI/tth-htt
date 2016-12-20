import logging, sys, argparse, os, getpass, re

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

  analysis_path = os.path.join(
    '/home', args.user, 'ttHAnalysis', str(args.era), args.version, 'output_rle', args.channel
  )
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

  logging.info("Result:")
  max_key_len = max(map(len, rles.keys()))
  padding = lambda x: ' ' * (max_key_len - len(x))
  for sample_name in rles:
    print("{sample_name}: %s{nof_rles}".format(
      sample_name = sample_name,
      nof_rles    = len(rles[sample_name])
    ) % padding(sample_name))
  print("Total: %s{nof_rles}".format(nof_rles = sum(map(len, rles.values()))) % padding("Total"))
  logging.info("Done")

  #TODO: SAVE THE RLE NUMBERS TO DISK
  #TODO: FIGURE OUT HOW TO USE THESE FILES IN ADDMEM CFG FILE THAT CREATES MEM JOBS