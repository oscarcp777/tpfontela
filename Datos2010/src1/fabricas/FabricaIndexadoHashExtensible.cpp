/*
 * FabricaIndexadoHashExtensible.cpp
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#include "FabricaIndexadoHashExtensible.h"
#include "../Estrategy/IndexadoHashExtensible.h"
FabricaIndexadoHashExtensible::FabricaIndexadoHashExtensible() {
	// TODO Auto-generated constructor stub

}

FabricaIndexadoHashExtensible::~FabricaIndexadoHashExtensible() {
	// TODO Auto-generated destructor stub
}
Object* FabricaIndexadoHashExtensible::fabricar(){
	return new IndexadoHashExtensible();

}
