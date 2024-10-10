all: compil run

compil: tablet.c tablet.h lib.c lib.h main.c
	gcc -c lib.c tablet.c
	gcc -o main main.c lib.o tablet.o
	gcc -o experiments experiments.c lib.o tablet.o

run: compil main
	./main

experiments: compil
	./experiments

plot: experiments gnuplot/memory_plot.gnu gnuplot/time_plot.gnu gnuplot/time.dat gnuplot/memory.dat
	gnuplot gnuplot/memory_plot.gnu
	gnuplot gnuplot/time_plot.gnu

clean:
	rm -f *.o main experiments gnuplot/*.dat