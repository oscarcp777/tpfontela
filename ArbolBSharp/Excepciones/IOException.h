/*
 * IOException.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "Exception.h"

#ifndef IOEXCEPTION_H_
#define IOEXCEPTION_H_

using namespace std;

class IOException: public Exception{

	public:
			IOException();
			const char* what() const throw();
		   ~IOException();

};

#endif /* IOEXCEPTION_H_ */
