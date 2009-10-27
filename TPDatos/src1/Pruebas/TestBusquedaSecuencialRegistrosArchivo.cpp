/*
 * TestBusquedaSecuencialRegistrosArchivo.cpp
 *
 *  Created on: 17/10/2009
 *      Author: richy
 */

#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
using namespace std;

int main1234() {
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
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoRegistros");


	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"padron=85440|nombre=Oscar");
					iter = listaAlumnos.begin();

	std::cout<<"Alumnos Encontrados: "<<std::endl;
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


