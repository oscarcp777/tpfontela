/*
 * TestEliminarComponenteArchivoTexto.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestEliminarComponenteArchivoTexto.h"

TestEliminarComponenteArchivoTexto::TestEliminarComponenteArchivoTexto() {
	// TODO Auto-generated constructor stub

}

TestEliminarComponenteArchivoTexto::~TestEliminarComponenteArchivoTexto() {
	// TODO Auto-generated destructor stub
}
void TestEliminarComponenteArchivoTexto::ejecutarTest(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
	Alumno* alumno = new Alumno(31993745,"Santy Donikian",85689);

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoTexto");


	recurso->baja(alumno);


	recurso->cerrar();
	delete alumno;
	delete recurso;
	delete fabricaDeRecursos;

}
