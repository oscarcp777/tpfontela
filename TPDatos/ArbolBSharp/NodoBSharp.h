/*
 * NodoBMas.h
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */
#include "NodoRegistro.h"

#ifndef NODOBSHARP_H_
#define NODOBSHARP_H_

// Clase Nodo B+
class NodoBSharp{
    public:
	   NodoBSharp();
	   NodoBSharp(unsigned char cantClavesPorNivel);
	   NodoBSharp* getRama(unsigned char posRama);
	   NodoRegistro* getNodoRegistro(unsigned char posClave);
	   void setCuentas(int cuentas);
	   int getCuentas();
	   void setRama(unsigned char posRama,NodoBSharp*rama);
	   void setNodoRegistro(unsigned char posClave,NodoRegistro* nodoRegistro);
	   void setHoja(NodoBSharp* hoja);
	   NodoBSharp*getHoja();
	   ~NodoBSharp();

	private:
	  NodoRegistro* nodosRegistros[5];
	  NodoBSharp* ramas[5];
	  NodoBSharp *shojas;
	  int cuentas;
};

#endif /* NODOBMAS_H_ */
