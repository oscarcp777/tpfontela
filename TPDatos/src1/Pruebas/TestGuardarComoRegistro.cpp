/*
 * guardarComoRegistro.cpp
 *
 *  Created on: 11/10/2009
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

int main1() {
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_REGISTROS,40,
					"../TP0Datos/files/","archivoRegistros","padron",INDEXADO_BSHARP);

	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	//Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	//Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);

	recurso->alta(alumno1);
	//recurso->alta(alumno2);
	//recurso->alta(alumno3);

	cout << endl;
	cout << "Archivo guardado" << endl;

	delete recurso;
	delete fabricaDeRecursos;
	return 0;
}
