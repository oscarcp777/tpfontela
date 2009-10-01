/*
 * Clave.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */
#include <iostream>

#ifndef CLAVE_H_
#define CLAVE_H_

class Clave {
public:
	Clave(std::string nombre);
	virtual ~Clave();
	void setearAtributo(std::string nombre, std::string valor);
};

#endif /* CLAVE_H_ */
