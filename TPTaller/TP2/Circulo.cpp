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
	
	
	SDL_Color color;
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
	std::cout<<path;
	this->imagen = IMG_Load (path.begin());
	
	
	float ang;
	float radio;
	float PI =3.14f;
	
	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = imagen->w/2;
	int YiniColor = imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float xCirculo= this->getPosicion()->getX();
	float yCirculo= this->getPosicion()->getY();
	/*
	color.r=0x0000ff00;
	color.g=0x000000ff;
	color.b=0x00ff0000;;
	imagen = NULL;
	*/
	for(ang = 0;ang<=360;ang+=0.2){
         
  		for(radio = 1;radio<this->getRadio();radio+=0.477){
			
			if(imagen!= NULL){
			color = this->getpixel(imagen,XiniColor,YiniColor);
			XiniColor=imagen->w/2+radio*cos(PI*ang/180);
			YiniColor=imagen->h/2+radio*sin(PI*ang/180);
			}
			this->putpixel(screen,xCirculo,yCirculo,color);
			
            
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


