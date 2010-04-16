/*
 * TestEliminarComponenteArchivoBloques.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestEliminarComponenteArchivoBloques.h"

TestEliminarComponenteArchivoBloques::TestEliminarComponenteArchivoBloques() {
	// TODO Auto-generated constructor stub

}

TestEliminarComponenteArchivoBloques::~TestEliminarComponenteArchivoBloques() {
	// TODO Auto-generated destructor stub
}
void TestEliminarComponenteArchivoBloques::ejecutarTest(){
	Alumno* alumno = new Alumno(31993745,"Santy",85689);
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoBloques");

	recurso->baja(alumno);
	recurso->cerrar();
	delete alumno;
	delete recurso;
	delete fabricaDeRecursos;

}
