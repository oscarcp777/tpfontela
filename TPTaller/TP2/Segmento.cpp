#include "Segmento.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Segmento::Segmento(std::string id,Posicion *inicio, Posicion *fin){
		this->id = id;
		this->inicio = inicio;
		this->fin = fin;

}
Segmento::~Segmento(){
	delete this->inicio;
	delete this->fin;
    std::cout << "Destructor de Segmento\n";
}
int Segmento::dibujar(SDL_Surface *screen){
	this->color = Escenario::obtenerInstancia()->getColorLinea();

	this->dibujarLinea(color,screen ,this->getInicio()->getX(),  this->getInicio()->getY(), this->getFin()->getX(), this->getFin()->getY());

	return 0;
}

Posicion* Segmento::getInicio(){
	return this->inicio;
}

Posicion* Segmento::getFin(){
	return this->fin;
}
