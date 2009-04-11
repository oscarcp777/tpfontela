#include <stdio.h>
#include "Escenario.h"
#include "Circulo.h"


int main(){


	Circulo *a = new Circulo(9);
	int i = 0;
	while (i<10000)
		printf("RADIO: %d\n",a->getRadio());

}