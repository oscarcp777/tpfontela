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
	double x,y;
	int raiz=0;
	x=(double)derX-izqX;
	y=(double)derY-izqY;
	if(x>=0&&y>=0){
		raiz=(int)sqrt(pow(x,2)+pow(y,2));
	}
	return raiz;
}


void Circulo::calcularRadioDeInfluencia(){
	/*####################################################################################*/
	//calculo ancho de triangulo intermedios del circulo y los agrego a lista en los angulos calculados

	/*####################################################################################*/
	int anchoTipo1=calcularDistancia((int)getRadio()*cos(55*PI/180)+getX(),(int)getRadio()*sin(55*PI/180)+getY(),
			(int)getRadio()*cos(125*PI/180)+getX(), (int)getRadio()*sin(125*PI/180)+getY());
	int altoTipo1=20;
	SDL_Rect rectangulo ;
	rectangulo.x=(int)getRadio()*cos(55*PI/180)+getX();
	rectangulo.y=(int)getRadio()*sin(55*PI/180)+getY();
	rectangulo.w=anchoTipo1;
	rectangulo.h=altoTipo1;
	RectanguloInfluencia* rectanguloInfluencia= new RectanguloInfluencia(rectangulo,ARRIBA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia);
	SDL_Rect rectangulo1;
	rectangulo1.x=(int)getRadio()*cos(145*PI/180)+getX();
	rectangulo1.y=(int)getRadio()*sin(145*PI/180)+getY();
	rectangulo1.w=anchoTipo1;
	rectangulo1.h=altoTipo1;
	RectanguloInfluencia* rectanguloInfluencia1= new RectanguloInfluencia(rectangulo1,DERECHA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia1);
	SDL_Rect rectangulo2;
	rectangulo2.x=(int)getRadio()*cos(235*PI/180)+getX();
	rectangulo2.y=(int)getRadio()*sin(235*PI/180)+getY();
	rectangulo2.w=anchoTipo1;
	rectangulo2.h=altoTipo1;
	RectanguloInfluencia* rectanguloInfluencia2= new RectanguloInfluencia(rectangulo2,ABAJO);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia2);
	SDL_Rect rectangulo3;
	rectangulo3.x=(int)getRadio()*cos(325*PI/180)+getX();
	rectangulo3.y=(int)getRadio()*sin(325*PI/180)+getY();
	rectangulo3.w=anchoTipo1;
	rectangulo3.h=altoTipo1;
	RectanguloInfluencia* rectanguloInfluencia3= new RectanguloInfluencia(rectangulo3,IZQUIERDA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia3);


	/*####################################################################################*/
	//calculo ancho de triangulo pequenios del circulo y los agrego a lista en los angulos calculados

	/*####################################################################################*/
	int anchoTipo2=calcularDistancia((int)getRadio()*cos(70*PI/180)+getX(),(int)getRadio()*sin(70*PI/180)+getY(),
			(int)getRadio()*cos(110*PI/180)+getX(), (int)getRadio()*sin(100*PI/180)+getY());
	int altoTipo2=10;



	SDL_Rect rectangulo4;
	rectangulo4.x=(int)getRadio()*cos(70*PI/180)+getX();
	rectangulo4.y=(int)getRadio()*sin(70*PI/180)+getY();
	rectangulo4.w=anchoTipo2;
	rectangulo4.h=altoTipo2;
	RectanguloInfluencia* rectanguloInfluencia4= new RectanguloInfluencia(rectangulo4,ARRIBA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia4);
	SDL_Rect rectangulo5;
	rectangulo5.x=(int)getRadio()*cos(160*PI/180)+getX();
	rectangulo5.y=(int)getRadio()*sin(160*PI/180)+getY();
	rectangulo5.w=anchoTipo2;
	rectangulo5.h=altoTipo2;
	RectanguloInfluencia* rectanguloInfluencia5= new RectanguloInfluencia(rectangulo5,DERECHA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia5);
	SDL_Rect rectangulo6;
	rectangulo6.x=(int)getRadio()*cos(250*PI/180)+getX();
	rectangulo6.y=(int)getRadio()*sin(250*PI/180)+getY();
	rectangulo6.w=anchoTipo2;
	rectangulo6.h=altoTipo2;
	RectanguloInfluencia* rectanguloInfluencia6= new RectanguloInfluencia(rectangulo6,ABAJO);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia6);
	SDL_Rect rectangulo7;
	rectangulo7.x=(int)getRadio()*cos(240*PI/180)+getX();
	rectangulo7.y=(int)getRadio()*sin(340*PI/180)+getY();
	rectangulo7.w=anchoTipo2;
	rectangulo.h=altoTipo2;
	RectanguloInfluencia* rectanguloInfluencia7= new RectanguloInfluencia(rectangulo7,IZQUIERDA);
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia7);

}
int Circulo::dibujar(SDL_Surface *screen){
	calcularRadioDeInfluencia();
	this->color = getColorFigura()->getColor();

	if(this->imagen==NULL){
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
	}
	//   SDL_SetColorKey(this->imagen,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(this->imagen->format,255,255,255));
	//   	this->imagen=SDL_DisplayFormat(this->imagen);
	//
	//   	    SDL_Rect rect;
	//   		rect.x =this->getPosicion()->getX();
	//   		rect.y = this->getPosicion()->getY();
	//   		SDL_BlitSurface(this->imagen, NULL, screen, &rect);

	float ang;
	float radio;

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

