 #!/usr/bin/gnuplot

set terminal jpeg
set output "./outputs/wind_graph.jpg"

set datafile separator ';'

set title "Wind"
set xlabel "Longitude"
set ylabel "Latitude" 

plot "./outputs/wind_output.csv" using 3:4:1:2 with vectors

