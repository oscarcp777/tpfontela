/*
 * FabricaBuffer.cpp
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#include "FabricaBuffer.h"
#include "../Almacenamiento/Buffer.h"

FabricaBuffer::FabricaBuffer() {
	// TODO Auto-generated constructor stub

}

FabricaBuffer::~FabricaBuffer() {
	// TODO Auto-generated destructor stub
}
Object* FabricaBuffer::fabricar(Object* comp){
	return new Buffer((Compuesto*)comp);

}
