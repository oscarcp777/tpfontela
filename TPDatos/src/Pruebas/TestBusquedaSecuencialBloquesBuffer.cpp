/*
 * TestBusquedaSecuencialBloquesBuffer.cpp
 *
 *  Created on: 21/10/2009
 *      Author: richy
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

int main() {

	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../files/","miBuffer");

		Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
		Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
		Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
		Alumno* alumno4 = new Alumno(31993745,"A",9,8,8,8);

		recurso->cargarComponente(alumno1);
		recurso->cargarComponente(alumno2);
		recurso->cargarComponente(alumno3);
		recurso->cargarComponente(alumno4);
		recurso->escribirArchivo("../files/","miBuffer");
		std::cout<<"Cargo bien los componentes. "<<std::endl;

		Alumno* alumno = new Alumno();
		recurso->busquedaSecuencial(alumno,"85689");
		std::cout<<"resultados busqueda: "<<std::endl;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"padron: "<<alumno->getPadron()<<std::endl;

	delete recurso;
	delete fabricaDeRecursos;
	return 0;


}

