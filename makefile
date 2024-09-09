all: roof_line.h roof_line.c test.c
	gcc -c roof_line.c
	gcc -o main main.c roof_line.o
	gcc -o test test.c roof_line.o

clean:
	rm -rf main roof_line.o test file.html