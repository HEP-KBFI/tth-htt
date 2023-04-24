#!/bin/bash

# Example usage:
# archive_results.sh -i ~/ttHAnalysis/2017/2020Mar22 -o /local/$USER/archives -f
# for d in ~/ttHAnalysis/201*/*; do archive_results.sh -i $d -o /local/$USER/archives -f; done

check_if_exists() {
  if [ ! -z "$1" ] && [ ! -d "$1" ]; then
    echo "Directory '$1' does not exist";
    exit 1;
  fi
}

TMP_DIR=/scratch/persistent/$USER;
OUTPUT_DIR=/local/$USER/archives;
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

INPUT_DIR_SP=$(echo $INPUT_DIR | sed 's/^\/home\//\/scratch/persistent\//g');
if [ ! -d $INPUT_DIR_SP ]; then
  echo "Unable to find complementary directory on /scratch/persistent: $INPUT_DIR_SP";
  exit 1;
fi

INPUT_SPLIT_LV2=$(echo $INPUT_SPLIT | awk '{print $3}')
INPUT_SPLIT_LV3=$(echo $INPUT_SPLIT | awk '{print $4}')
INPUT_SPLIT_LV4=$(echo $INPUT_SPLIT | awk '{print $5}')
CHANNELS=$(ls $INPUT_DIR/datacards)

INPUT_DIR_REALPATH=$(realpath $INPUT_DIR)
INPUT_DIR_TMP=$TMP_DIR/"${INPUT_DIR_REALPATH:1}"
INPUT_DIR_TMP_PARENT=$INPUT_DIR_TMP/..

for CHANNEL in $CHANNELS; do
  echo "Recreating $INPUT_DIR_TMP";
  rm -rf $INPUT_DIR_TMP;
  mkdir -p $INPUT_DIR_TMP;

  OUTPUT_FILE_NAME=${INPUT_SPLIT_LV2}_${INPUT_SPLIT_LV3}_${INPUT_SPLIT_LV4}_${CHANNEL}.tar.lz4
  OUTPUT_FILE_PATH=${OUTPUT_DIR}/${OUTPUT_FILE_NAME}
  if [ -f $OUTPUT_FILE_PATH ] && [ $OVERWRITE_OUTPUT_FILE = false ]; then
    echo "File $OUTPUT_FILE_PATH already exists. Use -f to enable overwriting. Aborting.";
    exit 1;
  fi

  SP_SUBDIRS=$(ls -l $INPUT_DIR_SP 2>/dev/null | grep ^d | awk '{print $NF}' | tr '/' ' ' | awk '{print $NF}');
  for SP_SUBDIR in $SP_SUBDIRS; do
    SYMLINK_SRC=${INPUT_DIR_SP}/${SP_SUBDIR}/${CHANNEL};
    SYMLINK_DST_DIR=${INPUT_DIR_TMP}/${SP_SUBDIR}_scratch-persistent;
    mkdir -p $SYMLINK_DST_DIR;
    SYMLINK_DST=${SYMLINK_DST_DIR}/${CHANNEL};
    echo "Creating symlink: $SYMLINK_DST -> $SYMLINK_SRC";
    rm -f $SYMLINK_DST;
    ln -s $SYMLINK_SRC $SYMLINK_DST;
  done

  OUTPUT_FILE_TMP=${TMP_DIR}/${OUTPUT_FILE_NAME};
  TAR_OPTS=cfh
  if [ $VERBOSE = true ]; then
    TAR_OPTS=${TAR_OPTS}v;
  fi
  cd $INPUT_DIR_TMP_PARENT;
  echo "Current working directory: $PWD";
  echo "Current time: `date`";
  echo "Creating archive: $OUTPUT_FILE_TMP";
  INPUT_FILES="${INPUT_DIR}/*${CHANNEL} ${INPUT_DIR}/*${CHANNEL}.log* ${INPUT_DIR}/*/${CHANNEL}";
  for INPUT_FILE in $INPUT_FILES; do
    SYMLINK_TARGET=$TMP_DIR/"${INPUT_FILE:1}";
    if [ -d $INPUT_FILE ]; then
      mkdir -p $(dirname $SYMLINK_TARGET);
    fi
    ln -s $INPUT_FILE $SYMLINK_TARGET;
  done
  ARCHIVE_TARGET="$(basename $INPUT_DIR_TMP)/*"
  echo "Input files: $ARCHIVE_TARGET";
  if [ $DRYRUN = false ]; then
    tar $TAR_OPTS - $ARCHIVE_TARGET | lz4 -f - $OUTPUT_FILE_TMP;
  fi
  echo "Finished at: `date`";

  if [ $DRYRUN = false ]; then
    mv -v $OUTPUT_FILE_TMP $OUTPUT_FILE_PATH;
  fi
  echo "Created archive: $OUTPUT_FILE_PATH";
done

echo "If you want to delete the archived files, run:";
echo "mkdir -p /scratch/persistent/$USER/empty_dir && rm -rf /scratch/persistent/$USER/empty_dir/*";
echo "rsync -a --delete /scratch/persistent/$USER/empty_dir/ $INPUT_DIR_SP/";
echo "rmdir $INPUT_DIR_SP";
echo "mkdir -p ~/empty_dir && rm -rf ~/empty_dir/*";
echo "rsync -a --delete ~/empty_dir/ $INPUT_DIR/";
echo "rmdir $INPUT_DIR";
