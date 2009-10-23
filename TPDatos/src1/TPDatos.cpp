////============================================================================
//// Name        : TPDatos.cpp
//// Author      : richy
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//#include "Object/Object.h"
//#include "utils/Define.h"
//#include "Composite/Componente.h"
//#include "Factory/FabricaDeRecursosDeAlmacenamiento.h"
//#include "Almacenamiento/RecursoDeAlmacenamiento.h"
//using namespace std;
//
//int main() {
//	/**
//	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
//	 */
//	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
//	/**
//	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
//	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
//	 */
//	RecursoDeAlmacenamiento* recurso=
//			fabricaDeRecursos->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_TEXTO,ARCHIVO,new Componente(100));
//
//	/**
//	 * el metodo toString lo implementan todos los que hereden de object entonces
//	 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
//	 * la fabrica
//	 */
//	cout << "VEO QUE CARGO LA FABRICA DE RECURSOS :" <<recurso->toString()<< endl;
//	cout << "!!!NOS VAN A ROMPER EL ORTO EN DATOS LALALA!!!" << endl; // prints !!!Hello World!!!
//	delete recurso;
//	return 0;
//}