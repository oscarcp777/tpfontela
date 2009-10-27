/*
 * StringUtils.cpp
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */

#include "StringUtils.h"

byte* StringUtils::stringToArray(string cadena){
	int tamanioCadena = strlen(cadena.c_str());
	byte* arreglo=new byte[tamanioCadena];
	int i;
	for(i=0;i<tamanioCadena-1;i++){
		arreglo[i]=cadena.substr(i,i+1);
	}

	return arreglo;
}

 string StringUtils::arrayToString(byte array[],int tamanioArray){
	int i;
	string cadena;

	for(i=0;i<tamanioArray;i++){
		cadena=cadena+array[i];
	}
	return cadena;
}

/**
 * Copia los primeros elementos definidos por tamanio del arreglo array en el arreglo otroArray.
 *
 */
 void StringUtils::vecTovec(byte array[],int pos1,byte otroArray[],int pos2,int tamanio){
	int i=0;

	for(;i<tamanio;i++){
		otroArray[i+pos2]=array[i+pos1];
	}

}

