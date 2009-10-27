/*
 * RegistroConsulta.cpp
 *
 *  Created on: Oct 26, 2009
 *      Author: dan
 */

#include "RegistroConsulta.h"

RegistroConsulta::RegistroConsulta(){

}
/**
	 * Constructor
	 * @param termino
	 * @param listaInvertida
	 */
	RegistroConsulta::RegistroConsulta(string termino,double pesoGlobal) {
		this->termino= termino;
		this->pesoGlobal= pesoGlobal;
	}


	/**
	 * Devuelve el termino
	 * @return El termino
	 */

	string RegistroConsulta::getTermino(){

		return termino;

	}

	/**
	 * Devuelve el peso global
	 * @return Peso global
	 */

	double RegistroConsulta::getPesoGlobal() {

		return pesoGlobal;

	}

	int RegistroConsulta::compareTo(RegistroConsulta o) {
		if (o.getPesoGlobal() < pesoGlobal) return -1;
		if ((o.getPesoGlobal() == pesoGlobal) && (o.getTermino().compare(termino.c_str()))) return -1;
		return 1;
	}

	RegistroConsulta::~RegistroConsulta(){

	}
