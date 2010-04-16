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
	int modificar(char* key, int dir);
	int remover(char* key, int dir=-1);
	int buscar(char* key, int dir=-1);

	void imprimir(ostream &);
	void imprimir(ostream &, int dirNodo, int nivel);
	void imprimirArbol(ostream &);

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
	//int concatenarClaves(NodeBSharp* nodoHoja,NodeBSharp* nodoHojaVecino,NodeBSharp* nodoPadreHoja,char* keyRemovida);
	int actualizarSeparador(NodeBSharp* nodoPadre,char* keyNueva,char* keyAnterior,int dir);
	int colocarClaveOrdenadamente(char**keysNodo,int numKeys,char*keyAinsertar);
	int underflow(NodeBSharp* nodo,char* key);
	int actualizarIndexSet(char* keyVieja, char* keyNueva,bool escribirNodo);
	int eliminarIndexSet(char* key,NodeBSharp* nodoHoja,int nivelArbol,bool modificarDireccion,bool underflowNodoInterno);
	int resolverUnderflowNodoInterno(NodeBSharp* nodoAbuelo,NodeBSharp* nodoPadre, NodeBSharp* nodo, char* key);
	//char* obtenerClaveRedistribucion(NodeBSharp* nodo,char*keyABorrar);
	int redistribuirClaves(char*key,NodeBSharp* nodoPadre,NodeBSharp* nodo, NodeBSharp* nodoVecino/*,bool hasNodeFeal*/);
	int bajarUnNivel(int nivelInferiorNodo);
	void resolverUnderflowRaiz(NodeBSharp* nodoPadre,char* key);
	int concatenarNodos(char* key,NodeBSharp* nodoPadre,NodeBSharp* nodo, NodeBSharp* nodoVecino,bool hasNodeFeal);
	NodeBSharp* obtenerNodoVecino(NodeBSharp* nodoHoja, NodeBSharp* nodoPadreHoja, int indiceClave,bool underflowNodoInterno);
	int escribirNodo(NodeBSharp* nodo); //Store
	int escribirProfundidad(char* buffer);
	int leerProfundidad(char* buffer);
};

#endif /* INDEXADOBSHARP_H_ */
