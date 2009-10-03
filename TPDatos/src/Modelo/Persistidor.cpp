/*
 * Persistidor.cpp
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include "Persistidor.h"

Persistidor::Persistidor() {
	// TODO Auto-generated constructor stub

}

void Persistidor::guardar(std::string nombreArchivo,Dato* dato,std::string eAlmacenamiento){
		//guardar archivo llamando a dato.serializarToolkit()
		//en este caso dato es un alumno con datos a ser guardados en un archivo con ese nombre
		//FabricaDeRecursosDeAlmacenamiento.

}

void Persistidor::recuperar(std::string nombreArchivo,Dato* dato){
		//recuperar archivo llamando a dato.hidratarToolkit()
	    //en este caso dato es un alumno vacio con datos a ser levantados desde ese archivo
}

Persistidor::~Persistidor() {
	// TODO Auto-generated destructor stub
}
