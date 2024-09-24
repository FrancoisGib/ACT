all: compil run plot

compil: tablet.c tablet.h lib.c lib.h main.c
	gcc -c lib.c tablet.c
	gcc -o main main.c lib.o tablet.o

run: compil main
	./main

plot: plot_script.gnu output.dat
	gnuplot plot_script.gnu

clean:
	rm *.o main