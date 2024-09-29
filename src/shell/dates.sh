#!/bin/bash

check_date_format() 
{
    date_format="^[0-9]{4}-(0[0-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$"

    if [[ ! "$1" =~ $date_format ]]
    then
        echo "Date format is not respected, it should be : year-month-day ( YYYY-MM-DD )"
        exit 0
    fi
}

inverse_date_minimum_et_maximum()
{
    date_temp=$1
    DATE_MINIMUM=$2
    DATE_MAXIMUM=$date_temp
}

get_dates()
{
    DATE_MINIMUM=$1

    if [ -z $2 ]
    then
        echo "The maximum for date is not defined"
        exit 0
    else
        DATE_MAXIMUM=$2
    fi

    check_date_format $DATE_MINIMUM
    check_date_format $DATE_MAXIMUM

    date_minimum_year=$(echo $DATE_MINIMUM | cut -c 1-4)
    date_minimum_month=$(echo $DATE_MINIMUM | cut -c 6-7)
    date_minimum_day=$(echo $DATE_MINIMUM | cut -c 9-10)

    date_maximum_year=$(echo $DATE_MAXIMUM | cut -c 1-4)
    date_maximum_month=$(echo $DATE_MAXIMUM | cut -c 6-7)
    date_maximum_day=$(echo $DATE_MAXIMUM | cut -c 9-10)

    # Compare year minimum and maximum
    if [ $date_minimum_year -gt $date_maximum_year ] 
    then
        inverse_date_minimum_et_maximum $DATE_MINIMUM $DATE_MAXIMUM
    
    # If year are the same
    # Compare month minimum and maximum
    elif [ $date_minimum_year -eq $date_maximum_year ] && [ $date_minimum_month -gt $date_maximum_month ]
    then
        inverse_date_minimum_et_maximum $DATE_MINIMUM $DATE_MAXIMUM
    
    # If year and month are the same
    # Compare day minimum and maximum
    elif [ $date_minimum_year -eq $date_maximum_year ] && [ $date_minimum_month -eq $date_maximum_month ] && [ $date_minimum_day -gt $date_maximum_day ]
    then
        inverse_date_minimum_et_maximum $DATE_MINIMUM $DATE_MAXIMUM
    fi
}

sort_csv_by_dates()
{
    date_minimum_year=$(echo $DATE_MINIMUM | cut -c 1-4)
    date_minimum_month=$(echo $DATE_MINIMUM | cut -c 6-7)
    date_minimum_day=$(echo $DATE_MINIMUM | cut -c 9-10)

    date_maximum_year=$(echo $DATE_MAXIMUM | cut -c 1-4)
    date_maximum_month=$(echo $DATE_MAXIMUM | cut -c 6-7)
    date_maximum_day=$(echo $DATE_MAXIMUM | cut -c 9-10)

    # Years sorting
    awk -v date_minimum_year="$date_minimum_year" -v date_maximum_year="$date_maximum_year" -F ";" 'substr($2,0,4) >= date_minimum_year && substr($2,0,4) <= date_maximum_year { print }' $FILE > tmp && mv tmp $FILE
    
    # Months sorting
    awk -v date_minimum_month="$date_minimum_month" -v date_maximum_month="$date_maximum_month" -F ";" 'substr($2,6,2) >= date_minimum_month && substr($2,6,2) <= date_maximum_month { print }' $FILE > tmp && mv tmp $FILE
    
    # Days sorting
    awk -v date_minimum_day="$date_minimum_day" -v date_maximum_day="$date_maximum_day" -F ";" 'substr($2,9,2) >= date_minimum_day && substr($2,9,2) <= date_maximum_day { print }' $FILE > tmp && mv tmp $FILE

    sed -i 's/$/;/' $FILE
}

