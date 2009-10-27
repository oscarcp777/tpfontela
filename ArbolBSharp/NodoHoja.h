/*
 * NodoHoja.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include <list>
#include "Nodo.h"
#include "StringUtils.h"
#include "Excepciones/Exception.h"
#include "Indice/RegistroIndice.h"
#include "BloqueUtils.h"
#include "Constantes.h"

#ifndef NODOHOJA_H_
#define NODOHOJA_H_

class NodoHoja: public Nodo{

	public:
			NodoHoja();
			NodoHoja(byte buffer[], int bloque,int tamanioBuffer);
			RegistroIndice* obtenerRegistros();
			RegistroIndice obtenerRegistroIndice(string termino);
			void modificarRegistro(RegistroIndice registro);
			static byte* obtenerByteArrayRegistros(RegistroIndice registros[], int cantRegistros,int* tamanioArray);
			static byte* completarBuffer(byte buffer[],int proxHoja,int* tamanioBuffer);
			byte* agregarRegistro(RegistroIndice registro);
			int getCantidadRegistros();
			void setCantidadRegistros(int cantidadRegistros);
			RegistroIndice* agregarRegistroNuevo(RegistroIndice registro);
			static list<RegistroIndice*> dividirRegistrosIndice(RegistroIndice registros[], int partes,int tamanioRegistros);
			static RegistroIndice* eliminarUltimoRegistro(RegistroIndice registros[],int* tamanioRegistros);
			static RegistroIndice* agregarRegistroAlComienzo(RegistroIndice registros[], RegistroIndice registro,int* tamanioRegistros);
			static RegistroIndice* eliminarPrimerRegistro(RegistroIndice registros[],int* tamanioRegistros);
			static RegistroIndice* agregarRegistroAlFinal(RegistroIndice registros[], RegistroIndice registro,int* tamanioRegistros);
			static RegistroIndice* unir(RegistroIndice registrosIzquierdo[],int tamanioRegIzq, RegistroIndice registrosDerecho[],int tamanioRegDer);
	private:
			int cantRegistros;
};

#endif /* NODOHOJA_H_ */
