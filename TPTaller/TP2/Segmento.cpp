#include "Segmento.h"

Segmento::Segmento(Posicion *inicio, Posicion *fin){
		this->inicio = inicio;
		this->fin = fin;
	
}

int Segmento::dibujar(){
	std::cout<<"se dibujo un segmento \n";
	return 0;
}

Posicion* Segmento::getInicio(){
	return this->inicio;
}

Posicion* Segmento::getFin(){
	return this->fin;
}