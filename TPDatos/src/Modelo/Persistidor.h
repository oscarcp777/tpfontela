/*
 * Persistidor.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */
#include <iostream>
#include "../Composite/Dato.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"

#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

class Persistidor {
public:
	Persistidor();
	virtual ~Persistidor();
	static void guardar(std::string nombreArchivo,Dato* dato, std::string eAlmacenamiento);
	static void recuperar(std::string nombreArchivo,Dato* dato);
};

#endif /* PERSISTIDOR_H_ */
