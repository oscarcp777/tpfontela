/*
 * Archivo.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Archivo.h"

Archivo::Archivo(Compuesto* comp):Almacenamiento(comp) {
	// TODO Auto-generated constructor stub

}

Archivo::~Archivo() {
	// TODO Auto-generated destructor stub
}
std::string Archivo::toString(){
	return "Archivo";
}
