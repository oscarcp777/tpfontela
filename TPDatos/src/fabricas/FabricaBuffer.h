/*
 * FabricaBuffer.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#ifndef FABRICABUFFER_H_
#define FABRICABUFFER_H_

#include "FabricaAbstracta.h"
#include "../Composite/Componente.h"

class FabricaBuffer: public FabricaAbstracta {
public:
	Object* fabricar();
	FabricaBuffer();
	virtual ~FabricaBuffer();
};

#endif /* FABRICABUFFER_H_ */
