#include "Rectangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
#define WALLCOLOR 0x9f1f1f

Rectangulo::Rectangulo(){
}
Rectangulo::~Rectangulo(){
	delete this->pos;
	 std::cout << "Destructor de Rectangulo\n";
}

Rectangulo::Rectangulo(std::string id,int base,int altura,Posicion *p){
	this->id = id;
	this->altura = altura;
	this->base = base;
	this->pos = p;
	
}
int Rectangulo::dibujar(SDL_Surface *screen){

	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();
	SDL_Color colorLinea = Escenario::obtenerInstancia()->getColorLinea();

	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	
	this->imagen = IMG_Load (path.begin());
	this->imagen = ScaleSurface(this->imagen, this->getBase(), this->getAltura());		


	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo	
	int x= this->getPosicion()->getX();
	int y= this->getPosicion()->getY();
	int j = 0;
	int k = 0;
	
	while(x<=this->getBase()+this->getPosicion()->getX()){
		
		y=this->getPosicion()->getY();
		k=0;
		while(y<=this->getAltura()+this->getPosicion()->getY()){
		
			if(y==this->getPosicion()->getY()||y==this->getAltura()+this->getPosicion()->getY()||x==this->getBase()+this->getPosicion()->getX()||x==this->getPosicion()->getX()){
				this->putpixel(screen,x,y,colorLinea);
			}
			else{
				if(imagen != NULL){
					this->color = this->getpixel(imagen,j,k);
				}
				this->putpixel(screen,x,y,this->color);
			}
			y++;
			k++;
		}
		x++;
		j++;
	
	}
	return 0;
}
int Rectangulo::getAltura(){

	return this->altura;
	
}
int Rectangulo::getBase(){

	return this->base;
	
}

void Rectangulo::setBase(int base){
	this->base = base;
}


void Rectangulo::setAltura(int altura){
	this->altura = altura;
}

Posicion* Rectangulo::getPosicion(){
	return this->pos;
}

void Rectangulo::setPosicion(Posicion *posicion){
	this->pos = posicion;
}
