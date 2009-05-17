/*
 * Movible.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Posicion.h"
#include "Figura.h"
#ifndef MOVIBLE_H_
#define MOVIBLE_H_

class Movible {
public:
	Movible();
	virtual ~Movible();
	Figura*getFigura();
	void setFigura(Figura *figura);
	Posicion* getPosicion();
	void setPosicion(Posicion * posicion);
	 virtual int mover(Posicion* posicion)=0; //metodo virtual puro
protected:
	Figura* figura;
	Posicion * posicion;
};

#endif /* MOVIBLE_H_ */
