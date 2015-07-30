#!/bin/bash

# PRE-REQUISITES
# - We need astyle (use brew install astyle)
# - We need colordiff installed (use brew install colordiff)

TMP_FILE="/tmp/indented"
ASTYLE_OPTS="-n -s2 -C --style=java" # slighlty un-standard with soft tabs of size 2...

for f in $(find sternenwecker -type f \( -iname \*.h -o -iname \*.cpp -o -iname \*.ino \)); do
  astyle $ASTYLE_OPTS < $f > $TMP_FILE
  
  diff $f $TMP_FILE >/dev/null
  if [[ $? == 0 ]]; then
    continue
  fi
  
  echo "----------------------------------------------------------------"
  echo "----------------------------------------------------------------"
  echo "----------------------------------------------------------------"
  tput clear
  colordiff --context=0 $f $TMP_FILE
  
  read -p "Do you want to correct? " -n 1
  if [[ $REPLY =~ ^[Qq]$ ]]; then
    echo
    exit 0
  fi
  if [[ $REPLY =~ ^[Yy]$ ]]; then
    cp $TMP_FILE $f
  fi
  
  rm $TMP_FILE
done
# for i in *; do gindent -kr -l200 -i2 -nut $i -o c/$i; done
#
# for i in *; do gindent -kr -l200 $i -ut -ts4 -i4 -o c/$i; done