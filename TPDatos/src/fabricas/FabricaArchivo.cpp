/*
 * FabricaArchivo.cpp
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#include "FabricaArchivo.h"
#include "../Almacenamiento/Archivo.h"
FabricaArchivo::FabricaArchivo() {
	// TODO Auto-generated constructor stub

}

FabricaArchivo::~FabricaArchivo() {
	// TODO Auto-generated destructor stub
}
Object* FabricaArchivo::fabricar(Object* comp){
	return new Archivo((Compuesto*)comp);

}
