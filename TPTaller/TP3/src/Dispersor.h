/*
 * Dispersor.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Posicion.h"
#include "Figura.h"
#ifndef DISPERSOR_H_
#define DISPERSOR_H_


class Dispersor {
public:
	Dispersor();
	Dispersor(Figura* figura);
	virtual ~Dispersor();
	Figura* getFigura();
	void setFigura(Figura *figura);
private:
	Figura* figura;
};

#endif /* DISPERSOR_H_ */
