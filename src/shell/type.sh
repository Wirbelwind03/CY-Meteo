#!/bin/bash

modes_type=(
    "MODE_1"
    "MODE_2"
    "MODE_3"
)

type_option_format="^-(t|p)[1-3]$"

check_mode()
{
    if [ $2 -lt 1 ] || [ $2 -gt 3 ]
    then
        echo "The mode for option $1 need to be between 1 and 3"
        exit 0
    fi
    
}

check_type_option_space()
{
    # Check if user used a space for -t and -p
    if [ -z $2 ] || [[ ! "$2" =~ $type_option_format ]]
    then
        type_option_argument=$1 
        type_option_number="${type_option_argument//[^0-9]/}"
    else
        type_option_number=$2
    fi   
}


get_type_option()
{
    case $1 in
        
        "-t"*)
            if [ $2 -ge 1 ] || [ $2 -le 3 ]
            then
                type_option_number=$2
            else
                type_option_argument=$1 
                type_option_number="${type_option_argument//[^0-9]/}"
                #check_type_option_space $1 $2
                echo $type_option_number
                
                check_mode $1 $type_option_number
            fi

            case $type_option_number in

                1) TEMPERATURES_MODE=${modes_type[0]} ;;
                2) TEMPERATURES_MODE=${modes_type[1]} ;;
                3) TEMPERATURES_MODE=${modes_type[2]} ;;

            esac
            ;;

        "-p"*)
            if [ $2 -ge 1 ] || [ $2 -le 3 ]
            then
                type_option_number=$2
            else
                type_option_argument=$1 
                type_option_number="${type_option_argument//[^0-9]/}"
                #check_type_option_space $1 $2
                echo $type_option_number
                
                check_mode $1 $type_option_number
            fi
            
            case $2 in

                1) PRESSIONS_MODE=${modes_type[0]} ;;
                2) PRESSIONS_MODE=${modes_type[1]} ;;
                3) PRESSIONS_MODE=${modes_type[2]} ;;

            esac
            ;;

        -w) 
            WIND=true
            ;;
        
        -h) 
            HEIGHT=true 
            ;;
        
        -m) 
            MOISTURE=true 
            ;;

    esac
}

get_type_csv()
{
    gcc -o obj/weather_sorting src/weather/weather_sorting.c src/weather/wind_sorting.c src/weather/height_sorting.c src/weather/moisture_sorting.c src/weather/tpmode_sorting.c src/lib/common.c src/lib/iso8601.c src/lib/structures/binaryTree.c src/lib/structures/avl.c src/lib/structures/linkedList.c src/lib/math/math.c src/lib/math/vector.c src/weather/common.c

    if [ ! -z ${TEMPERATURES_MODE} ]
    then
        case $TEMPERATURES_MODE in

            # $1 = Stations, $7 = Temperatures
            MODE_1)
                awk -F ";" 'BEGIN{print "t1"}; NR>1 && $11 != "" { print $1 ";" $11 }' $FILE > ./outputs/temperature_data.txt
                ./obj/weather_sorting -f ./outputs/temperature_data.txt -o ./outputs/temperature_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/temperature_output.csv'; graphTitle='Minimum, maximum and medium temperature by station'; graphYLabel='Temperature'; graphOutputName='./outputs/temperature_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode1.sh
            ;;

            # $2 = Dates, $7 = Temperatures
            MODE_2)
                awk -F ";" 'BEGIN{print "t2"}; NR>1 && $11 != "" { print $2 ";" $11 }' $FILE > ./outputs/temperature_data.txt
                ./obj/weather_sorting -f ./outputs/temperature_data.txt -o ./outputs/temperature_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/temperature_output.csv'; graphTitle='Temperature by date'; graphYLabel='Temperature'; graphOutputName='./outputs/temperature_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode2.sh
            ;;

            # $1 = Stations, $2 = Dates, $7 = Temperatures
            MODE_3)
                awk -F ";" 'BEGIN{print "t3"}; NR>1 && $11 != "" { print $1 ";" $2 ";" $11 }' $FILE > ./outputs/temperature_data.txt
                ./obj/weather_sorting -f ./outputs/temperature_data.txt -o ./outputs/temperature_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/temperature_output.csv'; graphTitle='Temperature by station'; graphYLabel='Temperature'; graphOutputName='./outputs/temperature_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode3.sh
            ;;
            *)
                echo "Error in -t mode option"
                exit 0
            ;;

        esac
        rm ./outputs/temperature_data.txt ./outputs/temperature_output.csv
    fi

    if [ ! -z ${PRESSIONS_MODE} ]
    then
        case $PRESSIONS_MODE in

            # $1 = Stations, $7 = Pressures
            MODE_1)
                awk -F ";" 'BEGIN{print "p1"}; NR>1 && $7 != "" { print $1 ";" $7 }' $FILE > ./outputs/pressure_data.txt
                ./obj/weather_sorting -f ./outputs/pressure_data.txt -o ./outputs/pressure_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/pressure_output.csv'; graphTitle='Minimum, maximum and medium pressure by station'; graphYLabel='Pressure'; graphOutputName='./outputs/pressure_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode1.sh
            ;;

            # $2 = Dates, $7 = Pressures
            MODE_2)
                awk -F ";" 'BEGIN{print "p2"}; NR>1 && $7 != "" { print $2 ";" $7 }' $FILE > ./outputs/pressure_data.txt
                ./obj/weather_sorting -f ./outputs/pressure_data.txt -o ./outputs/pressure_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/pressure_output.csv'; graphTitle='Pressure by date'; graphYLabel='Pressure'; graphOutputName='./outputs/pressure_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode2.sh
            ;;

            # $1 = Stations, $2 = Dates, $7 = Pressures
            MODE_3)
                awk -F ";" 'BEGIN{print "p3"}; NR>1 && $7 != "" { print $1 ";" $2 ";" $7 }' $FILE > ./outputs/pressure_data.txt
                ./obj/weather_sorting -f ./outputs/pressure_data.txt -o ./outputs/pressure_output.csv $SORTING_OPTION
                gnuplot -persist -e "graphFile='./outputs/pressure_output.csv'; graphTitle='Pressure by station'; graphYLabel='Pressure'; graphOutputName='./outputs/pressure_graph.jpg'" ./src/shell/gnuplot/gnuplot_mode3.sh
            ;;
            *)
                echo "Error in -p mode option"
                exit 0
            ;;

        esac
        rm ./outputs/pressure_data.txt ./outputs/pressure_output.csv
    fi

    if [ ! -z ${WIND} ]
    then
        # $1 = Stations, $4 = Winds direction, $5 = Winds speed, $10 = X Coordinates, $11 = Y Coordinates
        awk -F "[;,]" 'BEGIN{print "w"}; NR>1 && $4 != "" && $5 != "" { print $1 ";" $4 ";" $5 ";" $10 ";" $11 }' $FILE > ./outputs/wind_data.txt
        ./obj/weather_sorting -f ./outputs/wind_data.txt -o ./outputs/wind_output.csv $SORTING_OPTION
        gnuplot -persist ./src/shell/gnuplot/gnuplot_w.sh
        rm ./outputs/wind_data.txt ./outputs/wind_output.csv
    fi

    if [ ! -z ${HEIGHT} ]
    then
        # $1 = Stations, $15 = Height, $10 = X Coordinates, $11 = Y Coordinates
        awk -F "[;,]" 'BEGIN{print "h"}; NR>1 && $15 != "" { print $1 ";" $15 ";" $10 ";" $11 }' $FILE > ./outputs/height_data.txt
        ./obj/weather_sorting -f ./outputs/height_data.txt -o ./outputs/height_output.csv -r $SORTING_OPTION
        gnuplot -persist ./src/shell/gnuplot/gnuplot_h.sh
        rm ./outputs/height_data.txt ./outputs/height_output.csv 
    fi

    if [ ! -z ${MOISTURE} ]
    then   
        # $1 = Stations, $6 = Moisture, $10 = X Coordinates, $11 = Y Coordinates
        awk -F "[;,]" 'BEGIN{print "m"}; NR>1 && $6 != "" { print $1 ";" $6 ";" $10 ";" $11 }' $FILE > ./outputs/moisture_data.txt
        ./obj/weather_sorting -f ./outputs/moisture_data.txt -o ./outputs/moisture_output.csv -r $SORTING_OPTION
        gnuplot -persist ./src/shell/gnuplot/gnuplot_m.sh
        rm ./outputs/moisture_data.txt ./outputs/moisture_output.csv
    fi
}



