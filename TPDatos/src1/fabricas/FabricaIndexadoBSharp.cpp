/*
 * FabricaIndexadoBSharp.cpp
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#include "FabricaIndexadoBSharp.h"
#include "../Estrategy/IndexadoBSharp.h"
FabricaIndexadoBSharp::FabricaIndexadoBSharp() {
	// TODO Auto-generated constructor stub

}

FabricaIndexadoBSharp::~FabricaIndexadoBSharp() {
	// TODO Auto-generated destructor stub
}
Object* FabricaIndexadoBSharp::fabricar(){
	return new IndexadoBSharp(5,20); //ordenArbol,tamaño llave

}
