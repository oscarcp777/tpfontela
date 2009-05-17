/*
 * Tejo.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Movible.h"
#include "Posicion.h"
#ifndef TEJO_H_
#define TEJO_H_

class Tejo : public Movible {
public:
	Tejo();
	Tejo(int radio,Posicion * posicion);
	virtual ~Tejo();
	int mover(Posicion* posicion);
};

#endif /* TEJO_H_ */
