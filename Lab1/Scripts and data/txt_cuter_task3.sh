#!/bin/bash
# Batch processing
FILES='./*'
result_file="result.txt"


# Grab specific metrics 
echo "" > cache_misses.txt
echo "" > instructions.txt
echo "" > cache_ref.txt
echo "" > bogo.csv
for file in $FILES
do
  # pick Instructions
  data=`cat $file | grep 'Instructions' | grep 'per' | awk {'$1=$2=$3=""; print $0'}’ | sed -e 's/^[ \t]*//' | awk '{print $1", "$2", "$3", "$4}'`
  result="$file, $data"
  echo $result >> instructions.txt

  # pick Cache References
  data=`cat $file | grep 'Cache References'| awk {'$1=$2=$3=""; print $0'}’ | sed -e 's/^[ \t]*//' | awk '{print $1", "$2", "$3", "$4", "$5}'`
  result="$file, $data"
  echo $result >> cache_ref.txt

  # pick Cache Misses
  data=`cat $file | grep 'Cache Miss'| awk {'$1=$2=$3=""; print $0'}’ | sed -e 's/^[ \t]*//' | awk '{print $1", "$2", "$3", "$4", "$5}'`
  result="$file, $data"
  echo $result >> cache_misses.txt

  # pick bogo ops 
  data=`nl $file | sed -n '7p' | awk {'print $6'}’`
  result="$file,$data"
  echo $result >> bogo.csv
done