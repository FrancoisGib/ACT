set terminal png size 800,500 enhanced background rgb 'white
set output 'courbes.png'

set title 'Construct line algorithm'
set xrange [0:]
set yrange [0:]
set ylabel "allocations"
set xlabel "(i, n - 1 - i)"

logb(x, base) = log(x)/log(base)

plot 'output.dat' using 1:2 smooth bezier w lines title "dynamic", \
'output.dat' using 1:3 smooth bezier w lines title "memory symetric", \
'output.dat' using 1:4 smooth bezier w lines title "dynamic symetric", \
'output.dat' using 1:5 smooth bezier w lines title "memory dynamic symetric";