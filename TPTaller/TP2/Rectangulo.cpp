#include "Rectangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
#define WALLCOLOR 0x9f1f1f
Rectangulo::Rectangulo(std::string id,int altura,int base,Posicion *p){
	this->id = id;
	this->altura = altura;
	this->base = base;
	this->pos = p;

}
int Rectangulo::dibujar(SDL_Surface *screen){

	Dibujar::dibujarRectangulo(screen,this->pos->getX(),this->pos->getY(),this->base,this->altura);
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	std::cout<<path;
	this->imagen = IMG_Load (path.begin());

	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	int x= this->getPosicion()->getX();
	int y= this->getPosicion()->getY();
	/*color.r=0x0000ff00;
	color.g=0x000000ff;
	color.b=0x00ff0000;;
	imagen = NULL;*/

	while(x<=(this->getBase()+this->getPosicion()->getX())){

		y=this->getPosicion()->getY();

		while(y<=(this->getAltura()+this->getPosicion()->getY())){
		//	std::cout<<"y "<<y<<endl;
			if(imagen != NULL){
			this->color = this->getpixel(imagen,x,y);
			}
			this->putpixel(screen,x,y,this->color);
			y++;
		}
		x++;

	}
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
