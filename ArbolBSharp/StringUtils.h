/*
 * StringUtils.h
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */

#include <string>

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_
#include <stdio.h>
#include <stdlib.h>
typedef char byte;
using namespace std;
class StringUtils{

	public:
			static byte* stringToArray(string cadena);
			static string arrayToString(byte array[],int tamanioArray);
			static void vecTovec(byte array[],int pos1,byte otroArray[],int pos2,int tamanio);


};

#endif /* STRINGUTILS_H_ */
