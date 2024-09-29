 #!/usr/bin/gnuplot

set terminal jpeg
set output graphOutputName

set datafile separator ';'

set title graphTitle
set xlabel "Stations ID"
set ylabel graphYLabel

plot graphFile
