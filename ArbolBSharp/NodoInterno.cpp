/*
 * NodoInterno.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "NodoInterno.h"

NodoInterno::NodoInterno(){

}

NodoInterno::NodoInterno(byte buffer[], int bloque, int nivel, int tamanioBuffer):Nodo(buffer,bloque,nivel,tamanioBuffer) {

}

 int NodoInterno::obtenerBloque(byte buffer[],string termino) {
	int cantidad = buffer[1];
	int bloque= 0;
	int i=0;
	int desde= (i*TAMANO_ELEMENTO) + 2;
	while (i < cantidad) {
		bloque= BloqueUtils::byteArrayToInt(buffer,desde);
		string clave=  obtenerBytesString(buffer, desde + 4 , desde + TAMANO_ELEMENTO-1);
		if ((clave.compare(termino) > 0)  && (clave.compare(termino)!=0)){
			return bloque;
		}
		i++;
		desde= desde + TAMANO_ELEMENTO;
	}
	int offsetBloque= ((i-1)*TAMANO_ELEMENTO) + 2 + TAMANO_ELEMENTO;
	bloque= BloqueUtils::byteArrayToInt(buffer, offsetBloque);
	return bloque;
}

int NodoInterno::getCantidadElementos(){
	byte* buffer = getBuffer();
	int cantidad = buffer[1];
	return cantidad;
}

Elemento* NodoInterno::obtenerElementos() {
	byte* buffer= getBuffer();
	int cantidad= buffer[1];
	Elemento* elementos= new Elemento[cantidad];
	for (int i = 0; i < cantidad; i++) {
		int desde= (TAMANO_ELEMENTO*i) + 2;
		int hijoIzquierdo= BloqueUtils::byteArrayToInt(buffer, desde);
		string termino= obtenerBytesString(buffer, desde+4, desde+TAMANO_ELEMENTO-1);
		int hijoDerecho= BloqueUtils::byteArrayToInt(buffer, desde+TAMANO_ELEMENTO);
		elementos[i]= new Elemento(hijoIzquierdo,hijoDerecho,termino);
	}
	return elementos;
}

 byte* NodoInterno::obtenerBytesString(byte buffer[], int desde, int hasta) {
	byte* bytes= new byte[0];
	for (int i = desde; i <= hasta ; i++) {
		byte* aux= new byte[1];
		if (buffer[i] != 0){
			StringUtils::vecTovec(buffer, i, aux, 0, 1);
			bytes= BloqueUtils::concatena(bytes, aux);
		}else{
			return bytes;
		}
	}
	return bytes;
}

 byte* NodoInterno::obtenerByteArrayElementos(Elemento elementos[], int cantElementos,int* cantElementosBuffer){
	byte* buffer= new byte[1];

	buffer[0]= (byte)cantElementos;
	int tamanioBuffer = 1;
	for (int i = 0; i < cantElementos; i++) {
		Elemento elemento= elementos[i];
		byte* hijoIzq= BloqueUtils::intToByteArray(elemento.getHijoIzq());
		byte* clave= StringUtils::stringToArray(elemento.getClave());
		buffer= BloqueUtils::concatena(buffer, hijoIzq, tamanioBuffer, &tamanioBuffer);
		tamanioBuffer=tamanioBuffer+4;
		buffer= BloqueUtils::concatena(buffer, clave, tamanioBuffer, strlen(elemento.getClave().c_str()));
		tamanioBuffer=tamanioBuffer+strlen(elemento.getClave().c_str());
		buffer= BloqueUtils::concatena(buffer, new byte[TAMANO_ELEMENTO-4-strlen(elemento.getClave().c_str())],tamanioBuffer,TAMANO_ELEMENTO-4-strlen(elemento.getClave().c_str()));
		tamanioBuffer=tamanioBuffer+TAMANO_ELEMENTO-4-strlen(elemento.getClave().c_str());
		if (i == cantElementos-1){
			byte* hijoDer= BloqueUtils::intToByteArray(elemento.getHijoDer());
			buffer= BloqueUtils::concatena(buffer, hijoDer,tamanioBuffer,4);
			tamanioBuffer=tamanioBuffer+4;
		}
	}
	cantElementosBuffer=&tamanioBuffer;
	return buffer;
}

 byte* NodoInterno::completarBuffer(byte buffer[],int* tamanioBuffer){
	int tamanioBufferAux=TAMANO_BLOQUE_BYTES;
	byte* ret = BloqueUtils::concatena(buffer, new byte[TAMANO_BLOQUE_BYTES-*tamanioBuffer],*tamanioBuffer,TAMANO_BLOQUE_BYTES-*tamanioBuffer);
	tamanioBuffer=&tamanioBufferAux;
	return ret;
}

 Elemento* NodoInterno::eliminarPrimerElemento(Elemento elementos[],int cantidadElementos) {
	Elemento* elementosNuevos= new Elemento[cantidadElementos-1];
	StringUtils::vecTovec(elementos, 1, elementosNuevos, 0, cantidadElementos-1);
	return elementosNuevos;
}

 Elemento* NodoInterno::agregarElementoAlFinal(Elemento elementos[], Elemento elemento,int cantElementos) {
	Elemento* elementosNuevos= new Elemento[cantElementos+1];
	StringUtils::vecTovec(elementos, 0, elementosNuevos, 0, cantElementos);
	elementosNuevos[cantElementos-1]= elemento;
	return elementosNuevos;

}

 int NodoInterno::obtenerElementoaIzquierda(Elemento elementos[], Elemento elemento,int cantElementos) {
	for (int i = 0; i < cantElementos; i++) {
		Elemento elementoAux= elementos[i];
		if (elementoAux.getClave().compare(elemento.getClave()) > 0){
			return i-1;
		}
	}
	return cantElementos-1;
}

 list<Elemento*> NodoInterno::dividirElementos(Elemento elementos[],int partes,int cantElementos) {
	list<Elemento*> lista= new list<Elemento*>();
	int tamano= cantElementos/partes;
	int desde;
	if ((cantElementos % partes) > 1) tamano++;
	for (int i = 0; i < partes; i++) {
		desde= i*tamano;
		if (i == partes -1){
			if ((cantElementos % partes) != 0){
				if (partes == 2){
					tamano++;
				}else{
					tamano--;
				}
			}
		}
		Elemento* elemento= new Elemento[tamano];
		StringUtils::vecTovec(elementos, desde, elemento,0 , tamano);
		lista.push_back(elemento);
	}

	return lista;
}

 Elemento* NodoInterno::eliminarUltimoElemento(Elemento elementos[],int* cantElementos) {
	int cantElementosAux=*cantElementos-1;
	Elemento* elementosNuevos= new Elemento[*cantElementos-1];
	StringUtils::vecTovec(elementos, 0, elementosNuevos, 0, *cantElementos-1);
	cantElementos=&cantElementosAux;
	return elementosNuevos;
}

 Elemento* NodoInterno::agregarElementoAlComienzo(Elemento elementos[], Elemento elemento,int cantElementos) {
	Elemento* elementosNuevos= new Elemento[cantElementos+1];
	StringUtils::vecTovec(elementos, 0, elementosNuevos, 1, cantElementos);
	elementosNuevos[0]= elemento;
	return elementosNuevos;
}

 int NodoInterno::obtenerElementoaDerecha(Elemento elementos[], Elemento elemento,int cantElementos) {
	for (int i = 0; i < cantElementos; i++) {
		Elemento elementoAux= elementos[i];
		if (elementoAux.getClave().compare(elemento.getClave()) > 0){
			return i;
		}
	}
	return cantElementos-1;
}

 Elemento* NodoInterno::agregarElemento(Elemento elementos[], int indice, Elemento elemento,int* cantElementos) {
	int cantElementosAux=*cantElementos+1;
	Elemento* elementosNuevos= new Elemento[*cantElementos+1];
	StringUtils::vecTovec(elementos, 0, elementosNuevos, 0, indice+1);
	elementosNuevos[indice+1]= elemento;
	if (indice < *cantElementos-1){
		StringUtils::vecTovec(elementos, indice+1, elementosNuevos, indice+2, *cantElementos-indice-1);
	}
	cantElementos=&cantElementosAux;
	return elementosNuevos;
}

 Elemento* NodoInterno::unir(Elemento elementosIzquierdo[], int cantElementosIzq, Elemento elementosDerecho[], int cantElementosDer, Elemento elementoPadre) {
	Elemento* elementosNuevos= new Elemento[cantElementosIzq+cantElementosDer+1];
	StringUtils::vecTovec(elementosIzquierdo, 0, elementosNuevos, 0, cantElementosIzq);
	elementosNuevos[cantElementosIzq]= new Elemento(elementosIzquierdo[cantElementosIzq-1].getHijoDer(),elementosDerecho[0].getHijoIzq(),elementoPadre.getClave());
	StringUtils::vecTovec(elementosDerecho, 0, elementosNuevos, cantElementosIzq+1, cantElementosDer);
	return elementosNuevos;
}
