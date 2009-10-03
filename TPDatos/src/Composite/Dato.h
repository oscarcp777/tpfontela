/*
 * Dato.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */
#include "Registro/Registro.h"
#include "Clave.h"

#ifndef DATO_H_
#define DATO_H_

//funciona como interface
class Dato : public Registro {
public:
	Dato();
	virtual ~Dato();

	//metodos virtuales a implementar por clase hija
	virtual Clave* serializarToolkit() const =0;
	virtual void hidratarToolkit (Clave* desde) const =0;
};

#endif /* DATO_H_ */
