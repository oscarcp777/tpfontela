/*
 * BloqueMemoria.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BLOQUEMEMORIA_H_
#define BLOQUEMEMORIA_H_

#include "Bloque.h"

class BloqueMemoria: public Bloque {
public:
	BloqueMemoria(int tamanio);
	virtual ~BloqueMemoria();
};

#endif /* BLOQUEMEMORIA_H_ */
