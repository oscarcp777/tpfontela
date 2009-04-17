#include <stdio.h>
#include <list>
#include "Escenario.h"

Escenario::Escenario(){
	//listaFiguras = new std::list();
	//mapaTexturas  = new std::map();
	
}
void Escenario::addFigura(Figura *figura){
	this->listaFiguras.push_back(figura);
}
void Escenario::addTextura(Textura *textura){
	std::string idTextura,path;
	idTextura = textura->getId();
	path = textura->getPath();
	//this->mapaTexturas.insert("hola","chau"); //LA COMENTE PORQUE TIRA ERROR algun error son std::string probe tirando cadenas entre "" pero igual da error
	//probe utilizando pair y agregandoselo al map pero tampoco anda
	
	
}

int Escenario::sizeListaFiguras(){
	return this->listaFiguras.size();
}

std::list<Figura*>::iterator Escenario::iteratorListaFiguras(){
	return this->listaFiguras.begin();
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
