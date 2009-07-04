/*
 * Bonus2.cpp
 *
 *  Created on: 20-jun-2009
 *      Author: pablosivori
 */

#include "Bonus.h"
#include "Escenario.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Bonus::Bonus() {
this->imagen=NULL;

}
void Bonus::cargarImagen(std::string pathTextura){
	SDL_Surface* image;
		//	 Cargamos la imagen
		if(this->imagen==NULL){
			std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(pathTextura);
			image = IMG_Load(path.begin());
			//			this->imagen = SDL_LoadBMP(path.begin());
			if(image == NULL) {
				std::cout<< "Error: " << SDL_GetError() << endl;
				exit(1);
			}
			this->imagen = SDL_DisplayFormat(image);
			  SDL_FreeSurface(image);
		}
}
Bonus::~Bonus() {
	// TODO Auto-generated destructor stub
}
SDL_Surface* Bonus::getImagen()
    {
        return this->imagen;
    }

    void Bonus::setImagen(SDL_Surface *imagen)
    {
        this->imagen = imagen;
    }

int Bonus::getActivo(){
	return this->activo;
}

void Bonus::setActivo(int activo){
	this->activo = activo;
}

void Bonus::setVelocidadAnterior(int velocidadAnterior){
	this->velocidadAnterior = velocidadAnterior;
}

int Bonus::getVelocidadAnterior(){
	return this->velocidadAnterior;
}

void Bonus::setAlturaAnterior(int alturaAnterior){
	this->alturaAnterior = alturaAnterior;
}

int Bonus::getAlturaAnterior(){
	return this->alturaAnterior;
}

void Bonus::setRadioAnterior(int radioAnterior){
	this->radioAnterior = radioAnterior;
}

int Bonus::getRadioAnterior(){
	return this->radioAnterior;
}

int Bonus::getTipoBonus(){
	return this->tipoBonus;
}
int Bonus::setTipoBonus(int tipoBonus){
	return this->tipoBonus =tipoBonus;
}
