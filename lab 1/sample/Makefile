p1.o: p1.c
	gcc -c p1.c
p1.out: p1.o
	gcc -o p1.out p1.o

run: p1.out
	./p1.out

.PHONY: clean
clean:
	rm p1.o p1.out