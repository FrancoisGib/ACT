set terminal png size 800,500 enhanced background rgb 'white
set output 'courbes.png'

set title 'Fusion'
set xrange [0:]
set yrange [0:]

f(n) = n
g(n) = n * (log(n)/log(2))
plot 'output.dat' using 1:2 smooth bezier w lines title "tests",\
 'worst_case.dat' using 1:2 smooth bezier w lines title "worst case",\
 f(x) w lines title "n",\
 g(x) w lines title "n log2 n"
 