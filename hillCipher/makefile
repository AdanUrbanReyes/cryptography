run: a.out
	./a.out

a.out: algorithms.o hillCipher.o unidimensionalMatrix.o main.o
	gcc algorithms.o hillCipher.o unidimensionalMatrix.o main.o -Wall -Werror

algorithms.o: algorithms.c
	gcc -c algorithms.c -Wall -Werror

hillCipher.o: hillCipher.c
	gcc -c hillCipher.c -Wall -Werror

unidimensionalMatrix.o: unidimensionalMatrix.c
	gcc -c unidimensionalMatrix.c -Wall -Werror

main.o: main.c
	gcc -c main.c -Wall -Werror

clean:
	rm a.out *.o
