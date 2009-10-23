/*
 * FabricaEstrategiaAlmacenamientoBloques.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#ifndef FabricaEstrategiaALMACENAMIENTOBLOQUES_H_
#define FabricaEstrategiaALMACENAMIENTOBLOQUES_H_
#include "FabricaAbstracta.h"
class FabricaEstrategiaAlmacenamientoBloques: public FabricaAbstracta {
public:
	Object* fabricar();
	FabricaEstrategiaAlmacenamientoBloques();
	virtual ~FabricaEstrategiaAlmacenamientoBloques();
};

#endif /* FabricaEstrategiaALMACENAMIENTOBLOQUES_H_ */
