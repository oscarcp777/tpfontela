/*
 * Bloque.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Bloque.h"
#include <list>
Bloque::Bloque(int tamanio, int id) {

	// TODO Auto-generated constructor stub
	this->setTamanio(tamanio);
	this->setId(id);
}

Bloque::~Bloque() {
//Comente estas lineas porque se llama solo al destructor de Compuesto desde aca (por la herencia)
// y rompia cuando queria destruir, supongo destruye bien

//	int i=0;
//		std::list<Componente*>::iterator iter = this->listaDeComponetes.begin();
//				Componente* componente;
//
//				while(i<this->getCantidadDeElelmentos()){
//					componente = (Componente*)*iter;
//					delete componente;
//					iter++;
//					i++;
//				}
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
