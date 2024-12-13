set terminal png size 1920,1080 enhanced background rgb 'white
set output 'experiments/ils.png'

set title 'Algorithms delays'
set xrange [0:]
set yrange [0:]
set ylabel "delay"
set xlabel "experimentations data"

plot 'experiments/ils.dat' using 1:2 smooth frequency w lines title "Swap symetric", \
'experiments/ils.dat' using 1:3 smooth frequency w lines title "Swap i and i plus 1 three times", \
'experiments/ils.dat' using 1:4 smooth frequency w lines title "Swap i and i plus 1 five times", \
'experiments/ils.dat' using 1:5 smooth frequency w lines title "Optimal solution";