/*
 * GuardarEnBloquesArchivo.cpp
 *
 *  Created on: 11/10/2009
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

int main() {
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
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,120,
									"../TPDatos/files/","archivoBloques","padron",INDEXADO_BSHARP,alumno);

	Alumno* alumno1 = new Alumno(31993745,"Santy",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
	Alumno* alumno4 = new Alumno(93850169,"Rodrigo Perez",80000,8,7,4);
	Alumno* alumno5 = new Alumno(93853439,"Daniel Sivori",86524,8,7,4);
	Alumno* alumno6 = new Alumno(93850139,"Perez",84029,8,7,4);
	Alumno* alumno7 = new Alumno(31850139,"Garcia",86531,8,7,4);
	Alumno* alumno8 = new Alumno(44850139,"Oscar Rigeri",86934,8,7,4);
	Alumno* alumno9 = new Alumno(10850139,"Garcia",86745,8,7,4);
	Alumno* alumno10 = new Alumno(2385013,"Don",87890,8,7,4);


	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);
	recurso->alta(alumno4);
	recurso->alta(alumno5);
	recurso->alta(alumno6);
	recurso->alta(alumno7);
	recurso->alta(alumno8);
	recurso->alta(alumno9);
	recurso->alta(alumno10);
	cout<<std::endl<< "Archivo guardado" << endl;





	/**
	 * el metodo toString lo implementan todos los que hereden de object entonces
	 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
	 * la fabrica
	 */

	delete alumno1;
	delete alumno2;
	delete alumno3;
	delete alumno4;
	delete alumno5;
	delete alumno6;
	delete alumno7;
	delete alumno8;
	delete alumno9;
	delete alumno10;
	delete recurso;
	delete fabricaDeRecursos;
	return 0;
}
