all: compil exec plot

compil: roof_line.h roof_line.c test.c
	gcc -c roof_line.c
	gcc -o main main.c roof_line.o
	gcc -o test test.c roof_line.o

exec:
	./test
	./main

clean:
	rm -rf main roof_line.o test file.html output.dat worst_case.dat

plot: plot_script.gnu worst_case.dat output.dat test
	sort -n output.dat > temp.dat
	mv temp.dat output.dat
	gnuplot plot_script.gnu