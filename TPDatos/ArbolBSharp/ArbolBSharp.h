/*
 * ArbolBSharp.h
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */
#include "NodoRegistro.h"
#include "NodoBSharp.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#ifndef _ARBOLBSHARP_H_
#define _ARBOLBSHARP_H_

class ArbolBSharp {
  public:
	ArbolBSharp(int cantClaves);
	~ArbolBSharp();
	void refrescar ();
	void insertar (NodoRegistro* clave);
	void empujar (NodoRegistro* clave, NodoBSharp *nodo);
	void meterHoja();
	bool arbolVacio(NodoBSharp *nodo);
	void dividir ();
	void doblar (NodoBSharp *mde);
	//imprime el arbol en orden por la referencia de la raiz
	void print_rec ();
	void print_rec_aux (NodoBSharp *nodo);//auxiliar
	bool buscarNodo (NodoRegistro* clave, NodoBSharp *nodo);
	bool buscar (NodoRegistro* clave, NodoBSharp *nodo);
	//busca si una clace existe o no en el arbol
	bool buscar (NodoRegistro* clave);
	//da la altura
	int  Altura ();
	//imprime en anchura
	void Anchura();
	void Anchura_aux (NodoBSharp *, int , int);
	//imprime por niveles auxiliar de anchura aux
	void ImprimeNivel(NodoBSharp *, int);
	//imprime por la referencia de orden
	void Imprimir ();
	//carga el archivo de productos
	void Cargar();

	/***********  Recorridos **************************/

	void postOrdenRecursivo(NodoBSharp *r);
	void postOrdenIterativo(NodoBSharp *r);
	void preOrdenRecursivo(NodoBSharp *r);
	void preOrdenIterativo(NodoBSharp *r);

	void postOrdenRecursivoAux(NodoBSharp *r);
	void postOrdenIterativoAux(NodoBSharp *r);
	void preOrdenRecursivoAux(NodoBSharp *r);
	void preOrdenIterativoAux(NodoBSharp *r);

	//bool buscarNodo (int clave, NodoBmas *pagina);
	bool Buscar (int clave);
	//elimina al archivo
	void Eliminar(int);
	//ve si c esta en el archivo
	int Esta(int c);
	NodoRegistro* Encontrar(int c);

	bool EstaArreglo(int num);
	void ImprimirArreglo();

  private:
	NodoBSharp *raiz, *Xr, *P, *N, *vsam;
	int k, cuentas, MAX, MIN, nivel,cantClaves;
	NodoRegistro* mediana;
	bool esta, ea;
	double contT, contTot;
	int eli;
	int arreglo[50];
	//bandera es del archivo maestro, y bandera2
    int bandera, bandera2;

    void asignarMaxMin();

};

#endif /* ARBOLBSHARP_H_ */
