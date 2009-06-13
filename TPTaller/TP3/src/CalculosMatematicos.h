/*
 * CalculosMatematicos.h
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#ifndef CALCULOSMATEMATICOS_H_
#define CALCULOSMATEMATICOS_H_
#include "Posicion.h"
#include "Circulo.h"
#include "Tejo.h"
class CalculosMatematicos {
public:
	CalculosMatematicos();
	virtual ~CalculosMatematicos();
	static Posicion* getInterseccionEsferas(Tejo* tejo,Circulo* circulo);
	static int calcularDistancia(int izqX, int izqY,int derX, int derY);
};

#endif /* CALCULOSMATEMATICOS_H_ */
