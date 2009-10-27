/*
 * BloqueUtils.h
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */
#include <stdio.h>
#include <stdlib.h>
#include "Indice/RegistroIndice.h"

#ifndef BLOQUEUTILS_H_
#define BLOQUEUTILS_H_

typedef char byte;
using namespace std;

class BloqueUtils{
public:
	static byte* intToByteArray(int i);
	static int byteArrayToInt(byte b[], int offset);
	static byte* concatena(byte array[],byte otroArray[],int tamanio1,int* tamanio2);
	static byte* longToByteArray(long numero);
	static long byteArrayToLong(byte bytes[], int offset);
	static byte* doubleToBytearray(double data);
	static double bytearrayToDouble(byte data[],int tamanio);
	static RegistroIndice* obtenerBytes(byte cadenaCodificada[], int desde, int hasta);
};

#endif /* BLOQUEUTILS_H_ */
