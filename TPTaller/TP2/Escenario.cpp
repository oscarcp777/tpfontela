#include <stdio.h>
#include <list>
#include "Escenario.h"
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

	this->setResolucion(RESOLUCION_800);
	this->texturaFig = "id";
	this->texturaEsc = "id";
	this->colorLinea = new Color(255,0,0);
	this->setColorFondoEscenario(new Color(255,255,255));
	this->setColorFondoFiguras(new Color( 255, 215 , 0));
	this->setColorLinea(new Color(0,255,0));
	inicializarLog(this->log, "errores.err");
	this->validador = new  Validador("config Validador.txt","config Atributos.txt");
	escribirTituloLog(*(this->getLog()),"DESCRIPCION DE ERRORES");
	this->validador->setLog(&(this->log));

}
Validador*  Escenario::getValidador(){
	return this->validador;
}
Escenario::~Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	destruirLog(this->log);


}

int Escenario::cargarArchivo(std::string nombreArchivo){
	return this->validador->validarSintaxis(nombreArchivo);

}

Escenario* Escenario::unicaInstanciaEscenario = NULL;
void Escenario::setTexturaFig(std::string texturaFig){
    this->texturaFig=texturaFig;
}
std::string Escenario::getTexturaFig(){
	 return this->texturaFig;
}
std::string Escenario::getTexturaEsc(){
	 return this->texturaEsc;
}
void Escenario::setTexturaEsc(std::string texturaEsc){
	 this->texturaEsc=texturaEsc;
}
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
SDL_Color Escenario::getColorFondoEscenario(){
return	this->colorFondoEscenario->getColor();
}
SDL_Color Escenario::getColorFondoFiguras(){
return	this->colorFondoFiguras->getColor();
}
SDL_Color Escenario::getColorLinea(){
return this->colorLinea->getColor();
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
int Escenario::getResolucion(){
	return this->resolucion;
}
void  Escenario::setResolucion(int resolucion){
	this->resolucion=resolucion;
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

void Escenario::setIdTextura(std::string idTextura){
	this->texturaEsc = idTextura;
}

Log* Escenario::getLog(){
	return &(this->log);
}


void Escenario::pintarPantalla(){
	std::cout<<"ENTRO AL IF \n";
	int res = this->texturaEsc.compare("NULL");
	SDL_Surface *imagen = NULL;

	if( res!=0){

		std::string path = this->obtenerPathTextura(this->texturaEsc);

		imagen = IMG_Load (path.begin());
		imagen = Figura::ScaleSurface(imagen, this->getAncho(), this->getAlto());
		SDL_Rect rect;
		rect.x =0;
		rect.y =0;
		rect.w = this->getAncho();
		rect.h = this->getAlto();
		SDL_BlitSurface(imagen, NULL,this->screen, &rect);
	}
	if(!imagen) {

		SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = this->screen->w;
		dest.h = this->screen->h;
		SDL_Color color = this->getColorFondoEscenario();
		SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));

	}
}

std::string Escenario::obtenerPathTextura(std::string id){
	std::list<Textura*>::iterator iter;
	Textura *textura;
	bool fin = false;
	iter = this->iteratorListaTexturas();
	int i=1;
	std::string idAux = "NULL";

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
	return idAux;

}

SDL_Surface* Escenario::getScreen(){
	return this->screen;

}

int Escenario::graficar(){

	int done = 0;
	SDL_Event event;

	// Iniciar SDL
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
        std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar SDL: " + aux );
		return -1;
	 }

	 //seteamos el titulo a la barra
  SDL_WM_SetCaption("    Taller de Programacion Grupo Nro:3   GRAFICADOR  ","       Taller de Programacion Grupo Nro:3   GRAFICADOR  ");

	this->screen = SDL_SetVideoMode(this->getAncho(),this->getAlto(),32, SDL_SWSURFACE | SDL_DOUBLEBUF );
	if(!screen){
		std::cout<<"No se pudo iniciar la pantalla: %s"<<SDL_GetError();
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar la pantalla: " + aux );
		return -1;
	}

	this->pintarPantalla();

	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int i = 1;
	Figura *figura;

	while(i<=this->sizeListaFiguras()){
		figura = *iter;
		figura->dibujar(this->screen);
		iter++;
		i++;
	}
	while (done == 0) {

		SDL_Flip (this->screen);

	// Comprobando teclas para opciones
		while (SDL_PollEvent(&event)) {
			// Cerrar la ventana
			if (event.type == SDL_QUIT) {
				done = 1;
			}
			// Pulsando una tecla
			if (event.type == SDL_KEYDOWN) {
			done = 1;
			}
		}
	}

	return 0;
}

