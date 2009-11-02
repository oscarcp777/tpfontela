/*
 * TestBusquedaArchivoBloques.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestBusquedaArchivoBloques.h"

TestBusquedaArchivoBloques::TestBusquedaArchivoBloques() {
	// TODO Auto-generated constructor stub

}

TestBusquedaArchivoBloques::~TestBusquedaArchivoBloques() {
	// TODO Auto-generated destructor stub
}
void TestBusquedaArchivoBloques::ejecutarTest(){
FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

//		Alumno* alumno = new Alumno();
//	Alumno* alumno = new Alumno(31440400,"Dubini",85440,6,6,7);
	Alumno* alumno = new Alumno(93853439,"Daniel Sivori",86524);
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoBloques");

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"Padron=85440");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"padron: "<<alumno->getPadron()<<std::endl;
		std::cout<<"dni: "<<alumno->getDni()<<std::endl;
		std::cout<<std::endl;
		iter++;
	}
    recurso->cerrar();
    delete alumno;
	delete recurso;
	delete fabricaDeRecursos;
	}
