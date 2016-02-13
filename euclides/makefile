run: a.out
	./a.out

a.out: main.o modularArithmetic.o
	gcc main.o modularArithmetic.o -Wall -Werror

main.o: main.c
	gcc -c main.c -Wall -Werror

modularArithmetic.o: modularArithmetic.c
	gcc -c modularArithmetic.c -Wall -Werror

clean:
	rm *.o a.out
