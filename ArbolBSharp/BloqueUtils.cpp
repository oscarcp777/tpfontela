/*
 * BloqueUtils.cpp
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */

/**
 * Retorna un byte[4] a partir de un entero (BigEndian)
 */
#include "BloqueUtils.h"

 byte* BloqueUtils::intToByteArray(int i) {
	byte* dword = new byte[4];
	dword[0] = (byte) ((i >> 24) & 0x000000FF);
	dword[1] = (byte) ((i >> 16) & 0x000000FF);
	dword[2] = (byte) ((i >> 8) & 0x000000FF);
	dword[3] = (byte) (i & 0x00FF);
	return dword;
}

/**
 * Convierte un byte array a int a partir de un offset dado
 *
 * @param b El byte array
 * @param offset El offset al array
 * @return El entero
 */
 int BloqueUtils::byteArrayToInt(byte b[], int offset) {
	int value = 0;
	int i;
	for (i = 0; i < 4; i++) {
		int shift = (4 - 1 - i) * 8;
		value += (b[i + offset] & 0x000000FF) << shift;
	}
	return value;
}

/**
 * Concatena dos byte array
 * @param array Primer byte array
 * @param otroArray Segundo byte array
 * @return Byte array
 */

 byte* BloqueUtils::concatena(byte array[],byte otroArray[],int tamanio1,int*tamanio2){
	int tamanioTotal = tamanio1+*tamanio2;
	tamanio2=&tamanioTotal;
	byte* concatenacion=new byte[tamanio1+*tamanio2];
	int i;
	for(i=0;i<tamanio1;i++){
		concatenacion[i]=array[i];
	}
	for(i=0;i<*tamanio2;i++){
		concatenacion[i]=otroArray[i];
	}
	return concatenacion;
}

/**
 * Retorna un byte[8] a partir de un long (Big Endian)
 * @param numero El long
 * @return byte[8]
 */


 byte* BloqueUtils::longToByteArray(long numero) {
	byte* dword = new byte[8];
	dword[0] = (byte) ((numero >> 56) & 0x00000000000000FF);
	dword[1] = (byte) ((numero >> 48) & 0x00000000000000FF);
	dword[2] = (byte) ((numero >> 40) & 0x00000000000000FF);
	dword[3] = (byte) ((numero >> 32) & 0x00000000000000FF);
	dword[4] = (byte) ((numero >> 24) & 0x00000000000000FF);
	dword[5] = (byte) ((numero >> 16) & 0x00000000000000FF);
	dword[6] = (byte) ((numero >> 8) & 0x00000000000000FF);
	dword[7] = (byte) (numero & 0x00000000000000FF);
	return dword;
}

/**
 * Convierte un byte array a long a partir de un offset dado
 * @param bytes Byte array a convertir
 * @param offset Offset al byte array
 * @return El long
 */

 long BloqueUtils::byteArrayToLong(byte bytes[], int offset){

	long primerParte= byteArrayToInt(bytes, offset);
	long segundaParte= byteArrayToInt(bytes, offset + 4);
	long value= primerParte  << 32;
	long value1= value + (segundaParte & 0xFFFFFFFFL);
	return value1;
}

/**
 * Retorna un byte[8] a partir de un double
 * @param data El double
 * @return byte[8]
 */

 byte* BloqueUtils::doubleToBytearray(double data) {
	return longToByteArray(long(data));
}

/**
 * Convierte un byte array a double
 * @param data Byte array a convertir
 * @return El double
 */
 double BloqueUtils::bytearrayToDouble(byte data[],int tamanio) {
	if (data == NULL || tamanio != 8) return 0x0;
	return double(byteArrayToLong(data,0));
}
//Esta de prueba, ver bien como se hace
 RegistroIndice* BloqueUtils::obtenerBytes(byte cadenaCodificada[], int desde, int hasta) {
	RegistroIndice* registroIndice = new registroIndice[hasta-desde+1];
	 int cant = hasta - desde + 1;
	byte* ret = new byte[cant];
	string valor;
	int i;
	int cant=0;
	for (i = 0; i < cant; i++) {
		ret[i] = cadenaCodificada[desde + i];
		cant++;
		valor = valor + ret[i];
		if(cant==10){
			RegistroIndice* registroIndice=new RegistroIndice();
			registroIndice->termino = valor;
			registroIndice->pesoGlobal = i;
			registroIndice[i]=*registroIndice;
		}
	}
	return registroIndice;
}
