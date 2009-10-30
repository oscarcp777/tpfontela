/*
 * TestBusquedaArbolBSharp.cpp
 *
 *  Created on: 29-oct-2009
 *      Author: Santiago
 */

#include "../Estrategy/IndexadoBSharp.h"



const int bTreeSize = 4;

int main545(){
	IndexadoBSharp bt(bTreeSize,4);
	char nArch[]="testbt.dat";
	char ruta[]="../files/";
    string valor="A";
	bt.abrir(nArch,ruta);

	int resultado = 0;//bt.buscar((=valor.c_str());
	if(resultado == 20)
		cout<<"BUSQUEDA PERFECTA CAPO!!"<<endl;
	else
		cout<<"El resultado dio: "<<resultado<<endl;
	bt.close();

return 1;
}
