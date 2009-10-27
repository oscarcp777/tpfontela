/*
 * IOException.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "IOException.h"

IOException::IOException(){

}

const char* IOException::what() const throw(){
	return "Error al abrir el archivo, chequee que la ruta del mismo sea correcta";
}

IOException::~IOException(){

}
