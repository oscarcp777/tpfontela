/*
 * TestBusquedaSecuencialBloques.cpp
 *
 *  Created on: 12/10/2009
 *      Author: oscar
 */
#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
#include <vector>
#include "../utils/StringUtils.h"
using namespace std;

int main90() {

	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,55);

		recurso->leerArchivo("../TPDatos/files/","Bloques");
		Alumno* alumno = new Alumno();
		recurso->busquedaSecuencial(alumno,"85440");
		std::cout<<"resultados busqueda: "<<std::endl;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"padron: "<<alumno->getPadron()<<std::endl;
	delete recurso;
	delete fabricaDeRecursos;
	return 0;


}
