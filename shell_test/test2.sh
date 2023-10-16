#!/bin/bash

if [ -f data/userinfo.txt ]
then
    rm -f data/userinfo.txt
fi

for i in {00..09}
do
    p=$(date +%s | sha256sum | base64 | head -c 15)
    sudo useradd user_${i}
    echo -e "${p}/n${p}" | sudo passwd user_${i}
    echo "user_${i}  ${p}" >> data/userinfo.txt
done

