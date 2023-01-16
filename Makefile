all: init getty shell

init: init.c
	gcc init.c -o init

getty: getty.c
	gcc getty.c -o getty

shell: shell.c
	gcc shell.c -o shell
