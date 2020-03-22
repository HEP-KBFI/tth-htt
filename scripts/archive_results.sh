#!/bin/bash

# Example usage:
# archive_results.sh -i ~/ttHAnalysis/2017/2020Mar22 -o /hdfs/local/$USER/archives -f
# for d in ~/ttHAnalysis/201*/*; do archive_results.sh -i $d -o /hdfs/local/$USER/archives -f; done

check_if_exists() {
  if [ ! -z "$1" ] && [ ! -d "$1" ]; then
    echo "Directory '$1' does not exist";
    exit 1;
  fi
}

TMP_DIR=/scratch/1/$USER;
OUTPUT_DIR=$PWD;
DRYRUN=false;
OVERWRITE_OUTPUT_FILE=false;
VERBOSE=false;

show_help() {
  THIS_SCRIPT=$0;
  echo -ne "Usage: $(basename $THIS_SCRIPT) -i <input dir> [ -o <output dir> = $OUTPUT_DIR ] " 1>&2;
  echo     " [ -t <tmp dir> = $TMP_DIR ] [ -d ] [ -f ] [ -v ]" 1>&2;
  exit 0;
}

while getopts "h?dfvi:o:t:" opt; do
  case "${opt}" in
  h|\?) show_help
        ;;
  d) DRYRUN=true;
        ;;
  f) OVERWRITE_OUTPUT_FILE=true;
        ;;
  v) VERBOSE=true;
        ;;
  i) INPUT_DIR=${OPTARG};
        ;;
  o) OUTPUT_DIR=${OPTARG};
        ;;
  t) TMP_DIR=${OPTARG};
        ;;
  esac
done

check_if_exists $INPUT_DIR
check_if_exists $OUTPUT_DIR
check_if_exists $TMP_DIR

INPUT_SPLIT=$(echo $INPUT_DIR | tr '/' ' ')

if [ $(echo $INPUT_SPLIT | wc -w) != 5 ]; then
  echo "Invalid input directory: $INPUT_DIR";
  exit 1;
fi

INPUT_SPLIT_LV0=$(echo $INPUT_SPLIT | awk '{print $1}')
if [ $INPUT_SPLIT_LV0 != "home" ]; then
  echo "Directory '$INPUT_DIR' is not in \$HOME";
fi

INPUT_DIR_HDFS=$(echo $INPUT_DIR | sed 's/^\/home\//\/local\//g');
if [ $(hdfs dfs -ls $INPUT_DIR_HDFS 2>/dev/null | wc -l) = 0 ]; then
  echo "Unable to find complementary directory on /hdfs: $INPUT_DIR_HDFS";
  exit 1;
fi

INPUT_SPLIT_LV2=$(echo $INPUT_SPLIT | awk '{print $3}')
INPUT_SPLIT_LV3=$(echo $INPUT_SPLIT | awk '{print $4}')
INPUT_SPLIT_LV4=$(echo $INPUT_SPLIT | awk '{print $5}')
CHANNELS=$(ls $INPUT_DIR/datacards)

for CHANNEL in $CHANNELS; do
  OUTPUT_FILE_NAME=${INPUT_SPLIT_LV2}_${INPUT_SPLIT_LV3}_${INPUT_SPLIT_LV4}_${CHANNEL}.tar.lz4
  OUTPUT_FILE_PATH=${OUTPUT_DIR}/${OUTPUT_FILE_NAME}
  if [ -f $OUTPUT_FILE_PATH ] && [ $OVERWRITE_OUTPUT_FILE = false ]; then
    echo "File $OUTPUT_FILE_PATH already exists. Use -f to enable overwriting. Aborting.";
    exit 1;
  fi

  HDFS_SUBDIRS=$(hdfs dfs -ls $INPUT_DIR_HDFS 2>/dev/null | grep ^d | awk '{print $NF}' | tr '/' ' ' | awk '{print $NF}');
  for HDFS_SUBDIR in $HDFS_SUBDIRS; do
    SYMLINK_SRC=/hdfs${INPUT_DIR_HDFS}/${HDFS_SUBDIR}/${CHANNEL};
    SYMLINK_DST_DIR=${INPUT_DIR}/${HDFS_SUBDIR}_hdfs;
    mkdir -p $SYMLINK_DST_DIR;
    SYMLINK_DST=${SYMLINK_DST_DIR}/${CHANNEL};
    echo "Creating symlink: $SYMLINK_DST -> $SYMLINK_SRC";
    if [ $DRYRUN = false ]; then
      rm -f $SYMLINK_DST;
      ln -s $SYMLINK_SRC $SYMLINK_DST;
    fi
  done

  OUTPUT_FILE_TMP=${TMP_DIR}/${OUTPUT_FILE_NAME};
  TAR_OPTS=cfh
  if [ $VERBOSE = true ]; then
    TAR_OPTS=${TAR_OPTS}v;
  fi
  cd $INPUT_DIR/..;
  echo "Current working directory: $PWD";
  echo "Current time: `date`";
  echo "Creating archive: $OUTPUT_FILE_TMP";
  INPUT_DIR_BASE=$(basename $INPUT_DIR);
  INPUT_FILES="${INPUT_DIR_BASE}/*${CHANNEL} ${INPUT_DIR_BASE}/*${CHANNEL}.log* ${INPUT_DIR_BASE}/*/${CHANNEL}";
  echo "Input files: $INPUT_FILES";
  if [ $DRYRUN = false ]; then
    tar $TAR_OPTS - $INPUT_FILES | lz4 -f - $OUTPUT_FILE_TMP;
  fi
  echo "Finished at: `date`";

  if [ $DRYRUN = false ]; then
    if [[ $OUTPUT_FILE_PATH =~ ^/hdfs/ ]]; then
      OUTPUT_FILE_PATH_NOHDFS=$(echo $OUTPUT_DIR | sed 's/^\/hdfs\//\//g');
      hdfs dfs -copyFromLocal -f $OUTPUT_FILE_TMP $OUTPUT_FILE_PATH_NOHDFS 2>/dev/null;
      rm -f $OUTPUT_FILE_TMP;
    else
      mv $OUTPUT_FILE_TMP $OUTPUT_FILE_PATH;
    fi
  fi
  echo "Created archive: $OUTPUT_FILE_PATH";

  for HDFS_SUBDIR in $HDFS_SUBDIRS; do
    SYMLINK_DST=${INPUT_DIR}/${HDFS_SUBDIR}_hdfs/${CHANNEL};
    echo "Removing symlink: $SYMLINK_DST";
    if [ $DRYRUN = false ]; then
      rm -f $SYMLINK_DST;
    fi
  done
done

echo "If you want to delete the archived files, run:";
echo "hdfs -rm -r $INPUT_DIR_HDFS";
echo "mkdir -p ~/empty_dir && rm -rf ~/empty_dir/*";
echo "rsync -a --delete ~/empty_dir/ $INPUT_DIR/";
echo "rmdir $INPUT_DIR";
