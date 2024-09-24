compil: tablet.c tablet.h lib.c lib.h main.c
	gcc -c lib.c tablet.c
	gcc -o main main.c lib.o tablet.o

clean:
	rm *.o main