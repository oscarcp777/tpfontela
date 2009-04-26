#include <stdio.h>
#include <list>
#include "Escenario.h"
#include "Dibujar.h"
#include <utility>
	//pasar estas constantes a Constantes.h
const int RESOLUCION_640=640;
const int RESOLUCION_640_ALTO=480;
const int RESOLUCION_640_ANCHO=640;
const int RESOLUCION_800=800;
const int RESOLUCION_800_ALTO=600;
const int RESOLUCION_800_ANCHO=800;
const int RESOLUCION_1024=1024;
const int RESOLUCION_1024_ALTO=768;
const int RESOLUCION_1024_ANCHO=1024;
const int RESOLUCION_1280=1280;
const int RESOLUCION_1280_ALTO=768;
const int RESOLUCION_1280_ANCHO=1280;
const int RESOLUCION_BIT=32;

Escenario::Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	this->setResolucion(800);
	this->colorFondoFig = "XXXYYYZZZ";
	this->texturaFig = "id";
	this->colorLineaString = "XXXYYYZZZ";
	this->colorFondoEsc = "XXXYYYZZZ";
	this->texturaEsc = "id2";
	this->setColorFondoEscenario(new Color(255,255,255));
	this->setColorFondoFiguras(new Color( 255, 215 , 0));
	this->setColorLinea(new Color(0,0,0));
	
}

Escenario* Escenario::unicaInstanciaEscenario = NULL;

Escenario* Escenario::obtenerInstancia(){
	
	if(!Escenario::unicaInstanciaEscenario){
		Escenario::unicaInstanciaEscenario = new Escenario();
	}
	
	return Escenario::unicaInstanciaEscenario;
}
void  Escenario::setColorFondoEscenario(Color* colorFondoEscenario){
  this->colorFondoEscenario=colorFondoEscenario;
}
void  Escenario::setColorFondoFiguras(Color* colorFondoFiguras){
 this->colorFondoFiguras=colorFondoFiguras;
}
void  Escenario::setColorLinea(Color* colorLinea){
 this->colorLinea=colorLinea;
}
Color* Escenario::getColorFondoEscenario(){
return	this->colorFondoEscenario;
}
Color* Escenario::getColorFondoFiguras(){
return	this->colorFondoFiguras;
}
Color* Escenario::getColorLinea(){
return this->colorLinea;
}
void  Escenario::setAncho(int ancho){
this->ancho=ancho;
}
int   Escenario::getAncho(){
return	this->ancho;
}
void  Escenario::setAlto(int alto){
	this->alto=alto;
}
int   Escenario::getAlto(){
	return this->alto;
}
void  Escenario::setResolucion(int resolucion){
    if(resolucion==RESOLUCION_640){
       	this->alto=RESOLUCION_640_ALTO;
		this->ancho=RESOLUCION_640_ANCHO;
	}
	if(resolucion==RESOLUCION_800){
       	this->alto=RESOLUCION_800_ALTO;
		this->ancho=RESOLUCION_800_ANCHO;
	}
	if(resolucion==RESOLUCION_1024){
       	this->alto=RESOLUCION_1024_ALTO;
		this->ancho=RESOLUCION_1024_ANCHO;
	}
	if(resolucion==RESOLUCION_1280){
       	this->alto=RESOLUCION_1280_ALTO;
		this->ancho=RESOLUCION_1280_ANCHO;
	}
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

SDL_Surface* Escenario::getScreen(){
	return this->screen;

}



int Escenario::graficar(){
	
	int done = 0;
	SDL_Event event;
	SDL_Surface *screen;
	// Iniciar SDL
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
        exit(1);
	 }
  //seteamos el titulo a la barra
  SDL_WM_SetCaption("    Taller de Programacion Grupo Nro:3   GRAFICADOR  ","       Taller de Programacion Grupo Nro:3   GRAFICADOR  ");  

	screen = SDL_SetVideoMode(this->getAncho(),this->getAlto(),32, SDL_SWSURFACE | SDL_DOUBLEBUF );
	if(!screen){
		std::cout<<"No se pudo iniciar la pantalla: %s\n"<< SDL_GetError()<<"\n";
		SDL_Quit();
		exit(-1);
	}
	Dibujar::pintarPantalla(screen);
	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int i = 1;
	Figura *figura;
	std::cout<<"sizeFigura"<<sizeListaFiguras();
	while(i<=this->sizeListaFiguras()){
	
	figura = *iter;
	figura->dibujar(screen);
	iter++;
	i++;
	}
	while (done == 0) {
		SDL_Flip (screen);
		
	// Comprobando teclas para opciones
		while (SDL_PollEvent(&event)) {
			// Cerrar la ventana
			if (event.type == SDL_QUIT) { done = 1; }
			// Pulsando una tecla
			if (event.type == SDL_KEYDOWN) {
			done = 1;
			}
		}
	}
	;
	return 0;
}
