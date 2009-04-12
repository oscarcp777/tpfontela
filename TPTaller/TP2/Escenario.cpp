#include <stdio.h>
#include "Escenario.h"
#include "Circulo.h"


int main_old(){

	//std::string id = "esElCirculo";
	Posicion *pos = new Posicion(9,10);
	Circulo *a = new Circulo(100,pos);
	int i = 0;
	while (i<10000)
		std::cout<<a->getRadio()<<endl;
		
	
	

return 0;
}