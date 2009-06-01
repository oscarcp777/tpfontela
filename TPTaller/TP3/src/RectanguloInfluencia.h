/*
 * RectanguloInfluencia.h
 *
 *  Created on: 31/05/2009
 *      Author: oscar
 */

#ifndef RECTANGULOINFLUENCIA_H_
#define RECTANGULOINFLUENCIA_H_
#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
class RectanguloInfluencia {
public:
	RectanguloInfluencia( SDL_Rect rectangulo,std::string posicion);
	 ~RectanguloInfluencia();
    SDL_Rect getRectangulo();
    std::string getPosicionRectangulo();

private:
	  std::string posicionRectangulo;
	  SDL_Rect rectangulo;

};

#endif /* RECTANGULOINFLUENCIA_H_ */
