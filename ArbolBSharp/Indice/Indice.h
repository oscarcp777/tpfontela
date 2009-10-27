/*
 * Indice.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */
#include <list>
#include <math.h>
#include "../Excepciones/Exception.h"
#include "../ArbolBSharp.h"
#include "RegistroIndexador.h"
#include "RegistroConsulta.h"

#ifndef INDICE_H_
#define INDICE_H_

class Indice{
	public:
			 Indice();
			 void agregarRegistro(RegistroIndexador registroIndexador, int cantidadDocumentosTotal);
			 RegistroConsulta buscarRegistro(string termino);
			 double calcularPesoGlobal(list<RegistroDocumento> lista, int cantidadDocumentosTotal);

	private:
			 ArbolBSharp lexico;

};

#endif /* INDICE_H_ */
