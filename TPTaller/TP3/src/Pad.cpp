/*
 * Pad.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Pad.h"
#include "Rectangulo.h"
#include "Escenario.h"
#include "Define.h"
Pad::Pad() {

}
Rectangulo* Pad::getFigura(){
	return this->rectangulo;
}
void Pad::volverEstadoInicial(){
	this->setAltura(this->getAlturaDefault());
	this->setModificar(true);

}
Pad::Pad(Rectangulo* rectangulo,Puntaje* puntaje){
	this->imagen=NULL;
	this->fondoPad=NULL;
	this->rectangulo=rectangulo;
	this->puntaje = puntaje;
	this->cantGoles = 0;
	this->modificar=false;
	this->soltarTejo=false;
	this->cambioPosicion=false;
	this->moverArriba = false;
	this->moverAbajo = false;
	this->mutex = CreateMutex(NULL,false,NULL);


}
int Pad::getVelocidad()
    {
        return velocidad;
    }

    void Pad::setVelocidad(int velocidad)
    {
        this->velocidad = velocidad;
    }
 Pad::~Pad() {
	   if(this->imagen!=NULL)
    	SDL_FreeSurface(this->imagen);
    	delete rectangulo;
    	delete puntaje;
    	if(DEBUG_DESTRUCTOR==1)
    		std::cout<<" entro al destructor de Pad"<<endl;
		CloseHandle(this->mutex);
}
void Pad::dibujar(SDL_Surface *pantalla){
	// Cargamos la imagen
	 SDL_Surface* imageACargar1;

	if(this->imagen==NULL){
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->rectangulo->getIdTextura());
		imageACargar1 = IMG_Load(path.begin());
		if(imageACargar1 == NULL) {
			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);
		}
		if(imageACargar1 != NULL){
			std::cout<< "cargo imagen"<< endl;
			imageACargar1 = this->getFigura()->ScaleSurface(imageACargar1, this->getFigura()->getBase(), this->getFigura()->getAltura());
		}
		this->imagen = SDL_DisplayFormat(imageACargar1);
	    SDL_FreeSurface(imageACargar1);
	}
	if(this->modificar){
			this->imagen = this->getFigura()->ScaleSurface(this->imagen,  this->getFigura()->getBase(), this->getFigura()->getAltura());
		    this->modificar=false;
	}
	SDL_Rect rect;
	rect.x =this->getX();
	rect.y = this->getY();
	SDL_BlitSurface(this->imagen, NULL, pantalla, &rect);
}
int Pad::getX(){
	return this->rectangulo->getPosicion()->getX();
}
int Pad::getY(){
	return this->rectangulo->getPosicion()->getY();
}
bool Pad::getModificar()
    {
        return modificar;
    }

    void Pad::setModificar(bool modificar)
    {
        this->modificar = modificar;
    }

void Pad::setX(int x){
	this->rectangulo->getPosicion()->setX(x);
}
void Pad::setY(int y){
	this->rectangulo->getPosicion()->setY(y);
	this->cambioPosicion = true;
}

int Pad::getBase(){
	return this->rectangulo->getBase();
}
int Pad::getAltura(){
	return this->rectangulo->getAltura();
}

void Pad::setAltura(int altura){
	this->rectangulo->setAltura(altura);
}
// El movimiento de la imagen se establece
// de 4 en 4 píxeles
void Pad::avanzar_x() {
	int x =this->getX();
	x += this->velocidad;
	this->setX(x);
}
void Pad::retrasar_x() {
	int x =this->getX();
	x -= this->velocidad;
	this->setX(x);
}
void Pad::bajar_y() {
//	WaitForSingleObject(this->mutex,INFINITE);	
					
	int y =this->getY();
	y += this->velocidad;
	this->setY(y);
	WaitForSingleObject(this->mutex,INFINITE);	

	this->cambioPosicion = true;
	ReleaseMutex(this->mutex);
}
void Pad::subir_y() {
					
	int y =this->getY();
	y -= this->velocidad;
	this->setY(y);
	WaitForSingleObject(this->mutex,INFINITE);	

	this->cambioPosicion = true;
	ReleaseMutex(this->mutex);
}
int Pad::calcularProximaPosicionAlSubir(){
		int y =this->getY();
		y -= this->velocidad;
		return y;
	}

int Pad::calcularProximaPosicionAlBajar(){
	int y =this->getY();
	y += this->velocidad;
	return y;
	}

Puntaje* Pad::getPuntaje(){
	return this->puntaje;
}

int Pad::getCantGoles()
{
	return cantGoles;
}

void Pad::setCantGoles(int cantGoles)
{
	this->cantGoles = cantGoles;
}
void Pad::setImagen(SDL_Surface *imagen){

	this->imagen = imagen;
}
int Pad::getAlturaDefault(){
	return this->alturaDefault;
}
void Pad::setAlturaDefault(int altura){
	this->alturaDefault = altura;
}
void Pad::setSoltarTejo(bool soltar){
	this->soltarTejo = soltar;
}
bool Pad::getSoltarTejo(){
	return this->soltarTejo;
}

bool Pad::getCambioPosicion()
{
		//WaitForSingleObject(this->mutex,INFINITE);	
		bool aux = this->cambioPosicion;
		if (this->cambioPosicion)
			this->cambioPosicion = false;
        return aux;
		//ReleaseMutex(this->mutex);
}
bool Pad::getMoverArriba(){
	return this->moverArriba;
}
void Pad::setMoverArriba(bool moverArriba){
	this->moverArriba = moverArriba;
}
bool Pad::getMoverAbajo(){
	return this->moverAbajo;
}
void Pad::setMoverAbajo(bool moverAbajo){
	this->moverAbajo = moverAbajo;
}
void Pad::setXString(int i){
	this->xString = "";
    if (i == 0)
    {
        this->xString = "0";
        return;
    }
    if (i < 0)
    {
        this->xString += '-';
        i = -i;
    }
    int count = (int)log10(i);
    while (count >= 0)
    {
        this->xString += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }

}

void Pad::setYString(int i){
	this->yString = "";
    if (i == 0)
    {
        this->yString = "0";
        return;
    }
    if (i < 0)
    {
        this->yString += '-';
        i = -i;
    }
    int count = (int)log10(i);
    while (count >= 0)
    {
        this->yString += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }

}

std::string Pad::getXString(){
	return this->xString;
}
std::string Pad::getYString(){
	return this->yString;

}

