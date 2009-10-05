/*
 * EstrategiaRecurso.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIARECURSO_H_
#define ESTRATEGIARECURSO_H_
#include "../Object/Object.h"
class EstrategiaRecurso :public Object{
public:
	EstrategiaRecurso();
	virtual ~EstrategiaRecurso();
	std::string toString();
};

#endif /* ESTRATEGIARECURSO_H_ */
