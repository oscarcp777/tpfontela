#include "Circulo.h"
#include <string>
#include <iostream>



Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;
	
}

int Circulo::dibujar(){
	std::cout<<"se dibujo un circulo, id:"<<this->getId()<<"\n";
	return 0;

}
int Circulo::getRadio(){

	return this->radio;
	
}

Posicion* Circulo::getPosicion(){
	return this->pos;
}


