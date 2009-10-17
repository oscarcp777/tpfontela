/*
 *  main.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */

#include "ArbolBSharp.h"
#include <sstream>
#include <stdlib.h>
using namespace std;
// Main
int main(){
	ArbolBSharp* H=new ArbolBSharp(5); //observacion: ingresar una cantidad impar, empezando por el 3. Ej: 3, 5, 7, 11...
	NodoRegistro* temp;

	int i=10;

	while (i>0){
		temp = new NodoRegistro();
		temp->setClaveRegistro(i);
		temp->setPosicionRegistro(i*2);
		H->insertar(temp);
		i--;
	}
    cout<<endl;
    H->Anchura();
    cout<<endl;
    H->Imprimir();
    cout<<endl;
    cout << "La altura del arbol b+ es: "<<H->Altura()<< endl;
    cout << "Posicion del registro con clave 4:"<<H->Encontrar(59)->getPosicionRegistro() << endl;
    cout<<endl;
    delete(H);
    return 0;
}


