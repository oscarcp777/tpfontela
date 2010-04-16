/*
 * NodeBSharp.h
 *
 *  Created on: 27/10/2009
 *      Author: richy
 */

#ifndef NODEBSHARP_H_
#define NODEBSHARP_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../utils/Define.h"
using namespace std;

class NodeBSharp {
public:
	NodeBSharp(int maxKeys, int tamanioLlave);
	virtual ~NodeBSharp();

	//Insertar y remover devuelven
		//0 para falla
		//-1 para overflow
		//1 para exito
	int insert(char* key, int dir);
	int remover(char* key, int dir = -1);

	char* claveMayor(); 						//retorna el valor de la clave mayor
	int split(NodeBSharp* nuevoNodo); 		//mover al nuevo nodo
	int merge(NodeBSharp* desdeNodo);		//mueve desde el nodo
	int actualizarKey(char* viejaKey, char* nuevaKey, int dir= -1);
	int serializar(char* buffer);
	int hidratar(char* buffer);
	int buscar(char* key, int dir = -1, int exacto = 1);
	void modificarDireccion(char* key,int dir);
	void imprimir(ostream &);
    int getNodoSiguiente() const
    {
        return nodoSiguiente;
    }

    void setNodoSiguiente(int nodoSiguiente)
    {
        this->nodoSiguiente = nodoSiguiente;
    }

    void clear(){
		this->numKeys = 0;
		this->dir = -1;
	}

    int getNumKeys() const
    {
        return numKeys;
    }

    void setNumKeys(int numKeys)
    {
        this->numKeys = numKeys;
    }

    int getMinKeys() const{
    	return (maxKeys-1)/2;
    }

    int *getDirecciones() const
    {
        return direcciones;
    }

    void setDirecciones(int *direcciones)
    {
        this->direcciones = direcciones;
    }

    char **getKeys() const
    {
        return keys;
    }

    void setKeys(char **keys)
    {
        this->keys = keys;
    }

    int getDir() const
	{
		return dir;
	}

	void setDir(int dir)
	{
		this->dir = dir;
	}


protected:
	int numKeys;
	char** keys;
	int *direcciones;
	int maxKeys;
	int tamanioLlave;


	int nodoSiguiente;   //direccion del siguiente nodo en el mismo nivel
	int dir;			 //direccion de este nodo en el archivo del arbol
	int minKeys;		 //minimo numero de keys en un nodo
	int maxBKeys;		 //maximo number de keys en un nodo

	int init();
	int encontrar(char* key, int dir = -1, int exacto = 1);

};

#endif /* NODEBSHARP_H_ */
