#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
#define BLANCO 0xEFFBF5

Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;
	
}

int Circulo::dibujar(SDL_Surface *screen){
	/*/std::cout<<"se dibujo un circulo, id:"<<this->getId()<<"\n";
	SDL_Surface *imagen;
	SDL_Rect rect;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	imagen = IMG_Load ("circulo.png");
	
	rect.x = this->getPosicion()->getX();
	rect.y = this->getPosicion()->getY();
	rect.w = /*imagen->w; = this->getRadio();
	rect.h = /*imagen->h; //= this->getRadio();
	
	SDL_BlitSurface(imagen, NULL, screen, &rect);*/
	Dibujar *dibujar =Dibujar::obtenerInstancia();
	dibujar->dibujarCirculo(this->getPosicion()->getX(),this->getPosicion()->getY(),this->radio,BLANCO);
	return 0;

}
int Circulo::getRadio(){
		
	return this->radio;
	
}

Posicion* Circulo::getPosicion(){
	return this->pos;
}


