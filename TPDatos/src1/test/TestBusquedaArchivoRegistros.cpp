/*
 * TestBusquedaArchivoRegistros.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestBusquedaArchivoRegistros.h"

TestBusquedaArchivoRegistros::TestBusquedaArchivoRegistros() {
	// TODO Auto-generated constructor stub

}

TestBusquedaArchivoRegistros::~TestBusquedaArchivoRegistros() {
	// TODO Auto-generated destructor stub
}
void TestBusquedaArchivoRegistros::ejecutarTest(){
	/**
			 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
			 */
			FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

			/**
			 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
			 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
			 */
			Alumno* alumno = new Alumno();

			RecursoDeAlmacenamiento* recurso=
					fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("./","archivoRegistros");


			std::list<Componente*> listaAlumnos;
			list<Componente*>::iterator iter;

			recurso->buscar(listaAlumnos,alumno,"Nombre=Perez");
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
