/*
 * Pad.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Rectangulo.h"
#ifndef __PAD_H__
#define __PAD_H__
#include <SDL.h>
#include "Figura.h"
#include "Puntaje.h"

class Pad{
public:
	Pad();
	Pad(Rectangulo* rectangulo,Puntaje* puntaje);
	virtual ~Pad();
    void dibujar(SDL_Surface *pantalla);
    Rectangulo* getFigura();
	Puntaje* getPuntaje();
  	 void avanzar_x();
  	 void retrasar_x();
    void bajar_y();
    void subir_y();
    int getBase();
    int getAltura();
	void setAltura(int altura);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getVelocidad();

    void setVelocidad(int velocidad);
	

private:
  	Rectangulo* rectangulo;
  	SDL_Surface *imagen;
  	SDL_Surface* fondoPad;
	Puntaje* puntaje;
	int velocidad;
	
};

#endif /* PAD_H_ */
