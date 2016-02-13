run: a.out
	./a.out

a.out: main.o GF2n.o
	gcc main.o GF2n.o -Wall -Werror -lm

main.o: main.c
	gcc -c main.c -Wall -Werror

GF2n.o: GF2n.c
	gcc -c GF2n.c -Wall -Werror -lm

clean:
	rm *.o a.out
