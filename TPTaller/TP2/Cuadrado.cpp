#include "Cuadrado.h"
#include <string>
#include <iostream>

Cuadrado::Cuadrado(std::string id,int l,Posicion *p){//,std::string i):Figura(i){
	this->id = id;
	this->lado = l;
	this->pos = p;
	
}
int Cuadrado::dibujar(){
	std::cout<<"se dibujo un cuadrado, id:"<<this->getId()<<"\n";
	return 0;
}
int Cuadrado::getLado(){

	return this->lado;
	
}
Posicion* Cuadrado::getPosicion(){
	return this->pos;
}

