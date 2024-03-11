all: main

main: lab7.o orig_funcs.o
	gcc orig_funcs.o lab7.o -o main

lab7.o: lab7.c
	gcc -c lab7.c

orig_funcs.o: orig_funcs.c
	gcc -c orig_funcs.c

.PHONY: clean

clean: 
	rm main lab7.o orig_funcs.o
