#include "Cuadrado.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
Cuadrado::Cuadrado(std::string id,int l,Posicion *p){//,std::string i):Figura(i){
	this->id = id;
	this->lado = l;
	this->pos = p;

}

int Cuadrado::dibujar(SDL_Surface *screen){

	Dibujar::dibujarRectangulo(screen,this->pos->getX(),this->pos->getY(),this->lado,this->lado);
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

	while(x<=(this->getLado()+this->getPosicion()->getX())){

		y=this->getPosicion()->getY();

		while(y<=(this->getLado()+this->getPosicion()->getY())){
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

int Cuadrado::getLado(){

	return this->lado;

}
Posicion* Cuadrado::getPosicion(){
	return this->pos;
}

