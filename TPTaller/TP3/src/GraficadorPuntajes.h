/*
 * GraficadorPuntajes.h
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#ifndef __GRAFICADORPUNTAJES_H__
#define __GRAFICADORPUNTAJES_H__
#include <SDL_TTF.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>

class GraficadorPuntajes {
public:

	static GraficadorPuntajes* obtenerInstancia();
	virtual ~GraficadorPuntajes();

	  void graficarCantidadDeTejos(SDL_Surface*screen,bool gol);
	 int graficarPuntaje(int puntajeJugadorIzquierda, int puntajeJugadorDerecha,SDL_Surface*screen,TTF_Font* fuente,bool gol);
     int graficarTexto(SDL_Surface*screen,TTF_Font* fuente, std::string textoGraficar, int posInicialX, int posInicialY, int ancho, int largo);

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
		SDL_Surface* textImagenTexto;
		SDL_Surface *imagenTejo;
};

#endif /* GRAFICADORPUNTAJES_H_ */
