#!/bin/bash

function task_1_1()
{
    dir="./task_4_1_1"
    sar_pre="${dir}/sar/sar_"
    top_pre="${dir}/top/top_"
    str_pre="${dir}/str/str_"

    interval=1
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
    sar -P ALL $interval $run_time > $sar_file &
    # run top
    top -b -n $run_time -d $interval > $top_file &
    wait
    exit 1
}

function task_1_2()
{   
    dir="./task_4_1_2"
    crypt_num=8
    run_num=5

    if [[ $1 == "-crypt-ops" ]]; then
        for (( j=1; j<=$crypt_num; j++ ))
        do
            for (( i=1; i<=$run_num; i++ ))
            do
                suffix=/crypt-ops/cryptops_${j}_${i}run.txt
                # run with crypt-ops
                str_file=${dir}${suffix}
                stress-ng --crypt $crypt_num --crypt-ops 8000 --metrics-brief --perf -t 10s --log-file $str_file &
                wait
            done
        done
    else
        for (( j=1; j<=$crypt_num; j++ ))
        do
            for (( i=1; i<=$run_num; i++ ))
            do
                suffix=/crypt/crypt_${j}_${i}run.txt
                str_file=${dir}${suffix}
                # run simple crypt
                stress-ng --crypt $crypt_num --metrics-brief --perf -t 10s --log-file $str_file &
                wait
            done
        done
    fi
    exit 1
}

function task_1_3()
{
    dir="./task_4_1_3"
    matrix_num=( 2 4 8 )
    matrix_size=( 128 256 512 )
    for num in "${matrix_num[@]}"
    do
        for size in  "${matrix_size[@]}"
        do
            suffix=/matrix_${num}_size${size}.txt
            str_file=${dir}${suffix}
            stress-ng --matrix $num --matrix-method prod --matrix-size $size --metrics-brief --perf -t 10s --log-file $str_file &
            wait
        done
    done
    
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
          task_1_2 $@
          break
          ;;
      (-matrix)
          echo "Task 1.3"
          task_1_3 $@
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