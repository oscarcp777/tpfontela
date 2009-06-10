/*
 * GraficadorPuntajes.h
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#ifndef GRAFICADORPUNTAJES_H_
#define GRAFICADORPUNTAJES_H_
#include <SDL_TTF.h>
#include <SDL.h>
#include <SDL_image.h>
class GraficadorPuntajes {
public:

	static GraficadorPuntajes* obtenerInstancia();
	virtual ~GraficadorPuntajes();
	  void graficarCantidadDeTejos(SDL_Surface*screen,bool gol);
	 int graficarPuntaje(int puntajeJugadorIzquierda, int puntajeJugadorDerecha,SDL_Surface*screen,TTF_Font* fuente,bool gol);
protected:
	      GraficadorPuntajes();
private:
	    int contadorDeTejos;
	     static GraficadorPuntajes *unicaInstancia;
		SDL_Surface* textImagen;
		SDL_Surface *imagenTejo;
};

#endif /* GRAFICADORPUNTAJES_H_ */
