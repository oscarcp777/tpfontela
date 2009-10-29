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

int main534(){

	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	Alumno* alumno = new Alumno();

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoBloques");

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"DNI=44850139");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
		std::cout<<"padron: "<<alumno->getDni()<<std::endl;
		std::cout<<std::endl;
		iter++;
	}

	delete recurso;
	delete fabricaDeRecursos;
	return 0;


}
