/*
 * FabricaEstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#include "FabricaEstrategiaAlmacenamientoBloques.h"
#include "../Estrategy/EstrategiaAlmacenamientoBloques.h"

FabricaEstrategiaAlmacenamientoBloques::FabricaEstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated constructor stub

}

FabricaEstrategiaAlmacenamientoBloques::~FabricaEstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated destructor stub
}
Object* FabricaEstrategiaAlmacenamientoBloques::fabricar(){
	return new EstrategiaAlmacenamientoBloques();

}
