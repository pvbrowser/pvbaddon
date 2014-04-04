#!/bin/bash
# make within directory
if [ "${1}" = "." ]; then
  exit
fi
if [ "${1}" = "./shell" ]; then
  exit
fi
# echo make within $1
cd $1
if [ "x${2}" = "x" ]; then
  export profile=$(ls *.pro)
  if [ "x${profile}" != "x" ]; then
    qmake $profile
  fi
fi
make $2
if [ "x${mypause}" = "xtrue" ]; then
  echo hit return
  read
fi
