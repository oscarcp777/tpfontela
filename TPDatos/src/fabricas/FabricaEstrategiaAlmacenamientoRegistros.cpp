/*
 * FabricaEstrategiaAlmacenamientoRegistros.cpp
 *
 *  Created on: 03/10/2009
 *      Author: oscar
 */

#include "FabricaEstrategiaAlmacenamientoRegistros.h"
#include "../Estrategy/EstrategiaAlmacenamientoRegistros.h"
FabricaEstrategiaAlmacenamientoRegistros::FabricaEstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated constructor stub

}

FabricaEstrategiaAlmacenamientoRegistros::~FabricaEstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated destructor stub
}
Object* FabricaEstrategiaAlmacenamientoRegistros::fabricar(){
	return new EstrategiaAlmacenamientoRegistros();

}
