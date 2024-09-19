set terminal png size 800,500 enhanced background rgb 'white
set output 'courbes.png'

set title 'Construct line algorithm'
set xrange [0:]
set yrange [0:]
set ylabel "operations"
set xlabel "n"

logb(x, base) = log(x)/log(base)

f(n) = n
g(n) = n * logb(n, 2)
plot 'output.dat' using 1:2 smooth bezier w lines title "tests",\
 'worst_case.dat' using 1:2 smooth bezier w lines title "worst case",\
 f(x) w lines title "n",\
 g(x) w lines title "n log_2(n)"
 