#!/bin/bash
sar_pre="./sar/sar_"
top_pre="./top/top_"
str_pre="./str/str_"

function task_1_1()
{
    cpu_stressor_num=$1
    run_time=$2
    shift 2

    # the common suffix of files
    suffix="${cpu_stressor_num}_cpu.txt"
    # the result file for stress
    str_file=${str_pre}${suffix}

    if [[ $1 == "-load" ]]; then
        percent=$2
        suffix="${percent}%load_${suffix}"
        str_file=${str_pre}${suffix}
        
        if [[ $3 == "-backoff" ]]; then
            bo_input=$4
            let bo_time=bo_input*1000000

            suffix="backoff_${bo_input}s_${suffix}"
            str_file=${str_pre}${suffix}

            # "run cpu load with backoff stress"
            echo "run cpu load with backoff stress"
            stress-ng --cpu $cpu_stressor_num --cpu-load $percent --metrics-brief --perf --timeout $run_time --backoff $bo_time --log-file $str_file &
        else
            # "run with cpu load"
            echo "run with cpu load"
            stress-ng --cpu $cpu_stressor_num --cpu-load $percent --metrics-brief --perf --timeout $run_time --log-file $str_file &
        fi        
    else
        # "run without cpu load"
        echo "run without cpu-load"
        stress-ng --cpu $cpu_stressor_num --metrics-brief --perf --timeout $run_time --log-file $str_file &
    fi

    # the result file for sar and top
    sar_file=${sar_pre}${suffix}
    top_file=${top_pre}${suffix}

    # run sar
    sar -P ALL 1 $run_time > $sar_file &
    # run top
    top -b -n $run_time -d 1 > $top_file &
    wait
    exit 1
}

function task_1_2()
{
    exit 1
}

function task_1_3()
{
    exit 1
}

function task_1_4()
{
    exit 1
}

function task_2_1()
{
    exit 1
}

function task_3_1()
{
    exit 1
}

while :
do
    case "$1" in
      (-cpu)
          echo "Task 1.1"
          shift
          task_1_1 $@
          break
          ;;

      (-crypt)
          echo "Task 1.2"
          shift
          break
          ;;
      (-matrix)
          echo "Task 1.3"
          
          shift
          break
           ;;
      (-pthread) 
          echo "Task 1.4"
          
          shift
          break
          ;;
      (-brk)
          echo "Task 2.1"
          
          shift
          break
          ;;
      (-hdd)  
          echo "Task 3.1"
          
          shift
          break
          ;;
    esac
done