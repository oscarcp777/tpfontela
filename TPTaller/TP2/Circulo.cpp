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
	
	
	float ang;
	float radio;
	float PI =3.14f;
	
	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = 0;//imagen->w/2;
	int YiniColor = 0;//imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float xCirculo= this->getPosicion()->getX();
	float yCirculo= this->getPosicion()->getY();
	
	/*
	TODO
	imagen = NULL;
	*/
	
	for(ang = 0;ang<=360;ang+=0.2){
         
  		for(radio = 1;radio<this->getRadio();radio+=0.477){
			
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


