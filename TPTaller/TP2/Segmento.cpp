#include "Segmento.h"
#include <string>
#include <iostream>

Segmento::Segmento(std::string id,Posicion *inicio, Posicion *fin){
		this->id = id;
		this->inicio = inicio;
		this->fin = fin;
	
}

int Segmento::dibujar(SDL_Surface *screen){
	
	return 0;
}

Posicion* Segmento::getInicio(){
	return this->inicio;
}

Posicion* Segmento::getFin(){
	return this->fin;
}