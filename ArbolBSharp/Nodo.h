/*
 * Nodo.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include <stdio.h>
#include "StringUtils.h"

#ifndef NODO_H_
#define NODO_H_

typedef char byte;

class Nodo{

	public:
			Nodo();
			Nodo(byte buffer[], int bloque, int nivel, int tamanioBuffer);
			int getNivel();
			int getBloque();
			byte* getBuffer();
			int getTamanioBuffer();
			void setBloque(int bloque);
			void setBuffer(byte buffer[],int tamanioBuffer);
			void setNivel(int nivel);
			~Nodo();

	private:
			byte* buffer;
			int bloque;
			int nivel;
			int tamanioBuffer;
};

#endif /* NODO_H_ */
