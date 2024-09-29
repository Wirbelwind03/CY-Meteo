#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source "$DIR/src/shell/type.sh"
source "$DIR/src/shell/locations.sh"
source "$DIR/src/shell/dates.sh"
source "$DIR/src/shell/sortings.sh"
source "$DIR/src/shell/file.sh"

LATITUDE_MINIMUM=-90
LATITUDE_MAXIMUM=90
LONGITUDE_MINIMUM=-180
LONGITUDE_MAXIMUM=180

show_help(){
    cat documentation/help.txt
}

check_missing_arguments(){
    if [[ $2 == "" ]]
    then
        echo "Option $1 need a argument !"
        exit 0
    fi
}

while [ $# -gt 0 ] ; do
  case $1 in
    "-t"* | "-p"* | -w | -h | -m) 
        if [[ $1 == "-t" ]] || [[ $1 == "-p" ]]
        then
            check_missing_arguments $1 $2
        fi
        get_type_option $1 $2
        TYPE_OPTION_DEFINED=true
        ;;
    -F | -G | -S | -A | -O | -Q) 
        get_location_option $1
        LOCATION_OPTION_DEFINED=true
        ;;
    -d) 
        check_missing_arguments $1 $2
        get_dates $2 $3
        DATE_OPTION_DEFINED=true
        ;;
    -f) 
        check_missing_arguments $1 $2
        get_file $2
        ;;
    --tab | --abr | --avl) get_tri $1;;
    --help) 
        show_help 
        exit 0
        ;;
  esac
  shift
done

# Check if file has been defined
if [ -z ${FILE} ]
then
    echo "File is not defined !"
    exit 0
fi

if [ -z ${TYPE_OPTION_DEFINED} ]
then
    echo "At least one option of \"type\" must be choosen. See --help"
    exit 0
fi

if [ -z ${SORTING_OPTION} ]
then
    SORTING_OPTION="AVL"
fi

# Get location in the CSV if option has been choosen
if [ ! -z ${LOCATION} ]
then
    sort_csv_by_location
fi

# Get dates in the CSV if option has been choosen
if [ ! -z ${DATE_MINIMUM} ] && [ ! -z ${DATE_MAXIMUM} ]
then
    sort_csv_by_dates
fi

get_type_csv

rm $FILE
