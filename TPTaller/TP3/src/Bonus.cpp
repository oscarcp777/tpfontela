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
void Bonus::desAplicar(){
	Escenario* escenario=Escenario::obtenerInstancia();
	escenario->getPadCliente1()->volverEstadoInicial();
	escenario->getPadCliente2()->volverEstadoInicial();
	escenario->getTejo()->volverEstadoInicial();
}
void Bonus::cargarImagen(std::string idTextura){
	SDL_Surface* image;
		//	 Cargamos la imagen
		if(this->imagen==NULL){
			std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(idTextura);
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
	if(!this->imagen){
		SDL_FreeSurface(this->imagen);
	}

}
SDL_Surface* Bonus::getImagen()
    {
        return this->imagen;
    }

    void Bonus::setImagen(SDL_Surface *imagen)
    {
        this->imagen = imagen;
    }

int Bonus::getTipoBonus(){
	return this->tipoBonus;
}
int Bonus::setTipoBonus(int tipoBonus){
	return this->tipoBonus =tipoBonus;
}
