/*
 * TestBusquedaSecuencialTextoBuffer.cpp
 *
 *  Created on: 12/10/2009
 *      Author: oscar
 */
#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
using namespace std;

int main54657() {
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();
	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_TEXTO,40,"padron");

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;


	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);

	//recurso->alta("../files/","archivoTexto");
	cout<<endl << "guardado en Buffer" << endl;

	recurso->buscar(listaAlumnos,alumno,"padron=85440|nombre=Oscar");
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
