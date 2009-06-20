#include "Rectangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#define WALLCOLOR 0x9f1f1f

Rectangulo::Rectangulo(){
}
Rectangulo::~Rectangulo(){
	delete this->pos;


}

Rectangulo::Rectangulo(std::string id,int base,int altura,Posicion *p){
	this->id = id;
	this->altura= altura;
	this->base= base;
	this->pos = p;
	this->setAltoInfluencia(altura);
	this->setAnchoInfluencia(base);
	this->setXInfluencia(p->getX());
	this->setYInfluencia(p->getY());
}
int Rectangulo::getX(){
	return this->getPosicion()->getX();
}
int Rectangulo::getY(){
	return this->getPosicion()->getY();
}
int Rectangulo::dibujar(SDL_Surface *screen){

	this->color = getColorFigura()->getColor();
	 SDL_Surface* image;
		if(this->imagen==NULL){
		//si la textura no es NULL es porque le seteo algun idTextura
	    if(this->getIdTextura().compare("NULL") != 0){
		//si se le seteo algun idTextura busco el path
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());

		//si el path NO es NULL intento levantar la imagen
		if(path.compare("NULL") != 0){
			image = IMG_Load (path.begin());

			//si la imagen no es null (es decir si la levanto bien) la escalo
			if(image != NULL){
				image = ScaleSurface(image, this->getBase(), this->getAltura());
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
		image = IMG_Load (path.begin());
		if(image != NULL){
						image = ScaleSurface(image, this->getBase(), this->getAltura());
					}
	}
	    SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255,255,255));
	    		this->imagen=SDL_DisplayFormat(image);
	    		SDL_FreeSurface(image);
	    	}
	if(this->imagen!=NULL){
		SDL_Rect rect;
			   		rect.x =this->getPosicion()->getX();
			   		rect.y = this->getPosicion()->getY();
			   		SDL_BlitSurface(this->imagen, NULL, screen, &rect);
		}

//	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
//	int x= this->getPosicion()->getX();
//	int y= this->getPosicion()->getY();
//	int j = 0;
//	int k = 0;
//
//	while(x<=this->getBase()+this->getPosicion()->getX()){
//
//		//valido que la x este dentro del escenario
//		if(x>=0 && x<=Escenario::obtenerInstancia()->getAncho()){
//			y=this->getPosicion()->getY();
//			k=0;
//			while(y<=this->getAltura()+this->getPosicion()->getY()){
//
//			//valido que la y este dentro del escenario
//			if(y>=0 && y<Escenario::obtenerInstancia()->getAlto()){
//				//std::cout<<"y "<<y<<endl;
//				if(y==this->getPosicion()->getY()||y==this->getAltura()+this->getPosicion()->getY()||x==this->getBase()+this->getPosicion()->getX()||x==this->getPosicion()->getX()){
//					this->putpixel(screen,x,y,getColorLinea()->getColor());
//				}
//				else{
//					if(imagen != NULL){
//						this->color = this->getpixel(imagen,j,k);
//					}
//					this->putpixel(screen,x,y,this->color);
//				}
//			}
//
//
//			y++;
//			k++;
//			}
//		}
//	x++;
//	j++;
//
//	}
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

void Rectangulo::calcularRadioDeInfluencia(){

//		  Posicion* posicion= new Posicion(this->getX(),this->getY());
//		  this->puntosDeInfluencia.push_back(posicion);
//		  Posicion* posicion2= new Posicion(this->getX()+this->getBase(),this->getY());
//		 this->puntosDeInfluencia.push_back(posicion2);
//		  Posicion* posicion3= new Posicion(getX(),getY());
//		  this->puntosDeInfluencia.push_back(posicion3);
//		  Posicion* posicion4= new Posicion(getX(),getY());
//		 this->puntosDeInfluencia.push_back(posicion4);



//TODO

}