#include "Posicion.h"
#include "Define.h"
#include <iostream>

Posicion::Posicion(int posX,int posY){

	this->x = posX;
	this->y = posY;
}
Posicion::~Posicion(){
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Posicion"<<std::endl;

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
