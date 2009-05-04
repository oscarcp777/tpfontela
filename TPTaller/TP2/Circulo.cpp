#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
#include<math.h>

Circulo::Circulo(void){

}

Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;
	
}

int Circulo::dibujar(SDL_Surface *screen){
	std::cout<<"CIRCULO "<<endl;
	std::cout<<"id: "<<this->getId()<<endl;
	std::cout<<"radio: "<<this->getRadio()<<endl;
	std::cout<<"x: "<<this->getPosicion()->getX()<<endl;
	std::cout<<"y: "<<this->getPosicion()->getY()<<endl;
	
	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();
	SDL_Color colorLinea = Escenario::obtenerInstancia()->getColorLinea();
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());

	this->imagen = IMG_Load (path.begin());
	this->imagen = ScaleSurface(this->imagen, this->getRadio()*2, this->getRadio()*2);
	
	float ang;
	float radio;
	float PI =3.141592654;
	
	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = 0;//imagen->w/2;
	int YiniColor = 0;//imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float xCirculo= this->getPosicion()->getX();
	float yCirculo= this->getPosicion()->getY();
	
	
	for(ang = 0;ang<360;ang+=0.19){
         
  		for(radio = 0;radio<=this->getRadio();radio+=0.5){
			

			if(this->getRadio()-radio <= 1|| radio > this->getRadio() ){
				this->putpixel(screen,xCirculo,yCirculo,colorLinea);
			}
			else{
				if(imagen!= NULL){
					this->color = this->getpixel(imagen,XiniColor,YiniColor);
					XiniColor=imagen->w/2+radio*cos(PI*ang/180);
					YiniColor=imagen->h/2+radio*sin(PI*ang/180);
				}
				this->putpixel(screen,xCirculo,yCirculo,this->color);
			}            
			xCirculo=this->getPosicion()->getX()+radio*cos(PI*ang/180);
			yCirculo=this->getPosicion()->getY()+radio*sin(PI*ang/180);		
			
		}			
		
	}
	return 0;

}
int Circulo::getRadio(){
		
	return this->radio;
	
}

void Circulo::setRadio(int radio){
	this->radio=radio;
}

Posicion* Circulo::getPosicion(){
	return this->pos;
}

void Circulo::setPosicion(Posicion*posicion){
	this->pos = posicion;
}

Circulo::~Circulo(){

}


