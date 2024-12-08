set terminal png size 800,500 enhanced background rgb 'white
set output 'experiments/delay.png'

set title 'Algorithms delays'
set xrange [0:]
set yrange [0:]
set ylabel "delay"
set xlabel "experimentations data"

plot 'experiments/delay.dat' using 1:2 smooth frequency w lines title "Constructive heuristic", \
'experiments/delay.dat' using 1:3 smooth frequency w lines title "Hill climbing", \
'experiments/delay.dat' using 1:4 smooth frequency w lines title "VND", \
'experiments/delay.dat' using 1:5 smooth frequency w lines title "Optimal solution";