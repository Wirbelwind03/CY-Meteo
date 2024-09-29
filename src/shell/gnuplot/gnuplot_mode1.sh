 #!/usr/bin/gnuplot

set terminal jpeg
set output graphOutputName

set datafile separator ';'

set title graphTitle
set xlabel "Stations ID"
set ylabel graphYLabel

plot graphFile using 1:4:2 title "Minimum" with filledcurves fc rgb "green", \
    graphFile using 1:4:3 title "Maximum" with filledcurves fc rgb "red", \
    graphFile using 1:4 title "Medium" with lines lw 2 lt rgb "black"

