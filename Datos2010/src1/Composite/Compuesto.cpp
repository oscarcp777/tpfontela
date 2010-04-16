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
std::string Compuesto::toString(){
   return "Compuesto";
}
void Compuesto::agregarComponente(Componente* componente){
		this->listaDeComponetes.push_back(componente);
}
void Compuesto::removerComponente(Componente* componente){
	this->listaDeComponetes.remove(componente);
}
Compuesto::~Compuesto() {
//	int i=0;
//	std::list<Componente*>::iterator iter = this->listaDeComponetes.begin();
//			Componente* componente;
//			cout<<"borro Compuesto"<<endl;
//			while(i<this->getCantidadDeElelmentos()){
//				componente = (Componente*)*iter;
//				delete componente;
//				iter++;
//				i++;
//			}
}
int Compuesto::getCantidadDeElelmentos(){
	return this->listaDeComponetes.size();
}
std::list<Componente*>::iterator  Compuesto::iteratorListaDeComponetes(){
	return this->listaDeComponetes.begin();
}
void Compuesto::vaciarListaComponentes(){

	this->listaDeComponetes.clear();

}
