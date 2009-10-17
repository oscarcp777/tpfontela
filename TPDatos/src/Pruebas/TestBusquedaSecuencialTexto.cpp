/*
 * TestBusquedaSecuencialTexto.cpp
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
#include "../utils/StringUtils.h"
using namespace std;

int main() {
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */

		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_TEXTO);


		recurso->leerArchivo("../TP0Datos/files/","archivoTexto");
		Alumno* alumno = new Alumno();
		recurso->busquedaSecuencial(alumno, "86534");

		std::cout<<std::endl;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"padron: "<<alumno->getPadron()<<std::endl;
		/**
		 * el metodo toString lo implementan todos los que hereden de object entonces
		 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
		 * la fabrica
		 */


		delete recurso;
		delete fabricaDeRecursos;
		return 0;
}
