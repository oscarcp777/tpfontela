#include "Circulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"
#include "Define.h"
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
	this->imagen=NULL;
	this->setAltoInfluencia(this->radio*2);
	this->setAnchoInfluencia(this->radio*2);
	this->setXInfluencia(p->getX()-this->radio);
	this->setYInfluencia(p->getY()-this->radio);

}
int calcularDistancia(int izqX, int izqY,int derX, int derY){
	int x,y;
	int raiz=0;
	std::cout<<izqX<<izqY<<derX<<derY;
	x=abs(derX-izqX);
	y=abs(derY-izqY);
		raiz=(int)sqrt(pow(x,2)+pow(y,2));

	return raiz;
}


void Circulo::calcularRadioDeInfluencia(){
	/*####################################################################################*/
	//calculo ancho de triangulo intermedios del circulo y los agrego a lista en los angulos calculados

	/*####################################################################################*/

	int anchoTipo1=calcularDistancia((int)(getRadio()*cos(55*PI/180))+getX(),(int)(getRadio()*sin(55*PI/180))+getY(),
			(int)(getRadio()*cos(125*PI/180))+getX(), (int)(getRadio()*sin(125*PI/180))+getY());
	int altoTipo1=20;
	RectanguloInfluencia* rectanguloInfluencia= new RectanguloInfluencia(abs((int)(getRadio()*cos(55*PI/180)))+getX()
			,abs((int)(getRadio()*sin(55*PI/180)))+getY(),anchoTipo1,altoTipo1,ARRIBA);
	this->addRectanguloInfluencia(rectanguloInfluencia);

	RectanguloInfluencia* rectanguloInfluencia1= new RectanguloInfluencia(abs((int)(getRadio()*cos(145*PI/180)))+getX(),
			abs((int)(getRadio()*sin(145*PI/180)))+getY(),anchoTipo1,altoTipo1,DERECHA);
	this->addRectanguloInfluencia(rectanguloInfluencia1);
	RectanguloInfluencia* rectanguloInfluencia2= new RectanguloInfluencia(abs((int)(getRadio()*cos(235*PI/180)))+getX(),
			abs((int)(getRadio()*sin(235*PI/180))+getY()),anchoTipo1,altoTipo1,ABAJO);
	this->addRectanguloInfluencia(rectanguloInfluencia2);

	RectanguloInfluencia* rectanguloInfluencia3= new RectanguloInfluencia(abs((int)(getRadio()*cos(325*PI/180)))+getX(),
			abs((int)(getRadio()*sin(325*PI/180)))+getY(),anchoTipo1,altoTipo1,IZQUIERDA);
	this->addRectanguloInfluencia(rectanguloInfluencia3);


	/*####################################################################################*/
	//calculo ancho de triangulo pequenios del circulo y los agrego a lista en los angulos calculados

	/*####################################################################################*/
	int anchoTipo2=calcularDistancia((int)getRadio()*cos(70*PI/180)+getX(),(int)(getRadio()*sin(70*PI/180))+getY(),
		(int)(getRadio()*cos(110*PI/180))+getX(), (int)(getRadio()*sin(100*PI/180))+getY());
	int altoTipo2=10;


	RectanguloInfluencia* rectanguloInfluencia4= new RectanguloInfluencia(abs((int)(getRadio()*cos(70*PI/180)))+getX(),
			abs((int)(getRadio()*sin(70*PI/180)))+getY(),anchoTipo2,altoTipo2,ARRIBA);
	this->addRectanguloInfluencia(rectanguloInfluencia4);

	RectanguloInfluencia* rectanguloInfluencia5= new RectanguloInfluencia(abs((int)(getRadio()*cos(160*PI/180)))+getX(),
			abs((int)(getRadio()*sin(160*PI/180)))+getY(),anchoTipo2,altoTipo2,DERECHA);
	this->addRectanguloInfluencia(rectanguloInfluencia5);

	RectanguloInfluencia* rectanguloInfluencia6= new RectanguloInfluencia(abs((int)(getRadio()*cos(250*PI/180)))+getX(),
			abs((int)(getRadio()*sin(250*PI/180)))+getY(),anchoTipo2,altoTipo2,ABAJO);
	this->addRectanguloInfluencia(rectanguloInfluencia6);

	RectanguloInfluencia* rectanguloInfluencia7= new RectanguloInfluencia(abs((int)(getRadio()*cos(340*PI/180)))+getX(),
			abs((int)(getRadio()*sin(340*PI/180)))+getY(),anchoTipo2,altoTipo2,IZQUIERDA);
	this->addRectanguloInfluencia(rectanguloInfluencia7);

}
int Circulo::dibujar(SDL_Surface *screen){
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
					image = ScaleSurface(image, this->getRadio()*2, this->getRadio()*2);
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
			if( image!= NULL){
				image = ScaleSurface(image, this->getRadio()*2, this->getRadio()*2);
			}
		}
		SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255,255,255));
		this->imagen=SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
	}

	if(this->imagen!=NULL){
	   	    SDL_Rect rect;
	   		rect.x =this->getX()-this->getRadio();
	   		rect.y = this->getY()-this->getRadio();
	   		SDL_BlitSurface(this->imagen, NULL, screen, &rect);
	}
//	float ang;
//	float radio;
//
//	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
//	int XiniColor = 0;//imagen->w/2;
//	int YiniColor = 0;//imagen->h/2;
//	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
//	float xCirculo= this->getPosicion()->getX();
//	float yCirculo= this->getPosicion()->getY();
//
//
//	for(ang = 0;ang<360;ang+=0.2){
//
//		for(radio = 0;radio<=this->getRadio();radio+=0.3){
//
//
//			//valido que x e y esten dentro del escenario
//			if(xCirculo>=0 && xCirculo<Escenario::obtenerInstancia()->getAncho() && yCirculo>=0 && yCirculo<Escenario::obtenerInstancia()->getAlto()){
//
//				if(this->getRadio()-radio <= 1|| radio > this->getRadio() ){
//					this->putpixel(screen,xCirculo,yCirculo,getColorLinea()->getColor());
//				}
//				else{
//					if(imagen!= NULL){
//						this->color = this->getpixel(imagen,XiniColor,YiniColor);
//						XiniColor=imagen->w/2+radio*cos(PI*ang/180);
//						YiniColor=imagen->h/2+radio*sin(PI*ang/180);
//					}
//					this->putpixel(screen,xCirculo,yCirculo,this->color);
//				}
//
//			}
//			xCirculo=this->getPosicion()->getX()+radio*cos(PI*ang/180);
//			yCirculo=this->getPosicion()->getY()+radio*sin(PI*ang/180);
//		}
//
//	}
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

