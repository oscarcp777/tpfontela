/*
 * FabricaIndexadoBSharp.h
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#ifndef FABRICAINDEXADOBSHARP_H_
#define FABRICAINDEXADOBSHARP_H_

#include "FabricaAbstracta.h"

class FabricaIndexadoBSharp: public FabricaAbstracta {
public:
	FabricaIndexadoBSharp();
	Object* fabricar();
	virtual ~FabricaIndexadoBSharp();
};

#endif /* FABRICAINDEXADOBSHARP_H_ */
