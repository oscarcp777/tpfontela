#include "Triangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Triangulo::Triangulo(std::string id,Posicion *ver1,Posicion *ver2,Posicion *ver3){
	this->id = id;
	this->vertice1 = ver1;
	this->vertice2 = ver2;
	this->vertice3 = ver3;
	
}
int Triangulo::dibujar(SDL_Surface *screen){
	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();

	this->dibujarLinea(color,screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice2()->getX(), this->getVertice2()->getY());
	this->dibujarLinea(color,screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY()); 
	this->dibujarLinea(color,screen ,this->getVertice2()->getX(),  this->getVertice2()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY());
	return 0;
}

Posicion* Triangulo::getVertice1(){
		
	return this->vertice1;
}

Posicion* Triangulo::getVertice2(){
		
	return this->vertice2;
}

Posicion* Triangulo::getVertice3(){
		
	return this->vertice3;
}