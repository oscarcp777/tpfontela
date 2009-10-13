/*
 * RegistroDisco.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef REGISTRODISCO_H_
#define REGISTRODISCO_H_

#include "Registro.h"

class RegistroDisco: public Registro {
public:
	RegistroDisco();
	virtual ~RegistroDisco();
	void serializar();
	void hidratar();
};

#endif /* REGISTRODISCO_H_ */
