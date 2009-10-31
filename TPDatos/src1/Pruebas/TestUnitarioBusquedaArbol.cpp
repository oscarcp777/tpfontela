/*
 * TestUnitarioBusquedaArbol.cpp
 *
 *  Created on: 30-oct-2009
 *      Author: Santiago
 */

#include "../Estrategy/IndexadoBSharp.h"



const int bTreeSize = 4;

int main111(){
	IndexadoBSharp bt(bTreeSize,4);
	char nArch[]="testbt.dat";
	char ruta[]="../files/";
    char valor[5]="A";
    bt.setArchivo(nArch,ruta);
	bt.abrir();
    char* pchar=valor;
	int resultado = bt.buscar(pchar);
	if(resultado == 4)
		cout<<"BUSQUEDA PERFECTA CAPO!!"<<endl;
	else
		cout<<"El resultado dio: "<<resultado<<endl;
	bt.cerrar();

return 1;
}