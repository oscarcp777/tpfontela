#include <stdio.h>
#include <list>
#include "Escenario.h"


void Escenario::addFigura(Figura *figura){
	ListaFiguras.push_back(figura);
}
void Escenario::addTextura(Textura *textura){
	std::string idTextura,path;
	idTextura = textura->getId();
	path = textura->getPath();
	//mapaTexturas[idTextura] = path; //LA COMENTE PORQUE TIRA ERROR algun error son std::string probe tirando cadenas entre "" pero igual da error
	
	
	
}
			
int Escenario::graficar(){
	/*
	se grafica asi mismo y despues hace un
	while donde recorre la listaFiguras y le dice a
	cada una figura->dibujar();
	POLIMORFISMO PUROOOOOOOOOOOOOOOOOOO que diseño PAPA :P
	
	
	*/
	return 0;
}
