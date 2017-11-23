all:
	gcc -o shsh main.c

run: all
	./shsh

clean:
	rm shsh

test:
	gcc -o shsh -g
