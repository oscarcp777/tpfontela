/*
 * TestBuffer.cpp
 *
 *  Created on: 12/10/2009
 *      Author: oscar
 */
#include <iostream>
#include "../Almacenamiento/Buffer.h"
#include "../utils/StringUtils.h"
#include <stdio.h>
using namespace std;

int main6() {
	char* datos;
	Buffer* unBuffer = new Buffer();
	Buffer* otroBuffer = new Buffer();

	unBuffer->guardar("Santiago Donikian|86457|31897362\n");
	unBuffer->guardar("Richard Dubini|85440|31440400\n");

	otroBuffer->guardar("Santiago Donikian|86457|31897362",50);
	otroBuffer->guardar("Richard Dubini|85440|31440400",50);

	//while leer comun
	//TODO IMPRIME LOS BARRA N "\n" HACER ALGO CON ESO
	while(!unBuffer->fin()){
		cout<<"contenido unBuffer: "<<unBuffer->leer()<<endl;
	}


	//while leer con tamanio indicado
	while(!otroBuffer->fin()){
		otroBuffer->leer(datos,50);
		cout<<"contenido otroBuffer: "<<datos<<"#FIN#"<<endl;
}
	otroBuffer->cerrar();
	unBuffer->cerrar();
	return 0;

}
