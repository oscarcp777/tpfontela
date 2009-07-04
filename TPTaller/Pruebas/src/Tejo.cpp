/*
 * Tejo.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Tejo.h"
#include "Circulo.h"
#include <math.h>
#include "Escenario.h"
#include "Define.h"
Tejo::Tejo() {
	// TODO Auto-generated constructor stub

}
Recta* Tejo::getRectaDireccion(){

	return new Recta(this->getX(),this->getXSiguiente(this->getX()),this->getY(),this->getYSiguiente(this->getY()));

}

bool Tejo::getChocoFiguraConBonus()
   {
       return chocoFiguraConBonus;
   }
void Tejo::volverEstadoInicial(){
	if(this->getRadio()!=this->getRadioDefault()){
	this->setRadio(this->getRadioDefault());
	this->imagen=this->imagenAuxiliar;
	}
	this->setVelocidad(this->getVelocidadDefault());
}
void Tejo::setChocoFiguraConBonus(bool chocoFiguraConBonus)
   {
       this->chocoFiguraConBonus = chocoFiguraConBonus;
   }
Circulo* Tejo::getFigura(){
	return	this->circulo;
}
bool Tejo::getChoco()
    {
        return choco;
    }

    void Tejo::setChoco(bool choco)
    {
        this->choco = choco;
    }

Tejo::Tejo(Circulo* circulo){
	this->circulo=circulo;
	std::cout<< "padv1: "  <<this->circulo->getIdTextura()<< endl;
	this->imagen=NULL;
	this->imagenAuxiliar=NULL;
	this->choco=false;
	this->direccion = new Direccion();
	this->modificarRadio=false;
	this->ultimaColisionPad = PAD_CLIENTE2;
	this->mover= true;
	this->pegajoso=false;
	this->chocoFiguraConBonus=false;

}
SDL_Surface* Tejo::getImagen()
    {
        return this->imagen;
    }
void Tejo::setImagen(SDL_Surface *imagen){

	this->imagen = imagen;
}


void Tejo::setRadioDefault(int radioDefault){
	this->radioDefault = radioDefault;
}

int Tejo::getRadioDefault(){
	return this->radioDefault;
}

void Tejo::cargarRadioDeInfluencia(){


	for(int i=0;i<8;i++){
		double angulo=i*PI/4;
		Posicion* posicion= new Posicion((int)getRadio()*cos(angulo)+getX(),(int)getRadio()*sin(angulo)+getY());
		this->puntosDeInfluencia.push_back(posicion);
		//	  	std::cout<<"puntos de influencia "<<"("<<posicion->getX()<<","<<posicion->getY()<<")"<<"iter"<<angulo<<endl;
		//		system("PAUSE");
	}
}
std::vector<Posicion*> Tejo::getPuntosDeInfluencia()
{
	return puntosDeInfluencia;
}

void Tejo::setPuntosDeInfluencia(std::vector<Posicion*> puntosDeInfluencia)
{
	this->puntosDeInfluencia = puntosDeInfluencia;
}
void Tejo::borrarTejo(){
	Escenario* escenario=Escenario::obtenerInstancia();
	SDL_Rect rectangulo;
	rectangulo.x=this->getXAnterior()-this->getRadio();
	rectangulo.y=this->getYAnterior()-this->getRadio();
	rectangulo.w=this->getFigura()->getRadio()*2;
	rectangulo.h=this->getFigura()->getRadio()*2;

	SDL_FillRect(escenario->getScreen(),&rectangulo,SDL_MapRGB(escenario->getScreen()->format,87,122,18));
	//	SDL_UpdateRect(escenario->getScreen(),this->getXAnterior()-this->getRadio(),this->getYAnterior()-this->getRadio(), this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
}

int Tejo::getVelocidad()
{
	return velocidad;
}

void Tejo::setVelocidad(int velocidad)
{
	this->velocidad = velocidad;
}
void Tejo::dibujar(SDL_Surface *pantalla){
    SDL_Surface* image;

	//	 Cargamos la imagen
	if(this->imagen==NULL){
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->circulo->getIdTextura());
		image = IMG_Load(path.begin());
		this->imagenGrande = IMG_Load(path.begin());
		this->imagenChica = IMG_Load(path.begin());
		//			this->imagen = SDL_LoadBMP(path.begin());
		if(image == NULL) {
			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);
		}
		//si la imagen no es null (es decir si la levanto bien) la escalo
		if(image != NULL){
			image = this->getFigura()->ScaleSurface(image, this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);

		}
		//			// Calculamos el color transparente, en nuestro caso el verde
		SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255 ,255, 255));
		this->imagen = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
		this->imagenAuxiliar=this->imagen;

	}

	if(this->modificarRadio){
		if(this->radioDefault<this->getRadio()){
		this->imagenGrande = Figura::ScaleSurface(this->imagenGrande, this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
		SDL_SetColorKey(this->imagenGrande,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(this->imagenGrande->format,255 ,255, 255));
		this->imagen = SDL_DisplayFormat(this->imagenGrande);
		}else{
			this->imagenChica = Figura::ScaleSurface(this->imagenChica, this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
			SDL_SetColorKey(this->imagenChica,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(this->imagenChica->format,255 ,255, 255));
			this->imagen = SDL_DisplayFormat(this->imagenChica);
		}
		this->modificarRadio=false;
	}
	SDL_Rect rect;
	rect.x =this->getX()-this->getRadio();
	rect.y = this->getY()-this->getRadio();

	SDL_BlitSurface(this->imagen, NULL, pantalla, &rect);


}
Tejo::~Tejo() {

	delete direccion;
	delete circulo;
	SDL_FreeSurface(this->imagen);
	SDL_FreeSurface(this->imagenAuxiliar);
   if(DEBUG_DESTRUCTOR==1)
	std::cout<<" entro al destructor de Tejo"<<endl;
}
int Tejo::getX(){
	return this->circulo->getPosicion()->getX();
}
int Tejo::getY(){
	return this->circulo->getPosicion()->getY();
}
void Tejo::setX(int x){
	this->circulo->getPosicion()->setX(x);
}
void Tejo::setY(int y){
	this->circulo->getPosicion()->setY(y);
}
// El movimiento de la imagen se establece

void Tejo::mover_x() {
	int x =this->getX();
	this->setXAnterior(x);
	this->setX(this->getXSiguiente(x));
//	std::cout<<"posicion X :"<<x<<endl;
}
int Tejo::getXSiguiente(int x) {
	Escenario* escenario= Escenario::obtenerInstancia();
	if(x>=escenario->getAncho()-this->getRadio()){
			x += this->moverMayor*-1;
		}else{

		double res = cos(this->direccion->getFi());
		if(res>=0.5&&res<1){
			x += this->moverMayor;
		}else{
			if(res<=-0.5&&res>=-1){
				x += this->moverMayor*-1;
			}else{
				if(res>0.05&&res<0.5){
					x += this->moverMenor;
				}else{
					if(res<-0.05&&res>-0.5){
						x += this->moverMenor*-1;
					}else{
						if(res==1.0){
					     x += this->moverMenor;
						}
					}

				}
			}
		}
}
return x;
}

void Tejo::moverTejo(){
	if(this->mover){
		this->cargarPixelesAMover();
		this->mover_x();
		this->mover_y();
	}
	else{
		if(this->getPadPegajoso().compare(PAD_CLIENTE1) == 0){
			Pad* pad = Escenario::obtenerInstancia()->getPadCliente1();
			this->setY(pad->getY()+pad->getAltura()/2);
			this->setX(pad->getX()-this->getRadio());

		}
		else if(this->getPadPegajoso().compare(PAD_CLIENTE2) == 0){
			Pad* pad = Escenario::obtenerInstancia()->getPadCliente2();
			this->setX(pad->getX()+pad->getBase()+this->getRadio());
			this->setY(pad->getY()+pad->getAltura()/2);
		}

	}
}
void Tejo::mover_y(){
	int y =this->getY();
	this->setYAnterior(y);
	this->setY(this->getYSiguiente(y));
	if(DEBUG2==1){
		std::cout<<"direccion  :"<<(this->direccion->getFi()*180)/PI<<endl;
		std::cout<<"posision X : "<<this->getX()<<endl;
		std::cout<<"posision Y :   "<<this->getY()<<endl;
	}
}
void  Tejo::cargarPixelesAMover() {

	switch (this->velocidad) {
	case 1:
		this->moverMayor=2;
		this->moverMenor=1;
		if(DEBUG==1){
		std::cout << "velocidad 1 " << endl;
		}
		break;
	case 2:
		this->moverMayor=3;
		this->moverMenor=2;
		if(DEBUG==1){
		std::cout << "velocidad 2 " << endl;
		}
		break;
	case 3:              // L-16:
		this->moverMayor=4;
		this->moverMenor=2;
		if(DEBUG==1){
	//	std::cout << "velocidad 3 " << endl;
		}
		break;
	case 4:              // L-16:
		this->moverMayor=5;
		this->moverMenor=3;
		if(DEBUG==1){
		std::cout << "velocidad 4 " << endl;
		}
		break;
	case 5:              // L-16:
		this->moverMayor=6;
		this->moverMenor=3;
		if(DEBUG==1){
		std::cout << "velocidad 5 " << endl;
		}
		break;
	case 6:              // L-16:
		this->moverMayor=7;
		this->moverMenor=4;
		if(DEBUG==1){
		std::cout << "velocidad 6 " << endl;
		}
		break;
	case 7:              // L-16:
		this->moverMayor=8;
		this->moverMenor=4;
		if(DEBUG==1){
		std::cout << "velocidad 7 " << endl;
		}
		break;
	default:             // L-20:
		this->moverMayor=9;
		this->moverMenor=5;
		if(DEBUG==1){
		std::cout << "velocidad 9 pixeles  o mas esta es la maxima" << endl;
		}
	}
}
int Tejo::getYSiguiente(int y) {
	Escenario* escenario= Escenario::obtenerInstancia();
	if(y>=escenario->getAlto()-this->getRadio()){
		y += this->moverMayor*-1;
	}else{

		double res =sin(this->direccion->getFi());
		if(res>=0.5&&res<1){
			y -= this->moverMayor;
		}else{
			if(res<=-0.5&&res>=-1){
				y -= this->moverMayor*-1;
			}else{
				if(res>0.05&&res<0.5){
					y -= this->moverMenor;
				}else{
					if(res<-0.05&&res>-0.5){
						y -= this->moverMenor*-1;
					}else{
//						if(res==0.0){
//							y -= this->moverMenor;
//						}
					}
				}
			}
		}
		}


	return y;
}
void Tejo::setRadio(int radio){
	this->circulo->setRadio(radio);
}

int Tejo::getRadio(){
	return this->circulo->getRadio();
}

Direccion* Tejo::getDireccion(){
	return this->direccion;
}

int Tejo::getXAnterior(){
	return this->XAnterior;
}
int Tejo::getYAnterior(){
	return this->YAnterior;
}
void Tejo::setXAnterior(int x){
	this->XAnterior = x;
}
void Tejo::setYAnterior(int y){
	this->YAnterior = y;
}

void Tejo::setMover(bool mover){
	this->mover = mover;
}

bool Tejo::getMover(){
	return this->mover;
}

void Tejo::setPegajoso(bool pegajoso){
	this->pegajoso = pegajoso;
}

bool Tejo::getPegajoso(){
	return this->pegajoso;
}
std::string Tejo::obtenerUltimaColisionPad(){
	return this->ultimaColisionPad;
}

void Tejo::setUltimaColisionPad(std::string ultimoPad){
	this->ultimaColisionPad = ultimoPad;

}
bool Tejo::getModificarRadio()
   {
       return modificarRadio;
   }

void Tejo::setModificarRadio(bool modificarRadio)
 {
      this->modificarRadio = modificarRadio;
  }

int Tejo::getVelocidadDefault(){
   return this->velocidadDefault;
}
void Tejo::setVelocidadDefault(int velocidad){
  this->velocidadDefault = velocidad;
}
std::string	Tejo::getPadPegajoso(){
	return this->padPegajoso;
}
void Tejo::setPadPegajoso(std::string padPegajoso){
	this->padPegajoso = padPegajoso;
}
