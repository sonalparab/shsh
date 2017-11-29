all:
	gcc -o shsh main.c exec.c

run: all
	./shsh < commands.txt > output.txt
	./shsh

debug:
	gcc -o shsh -g main.c exec.c

valgrind: debug
	valgrind ./shsh --leak-check=yes

clean:
	rm shsh
	rm output.txt
