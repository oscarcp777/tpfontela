/*
 * TestFreeBlockController.cpp
 *
 *  Created on: 25/04/2010
 *      Author: Richard
 */

#include "TestFreeBlockController.h"

TestFreeBlockController::TestFreeBlockController() {

}

TestFreeBlockController::~TestFreeBlockController() {
}

/**
 * Test que evalúa el funcionamiento general del FreeBlockController, hace un numero n de adds y pide n+1
 * gets para comprobar que se devuelven todos los bloques y que luego se devuelve -1
 *
 */
void TestFreeBlockController::runGeneralTest(){

	FreeBlockController list(20);
	string ruta="files/prueba";
	list.create(ruta,ios::out);
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.add(6);
	list.add(7);
	list.add(8);
	list.add(9);
	list.add(10);
	list.add(11);
	list.add(12);
	list.add(13);
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	list.add(14);
	list.add(15);
	list.add(16);
	list.add(17);
	list.add(18);
	list.add(19);
	list.add(20);
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	list.close();
}

/**
 * Testea el método add del controlador de bloques libres
 */
void TestFreeBlockController::runAddTest(){

	FreeBlockController list(20);
	string ruta="files/prueba";
	list.create(ruta,ios::out);
	list.add(1); list.add(2); list.add(3); list.add(4); list.add(5); list.add(6);
	list.add(7); list.add(8); list.add(9); list.add(10); list.add(11); list.add(12);
	list.add(13); list.add(14); list.add(15); list.add(16); list.add(17); list.add(18);
	list.close();
}

/**
 * Testea el método get del controlador y verifica la correcta recuperación de la estructura luego de
 * abrirse un archivo existente
 */
void TestFreeBlockController::runGetTest(){

	FreeBlockController list(20);
	string ruta="files/prueba";
	list.open(ruta,ios::out);
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;

	cout << "Direcciones restantes: "<<list.getSize()<<endl;

	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	cout<<"Obtengo Bloque numero: "<<list.get()<<endl;
	list.close();
}


