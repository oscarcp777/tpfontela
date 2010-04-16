/*
 * TestActualizarRegistroArchivoRegistros.cpp
 *
 *  Created on: 02/11/2009
 *      Author: richy
 */

#include "TestActualizarRegistroArchivoRegistros.h"

TestActualizarRegistroArchivoRegistros::TestActualizarRegistroArchivoRegistros() {
	// TODO Auto-generated constructor stub

}

TestActualizarRegistroArchivoRegistros::~TestActualizarRegistroArchivoRegistros() {
	// TODO Auto-generated destructor stub
}
void TestActualizarRegistroArchivoRegistros::ejecutarTest(){
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno(93850139,"Oscar Caceres",86534);
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoRegistros");

	recurso->modificion(alumno);
	recurso->cerrar();
	delete alumno;
	delete recurso;
	delete fabricaDeRecursos;

}
