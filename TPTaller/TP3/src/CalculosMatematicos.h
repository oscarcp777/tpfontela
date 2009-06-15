/*
 * CalculosMatematicos.h
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#ifndef CALCULOSMATEMATICOS_H_
#define CALCULOSMATEMATICOS_H_
#include "Tejo.h"
#include "Recta.h"
class CalculosMatematicos {
public:
	CalculosMatematicos();
	virtual ~CalculosMatematicos();
	static Posicion* getInterseccionEsferas(Tejo* tejo,Circulo* circulo);
	static int calcularDistancia(int izqX, int izqY,int derX, int derY);
	static bool verificarPerpendicularidad(Recta* recta1,Recta* recta2);
	static bool isPrimerCuadrante(double direccion);
	static bool isSegundoCuadrante(double direccion);
	static bool isTercerCuadrante(double direccion);
	static bool isCuartoCuadrante(double direccion);
};

#endif /* CALCULOSMATEMATICOS_H_ */
