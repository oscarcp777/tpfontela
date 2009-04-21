#include "Cuadrado.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Cuadrado::Cuadrado(std::string id,int l,Posicion *p){//,std::string i):Figura(i){
	this->id = id;
	this->lado = l;
	this->pos = p;
	
}

int Cuadrado::dibujar(SDL_Surface *screen){
	SDL_Surface *imagen;
	SDL_Rect rect;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	imagen = IMG_Load ("pocoyo.jpg");
	
	rect.x = this->getPosicion()->getX();
	rect.y = this->getPosicion()->getY();
	rect.w = imagen->w = this->getLado();
	rect.h = imagen->h = this->getLado();
	
	SDL_BlitSurface(imagen, NULL, screen, &rect);
	return 0;
}

int Cuadrado::getLado(){

	return this->lado;
	
}
Posicion* Cuadrado::getPosicion(){
	return this->pos;
}

