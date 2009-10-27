/*
 * Indice.cpp
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

/**
 * Clase indice, contiene y maneja el lexico y las listas invertidas
 * @author Diego Saez y Facundo Zarate
 *
 */

#include "Indice.h"

	Indice::Indice(){
		this->lexico= new ArbolBSharp();
	}

	/**
	 * Agrega un registro al indice
	 * @param registroIndexador Registro a agregar
	 * @param cantidadDocumentosTotal Cantidad de documentos total para calcular el peso global
	 * @throws IOException
	 */

	void Indice::agregarRegistro(RegistroIndexador registroIndexador, int cantidadDocumentosTotal){
		lexico.abrir();

//		try {
			RegistroIndice registroIndice = lexico.buscarTermino(registroIndexador.getTermino());
			lexico.modificarRegistro(new RegistroIndice(registroIndice.getTermino(),1000));
//		} catch (RegistroNoEncontradoException e) {
			double pesoGlobal= calcularPesoGlobal(cantidadDocumentosTotal);
//			try {
				lexico.insertar(new RegistroIndice(registroIndexador.getTermino(),pesoGlobal));
//			} catch (ClaveExistenteException e1) {
//				// Es seguro que no existe la clave ya que se busco antes y no se encontro
//			}
		}
		lexico.cerrar();

	}

	/**
	 * Busca un registro a partir del termino
	 * @param termino Termino a buscar
	 * @return RegistroConsulta
	 * @throws RegistroNoEncontradoException
	 * @throws IOException
	 */

	RegistroConsulta Indice::buscarRegistro(string termino){
		lexico.abrir();

		RegistroIndice registroIndice= lexico.buscarTermino(termino);
		lexico.cerrar();
		return new RegistroConsulta(termino,registroIndice.getPesoGlobal());
	}

	double Indice::calcularPesoGlobal(list<RegistroDocumento> lista, int cantidadDocumentosTotal) {
		return log10(cantidadDocumentosTotal/(lista.size()));
	}
}
