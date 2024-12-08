set terminal png size 800,500 enhanced background rgb 'white
set output 'experiments/ratio.png'

set title 'Algorithms ratio'
set xrange [0:21]
set yrange [0:5]
set ylabel "ratio"
set xlabel "experimentations data"

plot 'experiments/ratio.dat' using 1:2 smooth frequency w lines title "Constructive heuristic", \
'experiments/ratio.dat' using 1:3 smooth frequency w lines title "Hill climbing", \
'experiments/ratio.dat' using 1:4 smooth frequency w lines title "VND", \
'experiments/ratio.dat' using 1:5 smooth frequency w lines title "Optimal solution";