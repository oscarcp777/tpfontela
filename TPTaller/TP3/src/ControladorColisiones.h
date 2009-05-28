/*
 * ControladorColisiones.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef CONTROLADORCOLISIONES_H_
#define CONTROLADORCOLISIONES_H_

class ControladorColisiones {

public:
	ControladorColisiones();
	virtual ~ControladorColisiones();
	static bool posibilidadDeColisionDispersores();
	static void calcularDireccion();
	static void colisionesPads();
};

#endif /* CONTROLADORCOLISIONES_H_ */
