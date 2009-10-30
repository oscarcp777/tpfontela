/*
 * TestBusquedaArbolBSharp.cpp
 *
 *  Created on: 29-oct-2009
 *      Author: Santiago
 */

#include "../Estrategy/IndexadoBSharp.h"



const int bTreeSize = 4;

int main(){
	IndexadoBSharp bt(bTreeSize,4);
	char nArch[]="testbt.dat";
	char ruta[]="../files/";

	bt.abrir(nArch,ruta);

	int resultado = bt.buscar("A");
	if(resultado == 20)
		cout<<"BUSQUEDA PERFECTA CAPO!!"<<endl;
	else
		cout<<"El resultado dio: "<<resultado<<endl;
	bt.close();

return 1;
}
