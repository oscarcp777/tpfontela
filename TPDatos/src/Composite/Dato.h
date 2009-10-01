/*
 * Dato.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */
#include "Clave.h"

#ifndef DATO_H_
#define DATO_H_

//funciona como interface
class Dato {
public:
	Dato();
	virtual ~Dato();

	//metodos virtuales a implementar por clase hija
	virtual Clave* serializarToolkit()=0;
	virtual void hidratarToolkit (Clave* desde)=0;
};

#endif /* DATO_H_ */
