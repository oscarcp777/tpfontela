/*
 * EstrategiaAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTO_H_
#define ESTRATEGIAALMACENAMIENTO_H_
#include "../Object/Object.h"
#include "../Almacenamiento/Almacenamiento.h"
class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	virtual void guardar(Almacenamiento* donde) const=0;
	std::string toString();
};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
