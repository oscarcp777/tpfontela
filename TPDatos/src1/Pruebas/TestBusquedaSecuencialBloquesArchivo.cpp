/*
 * TestBusquedaSecuencialBloquesArchivo.cpp
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

int main6456(){

	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	Alumno* alumno = new Alumno();

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoBloques");

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"padron=85440|nombre=Oscar");
	iter = listaAlumnos.begin();

	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
		std::cout<<"padron: "<<alumno->getDni()<<std::endl;
		iter++;
	}

	delete recurso;
	delete fabricaDeRecursos;
	return 0;


}
