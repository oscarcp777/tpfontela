/*
 * FabricaAbstracta.h
 *
 *  Created on: 03/10/2009
 *      Author: oscar
 */

#ifndef FABRICAABSTRACTA_H_
#define FABRICAABSTRACTA_H_
#include "../Object/Object.h"
class FabricaAbstracta {
public:
	FabricaAbstracta();
	//metodo virtual para fabricar
    virtual	Object* fabricar();
    virtual Object* fabricar(Object* comp);
	virtual ~FabricaAbstracta();
};

#endif /* FABRICAABSTRACTA_H_ */
