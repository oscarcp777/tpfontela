/*
 * TestEliminarComponenteArchivoRegistros.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestEliminarComponenteArchivoRegistros.h"

TestEliminarComponenteArchivoRegistros::TestEliminarComponenteArchivoRegistros() {
	// TODO Auto-generated constructor stub

}

TestEliminarComponenteArchivoRegistros::~TestEliminarComponenteArchivoRegistros() {
	// TODO Auto-generated destructor stub
}
void TestEliminarComponenteArchivoRegistros::ejecutarTest(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
	Alumno* alumno = new Alumno(31993745,"Santy Donikian",85689);

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoRegistros");


	recurso->baja(alumno);


	recurso->cerrar();
	delete alumno;
	delete recurso;
	delete fabricaDeRecursos;

}
