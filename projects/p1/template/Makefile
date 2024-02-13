# TODO: Complete the Makefile
main: main.o graph.o
	gcc -g -o depGraph main.o graph.o

graph.o: graph.c graph.h
	gcc -c graph.c graph.h

main.o: main.c main.h
	gcc -c main.c main.h

.PHONY: clean

run1: main
	@echo sequential:
	./depGraph ../testcases/input1.txt
	@echo -----------------------------------------

	@echo parallel:
	./depGraph -p ../testcases/input1.txt

run2: main
	@echo sequential:
	./depGraph ../testcases/input2.txt
	@echo -----------------------------------------

	@echo parallel:
	./depGraph -p ../testcases/input2.txt

run3: main
	@echo sequential:
	./depGraph ../testcases/input3.txt
	@echo -----------------------------------------

	@echo parallel:
	./depGraph -p ../testcases/input3.txt

run4: main
	@echo sequential:
	./depGraph ../testcases/input4.txt
	@echo -----------------------------------------

	@echo parallel:
	./depGraph -p ../testcases/input4.txt

run5: main
	@echo sequential:
	./depGraph ../testcases/input5.txt
	@echo -----------------------------------------

	@echo parallel:
	./depGraph -p ../testcases/input5.txt



valgrind: main
	valgrind ./depGraph ../testcases/input1.txt

clean : 
	rm *.o
	rm *.h.gch
	rm results.txt
	touch results.txt