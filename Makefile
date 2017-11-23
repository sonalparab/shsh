all:
	gcc -o shsh main.c

run: all
	./shsh

clean:
	rm shsh

debug:
	gcc -o shsh -g main.c

valgrind: debug
	valgrind ./shsh --leak-check=yes
