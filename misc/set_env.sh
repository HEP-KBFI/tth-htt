#!/bin/bash

if [ -z "$CMSSW_BASE" ]; then
  echo "Error! Variable CMSSW_BASE unset";
  return 1;
fi

if [ -z "$SCRAM_ARCH" ]; then
  echo "Error! Variable SCRAM_ARCH unset";
  return 1;
fi

MAKEFILE_LOCATION="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/Makefile";
if [ ! -f $MAKEFILE_LOCATION ]; then
  echo "File $MAKEFILE_LOCATION not present in the system, aborting";
  return 1;
fi

LIBHDFS_BUILT=false
make -f $MAKEFILE_LOCATION;
if [ $? -ne 0 ]; then
  echo "Failed to build libHDFS";
  return 1;
else
  echo "Successfully built libHDFS";
  LIBHDFS_BUILT=true;
fi

FORCE_SETENV=false
if [ "$LIBHDFS_BUILT" = true ]; then
  if [ $# -eq 1 ]; then
    if [ "$1" = "-f" ]; then
      FORCE_SETENV=true;
    else
      echo "Unrecognized argument: $1";
      return 1;
    fi
  elif [ $# -gt 1 ]; then
    echo "Too many arguments";
    return 1;
  fi

  if [[ -z "$CLASSPATH" || "$FORCE_SETENV" = true ]]; then
    echo "Setting up CLASSPATH";
    export CLASSPATH=`hadoop classpath --glob`;
    for j in $(ls /usr/lib/hadoop/client/*.jar); do export CLASSPATH=$CLASSPATH:$j; done;
  fi
fi

