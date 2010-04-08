/*
 * Hashing.h
 *
 *  Created on: 08/11/2009
 *      Author: santiago
 */

#ifndef HASHING_H_
#define HASHING_H_

#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include <stdexcept>
#include <stdio.h>
#include "RegistroClaveHash.h"
//#include "Tabla.h"

class Hashing {
public:
	fstream* fileTabla;
		fstream* fileCubos;
		int tamanioTabla;
		int cantCubos;
		int ultimoCubo;
		Tabla tabla;

		Hashing();
		void Crear(string *filePathName) throw (exception);
	    void Abrir(string *filePathName) throw (exception);
	    Tabla GetTabla();
	    void SaveTabla() throw (exception);
	    //Cubo GetCubo();
	    //void SaveCubo() thrown (exception);
	    void Cerrar() throw (exception);
	    void AddClave(RegistroClaveHash* clave) throw (exception);
	    //bool ModificarClave(RegistroClaveHash Clave, Registro* registro) throw (exception); //ver esto
	    RegistroClaveHash ObtenerRegistro(string* clave) throw (exception);
	    void Imprimir(int offset);
	    list<string>* RecorrerOrdenado();
	virtual ~Hashing();
};

#endif /* HASHING_H_ */
