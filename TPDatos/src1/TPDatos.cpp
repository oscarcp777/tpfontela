/*
 * main.cpp
 *
 *  Created on: 29/10/2009
 *      Author: richy
 */
#include "Pruebas/Pruebas.h"
#include "test/AbstractTest.h"
#include "test/TestGuardarComoArchivoRegistros.h"
#include "test/TestGuardarComoArchivoTexto.h"
#include "test/TestGuardarComoArchivoBloques.h"
#include "test/TestBusquedaArchivoTexto.h"
#include "test/TestBusquedaArchivoRegistros.h"
#include "test/TestBusquedaArchivoBloques.h"
#include "test/TestRegistrosEnBuffer.h"
#include "test/TestBloquesEnBuffer.h"
#include "test/TestTextoEnBuffer.h"
#include "test/TestEliminarComponenteArchivoTexto.h"
#include "test/TestEliminarComponenteArchivoRegistros.h"
#include "test/TestEliminarComponenteArchivoBloques.h"
#include "test/TestActualizarRegistroArchivoBloques.h"
#include "test/TestActualizarRegistroArchivoTexto.h"
#include "test/TestActualizarRegistroArchivoRegistros.h"
using namespace std;

void imprimirOrdenPruebas(){
	cout<<"1: Guardar un archivo con registros fijos"<<endl;
	cout<<"2: Guardar un archivo de texto"<<endl;
	cout<<"3: Guardar un archivo de bloques con registros variables"<<endl;
	cout<<"4: Busqueda en archivo de texto"<<endl;
	cout<<"5: Busqueda en archivo con registros fijos"<<endl;
	cout<<"6: Busqueda en archivo de bloques con registros variables"<<endl;
	cout<<"7: Busqueda de registros fijos en Buffer"<<endl;
	cout<<"8: Busqueda de bloques con registros variables en Buffer"<<endl;
	cout<<"9: Busqueda Texto Buffer"<<endl;
	cout<<"10: Eliminar Componente de archivo de texto"<<endl;
	cout<<"11: Eliminar Componente  de archivo con registros fijos"<<endl;
	cout<<"12: Eliminar Componente  de archivo de bloques con registros variables"<<endl;
	cout<<"13: Modificar Componente  de archivo de bloques con registros variables"<<endl;
	cout<<"14: Modificar Componente  de archivo de texto"<<endl;
	cout<<"15: Modificar Componente  de archivo de registros"<<endl;
}

AbstractTest* seleccionarTest(int numPrueba){

	switch(numPrueba){

	case 1:
		return new TestGuardarComoArchivoRegistros();
		break;

	case 2:
		return new TestGuardarComoArchivoTexto();
		break;

	case 3:
		return new TestGuardarComoArchivoBloques();
		break;

	case 4:
		return new TestBusquedaArchivoTexto();
		break;

	case 5:
		return new TestBusquedaArchivoRegistros();
		break;

	case 6:
		return new TestBusquedaArchivoBloques();
		break;

	case 7:
		return new TestRegistrosEnBuffer();
		break;

	case 8:
		return  new TestBloquesEnBuffer();
		break;

	case 9:
		return new TestTextoEnBuffer();
		break;

	case 10:
		return new TestEliminarComponenteArchivoTexto();
		break;

	case 11:
		return new TestEliminarComponenteArchivoRegistros();
		break;

	case 12:
		return new TestEliminarComponenteArchivoBloques();
		break;
	case 13:
			return new TestActualizarRegistroArchivoBloques();
			break;
	case 14:
			return new TestActualizarRegistroArchivoTexto();
			break;
	case 15:
			return new TestActualizarRegistroArchivoRegistros();
			break;
	default :
		cout<<"NUMERO DE PRUEBA INVALIDO"<<endl;
		return NULL;

	}
}


int main(){

	int numPrueba;
	cout<<"Ingrese el numero de la prueba seleccionada:"<<endl;
	imprimirOrdenPruebas();
	cin>>numPrueba;
	AbstractTest* test=seleccionarTest(numPrueba);
	test->ejecutarTest();
	return 0;

}
