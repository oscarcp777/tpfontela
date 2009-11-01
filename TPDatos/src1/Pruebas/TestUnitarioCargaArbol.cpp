/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../Estrategy/IndexadoBSharp.h"



const char* keys="CSDTAMPIBWNGURKEHOLJYQZFXV";



const int bTreeSize = 4;

int main546756(){
	char letra[2] = "";
	char valor[5]="A";
	char* pchar=valor;
	IndexadoBSharp bt(bTreeSize,4);
	char nArch[]="testbt.dat";
	char ruta[]="../TP0Datos/files/";

	bt.crear(nArch,ruta);
	bt.abrir();

	for (int i = 0; i<26; i++){
		memcpy(letra,keys,sizeof(char));
		bt.insertar(letra,i);
		bt.imprimir(cout);
		keys++;

	}
	bt.cerrar();
	bt.abrir();
	int resultado = bt.buscar(pchar);
	if(resultado == 4)
		cout<<"BUSQUEDA PERFECTA CAPO!!"<<endl;
	else
		cout<<"El resultado dio: "<<resultado<<endl;
	bt.cerrar();

	return 1;
}
