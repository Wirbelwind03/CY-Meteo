 #!/usr/bin/gnuplot

set terminal jpeg
set output "./outputs/height_graph.jpg"

set datafile separator ';'

set title "Interpolation map of heights"
set xlabel "Longitude"
set ylabel "Latitude" 

set palette rgb 33,13,10
set view map
set pm3d
set dgrid3d
splot "./outputs/height_output.csv" using 2:3:1 w image notitle