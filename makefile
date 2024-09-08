all: roof_line.h roof_line.c
	gcc -c roof_line.c
	gcc -o main main.c roof_line.o

clean:
	rm -rf main roof_line.o file.html