#!/bin/bash

cd data/wwwroot/app
for f in `find .`
do
    f_p=`stat -c %a $f`
    f_u=`stat -c %U $f`
    f_g=`stat -c %G $f`

    if [ -d $f ]
    then
        [ $f_p != '755' ] && chmod 755 $f    
    else
        [ $f_p != '644' ] && chmod 644 $f
    fi

    [ $f_u != 'www' ] && chown liu $f
    [ $f_g != 'root' ] && chown :root $f
done