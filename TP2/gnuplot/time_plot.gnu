set terminal png size 800,500 enhanced background rgb 'white
set output './images/cpu_time_consumption.png'

set title 'CPU time consumption'
set xrange [0:]
set yrange [0:]
set ylabel "seconds"
set xlabel "(i, n - 1 - i)"

plot 'gnuplot/time.dat' using 1:2 smooth frequency w lines title "dynamic time", \
'gnuplot/time.dat' using 1:3 smooth frequency w lines title "dynamic symetric time", \
'gnuplot/time.dat' using 1:4 smooth frequency w lines title "hashmap time";