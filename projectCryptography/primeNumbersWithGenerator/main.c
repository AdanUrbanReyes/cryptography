#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "primeNumbersWithGenerator.h"
int main(int ari,char **arc){
	if(ari<3){
		printf("Error ejecute como %s limiteInferior limiteSuperior\n\tDonde\nlimiteInferior corresponde al numero entero positivo mas chico apartir del cual quiere los numeros primos\nlimiteSuperior corresponde al numero entero positivo mas grande (tope) del cual quiere los numeros primos\n\n NOTA: el rango para ambos numeros es de 0 - 2^ ademas que se deven ingresar en formato decimal (base 10)\n",arc[0]);
		return -1;
	}
	uint64_t u,l;//upper limite, lower limit
	//uint64_t u=0xffffffffffffffff,l=2;//upper limite, lower limit
	sscanf(arc[1],"%" PRIx64,&l);
	sscanf(arc[2],"%" PRIx64,&u);
	printf("%"PRIx64"\n",l);
	printf("%"PRIx64"\n",u);
	if(l>u){
		printf("Error el limite inferior no puede ser mayor que el limite superior\n");
		return -3;
	}
	primeNumbersWithGenerator(l,u,arc[3]);
	return 0;
}
