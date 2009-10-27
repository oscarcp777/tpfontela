/*
 * Exception.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

using namespace std;

class Exception{
	public:
			Exception();
			virtual const char* what() const throw()=0;
			~Exception();
};

#endif /* EXCEPTION_H_ */
