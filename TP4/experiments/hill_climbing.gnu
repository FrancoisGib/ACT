set terminal png size 1920,1080 enhanced background rgb 'white
set output 'experiments/hill_climbing.png'

set title 'Hill climbing heuristics delays'
set xrange [0:]
set yrange [0:]
set ylabel "delay"
set xlabel "experimentations data"

plot 'experiments/hill_climbing.dat' using 1:2 smooth frequency w lines title "swap symetric", \
'experiments/hill_climbing.dat' using 1:3 smooth frequency w lines title "swap i and middle", \
'experiments/hill_climbing.dat' using 1:4 smooth frequency w lines title "swap i and i plus nb processes div 2", \
'experiments/hill_climbing.dat' using 1:5 smooth frequency w lines title "swap i and i plus 1", \
'experiments/hill_climbing.dat' using 1:6 smooth frequency w lines title "swap pseudo random", \
'experiments/hill_climbing.dat' using 1:7 smooth frequency w lines title "shift left", \
'experiments/hill_climbing.dat' using 1:8 smooth frequency w lines title "shift right", \
'experiments/hill_climbing.dat' using 1:9 smooth frequency w lines title "swap sub list nb processes per 4", \
'experiments/hill_climbing.dat' using 1:10 smooth frequency w lines title "swap random nb processes per 4", \
'experiments/hill_climbing.dat' using 1:11 smooth frequency w lines title "shift left lasts i", \
'experiments/hill_climbing.dat' using 1:12 smooth frequency w lines title "swap sub list", \
'experiments/hill_climbing.dat' using 1:13 smooth frequency w lines title "swap i and i plus 1 three times", \
'experiments/hill_climbing.dat' using 1:14 smooth frequency w lines title "swap i and i plus 1 five times", \
'experiments/hill_climbing.dat' using 1:15 smooth frequency w lines title "Optimal solution";