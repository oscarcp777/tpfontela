/*
 * TestBusquedaSecuencialRegistros.cpp
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
#include <vector>
#include <list>
#include "../utils/StringUtils.h"
using namespace std;

int main456() {
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */
	    Alumno* alumno = new Alumno();
		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_REGISTROS,500,
									"../TP0Datos/files/","archivoRegistros","padron",INDEXADO_BSHARP,alumno);

			std::list<Componente*> listaAlumnos;
			list<Componente*>::iterator iter;


			recurso->buscar(listaAlumnos,alumno,"85440");
			iter = listaAlumnos.begin();


			while(iter != listaAlumnos.end()){
				alumno = (Alumno*) *iter;
				std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
				std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
				std::cout<<"padron: "<<alumno->getDni()<<std::endl;
				iter++;
			}

			delete recurso;
			delete fabricaDeRecursos;
			return 0;
}


