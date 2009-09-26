/*
 * Bloque.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "../../Composite/Componente.h"
#include "../../Composite/Compuesto.h"

class Bloque : public Componente , Compuesto{
public:
	Bloque(int tamanio);
	virtual ~Bloque();
};

#endif /* BLOQUE_H_ */
