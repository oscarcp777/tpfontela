#include "Segmento.h"
#include <string>
#include <iostream>

Segmento::Segmento(std::string id,Posicion *inicio, Posicion *fin){
		this->id = id;
		this->inicio = inicio;
		this->fin = fin;
	
}

int Segmento::dibujar(SDL_Surface *screen){
	std::cout<<"se dibujo un segmento, id:"<<this->getId()<<"\n";
	return 0;
}

Posicion* Segmento::getInicio(){
	return this->inicio;
}

Posicion* Segmento::getFin(){
	return this->fin;
}