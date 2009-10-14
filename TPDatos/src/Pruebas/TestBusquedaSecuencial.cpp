/*
 * TestBusquedaSecuencial.cpp
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
#include <vector>
#include "../utils/StringUtils.h"
using namespace std;
void pruebaParseo(){
	vector<string> tokens;
	  string linea="93850139  |oscar caceres|84939|capital";
	  StringUtils::Tokenize(linea,tokens,"|");
	  vector<string>::iterator the_iterator;
	   	string valor ;
	   	the_iterator = tokens.begin();
	   	while( the_iterator != tokens.end() ) {
	   		valor = *the_iterator;
	   		++the_iterator;
	     cout<<"datos :"<<valor<<endl;
	   	}

}

int main3() {
          //  pruebaParseo();

/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,55);

	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);

	recurso->leerArchivo("/home/richy/","archivoBloques1");
	recurso->busquedaSecuencial(alumno1, "hola");
	cout << "Archivo guardado" << endl;
	/**
	 * el metodo toString lo implementan todos los que hereden de object entonces
	 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
	 * la fabrica
	 */


	delete recurso;
	delete fabricaDeRecursos;
	return 0;


}
