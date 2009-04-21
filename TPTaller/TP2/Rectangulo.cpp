#include "Rectangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Rectangulo::Rectangulo(std::string id,int altura,int base,Posicion *p){
	this->id = id;
	this->altura = altura;
	this->base = base;
	this->pos = p;
	
}
int Rectangulo::dibujar(SDL_Surface *screen){
	SDL_Surface *imagen;
	SDL_Rect rect;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	imagen = IMG_Load ("pocoyo2.jpg");
	
	rect.x = this->getPosicion()->getX();
	rect.y = this->getPosicion()->getY();
	rect.w = imagen->w = this->getBase();
	rect.h = imagen->h = this->getAltura();
	
	SDL_BlitSurface(imagen, NULL, screen, &rect);
	return 0;
}
int Rectangulo::getAltura(){

	return this->altura;
	
}
int Rectangulo::getBase(){

	return this->base;
	
}
Posicion* Rectangulo::getPosicion(){
	return this->pos;
}