/*
 * FabricaIndexadoHashExtensible.h
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#ifndef FABRICAINDEXADOHASHEXTENSIBLE_H_
#define FABRICAINDEXADOHASHEXTENSIBLE_H_

#include "FabricaAbstracta.h"

class FabricaIndexadoHashExtensible: public FabricaAbstracta {
public:
	FabricaIndexadoHashExtensible();
	Object* fabricar();
	virtual ~FabricaIndexadoHashExtensible();
};

#endif /* FABRICAINDEXADOHASHEXTENSIBLE_H_ */
