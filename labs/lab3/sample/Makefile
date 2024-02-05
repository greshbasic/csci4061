p_fork: fork.c
	gcc -o fork fork.c
	./fork

p_wait_stat: wait_stat.c
	gcc -o wait_stat wait_stat.c
	./wait_stat

p_exec: exec.c
	gcc -o exec exec.c
	./exec

.PHONY: clean

clean:
	rm -f fork wait_stat exec
