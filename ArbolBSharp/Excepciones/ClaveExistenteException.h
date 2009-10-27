/*
 * ClaveExistenteException.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "Exception.h"

#ifndef CLAVEEXISTENTEEXCEPTION_H_
#define CLAVEEXISTENTEEXCEPTION_H_

class ClaveExistenteException: public Exception{
	public:
			ClaveExistenteException();
			const char* what() const throw();
			~ClaveExistenteException();
};

#endif /* CLAVEEXISTENTEEXCEPTION_H_ */
