/*
 * Pruebas.h
 *
 *  Created on: 29/10/2009
 *      Author: richy
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_
#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
#include <vector>
#include "../utils/StringUtils.h"

class Pruebas{

public:
	Pruebas();
	void imprimirOrdenPruebas();
	int testBusquedaSecuencialBloquesArchivo();
	int testBusquedaSecuencialBloquesBuffer();
	int testBusquedaSecuencialRegistrosArchivo();
	int testBusquedaSecuencialRegistrosBuffer();
	int testBusquedaSecuencialTextoArchivo();
	int testBusquedaSecuencialTextoBuffer();
	int testGuardarComoRegistroArchivo();
	int testGuardarComoTexoArchivo();
	int testGuardarEnBloquesArchivo();
	void seleccionarTest(int numPrueba);
};
#endif /* PRUEBAS_H_ */
