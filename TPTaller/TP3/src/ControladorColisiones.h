/*
 * ControladorColisiones.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef CONTROLADORCOLISIONES_H_
#define CONTROLADORCOLISIONES_H_
#include "Tejo.h"
#include "Figura.h"



class ControladorColisiones {

public:
	ControladorColisiones();
	virtual ~ControladorColisiones();
	static bool posibilidadDeColisionDispersores();
	static void calcularDireccion();
	static void colisionesPads();
	static int colisionesArcos();
	static void colisionCirculo(Tejo* tejo,Figura* figura);
};

#endif /* CONTROLADORCOLISIONES_H_ */
