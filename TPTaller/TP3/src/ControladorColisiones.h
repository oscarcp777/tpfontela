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
#include "Recta.h"
#include "Circulo.h"


class ControladorColisiones {

public:
	ControladorColisiones();
	virtual ~ControladorColisiones();
	static bool posibilidadDeColisionDispersores();
	static void calcularDireccion();
	static void colisionesPads();
	static int colisionesArcos();
	static void decidirDireccion(Recta* rectaPerpendicular,Tejo* tejo);
	static void colisionCirculo(Tejo* tejo,Circulo* figura);
};

#endif /* CONTROLADORCOLISIONES_H_ */
