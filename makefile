all: ex2.h ex2.c
	gcc -c ex2.c
	gcc -o main main.c ex2.o