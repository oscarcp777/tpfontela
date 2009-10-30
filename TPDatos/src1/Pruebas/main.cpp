/*
 * main.cpp
 *
 *  Created on: 29/10/2009
 *      Author: richy
 */
#include "Pruebas.h"
#include <stdio.h>

using namespace std;

int main(){
	Pruebas* prueba = new Pruebas();
	int numPrueba;
	cout<<"Ingrese el numero de la prueba seleccionada:"<<endl;
	prueba->imprimirOrdenPruebas();
	cin>>numPrueba;
	prueba->seleccionarTest(numPrueba);

	return 0;

}
