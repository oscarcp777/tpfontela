/*
 * RectanguloInfluencia.cpp
 *
 *  Created on: 31/05/2009
 *      Author: oscar
 */
#include "RectanguloInfluencia.h"

RectanguloInfluencia::RectanguloInfluencia(SDL_Rect rectangulo,std::string posicion) {
	this->rectangulo=rectangulo;
    this->posicionRectangulo=posicion;
}
SDL_Rect RectanguloInfluencia::getRectangulo(){
	std::cout<<this->rectangulo.h<<std::endl;
        return this->rectangulo;
    }

RectanguloInfluencia::~RectanguloInfluencia() {
	// TODO Auto-generated destructor stub
}
std::string RectanguloInfluencia::getPosicionRectangulo()
    {
        return this->posicionRectangulo;
    }

