/*
 * Bloque.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Bloque.h"
#include <list>
Bloque::Bloque(int tamanio, int id):Componente(tamanio) {

	// TODO Auto-generated constructor stub
	this->setId(id);
}

Bloque::~Bloque() {
	int i=0;
		std::list<Componente*>::iterator iter = this->listaDeComponetes.begin();
				Componente* componente;

				while(i<this->getCantidadDeElelmentos()){
					componente = (Componente*)*iter;
					delete componente;
					iter++;
					i++;
				}
}

std::string Bloque::getDatosRegistro()
{
	std::list<Componente*>::iterator iteraRegistros = this->iteratorListaDeComponetes();
	int i=0;
	Componente* componente;
	std::string datosBloque = "";


	while (i<this->getCantidadDeElelmentos()){
		componente = (Componente*)*iteraRegistros;
		datosBloque += componente->getDatosRegistro();
		iteraRegistros++;
		i++;
	}

	return datosBloque;
}

void Bloque::setDatosRegistro(std::string datosRegistro)
{
	//this->datosRegistro = datosRegistro;
}

void Bloque::serializar(){

}

void Bloque::hidratar(){

}
