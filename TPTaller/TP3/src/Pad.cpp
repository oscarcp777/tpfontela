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
	int y =this->getY();
	y += this->velocidad;
	this->setY(y);
}
void Pad::subir_y() {
	int y =this->getY();
	y -= this->velocidad;
	this->setY(y);
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
		bool aux = this->cambioPosicion;
		if (this->cambioPosicion)
			this->cambioPosicion = false;
        return aux;
}

