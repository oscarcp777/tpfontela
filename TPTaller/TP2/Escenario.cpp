#include <stdio.h>
#include <list>
#include "Escenario.h"
#include <utility>

Escenario::Escenario(){
	//listaFiguras = new std::list();
	//mapaTexturas  = new std::map();
	
}
void Escenario::addFigura(Figura *figura){
	this->listaFiguras.push_back(figura);
}

void Escenario::addTextura(Textura *textura){
	this->listaTexturas.push_back(textura);
	
}

int Escenario::sizeListaFiguras(){
	return this->listaFiguras.size();
}


int Escenario::sizeListaTexturas(){
	return this->listaTexturas.size();
}

std::list<Figura*>::iterator Escenario::iteratorListaFiguras(){
	return this->listaFiguras.begin();
}
		

std::list<Textura*>::iterator Escenario::iteratorListaTexturas(){
	return this->listaTexturas.begin();
}

std::string Escenario::obtenerPathTextura(std::string id){
	std::list<Textura*>::iterator iter;
	Textura *textura;
	bool fin = false;
	iter = this->iteratorListaTexturas();
	int i=1;
	
	while(i<=this->sizeListaTexturas() && fin==false){
	textura = *iter;
	
	if(textura->getId().compare(id)==0){
		fin = true;
		return textura->getPath();
	}

	else{
		i++;
		iter++;
	}

	}

}

int Escenario::graficar(){
	/*
	se grafica asi mismo y despues hace un
	while donde recorre la listaFiguras y le dice a
	cada una, figura->dibujar();
	POLIMORFISMO PUROOOOOOOOOOOOOOOOOOO que diseño PAPA :P
	*/
	std::cout<<"SE GRAFICA EL ESCENARIO \n";
	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int i = 1;
	Figura *figura;

	while(i<=this->sizeListaFiguras()){
	figura = *iter;
	figura->dibujar();
	iter++;
	i++;
	}

	return 0;
}
