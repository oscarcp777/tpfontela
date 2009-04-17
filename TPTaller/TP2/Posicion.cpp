#include "Posicion.h"
#include <iostream>

Posicion::Posicion(int posX,int posY){
	
	this->x = posX;
	this->y = posY;
}

int Posicion::getX(){

	return this->x;
}

int Posicion::getY(){

	return this->y;
}