/*
 * NodoInterno.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */
#include <list>
#include "Nodo.h"
#include "Elemento.h"
#include "BloqueUtils.h"
#include "Constantes.h"

#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

class NodoInterno: public Nodo{
	public:
			NodoInterno();
			NodoInterno(byte buffer[], int bloque, int nivel, int tamanioBuffer);
			static int obtenerBloque(byte buffer[],string termino);
			Elemento* obtenerElementos();
			int getCantidadElementos(); //se guarda en la primera posicion del buffer
			static byte* obtenerBytesString(byte buffer[], int desde, int hasta);
			static byte* obtenerByteArrayElementos(Elemento elementos[], int cantElementos, int* cantElementosBuffer);
			static byte* completarBuffer(byte buffer[],int* tamanioBuffer);
			static Elemento* eliminarPrimerElemento(Elemento elementos[],int cantidadElementos);
			static Elemento* agregarElementoAlFinal(Elemento elementos[], Elemento elemento,int cantElementos);
			static int obtenerElementoaIzquierda(Elemento elementos[], Elemento elemento,int cantElementos);
			static list<Elemento*> dividirElementos(Elemento elementos[],int partes,int cantElementos);
			static Elemento* eliminarUltimoElemento(Elemento elementos[],int* cantElementos);
			static Elemento* agregarElementoAlComienzo(Elemento elementos[], Elemento elemento,int cantElementos);
			static int obtenerElementoaDerecha(Elemento elementos[], Elemento elemento,int cantElementos);
			static Elemento* agregarElemento(Elemento elementos[], int indice, Elemento elemento,int* cantElementos);
			static Elemento* unir(Elemento elementosIzquierdo[], int cantElementosIzq, Elemento elementosDerecho[], int cantElementosDer, Elemento elementoPadre);

};

#endif /* NODOINTERNO_H_ */
