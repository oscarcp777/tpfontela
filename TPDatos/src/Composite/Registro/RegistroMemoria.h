/*
 * RegistroMemoria.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef REGISTROMEMORIA_H_
#define REGISTROMEMORIA_H_

#include "Registro.h"

class RegistroMemoria: public Registro {
public:
	RegistroMemoria(int tamanio);
	virtual ~RegistroMemoria();
	void serializar();
	void hidratar();
};

#endif /* REGISTROMEMORIA_H_ */
