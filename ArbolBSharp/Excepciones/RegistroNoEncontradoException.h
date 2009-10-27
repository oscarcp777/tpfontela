/*
 * RegistroNoEncontradoException.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */
#include "Exception.h"

#ifndef REGISTRONOENCONTRADOEXCEPTION_H_
#define REGISTRONOENCONTRADOEXCEPTION_H_

using namespace std;

class RegistroNoEncontradoException: public Exception{
	public:
			RegistroNoEncontradoException();
			const char* what() const throw();
			~RegistroNoEncontradoException();
};

#endif /* REGISTRONOENCONTRADOEXCEPTION_H_ */
