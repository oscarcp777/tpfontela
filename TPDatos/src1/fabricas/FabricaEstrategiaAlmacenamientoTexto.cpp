/*
 * FabricaEstrategiaAlmacenamientoTexto.cpp
 *
 *  Created on: 03/10/2009
 *      Author: oscar
 */

#include "FabricaEstrategiaAlmacenamientoTexto.h"
#include "../Estrategy/EstrategiaAlmacenamientoTexto.h"
FabricaEstrategiaAlmacenamientoTexto::FabricaEstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated constructor stub

}

FabricaEstrategiaAlmacenamientoTexto::~FabricaEstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated destructor stub
}
Object* FabricaEstrategiaAlmacenamientoTexto::fabricar(){
	return new EstrategiaAlmacenamientoTexto();

}
