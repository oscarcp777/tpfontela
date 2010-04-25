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


void TestFreeBlockController::runFreeBlockControllerTest(){

		FreeBlockList list(20);
		string ruta="files/prueba";
		list.create(ruta,ios::out);
		list.add(1);
		list.add(8);
		list.add(12);
		list.add(5);
		list.add(9);
		list.add(22);
		list.add(10);
		list.add(100);
		list.add(2);
		list.add(55);

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
