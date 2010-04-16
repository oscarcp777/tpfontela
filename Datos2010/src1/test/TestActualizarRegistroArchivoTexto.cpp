/*
 * TestActualizarRegistroArchivoTexto.cpp
 *
 *  Created on: 02/11/2009
 *      Author: richy
 */

#include "TestActualizarRegistroArchivoTexto.h"

TestActualizarRegistroArchivoTexto::TestActualizarRegistroArchivoTexto() {
	// TODO Auto-generated constructor stub

}

TestActualizarRegistroArchivoTexto::~TestActualizarRegistroArchivoTexto() {
	// TODO Auto-generated destructor stub
}
void TestActualizarRegistroArchivoTexto::ejecutarTest(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */

		Alumno* alumnoModificar = new Alumno(31850139,"Garcia raul",86531);
		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoTexto");

		std::list<Componente*> listaAlumnos;
		list<Componente*>::iterator iter;

		recurso->modificion(alumnoModificar);

		recurso->cerrar();
		delete alumnoModificar;
		delete recurso;
		delete fabricaDeRecursos;

}
