run: a.out
	./a.out

a.out: main.o list.o
	gcc main.o list.o -Wall -Werror -lm

main.o: main.c
	gcc -c main.c -Wall -Werror -lm

list.o: list.c
	gcc -c list.c -Wall -Werror

clean:
	rm *.o a.out
