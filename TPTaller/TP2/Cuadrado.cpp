#include "Cuadrado.h"
#include <string>
#include <iostream>
#include "Escenario.h"

Cuadrado::Cuadrado(){
}

Cuadrado::Cuadrado(std::string id,int l,Posicion *p){//,std::string i):Figura(i){
	this->id = id;
	this->lado = l;
	this->pos = p;
	
}

int Cuadrado::dibujar(SDL_Surface *screen){

	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();

	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	
	this->imagen = IMG_Load (path.begin());
	this->imagen = ScaleSurface(this->imagen, this->getLado(), this->getLado());		
	
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo	
	int x= this->getPosicion()->getX();
	int y= this->getPosicion()->getY();
	int j = 0;
	int k = 0;
	
	while(x<this->getLado()+this->getPosicion()->getX()){
		
		y=this->getPosicion()->getY();
		k=0;
		while(y<=this->getLado()+this->getPosicion()->getY()){
		
			if(imagen != NULL){
			this->color = this->getpixel(imagen,j,k);
			}
			this->putpixel(screen,x,y,this->color);
			y++;
			k++;
		}
		x++;
		j++;
	
	}
	return 0;
}

int Cuadrado::getLado(){

	return this->lado;
	
}

void Cuadrado::setLado(int lado){
	this->lado = lado;
}

Posicion* Cuadrado::getPosicion(){
	return this->pos;
}

