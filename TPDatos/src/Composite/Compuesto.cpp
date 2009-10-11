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
int Compuesto::getCantidadDeElelmentos(){
	return this->listaDeComponetes.size();
}
std::list<Componente*>::iterator  Compuesto::iteratorListaDeComponetes(){
	return this->listaDeComponetes.begin();
}
