/*
 * TestActualizarRegistroArchivoBloques.cpp
 *
 *  Created on: 02/11/2009
 *      Author: richy
 */

#include "TestActualizarRegistroArchivoBloques.h"

TestActualizarRegistroArchivoBloques::TestActualizarRegistroArchivoBloques() {
	// TODO Auto-generated constructor stub

}

TestActualizarRegistroArchivoBloques::~TestActualizarRegistroArchivoBloques() {
	// TODO Auto-generated destructor stub
}

void TestActualizarRegistroArchivoBloques::ejecutarTest(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		Alumno* alumno = new Alumno(31440400,"Dubini Pablo",85440);

		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoBloques");

		recurso->modificion(alumno);
	    recurso->cerrar();
	    delete alumno;
		delete recurso;
		delete fabricaDeRecursos;

}
