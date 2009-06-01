/*
 * ControladorColisiones.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef CONTROLADORCOLISIONES_H_
#define CONTROLADORCOLISIONES_H_

static int PUNTAJE_GOL=10;

class ControladorColisiones {

public:
	ControladorColisiones();
	virtual ~ControladorColisiones();
	static bool posibilidadDeColisionDispersores();
	static void calcularDireccion();
	static void colisionesPads();
	static int colisionesArcos();
};

#endif /* CONTROLADORCOLISIONES_H_ */
