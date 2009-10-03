/*
 * Registro.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../../Composite/Componente.h"

class Registro : public Componente{
public:
	Registro(int tamanio);
	virtual ~Registro();


private:
	void* datos;

};

#endif /* REGISTRO_H_ */
