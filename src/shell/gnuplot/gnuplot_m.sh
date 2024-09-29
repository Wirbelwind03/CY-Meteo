 #!/usr/bin/gnuplot

set terminal jpeg
set output "./outputs/moisture_graph.jpg"

set datafile separator ';'

set title "Moisture"
set xlabel "Longitude"
set ylabel "Latitude" 

set view map
set pm3d
set dgrid3d
splot "./outputs/moisture_output.csv" using 2:3:1 w image notitle

