#include <stdio.h>
#include <list>
#include "Escenario.h"
#include <utility>
#include "archivoTexto.h"
#include "Posicion.h"
#include "Teclado.h"
#include "Pad.h"
#include "Tejo.h"
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
const string configDefaultEscenario = "config Default Escenario.txt";
Escenario::Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)

	this->setResolucion(RESOLUCION_800);
	this->texturaFig = "FigDefault";
	this->texturaEsc = "EscDefault";
	this->setColorFondoEscenario(new Color(0,0,0));
	this->setColorFondoFiguras(new Color(42,0,246));
	this->setColorLinea(new Color(255,0,0));
	inicializarLog(this->log, "errores.err");
	this->validador = new  Validador("config Validador.txt","config Atributos.txt");
	escribirTituloLog(*(this->getLog()),"DESCRIPCION DE ERRORES");
	this->validador->setLog(&(this->log));

	//levanto del archivo siguiente las texturas por default para el escenario
	ArchivoTexto miArchivoDefault(configDefaultEscenario);
	string linea;
	//la primer linea tiene el path de textura figura por default
	miArchivoDefault.leerLinea(linea);
	Textura * texturaFigDefault = new Textura("FigDefault", linea);
//	this->addTextura(texturaFigDefault);
	//la segunda linea tiene el path de textura escenario por default
	miArchivoDefault.leerLinea(linea);
	Textura * texturaEscDefault = new Textura("EscDefault", linea);
//
	this->addTextura(texturaEscDefault);


}

Validador*  Escenario::getValidador(){
	return this->validador;
}
Escenario::~Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	destruirLog(this->log);
	delete this->colorLinea;
	delete this->colorFondoEscenario;
	delete this->colorFondoFiguras;
	this->validador->~Validador();
	list<Textura*>::iterator iterTextura;
	Textura* textura;
	iterTextura=this->listaTexturas.begin();
	while(iterTextura !=this->listaTexturas.end()){
		textura=*iterTextura;
		delete textura;
		iterTextura++;
	}
	list<Figura*>::iterator iterFiguras;
	Figura* figura;
		iterFiguras=this->listaFiguras.begin();
		while(iterFiguras !=this->listaFiguras.end()){
			figura=*iterFiguras;
			delete figura;
			iterFiguras++;
		}

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
	//si existe el id de figura tiro error y no lo agrego
	if(this->existeIdFigura(figura->getId())){
		escribirMensajeLog(this->log,"error: idFigura duplicado, ya existia una figura con el id: " + figura->getId() );
	}
	//sino la agrego
	else{
	this->listaFiguras.push_back(figura);
	}
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

	int res = this->texturaEsc.compare("NULL");
	SDL_Surface *imagen = NULL;

	if( res!=0){
		//si no tiene NULL en texturaEsc
		std::string path = this->obtenerPathTextura(this->texturaEsc);

		if(path.compare("NULL") != 0){
			//si se encontro el path de la textura
			imagen = IMG_Load (path.begin());
			imagen = Figura::ScaleSurface(imagen, this->getAncho(), this->getAlto());
			SDL_Rect rect;
			rect.x =0;
			rect.y =0;
			rect.w = this->getAncho();
			rect.h = this->getAlto();
			SDL_BlitSurface(imagen, NULL,this->screen, &rect);

			if(!imagen) {
				//si NO se levanto bien la imagen (este es el caso que esta el id en la lista textura, se obtiene el path pero la imagen no esta en ese directorio
				escribirMensajeLog(this->log,"error al intentar cargar la imagen: "+path);
				SDL_Rect dest;
				dest.x = 0;
				dest.y = 0;
				dest.w = this->screen->w;
				dest.h = this->screen->h;
				SDL_Color color = this->getColorFondoEscenario();
				SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));
			}

		}
		else{
			//si NO se encontro el path de la textura, es porque el id no existe en la lista
			escribirMensajeLog(this->log,"no se encontro el path correspondiente a texturaEsc: "+this->texturaEsc);
			SDL_Rect dest;
			dest.x = 0;
			dest.y = 0;
			dest.w = this->screen->w;
			dest.h = this->screen->h;
			SDL_Color color = this->getColorFondoEscenario();
			SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));
		}

	}


}

std::string Escenario::obtenerPathTextura(std::string id){
	std::list<Textura*>::iterator iter;
	Textura *textura;
	iter = this->iteratorListaTexturas();
	int i=1;
	std::string idAux = "NULL";

	while(i<=this->sizeListaTexturas()){
		textura = *iter;

		if(textura->getId().compare(id)==0){
			return textura->getPath();
		}

		else{
			i++;
			iter++;
		}

	}
	return idAux;

}

bool Escenario::existeIdFigura(std::string idFigura){
	bool existe = false;
	std::list<Figura*>::iterator iter;
	Figura *figura;
	iter = this->iteratorListaFiguras();
	int i=1;
	while(i<=this->sizeListaFiguras()){
		figura = *iter;
		if(figura->getId().compare(idFigura) == 0){
			return true;
		}
		else{
			i++;
			iter++;
		}
	}
	return existe;
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
	atexit(SDL_Quit);

	 // Comprobamos que sea compatible el modo de video

	if(SDL_VideoModeOK(this->getAncho(), this->getAlto(), 32, SDL_SWSURFACE|SDL_DOUBLEBUF) == 0) {

	std::cout<< "Modo no soportado: " << SDL_GetError() << endl;
	 exit(1);

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
	Posicion *posicion=  new Posicion(150,150);
	while(i<=this->sizeListaFiguras()){
		figura = *iter;
	figura->dibujar(this->screen);
		iter++;
		i++;
	}

/*	// Teclado para controlar al personaje
				 Teclado teclado;

			// Lo mostramos por pantalla
				 Pad* padCliente1=this->getPadCliente1();
				 	padCliente1->getFigura()->dibujar(this->screen);
				 		std::cout<< "padv1: "  << endl;
				 	    Pad* padCliente2=this->getPadCliente2();
				 	    padCliente2->getFigura()->dibujar(this->screen);
				 	    std::cout<< "padv1: "  << endl;
				 		 Tejo* tejo=this->getTejo();
				 		 tejo->getFigura()->dibujar(this->screen);
				 		 std::cout<< "padv1: " << endl;
			 // Variables auxiliares
			 SDL_Event evento;
			 bool terminar = false;
				 int x0, y0;

				 // Game loop

				 while(terminar == false) {

				// Actualizamos el estado del teclado
				
			 teclado.actualizar();

			// Variables de control para saber si
				 // tenemos que refrescar la pantalla o no

				 x0 = padCliente1->getX();
			 y0 = padCliente1->getY();

			// Actualización lógica de la posición
			 if(teclado.pulso(Teclado::TECLA_SUBIR)) {
				 padCliente1->subir_y();
			 }

				 if(teclado.pulso(Teclado::TECLA_BAJAR)) {
				 padCliente1->bajar_y();
				 }
			 if(teclado.pulso(Teclado::TECLA_IZQUIERDA)) {
			 padCliente1->retrasar_x();
			 }
				 if(teclado.pulso(Teclado::TECLA_DERECHA)) {

			 padCliente1->avanzar_x();

			}


			 // Si existe modificación dibujamos

			 if(x0 != padCliente1->getX() || y0 != padCliente1->getY()) {
				 std::cout << "= Posición actual del personaje" << endl;
				 std::cout << "- X: " << padCliente1->getX() << endl;
				 std::cout << "- Y: " << padCliente1->getY() << endl;

				 // Dibujamos al personaje en su posición nueva

				 Uint32 negro = SDL_MapRGB(this->getScreen()->format, 0, 0, 0);

				 SDL_FillRect(this->getScreen(), NULL, negro);
					padCliente1->getFigura()->dibujar(this->screen);
			//	 	padCliente1->dibujar(this->screen);
				 SDL_Flip(this->getScreen());
				 }


				 // Control de Eventos

				 while(SDL_PollEvent(&evento)) {
			 if(evento.type == SDL_KEYDOWN) {
			 if(evento.key.keysym.sym == SDLK_ESCAPE)
				 terminar = true;
				 }
				 if(evento.type == SDL_QUIT)
			 terminar = true;

				 }

				 }

				SDL_FreeSurface(this->getScreen());
				SDL_Quit();*/
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

void Escenario::setPadCliente1(Pad *padCliente1){
	this->padCliente1 = padCliente1;
}

void Escenario::setPadCliente2(Pad *padCliente2){
	this->padCliente2 = padCliente2;
}

void Escenario::setTejo(Tejo *tejo){
	this->tejo = tejo;
}

Pad* Escenario::getPadCliente1(){
	return this->padCliente1;
}

Pad* Escenario::getPadCliente2(){
	return this->padCliente2;
}

Tejo* Escenario::getTejo(){
	return this->tejo;
}
