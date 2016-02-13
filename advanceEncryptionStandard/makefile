a.out: main.o advantaceEncryptionStandard.o GF2n.o unidimensionalMatrix.o list.o
	gcc main.o advantaceEncryptionStandard.o GF2n.o unidimensionalMatrix.o list.o -Wall -Werror -lm

main.o: main.c
	gcc -c main.c -Wall -Werror
	
advantaceEncryptionStandard.o: advantaceEncryptionStandard.c
	gcc -c advantaceEncryptionStandard.c -Wall -Werror

GF2n.o: GF2n.c
	gcc -c GF2n.c -Wall -Werror -lm

unidimensionalMatrix.o: unidimensionalMatrix.c
	gcc -c unidimensionalMatrix.c -Wall -Werror 

list.o: list.c
	gcc -c list.c -Wall -Werror

clean:
	rm *.o a.out
