# TODO: Complete the Makefile
main: main.o graph.o
	gcc -o depGraph main.o graph.o

graph.o: graph.c graph.h
	gcc -c graph.c graph.h

main.o: main.c main.h
	gcc -c main.c main.h

.PHONY: clean

run1: main
	./depGraph ../testcases/input1.txt

run2: main
	./depGraph ../testcases/input2.txt

run3: main
	./depGraph ../testcases/input3.txt

run4: main
	./depGraph ../testcases/input4.txt

run5: main
	./depGraph ../testcases/input5.txt

clean : 
	rm *.o
	rm *.h.gch