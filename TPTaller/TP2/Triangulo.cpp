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
	
	SDL_Surface *imagen;
	SDL_Rect rect;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	imagen = IMG_Load ("pocoyo4.jpg");
	
	rect.x = this->getVertice1()->getX();
	rect.y = this->getVertice1()->getY();
	rect.w = imagen->w; //= this->getRadio();
	rect.h = imagen->h; //= this->getRadio();
	

	SDL_BlitSurface(imagen, NULL, screen, &rect);
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