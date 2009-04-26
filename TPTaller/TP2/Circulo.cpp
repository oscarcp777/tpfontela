#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Dibujar.h"
#include<math.h>


Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;
	
}

int Circulo::dibujar(SDL_Surface *screen){
	
	
	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();
	
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
         
  		for(radio = 0;radio<this->getRadio();radio+=0.4777){
			
			if(imagen!= NULL){
			this->color = this->getpixel(imagen,XiniColor,YiniColor);
			XiniColor=imagen->w/2+radio*cos(PI*ang/180);
			YiniColor=imagen->h/2+radio*sin(PI*ang/180);
			}
			this->putpixel(screen,xCirculo,yCirculo,this->color);
			
            
			xCirculo=this->getPosicion()->getX()+radio*cos(PI*ang/180);
			yCirculo=this->getPosicion()->getY()+radio*sin(PI*ang/180);		
			
		}			
		
	}
	return 0;

}
int Circulo::getRadio(){
		
	return this->radio;
	
}

Posicion* Circulo::getPosicion(){
	return this->pos;
}


