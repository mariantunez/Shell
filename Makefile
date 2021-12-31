  
all: shell

shell: shell.c game.c game.h
	gcc -g shell.c game.c -o shell

run: shell
	./shell

valgrind: shell
	valgrind --leak-check=full -s ./shell

clean:
	rm -rf shell