#!/bin/bash

for mount_p in `df |sed '1d' |grep -v 'tmpfs' |awk '{print $NF}'`
do

    touch $mount_p/testfile && rm -f $mount_p/testfile
    if [ $? -ne 0 ]
    then
        echo "$mount_p 读写有问题"
    else
        echo "$mount_p 读写正常"
    fi
done
