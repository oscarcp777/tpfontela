/*
 * Dispersor.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Posicion.h"
#include "Figura.h"
#ifndef __DISPERSOR_H__
#define __DISPERSOR_H__


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
