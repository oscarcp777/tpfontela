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
#include <string>
#include <SDL_image.h>
class GraficadorPuntajes {
public:

	static GraficadorPuntajes* obtenerInstancia();
	virtual ~GraficadorPuntajes();
	void graficarCantidadDeTejos(SDL_Surface*screen);
	int graficarPuntaje(SDL_Surface*screen);
	int inicializarFuente(int puntajeJugadorIzquierda, int puntajeJugadorDerecha);
	void decrementarCantidadTejos();
	int graficarString(SDL_Surface*screen, std::string mensaje,int posX, int posY);

protected:
	      GraficadorPuntajes();

private:
	    
	    static GraficadorPuntajes *unicaInstancia;
		SDL_Surface* textImagen;
		SDL_Surface *imagenTejo;
		TTF_Font* fuente;
};

#endif /* GRAFICADORPUNTAJES_H_ */
