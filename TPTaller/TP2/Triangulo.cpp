#include "Triangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"

Triangulo::Triangulo(std::string id,Posicion *ver1,Posicion *ver2,Posicion *ver3){
	this->id = id;
	this->vertice1 = ver1;
	this->vertice2 = ver2;
	this->vertice3 = ver3;
	
}
int Triangulo::dibujar(SDL_Surface *screen){
	Dibujar::dibujarTriangulo(screen,this->vertice1->getX(),this->vertice1->getY(),
		this->vertice2->getX(),	this->vertice2->getY(),
		this->vertice3->getX(),this->vertice3->getY());
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