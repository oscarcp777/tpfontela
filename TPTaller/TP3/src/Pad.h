/*
 * Pad.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Posicion.h"
#ifndef PAD_H_
#define PAD_H_

#include "Figura.h"
#include "Movible.h"
class Pad: public Movible{
public:
	Pad();
	Pad(int base,int altura,Posicion * posicion);
	virtual ~Pad();
	int mover(Posicion* posicion);
	void dibujar(SDL_Surface *pantalla);
};

#endif /* PAD_H_ */
