/*
 * FabricaDeRecursosDeAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include <iostream>
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
#include "../Almacenamiento/Archivo.h"
#include "../Estrategy/EstrategiaRecursoUnAlmacenamiento.h"
#include "../Estrategy/EstrategiaAlmacenamientoTexto.h"

//#include "../Estrategy/EstrategiaRecurso.h"
//#include "../Estrategy/EstrategiaIndice.h"
//#include "../Composite/Componente.h"

#ifndef FABRICADERECURSOSDEALMACENAMIENTO_H_
#define FABRICADERECURSOSDEALMACENAMIENTO_H_

class FabricaDeRecursosDeAlmacenamiento {
public:
	FabricaDeRecursosDeAlmacenamiento();
	virtual ~FabricaDeRecursosDeAlmacenamiento();

	static void RecursoDeAlmacenamientoEnArchivo(std::string nombreArchivo, std::string eAlmacenamiento /*"texto","registros","bloques"*/,Componente* componente);
};

#endif /* FABRICADERECURSOSDEALMACENAMIENTO_H_ */


