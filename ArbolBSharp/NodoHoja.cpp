/*
 * NodoHoja.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include "NodoHoja.h"

NodoHoja::NodoHoja(){

}

NodoHoja::NodoHoja(byte buffer[], int bloque,int tamanioBuffer):Nodo(buffer,bloque,0,tamanioBuffer) { //se invoca al constructor padre
	cantRegistros=0;
}

RegistroIndice* NodoHoja::obtenerRegistros(){

	RegistroIndice* registros;

	registros= BloqueUtils::obtenerBytes(getBuffer(), 1, getTamanioBuffer()-5);

	cantRegistros = getTamanioBuffer()-5;

	return registros;
}

void NodoHoja::setCantidadRegistros(int cantidadRegistros){
	this->cantRegistros = cantidadRegistros;
}

int NodoHoja::getCantidadRegistros(){
	return cantRegistros;
}

RegistroIndice NodoHoja::obtenerRegistroIndice(string termino){
	RegistroIndice* registros= obtenerRegistros();
	int i= 0;
	int cant = getTamanioBuffer()-5;
	while (i < cant) {
		RegistroIndice registro= registros[i];
		if (registro.getTermino().compare(termino.c_str())){
			return registro;
		}
		i++;
	}
	//throw new RegistroNoEncontradoException();

}

void NodoHoja::modificarRegistro(RegistroIndice registro) {
	RegistroIndice* registros=obtenerRegistros();

	int i= 0;
	bool listo= false;
	int cantRegistros = getTamanioBuffer()-5;
	while ((i<cantRegistros) && (!listo)){
		RegistroIndice reg= registros[i];
		if (reg.getTermino().compare(registro.getTermino().c_str())==0){
			registros[i]= registro;
			listo= true;
		}
		i++;
	}
	int c = 4;
	byte* bytes= obtenerByteArrayRegistros(registros,cantRegistros,&c);
	byte* nivel= new byte[1];
	nivel[0]= 0;
	byte* buffer= BloqueUtils::concatena(nivel, bytes,1,cantRegistros);
	int proxHoja= BloqueUtils::byteArrayToInt(getBuffer(),getTamanioBuffer()-4);
	buffer= BloqueUtils::concatena(buffer, new byte[getTamanioBuffer() -4 - (cantRegistros + 1)],cantRegistros+1,getTamanioBuffer() -4 - (cantRegistros + 1));
	buffer= BloqueUtils::concatena(buffer, BloqueUtils::intToByteArray(proxHoja),getTamanioBuffer() -4,4 );
	setBuffer(buffer);
}

 byte* NodoHoja::obtenerByteArrayRegistros(RegistroIndice registros[],int cantRegistros,int* tamanioArray) {
/*
		int i=0;

		for(int i=0;i<cantRegistros;i++){
			registros[i].
		}

		byte bytesRegistro[] = armarBytesRegistro(termino, pesoGlobal, terminoAnterior);
		ret = BlockUtils.concatena(ret, bytesRegistro);

		return ret; */            ///VERRRRRRRRRR
	byte* arreglo = new byte[cantRegistros];
 	return arreglo;
}

 byte* NodoHoja::completarBuffer(byte buffer[],int proxHoja,int* tamanioBuffer){
	buffer= BloqueUtils::concatena(buffer, new byte[getTamanioBuffer()-(*tamanioBuffer-5)-4],*tamanioBuffer,getTamanioBuffer()-(*tamanioBuffer-5)-4);
	int tamanioNuevoBuffer = getTamanioBuffer()-(*tamanioBuffer-5)-4+*tamanioBuffer;
	byte* nuevoBuffer = BloqueUtils::concatena(buffer, BloqueUtils::intToByteArray(proxHoja),tamanioNuevoBuffer,4);
	tamanioNuevoBuffer = tamanioNuevoBuffer + 4;
	tamanioBuffer=&tamanioNuevoBuffer; //actualizo el tamañao del buffer al tamaño del nuevo buffer
	return nuevoBuffer;
}

byte* NodoHoja::agregarRegistro(RegistroIndice registro) {
	RegistroIndice* registros= agregarRegistroNuevo(registro);
	int x=2;
	byte* bytesRegistros= obtenerByteArrayRegistros(registros,1,&x);
	byte* byteNivel= new byte[1];
	byteNivel[0]= 0;
	byte* bufferModificado= BloqueUtils::concatena(byteNivel, bytesRegistros, 2, 1+2);
	return bufferModificado;
}

RegistroIndice* NodoHoja::agregarRegistroNuevo(RegistroIndice registro) {
	RegistroIndice* registros= obtenerRegistros();
	RegistroIndice* regs= new RegistroIndice[cantRegistros + 1];
	bool stop= false;
	int i= 0;
	while ((!stop) && (i < cantRegistros)){
		if (registros[i].getTermino().compare(registro.getTermino().c_str()) > 0){
			stop= true;
		}else{
			regs[i]= registros[i];
			i++;
		}
	}
	regs[i]= registro;
	int j=i+1;
	while (i < cantRegistros) {
		regs[j]= registros[i];
		j++;
		i++;
	}
	cantRegistros=cantRegistros+1; //*******??????ver si esta bien hacer esta incrementacion aqui
	return regs;

}

 list<RegistroIndice*> NodoHoja::dividirRegistrosIndice(RegistroIndice registros[], int partes,int tamanioRegistros) {
	list<RegistroIndice*> lista=new list<RegistroIndice*>();
	int tamano= tamanioRegistros/partes;
	int tamanoUltimo= 0;
	for (int i = 0; i < partes-1; i++) {
		RegistroIndice* registro = new RegistroIndice[tamano];
		int k= i*tamano;
		tamanoUltimo= tamanoUltimo + tamano;
		for (int j = 0; j < tamanioRegistros; j++) {
			registro[j]= registros[k];
			k++;
		}
		lista.push_back(registro);
	}
	tamanoUltimo= tamanioRegistros-tamanoUltimo;

	RegistroIndice* registro= new RegistroIndice[tamanoUltimo];
	int k=0;
	for (int desde= (tamanioRegistros/partes) * (partes - 1); desde < tamanioRegistros; desde++){
		registro[k]= registros[desde];
		k++;
	}
	lista.push_back(registro);

	return lista;
}

 RegistroIndice* NodoHoja::eliminarUltimoRegistro(RegistroIndice registros[],int* tamanioRegistros) {
	int tamanioRegistrosAux=*tamanioRegistros-1;
	RegistroIndice* registrosNuevos= new RegistroIndice[tamanioRegistros-1];
	StringUtils::vecTovec(registros, registrosNuevos, tamanioRegistros-1);
	tamanioRegistros=&tamanioRegistrosAux;
	return registrosNuevos;
}


 RegistroIndice* NodoHoja::agregarRegistroAlComienzo(RegistroIndice registros[], RegistroIndice registro,int* tamanioRegistros) {
	int cantRegistrosAux=*tamanioRegistros+1;

	RegistroIndice* registrosNuevos= new RegistroIndice[tamanioRegistros+1];

	StringUtils::vecTovec(registros, 0, registrosNuevos, 1, tamanioRegistros);
	registrosNuevos[0]= registro;
	tamanioRegistros=&cantRegistrosAux;
	return registrosNuevos;
}

 RegistroIndice* NodoHoja::eliminarPrimerRegistro(RegistroIndice registros[],int* tamanioRegistros) {
	int tamanioRegistrosAux = *tamanioRegistros-1;
	RegistroIndice* registrosNuevos= new RegistroIndice[tamanioRegistros-1];
	StringUtils::vecTovec(registros, 1, registrosNuevos, 0, tamanioRegistros-1);
	tamanioRegistros=&tamanioRegistrosAux;
	return registrosNuevos;
}

 RegistroIndice* NodoHoja::agregarRegistroAlFinal(RegistroIndice registros[], RegistroIndice registro,int* tamanioRegistros) {
	int tamanioRegistrosAux = *tamanioRegistros;
	RegistroIndice* registrosNuevos= new RegistroIndice[tamanioRegistros+1];
	StringUtils::vecTovec(registros, 0, registrosNuevos, 0, tamanioRegistros);
	registrosNuevos[tamanioRegistros-1]= registro;
	tamanioRegistrosAux=tamanioRegistrosAux+1;
	tamanioRegistros=&tamanioRegistrosAux;
	return registrosNuevos;

}

 RegistroIndice* NodoHoja::unir(RegistroIndice registrosIzquierdo[],int tamanioRegIzq, RegistroIndice registrosDerecho[],int tamanioRegDer) {
	RegistroIndice* registrosNuevos= new RegistroIndice[tamanioRegIzq+tamanioRegDer];
	StringUtils::vecTovec(registrosIzquierdo, 0, registrosNuevos, 0, tamanioRegIzq);
	StringUtils::vecTovec(registrosDerecho, 0, registrosNuevos, tamanioRegIzq, tamanioRegDer);
	return registrosNuevos;
}

NodoHoja::~NodoHoja() {

}
