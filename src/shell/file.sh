#!/bin/bash

get_file()
{
    if [ ! -f "$1" ]
    then
        echo "$1 doesn't exist"
        exit 0
    else
        output="./outputs/temp.csv"
        cp $1 $output
        FILE=$output
    fi
}



