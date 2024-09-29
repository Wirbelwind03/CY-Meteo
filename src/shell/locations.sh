#!/bin/bash

locations=(
    "France"
    "Guyane"
    "Saint_Pierre_et_Miquelon"
    "Antilles"
    "Océan_Indien"
    "Antarctique"
)

get_location_option() 
{
    # Check if the user has choosen multiple locations
    if [ ! -z ${LOCATION} ]
    then
        echo "A single location must be choosen"
        exit 0
    fi

    case $1 in

        -F) 
        LOCATION=${locations[0]} 
        LATITUDE_MINIMUM=41
        LATITUDE_MAXIMUM=51
        LONGITUDE_MINIMUM=-7.5
        LONGITUDE_MAXIMUM=10
        ;;
        -G) 
        LOCATION=${locations[1]} 
        LATITUDE_MINIMUM=2
        LATITUDE_MAXIMUM=6
        LONGITUDE_MINIMUM=-54
        LONGITUDE_MAXIMUM=-51
        ;;
        -S) 
        LOCATION=${locations[2]} 
        LATITUDE_MINIMUM=46
        LATITUDE_MAXIMUM=48
        LONGITUDE_MINIMUM=-57
        LONGITUDE_MAXIMUM=-56
        ;;
        -A) 
        LOCATION=${locations[3]} 
        LATITUDE_MINIMUM=8
        LATITUDE_MAXIMUM=28
        LONGITUDE_MINIMUM=-85
        LONGITUDE_MAXIMUM=-53
        ;;
        -O) 
        LOCATION=${locations[4]} 
        LATITUDE_MINIMUM=-45
        LATITUDE_MAXIMUM=15
        LONGITUDE_MINIMUM=42
        LONGITUDE_MAXIMUM=114
        ;;
        -Q) 
        LOCATION=${locations[5]} 
        LATITUDE_MAXIMUM=-63
        ;;

    esac
}

sort_csv_by_location()
{
    case $LOCATION in

        France) 
            awk -F ";" 'NR==1{ print } $1 ~ /^07+/ { print }' $FILE > tmp && mv tmp $FILE 
        ;;
        
        Guyane) 
            awk -F ";" 'NR==1{ print } $1 ~ /^81+/ { print }' $FILE > tmp && mv tmp $FILE 
        ;;
        
        Saint_Pierre_et_Miquelon) 
            awk -F ";" 'NR==1{ print } $1 == "71805" { print }' $FILE > tmp && mv tmp $FILE 
        ;;
        
        Antilles) 
            awk -F ";" 'NR==1{ print } $1 ~ /^78+/ { print }' $FILE > tmp && mv tmp $FILE 
        ;;
        
        Océan_Indien) 
            awk -F ";" 'NR==1{ print } $1 ~ /^6+/ { print }' $FILE > tmp && mv tmp $FILE 
        ;;
        
        Antarctique) 
            awk -F ";" 'NR==1{ print } $1 == "89642" { print }' $FILE > tmp && mv tmp $FILE 
        ;;

    esac

    sed -i 's/$/;/' $FILE
}
