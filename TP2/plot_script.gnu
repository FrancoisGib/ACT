set terminal png size 800,500 enhanced background rgb 'white
set output 'courbes.png'

set title 'Memory consumption'
set xrange [0:]
set yrange [0:]
set ylabel "bytes"
set xlabel "(i, n - 1 - i)"

plot 'output.dat' using 1:2 smooth frequency w lines title "dynamic", \
'output.dat' using 1:3 smooth frequency w lines title "dynamic symetric";