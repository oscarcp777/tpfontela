/*
 * RegistroNoEncontradoException.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "RegistroNoEncontradoException.h"

RegistroNoEncontradoException::RegistroNoEncontradoException(){

}

const char* RegistroNoEncontradoException::what() const throw(){
	return "No se encontro el registro";
}

RegistroNoEncontradoException::~RegistroNoEncontradoException(){

}
