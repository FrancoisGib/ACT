set terminal png size 800,500 enhanced background rgb 'white
set output 'experiments/constructive_heuristique.png'

set title 'Algorithms delays'
set xrange [0:]
set yrange [0:]
set ylabel "delay"
set xlabel "experimentations data"

plot 'experiments/constructive_heuristique.dat' using 1:2 smooth frequency w lines title "Constructive heuristic", \
'experiments/constructive_heuristique.dat' using 1:3 smooth frequency w lines title "limit time value", \
'experiments/constructive_heuristique.dat' using 1:4 smooth frequency w lines title "weight times 1 over limit", \
'experiments/constructive_heuristique.dat' using 1:5 smooth frequency w lines title "sum delay value", \
'experiments/constructive_heuristique.dat' using 1:6 smooth frequency w lines title "weight over time value", \
'experiments/constructive_heuristique.dat' using 1:7 smooth frequency w lines title "Optimal solution";