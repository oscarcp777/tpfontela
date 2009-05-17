#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include<math.h>

Circulo::Circulo(void){

}
Circulo::~Circulo(){
    delete this->pos;
    
}
Circulo::Circulo(std::string id,int r,Posicion *p){
	this->id = id;
	this->radio = r;
	this->pos = p;

}

int Circulo::dibujar(SDL_Surface *screen){
	
	this->color = getColorFigura()->getColor();
	
	
	//si la textura no es NULL es porque le seteo algun idTextura
	if(this->getIdTextura().compare("NULL") != 0){
		//si se le seteo algun idTextura busco el path
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());
		
		//si el path NO es NULL intento levantar la imagen
		if(path.compare("NULL") != 0){		
			this->imagen = IMG_Load (path.begin());
			
			//si la imagen no es null (es decir si la levanto bien) la escalo
			if(this->imagen != NULL){			
				this->imagen = ScaleSurface(this->imagen, this->getRadio()*2, this->getRadio()*2);
			}
			//si no la levanto es porque el path no es correcto o la imagen no existe
			else{
				escribirMensajeLog(*Escenario::obtenerInstancia()->getLog(),"error al intentar cargar la imagen: "+path);
			}	
		
		
		}
		//si el path ES null, tiro error (no existe path para dicho idTextura)
		else{
			escribirMensajeLog(*Escenario::obtenerInstancia()->getLog(),"no se encontro el path correspondiente al idTextura: "+this->getIdTextura());
		}

	}
	//si el idTextura es NULL intento levantar la imagen del escenario por default
	else{
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(Escenario::obtenerInstancia()->getTexturaFig());
		this->imagen = IMG_Load (path.begin());
		this->imagen = ScaleSurface(this->imagen, this->getRadio()*2, this->getRadio()*2);
	
	}
	

	float ang;
	float radio;
	float PI =3.141592654;

	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = 0;//imagen->w/2;
	int YiniColor = 0;//imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float xCirculo= this->getPosicion()->getX();
	float yCirculo= this->getPosicion()->getY();


	for(ang = 0;ang<360;ang+=0.2){

  		for(radio = 0;radio<=this->getRadio();radio+=0.3){

			
		   //valido que x e y esten dentro del escenario
		if(xCirculo>=0 && xCirculo<Escenario::obtenerInstancia()->getAncho() && yCirculo>=0 && yCirculo<Escenario::obtenerInstancia()->getAlto()){	

			if(this->getRadio()-radio <= 1|| radio > this->getRadio() ){
				this->putpixel(screen,xCirculo,yCirculo,getColorLinea()->getColor());
			}
			else{
				if(imagen!= NULL){
					this->color = this->getpixel(imagen,XiniColor,YiniColor);
					XiniColor=imagen->w/2+radio*cos(PI*ang/180);
					YiniColor=imagen->h/2+radio*sin(PI*ang/180);
				}
				this->putpixel(screen,xCirculo,yCirculo,this->color);
			}
			
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




