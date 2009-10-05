/*
 * EstrategiaAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTO_H_
#define ESTRATEGIAALMACENAMIENTO_H_
#include "../Object/Object.h"
class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	std::string toString();
};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
