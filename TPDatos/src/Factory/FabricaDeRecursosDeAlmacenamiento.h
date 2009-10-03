/*
 * FabricaDeRecursosDeAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include <iostream>
#include "../Composite/Componente.h"

#ifndef FABRICADERECURSOSDEALMACENAMIENTO_H_
#define FABRICADERECURSOSDEALMACENAMIENTO_H_

class FabricaDeRecursosDeAlmacenamiento {
public:
	FabricaDeRecursosDeAlmacenamiento();
	virtual ~FabricaDeRecursosDeAlmacenamiento();

	static void RecursoDeAlmacenamientoEnArchivo(std::string eAlmacenamiento /*"texto","registros","bloques"*/,Componente* componente);
};

#endif /* FABRICADERECURSOSDEALMACENAMIENTO_H_ */
