#include "Segmento.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Segmento::Segmento(std::string id,Posicion *inicio, Posicion *fin){
		this->id = id;
		this->inicio = inicio;
		this->fin = fin;
	
}

int Segmento::dibujar(SDL_Surface *screen){
	std::cout<<"SEGMENTO "<<endl;
	std::cout<<"id: "<<this->getId()<<endl;
	std::cout<<"inicio x: "<<this->getInicio()->getX()<<endl;
	std::cout<<"inicio y: "<<this->getInicio()->getY()<<endl;
	std::cout<<"fin x: "<<this->getFin()->getX()<<endl;
	std::cout<<"fin y: "<<this->getFin()->getY()<<endl;
	

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