#include <stdio.h>
#include <list>
#include "Escenario.h"
#include <utility>

Escenario::Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	this->resolucion = 800;
	this->colorFondoFig = "XXXYYYZZZ";
	this->texturaFig = "id";
	this->colorLinea = "XXXYYYZZZ";
	this->colorFondoEsc = "XXXYYYZZZ";
	this->texturaEsc = "id2";
	
}

Escenario* Escenario::unicaInstanciaEscenario = NULL;

Escenario* Escenario::obtenerInstancia(){
	
	if(!Escenario::unicaInstanciaEscenario){
		Escenario::unicaInstanciaEscenario = new Escenario();
	}
	
	return Escenario::unicaInstanciaEscenario;
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
	
	SDL_Surface *screen;
	
	screen = SDL_SetVideoMode(640,480,16, SDL_SWSURFACE | SDL_DOUBLEBUF );
	if(!screen){
		printf("No se pudo iniciar la pantalla: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int i = 1;
	Figura *figura;

	while(i<=this->sizeListaFiguras()){
	figura = *iter;
	figura->dibujar(screen);
	iter++;
	i++;
	}
	
	SDL_Flip (screen);	
	system("PAUSE");
	
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
