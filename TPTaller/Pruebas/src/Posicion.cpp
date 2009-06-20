#include "Posicion.h"
#include <iostream>

Posicion::Posicion(int posX,int posY){

	this->x = posX;
	this->y = posY;
}
Posicion::~Posicion(){
	
}
int Posicion::getX(){

	return this->x;
}

int Posicion::getY(){

	return this->y;
}

void Posicion::setX(int x){
	this->x = x;

}
void Posicion::setY(int y){
	this->y = y;
}
