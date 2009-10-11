/*
 * FabricaArchivo.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#ifndef FABRICAARCHIVO_H_
#define FABRICAARCHIVO_H_

#include "FabricaAbstracta.h"
#include "../Composite/Componente.h"

class FabricaArchivo: public FabricaAbstracta {
public:
	Object* fabricar();
	FabricaArchivo();
	virtual ~FabricaArchivo();
};

#endif /* FABRICAARCHIVO_H_ */
