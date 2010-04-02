/*
 * Hash.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */
#include "Hash.h"

int hash(char* key){
	int sum = 0;
	int len = strlen(key);
	if(len % 2 == 1) len++;

	//funcion de hash que propone en el libro, esta funcion se cambia adaptandola a nuestra conveniencia
	for(int j=0 ; j<len ; j+=2)
			sum = (sum + 100* key[j] + key[j+1]) % 19937;

	return sum;


}

int makeAddress(char* key, int depth){
	int retVal = 0;
	int mask = 1;
	int hashVal = hash(key);

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
