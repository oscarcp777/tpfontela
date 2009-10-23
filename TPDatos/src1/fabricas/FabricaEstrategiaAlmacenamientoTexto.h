/*
 * FabricaEstrategiaAlmacenamientoTexto.h
 *
 *  Created on: 03/10/2009
 *      Author: oscar
 */

#ifndef FabricaEstrategiaALMACENAMIENTOTEXTO_H_
#define FabricaEstrategiaALMACENAMIENTOTEXTO_H_

#include "FabricaAbstracta.h"


class FabricaEstrategiaAlmacenamientoTexto: public FabricaAbstracta {
public:

	Object* fabricar();
	FabricaEstrategiaAlmacenamientoTexto();
	virtual ~FabricaEstrategiaAlmacenamientoTexto();
};

#endif /* FabricaEstrategiaALMACENAMIENTOTEXTO_H_ */
