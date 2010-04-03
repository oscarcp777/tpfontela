/*
 * Hash.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */
#include "Hash2.h"

int hash(int key, int depth){

	//TODO funcion fruta buscar una buena
	if (key % 2 == 1) key++;

	return key%19937;
}

int makeAddress(int key, int depth){
	int retVal = 0;
	int mask = 1;
	int hashVal = hash(key,depth);

	//invierte la serie de bits ejemplo 0001 1101 lo convierte en 1011 1000 y extrae una parte (el tamaño lo define depth)
	//es para distinguir entre los buckets
	for(int j = 0; j<depth; j++){
		retVal = retVal << 1;
		int lowbit = hashVal & mask;
		retVal = retVal | lowbit;
		hashVal = hashVal >> 1;
	}
	return retVal;

}
