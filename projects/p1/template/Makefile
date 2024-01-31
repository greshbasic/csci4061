# TODO: Complete the Makefile
main: main.o graph.o
	gcc -o main main.o graph.o

graph.o: graph.c graph.h
	gcc -c graph.c graph.h

main.o: main.c main.h
	gcc -c main.c main.h

.PHONY: clean

clean : 
	rm *.o