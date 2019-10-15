#!/bin/bash

# get used and total.
echo '' > mem_used.txt
SECONDS=0
while [ $SECONDS -lt 1 ]
do
    sleep 0.1
    vmstat -s | grep 'used memory\| total memory' > a.txt
    used_mem=`cat a.txt | grep 'used memory' | awk {'print $1'}`
    total_mem=`cat a.txt | grep 'total memory' | awk {'print $1'}`
    percentail=`echo "scale=3; $used_mem/$total_mem" | bc`
    echo $percentail
    echo $percentail >> mem_used.txt
done
rm a.txt