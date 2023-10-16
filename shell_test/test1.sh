#!/bin/bash

#遍历data/目录下的txt文件，并备份

suffix=`date +%Y%m%d`

for f in `find data/ -type f -name "*.txt"`
do
	echo "file$f"
	cp ${f} ${f}_${suffix}
done
