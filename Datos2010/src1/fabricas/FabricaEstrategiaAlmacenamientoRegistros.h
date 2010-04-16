/*
 * FabricaEstrategiaAlmacenamientoRegistros.h
 *
 *  Created on: 03/10/2009
 *      Author: oscar
 */

#ifndef FabricaEstrategiaALMACENAMIENTOREGISTROS_H_
#define FabricaEstrategiaALMACENAMIENTOREGISTROS_H_

#include "../Estrategy/EstrategiaAlmacenamiento.h"
#include "FabricaAbstracta.h"
class FabricaEstrategiaAlmacenamientoRegistros: public FabricaAbstracta {

public:
	Object* fabricar();
	FabricaEstrategiaAlmacenamientoRegistros();
	virtual ~FabricaEstrategiaAlmacenamientoRegistros();
};

#endif /* FabricaEstrategiaALMACENAMIENTOREGISTROS_H_ */
