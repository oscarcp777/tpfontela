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
#include <map>
#include "../fabricas/FabricaAbstracta.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
class FabricaDeRecursosDeAlmacenamiento {
private:
	static FabricaDeRecursosDeAlmacenamiento* unicaInstanciaFabrica;
	FabricaDeRecursosDeAlmacenamiento();

private:
	std::map<std::string , FabricaAbstracta*> mapaFabricas;

public:
	        /**
			 * Enumerado de elementos posibles, para poder utilizar como claves de la fabrica
			 */

	FabricaAbstracta* getFabrica(std::string clave);
	static FabricaDeRecursosDeAlmacenamiento* obtenerInstancia();
	virtual ~FabricaDeRecursosDeAlmacenamiento();
	 /**
	     * recurso de almacenamiento para guardar en archivos con texto, registros y en bloques con registros  en disco
	 */
	RecursoDeAlmacenamiento* RecursoDeAlmacenamientoEnArchivo(std::string estrategiaAlmacenamiento,int tamanio);
	 /**
	   * recurso de almacenamiento para guardar en archivos de texto en buffer
	  */
	RecursoDeAlmacenamiento* RecursoDeAlmacenamientoEnBuffer(std::string estrategiaAlmacenamiento,int tamanio);
	 /**
	  * recurso de almacenamiento para guardar en archivos con registros y en bloques con registros
	  *  en buffer y en disco
	*/
	RecursoDeAlmacenamiento* RecursoDeAlmacenamientoEnArchivoConBuffer(std::string estrategiaAlmacenamiento,int tamanio);
};

#endif /* FABRICADERECURSOSDEALMACENAMIENTO_H_ */
