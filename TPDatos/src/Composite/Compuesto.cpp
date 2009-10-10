/*
 * Compuesto.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "Compuesto.h"

Compuesto::Compuesto() {
	// TODO Auto-generated constructor stub

}
void Compuesto::agregarComponente(Componente* componente){
		this->listaDeComponetes.push_back(componente);

}
Compuesto::~Compuesto() {
	// TODO Auto-generated destructor stub
}
int Compuesto::getCantidadDeElelmentos(){
	return this->listaDeComponetes.size();
}
std::list<Componente*>::iterator  Compuesto::iteratorListaDeComponetes(){
	return this->listaDeComponetes.begin();
}
