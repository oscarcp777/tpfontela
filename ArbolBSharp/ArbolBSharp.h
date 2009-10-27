/*
 * ArbolBSharp.h
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */


#include <stdio.h>
#include <string.h>
#include <iostream>

#include "Excepciones/Exception.h"
#include "Indice/RegistroIndice.h"
#include "Nodo.h"
#include "NodoHoja.h"
#include "NodoInterno.h"
#include "BloqueUtils.h"
#include "ArchivoEnBloques.h"
#include "Constantes.h"

#ifndef _ARBOLBSHARP_H_
#define _ARBOLBSHARP_H_

using namespace std;



class ArbolBSharp {
  public:
	ArbolBSharp();
	~ArbolBSharp();
	void abrir();
	void cerrar();
	RegistroIndice buscarTermino(string termino);
	void modificarRegistro(RegistroIndice registro);
	void insertar(RegistroIndice registro);
	void mostrarArbol();



  private:
	Nodo insert(RegistroIndice registro,Nodo nodoLeido,Nodo nodoPadre);
	int cuantoOverflow(Nodo nodoModificado,int tipo);
	bool hayOverflowHoja(byte buffer[] );
	bool hayOverflowNodo(byte buffer[]);
	Nodo balancear(Nodo nodoModificado,Nodo nodoPadre, Nodo nodoLeido);
	Nodo partirRaiz(Nodo nodoModificado);
	Nodo balancearConVecino(Nodo nodoModificado, Nodo nodoPadre, int bloqueVecino,int tipo,int cantidad);
	byte* distibuirIzquierda(Nodo nodoModificado, Nodo nodoVecino, Nodo nodoPadre,int cantidad,int* tamanioBufferRetorno);
	byte* distibuirDerecha(Nodo nodoModificado, Nodo nodoVecino, Nodo nodoPadre,int cantidad,int* tamanioBufferRetorno);
	byte* split(Nodo nodoIzquierdo, Nodo nodoDerecho,Nodo nodoPadre,int* tamanioBufferRetorno);
	bool estaLleno(Nodo nodoVecino, int cantidad,RegistroIndice registro[],int cantRegistros);
	int buscarVecinoDerecho(Nodo nodoPadre, Nodo nodoLeido);
	int buscarVecinoIzquierdo(Nodo nodoPadre, Nodo nodoLeido);
	Nodo obtenerHojaDelTermino(string termino, int bloque);
	void crear();
	void mostrar(Nodo nodo);

	ArchivoEnBloques* archivo;
};


#endif /* ARBOLBSHARP_H_ */
