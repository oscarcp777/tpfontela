/*
 * TestBusquedaSecuencialBloquesBuffer.cpp
 *
 *  Created on: 27/10/2009
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

int main987(){

	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
	Alumno* alumno = new Alumno();
	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,55,"padron",alumno1);



	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);

	cout << endl;
	cout << "Buffer guardado" << endl;

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

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
