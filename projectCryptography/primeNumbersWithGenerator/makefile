run: a.out
	./a.out $(li) $(ls) $(as)

a.out: main.o primeNumbersWithGenerator.o list.o
	gcc main.o primeNumbersWithGenerator.o list.o -lm -Wall -Werror

main.o: main.c
	gcc -c main.c -Wall -Werror

primeNumbersWithGenerator.o: primeNumbersWithGenerator.c
	gcc -c primeNumbersWithGenerator.c -lm -Wall -Werror

list.o: list.c
	gcc -c list.c -Wall -Werror

clean:
	rm *.o a.out

help:
	echo ejecuta como make ls=limiteInferiorElejido ls=limiteSuperiorElejido as=pathArchivoSalida
