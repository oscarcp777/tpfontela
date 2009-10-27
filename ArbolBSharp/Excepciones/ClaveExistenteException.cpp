/*
 * ClaveExistenteException.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */
#include "ClaveExistenteException.h"

ClaveExistenteException::ClaveExistenteException(){

}

const char* ClaveExistenteException::what() const throw(){
	return "La clave ya existe";
}

ClaveExistenteException::~ClaveExistenteException(){

}
