 #!/usr/bin/gnuplot

set terminal jpeg
set output graphOutputName

set datafile separator ';'

set title graphTitle
set xlabel "Dates"
set ylabel graphYLabel

plot graphFile using 1:2 w lines title "Medium"