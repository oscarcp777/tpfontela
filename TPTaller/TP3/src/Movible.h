/*
 * Movible.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#ifndef MOVIBLE_H_
#define MOVIBLE_H_

#include "Posicion.h"
#include "Figura.h"
#include <SDL.h>
class Movible {
public:
	Movible();
	virtual ~Movible();
	Figura* getFigura();
	void setFigura(Figura *figura);
	Posicion* getPosicion();
	void setPosicion(Posicion * posicion);
	 virtual int mover(Posicion* posicion)=0; //metodo virtual puro
	 void avanzar_x();
	 void retrasar_x();
	  // Modifica la posición del personaje con respecto al eje Y
	 void bajar_y();
	 void subir_y();
	 // Consultoras

	  int getPos_x();
	  int getPos_y();

	 virtual void dibujar(SDL_Surface *pantalla)=0;

	 // Modificadoras

	  void setPos_x(int x);
	  void setPos_y(int y);

protected:
	Figura* figura;
	Posicion * posicion;
	 SDL_Surface *imagen;
};

#endif /* MOVIBLE_H_ */
