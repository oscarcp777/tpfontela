#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"



Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;
	
}

int Circulo::dibujar(SDL_Surface *screen){
	//std::cout<<"se dibujo un circulo, id:"<<this->getId()<<"\n";
	SDL_Surface *imagen;
	SDL_Rect rect;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	imagen = IMG_Load ("circulo.gif");
	
	rect.x = this->getPosicion()->getX();
	rect.y = this->getPosicion()->getY();
	rect.w = /*imagen->w; =*/ this->getRadio();
	rect.h = /*imagen->h; //= */this->getRadio();
	
	SDL_BlitSurface(imagen, NULL, screen, &rect);
	return 0;

}
int Circulo::getRadio(){
		
	return this->radio;
	
}

Posicion* Circulo::getPosicion(){
	return this->pos;
}

