/*
 * IndexadoBSharp.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef INDEXADOBSHARP_H_
#define INDEXADOBSHARP_H_

#include "EstrategiaIndice.h"
#include "NodeBSharp.h"


#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
class IndexadoBSharp: public EstrategiaIndice {
public:
	IndexadoBSharp(int orden, int tamanioLlave);
	virtual ~IndexadoBSharp();

	int abrir();
	int crear(char* nombre, char* ruta);
	int cerrar();
	int insertar(char* key, int dir);
	int remover(char* key, int dir=-1);
	int buscar(char* key, int dir=-1);

	void imprimir(ostream &);
	void imprimir(ostream &, int dirNodo, int nivel);

protected:


	NodeBSharp raiz;
	int profundidad;
	int orden;
	int cantidadNodos;
	int tamanioMetadata;
	NodeBSharp** nodos; //nodos disponibles
	//nodos[1] es nivel 1, etc (ver buscarHoja)
	int tamanioRegistro;

	int tamanioLlave;

	NodeBSharp* buscarHoja(char* key);  //FindLeaf
	NodeBSharp* nuevoNodo();
	NodeBSharp* leerNodo(int dir); 		//Fetch
	int escribirNodo(NodeBSharp* nodo); //Store
	int escribirProfundidad(char* buffer);
	int leerProfundidad(char* buffer);
};

#endif /* INDEXADOBSHARP_H_ */
